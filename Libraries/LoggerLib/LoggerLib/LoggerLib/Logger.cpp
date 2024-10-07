#include "Logger.hpp"

Logger::Logger(std::filesystem::path logPath, std::string baseFileName)
{
	this->autoSaveLogEntries = false;
	this->maxLogEntries = 0;
	this->lastLogPos = 0;

	this->setLogStatus(LoggerError::LOGGER_ERROR_OK);

	if (std::filesystem::exists(logPath))
	{
		this->logPath = logPath;
	}
	else
	{
		if (std::filesystem::create_directory(logPath))
		{
			this->logPath = logPath;
		}
		else
		{
			this->setLogStatus(LoggerError::LOGGER_ERROR_PATH_DONT_EXIST);
		}
	}

	bool baseFileNameOk = true;

	// Search for invalid chars for file's name
	for (size_t i = 0; i < baseFileName.size(); i++)
	{
		if (baseFileNameOk)
		{
			switch (baseFileName[i])
			{
				case '\\':
				case '/':
				case ':':
				case '*':
				case '?':
				case '"':
				case '<':
				case '>':
					this->setLogStatus(LoggerError::LOGGER_ERROR_BASE_FILE_NAME_HAS_UNSUPPORTED_CHAR);
					baseFileNameOk = false;
					break;
				default:
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}

	if (this->lastLogStatus == LoggerError::LOGGER_ERROR_OK && this->logStatus.size() == 0)
	{
		this->dtCreation = getLoggerDateTime();

		this->baseFileName = baseFileName + "_" + convertDateTime2LogStrEntry(dtCreation, true);

		this->logFilePath = std::filesystem::path(this->logPath.string() + LOGGER_DIRECTORY_PATH_SEPARATOR + this->baseFileName + LOGGER_LOG_FILE_TYPE);

		// Create the file and make it ready to be used for write:

		std::fstream logFile;
		#ifdef WIN32
		logFile.open(logFilePath.string(), std::ios::out);
		#else
		logFile.open(logFilePath, std::ios_base::out);
		#endif // !WIN32

		//this->logFile.open(logFilePath.string(), std::ios::out);

		if (!logFile.is_open())
		{
			this->setLogStatus(LoggerError::LOGGER_ERROR_CAN_NOT_CREATE_FILE);
		}
		else
		{
			logFile.close();
		}

		if (!std::filesystem::exists(this->logFilePath))
		{
			this->setLogStatus(LoggerError::LOGGER_ERROR_FILE_CAN_NOT_BE_FOUNDED);
		}
	}
}

Logger::Logger(const Logger& other)
{
	this->baseFileName = other.baseFileName;
	this->lastLogStatus = other.lastLogStatus;
	this->logEntries = other.logEntries;
	//this->logFile = other.logFile;
	this->logFilePath = other.logFilePath;
	this->logPath = other.logPath;
	this->logStatus = other.logStatus;
	this->dtCreation = other.dtCreation;
	this->autoSaveLogEntries = other.autoSaveLogEntries;
	this->maxLogEntries = other.maxLogEntries;
	this->lastLogPos = other.lastLogPos;
}

Logger::Logger(Logger&& other) noexcept
{
	this->baseFileName = std::move(other.baseFileName);
	this->lastLogStatus = std::move(other.lastLogStatus);
	this->logEntries = std::move(other.logEntries);
	//this->logFile = std::move(other.logFile);
	this->logFilePath = std::move(other.logFilePath);
	this->logPath = std::move(other.logPath);
	this->logStatus = std::move(other.logStatus);
	this->dtCreation = std::move(other.dtCreation);
	this->autoSaveLogEntries = std::move(other.autoSaveLogEntries);
	this->maxLogEntries = std::move(other.maxLogEntries);
	this->lastLogPos = std::move(other.lastLogPos);
}

Logger& Logger::operator=(const Logger& other)
{
	this->baseFileName = other.baseFileName;
	this->lastLogStatus = other.lastLogStatus;
	this->logEntries = other.logEntries;
	//this->logFile = other.logFile;
	this->logFilePath = other.logFilePath;
	this->logPath = other.logPath;
	this->logStatus = other.logStatus;
	this->dtCreation = other.dtCreation;
	this->autoSaveLogEntries = other.autoSaveLogEntries;
	this->maxLogEntries = other.maxLogEntries;
	this->lastLogPos = other.lastLogPos;

	return *this;
}

Logger& Logger::operator=(Logger&& other) noexcept
{
	this->baseFileName = std::move(other.baseFileName);
	this->lastLogStatus = std::move(other.lastLogStatus);
	this->logEntries = std::move(other.logEntries);
	//this->logFile = std::move(other.logFile);
	this->logFilePath = std::move(other.logFilePath);
	this->logPath = std::move(other.logPath);
	this->logStatus = std::move(other.logStatus);
	this->dtCreation = std::move(other.dtCreation);
	this->autoSaveLogEntries = std::move(other.autoSaveLogEntries);
	this->maxLogEntries = std::move(other.maxLogEntries);
	this->lastLogPos = std::move(other.lastLogPos);

	other.~Logger();

	return *this;
}

bool Logger::operator==(const Logger& other) const
{
	return this->baseFileName == other.baseFileName &&
			this->lastLogStatus == other.lastLogStatus &&
			this->logEntries == other.logEntries &&
			this->logFilePath == other.logFilePath &&
			this->logPath == other.logPath &&
			this->logStatus == other.logStatus &&
			this->dtCreation.calendar == other.dtCreation.calendar &&
			this->dtCreation.hours == other.dtCreation.hours &&
			this->dtCreation.minutes == other.dtCreation.minutes &&
			this->dtCreation.mSeconds == other.dtCreation.mSeconds &&
			this->dtCreation.seconds == other.dtCreation.seconds &&
			this->dtCreation.weekday == other.dtCreation.weekday &&
			this->autoSaveLogEntries == other.autoSaveLogEntries &&
			this->maxLogEntries == other.maxLogEntries &&
			this->lastLogPos == other.lastLogPos;
}

int Logger::saveLog()
{
	if (this->autoSaveLogEntries)
	{
		if (this->writeLogFile(true))
		{
			this->setLogStatus(LoggerError::LOGGER_ERROR_SAVE_LOG_ENTRIES_OK);
			return 0;
		}
		else
		{
			this->setLogStatus(LoggerError::LOGGER_ERROR_SAVE_LOG_ENTRIES_FAIL);
			return 1;
		}
	}
	else
	{
		if (this->writeLogFile(false))
		{
			this->setLogStatus(LoggerError::LOGGER_ERROR_SAVE_LOG_ENTRIES_OK);
			return 0;
		}
		else
		{
			this->setLogStatus(LoggerError::LOGGER_ERROR_SAVE_LOG_ENTRIES_FAIL);
			return 1;
		}
	}
}

Logger::~Logger()
{

}

std::filesystem::path Logger::getLogDirectoryPath()
{
	return this->logPath;
}

std::filesystem::path Logger::getLogFilePath()
{
	return this->logFilePath;
}

LoggerLocalDateTime Logger::getLogDateTime()
{
	return this->dtCreation;
}

bool Logger::writeLogFile(bool ateMode)
{
	try
	{
		bool isLogFileCreated = true;

		for (LoggerError& errCode : this->logStatus)
		{
			if (errCode == LoggerError::LOGGER_ERROR_CAN_NOT_CREATE_FILE || errCode == LoggerError::LOGGER_ERROR_FILE_CAN_NOT_BE_FOUNDED)
			{
				isLogFileCreated = false;
			}
		}

		if (isLogFileCreated)
		{
			std::fstream logFile;

			if (ateMode)
			{
				#ifdef WIN32
				logFile.open(this->logFilePath.string(), std::ios::out | std::ios::in);
				#else
				logFile.open(this->logFilePath, std::ios_base::out | std::ios_base::in);
				#endif // !WIN32
			}
			else
			{
				#ifdef WIN32
				logFile.open(this->logFilePath.string(), std::ios::out);
				#else
				logFile.open(this->logFilePath, std::ios_base::out);
				#endif // !WIN32
			}

			// Set the last position to write the log, if the maxLogEntries and autoSaveLogEntries are defined
			if (this->maxLogEntries > 0 && this->autoSaveLogEntries)
			{
				int g = 0;

				std::string line;
				while (std::getline(logFile, line))
				{
					#ifdef _MSC_VER
					#pragma warning (suppress : 4244)
					#endif // !_MSC_VER
					g = logFile.tellg();
				}

				if (g >= 0)
				{
					this->lastLogPos = g;
				}

				// Set to clear the flags and define a new position for writing and reading
				if (logFile.tellg() != 0 || logFile.tellg() != 0)
				{
					logFile.clear();
					logFile.seekg(this->lastLogPos);
					logFile.seekp(this->lastLogPos);
				}
			}

			// If the log file was created with success, save the entries
			if (isLogFileCreated)
			{
				for (LogEntry& entry : this->logEntries)
				{
					logFile << entry.getEntry() << std::endl;
				}
			}

			if (isLogFileCreated)
			{
				if (logFile.is_open())
				{
					logFile.close();
				}
			}

			return true;
		}

		return false;
	}
	catch (const std::exception& e)
	{
		this->logEntries.push_back(LogEntry("[EXCEPTION]::", e.what()));
		return false;
	}
}

void Logger::setLogStatus(LoggerError errCode)
{
	this->lastLogStatus = errCode;

	if (errCode != LoggerError::LOGGER_ERROR_OK)
	{
		this->logStatus.push_back(errCode);
	}
}

LoggerError Logger::autoSave()
{
	if (this->maxLogEntries > 0)
	{
		if (this->logEntries.size() >= this->maxLogEntries)
		{
			this->setLogStatus(LoggerError::LOGGER_ERROR_AUTOSAVE_LOG_ENTRIES_FULL);

			bool logStatus = this->writeLogFile(true);

			this->logEntries.clear();

			if (logStatus)
			{
				return LoggerError::LOGGER_ERROR_AUTOSAVE_LOG_ENTRIES_OK;
			}
			else
			{
				return LoggerError::LOGGER_ERROR_AUTOSAVE_LOG_ENTRIES_FAIL;
			}
		}

		return LoggerError::LOGGER_ERROR_AUTOSAVE_LOG_ENTRIES_NOT_FULL;
	}
	else
	{
		if (this->saveLog() == 0)
		{
			return LoggerError::LOGGER_ERROR_AUTOSAVE_LOG_ENTRIES_OK;
		}
		
		return LoggerError::LOGGER_ERROR_AUTOSAVE_LOG_ENTRIES_FAIL;
	}
}

void Logger::newEntry(LogEntry entry)
{
	if (this->autoSaveLogEntries)
	{
		this->setLogStatus(this->autoSave());
	}

	this->logEntries.push_back(entry);
}

void Logger::setAutoSave(bool autoSave, size_t maxLogEntries)
{
	this->autoSaveLogEntries = autoSave;
	this->maxLogEntries = maxLogEntries;
}

LoggerW::LoggerW(std::filesystem::path logPath, std::wstring baseFileName)
{
	this->autoSaveLogEntries = false;
	this->maxLogEntries = 0;
	this->lastLogPos = 0;

	this->setLogStatus(LoggerError::LOGGER_ERROR_OK);

	if (std::filesystem::exists(logPath))
	{
		this->logPath = logPath;
	}
	else
	{
		if (std::filesystem::create_directory(logPath))
		{
			this->logPath = logPath;
		}
		else
		{
			this->setLogStatus(LoggerError::LOGGER_ERROR_PATH_DONT_EXIST);
		}
	}

	bool baseFileNameOk = true;

	// Search for invalid chars for file's name
	for (size_t i = 0; i < baseFileName.size(); i++)
	{
		if (baseFileNameOk)
		{
			switch (baseFileName[i])
			{
				case L'\\':
				case L'/':
				case L':':
				case L'*':
				case L'?':
				case L'"':
				case L'<':
				case L'>':
					this->setLogStatus(LoggerError::LOGGER_ERROR_BASE_FILE_NAME_HAS_UNSUPPORTED_CHAR);
					baseFileNameOk = false;
					break;
				default:
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}

	if (this->lastLogStatus == LoggerError::LOGGER_ERROR_OK && this->logStatus.size() == 0)
	{
		this->dtCreation = getLoggerDateTime();

		this->baseFileName = baseFileName + L"_" + convertDateTime2LogStrEntryW(dtCreation, true);

		this->logFilePath = std::filesystem::path(this->logPath.wstring() + LOGGER_DIRECTORY_PATH_SEPARATOR_W + this->baseFileName + LOGGER_LOG_FILE_TYPE_W);

		// Create the file and make it ready to be used for write:

		std::wfstream logFile;
		#ifdef WIN32
		logFile.open(logFilePath.wstring(), std::ios::out);
		#else
		logFile.open(logFilePath, std::ios_base::out);
		#endif // !WIN32

		//this->logFile.open(logFilePath.wstring(), std::ios::out);

		if (!logFile.is_open())
		{
			this->setLogStatus(LoggerError::LOGGER_ERROR_CAN_NOT_CREATE_FILE);
		}
		else
		{
			logFile.close();
		}

		if (!std::filesystem::exists(this->logFilePath))
		{
			this->setLogStatus(LoggerError::LOGGER_ERROR_FILE_CAN_NOT_BE_FOUNDED);
		}
	}
}

LoggerW::LoggerW(const LoggerW& other)
{
	this->baseFileName = other.baseFileName;
	this->lastLogStatus = other.lastLogStatus;
	this->logEntries = other.logEntries;
	//this->logFile = other.logFile;
	this->logFilePath = other.logFilePath;
	this->logPath = other.logPath;
	this->logStatus = other.logStatus;
	this->dtCreation = other.dtCreation;
	this->autoSaveLogEntries = other.autoSaveLogEntries;
	this->maxLogEntries = other.maxLogEntries;
	this->lastLogPos = other.lastLogPos;
}

LoggerW::LoggerW(LoggerW&& other) noexcept
{
	this->baseFileName = std::move(other.baseFileName);
	this->lastLogStatus = std::move(other.lastLogStatus);
	this->logEntries = std::move(other.logEntries);
	//this->logFile = std::move(other.logFile);
	this->logFilePath = std::move(other.logFilePath);
	this->logPath = std::move(other.logPath);
	this->logStatus = std::move(other.logStatus);
	this->dtCreation = std::move(other.dtCreation);
	this->autoSaveLogEntries = std::move(other.autoSaveLogEntries);
	this->maxLogEntries = std::move(other.maxLogEntries);
	this->lastLogPos = std::move(other.lastLogPos);
}

LoggerW& LoggerW::operator=(const LoggerW& other)
{
	this->baseFileName = other.baseFileName;
	this->lastLogStatus = other.lastLogStatus;
	this->logEntries = other.logEntries;
	//this->logFile = other.logFile;
	this->logFilePath = other.logFilePath;
	this->logPath = other.logPath;
	this->logStatus = other.logStatus;
	this->dtCreation = other.dtCreation;
	this->autoSaveLogEntries = other.autoSaveLogEntries;
	this->maxLogEntries = other.maxLogEntries;
	this->lastLogPos = other.lastLogPos;

	return *this;
}

LoggerW& LoggerW::operator=(LoggerW&& other) noexcept
{
	this->baseFileName = std::move(other.baseFileName);
	this->lastLogStatus = std::move(other.lastLogStatus);
	this->logEntries = std::move(other.logEntries);
	//this->logFile = std::move(other.logFile);
	this->logFilePath = std::move(other.logFilePath);
	this->logPath = std::move(other.logPath);
	this->logStatus = std::move(other.logStatus);
	this->dtCreation = std::move(other.dtCreation);
	this->autoSaveLogEntries = std::move(other.autoSaveLogEntries);
	this->maxLogEntries = std::move(other.maxLogEntries);
	this->lastLogPos = std::move(other.lastLogPos);

	other.~LoggerW();

	return *this;
}

bool LoggerW::operator==(const LoggerW& other) const
{
	return this->baseFileName == other.baseFileName &&
			this->lastLogStatus == other.lastLogStatus &&
			this->logEntries == other.logEntries &&
			this->logFilePath == other.logFilePath &&
			this->logPath == other.logPath &&
			this->logStatus == other.logStatus &&
			this->dtCreation.calendar == other.dtCreation.calendar &&
			this->dtCreation.hours == other.dtCreation.hours &&
			this->dtCreation.minutes == other.dtCreation.minutes &&
			this->dtCreation.mSeconds == other.dtCreation.mSeconds &&
			this->dtCreation.seconds == other.dtCreation.seconds &&
			this->dtCreation.weekday == other.dtCreation.weekday &&
			this->autoSaveLogEntries == other.autoSaveLogEntries &&
			this->maxLogEntries == other.maxLogEntries &&
			this->lastLogPos == other.lastLogPos;
}

int LoggerW::saveLog()
{
	if (this->autoSaveLogEntries)
	{
		if (this->writeLogFile(true))
		{
			this->setLogStatus(LoggerError::LOGGER_ERROR_SAVE_LOG_ENTRIES_OK);
			return 0;
		}
		else
		{
			this->setLogStatus(LoggerError::LOGGER_ERROR_SAVE_LOG_ENTRIES_FAIL);
			return 1;
		}
	}
	else
	{
		if (this->writeLogFile(false))
		{
			this->setLogStatus(LoggerError::LOGGER_ERROR_SAVE_LOG_ENTRIES_OK);
			return 0;
		}
		else
		{
			this->setLogStatus(LoggerError::LOGGER_ERROR_SAVE_LOG_ENTRIES_FAIL);
			return 1;
		}
	}
}

LoggerW::~LoggerW()
{

}

std::filesystem::path LoggerW::getLogDirectoryPath()
{
	return this->logPath;
}

std::filesystem::path LoggerW::getLogFilePath()
{
	return this->logFilePath;
}

LoggerLocalDateTime LoggerW::getLogDateTime()
{
	return this->dtCreation;
}

bool LoggerW::writeLogFile(bool ateMode)
{
	try
	{
		bool isLogFileCreated = true;

		for (LoggerError& errCode : this->logStatus)
		{
			if (errCode == LoggerError::LOGGER_ERROR_CAN_NOT_CREATE_FILE || errCode == LoggerError::LOGGER_ERROR_FILE_CAN_NOT_BE_FOUNDED)
			{
				isLogFileCreated = false;
			}
		}

		if (isLogFileCreated)
		{
			std::wfstream logFile;

			if (ateMode)
			{
				#ifdef WIN32
				logFile.open(this->logFilePath.wstring(), std::ios::out | std::ios::in);
				#else
				logFile.open(this->logFilePath, std::ios_base::out | std::ios_base::in);
				#endif // !WIN32
			}
			else
			{
				#ifdef WIN32
				logFile.open(this->logFilePath.wstring(), std::ios::out);
				#else
				logFile.open(this->logFilePath, std::ios_base::out);
				#endif // !WIN32
			}

			// Set the last position to write the log, if the maxLogEntries and autoSaveLogEntries are defined
			if (this->maxLogEntries > 0 && this->autoSaveLogEntries)
			{
				int g = 0;

				std::wstring line;
				while (std::getline(logFile, line))
				{
					#ifdef _MSC_VER
					#pragma warning (suppress : 4244)
					#endif // !_MSC_VER
					g = logFile.tellg();
				}

				if (g >= 0)
				{
					this->lastLogPos = g;
				}

				// Set to clear the flags and define a new position for writing and reading
				if (logFile.tellg() != 0 || logFile.tellg() != 0)
				{
					logFile.clear();
					logFile.seekg(this->lastLogPos);
					logFile.seekp(this->lastLogPos);
				}
			}

			// If the log file was created with success, save the entries
			if (isLogFileCreated)
			{
				for (LogEntryW& entry : this->logEntries)
				{
					logFile << entry.getEntry() << std::endl;
				}
			}

			if (isLogFileCreated)
			{
				if (logFile.is_open())
				{
					logFile.close();
				}
			}

			return true;
		}

		return false;
	}
	catch (const std::exception& e)
	{
		//this->logEntries.push_back(LogEntry(L"[EXCEPTION]::", e.what()));
		return false;
	}
}

void LoggerW::setLogStatus(LoggerError errCode)
{
	this->lastLogStatus = errCode;

	if (errCode != LoggerError::LOGGER_ERROR_OK)
	{
		this->logStatus.push_back(errCode);
	}
}

LoggerError LoggerW::autoSave()
{
	if (this->maxLogEntries > 0)
	{
		if (this->logEntries.size() >= this->maxLogEntries)
		{
			this->setLogStatus(LoggerError::LOGGER_ERROR_AUTOSAVE_LOG_ENTRIES_FULL);

			bool logStatus = this->writeLogFile(true);

			this->logEntries.clear();

			if (logStatus)
			{
				return LoggerError::LOGGER_ERROR_AUTOSAVE_LOG_ENTRIES_OK;
			}
			else
			{
				return LoggerError::LOGGER_ERROR_AUTOSAVE_LOG_ENTRIES_FAIL;
			}
		}

		return LoggerError::LOGGER_ERROR_AUTOSAVE_LOG_ENTRIES_NOT_FULL;
	}
	else
	{
		if (this->saveLog() == 0)
		{
			return LoggerError::LOGGER_ERROR_AUTOSAVE_LOG_ENTRIES_OK;
		}
		
		return LoggerError::LOGGER_ERROR_AUTOSAVE_LOG_ENTRIES_FAIL;
	}
}

void LoggerW::newEntry(LogEntryW entry)
{
	if (this->autoSaveLogEntries)
	{
		this->setLogStatus(this->autoSave());
	}

	this->logEntries.push_back(entry);
}

void LoggerW::setAutoSave(bool autoSave, size_t maxLogEntries)
{
	this->autoSaveLogEntries = autoSave;
	this->maxLogEntries = maxLogEntries;
}