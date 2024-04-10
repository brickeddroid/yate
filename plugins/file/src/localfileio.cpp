#include <localfileio.hpp>
#include <filesystem>
#include <fstream>

#include "../../../utils/log.hpp"

namespace fs = std::filesystem;

namespace Yate::Plugin {

using namespace Utils;

constexpr const char* DOMAIN = "YPLUGIN::FILE";

Core::Document LocalFileReader::read(const std::string& filepath){
    log(Log_t::DEBUG, DOMAIN, "Try open file... %s\n", filepath.c_str());
    Core::Document d(filepath);
    if (std::ifstream ifs { filepath }) {
        std::string data((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        d.set_content(data);
        log(Log_t::DEBUG, DOMAIN, "Document created\n");
    }
    log(Log_t::DEBUG, DOMAIN, "File open done. %s\n", filepath.c_str());
    return d;
}

} // end namespace Yate::Plugin
