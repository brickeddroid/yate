#include "../jsonwrapper.hpp"
#include "../../../utils/log.hpp"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

using namespace YateUtils;

namespace YateWrapper {
std::string JsonWrapper::get_updated_data()
{
    std::string json = "";

    return json;
}


void JsonWrapper::update_data(const std::string& json_data){

}

void JsonWrapper::wrap_document(YateCore::IDocument* const doc, std::string& result)
{
    log(Log_t::INFO, "Wrap document to json...\n");
    const std::vector<std::string>& line_vector = doc->get_lines();
    json j;
    for(auto line : line_vector){
        j["lines"].push_back(line);
    }
    result = j.dump();
}

} // endof namespace YateWrapper
