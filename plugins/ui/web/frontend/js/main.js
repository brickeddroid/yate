function determineLanguage(filename){
    console.log(filename);
    if(filename == "/") return "html";
    const arr = filename.split('.')
    const ext = arr[arr.length-1] || "plaintext";
    return ext;
    //return file_ext;
}

function load_file(event){
    var input = event.target;
    var reader = new FileReader();

    reader.onload = (e) => {
        console.log(e.target.result);
        //
    };
    const objectUrl = window.URL.createObjectURL(input.files[0]);
    console.log(objectUrl);
    open_file(objectUrl);
    //reader.readAsDataURL();
}

function open_file(filename)
{
    fetch('./open?file=' + filename)
        .then((response) => {
            response.text().then((data) => {
                const regex = /(\<\/?[a-z]\>?)/
                //const new_data = data.replace(regex, "<span style='color:red;'>$1</span>")
                const lang = determineLanguage(filename);
                const cel = document.querySelector("#textdiv");
                if(hljs.getLanguage(lang) != undefined ){
                    console.log(lang);
                    const highlightedCode = hljs.highlight(
                        data,
                        { language: lang }
                    ).value
                    cel.innerHTML = highlightedCode;
                } else {
                    cel.innerHTML = data;
                }
                cel.language = lang;
            });
        })
        .catch((err) => {  })
}

function highlight(){
    //const lang = determineLanguage(filename);
    const cel = document.querySelector("#textdiv");
    const highlightedCode = hljs.highlight(
        cel.innerText,
        { language: cel.language }
    ).value
    cel.innerHTML = highlightedCode;

}

function init_filehandle(){
    open_file('/');
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

function init(){
    init_dropzone();
    init_filehandle();
}
