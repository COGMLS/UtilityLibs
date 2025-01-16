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
#include <filesystem>
#include <algorithm>
#include <ostream>
#include <ctime>

#ifdef _WIN32
	#include <timezoneapi.h>
	#include <sysinfoapi.h>
	#include <minwinbase.h>
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

/**
 * @brief Log file date time information.
 * @details This class is used to mitigate the OS date time interpretation from LAST TIME WRITE or FILE TIME CREATION and use the log file name, that contains the date and time log report with ISO 8601 format (YYYY-MM-dd hh-mm-ss)
 * @note The LogFileDateTime is only used for created log files and for sort the log file list, to mitigate the missing order on Unix systems.
 * @note The LogFileDateTime class can hold the LAST TIME WRITE instead to hold the date and time information present on file's name. This is not the standard behavior.
 */
class LOGGER_LIB_API LogFileDateTime
{
	private:

		int day = -1;
		int month = -1;
		int year = -1;
		int hour = -1;
		int minute = -1;
		int second = -1;
		bool isDateTimeOk = false;

		/**
		 * @brief Get the Log date and time information from file's name, following the LoggerLib naming convention: <LogName>_<Date>T<Time>.log
		 * @param filename File name. If the extension was passed on file's name, it will be removed.
		 * @return Return the same value of isDateTimeOk private variable. If true, the date and time informations are ready to be used.
		 */
		bool getLogDtFromFilename (std::string filename);

		/**
		 * @brief Get the log date and time information from filesystem date and time. This method allows to added DateTime checks with files that does not use LoggerLib naming convention: <LogName>_<Date>T<Time>.log
		 * @param filepath File path
		 * @param useTimezoneCorrection Use timezone correction to local time. This resolves the missing time precision with file's name, when using Logger naming convention.
		 */
		void getLogDtFromFileDateTime (std::filesystem::path filepath, bool useTimezoneCorrection);

	public:

		/// @brief Create an empty log file date time
		LogFileDateTime();

		/**
		 * @brief Create an log file date time information object with an string with the file's name
		 * @param fileName File name string formatted with LoggerLib naming convention: <FileName>_YYYY-MM-ddThh-mm-ss.log
		 * @note If the filename contains the file's extension, the constructor will remove it before start the name analysis.
		 */
		LogFileDateTime (std::string fileName);

		/**
		 * @brief Create an log file date time information object using the file's path
		 * @param filepath Path to the an log file created with the LoggerLib or respecting the file name format: <FileName>_YYYY-MM-ddThh-mm-ss
		 * @param useFileDateTime Use the file date and time information instead the date time in file's name. Note: This parameter allows to use in other logs that does not match with LoggerLib convention naming.
		 * @param useTimezoneCorrection Use the Timezone offset correction from file date time information to resolve the time precision loss when comparing with file's name information. Note: This parameter only has effect when useFileDateTime is true.
		 */
		LogFileDateTime (std::filesystem::path filepath, bool useFileDateTime = false, bool useTimezoneCorrection = true);

		LogFileDateTime (const LogFileDateTime& other);
		LogFileDateTime (LogFileDateTime&& other) noexcept;

		~LogFileDateTime();

		/// @brief Check if the log file date time is correct
		bool isLogDtOk();

		/**
		 * @brief Export the date and time information as a literal ULL value. Similar to C++ version preprocessor definition
		 * @note This method was designed to test the class and object interactions.
		 */
		unsigned long long getLiteralUllDt();

		friend std::ostream& operator<<(std::ostream& os, const LogFileDateTime& logDt);

		LogFileDateTime& operator=(const LogFileDateTime& other);
		LogFileDateTime& operator=(LogFileDateTime&& other) noexcept;

		bool operator==(const LogFileDateTime& other);
		bool operator!=(const LogFileDateTime& other);

		bool operator<(const LogFileDateTime& other);
		bool operator<=(const LogFileDateTime& other);
		bool operator>(const LogFileDateTime& other);
		bool operator>=(const LogFileDateTime& other);
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