#include "../fileiofactory.hpp"

#include "../localfileio.hpp"
#include "../../../utils/log.hpp"

namespace Yate::Plugin {

using namespace Utils;

constexpr const char* DOMAIN = "YPLUGIN::FILE";
std::unique_ptr<Core::Api::FileReader> FileIOFactory::create_reader(const std::string& name) const {
    if("local" == name){
        return std::make_unique<LocalFileReader>();
    }
    return std::make_unique<Core::Api::FileReader>();
}

std::unique_ptr<Core::Api::FileWriter> FileIOFactory::create_writer(const std::string& name) const {
    if("local" == name){
        return std::make_unique<LocalFileWriter>();
    }
    return std::make_unique<Core::Api::FileWriter>();
}

} //end namespace Yate::Plugin
