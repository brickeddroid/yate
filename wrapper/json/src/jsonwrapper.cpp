#include "../jsonwrapper.hpp"
#include "../../../utils/log.hpp"

#include <json.hpp>
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
JsonWrapper::JsonWrapper()
    : IWrapper("JsonWrapper")
        /*m_fileio_factory(fileio_factory)*/
{
}
/*
Core::Api::CommandEventMessage JsonWrapper::from_string(const std::string& msg){

}
std::string JsonWrapper::to_string(const Core::Api::EventMessage& event_message){
    json j;


    return j.dump();
}
*/

Core::Api::CommandEventMessage JsonWrapper::cmd_from_string(const std::string& msg){
    Core::Api::CommandEventMessage evt_msg;
    json j = json::parse(msg);
    evt_msg.cmd = j["cmd"].get<std::string>();
    evt_msg.filename = j["file"].get<std::string>();
    evt_msg.filerw = j["filerw"].get<std::string>();
    log(Log_t::DEBUG, DOMAIN, "Command: '%s %s %s'\n", evt_msg.cmd.c_str(), evt_msg.filename.c_str(), evt_msg.filerw.c_str());
    return evt_msg;
}
/*
std::string JsonWrapper::to_string(const std::string& str)
{

}
*/
std::string JsonWrapper::doc_change_to_string(const Core::DocumentChange& change)
{
    json j;
    j["origin_id"] = change.origin_id;
    j["timestamp"] = change.timestamp;
    j["operation"] = change.operation;
    j["cursor_position"] = change.cursor_position;
    j["length"]    = change.length;
    j["data"]      = change.data;
    return j.dump();
}

std::string JsonWrapper::document_to_string(const Core::Document& document)
{
    json j;
    j["filename"] = document.name();
    j["content"] = document.content();
    return j.dump();
}

std::string JsonWrapper::doc_list_to_string(const std::map<std::string, Core::Document>& doc_map)
{
    json j;
    j["doc_list"] = json::array();
    for (const auto& pair : doc_map) {
        j["doc_list"].push_back(pair.first);
    }
    return j.dump();
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
