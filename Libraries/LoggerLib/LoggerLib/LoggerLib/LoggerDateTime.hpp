#pragma once

#ifndef LOGGER_DATE_TIME_HPP
#define LOGGER_DATE_TIME_HPP

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

#ifdef WIN32
#include "pch.h"
#endif // !WIN32

#include <chrono>

#ifdef _WIN32
	#include <timezoneapi.h>
	#include <sysinfoapi.h>
	#include <minwinbase.h>
#else
	#include <ctime>
#endif

/// @brief Logger local date time for log entries
struct LOGGER_LIB_API LoggerLocalDateTime
{
	std::chrono::year_month_day calendar;
	std::chrono::weekday weekday;
	std::chrono::hours hours;
	std::chrono::minutes minutes;
	std::chrono::seconds seconds;
	std::chrono::milliseconds mSeconds;
};

/// @brief Get all date and time data for log entries
/// @return Return a LoggerLocalDateTime struct to use in conditions tests and log reports
LoggerLocalDateTime LOGGER_LIB_API getLoggerDateTime();

/// @brief Convert the custom local date and time struct to string for log entries, using ISO 8601 format
/// @param dt Date and time information that will be converted to ISO 8601
/// @param exportsToFileSystem Convert the date and time format not using signal ':'
/// @param useHighPrecision Use milliseconds in the time conversion
/// @return Converted date and time information
std::string LOGGER_LIB_API convertDateTime2LogStrEntry(LoggerLocalDateTime& dt, bool exportsToFileSystem = false, bool useHighPrecisionTime = false);

/// @brief Convert the custom local date and time struct to string for log entries, using ISO 8601 format
/// @param dt Date and time information that will be converted to ISO 8601
/// @param exportsToFileSystem Convert the date and time format not using signal ':'
/// @param useHighPrecision Use milliseconds in the time conversion
/// @return Converted date and time information
std::wstring LOGGER_LIB_API convertDateTime2LogStrEntryW(LoggerLocalDateTime& dt, bool exportsToFileSystem = false, bool useHighPrecisionTime = false);

#endif // !LOGGER_DATE_TIME_HPP