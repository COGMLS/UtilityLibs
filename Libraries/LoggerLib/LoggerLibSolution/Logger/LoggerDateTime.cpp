#include "pch.h"
#include "LoggerDateTime.hpp"

LoggerLocalDateTime getLoggerDateTime()
{
	LoggerLocalDateTime dt{};

	const std::chrono::time_point now{ std::chrono::system_clock::now() };

	dt.calendar = std::chrono::year_month_day(std::chrono::floor<std::chrono::days>(now));
	dt.weekday = std::chrono::weekday(dt.calendar._Calculate_weekday());

	#ifdef _WIN32
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		
		//dt.weekday = std::chrono::weekday(tm.wDayOfWeek);
		dt.hours = std::chrono::hours(tm.wHour);
		dt.minutes = std::chrono::minutes(tm.wMinute);
		dt.seconds = std::chrono::seconds(tm.wSecond);
		dt.mSeconds = std::chrono::milliseconds(tm.wMilliseconds);
	#else
		const std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::tm* tm = std::localtime(&t);
	
		dt.weekday = std::chrono::weekday(tm->tm_wday);
		dt.hours = std::chrono::hours(tm->tm_hour);
		dt.minutes = std::chrono::minutes(tm->tm_min);
		dt.seconds = std::chrono::seconds(tm->tm_sec);
		dt.mSeconds = std::chrono::milliseconds(0);
	#endif

	return dt;
}

std::string convertDateTime2LogStrEntry(LoggerLocalDateTime& dt, bool exportsToFileSystem, bool useHighPrecisionTime)
{
	std::string logDateTimeEntry;

	logDateTimeEntry = std::to_string((int)dt.calendar.year()) + "-";

	if ((unsigned int)dt.calendar.month() < 10)
	{
		logDateTimeEntry += '0';
	}

	logDateTimeEntry += std::to_string((unsigned int)dt.calendar.month()) + "-";

	if ((unsigned int)dt.calendar.day() < 10)
	{
		logDateTimeEntry += '0';
	}

	logDateTimeEntry += std::to_string((unsigned int)dt.calendar.day()) + "T";


	if (dt.hours.count() < 10)
	{
		logDateTimeEntry += '0';
	}

	logDateTimeEntry += std::to_string(dt.hours.count());

	if (exportsToFileSystem)
	{
		logDateTimeEntry += "-";
	}
	else
	{
		logDateTimeEntry += ":";
	}

	if (dt.minutes.count() < 10)
	{
		logDateTimeEntry += '0';
	}

	logDateTimeEntry += std::to_string(dt.minutes.count());

	if (exportsToFileSystem)
	{
		logDateTimeEntry += "-";
	}
	else
	{
		logDateTimeEntry += ":";
	}

	if (dt.seconds.count() < 10)
	{
		logDateTimeEntry += '0';
	}

	logDateTimeEntry += std::to_string(dt.seconds.count());

	if (useHighPrecisionTime)
	{
		if (exportsToFileSystem)
		{
			logDateTimeEntry += "-";
		}
		else
		{
			logDateTimeEntry += ":";
		}

		long long mSeconds = dt.mSeconds.count();

		if (mSeconds < 10)
		{
			logDateTimeEntry += "00";
		}
		else if (mSeconds < 100)
		{
			logDateTimeEntry += "0";
		}
		
		logDateTimeEntry += std::to_string(mSeconds);
	}

	return logDateTimeEntry;
}
