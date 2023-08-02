#pragma once

#include "utils/singleton.h"

#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/async_logger.h"
#include "spdlog/details/thread_pool.h"
#include "spdlog/details/thread_pool-inl.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"

#include <string>
#include <vector>
#include <memory>
#include <map>

#define LOG_OUTPUT_FORMAT      "%^[ %Y-%m-%d %H:%M:%S.%e ] <thread %t> [%n] [%l] %@,%! %v%$ "

#define LOG_TRACE(loggerName, ...) SPDLOG_LOGGER_CALL(spdlog::get(loggerName), spdlog::level::trace, __VA_ARGS__)
#define LOG_DEBUG(loggerName, ...) SPDLOG_LOGGER_CALL(spdlog::get(loggerName), spdlog::level::debug, __VA_ARGS__)
#define LOG_INFO(loggerName, ...) SPDLOG_LOGGER_CALL(spdlog::get(loggerName), spdlog::level::info, __VA_ARGS__)
#define LOG_WARN(loggerName, ...) SPDLOG_LOGGER_CALL(spdlog::get(loggerName), spdlog::level::warn, __VA_ARGS__)
#define LOG_ERROR(loggerName, ...) SPDLOG_LOGGER_CALL(spdlog::get(loggerName), spdlog::level::err, __VA_ARGS__)
#define LOG_CRITI(loggerName, ...) SPDLOG_LOGGER_CALL(spdlog::get(loggerName), spdlog::level::critical, __VA_ARGS__)


#define SLOG_T(...) do {LOG_TRACE("console", __VA_ARGS__); LOG_TRACE("rotating_file", __VA_ARGS__);} while(0);
#define SLOG_D(...) do {LOG_DEBUG("console", __VA_ARGS__); LOG_DEBUG("rotating_file", __VA_ARGS__);} while(0);
#define SLOG_I(...) do {LOG_INFO("console", __VA_ARGS__); LOG_INFO("rotating_file", __VA_ARGS__);} while(0);
#define SLOG_W(...) do {LOG_WARN("console", __VA_ARGS__); LOG_WARN("rotating_file", __VA_ARGS__);} while(0);
#define SLOG_E(...) do {LOG_ERROR("console", __VA_ARGS__); LOG_ERROR("rotating_file", __VA_ARGS__);} while(0);
#define SLOG_C(...) do {LOG_CRITI("console", __VA_ARGS__); LOG_CRITI("rotating_file", __VA_ARGS__);} while(0);

#define LOGGER_INSTANCE() sinfer::Logger_s::instance();

namespace sinfer {

class Logger {
public:
    enum class Level {
		TRACE = 0,
		DEBUG = 1,
		INFO = 2,
		WARN = 3,
		ERROR = 4,
		CRITI = 5,
		OFF = 6,
	};
    static Level GetOutLevelEnum(const std::string& strLevel);

public:
    Logger();
    ~Logger();

    bool AddColorConsole(const char* pLoggerName, const Level level = Level::TRACE);

    bool AddRotatingFile(const char* pLoggerName, const char* pFileName, const Level level = Level::TRACE, 
                            const int nMaxFileSize = 1024 * 1024 * 10, const int nMaxFile = 10);

    bool AddDailyFile(const char* pLoggerName, const char* pFileName, const int nHour, const int nMinute, const Level level = Level::TRACE);

    bool Init(const std::string strLogFormat = LOG_OUTPUT_FORMAT);
    void DeInit();

private:
	std::vector<std::string> StringSplit(const std::string& strSrc, const std::string& strSplit);
    void UpdateSinkMap(std::string strLoggerName, spdlog::sink_ptr pSink);
    void UpdateThreadPoolMap(std::string strLoggerName, std::shared_ptr<spdlog::details::thread_pool> pThreadPool);

private:
    bool init_;
    std::map<std::string, std::vector<spdlog::sink_ptr>> logger_sinks_map_; 
    std::map<std::string, std::shared_ptr<spdlog::details::thread_pool>> async_threadpool_map_;
};

using Logger_s = singleton<Logger>;

} // namespace sinfer