#ifndef LOG_HPP
#define LOG_HPP

#include <stdio.h>
#include <stdarg.h>
#include <string>

namespace YateUtils {
enum Log_t {
    NONE,
    SILLY,
    VERBOSE,
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

//std::string log_level_to_string(Log_t ltype);
int log(Log_t log_level, std::string format, ...);

} // end namespace YateUtil

#endif
