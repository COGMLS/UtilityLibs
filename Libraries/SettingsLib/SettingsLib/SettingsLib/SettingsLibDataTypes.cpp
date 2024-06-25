#include "SettingsLibDataTypes.hpp"

SettingsLib::Types::ConfigDataStore::ConfigDataStore()
{
	this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY;
}

SettingsLib::Types::ConfigDataStore::ConfigDataStore(const ConfigDataStore &other)
{
	try
	{
		if (other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
		{
			this->data.s = new std::string;
			*this->data.s = *other.data.s;
		}
		else if (other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
		{
			this->data.w = new std::wstring;
			*this->data.w = *other.data.w;
		}
		else
		{
			this->data = other.data;
		}

		this->type = other.type;
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
	}
}

SettingsLib::Types::ConfigDataStore::ConfigDataStore(ConfigDataStore &&other) noexcept
{
	try
	{
		this->data = std::move(other.data);
		this->type = other.type;
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
	}
}

bool SettingsLib::Types::ConfigDataStore::cleanStringData()
{
	try
	{
		if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
		{
			delete this->data.s;
			this->data.s = nullptr;
		}

		if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
		{
			delete this->data.w;
			this->data.w = nullptr;
		}

		return true;
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
		return false;
	}
}

SettingsLib::Types::ConfigDataStore::ConfigDataStore(unsigned long long data)
{
	try
	{
		this->data.ull = data;
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_UNSIGNED_INTEGER;
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
	}
}

SettingsLib::Types::ConfigDataStore::ConfigDataStore(long long data)
{
	try
	{
		this->data.ll = data;
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_INTERGER;
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
	}
}

SettingsLib::Types::ConfigDataStore::ConfigDataStore(double data)
{
	try
	{
		this->data.d = data;
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_FLOAT;
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
	}
}

SettingsLib::Types::ConfigDataStore::ConfigDataStore(bool data)
{
	try
	{
		this->data.b = data;
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_BOOLEAN;
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
	}
}

SettingsLib::Types::ConfigDataStore::ConfigDataStore(std::string data)
{
	try
	{
		this->data.s = new std::string;
		*this->data.s = data;
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING;
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
	}
}

SettingsLib::Types::ConfigDataStore::ConfigDataStore(std::wstring data)
{
	try
	{
		this->data.w = new std::wstring;
		*this->data.w = data;
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING;
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
	}
}

SettingsLib::Types::ConfigDataStore::~ConfigDataStore()
{
	if (this->type != SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL)
	{
		if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
		{
			delete this->data.s;
			this->data.s = nullptr;
		}

		if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
		{
			delete this->data.w;
			this->data.w = nullptr;
		}
	}
}

SettingsLib::Types::ConfigDataType SettingsLib::Types::ConfigDataStore::getDataType()
{
	return this->type;
}

bool SettingsLib::Types::ConfigDataStore::cleanData()
{
	try
	{
		if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING || this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
		{
			if (this->cleanStringData())
			{
				this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY;
			}
			else
			{
				this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
				return false;
			}
		}
		else
		{
			this->data.ull = 0ull;
			this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY;
		}

		return true;
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
		return false;
	}
	
}

SettingsLib::Types::ConfigDataStore &SettingsLib::Types::ConfigDataStore::operator=(unsigned short data)
{
	return this->operator=(static_cast<unsigned long long>(data));
}

SettingsLib::Types::ConfigDataStore &SettingsLib::Types::ConfigDataStore::operator=(unsigned int data)
{
	return this->operator=(static_cast<unsigned long long>(data));
}

SettingsLib::Types::ConfigDataStore &SettingsLib::Types::ConfigDataStore::operator=(unsigned long data)
{
	return this->operator=(static_cast<unsigned long long>(data));
}

SettingsLib::Types::ConfigDataStore &SettingsLib::Types::ConfigDataStore::operator=(unsigned long long data)
{
	try
	{
		// Remove the string data pointer:

		if (this->cleanStringData())
		{
			// Set the data:

			this->data.ull = data;
			this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_UNSIGNED_INTEGER;
		}
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
	}

    return *this;
}

SettingsLib::Types::ConfigDataStore &SettingsLib::Types::ConfigDataStore::operator=(short data)
{
	return this->operator=(static_cast<long long>(data));
}

SettingsLib::Types::ConfigDataStore &SettingsLib::Types::ConfigDataStore::operator=(int data)
{
	return this->operator=(static_cast<long long>(data));
}

SettingsLib::Types::ConfigDataStore &SettingsLib::Types::ConfigDataStore::operator=(long data)
{
	return this->operator=(static_cast<long long>(data));
}

SettingsLib::Types::ConfigDataStore& SettingsLib::Types::ConfigDataStore::operator= (long long data)
{
	try
	{
		// Remove the string data pointer:

		if (this->cleanStringData())
		{
			// Set the data:

			this->data.ll = data;
			this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_INTERGER;
		}
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
	}

    return *this;
}

SettingsLib::Types::ConfigDataStore &SettingsLib::Types::ConfigDataStore::operator=(float data)
{
	return this->operator=(static_cast<double>(data));
}

SettingsLib::Types::ConfigDataStore& SettingsLib::Types::ConfigDataStore::operator= (double data)
{
    try
	{
		// Remove the string data pointer:

		if (this->cleanStringData())
		{
			// Set the data:

			this->data.d = data;
			this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_FLOAT;
		}
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
	}

    return *this;
}

SettingsLib::Types::ConfigDataStore& SettingsLib::Types::ConfigDataStore::operator= (bool data)
{
	try
	{
		// Remove the string data pointer:

		if (this->cleanStringData())
		{
			// Set the data:

			this->data.b = data;
			this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_BOOLEAN;
		}
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
	}

    return *this;
}

SettingsLib::Types::ConfigDataStore &SettingsLib::Types::ConfigDataStore::operator=(char data)
{
	std::string lData;
	lData += data;
	return this->operator=(lData);
}

SettingsLib::Types::ConfigDataStore &SettingsLib::Types::ConfigDataStore::operator=(char data[])
{
    return this->operator=(std::string(data));
}

SettingsLib::Types::ConfigDataStore &SettingsLib::Types::ConfigDataStore::operator=(const char data[])
{
    return this->operator=(std::string(data));
}

SettingsLib::Types::ConfigDataStore &SettingsLib::Types::ConfigDataStore::operator=(wchar_t data)
{
	std::wstring lData;
	lData += data;
	return this->operator=(lData);
}

SettingsLib::Types::ConfigDataStore &SettingsLib::Types::ConfigDataStore::operator=(wchar_t data[])
{
    return this->operator=(std::wstring(data));
}

SettingsLib::Types::ConfigDataStore &SettingsLib::Types::ConfigDataStore::operator=(const wchar_t data[])
{
    return this->operator=(std::wstring(data));
}

SettingsLib::Types::ConfigDataStore &SettingsLib::Types::ConfigDataStore::operator=(std::string data)
{
	try
	{
		// Remove the string data pointer:

		if (this->type != SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
		{
			if (this->cleanStringData())
			{
				this->data.s = new std::string;
				*this->data.s = data;
				this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING;
			}
		}
		else
		{
			*this->data.s = data;
			this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING;
		}
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
	}

    return *this;
}

SettingsLib::Types::ConfigDataStore &SettingsLib::Types::ConfigDataStore::operator=(std::wstring data)
{
    try
	{
		// Remove the string data pointer:

		if (this->type != SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
		{
			if (this->cleanStringData())
			{
				this->data.w = new std::wstring;
				*this->data.w = data;
				this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING;
			}
		}
		else
		{
			*this->data.w = data;
			this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING;
		}
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
	}

    return *this;
}

SettingsLib::Types::ConfigDataStore& SettingsLib::Types::ConfigDataStore::operator= (const ConfigDataStore &other)
{
    if (this == &other)
	{
		return *this;
	}

	try
	{
		if (this->type == other.type)
		{
			if (other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
			{
				*this->data.s = *other.data.s;
			}
			else if (other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
			{
				*this->data.w = *other.data.w;
			}
			else
			{
				this->data = other.data;
			}

			this->type = other.type;
		}
		else
		{
			if (this->cleanStringData())
			{
				if (other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
				{
					this->data.s = new std::string;
					*this->data.s = *other.data.s;
				}
				else if (other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
				{
					this->data.w = new std::wstring;
					*this->data.w = *other.data.w;
				}
				else
				{
					this->data = other.data;
				}

				this->type = other.type;
			}
		}
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
	}

	return *this;
}

SettingsLib::Types::ConfigDataStore& SettingsLib::Types::ConfigDataStore::operator= (ConfigDataStore &&other) noexcept
{
    if (this == &other)
	{
		return *this;
	}

	try
	{
		bool cleanDataOK = true;

		if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING || this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
		{
			if (!this->cleanStringData())
			{
				cleanDataOK = false;
			}
		}

		if (cleanDataOK)
		{
			this->data = std::move(other.data);
			this->type = other.type;
		}
		else
		{
			this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
		}
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
	}

	return *this;
}

int SettingsLib::Types::ConfigDataStore::getData (unsigned long long *data)
{
	if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL)
	{
		return -1;
	}

	if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY)
	{
		return 0;
	}
	
    if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_UNSIGNED_INTEGER)
	{
		try
		{
			*data = this->data.ull;
			return 1;
		}
		catch(const std::exception&)
		{
			return -2;
		}
	}
	else
	{
		return 2;
	}
}

int SettingsLib::Types::ConfigDataStore::getData(long long *data)
{
    if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL)
	{
		return -1;
	}

	if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY)
	{
		return 0;
	}
	
    if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_INTERGER)
	{
		try
		{
			*data = this->data.ll;
			return 1;
		}
		catch(const std::exception&)
		{
			return -2;
		}
	}
	else
	{
		return 2;
	}
}

int SettingsLib::Types::ConfigDataStore::getData(double *data)
{
    if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL)
	{
		return -1;
	}

	if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY)
	{
		return 0;
	}
	
    if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_FLOAT)
	{
		try
		{
			*data = this->data.d;
			return 1;
		}
		catch(const std::exception&)
		{
			return -2;
		}
	}
	else
	{
		return 2;
	}
}

int SettingsLib::Types::ConfigDataStore::getData(bool *data)
{
    if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL)
	{
		return -1;
	}

	if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY)
	{
		return 0;
	}
	
    if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_BOOLEAN)
	{
		try
		{
			*data = this->data.b;
			return 1;
		}
		catch(const std::exception&)
		{
			return -2;
		}
	}
	else
	{
		return 2;
	}
}

int SettingsLib::Types::ConfigDataStore::getData(std::string *data)
{
    if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL)
	{
		return -1;
	}

	if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY)
	{
		return 0;
	}
	
    if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
	{
		try
		{
			if (this->data.s == nullptr)
			{
				return -3;
			}

			*data = *this->data.s;
			return 1;
		}
		catch(const std::exception&)
		{
			return -2;
		}
	}
	else
	{
		return 2;
	}
}

int SettingsLib::Types::ConfigDataStore::getData(std::wstring *data)
{
    if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL)
	{
		return -1;
	}

	if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY)
	{
		return 0;
	}
	
    if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
	{
		try
		{
			if (this->data.w == nullptr)
			{
				return -3;
			}

			*data = *this->data.w;
			return 1;
		}
		catch(const std::exception&)
		{
			return -2;
		}
	}
	else
	{
		return 2;
	}
}

int SettingsLib::Types::ConfigDataStore::setData(unsigned short data)
{
	return this->setData(static_cast<unsigned long long>(data));
}

int SettingsLib::Types::ConfigDataStore::setData(unsigned int data)
{
	return this->setData(static_cast<unsigned long long>(data));
}

int SettingsLib::Types::ConfigDataStore::setData(unsigned long data)
{
	return this->setData(static_cast<unsigned long long>(data));
}

int SettingsLib::Types::ConfigDataStore::setData(unsigned long long data)
{
	try
	{
		// Remove the string data pointer:

		if (this->cleanStringData())
		{
			// Set the data:

			this->data.ull = data;
			this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_UNSIGNED_INTEGER;

			return 0;
		}

		return 1;
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
		return 2;
	}
}

int SettingsLib::Types::ConfigDataStore::setData(unsigned short *data)
{
	return this->setData(*data);
}

int SettingsLib::Types::ConfigDataStore::setData(unsigned int *data)
{
	return this->setData(*data);
}

int SettingsLib::Types::ConfigDataStore::setData(unsigned long *data)
{
	return this->setData(*data);
}

int SettingsLib::Types::ConfigDataStore::setData(unsigned long long *data)
{
	if (data == nullptr)
	{
		return 3;
	}

	try
	{
		// Remove the string data pointer:

		if (this->cleanStringData())
		{
			// Set the data:

			this->data.ull = *data;
			this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_UNSIGNED_INTEGER;

			return 0;
		}

		return 1;
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
		return 2;
	}
}

int SettingsLib::Types::ConfigDataStore::setData(short data)
{
    return this->setData(static_cast<unsigned long long>(data));
}

int SettingsLib::Types::ConfigDataStore::setData(int data)
{
    return this->setData(static_cast<unsigned long long>(data));
}

int SettingsLib::Types::ConfigDataStore::setData(long data)
{
    return this->setData(static_cast<unsigned long long>(data));
}

int SettingsLib::Types::ConfigDataStore::setData(long long data)
{
	try
	{
		// Remove the string data pointer:

		if (this->cleanStringData())
		{
			// Set the data:

			this->data.ll = data;
			this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_INTERGER;

			return 0;
		}

		return 1;
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
		return 2;
	}
}

int SettingsLib::Types::ConfigDataStore::setData(short *data)
{
    return this->setData(*data);
}

int SettingsLib::Types::ConfigDataStore::setData(int *data)
{
    return this->setData(*data);
}

int SettingsLib::Types::ConfigDataStore::setData(long *data)
{
    return this->setData(*data);
}

int SettingsLib::Types::ConfigDataStore::setData(long long *data)
{
    if (data == nullptr)
	{
		return 3;
	}

	try
	{
		// Remove the string data pointer:

		if (this->cleanStringData())
		{
			// Set the data:

			this->data.ll = *data;
			this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_INTERGER;

			return 0;
		}

		return 1;
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
		return 2;
	}
}

int SettingsLib::Types::ConfigDataStore::setData(float data)
{
    return this->setData(static_cast<double>(data));
}

int SettingsLib::Types::ConfigDataStore::setData(double data)
{
	try
	{
		// Remove the string data pointer:

		if (this->cleanStringData())
		{
			// Set the data:

			this->data.d = data;
			this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_FLOAT;

			return 0;
		}

		return 1;
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
		return 2;
	}
}

int SettingsLib::Types::ConfigDataStore::setData(float *data)
{
    return this->setData(*data);
}

int SettingsLib::Types::ConfigDataStore::setData(double *data)
{
    if (data == nullptr)
	{
		return 3;
	}

	try
	{
		// Remove the string data pointer:

		if (this->cleanStringData())
		{
			// Set the data:

			this->data.d = *data;
			this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_FLOAT;

			return 0;
		}

		return 1;
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
		return 2;
	}
}

int SettingsLib::Types::ConfigDataStore::setData(bool data)
{
	try
	{
		// Remove the string data pointer:

		if (this->cleanStringData())
		{
			// Set the data:

			this->data.b = data;
			this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_BOOLEAN;

			return 0;
		}

		return 1;
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
		return 2;
	}
}

int SettingsLib::Types::ConfigDataStore::setData(bool* data)
{
    if (data == nullptr)
	{
		return 3;
	}

	try
	{
		// Remove the string data pointer:

		if (this->cleanStringData())
		{
			// Set the data:

			this->data.b = *data;
			this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_BOOLEAN;

			return 0;
		}

		return 1;
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
		return 2;
	}
}

int SettingsLib::Types::ConfigDataStore::setData(char data)
{
    std::string lData;
	lData += data;
	return this->setData(lData);
}

int SettingsLib::Types::ConfigDataStore::setData(char data[])
{
	std::string lData = data;
    return this->setData(lData);
}

int SettingsLib::Types::ConfigDataStore::setData(const char data[])
{
	std::string lData = data;
    return this->setData(lData);
}

int SettingsLib::Types::ConfigDataStore::setData(wchar_t data)
{
	std::wstring lData;
	lData += data;
    return this->setData(lData);
}

int SettingsLib::Types::ConfigDataStore::setData(wchar_t data[])
{
	std::wstring lData = data;
    return this->setData(lData);
}

int SettingsLib::Types::ConfigDataStore::setData(const wchar_t data[])
{
	std::wstring lData = data;
    return this->setData(lData);
}

int SettingsLib::Types::ConfigDataStore::setData(std::string data)
{
	try
	{
		// Remove the string data pointer:

		if (this->type != SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
		{
			if (this->cleanStringData())
			{
				this->data.s = new std::string;
				*this->data.s = data;
				this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING;

				return 0;
			}

			return 1;
		}
		else
		{
			*this->data.s = data;
			this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING;

			return 0;
		}
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
		return 2;
	}
}

int SettingsLib::Types::ConfigDataStore::setData(std::string *data)
{
    if (data == nullptr)
	{
		return 3;
	}
	
	try
	{
		// Remove the string data pointer:

		if (this->type != SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
		{
			if (this->cleanStringData())
			{
				this->data.s = new std::string;
				*this->data.s = *data;
				this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING;

				return 0;
			}

			return 1;
		}
		else
		{
			*this->data.s = *data;
			this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING;

			return 0;
		}
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
		return 2;
	}
}

int SettingsLib::Types::ConfigDataStore::setData(std::wstring data)
{
	try
	{
		// Remove the string data pointer:

		if (this->type != SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
		{
			if (this->cleanStringData())
			{
				this->data.w = new std::wstring;
				*this->data.w = data;
				this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING;

				return 0;
			}

			return 1;
		}
		else
		{
			*this->data.w = data;
			this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING;

			return 0;
		}
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
		return 2;
	}
}

int SettingsLib::Types::ConfigDataStore::setData(std::wstring* data)
{
    if (data == nullptr)
	{
		return 3;
	}
	
	try
	{
		// Remove the string data pointer:

		if (this->type != SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
		{
			if (this->cleanStringData())
			{
				this->data.w = new std::wstring;
				*this->data.w = *data;
				this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING;

				return 0;
			}

			return 1;
		}
		else
		{
			*this->data.w = *data;
			this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING;

			return 0;
		}
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
		return 2;
	}
}
