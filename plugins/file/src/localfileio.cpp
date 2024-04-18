#include <localfileio.hpp>
#include <filesystem>
#include <fstream>

#include "../../../utils/log.hpp"

namespace fs = std::filesystem;

namespace Yate::Plugin {

using namespace Utils;

constexpr const char* DOMAIN = "YPLUGIN::FILEIO";

Core::Document LocalFileReader::read(const std::string& filepath){
    log(Log_t::DEBUG, DOMAIN, "Open file %s ... \n", filepath.c_str());
    Core::Document d(filepath);
    if (std::ifstream ifs { filepath }) {
        std::string data((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        d.set_content(data);
        log(Log_t::DEBUG, DOMAIN, "Document created\n");
    }
    log(Log_t::DEBUG, DOMAIN, "File open done. %s\n", filepath.c_str());
    return d;
}

void LocalFileWriter::write(const std::string& filepath, const Core::Document& document){
    log(Log_t::DEBUG, DOMAIN, "Writing to file %s ...\n", filepath.c_str());
    // TODO Write to local file
    log(Log_t::DEBUG, DOMAIN, "File open done. %s\n", filepath.c_str());
}

} // end namespace Yate::Plugin
