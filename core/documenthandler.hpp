#ifndef DOCUMENTHANDLER_HPP
#define DOCUMENTHANDLER_HPP

#include "document.hpp"
#include "api/ifileiofactory.hpp"

#include <string>
#include <map>


namespace Yate::Core {

class DocumentHandler : public Api::IObject {
private:
    std::map<std::string, Document> m_documents;
    Api::IFileIOFactory& m_fileio_factory;
    
public:
    DocumentHandler(Api::IFileIOFactory& fileio_factory);

    void open_file(const std::string& filepath, std::shared_ptr<Api::IFileReader> filereader);
    
    void close_file(const std::string& filepath);
    
    const std::map<std::string, Document>& get_open_documents();

    Document& get_document(const std::string& filepath);

    void onOpenFileCommand(const Utils::Event& event);
    void onCloseFileCommand(const Utils::Event& event);
    void onDocumentChangeCommand(const Utils::Event& event);
};

} // end namespace Yate::Core

#endif
