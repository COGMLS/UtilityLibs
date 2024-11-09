#include "SettingsLibDataTypes.hpp"

SettingsLib::Types::ConfigDataStore::ConfigDataStore()
{
	this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY;
	this->data.ull = 0ull;
}

SettingsLib::Types::ConfigDataStore::ConfigDataStore(const SettingsLib::Types::ConfigDataStore &other)
{
	this->data.ull = 0ull;

	try
	{
		if (other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_UNSIGNED_INTEGER)
		{
			this->data.ull = other.data.ull;
			this->type = other.type;
		}
		else if (other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_INTEGER)
		{
			this->data.ll = other.data.ll;
			this->type = other.type;
		}
		else if (other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_FLOAT)
		{
			this->data.d = other.data.d;
			this->type = other.type;
		}
		else if (other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_BOOLEAN)
		{
			this->data.b = other.data.b;
			this->type = other.type;
		}
		else if (other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
		{
			if (this->allocStringData())
			{
				this->strData->setStr(other.strData->getStr());
				this->type = other.type;
			}
		}
		else if (other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
		{
			if (this->allocStringData())
			{
				this->strData->setStr(other.strData->getStrW());
				this->type = other.type;
			}
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
}

SettingsLib::Types::ConfigDataStore::ConfigDataStore(SettingsLib::Types::ConfigDataStore &&other) noexcept
{
	try
	{
		this->data = std::move(other.data);
		this->type = std::move(other.type);

		if (other.strData != nullptr)
		{
			this->strData = std::move(other.strData);
		}
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
		if (this->strData.get() != nullptr)
		{
			this->strData.reset(nullptr);

			if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING || this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
			{
				this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY;
			}
		}

		return true;
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
		return false;
	}
}

bool SettingsLib::Types::ConfigDataStore::allocStringData()
{
	try
	{
		if (this->strData.get() == nullptr)
		{
			this->strData.reset(new SettingsLib::Types::ConfigStrData);
		}

		return true;
	}
	catch(const std::exception&)
	{
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
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_INTEGER;
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
		if (this->allocStringData())
		{
			if (this->strData->setStr(data))
			{
				this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING;
			}
			else
			{
				this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
			}
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
}

SettingsLib::Types::ConfigDataStore::ConfigDataStore(std::wstring data)
{
	try
	{
		if (this->allocStringData())
		{
			if (this->strData->setStr(data))
			{
				this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING;
			}
			else
			{
				this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
			}
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
}

SettingsLib::Types::ConfigDataStore::~ConfigDataStore()
{
	
}

SettingsLib::Types::ConfigDataType SettingsLib::Types::ConfigDataStore::getDataType() const
{
	if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING || this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
	{
		if (this->strData != nullptr)
		{
			SettingsLib::Types::ConfigDataType strType = this->strData->getDataType();
			if (strType != SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY && strType != SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_MISSING)
			{
				return this->type;
			}
		}
		return SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_MISSING;
	}

	return this->type;
}

bool SettingsLib::Types::ConfigDataStore::cleanData()
{
	try
	{
		if (this->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING || this->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
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
			this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_INTEGER;
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
				if (this->allocStringData())
				{
					if (this->strData->setStr(data))
					{
						this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING;
					}
					else
					{
						this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
					}
				}
			}
		}
		else
		{
			if (this->strData->setStr(data))
			{
				this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING;
			}
			else
			{
				this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
			}
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
				//*this->data.w = data;
				if (this->allocStringData())
				{
					if (this->strData->setStr(data))
					{
						this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING;
					}
					else
					{
						this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
					}
				}
			}
		}
		else
		{
			if (this->strData->setStr(data))
			{
				this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING;
			}
			else
			{
				this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
			}
		}
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
	}

    return *this;
}

SettingsLib::Types::ConfigDataStore& SettingsLib::Types::ConfigDataStore::operator= (const SettingsLib::Types::ConfigDataStore &other)
{
    if (this == &other)
	{
		return *this;
	}

	bool opSuccess = false;

	try
	{
		if (this->type != other.type)
		{
			opSuccess = this->cleanData();
		}

		if (opSuccess)
		{
			if (other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_UNSIGNED_INTEGER)
			{
				this->data.ull = other.data.ull;
				this->type = other.type;
			}
			else if (other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_INTEGER)
			{
				this->data.ll = other.data.ll;
				this->type = other.type;
			}
			else if (other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_FLOAT)
			{
				this->data.d = other.data.d;
				this->type = other.type;
			}
			else if (other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_BOOLEAN)
			{
				this->data.b = other.data.b;
				this->type = other.type;
			}
			else if (other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
			{
				if (this->allocStringData())
				{
					if (this->strData->setStr(other.strData->getStr()))
					{
						this->type = other.type;
					}
					else
					{
						this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
					}
				}
				else
				{
					this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
				}
			}
			else if (other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
			{
				if (this->allocStringData())
				{
					if (this->strData->setStr(other.strData->getStrW()))
					{
						this->type = other.type;
					}
					else
					{
						this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
					}
				}
				else
				{
					this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
				}
			}
			else
			{
				this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
			}
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

SettingsLib::Types::ConfigDataStore& SettingsLib::Types::ConfigDataStore::operator= (SettingsLib::Types::ConfigDataStore &&other) noexcept
{
    if (this == &other)
	{
		return *this;
	}

	try
	{
		bool cleanDataOK = false;

		if (this->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING || this->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
		{
			cleanDataOK = this->cleanStringData();
		}

		if (cleanDataOK)
		{
			if (other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING || other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
			{
				if (other.strData != nullptr)
				{
					this->strData = std::move(other.strData);
				}
				else
				{
					this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_MISSING;
				}
			}
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
	if (this->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL)
	{
		return -1;
	}

	if (this->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY)
	{
		return 0;
	}
	
    if (this->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_UNSIGNED_INTEGER)
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
    if (this->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL)
	{
		return -1;
	}

	if (this->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY)
	{
		return 0;
	}
	
    if (this->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_INTEGER)
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
    if (this->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL)
	{
		return -1;
	}

	if (this->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY)
	{
		return 0;
	}
	
    if (this->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_FLOAT)
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
    if (this->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL)
	{
		return -1;
	}

	if (this->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY)
	{
		return 0;
	}
	
    if (this->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_BOOLEAN)
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
	if (data == nullptr)
	{
		return -4;
	}

    if (this->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL)
	{
		return -1;
	}

	if (this->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY)
	{
		return 0;
	}

	if (this->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_MISSING)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_MISSING;
		return -3;
	}
	
    if (this->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
	{
		try
		{
			*data = this->strData->getStr();
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
	if (data == nullptr)
	{
		return -4;
	}

    if (this->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL)
	{
		return -1;
	}

	if (this->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY)
	{
		return 0;
	}

	if (this->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_MISSING)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_MISSING;
		return -3;
	}
	
    if (this->getDataType() == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
	{
		try
		{
			*data = this->strData->getStrW();
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

int SettingsLib::Types::ConfigDataStore::setData(short data)
{
    return this->setData(static_cast<long long>(data));
}

int SettingsLib::Types::ConfigDataStore::setData(int data)
{
    return this->setData(static_cast<long long>(data));
}

int SettingsLib::Types::ConfigDataStore::setData(long data)
{
    return this->setData(static_cast<long long>(data));
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
			this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_INTEGER;

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
				if (this->allocStringData())
				{
					if (this->strData->setStr(data))
					{
						this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING;
						return 0;
					}
				}
			}

			return 1;
		}
		else
		{
			if (this->strData->setStr(data))
			{
				this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING;
				return 0;
			}
		}

		return 1;
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
				if (this->allocStringData())
				{
					if (this->strData->setStr(data))
					{
						this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING;
						return 0;
					}
				}
			}

			return 1;
		}
		else
		{
			if (this->strData->setStr(data))
			{
				this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING;
				return 0;
			}
		}

		return 1;
	}
	catch(const std::exception&)
	{
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL;
		return 2;
	}
}

int SettingsLib::Types::ConfigDataStore::getDataStr(std::string *data)
{
	if (data == nullptr)
	{
		return 3;
	}

	try
	{
		switch (this->type)
		{
			case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_UNSIGNED_INTEGER:
			{
				*data = std::to_string(this->data.ull);
			}
			case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_INTEGER:
			{
				*data = std::to_string(this->data.ll);
			}
			case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_FLOAT:
			{
				*data = std::to_string(this->data.d);
				break;
			}
			case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING:
			{
				*data = this->strData->getStr();
			}
			case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_BOOLEAN:
			{
				if (this->data.b)
				{
					*data = "true";
				}
				else
				{
					*data = "false";
				}
				break;
			}
			case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING:
			{
				return 1;
			}
			default:
			{
				return 2;
			}
		}
		return 0;
	}
	catch(const std::exception&)
	{
		return 4;
	}
}

int SettingsLib::Types::ConfigDataStore::getDataStr(std::wstring *data)
{
    if (data == nullptr)
	{
		return 3;
	}

	try
	{
		switch (this->type)
		{
			case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_UNSIGNED_INTEGER:
			{
				*data = std::to_wstring(this->data.ull);
			}
			case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_INTEGER:
			{
				*data = std::to_wstring(this->data.ll);
			}
			case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_FLOAT:
			{
				*data = std::to_wstring(this->data.d);
				break;
			}
			case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING:
			{
				*data = this->strData->getStrW();
			}
			case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_BOOLEAN:
			{
				if (this->data.b)
				{
					*data = L"true";
				}
				else
				{
					*data = L"false";
				}
				break;
			}
			case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING:
			{
				return 1;
			}
			default:
			{
				return 2;
			}
		}
		return 0;
	}
	catch(const std::exception&)
	{
		return 4;
	}
}

SettingsLib::Types::ConfigStrData::ConfigStrData()
{
	this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY;
}

SettingsLib::Types::ConfigStrData::ConfigStrData(std::string str)
{
	this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING;
	this->s.reset(new std::string);
	*this->s = str;
}

SettingsLib::Types::ConfigStrData::ConfigStrData(std::wstring str)
{
	this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING;
	this->w.reset(new std::wstring);
	*this->w = str;
}

SettingsLib::Types::ConfigStrData::ConfigStrData(const SettingsLib::Types::ConfigStrData &other)
{
	this->type = other.type;

	if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
	{
		this->s.reset(new std::string);
		*this->s = *other.s;
	}

	if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
	{
		this->w.reset(new std::wstring);
		*this->w = *other.w;
	}
}

SettingsLib::Types::ConfigStrData::ConfigStrData(SettingsLib::Types::ConfigStrData &&other) noexcept
{
	this->type = std::move(other.type);

	if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
	{
		this->s = std::move(other.s);
	}

	if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
	{
		this->w = std::move(other.w);
	}
}

SettingsLib::Types::ConfigStrData::~ConfigStrData()
{
	
}

SettingsLib::Types::ConfigStrData &SettingsLib::Types::ConfigStrData::operator=(std::string str)
{
	if (this->type != SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
	{
		this->cleanData();
		this->s.reset(new std::string);
	}

	*this->s = str;
	this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING;

    return *this;
}

SettingsLib::Types::ConfigStrData &SettingsLib::Types::ConfigStrData::operator=(std::wstring str)
{
    if (this->type != SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
	{
		this->cleanData();
		this->w.reset(new std::wstring);
	}

	*this->w = str;
	this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING;

    return *this;
}

SettingsLib::Types::ConfigStrData &SettingsLib::Types::ConfigStrData::operator=(const SettingsLib::Types::ConfigStrData &other)
{
	if (this == &other)
	{
		return *this;
	}

	if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING && other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
	{
		*this->s = *other.s;
	}

	if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING && other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
	{
		*this->w = *other.w;
	}

	if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING && other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
	{
		if (this->cleanData())
		{
			this->w.reset(new std::wstring);
			*this->w = *other.w;
			this->type = other.type;
		}
	}

	if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING && other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
	{
		if (this->cleanData())
		{
			this->s.reset(new std::string);
			*this->s = *other.s;
			this->type = other.type;
		}
	}

	if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY)
	{
		if (other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
		{
			this->s.reset(new std::string);
			*this->s = *other.s;
			this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING;
		}

		if (other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
		{
			this->w.reset(new std::wstring);
			*this->w = *other.w;
			this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING;
		}
	}

	return *this;
}

SettingsLib::Types::ConfigStrData &SettingsLib::Types::ConfigStrData::operator=(SettingsLib::Types::ConfigStrData &&other) noexcept
{
    if (this == &other)
	{
		return *this;
	}

	if (this->cleanData())
	{
		if (other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
		{
			this->s = std::move(other.s);
		}

		if (other.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
		{
			this->w = std::move(other.w);
		}
	}

	this->type = std::move(other.type);

	return *this;
}

bool SettingsLib::Types::operator==(const SettingsLib::Types::ConfigStrData &lhs, const SettingsLib::Types::ConfigStrData &rhs)
{
	if (&lhs == &rhs)
	{
		return true;
	}

	if (lhs.type == rhs.type)
	{
		if (lhs.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
		{
			if (*lhs.s == *rhs.s)
			{
				return true;
			}
		}

		if (lhs.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
		{
			if (*lhs.w == *rhs.w)
			{
				return true;
			}
		}

		if (lhs.type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY)
		{
			return true;
		}
	}

    return false;
}

bool SettingsLib::Types::operator!=(const SettingsLib::Types::ConfigStrData &lhs, const SettingsLib::Types::ConfigStrData &rhs)
{
    return !(lhs == rhs);
}

SettingsLib::Types::ConfigDataType SettingsLib::Types::ConfigStrData::getDataType()
{
	return this->type;
}

std::string SettingsLib::Types::ConfigStrData::getStr()
{
	std::string buff;

	if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
	{
		buff = *this->s;
	}

	return buff;
}

std::wstring SettingsLib::Types::ConfigStrData::getStrW()
{
	std::wstring buff;

    if (this->type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
	{
		buff = *this->w;
	}

	return buff;
}

bool SettingsLib::Types::ConfigStrData::setStr(std::string str)
{
	if (this->cleanData())
	{
		this->s.reset(new std::string);
		*this->s = str;
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING;
		return true;
	}

	return false;
}

bool SettingsLib::Types::ConfigStrData::setStr(std::wstring str)
{
	if (this->cleanData())
	{
		this->w.reset(new std::wstring);
		*this->w = str;
		this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING;
		return true;
	}

	return false;
}

bool SettingsLib::Types::ConfigStrData::cleanData()
{
	try
	{
		if (this->type != SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING)
		{
			this->s.reset(nullptr);
			this->type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY;
		}

		if (this->type != SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING)
		{
			this->w.reset(nullptr);
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
