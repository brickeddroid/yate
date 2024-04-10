#ifndef LOG_HPP
#define LOG_HPP

#include <stdio.h>
#include <stdarg.h>
#include <string>
namespace Yate::Utils {
enum Log_t {
    SILLY,
    VERBOSE,
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    NONE
};

extern Log_t LogLevel;

int log(Log_t log_level, const std::string& domain, const std::string& format, ...);

} // end namespace Yate::Utils

#endif
