#pragma once

#ifndef LOGGER_COMMON_DATATYPES_HPP
#define LOGGER_COMMON_DATATYPES_HPP

#include "pch.h"

#include <chrono>
#include <ostream>
#include <string>

#include "LoggerDateTime.hpp"

#define LOGGER_LOG_FILE_TYPE								".log"

#ifdef _WIN32
	#define LOGGER_CONFIG_LINE_END							'\r\n'
	#define LOGGER_DIRECTORY_PATH_SEPARATOR					"\\"
	#define LOGGER_DIRECTORY_PATH_SEPARATOR_W				L"\\"
#else
	#define LOGGER_CONFIG_LINE_END							'\n'
	#define LOGGER_DIRECTORY_PATH_SEPARATOR					"/"
	#define LOGGER_DIRECTORY_PATH_SEPARATOR_W				L"/"
#endif

/// @brief Log entry type
enum LOGGER_LIB_API LogDataType
{
	LOG_NULL_DATA_ENTRY,
	LOG_INTEGER_ENTRY,
	LOG_FLOAT_ENTRY,
	LOG_STRING_ENTRY,					// Deprecated value. Union string pointer was removed.
	LOG_DATE_TIME_ENTRY,
	LOG_DATE_TIME_HIGH_PRECISION_ENTRY
};

/// @brief Log entry data
union LogEntryData
{
	long long LOG_ENTRY_INT;
	double LOG_ENTRY_FLOAT;
	bool LOG_ENTRY_STRING;
	LoggerLocalDateTime LOG_ENTRY_DATE_TIME;
};

/// @brief Log entry data
class LOGGER_LIB_API LogEntry
{
	private:
		std::string title;			// Log title
		std::string message;		// Log message
		LogEntryData data;			// Log data
		LogDataType dataType;		// Log data type id
		std::string strData;		// Log additional string data
	public:
		/// @brief Create a log entry
		/// @param title Log entry title
		/// @param message Log entry message
		LogEntry(std::string title, std::string message);

		/// @brief Create a log entry with additional data
		/// @param title Log entry title
		/// @param message Log entry message
		/// @param data Log entry data
		LogEntry(std::string title, std::string message, long long data);

		/// @brief Create a log entry with additional data
		/// @param title Log entry title
		/// @param message Log entry message
		/// @param data Log entry data
		LogEntry(std::string title, std::string message, double data);

		/// @brief Create a log entry with additional data
		/// @param title Log entry title
		/// @param message Log entry message
		/// @param data Log entry data
		LogEntry(std::string title, std::string message, std::string data);
		
		/// @brief Create a log entry with additional data
		/// @param title Log entry title
		/// @param message Log entry message
		/// @param data Log entry data
		/// @param useHighPrecisionTime Use milliseconds to date time log entry
		LogEntry(std::string title, std::string message, LoggerLocalDateTime data, bool useHighPrecisionTime = false);

		/// @brief Copy a log entry to another
		/// @param other Other log entry data reference
		LogEntry(const LogEntry& other);

		/// @brief Move a log entry to another
		/// @param other Other log entry data that will receive the reference data
		LogEntry(LogEntry&& other) noexcept;

		/// @brief Copy assignment
		/// @param other Other log entry reference data
		LogEntry& operator=(const LogEntry& other);

		/// @brief Move assignment
		/// @param other Other log entry reference data
		LogEntry& operator=(LogEntry&& other) noexcept;

		/// @brief Equality operator
		/// @param other Other log entry reference data
		/// @return True if is the same memory reference for all data, otherwise will be a False value
		bool operator==(const LogEntry& other) const;

		~LogEntry();

		/// @brief Export the log entry as a string
		/// @return 
		std::string getEntry();

		friend std::ostream& operator<<(std::ostream& os, const LogEntry& obj);
};

#endif // !LOGGER_COMMON_DATATYPES_HPP