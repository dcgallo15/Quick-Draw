#include "../include/log.h"

std::shared_ptr<spdlog::logger> log::m_coreLogger;
std::shared_ptr<spdlog::logger> log::m_fileLogger = spdlog::basic_logger_mt("basic_logger", "log.txt",true);

void log::init() 
{
	spdlog::set_pattern("%^ [%T] [%L]: %v%$");	// FORMATTING
	m_coreLogger = spdlog::stdout_color_mt("APP");
	m_coreLogger->set_level(spdlog::level::trace);
	m_fileLogger->set_level(spdlog::level::trace);
}