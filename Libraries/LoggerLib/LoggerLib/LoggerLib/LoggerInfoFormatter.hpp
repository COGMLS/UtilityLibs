#pragma once

#ifndef LOGGER_INFORMATION_FORMATTER_HPP
#define LOGGER_INFORMATION_FORMATTER_HPP

#ifdef WIN32
	#ifdef LOGGER_EXPORTS
		#define LOGGER_LIB_API __declspec(dllexport)
	#else
		#define LOGGER_LIB_API __declspec(dllimport)
	#endif //!LOGGER_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#else
	#if __GNUC__ >= 4
		#ifdef LOGGER_EXPORTS
			#define LOGGER_LIB_API __attribute__((visibility("default")))
		#else
			#define LOGGER_LIB_API __attribute__((visibility("default")))
		#endif //!LOGGER_EXPORTS
	#else
		#ifdef LOGGER_EXPORTS
			#define LOGGER_LIB_API
		#else
			#define LOGGER_LIB_API
		#endif //!LOGGER_EXPORTS
	#endif
#endif // !WIN32

#include "LoggerExperimental.hpp"

#ifdef WIN32
#include "pch.h"
#endif // !WIN32

#include <string>
#include <vector>
#include <filesystem>
#include <chrono>
#include <ostream>
#include <array>

#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_FORMATTER
#include "LoggerException.hpp"
#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_FORMATTER

enum LogFormatId : unsigned int
{
	RawStr,						// If a raw string content was found, identify as RawStr
	Unknown,					// If an unknown identify was send, like "%w", identify as Unknown id
	Title,						// Title id (%t)
	Message,					// Message id (%m)
	Data						// Data id (%d)
	//DateTime,					// Reserved
	//Date,						// Reserved
	//Time,						// Reserved
	//HighPrecisionDateTime,	// Reserved
	//HighPrecisionTime			// Reserved
};

const std::array<const char*, 3> LogFormatIdStr = 
{
	"t",
	"m",
	"d"
};

/**
 * @brief Log format information token
 */
class LOGGER_LIB_API LogFormatToken
{
	private:

		LogFormatId id;
		std::string info;

	public:

		/**
		 * @brief Create an empty format token, marked as Unknown id and empty information.
		 */
		LogFormatToken ();

		/**
		 * @brief Create a format token with specific ID and information
		 * @param id Token ID
		 * @param info Token information
		 */
		LogFormatToken (LogFormatId id, std::string info);

		LogFormatToken (const LogFormatToken& other);

		LogFormatToken (LogFormatToken&& other) noexcept;

		~LogFormatToken();

		LogFormatToken& operator= (const LogFormatToken& other);

		LogFormatToken& operator= (LogFormatToken&& other) noexcept;

		std::string operator+ (const LogFormatToken& other);

		std::string operator+ (const std::string& str);

		LogFormatId getId();

		std::string getInfo();
};

class LOGGER_LIB_API LogFormat
{
	private:

		//LogDataType formatType;					// Identify which type this format should be used, raw data, date and time, etc.
		std::string emptyReplacer;					// If a id is empty, use an generic information to generate a proper output
		std::vector<LogFormatToken> formatTokens;	// Format tokens: The tokens are defined by each type of id located in the given format. Unidentified tokens will be considered as a part of raw string output for log generation.

		void createFormat (std::string& format);

	public:

		/**
		 * @brief Create an empty log format information object
		 */
		LogFormat();

		/**
		 * @brief Create a log formatter object that holds how the log data will be wrote in the log file
		 * @param format Format information text. Check the notes to more information.
		 * @param emptyDataReplacer String information to replace any empty data that was identified
		 * @note Format information: %t to identify the title. %m Identify the message. %d to identify the log data.
		 * @note Adding other marks like '::', will be skiped to format id and used as part of custom information format
		 */
		LogFormat (std::string formatStr, std::string emptyDataReplacer = "");

		LogFormat (const LogFormat& other);

		LogFormat (LogFormat&& other) noexcept;

		~LogFormat();

		LogFormat& operator= (const LogFormat& other);

		LogFormat& operator= (LogFormat&& other) noexcept;

		std::string formatInfo (std::vector<std::string> info);
};

#endif // !LOGGER_INFORMATION_FORMATTER_HPP