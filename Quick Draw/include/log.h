#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

// static class so there is no data and no objects
class log
{
public:
	static void init();

	inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return m_coreLogger; }
	inline static std::shared_ptr<spdlog::logger>& getFileLogger() { return m_fileLogger; }

private:
	static std::shared_ptr<spdlog::logger> m_coreLogger;
	static std::shared_ptr<spdlog::logger> m_fileLogger;
};

#define and &&
#define or ||

#if defined(DEBUG)
// MUST CALL THIS ON START
	#define LOG_INIT ::log::init()

	// OUPUT
	#define LOG_TRACE(...) ::log::getCoreLogger()->trace(__VA_ARGS__);     ::log::getFileLogger()->trace(__VA_ARGS__)
	#define LOG_INFO(...)  ::log::getCoreLogger()->info(__VA_ARGS__);      ::log::getFileLogger()->info(__VA_ARGS__)
	#define LOG_WARN(...)  ::log::getCoreLogger()->warn(__VA_ARGS__);      ::log::getFileLogger()->warn(__VA_ARGS__)
	#define LOG_ERROR(...) ::log::getCoreLogger()->error(__VA_ARGS__);     ::log::getFileLogger()->error(__VA_ARGS__)
	#define LOG_FATAL(...) ::log::getCoreLogger()->critical(__VA_ARGS__);  ::log::getFileLogger()->critical(__VA_ARGS__)

	// SET_LEVEL
	#define LOG_SET_LEVEL_TRACE  ::log::getCoreLogger()->set_level(spdlog::level::trace)
	#define LOG_SET_LEVEL_INFO   ::log::getCoreLogger()->set_level(spdlog::level::info)
	#define LOG_SET_LEVEL_WARN   ::log::getCoreLogger()->set_level(spdlog::level::warn)
	#define LOG_SET_LEVEL_ERROR  ::log::getCoreLogger()->set_level(spdlog::level::err)
	#define LOG_SET_LEVEL_FATAL  ::log::getCoreLogger()->set_level(spdlog::level::critical)

#else
	#define LOG_INIT 

	// OUPUT
	#define LOG_TRACE
	#define LOG_INFO
	#define LOG_WARN
	#define LOG_ERROR
	#define LOG_FATAL

	// SET_LEVEL
	#define LOG_SET_LEVEL_TRACE
	#define LOG_SET_LEVEL_INFO 
	#define LOG_SET_LEVEL_WARN 
	#define LOG_SET_LEVEL_ERROR
	#define LOG_SET_LEVEL_FATAL


#endif