#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
namespace YateCore {
enum DocumentType {
    CPP_FILE,
    CSHARP_FILE,
    XML_FILE,
    UNKNOWN
};

class Document {
private:
    DocumentType m_type;
    std::string m_filepath;
    std::string m_project;
    
    std::string m_content;
public:
    Document(std::string filepath, DocumentType type);
    
    std::string getRaw();
    std::vector<std::string> getLines();
    std::vector<std::string> getKeywordsTable();
    
    void write(std::string doc);
    
    void writeLine(std::string line, int rowIndx = -1);
    
    void writeChar(char c, int rowIndx, int colIndx);
    
    void save();
};

class DocumentHandler {
private:
    std::vector<Document> m_docs;
    
    Document* m_currentDoc;
public:
    void open(std::string filepath);
    
    void close(std::string filepath);
    
    Document * const getCurrentDoc();
    
    const std::vector<Document>& getDocuments();
  
};
}

#endif
