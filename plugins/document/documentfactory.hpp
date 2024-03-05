#ifndef DOCUMENTFACTORY_HPP
#define DOCUMENTFACTORY_HPP

#include <string>

#include "../../core/interfaces/idocumentfactory.hpp"

namespace YateDocument {

enum DocumentType {
    CPP_FILE,
    CSHARP_FILE,
    XML_FILE,
    UNKNOWN
};

class DocumentFactory : public YateCore::IDocumentFactory {
public:
    DocumentFactory() : YateCore::IDocumentFactory() {}

    virtual YateCore::IDocument* const createDocument(const std::string& filepath) override;
};

} // endof namespace YateDocument

#endif
