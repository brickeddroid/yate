#ifndef IDOCUMENTFACTORY_HPP
#define IDOCUMENTFACTORY_HPP

#include <string>

#include "idocument.hpp"

namespace YateCore {

enum DocumentType {
    CPP_FILE,
    CSHARP_FILE,
    XML_FILE,
    UNKNOWN
};

class IDocumentFactory {
public:
    virtual IDocument* const createDocument(const std::string& filepath);
protected:
    IDocumentFactory(){}
};

} // endof namespace YateCore

#endif
