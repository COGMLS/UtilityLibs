#pragma once

#ifndef LOGGER_DATE_TIME_HPP
#define LOGGER_DATE_TIME_HPP

#include "pch.h"

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

#endif // !LOGGER_DATE_TIME_HPP