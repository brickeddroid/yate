#include "../documentfactory.hpp"

#include "../../../utils/log.hpp"

#include "../cpp_doc/cpp_doc.hpp"

using namespace YateUtils;

namespace YateDocument {

const char* to_string(DocumentType dt){
    switch(dt){
        case CPP_FILE:
            return "C++ file";
        case CSHARP_FILE:
            return "C# file";
        case XML_FILE:
            return "XML file";
        default:
            return "Unknown file";
    }
}

DocumentType get_doc_type(const std::string &filetype)
{
    DocumentType dt = DocumentType::UNKNOWN;

    if(filetype == "cpp" || filetype == "hpp"){
        dt = DocumentType::CPP_FILE;
    }

    log(Log_t::VERBOSE, "%s detected\n", to_string(dt));
    return dt;
}

YateCore::IDocument* const DocumentFactory::createDocument(const std::string& filepath)
{
    std::string filetype = filepath.substr(filepath.find('.', filepath.length()-5)+1);
    DocumentType doctype = get_doc_type(filetype);

    YateCore::IDocument* new_doc;
    switch(doctype)
    {
        case DocumentType::CPP_FILE:
            new_doc = new CppDocument(filepath);
        default:
            new_doc = YateCore::IDocumentFactory::createDocument(filepath);
    }
    new_doc->init_keywords();
    new_doc->read_file();
    return new_doc;
}

} //endof namespace YateDocument
