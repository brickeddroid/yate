let characterTimerId = -1;
let changeString = "";
let cursorPosition = -1;

const DocumentHandleOperation = {
    Nop: 0
    Open: 1,
    Close: 2,
    Save: 3,
}
const DocumentOperation = {
    Nop: 0,
    Insert: 1,
    Delete: 2
}

function sendInsertion(cursorPos, char){
    if(characterTimerId != -1){
        clearTimeout(characterTimerId);
    }
    changeString += char;
    if(cursorPosition == -1){
        cursorPosition = cursorPos;
    }
    characterTimerId = setTimeout(function(e){
        console.log("send character string '" +  changeString + "'| POS: " + cursorPosition);
        changeString = "";
        cursorPosition = -1;
        characterTimerId = -1;

    }, 500);
}
let deletionTimerId = -1;
let deletionCursorPosition = -1;
let deletionLength = 0;
function sendDeletion(cursorPos, length){
    if(deletionTimerId != -1){
        clearTimeout(deletionTimerId);
    }
    deletionLength += +length;

    deletionTimerId = setTimeout(function(e){
        deletionCursorPosition = cursorPos;
        console.log(`send deletion | POS: ${deletionCursorPosition} | LEN: ${deletionLength}`);
        deletionTimerId = -1;
        deletionLength = 0;
    }, 500);
}

// TODO
function sendDocumentChange(filename, operation, cursorPos, length, char)
{
    if(operation != current_operation){
        // clear timer
        // send document change
    }
}

function getCursorPosition(contentElement){
    return contentElement.selectionStart;
}

function determineLanguage(filename){
    return undefined;
    console.log(filename);
    if(filename == "/") return "html";
    const arr = filename.split('.')
    const ext = arr[arr.length-1] || "plaintext";
    return ext;
}

const regexFileExtension = /(?:\.([^.]+))?$/;
const regexHtml = /(HTM[XL]?)|(htm[xl]?)/;
function mimeTypeFromFileExt(filepath)
{
    return "text/plain";
    let mimetype = "text/plain";
    let fileext = filename.split('.').pop();
    if(fileext === filepath){
        return filepath;
    }

    if(regexHtml.test(fileext)) mimetype = "text/html";
    else if(regexJson.test(fileext)) mimetype = "application/html";
    return mimetype;
}

function load_file(event){
    var input = event.target;
    var reader = new FileReader();

    reader.onload = (e) => {
        console.log(e.target.result);
    };
    const objectUrl = window.URL.createObjectURL(input.files[0]);
    send_file_cmd_req(0, objectUrl, "local");
}

function send_file_cmd_req(op, filename, filereadwrite)
{
    hasOpened = true;
    (async () => {
        const rawResponse = await fetch('/cmd', {
            method: 'POST',
            headers: {
                'Accept': mimeTypeFromFileExt(filename),
                'Content-Type': mimeTypeFromFileExt(filename)
            },
            body: JSON.stringify({op: op, file: filename, filerw: filereadwrite })
        });
        const content = await rawResponse.text();
    })();
}

function getTextWidth(inputLine) {
    const computedStyle = getComputedStyle(document.documentElement);
    font = computedStyle.getPropertyValue("--text-editor-font-size")
        + " "
        + computedStyle.getPropertyValue("--text-editor-font-family");
    canvas = document.createElement("canvas");
    context = canvas.getContext("2d");
    context.font = font;
    width = context.measureText(inputLine).width;
    return Math.ceil(width);
}

function update_line_numbers(textarea){
    const lineNumbers = document.querySelector(".line-numbers");
    lineNumbers.innerHTML = "";
    const lines = textarea.value.split('\n');
    const numberOfLines = lines.length;
    for(let idx = 0; idx < numberOfLines; idx++){
        let span = document.createElement("span");
        span.innerHTML = idx+1;
        lineNumbers.appendChild(span);
        if(textarea.clientWidth < getTextWidth(lines[idx])){
            let additional_lines = Math.ceil(getTextWidth(lines[idx])/textarea.clientWidth) - 1;
            for(let i = 0; i < additional_lines; i++){
                let fillspan = document.createElement("span");
                fillspan.innerHTML = '&#8627;';
                lineNumbers.appendChild(fillspan);
            }
        }
    };
    document.querySelector(":root").style.setProperty("--text-editor-show-lines", numberOfLines);
    //console.log();
    //textarea.style.height = `calc(var(--text-editor-line-height)*)`;
}

function init_filehandle(){
   send_file_cmd_req(DocumentHandleOperation.Open, './frontend/index.html', 'local');
   let dir_tree = document.querySelector("#dir_tree");
   if(dir_tree.children.length > 0){
       dir_tree.children[0].firstElementChild.classList.add("active");
   }
}

function sendFile(file) {
    const uri = "/index.html";
    const xhr = new XMLHttpRequest();
    const fd = new FormData();
    xhr.open("POST", uri, true);
    xhr.onreadystatechange = () => {
        if (xhr.readyState === 4 && xhr.status === 200) {
            alert(xhr.responseText); // handle response.
        } else {
            // TODO
            alert(xhr.responseText); // handle response.
        }
    };
    fd.append('file', file);
    console.log(fd);
    // Initiate a multipart/form-data upload
    xhr.send(fd);
}

function init_dropzone () {
    const dropzone = document.querySelector(".dropzone");
    dropzone.ondragover = dropzone.ondragenter = (event) => {
        event.stopPropagation();
        event.preventDefault();
    }
    dropzone.ondrop = (event) => {
        event.stopPropagation();
        event.preventDefault();
        const filesArray = event.dataTransfer.files;
        for (let i=0; i<filesArray.length; i++) {
            sendFile(filesArray[i]);
        }
    }
}

function show_overlay(ov_type)
{
    let overlay = document.querySelector(".overlay");
    overlay.classList.add("active");
    let ov_concrete = document.querySelector("#ov_" + ov_type);
    ov_concrete.classList.add("active");
}

function close_overlay(){
    let overlay = document.querySelector(".overlay.active");
    if(!overlay) return;
    overlay.classList.remove("active");
    let ov_concrete = document.querySelector(".ovl_impl.active");
    ov_concrete.classList.remove("active");
}

var hasOpened = true;
var event_source;

function init(){
    event_source = new EventSource("/event");

    event_source.onconnect = (event) => {
        console.log("Event connected");
    }

    event_source.onerror = (event) => {
        console.error(event);
    }

    event_source.onmessage = (event) => {
        console.error("Ping");
    }

    event_source.addEventListener("file_opened", function(e){
        console.log("File opened received.");
        if(!hasOpened) {
            console.log("Not opened file, nothing todo...")
            return;
        }
        hasOpened = false;
        const tedit = document.querySelector("#text_editor");
        let json = JSON.parse(e.data);
        if(json.origin){
            return;
        }
        tedit.value = json.content;
        tedit.selectionStart = 0;
        tedit.selectionEnd = 0;
        tedit.parentElement.scrollTop = 0;
        update_line_numbers(tedit);
    });

    event_source.addEventListener("open_file_list_change", function(e){
        console.log("File list update received");
		let json = JSON.parse(e.data);
        let dir_tree = document.querySelector("#dir_tree");
        dir_tree.innerHTML = "";
        for(let i = 0; i < json.doc_list.length; i++){
            let file = json.doc_list[i];
            let li = document.createElement("li");
            let a = document.createElement("a");
            a.href = "#";
            a.addEventListener("click", function(e){
                open_file('cmd_open_file', this.innerText, 'local');
                let prevActiveElement = this.parentElement.parentElement.querySelector(".active");
                if(prevActiveElement){
                    prevActiveElement.classList.remove("active");
                }
                this.classList.add("active");
            });
            a.innerText = file;
            li.appendChild(a);
            dir_tree.appendChild(li);
        }
    });


    const text_editor = document.querySelector('#text_editor');

    text_editor.addEventListener("input", function(e){
        let cpos = getCursorPosition(this);

        if(e.inputType === "insertText"){
        }

        update_line_numbers(this);
    });

    const menu_file_open = document.querySelector("#menu_file_open");
    menu_file_open.addEventListener("click", function(e){
        show_overlay("open");
    });

    const btn_file_open = document.querySelector("#btn_file_open");
    btn_file_open.addEventListener("click", function(e){
        send_file_cmd_req(0, this.previousElementSibling.value, 'local'); close_overlay();
    });

    const menu_file_save = document.querySelector("#menu_file_save");
    menu_file_save.addEventListener("click", function(e){
        show_overlay("save");
    });

    const menu_about_yate = document.querySelector("#menu_about_yate");
    menu_about_yate.addEventListener("click", function(e){
        show_overlay("credits");
    });

    const btn_ov_close = document.querySelector("#ov_close");
    btn_ov_close.addEventListener("click", function(e){
        close_overlay();
    });

    init_dropzone();
    init_filehandle();

}
