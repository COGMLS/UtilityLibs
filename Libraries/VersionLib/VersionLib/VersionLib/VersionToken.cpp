#include "VersionToken.hpp"

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM

//
// Version Token Data class:
//

VersionLib::VersionTokenData::VersionTokenData()
{
	this->type = VersionLib::VersionTokenDataType::EMPTY_DATA_TYPE;
}

VersionLib::VersionTokenData::VersionTokenData (std::string data)
{
	this->type = VersionLib::VersionTokenDataType::STRING_TYPE;
	this->strData.reset(new std::string);
	*this->strData = data;
}

VersionLib::VersionTokenData::VersionTokenData (unsigned int data)
{
	this->type = VersionLib::VersionTokenDataType::UNSIGNED_INT_TYPE;
	this->numData.reset(new VersionTokenNumData);
	this->numData.get()->int_data = data;
}

VersionLib::VersionTokenData::VersionTokenData (unsigned long long data)
{
	this->type = VersionLib::VersionTokenDataType::UNSIGNED_LONG_LONG_TYPE;
	this->numData.reset(new VersionTokenNumData);
	this->numData.get()->long_data = data;
}

VersionLib::VersionTokenData::VersionTokenData (const VersionLib::VersionTokenData& other)
{
	this->clear();
	this->type = other.type;

	if (other.strData)
	{
		this->strData.reset(new std::string);
		*this->strData = *other.strData;
	}

	if (other.numData)
	{
		this->numData.reset(new VersionLib::VersionTokenData::VersionTokenNumData);
		*this->numData = *other.numData;
	}
}

VersionLib::VersionTokenData::VersionTokenData (VersionLib::VersionTokenData&& other) noexcept
{
	this->type = std::move(other.type);

	if (other.strData)
	{
		this->strData = std::move(other.strData);
	}

	if (other.numData)
	{
		this->numData = std::move(other.numData);
	}
}

VersionLib::VersionTokenData::~VersionTokenData()
{
	if (this->strData)
	{
		this->strData.reset(nullptr);
	}

	if (this->numData)
	{
		this->numData.reset(nullptr);
	}
}

VersionLib::VersionTokenData& VersionLib::VersionTokenData::operator= (const VersionLib::VersionTokenData& other)
{
	if (this == &other)
	{
		return *this;
	}

	this->clear();
	this->type = other.type;

	if (other.strData)
	{
		this->strData.reset(new std::string);
		*this->strData = *other.strData;
	}

	if (other.numData)
	{
		this->numData.reset(new VersionLib::VersionTokenData::VersionTokenNumData);
		*this->numData = *other.numData;
	}

	return *this;
}

VersionLib::VersionTokenData& VersionLib::VersionTokenData::operator= (VersionLib::VersionTokenData&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	this->type = std::move(other.type);

	if (other.strData)
	{
		this->strData = std::move(other.strData);
	}

	if (other.numData)
	{
		this->numData = std::move(other.numData);
	}

	return *this;
}

VersionLib::VersionTokenData& VersionLib::VersionTokenData::operator= (std::string& data)
{
	if (this->numData)
	{
		this->numData.reset(nullptr);
	}

	if (!this->strData)
	{
		this->strData.reset(new std::string);
	}

	*this->strData.get() = data;
	this->type = VersionLib::VersionTokenDataType::STRING_TYPE;

	return *this;
}

VersionLib::VersionTokenData& VersionLib::VersionTokenData::operator= (unsigned int& data)
{
	if (this->strData)
	{
		this->strData.reset(nullptr);
	}

	if (!this->numData)
	{
		this->numData.reset(new VersionTokenNumData);
	}

	this->numData.get()->int_data = data;
	this->type = VersionLib::VersionTokenDataType::UNSIGNED_INT_TYPE;

	return *this;
}

VersionLib::VersionTokenData& VersionLib::VersionTokenData::operator= (unsigned long long& data)
{
	if (this->strData)
	{
		this->strData.reset(nullptr);
	}

	if (!this->numData)
	{
		this->numData.reset(new VersionTokenNumData);
	}

	this->numData.get()->long_data = data;
	this->type = VersionLib::VersionTokenDataType::UNSIGNED_LONG_LONG_TYPE;

	return *this;
}

bool VersionLib::VersionTokenData::operator==(const VersionLib::VersionTokenData& other)
{
	if (this->type != other.type)
	{
		return false;
	}

	if (this->numData && other.numData)
	{
		if (this->type == VersionTokenDataType::UNSIGNED_INT_TYPE)
		{
			return this->numData.get()->int_data == other.numData.get()->int_data;
		}
		else
		{
			return this->numData.get()->long_data == other.numData.get()->long_data;
		}
	}

	if (this->strData && other.strData)
	{
		return *this->strData.get() == *other.strData.get();
	}

	return false;
}

bool VersionLib::VersionTokenData::operator==(VersionLib::VersionTokenDataType type)
{
	return this->type == type;
}

VersionLib::VersionTokenData::operator bool() const
{
	if (this->type != VersionTokenDataType::EMPTY_DATA_TYPE || this->type != VersionTokenDataType::NULL_TYPE)
	{
		if (this->numData || this->strData)
		{
			return true;
		}
	}
	return false;
}

VersionLib::VersionTokenDataType VersionLib::VersionTokenData::getDataType()
{
	return this->type;
}

bool VersionLib::VersionTokenData::isEmpty()
{
	return this->type == VersionLib::VersionTokenDataType::EMPTY_DATA_TYPE;
}

bool VersionLib::VersionTokenData::isNull()
{
	return this->type == VersionLib::VersionTokenDataType::NULL_TYPE;
}

bool VersionLib::VersionTokenData::isNumVal()
{
	if (this->numData && (this->type == VersionLib::VersionTokenDataType::UNSIGNED_INT_TYPE || this->type == VersionLib::VersionTokenDataType::UNSIGNED_LONG_LONG_TYPE))
	{
		return true;
	}
	return false;
}

bool VersionLib::VersionTokenData::isLongVal()
{
	if (this->numData && this->type == VersionLib::VersionTokenDataType::UNSIGNED_LONG_LONG_TYPE)
	{
		return true;
	}
	return false;
}

bool VersionLib::VersionTokenData::isStringVal()
{
	if (this->strData && this->type == VersionLib::VersionTokenDataType::STRING_TYPE)
	{
		return true;
	}
	return false;
}

std::string VersionLib::VersionTokenData::getStr()
{
	if (this->isStringVal())
	{
		return *this->strData.get();
	}

	return std::string();
}

unsigned int VersionLib::VersionTokenData::getInt()
{
	if (this->isNumVal() && !this->isLongVal())
	{
		return this->numData.get()->int_data;
	}

	return 0u;
}

unsigned long long VersionLib::VersionTokenData::getLong()
{
	if (this->isLongVal())
	{
		return this->numData.get()->long_data;
	}

	return 0ull;
}

void VersionLib::VersionTokenData::clear()
{
	if (this->numData)
	{
		this->numData.reset(nullptr);
	}

	if (this->strData)
	{
		this->strData.reset(nullptr);
	}

	this->type = VersionLib::VersionTokenDataType::EMPTY_DATA_TYPE;
}

void VersionLib::VersionTokenData::setNull()
{
	this->clear();
	this->type = VersionLib::VersionTokenDataType::NULL_TYPE;
}

//
// Version Token class:
//

VersionLib::VersionToken::VersionToken()
{
	this->mandatory = false;
	this->type = VersionLib::VersionTokenType::EMPTY_TOKEN;
}

VersionLib::VersionToken::VersionToken (std::string tokenPattern)
{
	this->mandatory = false;
	this->type = VersionLib::VersionTokenType::EMPTY_TOKEN;
}

#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM