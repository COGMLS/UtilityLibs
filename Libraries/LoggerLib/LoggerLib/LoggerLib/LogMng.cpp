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

		#ifdef LOGGER_ENABLE_EXPERIMENTAL_LOGGER_BUBBLE_SORT_1
		for (size_t i = 0; i < logFileList.size() - 1; i++)
		{
			swap = false;
			for (size_t j = 0; j < logFileList.size() - i - 1; j++)
			{
				if ((newestFirst && logDtArr[j] < logDtArr[j + 1]) || (!newestFirst && logDtArr[j] > logDtArr[j + 1]))
				{
					std::swap<std::filesystem::path>(logPaths[j], logPaths[j + 1]);
					std::swap<LogFileDateTime>(logDtArr[j], logDtArr[j + 1]);
					swap = true;
				}
			}

			if (!swap)
			{
				break;
			}
		}
		#else
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
				std::swap<std::filesystem::path>(logPaths[i], logPaths[min_index]);
				std::swap<LogFileDateTime>(logDtArr[i], logDtArr[min_index]);
			}
		}
		#endif // !LOGGER_ENABLE_EXPERIMENTAL_LOGGER_BUBBLE_SORT_1

		logFileList = logPaths;
	}
}

void sortLogFileList2(std::vector<std::filesystem::path> &logFileList, bool newestFirst)
{
	if (!logFileList.empty())
	{
		bool swap = false;
		size_t min_index = 0;
		std::filesystem::file_time_type refLogTime;
		std::filesystem::file_time_type logTime;

		std::chrono::nanoseconds refLogTime_ns;
		std::chrono::nanoseconds logTime_ns;

		std::chrono::time_point now = std::chrono::utc_clock::now();

		#ifdef LOGGER_ENABLE_EXPERIMENTAL_LOGGER_BUBBLE_SORT_2
		for (size_t i = 0; i < logFileList.size() - 1; i++)
		{
			swap = false;

			refLogTime = std::filesystem::last_write_time(logFileList[i]);

			for (size_t j = 0; j < logFileList.size() - i - 1; j++)
			{
				logTime = std::filesystem::last_write_time(logFileList[j]);

				if ((newestFirst && refLogTime > logTime) || (!newestFirst && refLogTime < logTime))
				{
					std::swap(logFileList[j], logFileList[j + 1]);
					swap = true;
				}
			}

			if (!swap)
			{
				break;
			}
		}
		#else
		for (size_t i = 0; i < logFileList.size() - 1; i++)
		{
			swap = false;
			min_index = i;
			refLogTime = std::filesystem::last_write_time(logFileList[i]);
			refLogTime_ns = now - std::chrono::clock_cast<std::chrono::utc_clock, std::chrono::file_clock>(refLogTime);

			for (size_t j = i + 1; j < logFileList.size(); j++)
			{
				logTime = std::filesystem::last_write_time(logFileList[j]);
				logTime_ns = now - std::chrono::clock_cast<std::chrono::utc_clock, std::chrono::file_clock>(logTime);

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
				std::swap(logFileList[i], logFileList[min_index]);
			}
		}
		#endif // !LOGGER_ENABLE_EXPERIMENTAL_LOGGER_BUBBLE_SORT_2
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

