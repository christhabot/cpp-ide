import os
import subprocess
import shutil
from datetime import datetime

SAVES_DIR = "C:/Users/chris/Downloads/pi/cpp-ide-static/saves"
GIT_REPO_DIR = "C:/Users/chris/Downloads/pi/cpp-ide-static/repo"
COMMIT_MESSAGE = f"auto {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}"

def main():
    if not os.path.exists(SAVES_DIR):
        print("Saves folder doesn't exist, bro.")
        return
    if not os.path.exists(GIT_REPO_DIR):
        print("Repo folder doesn't exist, bro.")
        return

    for item in os.listdir(SAVES_DIR):
        src = os.path.join(SAVES_DIR, item)
        dst = os.path.join(GIT_REPO_DIR, item)

        if os.path.exists(dst):
            if os.path.isfile(dst) or os.path.islink(dst):
                os.remove(dst)
            else:
                shutil.rmtree(dst)

        if os.path.isdir(src):
            shutil.copytree(src, dst)
        else:
            shutil.copy2(src, dst)
        print(f"Copied: {item}")

    subprocess.run(["git", "-C", GIT_REPO_DIR, "add", "."], check=True)
    subprocess.run(["git", "-C", GIT_REPO_DIR, "commit", "-m", COMMIT_MESSAGE], check=False)
    subprocess.run(["git", "-C", GIT_REPO_DIR, "push", "-u", "origin", "main"], check=True)

    print("Done.")

if __name__ == "__main__":
    main()