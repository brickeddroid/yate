#include "../iwrapper.hpp"

#include "../../../utils/log.hpp"

namespace Yate::Core::Api {

using namespace Utils;

constexpr const char* DOMAIN = "YCAPI::WRAP";

IWrapper::IWrapper(/*DocumentHandler& document_handler, IUiPlugin& uiplugin,*/ const std::string& name)
    : IObject(name)
      /*m_document_handler(document_handler)*/
{
    /*
    // DocumentHandler registration
    document_handler.register_observer("file_opened", &IWrapper::onFileOpened, this);
    document_handler.register_observer("open_file_list_change", &IWrapper::onOpenFileListChange, this);

    register_observer("cmd_open_file", &DocumentHandler::onOpenFileCommand, &document_handler);
    register_observer("cmd_close_file", &DocumentHandler::onCloseFileCommand, &document_handler);
    register_observer("cmd_document_change", &DocumentHandler::onDocumentChangeCommand, &document_handler);


    // IUiPlugin registration
    uiplugin.register_observer("cmd_request", &IWrapper::onCommandRequest, this);

    register_observer("file_opened", &IUiPlugin::onCoreUpdateMessage, &uiplugin);
    register_observer("open_file_list_change", &IUiPlugin::onCoreUpdateMessage, &uiplugin);
    */
}

void IWrapper::onFileOpened(const Utils::Event & event){
    auto& arguments = event.arguments;
    if (arguments.size() > 0) {
        try {
            auto doc = std::any_cast<const Core::Document&>(arguments[0]);
            std::string result = document_to_string(doc);
            log(Log_t::VERBOSE, DOMAIN, "Document converted\n");
            emit_event("file_opened", result);
        } catch(const std::bad_any_cast& e) {
            log(Log_t::ERROR, DOMAIN, "Error: %s\n", e.what());
        }
    }
}

void IWrapper::onOpenFileListChange(const Utils::Event & event){

    log(Log_t::DEBUG, DOMAIN, "onOpenFileListChange Callback received\n");
    auto& arguments = event.arguments;
    //json j;
    if (arguments.size() > 0) {
        try {
            auto doc_map = std::any_cast<const std::map<std::string, Core::Document>&>(arguments[0]);
            std::string result = doc_list_to_string(doc_map);
            log(Log_t::VERBOSE, DOMAIN, "Document list converted\n");
            emit_event("open_file_list_change", result);
        } catch(const std::bad_any_cast& e) {
            log(Log_t::ERROR, DOMAIN, "Error: %s\n", e.what());
        }
    }

    /*
    auto& open_docs = dochandler->get_open_documents();
    json j;
    j["doc_list"] = json::array();
    for(const auto& open_doc : open_docs){
        j["doc_list"].push_back(open_doc.first);
    }
    */

    //std::string result = "event: file_list\ndata: " + j.dump() + "\n\n";
    //process(result);
}

void IWrapper::onDocumentChange(const Utils::Event& event){
    log(Log_t::DEBUG, DOMAIN, "onDocumentChange Callback received\n");
    auto& arguments = event.arguments;
    if (arguments.size() > 0) {
        try {
            auto doc_change = std::any_cast<const DocumentChange&>(arguments[0]);
            std::string result = doc_change_to_string(doc_change);
            log(Log_t::VERBOSE, DOMAIN, "Document change converted\n");
            emit_event("document_change", result);
        } catch(const std::bad_any_cast& e) {
            log(Log_t::ERROR, DOMAIN, "Error: %s\n", e.what());
        }
    }
}

void IWrapper::onCommandRequest(const Utils::Event& event){
    log(Log_t::DEBUG, DOMAIN, "onCommandRequest Callback received\n");
    auto& arguments = event.arguments;
    if (arguments.size() > 0) {
        try {
            std::string msg = std::any_cast<const std::string&>(arguments[0]);
            Core::Api::CommandEventMessage evt_msg = cmd_from_string(msg);
            log(Log_t::VERBOSE, DOMAIN,
                "Command converted %s %s %s\n",
                evt_msg.cmd.c_str(),
                evt_msg.filename.c_str(),
                evt_msg.filerw.c_str()
            );
            emit_event(evt_msg.cmd, evt_msg.filename, evt_msg.filerw);
        } catch(const std::bad_any_cast& e) {
            log(Log_t::ERROR, DOMAIN, "Error: %s\n", e.what());
        }
    }
}

} // end namespace Yate::Core::Api
