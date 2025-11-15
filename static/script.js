let editor;

// ----------- Initialize Monaco Editor -----------
document.addEventListener('DOMContentLoaded', () => {
  require.config({ paths: { vs: 'https://unpkg.com/monaco-editor@latest/min/vs' } });
  
  require(["vs/editor/editor.main"], function () {
    
    editor = monaco.editor.create(document.getElementById("editor-container"), {
      value: initialCode,
      language: "cpp",
      theme: "vs-dark",
      automaticLayout: true,
      fontSize: 14,
      minimap: { enabled: false },
      mouseWheelZoom: true   
    });
    
    // Touch zoom code
    let lastTouchDistance = null;

    function getTouchDistance(e) {
      if (e.touches.length < 2) return null;
      const dx = e.touches[0].clientX - e.touches[1].clientX;
      const dy = e.touches[0].clientY - e.touches[1].clientY;
      return Math.sqrt(dx * dx + dy * dy);
    }

    document.getElementById("editor-container").addEventListener("touchmove", (e) => {
      const distance = getTouchDistance(e);
      if (!distance) return;

      if (lastTouchDistance) {
        const delta = distance - lastTouchDistance;
        if (Math.abs(delta) > 5) {
          let fontSize = editor.getOption(monaco.editor.EditorOption.fontSize);
          fontSize += delta > 0 ? 1 : -1;
          fontSize = Math.max(8, Math.min(40, fontSize));
          editor.updateOptions({ fontSize });
        }
      }
      lastTouchDistance = distance;
    }, { passive: true });

    document.getElementById("editor-container").addEventListener("touchend", () => {
      lastTouchDistance = null;
    });
  });
});

// ----------- Button Event Listeners -----------
document.addEventListener("DOMContentLoaded", () => {
  document.getElementById("run-button").addEventListener("click", runCode);
  document.getElementById("save-button").addEventListener("click", saveCurrent);
  document.getElementById("load-button").addEventListener("click", openLoadMenu);
  document.getElementById("download-button").addEventListener("click", downloadCurrentCode);
  document.getElementById("close-load-menu").addEventListener("click", () => {
    document.getElementById("load-menu").style.display = "none";
  });
});
// ----------- 1) RUN CODE -----------

let codechefSession = null;

async function getCodeChefSession() {
  if (codechefSession) return codechefSession;
  
  const workerUrl = "https://cors-header-proxy.christhabotyt.workers.dev";
  const response = await fetch(`${workerUrl}?getcsrf=true`);
  const data = await response.json();
  
  codechefSession = {
    csrf: data.csrf,
    cookies: data.cookies
  };
  
  return codechefSession;
}

function runCode() {
  const code = editor.getValue();
  const input = document.getElementById("input").value;
  const outputBox = document.getElementById("output-box");
  const runtimeLabel = document.getElementById("runtime-label");
  const spinner = document.getElementById("spinner");

  // Show spinner
  spinner.style.display = "inline-block";

  // Base64 encode the code and input
  let encodedCode, encodedInput;
  try {
    encodedCode = btoa(unescape(encodeURIComponent(code)));
    encodedInput = btoa(unescape(encodeURIComponent(input)));
  } catch (e) {
    spinner.style.display = "none";
    outputBox.textContent = "Error encoding input: " + e.message;
    return;
  }

  // Submit the code
  fetch("https://judge0-public.newtonschool.co/submissions/?base64_encoded=true&wait=false", {
    headers: {
      "accept": "*/*",
      "content-type": "application/json",
    },
    body: JSON.stringify({
      language_id: 54,
      compiler_options: "-O2 -DONLINE_JUDGE",
      source_code: encodedCode,
      playground_hash: "NON_LOGGED_IN_HASH",
      stdin: encodedInput,
      enable_network: false,
      max_processes_and_or_threads: 60
    }),
    method: "POST",
    mode: "cors",
  })
    .then(res => {
      if (!res.ok) {
        throw new Error(`HTTP error! status: ${res.status}`);
      }
      return res.json(); // a
    })
    .then(data => {
      if (!data.token) {
        throw new Error("No token received from API");
      }
      
      const token = data.token;
      let pollCount = 0;
      const maxPolls = 60; // Maximum 30 seconds
      
      // Poll for results every 500ms
      const pollInterval = setInterval(() => {
        pollCount++;
        
        if (pollCount > maxPolls) {
          clearInterval(pollInterval);
          spinner.style.display = "none";
          outputBox.textContent = "Timeout: Execution took too long";
          runtimeLabel.style.display = "none";
          return;
        }
        
        fetch(`https://judge0-public.newtonschool.co/submissions/${token}/?base64_encoded=true&wait=false`, {
          headers: {
            "accept": "*/*",
          },
          method: "GET",
          mode: "cors",
        })
          .then(res => {
            if (!res.ok) {
              throw new Error(`HTTP error! status: ${res.status}`);
            }
            return res.json();
          })
          .then(result => {
            // Status IDs: 1=In Queue, 2=Processing, 3=Accepted, others=Error/Complete
            if (result.status.id !== 1 && result.status.id !== 2) {
              clearInterval(pollInterval);
              spinner.style.display = "none";
              
              // Decode stdout/stderr if present
              let output = "";
              try {
                if (result.stdout) {
                  output = decodeURIComponent(escape(atob(result.stdout.trim())));
                } else if (result.stderr) {
                  output = "Error:\n" + decodeURIComponent(escape(atob(result.stderr.trim())));
                } else if (result.compile_output) {
                  output = "Compilation Error:\n" + decodeURIComponent(escape(atob(result.compile_output.trim())));
                } else if (result.message) {
                  output = "Message: " + result.message + "\nStatus: " + result.status.description;
                } else {
                  output = "Status: " + result.status.description;
                }
              } catch (e) {
                output = "Error decoding output: " + e.message;
              }
              
              outputBox.textContent = output;
              outputBox.scrollTop = outputBox.scrollHeight;
              
              // Show runtime info
              if (result.time !== null && result.time !== undefined) {
                const exitCode = result.status.id === 3 ? 0 : result.status.id;
                runtimeLabel.innerHTML = `Execution time: ${result.time} s&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;Exit code: ${exitCode}&nbsp;`;
                runtimeLabel.style.display = "block";
              } else {
                runtimeLabel.style.display = "none";
              }
            }
          })
          .catch(err => {
            clearInterval(pollInterval);
            spinner.style.display = "none";
            outputBox.textContent = "Error polling results: " + err.message;
            outputBox.scrollTop = outputBox.scrollHeight;
            runtimeLabel.style.display = "none";
          });
      }, 500);
    })
    .catch(err => {
      spinner.style.display = "none";
      outputBox.textContent = "Error submitting code: " + err.message + "\n\nThis API may require specific authentication or may be blocked by CORS policies.";
      outputBox.scrollTop = outputBox.scrollHeight;
      runtimeLabel.style.display = "none";
    });
}


function openSaveMenu() {
  document.getElementById("save-menu").style.display = "flex";
  refreshSaveLocationsList();
}

// Add this CSS for the save menu (you can add it to your main CSS file)
const saveMenuCSS = `
#save-menu {
  display: none;
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  background: rgba(0, 0, 0, 0.5);
  z-index: 1000;
}

#save-menu-box {
  position: absolute;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
  background: white;
  border-radius: 8px;
  padding: 20px;
  min-width: 500px;
  max-width: 80vw;
  max-height: 80vh;
  overflow-y: auto;
  box-shadow: 0 4px 20px rgba(0, 0, 0, 0.3);
}

#close-save-menu {
  float: right;
  background: #ff4444;
  color: white;
  border: none;
  border-radius: 50%;
  width: 30px;
  height: 30px;
  cursor: pointer;
  font-size: 16px;
  line-height: 1;
}

#close-save-menu:hover {
  background: #cc0000;
}

#save-location-list {
  list-style: none;
  padding: 0;
  margin: 0;
  font-family: system-ui, sans-serif;
  max-height: 400px;
  overflow-y: auto;
}

#save-location-list li {
  display: flex;
  align-items: center;
  justify-content: space-between;
  padding: 6px 8px;
  border-bottom: 1px solid rgba(0,0,0,0.05);
}

#save-location-list li.folder-row {
  cursor: pointer;
}

#save-location-list li .left {
  display: flex;
  align-items: center;
  gap: 8px;
  flex: 1;
}

.save-here-btn {
  background-color: #4CAF50;
  color: white;
  border: none;
  padding: 4px 8px;
  border-radius: 3px;
  cursor: pointer;
  font-size: 12px;
}

.save-here-btn:hover {
  background-color: #45a049;
}
`;

// Add the styles to the page if not already present
if (!document.getElementById('save-menu-styles')) {
  const style = document.createElement('style');
  style.id = 'save-menu-styles';
  style.textContent = saveMenuCSS;
  document.head.appendChild(style);
}

function passwordPrompt(message) {
    // create modal div
    const modal = document.createElement("div");
    modal.style.position = "fixed";
    modal.style.top = "0";
    modal.style.left = "0";
    modal.style.width = "100%";
    modal.style.height = "100%";
    modal.style.background = "rgba(0,0,0,0.5)";
    modal.style.display = "flex";
    modal.style.justifyContent = "center";
    modal.style.alignItems = "center";
    modal.style.zIndex = "9999";

    // inner box
    const box = document.createElement("div");
    box.style.background = "white";
    box.style.padding = "20px";
    box.style.borderRadius = "8px";
    box.style.textAlign = "center";

    const text = document.createElement("div");
    text.textContent = message;
    box.appendChild(text);

    const input = document.createElement("input");
    input.type = "password"; // masked input
    input.style.marginTop = "10px";
    input.style.width = "100%";
    box.appendChild(input);

    const btn = document.createElement("button");
    btn.textContent = "OK";
    btn.style.marginTop = "10px";
    box.appendChild(btn);

    modal.appendChild(box);
    document.body.appendChild(modal);

    return new Promise(resolve => {
        btn.addEventListener("click", () => {
            const value = input.value;
            document.body.removeChild(modal);
            resolve(value);
        });
        input.addEventListener("keypress", e => {
            if (e.key === "Enter") {
                btn.click();
            }
        });
        input.focus();
    });
}

let password, GITHUB_TOKEN;

(async () => {
  // Wait for DOM to be ready first
  if (document.readyState === 'loading') {
    await new Promise(resolve => {
      document.addEventListener('DOMContentLoaded', resolve, { once: true });
    });
  }
  
  // NOW prompt for password
  password = await passwordPrompt("Enter password");
  console.log("password", password); // This should now show the actual password
  
  const key = password + "Jh1QcY";
  const cipherBase64 = "H9Ib1iJLFXwjgvoe1rV6YZvln92KVH9nSJwdgMgXFs86Q6Aly8nYxUx9AI02zF7M";
  const decrypted = CryptoJS.AES.decrypt(cipherBase64, CryptoJS.enc.Utf8.parse(key), {
    mode: CryptoJS.mode.CBC,
    padding: CryptoJS.pad.Pkcs7,
    iv: CryptoJS.enc.Hex.parse('00000000000000000000000000000000')
  });
  const plainText = decrypted.toString(CryptoJS.enc.Utf8);
  GITHUB_TOKEN = plainText;
  console.log("GITHUB_TOKEN", GITHUB_TOKEN); // Should now show the decrypted token
})();

const GIST_ID = "10caccb12fdfbaae95a3488c9778136b";
const GIST_API_URL = `https://api.github.com/gists/${GIST_ID}`;

// ========== HELPER FUNCTIONS ==========

// Fetch the entire gist structure
async function fetchGist() {
  const response = await fetch(GIST_API_URL, {
    headers: {
      "Authorization": `token ${GITHUB_TOKEN}`,
      "Accept": "application/vnd.github.v3+json"
    }
  });
  
  if (!response.ok) {
    throw new Error(`GitHub API error: ${response.status}`);
  }
  
  return await response.json();
}

// Update the gist with new files
async function updateGist(files) {
  const response = await fetch(GIST_API_URL, {
    method: "PATCH",
    headers: {
      "Authorization": `token ${GITHUB_TOKEN}`,
      "Accept": "application/vnd.github.v3+json",
      "Content-Type": "application/json"
    },
    body: JSON.stringify({ files })
  });
  
  if (!response.ok) {
    throw new Error(`GitHub API error: ${response.status}`);
  }
  
  return await response.json();
}

// Convert flat file list to folder structure
function buildFolderStructure(files) {
  const root = [];
  const folderMap = new Map();
  
  // Get all file paths and decode them (replace ___ with /)
  const filePaths = Object.keys(files).map(path => path.replace(/___/g, '/'));
  
  // Build folder structure
  filePaths.forEach(path => {
    // Skip files in deleted folder
    if (path.startsWith('deleted/')) return;
    
    const parts = path.split('/');
    
    if (parts.length === 1) {
      // Root level file
      root.push({ name: parts[0], type: "file" });
    } else {
      // File in folder(s)
      let currentLevel = root;
      let currentPath = "";
      
      // Build folders
      for (let i = 0; i < parts.length - 1; i++) {
        currentPath = currentPath ? `${currentPath}/${parts[i]}` : parts[i];
        
        if (!folderMap.has(currentPath)) {
          const folder = { name: parts[i], type: "folder", contents: [] };
          currentLevel.push(folder);
          folderMap.set(currentPath, folder.contents);
        }
        
        currentLevel = folderMap.get(currentPath);
      }
      
      // Add file to its folder
      currentLevel.push({ name: parts[parts.length - 1], type: "file" });
    }
  });
  
  return root;
}

// ========== STORAGE API FUNCTIONS (Replace backend endpoints) ==========

// GET /saves - List all files in folder structure
async function getSaves() {
  try {
    const gist = await fetchGist();
    const structure = buildFolderStructure(gist.files);
    return { status: "ok", files: structure };
  } catch (err) {
    return { status: "error", message: err.message };
  }
}

// POST /save - Save a file
async function saveFile(filename, code, overwrite = false) {
  try {
    const gist = await fetchGist();
    
    // Check if file exists
    const encodedFilename = filename.replace(/\//g, '___'); // Gist doesn't allow / in filenames
    
    if (gist.files[encodedFilename] && !overwrite) {
      return { 
        status: "exists", 
        message: `File "${filename}" already exists. Do you want to overwrite it?` 
      };
    }
    
    // Save the file
    const files = {
      [encodedFilename]: {
        content: code
      }
    };
    
    await updateGist(files);
    
    return { status: "ok", filename: filename };
  } catch (err) {
    return { status: "error", message: err.message };
  }
}

// GET /load - Load a file
async function loadFile(filename) {
  try {
    const gist = await fetchGist();
    const encodedFilename = filename.replace(/\//g, '___');
    
    if (!gist.files[encodedFilename]) {
      return { status: "error", message: "File not found" };
    }
    
    return { status: "ok", code: gist.files[encodedFilename].content };
  } catch (err) {
    return { status: "error", message: err.message };
  }
}

// POST /delete - Delete a file (move to deleted folder)
async function deleteFile(filename) {
  try {
    const gist = await fetchGist();
    const encodedFilename = filename.replace(/\//g, '___');
    
    if (!gist.files[encodedFilename]) {
      return { status: "error", message: "File not found" };
    }
    
    // Get the file content
    const content = gist.files[encodedFilename].content;
    
    // Create new path in deleted folder with timestamp
    const timestamp = new Date().toISOString().replace(/[:.]/g, '-');
    const deletedPath = `deleted/${filename}_${timestamp}`;
    const deletedEncoded = deletedPath.replace(/\//g, '___');
    
    const files = {
      [encodedFilename]: null, // Delete original
      [deletedEncoded]: { content: content } // Move to deleted
    };
    
    await updateGist(files);
    
    return { status: "ok" };
  } catch (err) {
    return { status: "error", message: err.message };
  }
}

// POST /rename - Rename a file
async function renameFile(oldName, newName) {
  try {
    const gist = await fetchGist();
    const oldEncoded = oldName.replace(/\//g, '___');
    const newEncoded = newName.replace(/\//g, '___');
    
    if (!gist.files[oldEncoded]) {
      return { status: "error", message: "File not found" };
    }
    
    if (gist.files[newEncoded]) {
      return { status: "error", message: "A file with that name already exists" };
    }
    
    const content = gist.files[oldEncoded].content;
    
    const files = {
      [oldEncoded]: null, // Delete old
      [newEncoded]: { content: content } // Create new
    };
    
    await updateGist(files);
    
    return { status: "ok" };
  } catch (err) {
    return { status: "error", message: err.message };
  }
}

// POST /delete-folder - Delete a folder and all its contents
async function deleteFolder(folderPath) {
  try {
    const gist = await fetchGist();
    const prefix = folderPath.replace(/\//g, '___') + '___';
    
    const files = {};
    
    // Find all files that start with this folder path
    Object.keys(gist.files).forEach(filename => {
      if (filename.startsWith(prefix)) {
        files[filename] = null; // Mark for deletion
      }
    });
    
    if (Object.keys(files).length === 0) {
      return { status: "error", message: "Folder not found or empty" };
    }
    
    await updateGist(files);
    
    return { status: "ok" };
  } catch (err) {
    return { status: "error", message: err.message };
  }
}

// POST /rename-folder - Rename a folder
async function renameFolder(oldFolder, newFolderInput) {
  try {
    const gist = await fetchGist();

    // Split old folder path and get parent
    const oldParts = oldFolder.split('/');
    const oldFolderName = oldParts.pop(); // last part = folder being renamed
    const parentParts = oldParts; // parent path parts

    // Resolve new folder path relative to parent
    const newPartsRaw = newFolderInput.split('/');
    const newParts = [...parentParts]; // start from parent

    for (let part of newPartsRaw) {
      if (part === '..') {
        if (newParts.length > 0) newParts.pop(); // go up one
      } else if (part && part !== '.') {
        newParts.push(part);
      }
    }

    const newFolder = newParts.join('/');

    // Convert to gist filename encoding
    const encodePath = path => path.split('/').join('___') + '___';
    const oldPrefix = encodePath(oldFolder);
    const newPrefix = encodePath(newFolder);

    const files = {};

    Object.keys(gist.files).forEach(filename => {
      if (filename.startsWith(oldPrefix)) {
        const content = gist.files[filename].content;
        const newFilename = filename.replace(oldPrefix, newPrefix);

        files[filename] = null; // delete old
        files[newFilename] = { content }; // create new
      }
    });

    if (Object.keys(files).length === 0) {
      return { status: "error", message: "Folder not found" };
    }

    await updateGist(files);
    return { status: "ok" };
  } catch (err) {
    return { status: "error", message: err.message };
  }
}

// ========== UPDATE YOUR EXISTING FUNCTIONS ==========

// Replace the old saveCurrent function
function saveCurrent() {
  document.getElementById("save-menu").style.display = "flex";
  refreshSaveLocationsList();
}

function closeSaveMenu() {
  document.getElementById("save-menu").style.display = "none";
}

// Replace refreshSaveLocationsList
function refreshSaveLocationsList() {
  getSaves()
    .then(data => {
      const ul = document.getElementById("save-location-list");
      ul.innerHTML = "";
      
      // Add "Root" folder at the top
      const rootLi = document.createElement("li");
      rootLi.classList.add("folder-row");
      
      const leftDiv = document.createElement("div");
      leftDiv.className = "left";
      leftDiv.style.paddingLeft = "0px";
      
      const marker = document.createElement("span");
      marker.className = "toggle-marker";
      marker.textContent = "";
      
      const nameSpan = document.createElement("span");
      nameSpan.className = "folder-name";
      nameSpan.textContent = "Root";
      nameSpan.style.fontWeight = "600";
      
      leftDiv.appendChild(marker);
      leftDiv.appendChild(nameSpan);
      
      const actionsDiv = document.createElement("div");
      actionsDiv.className = "folder-actions";
      
      const saveBtn = document.createElement("button");
      saveBtn.textContent = "Save Here";
      saveBtn.classList.add("save-here-btn");
      saveBtn.addEventListener("click", (ev) => { 
        ev.stopPropagation(); 
        promptForFilenameAndSave("");
      });
      
      actionsDiv.appendChild(saveBtn);
      rootLi.appendChild(leftDiv);
      rootLi.appendChild(actionsDiv);
      ul.appendChild(rootLi);
      
      const entries = Array.isArray(data.files) ? data.files : [];
      
      function renderFoldersOnly(list, parentPath = "", depth = 0) {
        const rows = [];
        const folders = (list || []).filter(e => e && (String(e.type || "").toLowerCase() === "folder" || Array.isArray(e.contents)));
        
        folders.sort((a,b) => (a.name||"").localeCompare(b.name||""));
        
        for (const dir of folders) {
          if (!dir || !dir.name) continue;
          if (dir.name === "deleted") continue;
          
          const fullPath = parentPath ? `${parentPath}/${dir.name}` : dir.name;
          
          const li = document.createElement("li");
          li.classList.add("folder-row");
          
          const leftDiv = document.createElement("div");
          leftDiv.className = "left";
          leftDiv.style.paddingLeft = `${depth * INDENT_PX + INDENT_PX}px`;
          
          const marker = document.createElement("span");
          marker.className = "toggle-marker";
          marker.textContent = openFolders.has(fullPath) ? "v" : ">";
          
          const nameSpan = document.createElement("span");
          nameSpan.className = "folder-name";
          nameSpan.textContent = dir.name;
          nameSpan.style.fontWeight = "600";

          leftDiv.appendChild(marker);
          leftDiv.appendChild(nameSpan);
          
          const actionsDiv = document.createElement("div");
          actionsDiv.className = "folder-actions";
          
          const saveBtn = document.createElement("button");
          saveBtn.textContent = "Save Here";
          saveBtn.classList.add("save-here-btn");
          saveBtn.addEventListener("click", (ev) => { 
            ev.stopPropagation(); 
            promptForFilenameAndSave(fullPath);
          });
          
          actionsDiv.appendChild(saveBtn);
          li.appendChild(leftDiv);
          li.appendChild(actionsDiv);
          
          li.addEventListener("click", () => {
            if (openFolders.has(fullPath)) openFolders.delete(fullPath);
            else openFolders.add(fullPath);
            refreshSaveLocationsList();
          });
          
          rows.push(li);
          
          if (openFolders.has(fullPath) && Array.isArray(dir.contents)) {
            const childRows = renderFoldersOnly(dir.contents, fullPath, depth + 1);
            rows.push(...childRows);
          }
        }
        
        return rows;
      }
      
      const rows = renderFoldersOnly(entries, "", 0);
      rows.forEach(r => ul.appendChild(r));
    })
    .catch(err => {
      alert("Could not fetch save locations: " + err);
    });
}

// Replace promptForFilenameAndSave
function promptForFilenameAndSave(folderPath) {
  const code = editor.getValue();
  let filename = prompt("Enter a name for your file (without extension):");
  
  if (!filename) return;
  
  filename = filename.trim();
  if (!filename) {
    alert("Filename cannot be empty.");
    return;
  }
  
  if (!filename.endsWith(".cpp")) {
    filename = filename + ".cpp";
  }
  
  const fullPath = folderPath ? `${folderPath}/${filename}` : filename;
  
  saveFile(fullPath, code, false)
    .then(res => {
      if (res.status === "ok") {
        alert(`Saved as ${res.filename}`);
        closeSaveMenu();
      } else if (res.status === "exists") {
        const shouldOverwrite = confirm(`${res.message}`);
        if (shouldOverwrite) {
          saveFile(fullPath, code, true)
            .then(res2 => {
              if (res2.status === "ok") {
                alert(`Overwritten and saved as ${res2.filename}`);
                closeSaveMenu();
              } else {
                alert("Error saving: " + res2.message);
              }
            });
        }
      } else {
        alert("Error saving: " + res.message);
      }
    })
    .catch(err => {
      alert("Error: " + err);
    });
}

// Replace openLoadMenu
function openLoadMenu() {
  document.getElementById("load-menu").style.display = "flex";
  refreshSavesList();
}

// Replace refreshSavesList
function refreshSavesList() {
  getSaves()
    .then(data => {
      const ul = document.getElementById("load-file-list");
      ul.innerHTML = "";

      const entries = Array.isArray(data.files) ? data.files : [];

      function renderEntries(list, parentPath = "", depth = 0) {
        const rows = [];

        const folders = (list || []).filter(e => e && (String(e.type || "").toLowerCase() === "folder" || Array.isArray(e.contents)));
        const files   = (list || []).filter(e => e && (String(e.type || "").toLowerCase() === "file" || (e.name && e.name.includes("."))));

        folders.sort((a,b) => (a.name||"").localeCompare(b.name||""));
        files.sort((a,b) => (a.name||"").localeCompare(b.name||""));

        for (const dir of folders) {
          if (!dir || !dir.name) continue;
          if (dir.name === "deleted") continue;
          const fullPath = parentPath ? `${parentPath}/${dir.name}` : dir.name;

          const li = document.createElement("li");
          li.classList.add("folder-row");

          const leftDiv = document.createElement("div");
          leftDiv.className = "left";
          leftDiv.style.paddingLeft = `${depth * INDENT_PX}px`;

          const marker = document.createElement("span");
          marker.className = "toggle-marker";
          marker.textContent = openFolders.has(fullPath) ? "v" : ">";

          const nameSpan = document.createElement("span");
          nameSpan.className = "folder-name";
          nameSpan.textContent = dir.name;
          nameSpan.style.fontWeight = "600";

          leftDiv.appendChild(marker);
          leftDiv.appendChild(nameSpan);

          const actionsDiv = document.createElement("div");
          actionsDiv.className = "file-actions";

          const renameBtn = document.createElement("button");
          renameBtn.textContent = "Rename";
          renameBtn.classList.add("file-actions");
          renameBtn.addEventListener("click", (ev) => { ev.stopPropagation(); renameFolderUI(fullPath); });

          const deleteBtn = document.createElement("button");
          deleteBtn.textContent = "Delete";
          deleteBtn.classList.add("file-actions");
          deleteBtn.addEventListener("click", (ev) => { ev.stopPropagation(); deleteFolderUI(fullPath); });

          actionsDiv.appendChild(renameBtn);
          actionsDiv.appendChild(deleteBtn);

          li.appendChild(leftDiv);
          li.appendChild(actionsDiv);

          li.addEventListener("click", () => {
            if (openFolders.has(fullPath)) openFolders.delete(fullPath);
            else openFolders.add(fullPath);
            ul.innerHTML = "";
            const newRows = renderEntries(entries, "", 0);
            newRows.forEach(r => ul.appendChild(r));
          });

          rows.push(li);

          if (openFolders.has(fullPath) && Array.isArray(dir.contents)) {
            const childRows = renderEntries(dir.contents, fullPath, depth + 1);
            rows.push(...childRows);
          }
        }

        for (const file of files) {
          if (!file || !file.name) continue;
          if (file.name.split("/").includes("deleted")) continue;

          const filePath = parentPath ? `${parentPath}/${file.name}` : file.name;

          const li = document.createElement("li");
          li.classList.add("file-row");

          const leftDiv = document.createElement("div");
          leftDiv.className = "left";
          leftDiv.style.paddingLeft = `${depth * INDENT_PX}px`;

          const marker = document.createElement("span");
          marker.className = "toggle-marker";
          marker.textContent = "";

          const fspan = document.createElement("span");
          fspan.className = "file-name";
          fspan.textContent = file.name;

          leftDiv.appendChild(marker);
          leftDiv.appendChild(fspan);

          const actionsDiv = document.createElement("div");
          actionsDiv.className = "file-actions";

          const loadBtn = document.createElement("button");
          loadBtn.textContent = "Load";
          loadBtn.addEventListener("click", (ev) => { ev.stopPropagation(); loadSavedFile(filePath); });

          const renameBtn = document.createElement("button");
          renameBtn.textContent = "Rename";
          renameBtn.classList.add("file-actions");
          renameBtn.addEventListener("click", (ev) => { ev.stopPropagation(); renameSavedFile(filePath); });

          const deleteBtn = document.createElement("button");
          deleteBtn.textContent = "Delete";
          deleteBtn.classList.add("file-actions");
          deleteBtn.addEventListener("click", (ev) => { ev.stopPropagation(); deleteSavedFile(filePath); });

          actionsDiv.appendChild(loadBtn);
          actionsDiv.appendChild(renameBtn);
          actionsDiv.appendChild(deleteBtn);

          li.appendChild(leftDiv);
          li.appendChild(actionsDiv);
          rows.push(li);
        }

        return rows;
      }

      const rows = renderEntries(entries, "", 0);
      rows.forEach(r => ul.appendChild(r));
    })
    .catch(err => {
      alert("Could not fetch saves: " + err);
    });
}

// Replace renameFolderUI
function renameFolderUI(folderPath) {
  const newPath = prompt(`Rename folder "${folderPath}" to (can be relative like "../newName" or nested like "foo/bar"):`)
  if (!newPath) return;

  renameFolder(folderPath, newPath)
    .then(res => {
      if (res.status === "ok") refreshSavesList();
      else alert("Rename failed: " + res.message);
    })
    .catch(e => alert("Rename error: " + e));
}

// Replace deleteFolderUI
function deleteFolderUI(folderPath) {
  if (!confirm(`Delete folder "${folderPath}" and all its contents? This cannot be undone.`)) return;
  
  deleteFolder(folderPath)
    .then(res => {
      if (res.status === "ok") refreshSavesList();
      else alert("Delete failed: " + res.message);
    })
    .catch(e => alert("Delete error: " + e));
}

// Replace loadSavedFile
function loadSavedFile(filename) {
  loadFile(filename)
    .then(res => {
      if (res.status === "ok") {
        editor.setValue(res.code);
        document.getElementById("load-menu").style.display = "none";
      } else {
        alert("Error loading file: " + res.message);
      }
    })
    .catch(err => {
      alert("Error: " + err);
    });
}

// Replace deleteSavedFile
function deleteSavedFile(filename) {
  if (!confirm(`Are you sure you want to delete "${filename}"?`)) {
    return;
  }
  
  deleteFile(filename)
    .then(res => {
      if (res.status === "ok") {
        refreshSavesList();
      } else {
        alert("Error deleting: " + res.message);
      }
    })
    .catch(err => {
      alert("Error: " + err);
    });
}

// Replace renameSavedFile
function renameSavedFile(oldName) {
  let newName = prompt("Enter new name (without extension):", oldName.replace(/\.cpp$/, ""));
  if (!newName) return;
  newName = newName.trim();
  if (!newName) {
    alert("Filename cannot be empty.");
    return;
  }
  if (!newName.endsWith(".cpp")) {
    newName = newName + ".cpp";
  }

  renameFile(oldName, newName)
    .then(res => {
      if (res.status === "ok") {
        refreshSavesList();
      } else {
        alert("Error renaming: " + res.message);
      }
    })
    .catch(err => {
      alert("Error: " + err);
    });
}

// top-level (place once, outside the function)
const openFolders = new Set();
const INDENT_PX = 16;

// ----------- 4) DOWNLOAD CURRENT EDITOR AS main.cpp -----------
function randRange() {
  return Math.floor(Math.random() * (999999 - 100000 + 1)) + 100000;
}

function downloadCurrentCode() {
  const code = editor.getValue();
  const blob = new Blob([code], { type: "text/plain" });
  const url = URL.createObjectURL(blob);
  const a = document.createElement("a");
  a.href = url;
  a.download = `main_${randRange()}.cpp`;
  document.body.appendChild(a);
  a.click();
  document.body.removeChild(a);
  URL.revokeObjectURL(url);
}