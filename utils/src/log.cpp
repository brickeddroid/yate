#include "../log.hpp"
//#include <ctime>
#include <chrono>

//using namespace std::chrono;

namespace YateUtils {
/*
std::cout << std::asctime(std::localtime(&result))
          << result << " seconds since the Epoch\n";
*/
std::string log_level_to_string(Log_t ltype)
{
    switch(ltype){
        case Log_t::NONE:
            return "";
        case Log_t::SILLY:
            return "SILLY";
        case Log_t::VERBOSE:
            return "VERBOSE";
        case Log_t::DEBUG:
            return "DEBUG";
        case Log_t::INFO:
            return "INFO";
        case Log_t::WARNING:
            return "WARNING";
        case Log_t::ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}

//...


int log(Log_t log_level, std::string format, ...){
    if(log_level != Log_t::NONE){
        int64_t timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        std::string ins_string = "[" + std::to_string(timestamp) + "]["+ log_level_to_string(log_level) +"] ";
        format = format.insert(0, ins_string);
    }
    int done = 0;
    va_list arg;
    va_start(arg, format.c_str());
    done = vfprintf(stdout, format.c_str(), arg);
    va_end(arg);
    return done;
}

} // end namespace YateUtil
