#include "../documenthandler.hpp"

#include "../../utils/log.hpp"

namespace Yate::Core {

using namespace Utils;
constexpr const std::string DOMAIN = "YCORE::DOCH";

DocumentHandler::DocumentHandler(Api::IFileIOFactory& fileio_factory)
    : Api::IObject("DocumentHandler"),
      m_documents(),
      m_fileio_factory(fileio_factory)
{}

void DocumentHandler::update()
{
    for(auto d : m_documents){
        d.second.update_history();
    }
}

void DocumentHandler::open_file(const std::string& filepath, const std::string& fileio){
    if(m_documents.find(filepath) == m_documents.end()){
        log(Log_t::DEBUG, DOMAIN, "Open document...\n");
        std::unique_ptr<Core::Api::FileReader> filereader = m_fileio_factory.create_reader(fileio);
        m_documents.insert(std::make_pair(filepath, filereader->read(filepath)));
        log(Log_t::DEBUG, DOMAIN, "Document %s opened, notify observers\n", filepath.c_str());
        emit_event("open_file_list_change", m_documents);
    } else {
        log(Log_t::DEBUG, DOMAIN, "Document already opened, nothing to do.\n");
    }
    emit_event("file_opened", m_documents[filepath]);
}

void DocumentHandler::close_file(const std::string& filepath){
    emit_event("open_file_list_change", m_documents);
}

void DocumentHandler::onOpenFileCommand(const Utils::Event& event){
    log(Log_t::INFO, DOMAIN, "onOpenFile Callback received\n");
    auto& arguments = event.arguments;
    if (arguments.size() == 2) {
        try {
            auto filename = std::any_cast<const std::string&>(arguments[0]);
            auto fileio = std::any_cast<const std::string&>(arguments[1]);
            // Verwendung der Map...
            log(Log_t::SILLY, DOMAIN, "Callback data casted\n");
            //std::shared_ptr<Core::Api::IFileReader> reader = m_fileio_factory.get_reader();
            open_file(filename, fileio);
        } catch(const std::bad_any_cast& e) {
            log(Log_t::ERROR, DOMAIN, "Error: %s\n", e.what());
        }
    }
}

void DocumentHandler::onCloseFileCommand(const Utils::Event& event){
    log(Log_t::INFO, DOMAIN, "onCloseFile Callback received\n");
    auto& arguments = event.arguments;
    if (arguments.size() == 2) {
        try {
            auto filename = std::any_cast<const std::string&>(arguments[0]);
            auto filereader_name = std::any_cast<const std::string&>(arguments[1]);
            // Verwendung der Map...
            log(Log_t::SILLY, DOMAIN, "Callback data casted\n");
            close_file(filename/*, m_fileio_factory.get_reader(filereader_name)*/);
        } catch(const std::bad_any_cast& e) {
            log(Log_t::ERROR, DOMAIN, "Error: %s\n", e.what());
        }
    }
}

void DocumentHandler::onDocumentChangeCommand(const Utils::Event& event){

}

} // end namespace Yate::Core
