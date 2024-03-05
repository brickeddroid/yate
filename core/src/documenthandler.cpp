#include "../documenthandler.hpp"

namespace YateCore {

DocumentHandler::DocumentHandler(IDocumentFactory* const factory)
{
    m_factory = factory;
}

IDocument* const DocumentHandler::open(const std::string& filepath){
    if (filepath.length() == 0) return m_current_document;

    if(m_documents.find(filepath) == m_documents.end()){
        m_documents[filepath] = m_factory->createDocument(filepath);
    }
    m_current_document = m_documents[filepath];
    return m_current_document;
}

void DocumentHandler::close(const std::string& filepath){
    
}

IDocument * const DocumentHandler::get_current_doc(){
    return m_current_document;
}

const std::map<std::string, IDocument*>& DocumentHandler::get_documents(){
    return m_documents;
}

void DocumentHandler::set_factory(IDocumentFactory* const factory){
    m_factory = factory;
}

} // end namespace YateCore
