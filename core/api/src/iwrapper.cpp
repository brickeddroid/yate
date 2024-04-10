#include "../iwrapper.hpp"

namespace YateCore {
IWrapper::IWrapper(const std::string& name)
    : ICore(name),
      m_document_handler(nullptr)
{}

void IWrapper::set_document_handler(DocumentHandler* const doc_handler)
{
    m_document_handler = doc_handler;
}

const std::string& IWrapper::get_document(const std::string& file_path)
{
    if(m_document_handler != nullptr){
        IDocument* const doc = m_document_handler->open(file_path);
        //IDocument* const doc = doc_map[file_path]->open(file_path);
        wrap_document(doc, m_data);
    }
    return m_data;
}

} // end namespace YateCore
