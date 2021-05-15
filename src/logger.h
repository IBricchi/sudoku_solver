#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory>

using LoggerPtr = std::shared_ptr<spdlog::logger>;

class Logger{
public:
    static void init(std::string&& name);

    static LoggerPtr get_logger();
private:
    static LoggerPtr logger;
};

#ifdef DEBUG
    #define LOG_INFO(...) Logger::get_logger()->log(spdlog::source_loc{__FILE__, __LINE__, static_cast<const char *>(__FUNCTION__)},spdlog::level::info,__VA_ARGS__)
    #define LOG_WARN(...) Logger::get_logger()->log(spdlog::source_loc{__FILE__, __LINE__, static_cast<const char *>(__FUNCTION__)},spdlog::level::warn,__VA_ARGS__)
    #define LOG_ERR(...) Logger::get_logger()->log(spdlog::source_loc{__FILE__, __LINE__, static_cast<const char *>(__FUNCTION__)},spdlog::level::err,__VA_ARGS__)
    #define LOG_CRIT(...) Logger::get_logger()->log(spdlog::source_loc{__FILE__, __LINE__, static_cast<const char *>(__FUNCTION__)},spdlog::level::critical,__VA_ARGS__)
#else
    #define LOG_INFO
    #define LOG_WARN
    #define LOG_ERR
    #define LOG_CRIT
#endif