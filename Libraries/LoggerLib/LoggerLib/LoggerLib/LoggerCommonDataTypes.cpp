#include "LoggerCommonDataTypes.hpp"

LogEntry::LogEntry(std::string title, std::string message)
{
	this->title = title;
	this->message = message;
	this->dataType = LogDataType::LOG_NULL_DATA_ENTRY;
}

LogEntry::LogEntry(std::string title, std::string message, long long data)
{
	this->title = title;
	this->message = message;
	this->dataType = LogDataType::LOG_INTEGER_ENTRY;
	this->data.LOG_ENTRY_INT = data;
}

LogEntry::LogEntry(std::string title, std::string message, double data)
{
	this->title = title;
	this->message = message;
	this->dataType = LogDataType::LOG_FLOAT_ENTRY;
	this->data.LOG_ENTRY_FLOAT = data;
}

LogEntry::LogEntry(std::string title, std::string message, std::string data)
{
	this->title = title;
	this->message = message;
	this->dataType = LogDataType::LOG_STRING_ENTRY;
	this->strData = data;
}

LogEntry::LogEntry(std::string title, std::string message, LoggerLocalDateTime data, bool useHighPrecisionTime)
{
	this->title = title;
	this->message = message;

	if (useHighPrecisionTime)
	{
		this->dataType = LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY;
	}
	else
	{
		this->dataType = LogDataType::LOG_DATE_TIME_ENTRY;
	}

	this->data.LOG_ENTRY_DATE_TIME = data;
}

LogEntry::LogEntry(const LogEntry& other)
{
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

	this->message = other.message;
	this->title = other.title;
}

LogEntry::LogEntry(LogEntry&& other) noexcept
{
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

	this->message = other.message;
	this->title = other.title;
}

LogEntry& LogEntry::operator=(const LogEntry& other)
{
	this->data = other.data;
	this->dataType = other.dataType;
	this->message = other.message;
	this->strData = other.strData;
	this->title = other.title;

	return *this;
}

LogEntry& LogEntry::operator=(LogEntry&& other) noexcept
{
	this->data = other.data;
	this->dataType = other.dataType;
	this->message = other.message;
	this->strData = other.strData;
	this->title = other.title;

	other.~LogEntry();

	return *this;
}

bool LogEntry::operator==(const LogEntry& other) const
{
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
}

LogEntry::~LogEntry()
{

}

std::string LogEntry::getEntry()
{
	std::string entryLine;

	entryLine += this->title;
	entryLine += this->message;

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

	return entryLine;
}

std::ostream& operator<<(std::ostream& os, const LogEntry& obj)
{
	std::string entryLine;

	entryLine += obj.title;
	entryLine += obj.message;

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
			// TODO: Create a format date and time export
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

	os << entryLine;

	return os;
}

LogEntryW::LogEntryW(std::wstring title, std::wstring message)
{
	this->title = title;
	this->message = message;
	this->dataType = LogDataType::LOG_NULL_DATA_ENTRY;
}

LogEntryW::LogEntryW(std::wstring title, std::wstring message, long long data)
{
	this->title = title;
	this->message = message;
	this->dataType = LogDataType::LOG_INTEGER_ENTRY;
	this->data.LOG_ENTRY_INT = data;
}

LogEntryW::LogEntryW(std::wstring title, std::wstring message, double data)
{
	this->title = title;
	this->message = message;
	this->dataType = LogDataType::LOG_FLOAT_ENTRY;
	this->data.LOG_ENTRY_FLOAT = data;
}

LogEntryW::LogEntryW(std::wstring title, std::wstring message, std::wstring data)
{
	this->title = title;
	this->message = message;
	this->dataType = LogDataType::LOG_STRING_ENTRY;
	this->strData = data;
}

LogEntryW::LogEntryW(std::wstring title, std::wstring message, LoggerLocalDateTime data, bool useHighPrecisionTime)
{
	this->title = title;
	this->message = message;

	if (useHighPrecisionTime)
	{
		this->dataType = LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY;
	}
	else
	{
		this->dataType = LogDataType::LOG_DATE_TIME_ENTRY;
	}

	this->data.LOG_ENTRY_DATE_TIME = data;
}

LogEntryW::LogEntryW(const LogEntryW& other)
{
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

	this->message = other.message;
	this->title = other.title;
}

LogEntryW::LogEntryW(LogEntryW&& other) noexcept
{
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

	this->message = other.message;
	this->title = other.title;
}

LogEntryW& LogEntryW::operator=(const LogEntryW& other)
{
	this->data = other.data;
	this->dataType = other.dataType;
	this->message = other.message;
	this->strData = other.strData;
	this->title = other.title;

	return *this;
}

LogEntryW& LogEntryW::operator=(LogEntryW&& other) noexcept
{
	this->data = other.data;
	this->dataType = other.dataType;
	this->message = other.message;
	this->strData = other.strData;
	this->title = other.title;

	other.~LogEntryW();

	return *this;
}

bool LogEntryW::operator==(const LogEntryW& other) const
{
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
}

LogEntryW::~LogEntryW()
{

}

std::wstring LogEntryW::getEntry()
{
	std::wstring entryLine;

	entryLine += this->title;
	entryLine += this->message;

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

	return entryLine;
}

std::wostream& operator<<(std::wostream& os, const LogEntryW& obj)
{
	std::wstring entryLine;

	entryLine += obj.title;
	entryLine += obj.message;

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
			// TODO: Create a format date and time export
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

	os << entryLine;

	return os;
}