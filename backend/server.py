from flask import Flask, request, jsonify, render_template, send_from_directory
import subprocess
import uuid
import os
import time
import shutil
import re
import random

app = Flask(
    __name__,
    static_folder=os.path.join(os.path.dirname(__file__), "../static"),
    template_folder=os.path.join(os.path.dirname(__file__), "../templates")
)

CODE_DIR = "/tmp/cpp_ide"
os.makedirs(CODE_DIR, exist_ok=True)

SAVES_DIR = os.path.join(os.path.dirname(__file__), "../saves")
os.makedirs(SAVES_DIR, exist_ok=True)

@app.route("/")
def index():
    """Render the IDE, injecting templates/main.cpp as initial_code."""
    main_cpp_path = os.path.join(app.template_folder, "main.cpp")
    try:
        with open(main_cpp_path, "r") as f:
            initial_code = f.read()
    except FileNotFoundError:
        initial_code = "// Could not find main.cpp in templates/\n"
    return render_template("index.html", initial_code=initial_code)

@app.route("/run", methods=["POST"])
def run_code():
    """Compile & run user code, return JSON { output, error, runtime, exit_code }."""
    data = request.json
    code = data.get("code", "")
    stdin = data.get("input", "")

    filename = os.path.join(CODE_DIR, f"{uuid.uuid4().hex}.cpp")
    binary = filename.replace(".cpp", "")

    with open(filename, "w") as f:
        f.write(code)

    compile_proc = subprocess.run(
        [
            "g++",
            "-std=c++23",
            "-O2",
            filename,
            "-o",
            binary
        ],
        capture_output=True,
        text=True
    )

    if compile_proc.returncode != 0:
        os.remove(filename)
        return jsonify({
            "error": compile_proc.stderr,
            "exit_code": compile_proc.returncode
        })

    try:
        start = time.time()
        run_proc = subprocess.run(
            [binary],
            input=stdin,
            capture_output=True,
            text=True,
            timeout=5
        )
        end = time.time()
        runtime = round(end - start, 2)

        result = {
            "output": run_proc.stdout or "",
            "error": run_proc.stderr or "",
            "runtime": runtime,
            "exit_code": run_proc.returncode
        }
    except subprocess.TimeoutExpired:
        result = {
            "error": "Execution timed out.",
            "runtime": 5.0,
            "exit_code": -1  
        }
    finally:

        os.remove(filename)
        if os.path.exists(binary):
            os.remove(binary)

    return jsonify(result)

@app.route("/saves", methods=["GET"])
def list_saves():
    """
    List all saved files and directories in a hierarchical structure.
    Response: { status: "ok", files: [...] }
    """
    def list_dir_recursive(directory):
        items = []
        for entry in os.scandir(directory):
            if entry.is_dir():
                items.append({
                    "type": "folder",
                    "name": entry.name,
                    "contents": list_dir_recursive(entry.path)
                })
            elif entry.is_file() and entry.name.endswith(".cpp"):
                items.append({
                    "type": "file",
                    "name": entry.name
                })
        return items

    try:
        files = list_dir_recursive(SAVES_DIR)
        return jsonify({"status": "ok", "files": files})
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

WINDOWS_RESERVED_NAMES = {
    "CON", "PRN", "AUX", "NUL",
    *(f"COM{i}" for i in range(1, 10)),
    *(f"LPT{i}" for i in range(1, 10))
}

INVALID_CHARS = r'<>:"/\\|?*'  

def validate_filename(name: str) -> str | None:
    """
    Validate filename. Return error message string if invalid, else None.
    """
    base = os.path.basename(name)

    if re.search(f"[{re.escape(INVALID_CHARS)}]", base):
        return f"Filename contains invalid characters: {INVALID_CHARS}"

    root, _ = os.path.splitext(base)
    if root.upper() in WINDOWS_RESERVED_NAMES:
        return f"Filename '{root}' is reserved on Windows"

    if not base or base in {".", ".."}:
        return "Filename cannot be empty"

    return None  

@app.route("/save", methods=["POST"])
def save_file():
    """
    Save code under a given filename (must end with .cpp). 
    JSON payload: { filename, code, overwrite (optional) }.
    If overwriting, the existing file is moved to deleted/ as a backup.
    Supports nested directories.
    """
    data = request.json
    filename = (data.get("filename") or "").strip()
    code = data.get("code", "")
    overwrite = data.get("overwrite", False)

    if not filename.endswith(".cpp"):
        filename += ".cpp"

    error_msg = validate_filename(filename)
    if error_msg:
        return jsonify({
            "status": "invalid_filename",
            "message": error_msg,
            "filename": filename
        }), 200

    dest_path = os.path.join(SAVES_DIR, filename)

    if os.path.exists(dest_path):
        if not overwrite:
            return jsonify({
                "status": "exists",
                "message": f"File '{filename}' already exists. Overwrite?",
                "filename": filename
            }), 200
        else:
            try:
                deleted_dir = os.path.join(SAVES_DIR, "deleted")
                os.makedirs(deleted_dir, exist_ok=True)

                backup_path = os.path.join(deleted_dir, os.path.basename(filename))
                shutil.move(dest_path, backup_path)
            except Exception as e:
                return jsonify({
                    "status": "error",
                    "message": f"Failed to backup existing file: {str(e)}"
                }), 500

    try:
        os.makedirs(os.path.dirname(dest_path), exist_ok=True)
        with open(dest_path, "w", encoding="utf-8") as f:
            f.write(code)
        return jsonify({"status": "ok", "filename": filename})
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

BASE_SAVES_DIR = os.path.abspath(SAVES_DIR)

def resolve_save_path(rel_path):
    """
    Resolve a user-supplied relative path into an absolute path under BASE_SAVES_DIR.
    Raises ValueError on invalid / escaping paths.
    """
    if not isinstance(rel_path, str):
        raise ValueError("Invalid filename")

    rel_path = rel_path.lstrip("/\\")
    candidate = os.path.normpath(os.path.join(BASE_SAVES_DIR, rel_path))
    candidate_abs = os.path.abspath(candidate)

    base = BASE_SAVES_DIR
    if not (candidate_abs == base or candidate_abs.startswith(base + os.sep)):
        raise ValueError("Invalid filename (escape attempt)")
    return candidate_abs

@app.route("/load", methods=["GET"])
def load_file():
    filename = request.args.get("filename", "")
    try:
        path = resolve_save_path(filename)
    except ValueError:
        return jsonify({"status": "error", "message": "Invalid filename"}), 400

    if not path.endswith(".cpp"):
        return jsonify({"status": "error", "message": "Only .cpp files allowed"}), 400

    if not os.path.isfile(path):
        return jsonify({"status": "error", "message": "File not found"}), 404

    try:
        with open(path, "r", encoding="utf-8") as f:
            content = f.read()
        return jsonify({"status": "ok", "code": content})
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

@app.route("/delete", methods=["POST"])
def delete_file():
    data = request.json or {}
    filename = data.get("filename", "")
    try:
        src_path = resolve_save_path(filename)
    except ValueError:
        return jsonify({"status": "error", "message": "Invalid filename"}), 400

    if not os.path.isfile(src_path):
        return jsonify({"status": "error", "message": "File not found"}), 404

    deleted_dir = os.path.join(BASE_SAVES_DIR, "deleted")
    abs_deleted_dir = os.path.abspath(deleted_dir)
    abs_src = os.path.abspath(src_path)
    if abs_src.startswith(abs_deleted_dir + os.sep) or abs_src == abs_deleted_dir:
        return jsonify({"status": "error", "message": "Cannot delete protected folder"}), 403

    try:
        deleted_dir = os.path.join(BASE_SAVES_DIR, "deleted")
        os.makedirs(deleted_dir, exist_ok=True)
        dest_path = os.path.join(deleted_dir, os.path.basename(src_path))
        shutil.move(src_path, dest_path)
        return jsonify({"status": "ok", "filename": os.path.basename(src_path)})
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

@app.route("/rename", methods=["POST"])
def rename_file():
    data = request.json or {}
    old_name = (data.get("old_name") or "").strip()
    new_name = (data.get("new_name") or "").strip()

    if not old_name or not new_name:
        return jsonify({"status": "error", "message": "Missing names"}), 400

    if not new_name.endswith(".cpp"):
        new_name = new_name + ".cpp"

    try:
        old_path = resolve_save_path(old_name)
    except ValueError:
        return jsonify({"status": "error", "message": "Invalid old filename"}), 400

    if os.path.dirname(new_name):

        try:
            new_path = resolve_save_path(new_name)
        except ValueError:
            return jsonify({"status": "error", "message": "Invalid new filename"}), 400
    else:

        new_path = os.path.join(os.path.dirname(old_path), new_name)
        new_path = os.path.abspath(new_path)

        if not (new_path == BASE_SAVES_DIR or new_path.startswith(BASE_SAVES_DIR + os.sep)):
            return jsonify({"status": "error", "message": "Invalid new filename"}), 400

    if not os.path.isfile(old_path):
        return jsonify({"status": "error", "message": "Original file not found"}), 404

    if os.path.exists(new_path):
        return jsonify({"status": "error", "message": "A file with that name already exists"}), 409

    try:
        os.makedirs(os.path.dirname(new_path), exist_ok=True)
        os.rename(old_path, new_path)
        return jsonify({"status": "ok", "old_name": os.path.relpath(old_path, BASE_SAVES_DIR), "new_name": os.path.relpath(new_path, BASE_SAVES_DIR)})
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

@app.route("/download", methods=["GET"])
def download_template():
    """
    This endpoint isn�t used anymore because we download the current editor contents client-side.
    But we�ll keep it in case you want to revert to server-side downloads of templates.
    """
    return send_from_directory(
        directory=app.template_folder,
        filename=f"main.cpp",
        as_attachment=True,
        attachment_filename=f"main{random.randrange(100000, 999999, 1)}.cpp"
    )

@app.route("/delete_folder", methods=["POST"])
@app.route("/delete-folder", methods=["POST"])
def delete_folder():
    """
    "Delete" a saved folder by moving it (and all contents) into the deleted/ directory,
    while preserving its relative path hierarchy.
    JSON payload: { foldername } (e.g. "foo/bar/egg").
    """
    data = request.json or {}
    foldername = data.get("foldername", "")
    try:
        src_path = resolve_save_path(foldername)
    except ValueError:
        return jsonify({"status": "error", "message": "Invalid folder name"}), 400

    if os.path.abspath(src_path) == BASE_SAVES_DIR:
        return jsonify({"status": "error", "message": "Cannot delete the root saves directory"}), 400

    if not os.path.isdir(src_path):
        return jsonify({"status": "error", "message": "Folder not found"}), 404

    try:
        rel_path = os.path.relpath(src_path, BASE_SAVES_DIR)

        dest_path = os.path.join(BASE_SAVES_DIR, "deleted", rel_path)

        if os.path.commonpath([src_path]) == os.path.commonpath([src_path, dest_path]):
            return jsonify({"status": "error", "message": "Cannot move a folder into itself"}), 400

        os.makedirs(os.path.dirname(dest_path), exist_ok=True)

        final_dest = dest_path
        if os.path.exists(final_dest):
            i = 1
            while os.path.exists(f"{dest_path}_{i}"):
                i += 1
            final_dest = f"{dest_path}_{i}"

        shutil.move(src_path, final_dest)
        return jsonify({"status": "ok", "foldername": rel_path})
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

@app.route("/rename_folder", methods=["POST"])
@app.route("/rename-folder", methods=["POST"])
def rename_folder():
    """
    Rename a saved folder. JSON payload: { old_name, new_name }.
    Works within the same parent directory.
    """
    data = request.json or {}
    old_name = (data.get("old_name") or "").strip()
    new_name = (data.get("new_name") or "").strip()

    if not old_name or not new_name:
        return jsonify({"status": "error", "message": "Missing names"}), 400

    try:
        old_path = resolve_save_path(old_name)
    except ValueError:
        return jsonify({"status": "error", "message": "Invalid old folder name"}), 400

    parent_dir = os.path.dirname(old_path)
    new_path = os.path.join(parent_dir, new_name)
    new_path = os.path.abspath(new_path)

    if not (new_path == BASE_SAVES_DIR or new_path.startswith(BASE_SAVES_DIR + os.sep)):
        return jsonify({"status": "error", "message": "Invalid new folder name"}), 400

    if not os.path.isdir(old_path):
        return jsonify({"status": "error", "message": "Original folder not found"}), 404

    if os.path.exists(new_path):
        return jsonify({"status": "error", "message": "A file or folder with that name already exists"}), 409

    try:
        os.rename(old_path, new_path)
        return jsonify({
            "status": "ok",
            "old_name": os.path.relpath(old_path, BASE_SAVES_DIR),
            "new_name": os.path.relpath(new_path, BASE_SAVES_DIR)
        })
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

if __name__ == "__main__":

    app.run(debug=True, host="0.0.0.0", port=6502)