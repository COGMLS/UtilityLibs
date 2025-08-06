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

VersionLib::VersionTokenData::VersionTokenData (unsigned short data)
{
	this->type = VersionLib::VersionTokenDataType::UNSIGNED_SHORT_TYPE;
	this->numData.reset(new VersionTokenNumData);
	this->numData.get()->short_data = data;
}

VersionLib::VersionTokenData::VersionTokenData (unsigned int data)
{
	this->type = VersionLib::VersionTokenDataType::UNSIGNED_INT_TYPE;
	this->numData.reset(new VersionTokenNumData);
	this->numData.get()->int_data = data;
}

VersionLib::VersionTokenData::VersionTokenData (unsigned long data)
{
	this->type = VersionLib::VersionTokenDataType::UNSIGNED_LONG_TYPE;
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

VersionLib::VersionTokenData& VersionLib::VersionTokenData::operator= (unsigned short& data)
{
	if (this->strData)
	{
		this->strData.reset(nullptr);
	}

	if (!this->numData)
	{
		this->numData.reset(new VersionTokenNumData);
	}

	this->numData.get()->short_data = data;
	this->type = VersionLib::VersionTokenDataType::UNSIGNED_SHORT_TYPE;

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

VersionLib::VersionTokenData& VersionLib::VersionTokenData::operator= (unsigned long& data)
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
	this->type = VersionLib::VersionTokenDataType::UNSIGNED_LONG_TYPE;

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
		if (this->type == VersionTokenDataType::UNSIGNED_SHORT_TYPE)
		{
			return this->numData.get()->short_data == other.numData.get()->short_data;
		}
		else if (this->type == VersionTokenDataType::UNSIGNED_INT_TYPE)
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
	if (this->type != VersionLib::VersionTokenDataType::EMPTY_DATA_TYPE || this->type != VersionLib::VersionTokenDataType::NULL_TYPE)
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

bool VersionLib::VersionTokenData::isType (VersionLib::VersionTokenDataType type)
{
	return this->type == type;
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
	if (this->numData && (this->type == VersionLib::VersionTokenDataType::UNSIGNED_SHORT_TYPE || this->type == VersionLib::VersionTokenDataType::UNSIGNED_INT_TYPE || this->type == VersionLib::VersionTokenDataType::UNSIGNED_LONG_TYPE))
	{
		return true;
	}
	return false;
}

bool VersionLib::VersionTokenData::isIntVal()
{
	if (this->numData && this->type == VersionLib::VersionTokenDataType::UNSIGNED_INT_TYPE)
	{
		return true;
	}
	return false;
}

bool VersionLib::VersionTokenData::isLongVal()
{
	if (this->numData && this->type == VersionLib::VersionTokenDataType::UNSIGNED_LONG_TYPE)
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

unsigned short VersionLib::VersionTokenData::getShort()
{
	if (this->isNumVal() && !this->isIntVal() && !this->isLongVal())
	{
		return this->numData.get()->short_data;
	}

	return 0u;
}

unsigned int VersionLib::VersionTokenData::getInt()
{
	if (this->isIntVal())
	{
		return this->numData.get()->int_data;
	}

	return 0u;
}

unsigned long VersionLib::VersionTokenData::getLong()
{
	if (this->isLongVal())
	{
		return this->numData.get()->long_data;
	}

	return 0ul;
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
	this->position = -1;
	this->mandatory = false;
	this->type = VersionLib::VersionTokenType::EMPTY_TOKEN;
}

VersionLib::VersionToken::VersionToken(VersionLib::VersionTokenData data)
{
	this->position = -1;
	this->mandatory = false;
	this->data = data;
	
	if (this->data.isEmpty() || this->data.isNull())
	{
		this->type = VersionLib::VersionTokenType::EMPTY_TOKEN;
	}
	else if (this->data.isNumVal())
	{
		if (this->data.isIntVal())
		{
			this->type = VersionLib::VersionTokenType::NUMERIC_TOKEN;
		}
		else if (this->data.isLongVal())
		{
			this->type = VersionLib::VersionTokenType::LONG_NUMBER_TOKEN;
		}
		else
		{
			this->type = VersionLib::VersionTokenType::SHORT_NUMERIC_TOKEN;
		}
	}
	else if (this->data.isStringVal())
	{
		this->type = VersionLib::VersionTokenType::STRING_TOKEN;
	}
	else
	{
		this->type = VersionLib::VersionTokenType::UNDEFINED_TOKEN;
	}
}

VersionLib::VersionToken::VersionToken(VersionLib::VersionTokenData data, int position)
{
	if (position < 0)
	{
		position = -1;	// Set as a default value to disable the position
	}

	this->position = position;
	this->mandatory = false;
	this->data = data;
	
	if (this->data.isEmpty() || this->data.isNull())
	{
		this->type = VersionLib::VersionTokenType::EMPTY_TOKEN;
	}
	else if (this->data.isNumVal())
	{
		if (this->data.isIntVal())
		{
			this->type = VersionLib::VersionTokenType::NUMERIC_TOKEN;
		}
		else if (this->data.isLongVal())
		{
			this->type = VersionLib::VersionTokenType::LONG_NUMBER_TOKEN;
		}
		else
		{
			this->type = VersionLib::VersionTokenType::SHORT_NUMERIC_TOKEN;
		}
	}
	else if (this->data.isStringVal())
	{
		this->type = VersionLib::VersionTokenType::STRING_TOKEN;
	}
	else
	{
		this->type = VersionLib::VersionTokenType::UNDEFINED_TOKEN;
	}
}

VersionLib::VersionToken::VersionToken(VersionLib::VersionTokenData data, int position, bool mandatory)
{
	if (position < 0)
	{
		position = -1;	// Set as a default value to disable the position
	}

	this->position = position;
	this->mandatory = mandatory;
	this->data = data;
	
	if (this->data.isEmpty() || this->data.isNull())
	{
		this->type = VersionLib::VersionTokenType::EMPTY_TOKEN;
	}
	else if (this->data.isNumVal())
	{
		if (this->data.isIntVal())
		{
			this->type = VersionLib::VersionTokenType::NUMERIC_TOKEN;
		}
		else if (this->data.isLongVal())
		{
			this->type = VersionLib::VersionTokenType::LONG_NUMBER_TOKEN;
		}
		else
		{
			this->type = VersionLib::VersionTokenType::SHORT_NUMERIC_TOKEN;
		}
	}
	else if (this->data.isStringVal())
	{
		this->type = VersionLib::VersionTokenType::STRING_TOKEN;
	}
	else
	{
		this->type = VersionLib::VersionTokenType::UNDEFINED_TOKEN;
	}
}

VersionLib::VersionToken::VersionToken(VersionLib::VersionTokenData data, VersionLib::VersionTokenType type)
{
	this->position = -1;
	this->mandatory = false;
	this->data = data;
	this->type = type;
}

VersionLib::VersionToken::VersionToken(VersionLib::VersionTokenData data, VersionLib::VersionTokenType type, int position)
{
	if (position < 0)
	{
		position = -1;	// Set as a default value to disable the position
	}

	this->position = position;
	this->mandatory = false;
	this->data = data;
	this->type = type;
}

VersionLib::VersionToken::VersionToken(VersionLib::VersionTokenData data, VersionLib::VersionTokenType type, int position, bool mandatory)
{
	if (position < 0)
	{
		position = -1;	// Set as a default value to disable the position
	}

	this->position = position;
	this->mandatory = mandatory;
	this->data = data;
	this->type = type;
}

VersionLib::VersionToken::VersionToken(const VersionLib::VersionToken &other)
{
	this->position = other.position;
	this->mandatory = other.mandatory;
	this->type = other.type;
	this->data = other.data;
}

VersionLib::VersionToken::VersionToken(VersionLib::VersionToken &&other) noexcept
{
	this->position = std::move(other.position);
	this->mandatory = std::move(other.mandatory);
	this->type = std::move(other.type);
	this->data = std::move(other.data);
}

VersionLib::VersionToken::~VersionToken()
{
}

VersionLib::VersionToken& VersionLib::VersionToken::operator= (const VersionLib::VersionToken& other)
{
	if (this == &other)
	{
		return *this;
	}

	this->position = other.position;
	this->mandatory = other.mandatory;
	this->type = other.type;
	this->data = other.data;

	return *this;
}

VersionLib::VersionToken& VersionLib::VersionToken::operator= (VersionLib::VersionToken&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	this->position = std::move(other.position);
	this->mandatory = std::move(other.mandatory);
	this->type = std::move(other.type);
	this->data = std::move(other.data);

	return *this;
}

VersionLib::VersionToken& VersionLib::VersionToken::operator= (std::string& val)
{
	this->data = val;
	return *this;
}

VersionLib::VersionToken& VersionLib::VersionToken::operator= (unsigned short& val)
{
	this->data = val;
	return *this;
}

VersionLib::VersionToken& VersionLib::VersionToken::operator= (unsigned int& val)
{
	this->data = val;
	return *this;
}

VersionLib::VersionToken& VersionLib::VersionToken::operator= (unsigned long& val)
{
	this->data = val;
	return *this;
}

bool VersionLib::VersionToken::operator== (VersionLib::VersionTokenType type)
{
	return this->type == type;
}

bool VersionLib::VersionToken::operator!= (VersionLib::VersionTokenType type)
{
	return !(*this == type);
}

VersionLib::VersionToken::operator bool() const
{
	if (this->type != VersionLib::VersionTokenType::UNDEFINED_TOKEN && this->data)
	{
		return true;
	}
	return false;
}

bool VersionLib::VersionToken::isType (VersionLib::VersionTokenType type)
{
	return this->type == type;
}

bool VersionLib::VersionToken::isMandatory()
{
	return this->mandatory;
}

bool VersionLib::VersionToken::isEmpty()
{
	return this->type == VersionLib::VersionTokenType::EMPTY_TOKEN;
}

bool VersionLib::VersionToken::isNumVal()
{
	return this->type == VersionLib::VersionTokenType::SHORT_NUMERIC_TOKEN || 
			this->type == VersionLib::VersionTokenType::NUMERIC_TOKEN || 
			this->type == VersionLib::VersionTokenType::LONG_NUMBER_TOKEN;
}

bool VersionLib::VersionToken::isShortVal()
{
	return this->type == VersionLib::VersionTokenType::SHORT_NUMERIC_TOKEN;
}

bool VersionLib::VersionToken::isIntVal()
{
	return this->type == VersionLib::VersionTokenType::NUMERIC_TOKEN;
}

bool VersionLib::VersionToken::isLongVal()
{
	return this->type == VersionLib::VersionTokenType::LONG_NUMBER_TOKEN;
}

bool VersionLib::VersionToken::isStringVal()
{
	return this->type == VersionLib::VersionTokenType::STRING_TOKEN || this->data.isStringVal();
}

bool VersionLib::VersionToken::isSpecialToken()
{
	return this->type >= VersionLib::VersionTokenType::VERSION_TOKEN_VERSION_CORE_SEPARATOR;
}

int VersionLib::VersionToken::getPos()
{
	return this->position;
}

std::string VersionLib::VersionToken::getTokenStr()
{
	std::string tmp;

	if (this->data)
	{
		if (this->data.isLongVal())
		{
			tmp = this->data.getLong();
		}
		else if (this->data.isNumVal())
		{
			tmp = data.getInt();
		}
		else
		{
			tmp = data.getStr();
		}
	}

	return tmp;
}

VersionLib::VersionTokenType VersionLib::VersionToken::getType()
{
	return this->type;
}

VersionLib::VersionTokenData VersionLib::VersionToken::getTokenData()
{
	return this->data;
}

void VersionLib::VersionToken::setPos (int position)
{
	if (position < 0)
	{
		position = -1;
	}

	this->position = position;
}

void VersionLib::VersionToken::setMandatory (bool mandatory)
{
	this->mandatory = mandatory;
}

void VersionLib::VersionToken::setTokenType (VersionLib::VersionTokenType type)
{
	this->type = type;
}

void VersionLib::VersionToken::setTokenData (VersionLib::VersionTokenData& data)
{
	this->data = data;
}

//
// Version Token Tools:
//

std::string VersionLib::getTokenTypeStr (VersionLib::VersionTokenType type)
{
	switch (type)
	{
		case UNDEFINED_TOKEN:
		{
			return "UNDEFINED_TOKEN";
		}
		case EMPTY_TOKEN:
		{
			return "EMPTY_TOKEN";
		}
		case SHORT_NUMERIC_TOKEN:
		{
			return "SHORT_NUMERIC_TOKEN";
		}
		case NUMERIC_TOKEN:
		{
			return "NUMERIC_TOKEN";
		}
		case LONG_NUMBER_TOKEN:
		{
			return "LONG_NUMBER_TOKEN";
		}
		case STRING_TOKEN:
		{
			return "STRING_TOKEN";
		}
		case VERSION_TOKEN_VERSION_CORE_SEPARATOR:
		{
			return "VERSION_TOKEN_VERSION_CORE_SEPARATOR";
		}
		case VERSION_TOKEN_RELEASE_SEPARATOR:
		{
			return "VERSION_TOKEN_RELEASE_SEPARATOR";
		}
		case VERSION_TOKEN_RELEASE_COMPONENT_DEFINITION:
		{
			return "VERSION_TOKEN_RELEASE_COMPONENT_DEFINITION";
		}
		case VERSION_TOKEN_RELEASE_REVISION_SEPARATOR:
		{
			return "VERSION_TOKEN_RELEASE_REVISION_SEPARATOR";
		}
		case VERSION_TOKEN_BUILD_WORD:
		{
			return "VERSION_TOKEN_BUILD_WORD";
		}
		case VERSION_TOKEN_BUILD_VALUE:
		{
			return "VERSION_TOKEN_BUILD_VALUE";
		}
		case VERSION_TOKEN_BUILD_SEPARATOR:
		{
			return "VERSION_TOKEN_BUILD_SEPARATOR";
		}
		case VERSION_TOKEN_METADATA_SEPARATOR:
		{
			return "VERSION_TOKEN_METADATA_SEPARATOR";
		}
		case VERSION_TOKEN_GENERIC_SEPARATOR:
		{
			return "VERSION_TOKEN_GENERIC_SEPARATOR";
		}
		case VERSION_TOKEN_GENERIC_COMPONENT_DEFINITION:
		{
			return "VERSION_TOKEN_GENERIC_COMPONENT_DEFINITION";
		}
		default:
		{
			return "UNKNOWN TOKEN ID";
		}
	}
}

#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM