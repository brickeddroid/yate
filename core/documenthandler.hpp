#ifndef DOCUMENTHANDLER_HPP
#define DOCUMENTHANDLER_HPP

#include "interfaces/idocument.hpp"
#include "interfaces/idocumentfactory.hpp"

#include <string>
#include <map>

namespace YateCore {

class DocumentHandler {
private:
    std::map<std::string, IDocument*> m_documents;
    
    IDocument* m_current_document;
    IDocumentFactory* m_factory;
public:
    DocumentHandler(IDocumentFactory* const factory);

    IDocument* const open(const std::string& filepath);
    
    void close(const std::string& filepath);
    
    IDocument * const get_current_doc();
    
    const std::map<std::string, IDocument*>& get_documents();

    void set_factory(IDocumentFactory* const factory);
  
};
} // end namespace YateCore

#endif
