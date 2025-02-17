#include "LoggerCommonDataTypes.hpp"

LogEntry::LogEntry(std::string title, std::string message)
{
	this->title = title;
	this->message = message;
	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	#else
	this->dataType = LogDataType::LOG_NULL_DATA_ENTRY;
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
}

LogEntry::LogEntry(std::string title, std::string message, long long data)
{
	this->title = title;
	this->message = message;

	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	#else
	this->dataType = LogDataType::LOG_INTEGER_ENTRY;
	this->data.LOG_ENTRY_INT = data;
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
}

LogEntry::LogEntry(std::string title, std::string message, double data)
{
	this->title = title;
	this->message = message;

	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	#else
	this->dataType = LogDataType::LOG_FLOAT_ENTRY;
	this->data.LOG_ENTRY_FLOAT = data;
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
}

LogEntry::LogEntry(std::string title, std::string message, std::string data)
{
	this->title = title;
	this->message = message;

	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	#else
	this->dataType = LogDataType::LOG_STRING_ENTRY;
	this->strData = data;
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
}

LogEntry::LogEntry(std::string title, std::string message, LoggerLocalDateTime data, bool useHighPrecisionTime)
{
	this->title = title;
	this->message = message;

	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	#else
	if (useHighPrecisionTime)
	{
		this->dataType = LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY;
	}
	else
	{
		this->dataType = LogDataType::LOG_DATE_TIME_ENTRY;
	}
	
	this->data.LOG_ENTRY_DATE_TIME = data;
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
}

LogEntry::LogEntry(const LogEntry& other)
{
	this->message = other.message;
	this->title = other.title;

	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	#else
	this->dataType = other.dataType;

	switch (this->dataType)
	{
		case LogDataType::LOG_NULL_DATA_ENTRY:
		{
			break;
		}
		case LogDataType::LOG_INTEGER_ENTRY:
		{
			this->data.LOG_ENTRY_INT = other.data.LOG_ENTRY_INT;
			break;
		}
		case LogDataType::LOG_FLOAT_ENTRY:
		{
			this->data.LOG_ENTRY_FLOAT = other.data.LOG_ENTRY_FLOAT;
			break;
		}
		case LogDataType::LOG_STRING_ENTRY:
		{
			this->strData = other.strData;
			break;
		}
		case LogDataType::LOG_DATE_TIME_ENTRY:
		case LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY:
		{
			this->data.LOG_ENTRY_DATE_TIME = other.data.LOG_ENTRY_DATE_TIME;
			break;
		}
		default:
		{
			break;
		}
	}
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
}

LogEntry::LogEntry(LogEntry&& other) noexcept
{
	this->message = std::move(other.message);
	this->title = std::move(other.title);

	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	#else
	this->dataType = std::move(other.dataType);

	switch (this->dataType)
	{
		case LogDataType::LOG_NULL_DATA_ENTRY:
		{
			break;
		}
		case LogDataType::LOG_INTEGER_ENTRY:
		{
			this->data.LOG_ENTRY_INT = std::move(other.data.LOG_ENTRY_INT);
			break;
		}
		case LogDataType::LOG_FLOAT_ENTRY:
		{
			this->data.LOG_ENTRY_FLOAT = std::move(other.data.LOG_ENTRY_FLOAT);
			break;
		}
		case LogDataType::LOG_STRING_ENTRY:
		{
			this->strData = std::move(other.strData);
			break;
		}
		case LogDataType::LOG_DATE_TIME_ENTRY:
		case LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY:
		{
			this->data.LOG_ENTRY_DATE_TIME = std::move(other.data.LOG_ENTRY_DATE_TIME);
			break;
		}
		default:
		{
			break;
		}
	}
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
}

LogEntry& LogEntry::operator=(const LogEntry& other)
{
	this->title = other.title;
	this->message = other.message;
	this->data = other.data;

	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	#else
	this->dataType = other.dataType;
	this->strData = other.strData;
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE

	return *this;
}

LogEntry& LogEntry::operator=(LogEntry&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	this->title = std::move(other.title);
	this->message = std::move(other.message);
	this->data = std::move(other.data);

	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	#else
	this->dataType = std::move(other.dataType);
	this->strData = std::move(other.strData);
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE

	return *this;
}

bool LogEntry::operator==(const LogEntry& other) const
{
	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	/// @todo: Temporary to avoid compilation warnings.
	return true;
	#else
	bool isSame = true;

	if (this->dataType == other.dataType)
	{
		switch (this->dataType)
		{
			case LogDataType::LOG_NULL_DATA_ENTRY:
			{
				break;
			}
			case LogDataType::LOG_INTEGER_ENTRY:
			{
				if (this->data.LOG_ENTRY_INT != other.data.LOG_ENTRY_INT)
				{
					isSame = false;
				}
				break;
			}
			case LogDataType::LOG_FLOAT_ENTRY:
			{
				if (this->data.LOG_ENTRY_FLOAT != other.data.LOG_ENTRY_FLOAT)
				{
					isSame = false;
				}
				break;
			}
			case LogDataType::LOG_STRING_ENTRY:
			{
				if (this->strData != other.strData)
				{
					isSame = false;
				}
				break;
			}
			case LogDataType::LOG_DATE_TIME_ENTRY:
			{
				if (this->data.LOG_ENTRY_DATE_TIME.calendar != other.data.LOG_ENTRY_DATE_TIME.calendar || this->data.LOG_ENTRY_DATE_TIME.hours != other.data.LOG_ENTRY_DATE_TIME.hours || this->data.LOG_ENTRY_DATE_TIME.minutes != other.data.LOG_ENTRY_DATE_TIME.minutes || this->data.LOG_ENTRY_DATE_TIME.mSeconds != other.data.LOG_ENTRY_DATE_TIME.mSeconds || this->data.LOG_ENTRY_DATE_TIME.weekday != other.data.LOG_ENTRY_DATE_TIME.weekday)
				{
					isSame = false;
				}
				break;
			}
			case LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY:
			{
				break;
			}
			default:
			{
				break;
			}
		}
	}
	else
	{
		isSame = false;
	}

	if (this->title != other.title)
	{
		isSame = false;
	}

	return isSame;
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
}

LogEntry::~LogEntry()
{

}

std::string LogEntry::getTitle()
{
    return this->title;
}

std::string LogEntry::getMessage()
{
    return this->message;
}

LogDataType LogEntry::getType()
{
	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	return this->data.getType();
	#else
	return this->dataType;
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
}

#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
LogDataStore LogEntry::getData()
{
	return this->data;
}
#else
LogEntryData LogEntry::getData()
{
	if (this->dataType != LogDataType::LOG_NULL_DATA_ENTRY)
	{
		return this->data;
	}

    return LogEntryData();
}

std::string LogEntry::getStrData()
{
    return this->strData;
}
#endif // LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE

std::string LogEntry::getEntry()
{
	std::string entryLine;

	entryLine += this->title;
	entryLine += this->message;

	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	#else
	switch (this->dataType)
	{
		case LogDataType::LOG_INTEGER_ENTRY:
		{
			entryLine += std::to_string(this->data.LOG_ENTRY_INT);
			break;
		}
		case LogDataType::LOG_FLOAT_ENTRY:
		{
			entryLine += std::to_string(this->data.LOG_ENTRY_FLOAT);
			break;
		}
		case LogDataType::LOG_STRING_ENTRY:
		{
			if (this->strData.empty())
			{
				entryLine += "{FAIL TO READ POINTER TO DATA STRING}";
			}
			else
			{
				entryLine += this->strData;
			}
			break;
		}
		case LogDataType::LOG_DATE_TIME_ENTRY:
		{
			entryLine += convertDateTime2LogStrEntry(this->data.LOG_ENTRY_DATE_TIME);
			break;
		}
		case LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY:
		{
			entryLine += convertDateTime2LogStrEntry(this->data.LOG_ENTRY_DATE_TIME, false, true);
			break;
		}
		default:
		{
			break;
		}
	}
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE

	return entryLine;
}

std::ostream& operator<<(std::ostream& os, const LogEntry& obj)
{
	std::string entryLine;

	entryLine += obj.title;
	entryLine += obj.message;

	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	#else
	switch (obj.dataType)
	{
		case LogDataType::LOG_INTEGER_ENTRY:
		{
			entryLine += std::to_string(obj.data.LOG_ENTRY_INT);
			break;
		}
		case LogDataType::LOG_FLOAT_ENTRY:
		{
			entryLine += std::to_string(obj.data.LOG_ENTRY_FLOAT);
			break;
		}
		case LogDataType::LOG_STRING_ENTRY:
		{
			entryLine += obj.strData;
			break;
		}
		case LogDataType::LOG_DATE_TIME_ENTRY:
		{
			LoggerLocalDateTime dt = obj.data.LOG_ENTRY_DATE_TIME;
			entryLine += convertDateTime2LogStrEntry(dt);
			break;
		}
		case LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY:
		{
			LoggerLocalDateTime dt = obj.data.LOG_ENTRY_DATE_TIME;
			entryLine += convertDateTime2LogStrEntry(dt, false, true);
			break;
		}
		default:
		{
			break;
		}
	}
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE

	os << entryLine;

	return os;
}

LogEntryW::LogEntryW(std::wstring title, std::wstring message)
{
	this->title = title;
	this->message = message;
	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	#else
	this->dataType = LogDataType::LOG_NULL_DATA_ENTRY;
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
}

LogEntryW::LogEntryW(std::wstring title, std::wstring message, long long data)
{
	this->title = title;
	this->message = message;
	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	#else
	this->dataType = LogDataType::LOG_INTEGER_ENTRY;
	this->data.LOG_ENTRY_INT = data;
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
}

LogEntryW::LogEntryW(std::wstring title, std::wstring message, double data)
{
	this->title = title;
	this->message = message;
	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	#else
	this->dataType = LogDataType::LOG_FLOAT_ENTRY;
	this->data.LOG_ENTRY_FLOAT = data;
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
}

LogEntryW::LogEntryW(std::wstring title, std::wstring message, std::wstring data)
{
	this->title = title;
	this->message = message;
	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	#else
	this->dataType = LogDataType::LOG_STRING_ENTRY;
	this->strData = data;
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
}

LogEntryW::LogEntryW(std::wstring title, std::wstring message, LoggerLocalDateTime data, bool useHighPrecisionTime)
{
	this->title = title;
	this->message = message;

	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	#else
	if (useHighPrecisionTime)
	{
		this->dataType = LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY;
	}
	else
	{
		this->dataType = LogDataType::LOG_DATE_TIME_ENTRY;
	}

	this->data.LOG_ENTRY_DATE_TIME = data;
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
}

LogEntryW::LogEntryW(const LogEntryW& other)
{
	this->message = other.message;
	this->title = other.title;

	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	#else
	this->dataType = other.dataType;

	switch (this->dataType)
	{
		case LogDataType::LOG_NULL_DATA_ENTRY:
		{
			break;
		}
		case LogDataType::LOG_INTEGER_ENTRY:
		{
			this->data.LOG_ENTRY_INT = other.data.LOG_ENTRY_INT;
			break;
		}
		case LogDataType::LOG_FLOAT_ENTRY:
		{
			this->data.LOG_ENTRY_FLOAT = other.data.LOG_ENTRY_FLOAT;
			break;
		}
		case LogDataType::LOG_STRING_ENTRY:
		{
			this->strData = other.strData;
			break;
		}
		case LogDataType::LOG_DATE_TIME_ENTRY:
		case LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY:
		{
			this->data.LOG_ENTRY_DATE_TIME = other.data.LOG_ENTRY_DATE_TIME;
			break;
		}
		default:
		{
			break;
		}
	}
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	
}

LogEntryW::LogEntryW(LogEntryW&& other) noexcept
{
	this->message = std::move(other.message);
	this->title = std::move(other.title);

	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	#else
	this->dataType = std::move(other.dataType);

	switch (this->dataType)
	{
		case LogDataType::LOG_NULL_DATA_ENTRY:
		{
			break;
		}
		case LogDataType::LOG_INTEGER_ENTRY:
		{
			this->data.LOG_ENTRY_INT = std::move(other.data.LOG_ENTRY_INT);
			break;
		}
		case LogDataType::LOG_FLOAT_ENTRY:
		{
			this->data.LOG_ENTRY_FLOAT = std::move(other.data.LOG_ENTRY_FLOAT);
			break;
		}
		case LogDataType::LOG_STRING_ENTRY:
		{
			this->strData = std::move(other.strData);
			break;
		}
		case LogDataType::LOG_DATE_TIME_ENTRY:
		case LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY:
		{
			this->data.LOG_ENTRY_DATE_TIME = std::move(other.data.LOG_ENTRY_DATE_TIME);
			break;
		}
		default:
		{
			break;
		}
	}
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
}

LogEntryW& LogEntryW::operator=(const LogEntryW& other)
{
	this->title = other.title;
	this->message = other.message;
	this->data = other.data;

	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	#else
	this->dataType = std::move(other.dataType);
	this->strData = std::move(other.strData);
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE

	return *this;
}

LogEntryW& LogEntryW::operator=(LogEntryW&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	this->title = std::move(other.title);
	this->message = std::move(other.message);
	this->data = std::move(other.data);

	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	#else
	this->dataType = std::move(other.dataType);
	this->strData = std::move(other.strData);
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE

	return *this;
}

bool LogEntryW::operator==(const LogEntryW& other) const
{
	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	/// @todo: Temporary to avoid compilation warnings.
	return true;
	#else
	bool isSame = true;

	if (this->dataType == other.dataType)
	{
		switch (this->dataType)
		{
			case LogDataType::LOG_NULL_DATA_ENTRY:
			{
				break;
			}
			case LogDataType::LOG_INTEGER_ENTRY:
			{
				if (this->data.LOG_ENTRY_INT != other.data.LOG_ENTRY_INT)
				{
					isSame = false;
				}
				break;
			}
			case LogDataType::LOG_FLOAT_ENTRY:
			{
				if (this->data.LOG_ENTRY_FLOAT != other.data.LOG_ENTRY_FLOAT)
				{
					isSame = false;
				}
				break;
			}
			case LogDataType::LOG_STRING_ENTRY:
			{
				if (this->strData != other.strData)
				{
					isSame = false;
				}
				break;
			}
			case LogDataType::LOG_DATE_TIME_ENTRY:
			{
				if (this->data.LOG_ENTRY_DATE_TIME.calendar != other.data.LOG_ENTRY_DATE_TIME.calendar || this->data.LOG_ENTRY_DATE_TIME.hours != other.data.LOG_ENTRY_DATE_TIME.hours || this->data.LOG_ENTRY_DATE_TIME.minutes != other.data.LOG_ENTRY_DATE_TIME.minutes || this->data.LOG_ENTRY_DATE_TIME.mSeconds != other.data.LOG_ENTRY_DATE_TIME.mSeconds || this->data.LOG_ENTRY_DATE_TIME.weekday != other.data.LOG_ENTRY_DATE_TIME.weekday)
				{
					isSame = false;
				}
				break;
			}
			case LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY:
			{
				break;
			}
			default:
			{
				break;
			}
		}
	}
	else
	{
		isSame = false;
	}

	if (this->title != other.title)
	{
		isSame = false;
	}

	return isSame;
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
}

LogEntryW::~LogEntryW()
{

}

std::wstring LogEntryW::getTitle()
{
    return this->title;
}

std::wstring LogEntryW::getMessage()
{
    return this->message;
}

LogDataType LogEntryW::getType()
{
	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	return this->data.getType();
	#else
	return this->dataType;
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
}

#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
LogDataStore LogEntryW::getData()
{
	return this->data;
}
#else
LogEntryData LogEntryW::getData()
{
	if (this->dataType != LogDataType::LOG_NULL_DATA_ENTRY)
	{
		return this->data;
	}

    return LogEntryData();
}

std::wstring LogEntryW::getStrData()
{
    return this->strData;
}
#endif // LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE

std::wstring LogEntryW::getEntry()
{
	std::wstring entryLine;

	entryLine += this->title;
	entryLine += this->message;

	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	#else
	switch (this->dataType)
	{
		case LogDataType::LOG_INTEGER_ENTRY:
		{
			entryLine += std::to_wstring(this->data.LOG_ENTRY_INT);
			break;
		}
		case LogDataType::LOG_FLOAT_ENTRY:
		{
			entryLine += std::to_wstring(this->data.LOG_ENTRY_FLOAT);
			break;
		}
		case LogDataType::LOG_STRING_ENTRY:
		{
			if (this->strData.empty())
			{
				entryLine += L"{FAIL TO READ POINTER TO DATA STRING}";
			}
			else
			{
				entryLine += this->strData;
			}
			break;
		}
		case LogDataType::LOG_DATE_TIME_ENTRY:
		{
			entryLine += convertDateTime2LogStrEntryW(this->data.LOG_ENTRY_DATE_TIME);
			break;
		}
		case LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY:
		{
			entryLine += convertDateTime2LogStrEntryW(this->data.LOG_ENTRY_DATE_TIME, false, true);
			break;
		}
		default:
		{
			break;
		}
	}
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE

	return entryLine;
}

std::wostream& operator<<(std::wostream& os, const LogEntryW& obj)
{
	std::wstring entryLine;

	entryLine += obj.title;
	entryLine += obj.message;

	#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
	#else
	switch (obj.dataType)
	{
		case LogDataType::LOG_INTEGER_ENTRY:
		{
			entryLine += std::to_wstring(obj.data.LOG_ENTRY_INT);
			break;
		}
		case LogDataType::LOG_FLOAT_ENTRY:
		{
			entryLine += std::to_wstring(obj.data.LOG_ENTRY_FLOAT);
			break;
		}
		case LogDataType::LOG_STRING_ENTRY:
		{
			entryLine += obj.strData;
			break;
		}
		case LogDataType::LOG_DATE_TIME_ENTRY:
		{
			LoggerLocalDateTime dt = obj.data.LOG_ENTRY_DATE_TIME;
			entryLine += convertDateTime2LogStrEntryW(dt);
			break;
		}
		case LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY:
		{
			LoggerLocalDateTime dt = obj.data.LOG_ENTRY_DATE_TIME;
			entryLine += convertDateTime2LogStrEntryW(dt, false, true);
			break;
		}
		default:
		{
			break;
		}
	}
	#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE

	os << entryLine;

	return os;
}