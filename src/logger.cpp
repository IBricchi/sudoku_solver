#include "logger.h"

LoggerPtr Logger::logger;

void Logger::init(std::string&& name){
    spdlog::set_pattern("%^[%T] (%s:%#) %L: %v%$");
    logger = spdlog::stdout_color_mt(name);
}

LoggerPtr Logger::get_logger(){
    return logger;
}