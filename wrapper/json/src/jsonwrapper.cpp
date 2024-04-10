#include "../jsonwrapper.hpp"
#include "../../../utils/log.hpp"

#include <nlohmann/json.hpp>
using json = nlohmann::json;


namespace Yate::Wrapper {
using namespace Utils;
const std::string DOMAIN = "YWRAPPER";

//std::string JsonWrapper::get_updated_data()
//{
//    std::string json = "";
//
//    return json;
//}


//void JsonWrapper::update_data(const std::string& json_data){
//
//}
JsonWrapper::JsonWrapper(Core::DocumentHandler& document_handler, Core::Api::IUiPlugin& uiplugin/*, Core::Api::FileIOFactory& fileio_factory*/)
    : IWrapper(document_handler, uiplugin, "JsonWrapper")
        /*m_fileio_factory(fileio_factory)*/
{
}

//void JsonWrapper::preprocess(std::string& msg){
//
//}
/*
std::string JsonWrapper::wrap_document_content(const std::string& content)
{
    log(Log_t::INFO, DOMAIN, "Wrap document content to json...\n");
    json j;
    j["content"] = content;
    return j.dump();
}

std::string JsonWrapper::wrap_document_history(const std::vector<Core::DocumentChange>& history){
    return "";
}

std::string JsonWrapper::wrap_open_document_list(const std::map<std::string, Core::Document>& document_list){
    return "";
}
*/
void JsonWrapper::onFileOpened(const Utils::Event & event){
    auto& arguments = event.arguments;
    json j;
    if (arguments.size() > 0) {
        try {
            auto doc = std::any_cast<const Core::Document&>(arguments[0]);
            // Verwendung der Map...
            log(Log_t::SILLY, DOMAIN, "Callback data casted\n");
            j["filename"] = doc.name();
            j["content"] = doc.content();
        } catch(const std::bad_any_cast& e) {
            log(Log_t::ERROR, DOMAIN, "Error: %s\n", e.what());
        }
    }
    emit_event("file_opened", j.dump());
}

void JsonWrapper::onOpenFileListChange(const Utils::Event & event){

    log(Log_t::INFO, DOMAIN, "onOpenFileListChange Callback received\n");
    auto& arguments = event.arguments;
    json j;
    j["doc_list"] = json::array();
    if (arguments.size() > 0) {
        try {
            auto arg = std::any_cast<const std::map<std::string, Core::Document>&>(arguments[0]);
            // Verwendung der Map...
            log(Log_t::SILLY, DOMAIN, "Callback data casted\n");
            for (const auto& pair : arg) {
                j["doc_list"].push_back(pair.first);
            }
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
    std::string result = j.dump();
    emit_event("open_file_list_change", result);
    //process(result);
}

void JsonWrapper::onDocumentChange(const Utils::Event& event){
    log(Log_t::INFO, DOMAIN, "onDocumentChange Callback received\n");
    std::string msg;
    auto& arguments = event.arguments;
    if (arguments.size() > 0) {
        try {
            msg = std::any_cast<const std::string&>(arguments[0]);
            log(Log_t::SILLY, DOMAIN, "Callback data casted\n");
        } catch(const std::bad_any_cast& e) {
            log(Log_t::ERROR, DOMAIN, "Error: %s\n", e.what());
        }
    }
    emit_event("document_change", msg);
}

void JsonWrapper::onCommandRequest(const Utils::Event& event){
    log(Log_t::INFO, DOMAIN, "onCommandRequest Callback received\n");
    std::string msg;
    auto& arguments = event.arguments;
    if (arguments.size() > 0) {
        try {
            msg = std::any_cast<const std::string&>(arguments[0]);
            log(Log_t::SILLY, DOMAIN, "Callback data casted\n");
        } catch(const std::bad_any_cast& e) {
            log(Log_t::ERROR, DOMAIN, "Error: %s\n", e.what());
        }
    }

    json j = json::parse(msg);
    const auto cmd = j["cmd"].get<std::string>();
    auto filename = j["file"].get<std::string>();
    log(Log_t::DEBUG, DOMAIN, "Command: '%s %s'\n", cmd.c_str(), filename.c_str());
    if(cmd == "open"){
        //Core::Api::IFileReader& fr = m_fileio_factory.get_reader("local");
        //m_document_handler.open(filename, fr);
        emit_event("cmd_open_file", filename, "local");

        //return m_document_handler.get_document(filename).content();

    }

}
/*
void JsonWrapper::process_incoming_message(const std::string& msg){
    json j = json::parse(msg);

    const auto cmd = j["cmd"].get<std::string>();
    const auto filename = j["file"].get<std::string>();
    log(Log_t::DEBUG, DOMAIN, "Incoming message: %s %s\n", cmd.c_str(), filename.c_str());
    if(cmd == "open"){
        //Core::Api::IFileReader& fr = m_fileio_factory.get_reader("local");
        //m_document_handler.open(filename, fr);
        emit_event("cmd_open_file", filename, "local");

        //return m_document_handler.get_document(filename).content();

    }
}
*/
//void JsonWrapper::on_document_change(const Yate::Core::Document& document){
//    log(Log_t::SILLY, DOMAIN, document.content());
//    // Notify connected plugins about a change
//}

} // end namespace Yate::Wrapper
