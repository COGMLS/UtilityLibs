#include "LogDataStore.hpp"

void LogDataStore::setDataStore(LogDataType type)
{
	if (type == LogDataType::LOG_DATA_FAIL)
	{
		return;	// LOG_DATA_FAIL is exclusive for setDataStore method. No change will be made it.
	}

	try
	{
		// Destroy any data that does not match with new type:

		if (type != LogDataType::LOG_STRING_ENTRY)
		{
			this->str.reset(nullptr);
		}

		if (type != LogDataType::LOG_WSTRING_ENTRY)
		{
			this->wstr.reset(nullptr);
		}

		if (
				type != LogDataType::LOG_BOOLEAN_ENTRY || 
				type != LogDataType::LOG_UNSIGNED_INTEGER_ENTRY || 
				type != LogDataType::LOG_INTEGER_ENTRY || 
				type != LogDataType::LOG_FLOAT_ENTRY
			)
		{
			this->unionVal.reset(nullptr);
		}

		if (type != LogDataType::LOG_DATE_TIME_ENTRY || type != LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY)
		{
			this->localDt.reset(nullptr);
		}

		// Check and create the new data:

		if (type == LogDataType::LOG_STRING_ENTRY)
		{
			if (!this->str)
			{
				this->str.reset(new std::string);
			}
		}
		else if (type == LogDataType::LOG_WSTRING_ENTRY)
		{
			if (!this->wstr)
			{
				this->wstr.reset(new std::wstring);
			}
		}
		else if (type == LogDataType::LOG_DATE_TIME_ENTRY || type == LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY)
		{
			if (!this->localDt)
			{
				this->localDt.reset(new LoggerLocalDateTime);
			}
		}
		else if (	// Union possible values:
					type == LogDataType::LOG_BOOLEAN_ENTRY || 
					type == LogDataType::LOG_UNSIGNED_INTEGER_ENTRY || 
					type == LogDataType::LOG_INTEGER_ENTRY || 
					type == LogDataType::LOG_FLOAT_ENTRY
				)
		{
			if (!this->unionVal)
			{
				this->unionVal.reset(new LogEntryData);
			}
		}
		
		this->type = type;	// Automatically define the type
	}
	catch(const std::exception&)
	{
		// If fail, set all data as nullptr and define the store as LOG_DATA_FAIL (-1)
		this->str.reset(nullptr);
		this->wstr.reset(nullptr);
		this->unionVal.reset(nullptr);
		this->localDt.reset(nullptr);
		this->type = LogDataType::LOG_DATA_FAIL;
	}
}

LogDataStore::LogDataStore()
{
	this->setDataStore(LogDataType::LOG_NULL_DATA_ENTRY);
}

LogDataStore::LogDataStore(bool data)
{
	this->setDataStore(LogDataType::LOG_BOOLEAN_ENTRY);
	this->unionVal->LOG_ENTRY_BOOL = data;
}

LogDataStore::LogDataStore(char data)
{
	this->setDataStore(LogDataType::LOG_STRING_ENTRY);
	*this->str = data;
}

LogDataStore::LogDataStore(wchar_t data)
{
	this->setDataStore(LogDataType::LOG_WSTRING_ENTRY);
	*this->wstr = data;
}

LogDataStore::LogDataStore(short data)
{
	this->setDataStore(LogDataType::LOG_INTEGER_ENTRY);
	this->unionVal->LOG_ENTRY_INT = data;
}

LogDataStore::LogDataStore(unsigned short data)
{
	this->setDataStore(LogDataType::LOG_UNSIGNED_INTEGER_ENTRY);
	this->unionVal->LOG_ENTRY_UINT = data;
}

LogDataStore::LogDataStore(int data)
{
	this->setDataStore(LogDataType::LOG_INTEGER_ENTRY);
	this->unionVal->LOG_ENTRY_INT = data;
}

LogDataStore::LogDataStore(unsigned int data)
{
	this->setDataStore(LogDataType::LOG_UNSIGNED_INTEGER_ENTRY);
	this->unionVal->LOG_ENTRY_UINT = data;
}

LogDataStore::LogDataStore(long data)
{
	this->setDataStore(LogDataType::LOG_INTEGER_ENTRY);
	this->unionVal->LOG_ENTRY_INT = data;
}

LogDataStore::LogDataStore(unsigned long data)
{
	this->setDataStore(LogDataType::LOG_UNSIGNED_INTEGER_ENTRY);
	this->unionVal->LOG_ENTRY_UINT = data;
}

LogDataStore::LogDataStore(long long data)
{
	this->setDataStore(LogDataType::LOG_INTEGER_ENTRY);
	this->unionVal->LOG_ENTRY_INT = data;
}

LogDataStore::LogDataStore(unsigned long long data)
{
	this->setDataStore(LogDataType::LOG_UNSIGNED_INTEGER_ENTRY);
	this->unionVal->LOG_ENTRY_UINT = data;
}

LogDataStore::LogDataStore(float data)
{
	this->setDataStore(LogDataType::LOG_FLOAT_ENTRY);
	this->unionVal->LOG_ENTRY_FLOAT = data;
}

LogDataStore::LogDataStore(double data)
{
	this->setDataStore(LogDataType::LOG_FLOAT_ENTRY);
	this->unionVal->LOG_ENTRY_FLOAT = data;
}

LogDataStore::LogDataStore(char *data)
{
	this->setDataStore(LogDataType::LOG_STRING_ENTRY);
	*this->str = data;
}

LogDataStore::LogDataStore(const char *data)
{
	this->setDataStore(LogDataType::LOG_STRING_ENTRY);
	*this->str = data;
}

LogDataStore::LogDataStore(wchar_t *data)
{
	this->setDataStore(LogDataType::LOG_WSTRING_ENTRY);
	*this->wstr = data;
}

LogDataStore::LogDataStore(const wchar_t *data)
{
	this->setDataStore(LogDataType::LOG_WSTRING_ENTRY);
	*this->wstr = data;
}

LogDataStore::LogDataStore(std::string data)
{
	this->setDataStore(LogDataType::LOG_STRING_ENTRY);
	*this->str = data;
}

LogDataStore::LogDataStore(std::wstring data)
{
	this->setDataStore(LogDataType::LOG_WSTRING_ENTRY);
	*this->wstr = data;
}

LogDataStore::LogDataStore(LoggerLocalDateTime data)
{
	if (data.highPrecision)
	{
		this->setDataStore(LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY);
	}
	else
	{
		this->setDataStore(LogDataType::LOG_DATE_TIME_ENTRY);
	}
	
	*this->localDt.get() = data;
}

LogDataStore::LogDataStore(LoggerLocalDateTime data, bool highPrecisionTime)
{
	// Remove the high precision time:
	if (!highPrecisionTime && data.highPrecision)
	{
		data.mSeconds = std::chrono::milliseconds(0);
		data.highPrecision = false;
	}

	if (highPrecisionTime)
	{
		this->setDataStore(LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY);
	}
	else
	{
		this->setDataStore(LogDataType::LOG_DATE_TIME_ENTRY);
	}
	
	*this->localDt.get() = data;
}

LogDataStore::LogDataStore(const LogDataStore &other)
{
	if (this->type != other.type)
	{
		this->setDataStore();
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
		this->setDataStore();
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
	this->setDataStore();
}

LogDataStore &LogDataStore::operator=(const LogDataStore &other)
{
	if (this->type != other.type)
	{
		this->setDataStore();
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
		this->setDataStore();
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

bool LogDataStore::operator==(const LogDataStore &other) const
{
	if (this->type == other.type)
	{
		if (this->str && other.str)
		{
			return *this->str == *other.str;
		}

		if (this->wstr && other.wstr)
		{
			return *this->wstr == *other.wstr;
		}

		if (this->unionVal && other.unionVal)
		{
			switch (this->type)
			{
				case LogDataType::LOG_UNSIGNED_INTEGER_ENTRY:
				{
					return this->unionVal->LOG_ENTRY_UINT == other.unionVal->LOG_ENTRY_UINT;
				}
				case LogDataType::LOG_INTEGER_ENTRY:
				{
					return this->unionVal->LOG_ENTRY_INT == other.unionVal->LOG_ENTRY_INT;
				}
				case LogDataType::LOG_FLOAT_ENTRY:
				{
					return this->unionVal->LOG_ENTRY_FLOAT == other.unionVal->LOG_ENTRY_FLOAT;
				}
				case LogDataType::LOG_BOOLEAN_ENTRY:
				{
					return this->unionVal->LOG_ENTRY_BOOL == other.unionVal->LOG_ENTRY_BOOL;
				}
				default:
				{
					return false;
				}
			}
		}

		if (this->localDt && other.localDt)
		{
			if (this->type == LogDataType::LOG_DATE_TIME_ENTRY || this->type == LOG_DATE_TIME_HIGH_PRECISION_ENTRY)
			{
				bool dtEq = true;

				if (this->localDt->calendar != other.localDt->calendar || this->localDt->hours != other.localDt->hours || this->localDt->minutes != other.localDt->minutes || this->localDt->seconds != other.localDt->seconds || this->localDt->weekday != other.localDt->weekday)
				{
					dtEq = false;
				}

				#ifdef LOGGER_ENABLE_EXPERIMENTAL_ALL_PLATFORMS_HIGH_PRECISION_TIME
				if (this->type == LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY && this->localDt->highPrecision != other.localDt->highPrecision && this->localDt->mSeconds != other.localDt->mSeconds)
				{
					dtEq = false;
				}
				#else
					#ifdef WIN32	// On Windows platforms, high precision is already working
					if (this->type == LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY && this->localDt->highPrecision != other.localDt->highPrecision && this->localDt->mSeconds != other.localDt->mSeconds)
					{
						dtEq = false;
					}
					#endif // !WIN32
				#endif // !LOGGER_ENABLE_EXPERIMENTAL_ALL_PLATFORMS_HIGH_PRECISION_TIME

				#ifdef LOGGER_ENABLE_EXPERIMENTAL_UTC_AND_LOCAL_DT
				if (this->localDt->utcTime != other.localDt->utcTime)
				{
					dtEq = false;
				}
				#endif // !LOGGER_ENABLE_EXPERIMENTAL_UTC_AND_LOCAL_DT
				
				return dtEq;
			}
		}
	}

	return false;
}

bool LogDataStore::operator!=(const LogDataStore &other) const
{
    return !(*this == other);
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
	return (this->type != LogDataType::LOG_NULL_DATA_ENTRY || this->type != LogDataType::LOG_DATA_FAIL) && (this->str || this->wstr || this->unionVal || this->localDt);
}

bool LogDataStore::operator==(const bool &data)
{
	if (this->unionVal)
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
    if (this->unionVal)
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
    if (this->unionVal)
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
    if (this->unionVal)
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
    if (this->str)
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
    if (this->wstr)
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
    if (this->localDt)
	{
		if (this->type == LogDataType::LOG_DATE_TIME_ENTRY || this->type == LOG_DATE_TIME_HIGH_PRECISION_ENTRY)
		{
			bool dtEq = true;

			if (this->localDt->calendar != data.calendar || this->localDt->hours != data.hours || this->localDt->minutes != data.minutes || this->localDt->seconds != data.seconds || this->localDt->weekday != data.weekday)
			{
				dtEq = false;
			}

			#ifdef LOGGER_ENABLE_EXPERIMENTAL_ALL_PLATFORMS_HIGH_PRECISION_TIME
			if (this->type == LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY && this->localDt->highPrecision != data.highPrecision && this->localDt->mSeconds != data.mSeconds)
			{
				dtEq = false;
			}
			#else
				#ifdef WIN32	// On Windows platforms, high precision is already working
				if (this->type == LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY && this->localDt->highPrecision != data.highPrecision && this->localDt->mSeconds != data.mSeconds)
				{
					dtEq = false;
				}
				#endif // !WIN32
			#endif // !LOGGER_ENABLE_EXPERIMENTAL_ALL_PLATFORMS_HIGH_PRECISION_TIME

			#ifdef LOGGER_ENABLE_EXPERIMENTAL_UTC_AND_LOCAL_DT
			if (this->localDt->utcTime != data.utcTime)
			{
				dtEq = false;
			}
			#endif // !LOGGER_ENABLE_EXPERIMENTAL_UTC_AND_LOCAL_DT
			
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

	// Initialize the boolean. Other elements already contain an empty constructor
	newDt.highPrecision = false;
	newDt.utcTime = false;

    return newDt;
}

void LogDataStore::setData(bool data)
{
	this->setDataStore(LogDataType::LOG_BOOLEAN_ENTRY);
	this->unionVal->LOG_ENTRY_BOOL = data;
}

void LogDataStore::setData(char data)
{
	this->setDataStore(LogDataType::LOG_STRING_ENTRY);
	*this->str.get() = data;
}

void LogDataStore::setData(wchar_t data)
{
	this->setDataStore(LogDataType::LOG_WSTRING_ENTRY);
	*this->wstr.get() = data;
}

void LogDataStore::setData(short data)
{
	this->setDataStore(LogDataType::LOG_INTEGER_ENTRY);
	this->unionVal->LOG_ENTRY_INT = data;
}

void LogDataStore::setData(unsigned short data)
{
	this->setDataStore(LogDataType::LOG_UNSIGNED_INTEGER_ENTRY);
	this->unionVal->LOG_ENTRY_UINT = data;
}

void LogDataStore::setData(int data)
{
	this->setDataStore(LogDataType::LOG_INTEGER_ENTRY);
	this->unionVal->LOG_ENTRY_INT = data;
}

void LogDataStore::setData(unsigned int data)
{
	this->setDataStore(LogDataType::LOG_UNSIGNED_INTEGER_ENTRY);
	this->unionVal->LOG_ENTRY_UINT = data;
}

void LogDataStore::setData(long data)
{
	this->setDataStore(LogDataType::LOG_INTEGER_ENTRY);
	this->unionVal->LOG_ENTRY_INT = data;
}

void LogDataStore::setData(unsigned long data)
{
	this->setDataStore(LogDataType::LOG_UNSIGNED_INTEGER_ENTRY);
	this->unionVal->LOG_ENTRY_UINT = data;
}

void LogDataStore::setData(long long data)
{
	this->setDataStore(LogDataType::LOG_INTEGER_ENTRY);
	this->unionVal->LOG_ENTRY_INT = data;
}

void LogDataStore::setData(unsigned long long data)
{
	this->setDataStore(LogDataType::LOG_UNSIGNED_INTEGER_ENTRY);
	this->unionVal->LOG_ENTRY_UINT = data;
}

void LogDataStore::setData(float data)
{
	this->setDataStore(LogDataType::LOG_FLOAT_ENTRY);
	this->unionVal->LOG_ENTRY_FLOAT = data;
}

void LogDataStore::setData(double data)
{
	this->setDataStore(LogDataType::LOG_FLOAT_ENTRY);
	this->unionVal->LOG_ENTRY_FLOAT = data;
}

void LogDataStore::setData(char *data)
{
	this->setDataStore(LogDataType::LOG_STRING_ENTRY);
	*this->str.get() = *data;
}

void LogDataStore::setData(const char *data)
{
	this->setDataStore(LogDataType::LOG_STRING_ENTRY);
	*this->str.get() = *data;
}

void LogDataStore::setData(wchar_t *data)
{
	this->setDataStore(LogDataType::LOG_WSTRING_ENTRY);
	*this->wstr.get() = *data;
}

void LogDataStore::setData(const wchar_t *data)
{
	this->setDataStore(LogDataType::LOG_WSTRING_ENTRY);
	*this->wstr.get() = *data;
}

void LogDataStore::setData(std::string data)
{
	this->setDataStore(LogDataType::LOG_STRING_ENTRY);
	*this->str.get() = data;
}

void LogDataStore::setData(std::wstring data)
{
	this->setDataStore(LogDataType::LOG_WSTRING_ENTRY);
	*this->wstr.get() = data;
}

void LogDataStore::setData(LoggerLocalDateTime data, bool highPrecisionTime)
{
	#ifdef EXPERIMENTAL_AUTO_PRECISION_TIME
	if (data.highPrecision)
	{
		this->setDataStore(LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY);
	}
	else
	{
		this->setDataStore(LogDataType::LOG_DATE_TIME_ENTRY);
	}
	#else
	if (highPrecisionTime)
	{
		this->setDataStore(LogDataType::LOG_DATE_TIME_HIGH_PRECISION_ENTRY);
	}
	else
	{
		this->setDataStore(LogDataType::LOG_DATE_TIME_ENTRY);
	}
	#endif // !EXPERIMENTAL_AUTO_PRECISION_TIME
	
	*this->localDt.get() = data;
}

void LogDataStore::clean()
{
	this->setDataStore();
}

bool LogDataStore::hasData()
{
    return (this->type != LogDataType::LOG_NULL_DATA_ENTRY || this->type != LogDataType::LOG_DATA_FAIL) && (this->str || this->wstr || this->unionVal || this->localDt);
}
