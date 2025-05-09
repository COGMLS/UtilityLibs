#include "LoggerDateTime.hpp"

LoggerLocalDateTime getLoggerDateTime(bool useHighPrecision, bool utcTime)
{
	LoggerLocalDateTime dt{};

	const std::chrono::time_point now{ std::chrono::system_clock::now() };

	dt.calendar = std::chrono::year_month_day(std::chrono::floor<std::chrono::days>(now));

	#ifdef _WIN32
		SYSTEMTIME tm;
		
		#ifdef LOGGER_ENABLE_EXPERIMENTAL_UTC_AND_LOCAL_DT
		if (utcTime)
		{
			GetSystemTime(&tm);
		}
		else
		{
			GetLocalTime(&tm);
		}
		#else
		GetLocalTime(&tm);
		#endif // !LOGGER_ENABLE_EXPERIMENTAL_UTC_AND_LOCAL_DT
		
		dt.weekday = std::chrono::weekday(static_cast<unsigned short>(tm.wDayOfWeek));
		dt.hours = std::chrono::hours(tm.wHour);
		dt.minutes = std::chrono::minutes(tm.wMinute);
		dt.seconds = std::chrono::seconds(tm.wSecond);
		if (useHighPrecision)
		{
			dt.mSeconds = std::chrono::milliseconds(tm.wMilliseconds);
			dt.highPrecision = true;
		}
		else
		{
			dt.mSeconds = std::chrono::milliseconds(0);
			dt.highPrecision = false;
		}
	#else
		std::chrono::system_clock::time_point localDt = std::chrono::system_clock::now();

		#ifdef LOGGER_ENABLE_EXPERIMENTAL_UTC_AND_LOCAL_DT
		// On Unix systems the system_clock is in UTC time:
		if (!utcTime)
		{
			// Calculate the local datetime using timezone information:
			std::chrono::seconds tz_offset = std::chrono::zoned_time(std::chrono::current_zone()).get_info().offset;
			localDt = localDt + tz_offset;	// Overwrite the original date time file information with the timezone correction
		}
		#endif // !LOGGER_ENABLE_EXPERIMENTAL_UTC_AND_LOCAL_DT

		const std::time_t t = std::chrono::system_clock::to_time_t(localDt);
		std::tm* tm = std::localtime(&t);
	
		dt.weekday = std::chrono::weekday(tm->tm_wday);
		dt.hours = std::chrono::hours(tm->tm_hour);
		dt.minutes = std::chrono::minutes(tm->tm_min);
		dt.seconds = std::chrono::seconds(tm->tm_sec);

		#ifdef LOGGER_ENABLE_EXPERIMENTAL_ALL_PLATFORMS_HIGH_PRECISION_TIME
		if (useHighPrecision)
		{
			std::chrono::hh_mm_ss dayTime = std::chrono::hh_mm_ss(localDt - std::chrono::floor<std::chrono::days>(localDt));
			std::chrono::milliseconds ms = std::chrono::floor<std::chrono::milliseconds>(dayTime.subseconds());
			dt.mSeconds = ms;
			dt.highPrecision = true;
		}
		else
		{
			dt.mSeconds = std::chrono::milliseconds(0);
			dt.highPrecision = false;
		}
		#else
		dt.mSeconds = std::chrono::milliseconds(0);
		dt.highPrecision = false;
		#endif // !LOGGER_ENABLE_EXPERIMENTAL_ALL_PLATFORMS_HIGH_PRECISION_TIME
	#endif

	dt.utcTime = utcTime;

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

std::wstring convertDateTime2LogStrEntryW(LoggerLocalDateTime& dt, bool exportsToFileSystem, bool useHighPrecisionTime)
{
	std::wstring logDateTimeEntry;

	logDateTimeEntry = std::to_wstring((int)dt.calendar.year()) + L"-";

	if ((unsigned int)dt.calendar.month() < 10)
	{
		logDateTimeEntry += L'0';
	}

	logDateTimeEntry += std::to_wstring((unsigned int)dt.calendar.month()) + L"-";

	if ((unsigned int)dt.calendar.day() < 10)
	{
		logDateTimeEntry += L'0';
	}

	logDateTimeEntry += std::to_wstring((unsigned int)dt.calendar.day()) + L"T";


	if (dt.hours.count() < 10)
	{
		logDateTimeEntry += L'0';
	}

	logDateTimeEntry += std::to_wstring(dt.hours.count());

	if (exportsToFileSystem)
	{
		logDateTimeEntry += L"-";
	}
	else
	{
		logDateTimeEntry += L":";
	}

	if (dt.minutes.count() < 10)
	{
		logDateTimeEntry += L'0';
	}

	logDateTimeEntry += std::to_wstring(dt.minutes.count());

	if (exportsToFileSystem)
	{
		logDateTimeEntry += L"-";
	}
	else
	{
		logDateTimeEntry += L":";
	}

	if (dt.seconds.count() < 10)
	{
		logDateTimeEntry += L'0';
	}

	logDateTimeEntry += std::to_wstring(dt.seconds.count());

	if (useHighPrecisionTime)
	{
		if (exportsToFileSystem)
		{
			logDateTimeEntry += L"-";
		}
		else
		{
			logDateTimeEntry += L":";
		}

		long long mSeconds = dt.mSeconds.count();

		if (mSeconds < 10)
		{
			logDateTimeEntry += L"00";
		}
		else if (mSeconds < 100)
		{
			logDateTimeEntry += L"0";
		}
		
		logDateTimeEntry += std::to_wstring(mSeconds);
	}

	return logDateTimeEntry;
}

bool LogFileDateTime::getLogDtFromFilename(std::string filename)
{
	// 0 - Second, 1 - Minute, 2 - hour, 3 - day, 4 - month, 5 - year
	short j = 0;
	char c = '\0';
	int k = -1;
	std::string tmp;
	for (size_t i = filename.size() - 1; i >= 0; i--)
	{
		if (filename[i] >= '0' && filename[i] <= '9')
		{
			tmp += filename[i];
		}

		if (filename[i] == 'T' || filename[i] == 't' || filename[i] == '-' || filename[i] == '_')
		{
			if (!tmp.empty())
			{
				std::reverse(tmp.begin(), tmp.end());
			}

			try
			{
				k = std::stoi(tmp);

				if (j == 0)
				{
					this->second = k;
				}

				if (j == 1)
				{
					this->minute = k;
				}

				if (j == 2)
				{
					this->hour = k;
				}

				if (j == 3)
				{
					this->day = k;
				}

				if (j == 4)
				{
					this->month = k;
				}

				if (j == 5)
				{
					this->year = k;
				}
			}
			catch(const std::exception&)
			{

			}

			j++;
			k = -1;
			tmp.clear();
		}

		if (filename[i] == '_')
		{
			break;
		}
	}

	if (this->day >= 0 && this->month >= 0 && this->year >= 0 && this->hour >= 0 && this->minute >= 0 && this->second >= 0)
	{
		this->isDateTimeOk = true;
	}

	return this->isDateTimeOk;	// Return the date time status. This will be used in future modifications for this class
}

void LogFileDateTime::getLogDtFromFileDateTime(std::filesystem::path filepath, bool useTimezoneCorrection)
{
	std::chrono::system_clock::time_point dt = std::chrono::clock_cast<std::chrono::system_clock, std::chrono::file_clock>(std::filesystem::last_write_time(filepath));

	if (useTimezoneCorrection)
	{
		std::chrono::seconds tz_offset = std::chrono::zoned_time(std::chrono::current_zone()).get_info().offset;
		dt = dt + tz_offset;	// Overwrite the original date time file information with the timezone correction
	}

	time_t cTimet = std::chrono::system_clock::to_time_t(dt);
	tm cTime = *std::localtime(&cTimet);	// Use localtime to use system local time

	this->year = cTime.tm_year + 1900;	// On ctime, year is counted year - 1900.
	this->month = cTime.tm_mon + 1;		// On C style, January starts with 0. Adding 1 will match with traditional calendar.
	this->day = cTime.tm_mday;
	this->hour = cTime.tm_hour;
	this->minute = cTime.tm_min;
	this->second = cTime.tm_sec;

	if (
			std::chrono::year_month_day{
				std::chrono::year(this->year), 
				std::chrono::month(this->month), 
				std::chrono::day{static_cast<unsigned int>(this->day)}}.ok() &&
			this->hour >= 0 && this->hour < 24 &&
			this->minute >= 0 && this->minute < 60 &&
			this->second >= 0 && this->second < 60
		)
	{
		this->isDateTimeOk = true;
	}
}

LogFileDateTime::LogFileDateTime()
{
}

LogFileDateTime::LogFileDateTime(std::string filename)
{
	/** Look for the extension dot mark:
	 * -------------------------------------
	 * The Logger Library export the log files
	 * using the format <LogName>_<Date>T<Time>.log
	 * The algorithm in getLogDtFromFilename
	 * is design to only look for the date time
	 * information. The extension (including
	 * the dot), must be removed first.
	*/
	if (!filename.empty())
	{
		std::string filename_noExt = "";
		size_t i = filename.size() - 1;

		for (i; i >= 0; i--)
		{
			if (filename[i] == '.')
			{
				i--;
				break;
			}
		}

		if (i > 0)
		{
			filename_noExt = filename.substr(0, i + 1);
			this->getLogDtFromFilename(filename_noExt);
		}
	}
}

LogFileDateTime::LogFileDateTime(std::filesystem::path filepath, bool useFileDateTime, bool useTimezoneCorrection)
{
	if (std::filesystem::exists(filepath))
	{
		if (std::filesystem::is_regular_file(filepath))
		{
			if (useFileDateTime)
			{
				this->getLogDtFromFileDateTime(filepath, useTimezoneCorrection);
			}
			else
			{
				this->getLogDtFromFilename(filepath.stem().string());
			}
		}
	}
}

LogFileDateTime::LogFileDateTime(const LogFileDateTime &other)
{
	this->year = other.year;
	this->month = other.month;
	this->day = other.day;
	this->hour = other.hour;
	this->minute = other.minute;
	this->second = other.second;
	this->isDateTimeOk = other.isDateTimeOk;
}

LogFileDateTime::LogFileDateTime(LogFileDateTime &&other) noexcept
{
	this->year = std::move(other.year);
	this->month = std::move(other.month);
	this->day = std::move(other.day);
	this->hour = std::move(other.hour);
	this->minute = std::move(other.minute);
	this->second = std::move(other.second);
	this->isDateTimeOk = std::move(other.isDateTimeOk);
}

LogFileDateTime::~LogFileDateTime()
{
}

bool LogFileDateTime::isLogDtOk()
{
    return this->isDateTimeOk;
}

unsigned long long LogFileDateTime::getLiteralUllDt()
{
	std::string dt = "";
	
	if (this->isDateTimeOk)
	{
		dt = std::to_string(this->year) + std::to_string(this->month) + std::to_string(this->day) + std::to_string(this->hour) + std::to_string(this->minute) + std::to_string(this->second);
		return std::stoull(dt);
	}

    return 0;
}

LogFileDateTime &LogFileDateTime::operator=(const LogFileDateTime &other)
{
    this->year = other.year;
	this->month = other.month;
	this->day = other.day;
	this->hour = other.hour;
	this->minute = other.minute;
	this->second = other.second;
	this->isDateTimeOk = other.isDateTimeOk;
	return *this;
}

LogFileDateTime &LogFileDateTime::operator=(LogFileDateTime &&other) noexcept
{
    this->year = std::move(other.year);
	this->month = std::move(other.month);
	this->day = std::move(other.day);
	this->hour = std::move(other.hour);
	this->minute = std::move(other.minute);
	this->second = std::move(other.second);
	this->isDateTimeOk = std::move(other.isDateTimeOk);
	return *this;
}

bool LogFileDateTime::operator==(const LogFileDateTime &other)
{
	if (!this->isDateTimeOk || !other.isDateTimeOk) return false;
	if (this->year != other.year) return false;
	if (this->month != other.month) return false;
	if (this->day != other.day) return false;
	if (this->hour != other.hour) return false;
	if (this->minute != other.minute) return false;
	if (this->second != other.second) return false;
	return true;
}

bool LogFileDateTime::operator!=(const LogFileDateTime &other)
{
    if (!this->isDateTimeOk || !other.isDateTimeOk) return false;
	return !(*this == other);
}

bool LogFileDateTime::operator<(const LogFileDateTime &other)
{
    if (!this->isDateTimeOk || !other.isDateTimeOk) return false;
	if (this->year >= other.year && this->month >= other.month && this->day >= other.day && this->hour >= other.hour && this->minute >= other.minute && this->second >= other.second) return false;
	if (this->year >= other.year && this->month >= other.month && this->day >= other.day && this->hour >= other.hour && this->minute > other.minute) return false;
	if (this->year >= other.year && this->month >= other.month && this->day >= other.day && this->hour > other.hour) return false;
	if (this->year >= other.year && this->month >= other.month && this->day > other.day) return false;
	if (this->year >= other.year && this->month > other.month) return false;
	if (this->year > other.year) return false;
	return true;
}

bool LogFileDateTime::operator<=(const LogFileDateTime &other)
{
    if (!this->isDateTimeOk || !other.isDateTimeOk) return false;
	if (this->year >= other.year && this->month >= other.month && this->day >= other.day && this->hour >= other.hour && this->minute >= other.minute && this->second > other.second) return false;
	if (this->year >= other.year && this->month >= other.month && this->day >= other.day && this->hour >= other.hour && this->minute > other.minute) return false;
	if (this->year >= other.year && this->month >= other.month && this->day >= other.day && this->hour > other.hour) return false;
	if (this->year >= other.year && this->month >= other.month && this->day > other.day) return false;
	if (this->year >= other.year && this->month > other.month) return false;
	if (this->year > other.year) return false;
	return true;
}

bool LogFileDateTime::operator>(const LogFileDateTime &other)
{
	if (!this->isDateTimeOk || !other.isDateTimeOk) return false;
	if (this->year <= other.year && this->month <= other.month && this->day <= other.day && this->hour <= other.hour && this->minute <= other.minute && this->second <= other.second) return false;
	if (this->year <= other.year && this->month <= other.month && this->day <= other.day && this->hour <= other.hour && this->minute < other.minute) return false;
	if (this->year <= other.year && this->month <= other.month && this->day <= other.day && this->hour < other.hour) return false;
	if (this->year <= other.year && this->month <= other.month && this->day < other.day) return false;
	if (this->year <= other.year && this->month < other.month) return false;
	if (this->year < other.year) return false;
	return true;
}

bool LogFileDateTime::operator>=(const LogFileDateTime &other)
{
	if (!this->isDateTimeOk || !other.isDateTimeOk) return false;
	if (this->year <= other.year && this->month <= other.month && this->day <= other.day && this->hour <= other.hour && this->minute <= other.minute && this->second < other.second) return false;
	if (this->year <= other.year && this->month <= other.month && this->day <= other.day && this->hour <= other.hour && this->minute < other.minute) return false;
	if (this->year <= other.year && this->month <= other.month && this->day <= other.day && this->hour < other.hour) return false;
	if (this->year <= other.year && this->month <= other.month && this->day < other.day) return false;
	if (this->year <= other.year && this->month < other.month) return false;
	if (this->year < other.year) return false;
	return true;
}

std::ostream &operator<<(std::ostream &os, const LogFileDateTime &logDt)
{
	if (logDt.isDateTimeOk)
	{
		os << logDt.year << '-';

		if (logDt.month < 10)
		{
			os << '0';
		}
		os << logDt.month << '-';

		if (logDt.day < 10)
		{
			os << '0';
		}
		os << logDt.day << ' ';

		if (logDt.hour < 10)
		{
			os << '0';
		}
		os << logDt.hour << ':';
		
		if (logDt.minute < 10)
		{
			os << '0';
		}
		os << logDt.minute << ':';
		
		if (logDt.second < 10)
		{
			os << '0';
		}
		os << logDt.second;
	}
	else
	{
		os << "File date time is missing";
	}
	return os;
}
