#include "logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

std::shared_ptr<spdlog::logger> logger::m_logger;

void logger::init() {
    std::vector<spdlog::sink_ptr> sinks;
    sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("graphing.log", true));

    sinks[0]->set_pattern("%^[%T] %n: %v%$");
    sinks[1]->set_pattern("[%T] [%l] %n: %v");

    m_logger = std::make_shared<spdlog::logger>("GRAPHING", begin(sinks), end(sinks));
    spdlog::register_logger(m_logger);
    m_logger->set_level(spdlog::level::trace);
    m_logger->flush_on(spdlog::level::trace);
}