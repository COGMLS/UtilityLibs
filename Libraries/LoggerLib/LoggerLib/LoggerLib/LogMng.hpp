/***************************************************************
 * This header provide the tools to manage the log files
 * and keep the Smart Auto Run organized and avoid unnecessary
 * space used for to many log files.
***************************************************************/

#pragma once

#ifndef LOG_MANAGER_HPP
#define LOG_MANAGER_HPP

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

#include <filesystem>
#include <string>
#include <vector>

#include "LoggerCommonDataTypes.hpp"

#define LOGGER_LIB_MNG_MAXLOGFILES 30				// Default maximum log files to keep

/// @brief Get the log file list from a directory
/// @param logDirPath Log directory
/// @return List of log files
std::vector<std::filesystem::path> LOGGER_LIB_API getLogFileList(std::filesystem::path logDirPath);

/// @brief Clean the old log files inside the log list
/// @param logList Log list from a directory
/// @param keepLastNFiles Number of logs that will stay inside the directory. NOTE: If defined to 0, it will be replaced to 1, to make sure the last generated log is preserved
/// @return A positive number represents the number of removed files
/// @return -1 means the logList is empty
/// @return -2 when the log list don't have enough files to remove
/// @return -3 an exception occurred
int LOGGER_LIB_API cleanOldLogFiles(std::vector<std::filesystem::path>& logList, unsigned int keepLastNFiles);

#endif // !LOG_MANAGER_HPP