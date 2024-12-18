#include "LogMng.hpp"

std::vector<std::filesystem::path> getLogFileList(std::filesystem::path logDirPath)
{
	std::vector<std::filesystem::path>logList;

	std::filesystem::directory_iterator logs(logDirPath);
	for (const std::filesystem::directory_entry& l : logs)
	{
		if (l.is_regular_file())
		{
			if (l.path().extension().string() == LOGGER_LOG_FILE_TYPE)
			{
				logList.push_back(l.path());
			}
		}
	}

	return logList;
}

void sortLogFileList(std::vector<std::filesystem::path> &logFileList, bool newestFirst)
{
	if (!logFileList.empty())
	{
		bool swap = false;
		size_t i = 0;
		size_t min_index = 0;
		LogFileDateTime tmpLogDt;
		std::filesystem::path tmpLog;
		std::vector<LogFileDateTime> logDtArr;
		std::vector<std::filesystem::path> logPaths;

		// Create an vector of log date time to make an fast analysis of the comparisons:
		while (i < logFileList.size())
		{
			LogFileDateTime logDt(logFileList[i]);

			if (logDt.isLogDtOk())
			{
				logDtArr.push_back(logDt);
				logPaths.push_back(logFileList[i]);
			}

			i++;
		}

		for (i = 0; i < logPaths.size() - 1; i++)
		{
			swap = false;
			min_index = i;

			for (size_t j = i + 1; j < logPaths.size(); j++)
			{
				if ((newestFirst && logDtArr[i] < logDtArr[j]) || (!newestFirst && logDtArr[i] > logDtArr[j]))
				{
					min_index = j;
					swap = true;
				}
			}

			// Swap when found the last write time difference:
			if (swap)
			{
				tmpLog = logPaths[i];
				tmpLogDt = logDtArr[i];
				logPaths[i] = logPaths[min_index];
				logDtArr[i] = logDtArr[min_index];
				logPaths[min_index] = tmpLog;
				logDtArr[min_index] = tmpLogDt;
			}
		}

		logFileList = logPaths;
	}
}

void sortLogFileList2(std::vector<std::filesystem::path> &logFileList, bool newestFirst)
{
	/**
	 * Try to mitigate the sorting fail with std::chrono::duration,
	 * between current time_point and file_time_type time_point.
	 * The difference should be a duration object, representing the
	 * age of the file.
	 */

	if (!logFileList.empty())
	{
		bool swap = false;
		size_t min_index = 0;
		std::filesystem::path tmpLog;
		std::filesystem::file_time_type refLogTime;
		std::filesystem::file_time_type logTime;

		std::chrono::nanoseconds refLogTime_ns;
		std::chrono::nanoseconds logTime_ns;

		std::chrono::time_point now = std::chrono::system_clock::now();

		for (size_t i = 0; i < logFileList.size() - 1; i++)
		{
			swap = false;
			min_index = i;
			refLogTime = std::filesystem::last_write_time(logFileList[i]);
			refLogTime_ns = now - std::chrono::clock_cast<std::chrono::system_clock, std::chrono::file_clock>(refLogTime);

			for (size_t j = i + 1; j < logFileList.size(); j++)
			{
				logTime = std::filesystem::last_write_time(logFileList[j]);
				logTime_ns = now - std::chrono::clock_cast<std::chrono::system_clock, std::chrono::file_clock>(logTime);

				/*
				 * If the refLog is older than actual log obj and newer was set
				 * OR
				 * When the refLog is newer than actual log and newestFirst was not set
				 * mark to swap the objects:
				*/
				if ((newestFirst && refLogTime_ns > logTime_ns) || (!newestFirst && refLogTime_ns < logTime_ns))
				{
					min_index = j;
					swap = true;
				}
			}

			// Swap when found the last write time difference:
			if (swap)
			{
				tmpLog = logFileList[i];
				logFileList[i] = logFileList[min_index];
				logFileList[min_index] = tmpLog;
			}
		}
	}
}

int cleanOldLogFiles(std::vector<std::filesystem::path>& logList, unsigned int keepLastNFiles)
{
	if (keepLastNFiles == 0)
	{
		keepLastNFiles = 1;		// If no log was settled to keep, force it to 1, to make sure the last generated log available
	}

	if (logList.empty())
	{
		return -1;
	}

	try
	{
		if (logList.size() > keepLastNFiles)
		{
			int removedLogs = 0;
			#pragma warning (suppress : 4267)
			long logs2Rem = logList.size() - keepLastNFiles;

			for (size_t i = 0; i < logs2Rem; i++)
			{
				if (std::filesystem::remove(logList[i]))
				{
					removedLogs++;
				}
			}

			return removedLogs;		// Return the number of files removed
		}

		return -2;					// Not enough files
	}
	catch (const std::exception&)
	{
		return -3;					// An exception occurred
	}
}

