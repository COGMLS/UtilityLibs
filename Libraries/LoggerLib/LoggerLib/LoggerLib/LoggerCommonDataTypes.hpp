#pragma once

#ifndef LOGGER_COMMON_DATATYPES_HPP
#define LOGGER_COMMON_DATATYPES_HPP

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

#include <chrono>
#include <ostream>
#include <string>

#include "LoggerDateTime.hpp"

#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
#include "LogDataStore.hpp"
#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE

#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_FORMATTER
#include "LoggerInfoFormatter.hpp"
#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_FORMATTER

#ifdef LOGGER_ENABLE_EXPERIMENTAL_CUSTOM_EXCEPTIONS
#include "LoggerException.hpp"
#endif // !LOGGER_ENABLE_EXPERIMENTAL_CUSTOM_EXCEPTIONS

#define LOGGER_LOG_FILE_TYPE								".log"
#define LOGGER_LOG_FILE_TYPE_W								L".log"

#ifdef _WIN32
	#define LOGGER_CONFIG_LINE_END							'\r\n'
	#define LOGGER_CONFIG_LINE_END_W						L'\r\n'
	#define LOGGER_DIRECTORY_PATH_SEPARATOR					"\\"
	#define LOGGER_DIRECTORY_PATH_SEPARATOR_W				L"\\"
#else
	#define LOGGER_CONFIG_LINE_END							'\n'
	#define LOGGER_CONFIG_LINE_END_W						L'\r\n'
	#define LOGGER_DIRECTORY_PATH_SEPARATOR					"/"
	#define LOGGER_DIRECTORY_PATH_SEPARATOR_W				L"/"
#endif

#ifndef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
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
#endif

/// @brief Log entry data
class LOGGER_LIB_API LogEntry
{
	private:
		std::string title;			// Log title
		std::string message;		// Log message

		#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
		LogDataStore data;			// Log data. It can contain additional message or other datatypes like bool, int, float, date and time, etc.
		#else
		LogEntryData data;			// Log data
		LogDataType dataType;		// Log data type id
		std::string strData;		// Log additional string data
		#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
		
		#ifdef LOGGER_ENABLE_EXPERIMENTAL_LOGENTRY_DT_REG
		LoggerLocalDateTime dtReg;	// Log date and time entry register.
		#endif // !LOGGER_ENABLE_EXPERIMENTAL_LOGENTRY_DT_REG
	public:
		/// @brief Create a log entry
		/// @param title Log entry title
		/// @param message Log entry message
		LogEntry (std::string title, std::string message);

		/// @brief Create a log entry with additional data
		/// @param title Log entry title
		/// @param message Log entry message
		/// @param data Log entry data
		LogEntry (std::string title, std::string message, long long data);

		/// @brief Create a log entry with additional data
		/// @param title Log entry title
		/// @param message Log entry message
		/// @param data Log entry data
		LogEntry (std::string title, std::string message, double data);

		/// @brief Create a log entry with additional data
		/// @param title Log entry title
		/// @param message Log entry message
		/// @param data Log entry data
		LogEntry (std::string title, std::string message, std::string data);
		
		/// @brief Create a log entry with additional data
		/// @param title Log entry title
		/// @param message Log entry message
		/// @param data Log entry data
		/// @param useHighPrecisionTime Use milliseconds to date time log entry
		LogEntry (std::string title, std::string message, LoggerLocalDateTime data, bool useHighPrecisionTime = false);

		/// @brief Copy a log entry to another
		/// @param other Other log entry data reference
		LogEntry (const LogEntry& other);

		/// @brief Move a log entry to another
		/// @param other Other log entry data that will receive the reference data
		LogEntry (LogEntry&& other) noexcept;

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

		/// @brief Get the log entry title
		std::string getTitle();

		/// @brief Get the log entry message
		std::string getMessage();

		/// @brief Get the type of data this entry holds.
		LogDataType getType();

		#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
		/// @brief Get the LogDataStore available in this entry.
		/// @note If no data store is available, an empty data store will be returned
		LogDataStore getData();
		#else
		/// @brief Get the log entry data union
		/// @note If the entry does not hold a valid union, all values will set as zero.
		LogEntryData getData();

		/// @brief Get the additional string data the entry can hold.
		/// @note If no additional string was set, an empty string will be returned.
		std::string getStrData();
		#endif // LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE

		/// @brief Export the log entry as a string
		/// @return 
		std::string getEntry();

		friend std::ostream& operator<<(std::ostream& os, const LogEntry& obj);
};

/// @brief Log entry data
class LOGGER_LIB_API LogEntryW
{
	private:
		std::wstring title;			// Log title
		std::wstring message;		// Log message

		#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
		LogDataStore data;			// Log data. It can contain additional message or other datatypes like bool, int, float, date and time, etc.
		#else
		LogEntryData data;			// Log data
		LogDataType dataType;		// Log data type id
		std::wstring strData;		// Log additional string data
		#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
		
		#ifdef LOGGER_ENABLE_EXPERIMENTAL_LOGENTRY_DT_REG
		LoggerLocalDateTime dtReg;	// Log date and time entry register.
		#endif // !LOGGER_ENABLE_EXPERIMENTAL_LOGENTRY_DT_REG
	public:
		/// @brief Create a log entry
		/// @param title Log entry title
		/// @param message Log entry message
		LogEntryW (std::wstring title, std::wstring message);

		/// @brief Create a log entry with additional data
		/// @param title Log entry title
		/// @param message Log entry message
		/// @param data Log entry data
		LogEntryW (std::wstring title, std::wstring message, long long data);

		/// @brief Create a log entry with additional data
		/// @param title Log entry title
		/// @param message Log entry message
		/// @param data Log entry data
		LogEntryW (std::wstring title, std::wstring message, double data);

		/// @brief Create a log entry with additional data
		/// @param title Log entry title
		/// @param message Log entry message
		/// @param data Log entry data
		LogEntryW (std::wstring title, std::wstring message, std::wstring data);
		
		/// @brief Create a log entry with additional data
		/// @param title Log entry title
		/// @param message Log entry message
		/// @param data Log entry data
		/// @param useHighPrecisionTime Use milliseconds to date time log entry
		LogEntryW (std::wstring title, std::wstring message, LoggerLocalDateTime data, bool useHighPrecisionTime = false);

		/// @brief Copy a log entry to another
		/// @param other Other log entry data reference
		LogEntryW (const LogEntryW& other);

		/// @brief Move a log entry to another
		/// @param other Other log entry data that will receive the reference data
		LogEntryW (LogEntryW&& other) noexcept;

		/// @brief Copy assignment
		/// @param other Other log entry reference data
		LogEntryW& operator=(const LogEntryW& other);

		/// @brief Move assignment
		/// @param other Other log entry reference data
		LogEntryW& operator=(LogEntryW&& other) noexcept;

		/// @brief Equality operator
		/// @param other Other log entry reference data
		/// @return True if is the same memory reference for all data, otherwise will be a False value
		bool operator==(const LogEntryW& other) const;

		~LogEntryW();

		/// @brief Get the log entry title
		std::wstring getTitle();

		/// @brief Get the log entry message
		std::wstring getMessage();

		/// @brief Get the type of data this entry holds.
		LogDataType getType();

		#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
		/// @brief Get the LogDataStore available in this entry.
		/// @note If no data store is available, an empty data store will be returned
		LogDataStore getData();
		#else
		/// @brief Get the log entry data union
		/// @note If the entry does not hold a valid union, all values will set as zero.
		LogEntryData getData();

		/// @brief Get the additional string data the entry can hold.
		/// @note If no additional string was set, an empty string will be returned.
		std::wstring getStrData();
		#endif // LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE

		/// @brief Export the log entry as a string
		/// @return 
		std::wstring getEntry();

		friend std::wostream& operator<<(std::wostream& os, const LogEntryW& obj);
};

#endif // !LOGGER_COMMON_DATATYPES_HPP