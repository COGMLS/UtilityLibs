#pragma once

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "pch.h"

#include <string>
#include <fstream>
#include <vector>
#include <filesystem>
#include <chrono>

#include "LoggerCommonDataTypes.hpp"
#include "LoggerDateTime.hpp"

enum LOGGER_LIB_API LoggerError : unsigned int
{
	LOGGER_ERROR_OK,
	LOGGER_ERROR_PATH_DONT_EXIST,
	LOGGER_ERROR_BASE_FILE_NAME_HAS_UNSUPPORTED_CHAR,
	LOGGER_ERROR_CAN_NOT_CREATE_FILE,
	LOGGER_ERROR_FILE_CAN_NOT_BE_FOUNDED,
	LOGGER_ERROR_SAVE_LOG_ENTRIES_OK,
	LOGGER_ERROR_SAVE_LOG_ENTRIES_FAIL,
	LOGGER_ERROR_AUTOSAVE_LOG_ENTRIES_OK,
	LOGGER_ERROR_AUTOSAVE_LOG_ENTRIES_FAIL,
	LOGGER_ERROR_AUTOSAVE_LOG_ENTRIES_FULL,
	LOGGER_ERROR_AUTOSAVE_LOG_ENTRIES_NOT_FULL
};

class LOGGER_LIB_API Logger
{
	private:
		std::filesystem::path logPath;			// Log folder
		std::string baseFileName;				// Log file base name
		std::filesystem::path logFilePath;		// Log file path
		std::vector<LogEntry> logEntries;		// Log entries
		unsigned int lastLogStatus;				// Last log error code registered
		std::vector<LoggerError>logStatus;		// History of all error codes inside the Logger object
		LoggerLocalDateTime dtCreation;			// Log date and time creation
		size_t maxLogEntries;					// Define a maximum size for logEntries
		bool autoSaveLogEntries;				// Define if true and the maxLogEntries is bigger than 0, the auto save will automatically save the entries to the file
		int lastLogPos;							// Last log position, used for locate the last position when using maxLogEntries and autoSaveLogEntries

		/// @brief Set the logger error code status. This also add to the error list, except when is LOGGER_ERROR_OK.
		/// @param errCode Logger error code 
		void setLogStatus(LoggerError errCode);

		/// @brief Write the log entries on the disk
		bool writeLogFile(bool ateMode);

		/// @brief Save automatically the entries and clean the stored entries in memory
		LoggerError autoSave();

	public:
		/// @brief Create a logger register
		/// @param logPath Path where the log will be saved
		/// @param baseFileName Base name for create the log file, the rest of name will be used the date and time of creation
		Logger(std::filesystem::path logPath, std::string baseFileName);

		/// @brief Copy a logger to another
		/// @param other Other logger data reference
		Logger(const Logger& other);

		/// @brief Move a logger to another
		/// @param other Other logger data that will receive the reference data
		Logger(Logger&& other) noexcept;

		/// @brief Copy assignment
		/// @param other Other logger reference data
		Logger& operator=(const Logger& other);

		/// @brief Move assignment
		/// @param other Other logger reference data
		Logger& operator=(Logger&& other) noexcept;

		/// @brief Equality operator
		/// @param other Other logger reference data
		/// @return True if is the same memory reference for all data, otherwise will be a False value
		bool operator==(const Logger& other) const;

		/// @brief Destroy the logger object and save the entries
		~Logger();

		/// @brief Get the log folder path
		std::filesystem::path getLogDirectoryPath();

		/// @brief Get the actual log file path 
		std::filesystem::path getLogFilePath();

		/// @brief Get the log date and time creation
		LoggerLocalDateTime getLogDateTime();

		/// @brief Add a new entry for the logger
		void newEntry(LogEntry entry);

		/// @brief Save the log to a file
		int saveLog();

		/// @brief Define the autosave enabled or disabled and define if the logger will hold a limit of entries on the memory before save then on files
		/// @param autoSave Define if the auto save will be used. By default the auto save is disabled.
		/// @param maxLogEntries Define the maximum entries will be stored in memory. By default the value is 0, to keep all entries in memory. This feature is only used when auto save is enabled.
		void setAutoSave(bool autoSave, size_t maxLogEntries = 0);
};

#endif // !LOGGER_HPP