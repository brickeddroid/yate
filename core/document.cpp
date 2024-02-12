#include "document.hpp"

using namespace YateCore;

DocumentType settingUpEnvironment(const std::string &filetype)
{
    if(filetype == "cpp" || filetype == "hpp"){
        //init keyword/token detection for c++
        std::cout << "C++ extension detected" << std::endl;
        return DocumentType::CPP_FILE;
    }
    return DocumentType::UNKNOWN;
}


Document::Document(std::string filepath, DocumentType type) 
    : m_filepath(filepath), m_type(type)
{
    std::ifstream file;
    file.open(filepath, std::ios::binary | std::ios::in);
    std::string str;
    
    while(true){
        getline(file, str);
        if(file.fail()) break;
        std::cout << str << std::endl;
    }
}
void Document::write(std::string doc){
}

void Document::writeLine(std::string line, int rowIndx){
    if(rowIndx == -1){
        // indx = last => append at end of file
    }
}
void Document::writeChar(char c, int rowIndx, int colIndx){
    
}

void Document::save(){
    
}

void DocumentHandler::open(std::string filepath){
    if (filepath.length() == 0) return;
    // TODO Check if file exists
    // Add file
    std::string filetype = filepath.substr(filepath.find('.', filepath.length()-5)+1);
    
    std::cout << filetype << std::endl;
    
    DocumentType t = settingUpEnvironment(filetype);
    
    Document d(filepath, t);
    
    m_docs.push_back(std::move(d));
    /*    
    while(true){
        getline(file, str);
        if(file.fail()) break;
        std::cout << str << std::endl;
    }
    */
}

void DocumentHandler::close(std::string filepath){
    
}

Document * const DocumentHandler::getCurrentDoc(){
    return m_currentDoc;
}

const std::vector<Document>& DocumentHandler::getDocuments(){
    return m_docs;
}
