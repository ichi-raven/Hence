/*****************************************************************//**
 * @file   Logger.cpp
 * @brief  Loggerクラスの実装
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#include "../../include/Utility/Logger.hpp"

#include <cassert>
#include <iostream>

namespace Hence
{
	// コンソール文字色変更コード
	constexpr const char* kConsoleColorReset	= "\x1b[0m";
	constexpr const char* kConsoleColorBlack	= "\x1b[30m";
	constexpr const char* kConsoleColorRed		= "\x1b[31m";
	constexpr const char* kConsoleColorGreen	= "\x1b[32m";
	constexpr const char* kConsoleColorYellow	= "\x1b[33m";
	constexpr const char* kConsoleColorBlue		= "\x1b[34m";
	constexpr const char* kConsoleColorMagenta	= "\x1b[35m";
	constexpr const char* kConsoleColorCyan		= "\x1b[36m";
	constexpr const char* kConsoleColorWhite	= "\x1b[37m";

	Logger::Logger()
	{
		mFStream.open("log.txt");

		assert(mFStream || "failed to open log file!");
	}

	Logger::~Logger()
	{
		mFStream.close();
	}

	Logger& Logger::getInstance() noexcept
	{
		static Logger instance;

		return instance;
	}

	bool Logger::setOutputFile(std::string_view path) noexcept
	{
		auto& fs = getInstance().mFStream;
		fs.close();
		fs.open(path.data());
		
		return !!fs;
	}

	void Logger::logInfo(std::string_view message)
	{
		std::lock_guard<std::mutex> lock(this->mMutex);

		mFStream << kConsoleColorCyan << "[info] : " << message << "\n" << kConsoleColorReset;
		std::cerr << kConsoleColorCyan << "[info] : " << message << "\n" << kConsoleColorReset;
	}

	void Logger::logWarn(std::string_view message)
	{
		std::lock_guard<std::mutex> lock(this->mMutex);

		mFStream << kConsoleColorYellow << "[warning] : " << message << "\n" << kConsoleColorReset;
		std::cerr << kConsoleColorYellow << "[warning] : " << message << "\n" << kConsoleColorReset;
	}

	void Logger::logError(std::string_view message)
	{
		std::lock_guard<std::mutex> lock(this->mMutex);

		mFStream << kConsoleColorRed << "[error] : " << message << "\n" << kConsoleColorReset;
		std::cerr << kConsoleColorRed << "[error] : " << message << "\n" << kConsoleColorReset;
	}
}
