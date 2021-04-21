#pragma once

#include <spdlog/spdlog.h>

class logger {
public:
    static void init();
    static std::shared_ptr<spdlog::logger>& get_logger() { return m_logger; }

private:
    static std::shared_ptr<spdlog::logger> m_logger;
};

#define LOG_TRACE(...)  ::logger::get_logger()->trace(__VA_ARGS__)
#define LOG_INFO(...)   ::logger::get_logger()->info(__VA_ARGS__)
#define LOG_WARN(...)  ::logger::get_logger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)  ::logger::get_logger()->error(__VA_ARGS__)