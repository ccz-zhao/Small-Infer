#include "utils/logger.h"

namespace sinfer {

Logger::Level Logger::GetOutLevelEnum(const std::string& strLevel) {
    Level eLevel;

	if (strLevel == "TRACE")
	{
		eLevel = Level::TRACE;
	}
	else if (strLevel == "DEBUG")
	{
		eLevel = Level::DEBUG;
	}
	else if (strLevel == "INFO")
	{
		eLevel = Level::INFO;
	}
	else if (strLevel == "WARN")
	{
		eLevel = Level::WARN;
	}
	else if (strLevel == "ERROR")
	{
		eLevel = Level::ERROR;
	}
	else if (strLevel == "CRITI")
	{
		eLevel = Level::CRITI;
	}
	else
	{
		eLevel =  Level::TRACE;
	}

	return eLevel;
}

Logger::Logger()
    : init_(false)
{	
	this->AddColorConsole("console");
	this->AddRotatingFile("rotating_file", "./logs/log.log");
    if (!this->Init()) {
		printf("[Log] Logger init fail!");
	}
}


Logger::~Logger()
{
    if (init_) {
        this->DeInit();
    }
	
}


bool Logger::AddColorConsole(const char* pLoggerName, const Level level)
{
	printf("[log]: AddColorConsole, logName=%s  level=%d  \n", pLoggerName, static_cast<int>(level));
	auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	console_sink->set_level((spdlog::level::level_enum)level);
	//console_sink->set_pattern(LOG_OUTPUT_FORMAT);
	UpdateSinkMap(pLoggerName, console_sink);
	return true;
}

bool Logger::AddRotatingFile(const char* pLoggerName, const char* pFileName, const Level level, const int nMaxFileSize, const int nMaxFile)
{
	printf("[log]: AddRotatingFile, logName=%s  level=%d  fileName=%s  maxFileSize=%d  maxFile=%d \n", pLoggerName, level, pFileName, nMaxFileSize, nMaxFile);
	auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(pFileName, nMaxFileSize, nMaxFile);
	file_sink->set_level((spdlog::level::level_enum)level);
	//file_sink->set_pattern(LOG_OUTPUT_FORMAT);
	UpdateSinkMap(pLoggerName, file_sink);
	return true;
}

bool Logger::AddDailyFile(const char* pLoggerName, const char* pFileName, const int nHour, const int nMinute, const Level eLevel)
{ 
	//"%Y-%m-%d:%H:%M:%S.log"
	auto DailyFileSink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(pFileName, nHour, nMinute);
	DailyFileSink->set_level((spdlog::level::level_enum)eLevel);
	UpdateSinkMap(pLoggerName, DailyFileSink);
	return true;
}

void Logger::UpdateSinkMap(std::string strLoggerName, spdlog::sink_ptr pSink)
{
	auto iter = logger_sinks_map_.find(strLoggerName);
	if (iter != logger_sinks_map_.end())
	{
		iter->second.push_back(pSink);
	}
	else
	{
		std::vector<spdlog::sink_ptr> vecSink;
		vecSink.push_back(pSink);
		logger_sinks_map_[strLoggerName] = vecSink;
	}
}

void Logger::UpdateThreadPoolMap(std::string strLoggerName, std::shared_ptr<spdlog::details::thread_pool> pThreadPool)
{
	auto iter = async_threadpool_map_.find(strLoggerName);
	if (iter != async_threadpool_map_.end())
	{
		iter->second = (pThreadPool);
	}
	else
	{
		async_threadpool_map_[strLoggerName] = pThreadPool;
	}
}

bool Logger::Init(const std::string strLogFormat) {
	if (init_) {
		printf("It's already initialized\n");
		return false;
	}
	init_ = true;
	printf("[log]: mode=ASYNC \n");
	for (auto e : logger_sinks_map_)
	{
		std::string strLogName = e.first;
		std::vector<spdlog::sink_ptr> vecSink(e.second);
		auto tp = std::make_shared<spdlog::details::thread_pool>(1024, 1);
		auto logger = std::make_shared<spdlog::async_logger>(strLogName, begin(vecSink), end(vecSink), tp, spdlog::async_overflow_policy::block);
		UpdateThreadPoolMap(strLogName, tp);
		//设置根日志输出等级
		logger->set_level(spdlog::level::trace);
		//遇到warn级别，立即flush到文件
		logger->flush_on(spdlog::level::warn);
		spdlog::register_logger(logger);
	}
	//定时flush到文件，每三秒刷新一次
	spdlog::flush_every(std::chrono::seconds(3));
	//设置全局记录器的输出格式
	spdlog::set_pattern(strLogFormat);
	return true;
}

void Logger::DeInit()
{
	spdlog::drop_all();
	spdlog::shutdown();
	init_ = false;
}

}   // namespace sinfer