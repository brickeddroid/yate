#include "../log.hpp"
#include <chrono>
#include <map>
#include <mutex>

namespace Yate::Utils {

/* Used code colors can be found here:
 * https://www.codeproject.com/Tips/5255355/How-to-Put-Color-on-Windows-Console
*/
const std::map<Log_t, std::pair<const std::string, const std::string>> log_level_to_string = {
    { Log_t::SILLY,   std::make_pair("SILLY", "\033[90m") },
    { Log_t::VERBOSE, std::make_pair("VERBOSE", "\033[32m") },
    { Log_t::DEBUG,   std::make_pair("DEBUG", "\033[92m") },
    { Log_t::INFO,    std::make_pair("INFO", "\033[37m") },
    { Log_t::WARNING, std::make_pair("WARNING", "\033[93m") },
    { Log_t::ERROR,   std::make_pair("ERROR", "\033[91m") },
    { Log_t::NONE,    std::make_pair("NONE", "") }
};

constexpr const std::string default_console_color = "\033[0m";
Log_t LogLevel = Log_t::SILLY;

int log(Log_t log_level, const std::string& domain, const std::string& format, ...){
    //const std::lock_guard<std::mutex> lock(log_mutex);
    if( log_level < LogLevel ||
        log_level > Log_t::NONE){
        return 0;
    }
    std::stringstream ss;
    ss << log_level_to_string.at(log_level).second;
    int color_len = log_level_to_string.at(log_level).second.length();
    if(log_level != Log_t::NONE){
        ss << "["
           << std::chrono::floor<std::chrono::milliseconds>(std::chrono::system_clock::now())
           << "]["
           << log_level_to_string.at(log_level).first
           << "]["
           << domain
           << "] ";
    }
    ss << format << default_console_color;
    color_len += default_console_color.length();
    int done = -color_len;
    va_list arg;
    va_start(arg, ss.str().c_str());
    done = vfprintf(stdout, ss.str().c_str(), arg);
    va_end(arg);
    return done;
}

} // end namespace Yate::Utils
