#include "LogDataStore.hpp"

void LogDataStore::cleanData(LogDataType preserve)
{
	if (preserve == LogDataType::LOG_NULL_DATA_ENTRY)
	{
		this->str.reset(nullptr);
		this->wstr.reset(nullptr);
		this->unionVal.reset(nullptr);
		this->localDt.reset(nullptr);
		this->type = LogDataType::LOG_NULL_DATA_ENTRY;
	}
	else if (preserve == LogDataType::LOG_STRING_ENTRY)
	{
		this->wstr.reset(nullptr);
		this->unionVal.reset(nullptr);
		this->localDt.reset(nullptr);
	}
	else if (preserve == LogDataType::LOG_WSTRING_ENTRY)
	{
		this->str.reset(nullptr);
		this->unionVal.reset(nullptr);
		this->localDt.reset(nullptr);
	}
	else if (preserve == LogDataType::LOG_DATE_TIME_ENTRY || preserve == LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY)
	{
		this->str.reset(nullptr);
		this->wstr.reset(nullptr);
		this->unionVal.reset(nullptr);
	}
	else
	{
		this->str.reset(nullptr);
		this->wstr.reset(nullptr);
		this->localDt.reset(nullptr);
	}
}

LogDataStore::LogDataStore()
{
	this->type = LogDataType::LOG_NULL_DATA_ENTRY;
}

LogDataStore::LogDataStore(bool data)
{
	this->type = LogDataType::LOG_BOOLEAN_ENTRY;
	this->unionVal.reset(new LogEntryData);
	this->unionVal->LOG_ENTRY_BOOL = data;
}

LogDataStore::LogDataStore(char data)
{
	this->type = LogDataType::LOG_STRING_ENTRY;
	this->str.reset(new std::string);
	*this->str = data;
}

LogDataStore::LogDataStore(wchar_t data)
{
	this->type = LogDataType::LOG_WSTRING_ENTRY;
	this->wstr.reset(new std::wstring);
	*this->wstr = data;
}

LogDataStore::LogDataStore(short data)
{
	this->type = LogDataType::LOG_INTEGER_ENTRY;
	this->unionVal.reset(new LogEntryData);
	this->unionVal->LOG_ENTRY_INT = data;
}

LogDataStore::LogDataStore(unsigned short data)
{
	this->type = LogDataType::LOG_UNSIGNED_INTEGER_ENTRY;
	this->unionVal.reset(new LogEntryData);
	this->unionVal->LOG_ENTRY_UINT = data;
}

LogDataStore::LogDataStore(int data)
{
	this->type = LogDataType::LOG_INTEGER_ENTRY;
	this->unionVal.reset(new LogEntryData);
	this->unionVal->LOG_ENTRY_INT = data;
}

LogDataStore::LogDataStore(unsigned int data)
{
	this->type = LogDataType::LOG_UNSIGNED_INTEGER_ENTRY;
	this->unionVal.reset(new LogEntryData);
	this->unionVal->LOG_ENTRY_UINT = data;
}

LogDataStore::LogDataStore(long data)
{
	this->type = LogDataType::LOG_INTEGER_ENTRY;
	this->unionVal.reset(new LogEntryData);
	this->unionVal->LOG_ENTRY_INT = data;
}

LogDataStore::LogDataStore(unsigned long data)
{
	this->type = LogDataType::LOG_UNSIGNED_INTEGER_ENTRY;
	this->unionVal.reset(new LogEntryData);
	this->unionVal->LOG_ENTRY_UINT = data;
}

LogDataStore::LogDataStore(long long data)
{
	this->type = LogDataType::LOG_INTEGER_ENTRY;
	this->unionVal.reset(new LogEntryData);
	this->unionVal->LOG_ENTRY_INT = data;
}

LogDataStore::LogDataStore(unsigned long long data)
{
	this->type = LogDataType::LOG_UNSIGNED_INTEGER_ENTRY;
	this->unionVal.reset(new LogEntryData);
	this->unionVal->LOG_ENTRY_UINT = data;
}

LogDataStore::LogDataStore(float data)
{
	this->type = LogDataType::LOG_FLOAT_ENTRY;
	this->unionVal.reset(new LogEntryData);
	this->unionVal->LOG_ENTRY_FLOAT = data;
}

LogDataStore::LogDataStore(double data)
{
	this->type = LogDataType::LOG_FLOAT_ENTRY;
	this->unionVal.reset(new LogEntryData);
	this->unionVal->LOG_ENTRY_FLOAT = data;
}

LogDataStore::LogDataStore(char *data)
{
	this->type = LogDataType::LOG_STRING_ENTRY;
	this->str.reset(new std::string);
	*this->str = data;
}

LogDataStore::LogDataStore(const char *data)
{
	this->type = LogDataType::LOG_STRING_ENTRY;
	this->str.reset(new std::string);
	*this->str = data;
}

LogDataStore::LogDataStore(wchar_t *data)
{
	this->type = LogDataType::LOG_WSTRING_ENTRY;
	this->wstr.reset(new std::wstring);
	*this->wstr = data;
}

LogDataStore::LogDataStore(const wchar_t *data)
{
	this->type = LogDataType::LOG_WSTRING_ENTRY;
	this->wstr.reset(new std::wstring);
	*this->wstr = data;
}

LogDataStore::LogDataStore(std::string data)
{
	this->type = LogDataType::LOG_STRING_ENTRY;
	this->str.reset(new std::string);
	*this->str = data;
}

LogDataStore::LogDataStore(std::wstring data)
{
	this->type = LogDataType::LOG_WSTRING_ENTRY;
	this->wstr.reset(new std::wstring);
	*this->wstr = data;
}

LogDataStore::LogDataStore(LoggerLocalDateTime data, bool highPrecisionTime)
{
	#ifdef EXPERIMENTAL_AUTO_PRECISION_TIME
	if (data.highPrecision)
	{
		this->type = LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY;
	}
	else
	{
		this->type = LogDataType::LOG_DATE_TIME_ENTRY;
	}
	#else
	if (highPrecisionTime)
	{
		this->type = LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY;
	}
	else
	{
		this->type = LogDataType::LOG_DATE_TIME_ENTRY;
	}
	#endif // !EXPERIMENTAL_AUTO_PRECISION_TIME
	
	this->localDt.reset(new LoggerLocalDateTime);
	*this->localDt.get() = data;
}

LogDataStore::LogDataStore(const LogDataStore &other)
{
	if (this->type != other.type)
	{
		this->cleanData();
	}

	this->type = other.type;

	if (other.str)
	{
		this->str.reset(new std::string);
		*this->str.get() = *other.str.get();
	}

	if (other.wstr)
	{
		this->wstr.reset(new std::wstring);
		*this->wstr.get() = *other.wstr.get();
	}

	if (other.unionVal)
	{
		this->unionVal.reset(new LogEntryData);
		*this->unionVal.get() = *other.unionVal.get();
	}

	if (other.localDt)
	{
		this->localDt.reset(new LoggerLocalDateTime);
		*this->localDt.get() = *other.localDt.get();
	}
}

LogDataStore::LogDataStore(LogDataStore &&other) noexcept
{
	if (this->type != other.type)
	{
		this->cleanData();
	}

	this->type = std::move(other.type);

	if (other.str)
	{
		this->str = std::move(other.str);
	}

	if (other.wstr)
	{
		this->wstr = std::move(other.wstr);
	}

	if (other.unionVal)
	{
		this->unionVal = std::move(other.unionVal);
	}

	if (other.localDt)
	{
		this->localDt = std::move(other.localDt);
	}
}

LogDataStore::~LogDataStore()
{
	this->cleanData();
}

LogDataStore &LogDataStore::operator=(const LogDataStore &other)
{
	if (this->type != other.type)
	{
		this->cleanData();
	}

	this->type = other.type;

	if (other.str)
	{
		this->str.reset(new std::string);
		*this->str.get() = *other.str.get();
	}

	if (other.wstr)
	{
		this->wstr.reset(new std::wstring);
		*this->wstr.get() = *other.wstr.get();
	}

	if (other.unionVal)
	{
		this->unionVal.reset(new LogEntryData);
		*this->unionVal.get() = *other.unionVal.get();
	}

	if (other.localDt)
	{
		this->localDt.reset(new LoggerLocalDateTime);
		*this->localDt.get() = *other.localDt.get();
	}

	return *this;
}

LogDataStore &LogDataStore::operator=(LogDataStore &&other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

    if (this->type != other.type)
	{
		this->cleanData();
	}

	this->type = std::move(other.type);

	if (other.str)
	{
		this->str = std::move(other.str);
	}

	if (other.wstr)
	{
		this->wstr = std::move(other.wstr);
	}

	if (other.unionVal)
	{
		this->unionVal = std::move(other.unionVal);
	}

	if (other.localDt)
	{
		this->localDt = std::move(other.localDt);
	}

	return *this;
}

LogDataStore &LogDataStore::operator=(const bool &data)
{
	this->setData(data);
	return *this;
}

LogDataStore &LogDataStore::operator=(const char &data)
{
	this->setData(data);
	return *this;
}

LogDataStore &LogDataStore::operator=(const wchar_t &data)
{
    this->setData(data);
	return *this;
}

LogDataStore &LogDataStore::operator=(const short &data)
{
    this->setData(data);
	return *this;
}

LogDataStore &LogDataStore::operator=(const unsigned short &data)
{
    this->setData(data);
	return *this;
}

LogDataStore &LogDataStore::operator=(const int &data)
{
    this->setData(data);
	return *this;
}

LogDataStore &LogDataStore::operator=(const unsigned int &data)
{
    this->setData(data);
	return *this;
}

LogDataStore &LogDataStore::operator=(const long &data)
{
    this->setData(data);
	return *this;
}

LogDataStore &LogDataStore::operator=(const unsigned long &data)
{
    this->setData(data);
	return *this;
}

LogDataStore &LogDataStore::operator=(const long long &data)
{
    this->setData(data);
	return *this;
}

LogDataStore &LogDataStore::operator=(const unsigned long long &data)
{
    this->setData(data);
	return *this;
}

LogDataStore &LogDataStore::operator=(const float &data)
{
    this->setData(data);
	return *this;
}

LogDataStore &LogDataStore::operator=(const double &data)
{
    this->setData(data);
	return *this;
}

LogDataStore &LogDataStore::operator=(const std::string &data)
{
    this->setData(data);
	return *this;
}

LogDataStore &LogDataStore::operator=(const std::wstring &data)
{
    this->setData(data);
	return *this;
}

LogDataStore &LogDataStore::operator=(const LoggerLocalDateTime &data)
{
    this->setData(data);
	return *this;
}

bool LogDataStore::operator==(const LogDataType type)
{
    return this->type == type;
}

bool LogDataStore::operator!=(const LogDataType type)
{
    return !(*this == type);
}

LogDataStore::operator bool() const
{
	return this->type != LogDataType::LOG_NULL_DATA_ENTRY && (this->str || this->wstr || this->unionVal || this->localDt);
}

bool LogDataStore::operator==(const bool &data)
{
	if (this)
	{
		if (this->type == LogDataType::LOG_BOOLEAN_ENTRY)
		{
			return this->unionVal->LOG_ENTRY_BOOL == data;
		}
	}
    return false;
}

bool LogDataStore::operator==(const short &data)
{
	return *this == static_cast<long long>(data);
}

bool LogDataStore::operator==(const unsigned short &data)
{
	return *this == static_cast<unsigned long long>(data);
}

bool LogDataStore::operator==(const int &data)
{
	return *this == static_cast<long long>(data);
}

bool LogDataStore::operator==(const unsigned int &data)
{
	return *this == static_cast<unsigned long long>(data);
}

bool LogDataStore::operator==(const long &data)
{
	return *this == static_cast<long long>(data);
}

bool LogDataStore::operator==(const unsigned long &data)
{
	return *this == static_cast<unsigned long long>(data);
}

bool LogDataStore::operator==(const long long &data)
{
    if (this)
	{
		if (this->type == LogDataType::LOG_INTEGER_ENTRY)
		{
			return this->unionVal->LOG_ENTRY_INT == data;
		}
	}
    return false;
}

bool LogDataStore::operator==(const unsigned long long &data)
{
    if (this)
	{
		if (this->type == LogDataType::LOG_UNSIGNED_INTEGER_ENTRY)
		{
			return this->unionVal->LOG_ENTRY_UINT == data;
		}
	}
    return false;
}

bool LogDataStore::operator==(const float &data)
{
	return *this == static_cast<double>(data);
}

bool LogDataStore::operator==(const double &data)
{
    if (this)
	{
		if (this->type == LogDataType::LOG_FLOAT_ENTRY)
		{
			return this->unionVal->LOG_ENTRY_FLOAT == data;
		}
	}
    return false;
}

bool LogDataStore::operator==(const std::string &data)
{
    if (this)
	{
		if (this->type == LogDataType::LOG_STRING_ENTRY)
		{
			return *this->str == data;
		}
	}
    return false;
}

bool LogDataStore::operator==(const std::wstring &data)
{
    if (this)
	{
		if (this->type == LogDataType::LOG_WSTRING_ENTRY)
		{
			return *this->wstr == data;
		}
	}
    return false;
}

bool LogDataStore::operator==(const LoggerLocalDateTime &data)
{
    if (this)
	{
		if (this->type == LogDataType::LOG_DATE_TIME_ENTRY || this->type == LOG_DATE_TIME_HIGH_PRECISION_ENTRY)
		{
			bool dtEq = true;

			if (this->localDt->calendar != data.calendar || this->localDt->hours != data.hours || this->localDt->minutes != data.minutes || this->localDt->mSeconds != data.mSeconds || this->localDt->weekday != data.weekday)
			{
				dtEq = false;
			}

			#ifdef LOGGER_ENABLE_EXPERIMENTAL_ALL_PLATFORMS_HIGH_PRECISION_TIME
			if (this->type == LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY && this->localDt->highPrecision != data.highPrecision)
			{
				dtEq = false;
			}
			#else
				#ifdef WIN32	// On Windows platforms, high precision is already working
				if (this->type == LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY && this->localDt->highPrecision != data.highPrecision)
				{
					dtEq = false;
				}
				#endif
			#endif
			
			return dtEq;
		}
	}
    return false;
}

LogDataType LogDataStore::getType()
{
	return this->type;
}

std::string LogDataStore::getStr()
{
	if (this->str)
	{
		return *this->str.get();
	}

	return std::string();
}

std::wstring LogDataStore::getWstr()
{
	if (this->wstr)
	{
		return *this->wstr.get();
	}

    return std::wstring();
}

LogEntryData LogDataStore::getUnionData()
{
	if (this->unionVal)
	{
		return *this->unionVal.get();
	}

    LogEntryData newUnion;

	newUnion.LOG_ENTRY_INT = 0ll;

	return newUnion;
}

LoggerLocalDateTime LogDataStore::getLocalDt()
{
	if (this->localDt)
	{
		return *this->localDt.get();
	}

	LoggerLocalDateTime newDt;

	newDt.highPrecision = false;	// Initialize the boolean. Other elements already contain an empty constructor.

    return newDt;
}

void LogDataStore::setData(bool data)
{
	if (!this->unionVal)
	{
		this->cleanData();
		this->unionVal.reset(new LogEntryData);
	}

	this->unionVal->LOG_ENTRY_BOOL = data;
	this->type = LogDataType::LOG_BOOLEAN_ENTRY;
}

void LogDataStore::setData(char data)
{
	if (!this->str)
	{
		this->cleanData();
		this->str.reset(new std::string);
	}

	*this->str.get() = data;
	this->type = LogDataType::LOG_STRING_ENTRY;
}

void LogDataStore::setData(wchar_t data)
{
	if (!this->wstr)
	{
		this->cleanData();
		this->wstr.reset(new std::wstring);
	}

	*this->wstr.get() = data;
	this->type = LogDataType::LOG_WSTRING_ENTRY;
}

void LogDataStore::setData(short data)
{
	if (!this->unionVal)
	{
		this->cleanData();
		this->unionVal.reset(new LogEntryData);
	}

	this->unionVal->LOG_ENTRY_INT = data;
	this->type = LogDataType::LOG_INTEGER_ENTRY;
}

void LogDataStore::setData(unsigned short data)
{
	if (!this->unionVal)
	{
		this->cleanData();
		this->unionVal.reset(new LogEntryData);
	}

	this->unionVal->LOG_ENTRY_UINT = data;
	this->type = LogDataType::LOG_UNSIGNED_INTEGER_ENTRY;
}

void LogDataStore::setData(int data)
{
	if (!this->unionVal)
	{
		this->cleanData();
		this->unionVal.reset(new LogEntryData);
	}

	this->unionVal->LOG_ENTRY_INT = data;
	this->type = LogDataType::LOG_INTEGER_ENTRY;
}

void LogDataStore::setData(unsigned int data)
{
	if (!this->unionVal)
	{
		this->cleanData();
		this->unionVal.reset(new LogEntryData);
	}

	this->unionVal->LOG_ENTRY_UINT = data;
	this->type = LogDataType::LOG_UNSIGNED_INTEGER_ENTRY;
}

void LogDataStore::setData(long data)
{
	if (!this->unionVal)
	{
		this->cleanData();
		this->unionVal.reset(new LogEntryData);
	}

	this->unionVal->LOG_ENTRY_INT = data;
	this->type = LogDataType::LOG_INTEGER_ENTRY;
}

void LogDataStore::setData(unsigned long data)
{
	if (!this->unionVal)
	{
		this->cleanData();
		this->unionVal.reset(new LogEntryData);
	}

	this->unionVal->LOG_ENTRY_UINT = data;
	this->type = LogDataType::LOG_UNSIGNED_INTEGER_ENTRY;
}

void LogDataStore::setData(long long data)
{
	if (!this->unionVal)
	{
		this->cleanData();
		this->unionVal.reset(new LogEntryData);
	}

	this->unionVal->LOG_ENTRY_INT = data;
	this->type = LogDataType::LOG_INTEGER_ENTRY;
}

void LogDataStore::setData(unsigned long long data)
{
	if (!this->unionVal)
	{
		this->cleanData();
		this->unionVal.reset(new LogEntryData);
	}

	this->unionVal->LOG_ENTRY_UINT = data;
	this->type = LogDataType::LOG_UNSIGNED_INTEGER_ENTRY;
}

void LogDataStore::setData(float data)
{
	if (!this->unionVal)
	{
		this->cleanData();
		this->unionVal.reset(new LogEntryData);
	}

	this->unionVal->LOG_ENTRY_FLOAT = data;
	this->type = LogDataType::LOG_FLOAT_ENTRY;
}

void LogDataStore::setData(double data)
{
	if (!this->unionVal)
	{
		this->cleanData();
		this->unionVal.reset(new LogEntryData);
	}

	this->unionVal->LOG_ENTRY_FLOAT = data;
	this->type = LogDataType::LOG_FLOAT_ENTRY;
}

void LogDataStore::setData(char *data)
{
	if (!this->str)
	{
		this->cleanData();
		this->str.reset(new std::string);
	}

	*this->str.get() = *data;
	this->type = LogDataType::LOG_STRING_ENTRY;
}

void LogDataStore::setData(const char *data)
{
	if (!this->str)
	{
		this->cleanData();
		this->str.reset(new std::string);
	}

	*this->str.get() = *data;
	this->type = LogDataType::LOG_STRING_ENTRY;
}

void LogDataStore::setData(wchar_t *data)
{
	if (!this->wstr)
	{
		this->cleanData();
		this->wstr.reset(new std::wstring);
	}

	*this->wstr.get() = *data;
	this->type = LogDataType::LOG_WSTRING_ENTRY;
}

void LogDataStore::setData(const wchar_t *data)
{
	if (!this->wstr)
	{
		this->cleanData();
		this->wstr.reset(new std::wstring);
	}

	*this->wstr.get() = *data;
	this->type = LogDataType::LOG_WSTRING_ENTRY;
}

void LogDataStore::setData(std::string data)
{
	if (!this->str)
	{
		this->cleanData();
		this->str.reset(new std::string);
	}

	*this->str.get() = data;
	this->type = LogDataType::LOG_STRING_ENTRY;
}

void LogDataStore::setData(std::wstring data)
{
	if (!this->wstr)
	{
		this->cleanData();
		this->wstr.reset(new std::wstring);
	}

	*this->wstr.get() = data;
	this->type = LogDataType::LOG_WSTRING_ENTRY;
}

void LogDataStore::setData(LoggerLocalDateTime data, bool highPrecisionTime)
{
	if (!this->localDt)
	{
		this->cleanData();
		this->localDt.reset(new LoggerLocalDateTime);
	}

	#ifdef EXPERIMENTAL_AUTO_PRECISION_TIME
	if (data.highPrecision)
	{
		this->type = LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY;
	}
	else
	{
		this->type = LogDataType::LOG_DATE_TIME_ENTRY;
	}
	#else
	if (highPrecisionTime)
	{
		this->type = LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY;
	}
	else
	{
		this->type = LogDataType::LOG_DATE_TIME_ENTRY;
	}
	#endif // !EXPERIMENTAL_AUTO_PRECISION_TIME
	
	*this->localDt.get() = data;
}

void LogDataStore::clean()
{
	this->cleanData();
}

bool LogDataStore::hasData()
{
    return this->type != LogDataType::LOG_NULL_DATA_ENTRY && (this->str || this->wstr || this->unionVal || this->localDt);
}
