#include "../log.hpp"
#include <chrono>
#include <map>
#include <mutex>

namespace Yate::Utils {

const std::map<Log_t, const std::string> log_level_to_string = {
    { Log_t::SILLY,   "SILLY" },
    { Log_t::VERBOSE, "VERBOSE" },
    { Log_t::DEBUG,   "DEBUG" },
    { Log_t::INFO,    "INFO" },
    { Log_t::WARNING, "WARNING" },
    { Log_t::ERROR,   "ERROR" },
    { Log_t::NONE,    "NONE" }
};

Log_t LogLevel = Log_t::SILLY;

std::mutex log_mutex;

int log(Log_t log_level, const std::string& domain, const std::string& format, ...){
    const std::lock_guard<std::mutex> lock(log_mutex);
    if(log_level < LogLevel) return 0;
    std::stringstream ss;
    if(log_level != Log_t::NONE){
        ss << "["
           << std::chrono::floor<std::chrono::milliseconds>(std::chrono::system_clock::now())
           << "]["
           << log_level_to_string.at(log_level)
           << "]["
           << domain
           << "] ";
    }
    ss << format;
    int done = 0;
    va_list arg;
    va_start(arg, ss.str().c_str());
    done = vfprintf(stdout, ss.str().c_str(), arg);
    va_end(arg);
    return done;
}

} // end namespace Yate::Utils
