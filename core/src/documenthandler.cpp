#include "../documenthandler.hpp"

#include "../../utils/log.hpp"

namespace Yate::Core {

using namespace Utils;
constexpr const std::string DOMAIN = "YCORE::DOCH";

bool DocumentHandler::open_file(const std::string& filepath, const std::string& fileio){
    if(m_documents.find(filepath) != m_documents.end()){
        log(Log_t::INFO, DOMAIN, "Document %s already opened, nothing to do.\n", filepath.c_str());
        return false;
    }
    log(Log_t::DEBUG, DOMAIN, "Open document...\n");
    std::unique_ptr<Core::Api::FileReader> filereader = m_fileio_factory.create_reader(fileio);
    m_documents.insert(std::make_pair(filepath, filereader->read(filepath)));
    log(Log_t::DEBUG, DOMAIN, "Document %s opened, notify observers\n", filepath.c_str());
    return true;
}

bool DocumentHandler::close_file(const std::string& filepath, const std::string& fileio){
    if(m_documents.find(filepath) == m_documents.end()){
        log(Log_t::INFO, DOMAIN, "Document %s already closed, nothing to do.\n", filepath.c_str());
        return false;
    }
    return false;
}

bool DocumentHandler::save_file(const std::string& filepath, const std::string& fileio){
    //emit_event("file_saved", m_documents.at(filepath));
    return false;
}

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

void DocumentHandler::onFileCommand(const Utils::Event& event){
    if(event.arguments.size() != 3) {
        log(Log_t::ERROR, DOMAIN, "%s Callback error, wrong number of args\n", event.name.c_str());
        return;
    }
    log(Log_t::INFO, DOMAIN, "%s Callback received\n", event.name.c_str());
    auto& arguments = event.arguments;

    Operation docop = Operation::NOP;
    std::string filename = "";
    std::string fileio = "";

    try {
        docop = std::any_cast<Operation>(arguments[0]);
        filename = std::any_cast<const std::string&>(arguments[1]);
        fileio = std::any_cast<const std::string&>(arguments[2]);
        log(Log_t::SILLY, DOMAIN, "Callback data casted\n");
    } catch(const std::bad_any_cast& e) {
        log(Log_t::ERROR, DOMAIN, "Error: %s\n", e.what());
        return;
    }

    bool hasListChange = false;
    switch(docop){
        case Operation::OPEN:
            hasListChange = open_file(filename, fileio);
            emit_event("file_opened", m_documents[filename]);
            break;
        case Operation::CLOSE:
            hasListChange = close_file(filename, fileio);
            emit_event("file_closed", filename);
            break;
        case Operation::SAVE:
            save_file(filename, fileio);
            emit_event("file_saved", filename);
            break;
        default:
            log(Log_t::ERROR, DOMAIN, "Error: Not a valid doc handl op: %d\n", docop);
            return;
    }
    if(hasListChange){
        emit_event("open_file_list_change", m_documents);
    }

}

void DocumentHandler::onOpenFileCommand(const Utils::Event& event){
    if(event.arguments.size() != 2) {
        log(Log_t::ERROR, DOMAIN, "onOpenFile Callback error, wrong number of args\n");
        return;
    }
    log(Log_t::INFO, DOMAIN, "onOpenFile Callback received\n");
    auto& arguments = event.arguments;



    try {
        auto filename = std::any_cast<const std::string&>(arguments[0]);
        auto fileio = std::any_cast<const std::string&>(arguments[1]);
        log(Log_t::SILLY, DOMAIN, "Callback data casted\n");
        open_file(filename, fileio);
    } catch(const std::bad_any_cast& e) {
        log(Log_t::ERROR, DOMAIN, "Error: %s\n", e.what());
    }
}

void DocumentHandler::onCloseFileCommand(const Utils::Event& event){
    if(event.arguments.size() != 2) {
        log(Log_t::ERROR, DOMAIN, "onCloseFile Callback error, wrong number of args\n");
        return;
    }
    log(Log_t::INFO, DOMAIN, "onCloseFile Callback received\n");
    auto& arguments = event.arguments;
    if (arguments.size() == 2) {
        try {
            auto filename = std::any_cast<const std::string&>(arguments[0]);
            auto fileio = std::any_cast<const std::string&>(arguments[1]);
            log(Log_t::SILLY, DOMAIN, "Callback data casted\n");
            close_file(filename, fileio);
        } catch(const std::bad_any_cast& e) {
            log(Log_t::ERROR, DOMAIN, "Error: %s\n", e.what());
        }
    }
}

void DocumentHandler::onDocumentChangeCommand(const Utils::Event& event){

}

} // end namespace Yate::Core
