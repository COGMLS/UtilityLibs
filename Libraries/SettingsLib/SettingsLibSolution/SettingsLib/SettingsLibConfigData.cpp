#include "pch.h"
#include "SettingsLibConfigData.hpp"

void SettingsLib::ConfigData::setException(std::exception e)
{
	this->clearException();
	this->exceptInfo = new std::exception(e);
}

SettingsLib::ConfigData::ConfigData(std::string configLine, std::vector<std::string>* validConfigList)
{
	this->errCode = ConfigDataErrorStatus::CONFIG_DATA_ERROR_STATUS_OK;
	this->isConfigOk = false;
	this->data.ull = 0ull;

	this->exceptInfo = nullptr;

	std::string data;

	bool foundDataSetMark = false;
	bool chkForId = true;
	bool chkForData = false;
	bool foundComment = false;
	bool foundValidChar = false;

	for (size_t i = 0; i < configLine.size(); i++)
	{
		// Jump the first chars with space
		if (configLine[i] != SETTINGS_SPACE_CHAR && !foundValidChar)
		{
			foundValidChar = true;
		}

		// Can't have space in configuration id
		if (configLine[i] == SETTINGS_SPACE_CHAR && foundValidChar && !foundComment && !foundDataSetMark && chkForId)
		{
			this->errCode = ConfigDataErrorStatus::CONFIG_DATA_ERROR_STATUS_CONFIG_COMMENTED;
			this->isConfigOk = false;
			this->idName = SETTINGS_CONFIG_DATA_ID_FAIL;
			this->strData = SETTINGS_CONFIG_DATA_STR_DATA_FAIL;
			break;
		}

		// When a commentary mark appears, consider everything a comment after that
		if (configLine[i] == SETTINGS_COMMENT_MARK || configLine[i] == SETTINGS_COMMENT_MARK2)
		{
			foundComment = true;
			break;
		}

		// When found a data mark set '=' start to identify the data
		if (configLine[i] == SETTINGS_DATA_MARK)
		{
			foundDataSetMark = true;
			chkForId = false;

			if (i + 1 < configLine.size())
			{
				i++;
				chkForData = true;
			}
		}

		if (chkForId && !foundComment && foundValidChar)
		{
			this->idName += configLine[i];
		}

		if (chkForData && !foundComment)
		{
			data += configLine[i];
		}
	}

	// Check for the data type:

	// Start assuming is a possible digit the configuration data:

	bool isDigit = true;
	bool isInteger = true;
	bool isFpNumber = true;
	bool isString = false;
	bool isBoolean = false;
	
	// Control if a negative signal was found
	bool foundNegativeSignal = false;
	
	// Counters to identify possible integers or float points:

	unsigned int decimalDotCounter = 0;
	unsigned int expCounter = 0;
	unsigned int negativeNumberCounter = 0;
	unsigned int literalDoubleQuoteCounter = 0;

	if (!data.empty())
	{
		for (size_t i = 0; i < data.size(); i++)
		{
			// Identify a literal string
			if (data[i] == SETTINGS_DATA_TYPE_STRING)
			{
				isString = true;
				isDigit = false;
				isInteger = false;
				isFpNumber = false;
			}

			if (isDigit && (isFpNumber || isInteger))
			{
				if (data[i] == SETTINGS_DATA_TYPE_NEGATIVE_SIGNAL)
				{
					negativeNumberCounter++;
					foundNegativeSignal = true;
				}

				if (data[i] != SETTINGS_DATA_TYPE_EXPONENT_LOWER && data[i] != SETTINGS_DATA_TYPE_EXPONENT_UPPER && data[i] != SETTINGS_DATA_TYPE_DECIMAL && data[i] != SETTINGS_DATA_TYPE_NEGATIVE_SIGNAL)
				{
					if (std::isdigit(data[i]) == 0 && data[i] != EOF)
					{
						isDigit = false;
					}

					if (data[i] == EOF)
					{
						break;
					}
				}

				if (data[i] == SETTINGS_DATA_TYPE_DECIMAL)
				{
					decimalDotCounter++;

					if (isInteger)
					{
						isInteger = false;
					}
				}

				if (data[i] == SETTINGS_DATA_TYPE_EXPONENT_LOWER || data[i] == SETTINGS_DATA_TYPE_EXPONENT_UPPER)
				{
					expCounter++;
					
					if (isInteger)
					{
						isInteger = false;
					}
				}

				if (isFpNumber && (decimalDotCounter > 1 || expCounter > 1))
				{
					isFpNumber = false;
					isInteger = false;
					isDigit = false;
				}

				if (foundNegativeSignal && (isFpNumber && !isInteger && negativeNumberCounter > 2) || (isInteger && isFpNumber && negativeNumberCounter > 1))
				{
					isDigit = false;
					isInteger = false;
					isFpNumber = false;
				}
			}
			else
			{
				break;
			}
		}

		// Check if is a number end if is, check if is a possible decimal number

		if (isDigit)
		{
			bool isDigitStr = false;

			if (isInteger)
			{
				try
				{
					// Convert to integer number:
					this->type = SettingsLib::ConfigDataType::SETTINGS_LIB_INTERGER;
					this->data.ll = std::stoll(data);
				}
				catch (const std::invalid_argument& e)
				{
					this->type = SettingsLib::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_FAIL;
					this->data.ll = 0ll;
					this->setException(e);
				}
			}
			else if (isFpNumber)
			{
				try
				{
					// Convert to float point number:
					this->type = SettingsLib::ConfigDataType::SETTINGS_LIB_FLOAT;
					this->data.d = std::stod(data);
				}
				catch (const std::invalid_argument& e)
				{
					this->type = SettingsLib::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_FAIL;
					this->data.d = 0.0;
					this->setException(e);
				}
			}
			else
			{
				// Fail to identify correctly, keep it as string:
				this->type = SettingsLib::ConfigDataType::SETTINGS_LIB_STRING;
				this->strData = data;
			}
		}
		else
		{
			this->type = SettingsLib::ConfigDataType::SETTINGS_LIB_STRING;
			this->strData = data;
			isString = true;	// Test if the string contains a possible boolean information
		}
	}
	else if (isString)
	{
		this->type = SettingsLib::ConfigDataType::SETTINGS_LIB_STRING;
		this->strData = data;
	}
	else
	{
		this->type = SettingsLib::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_EMPTY;
		this->errCode = ConfigDataErrorStatus::CONFIG_DATA_ERROR_STATUS_CONFIG_DATA_EMPTY;
	}

	if (isString)
	{
		// Test if the string has a boolean information:

		std::string bTest;

		for (size_t i = 0; i < data.size(); i++)
		{
			if (data[i] != SETTINGS_SPACE_CHAR && data[i] != SETTINGS_NEW_LINE)
			{
				if (std::isalnum(data[i]))
				{
					try
					{
						bTest += std::tolower(data[i]);
					}
					catch (const std::exception&)
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
		}

		if (std::strcmp(bTest.data(), SETTINGS_DATA_TYPE_BOOL_FALSE) == 0)
		{
			this->type = SettingsLib::ConfigDataType::SETTINGS_LIB_BOOLEAN;
			this->strData.clear();
			this->data.b = false;
		}

		if (std::strcmp(bTest.data(), SETTINGS_DATA_TYPE_BOOL_TRUE) == 0)
		{
			this->type = SettingsLib::ConfigDataType::SETTINGS_LIB_BOOLEAN;
			this->strData.clear();
			this->data.b = true;
		}
	}

	// If a valid configuration list was not passed, assume nothing
	if (validConfigList != nullptr)
	{
		for (const std::string& s : *validConfigList)
		{
			if (this->idName == s)
			{
				this->isConfigOk = true;
				break;
			}
		}
	}
}

SettingsLib::ConfigData::ConfigData(const ConfigData& other)
{
	this->type = other.type;
	this->idName = other.idName;
	this->errCode = other.errCode;
	this->isConfigOk = other.isConfigOk;

	if (other.exceptInfo != nullptr)
	{
		this->exceptInfo = new std::exception(*other.exceptInfo);
	}
	else
	{
		this->exceptInfo = nullptr;
	}

	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_FAIL)
	{
		this->data.ull = 0ull;
		this->strData = other.strData;
	}

	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_EMPTY)
	{
		this->data.ull = 0ull;
	}
	
	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_UNSIGNED_INTEGER)
	{
		this->data.ull = other.data.ull;
	}
	
	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_INTERGER)
	{
		this->data.ll = other.data.ll;
	}
	
	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_FLOAT)
	{
		this->data.d = other.data.d;
	}

	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_STRING)
	{
		this->strData = other.strData;
	}

	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_BOOLEAN)
	{
		this->data.b = other.data.b;
	}

	if (this->errCode > ConfigDataErrorStatus::CONFIG_DATA_ERROR_STATUS_OK)
	{
		this->strData = other.strData;
	}
}

SettingsLib::ConfigData::ConfigData(ConfigData&& other) noexcept
{
	this->type = other.type;
	this->idName = other.idName;
	this->errCode = other.errCode;
	this->isConfigOk = other.isConfigOk;

	if (other.exceptInfo != nullptr)
	{
		this->exceptInfo = new std::exception(*other.exceptInfo);
	}
	else
	{
		this->exceptInfo = nullptr;
	}

	if (other.type == SettingsLib::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_FAIL)
	{
		this->data.ull = 0ull;
		this->strData = other.strData;
	}

	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_EMPTY)
	{
		this->data.ull = 0ull;
	}
	
	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_UNSIGNED_INTEGER)
	{
		this->data.ull = other.data.ull;
	}
	
	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_INTERGER)
	{
		this->data.ll = other.data.ll;
	}
	
	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_FLOAT)
	{
		this->data.d = other.data.d;
	}

	if (other.type == SettingsLib::ConfigDataType::SETTINGS_LIB_STRING)
	{
		this->strData = other.strData;
	}

	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_BOOLEAN)
	{
		this->data.b = other.data.b;
	}

	if (this->errCode > ConfigDataErrorStatus::CONFIG_DATA_ERROR_STATUS_OK)
	{
		this->strData = other.strData;
	}

	other.~ConfigData();
}

SettingsLib::ConfigData::~ConfigData()
{
	if (this->exceptInfo != nullptr)
	{
		delete this->exceptInfo;
		this->exceptInfo = nullptr;
	}
}

SettingsLib::ConfigData& SettingsLib::ConfigData::operator=(const ConfigData& other)
{
	this->type = other.type;
	this->idName = other.idName;
	this->errCode = other.errCode;
	this->isConfigOk = other.isConfigOk;

	if (other.exceptInfo != nullptr)
	{
		this->exceptInfo = new std::exception(*other.exceptInfo);
	}
	else
	{
		this->exceptInfo = nullptr;
	}

	if (other.type == SettingsLib::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_FAIL)
	{
		this->data.ull = 0ull;
		this->strData = other.strData;
	}

	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_EMPTY)
	{
		this->data.ull = 0ull;
	}
	
	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_UNSIGNED_INTEGER)
	{
		this->data.ull = other.data.ull;
	}
	
	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_INTERGER)
	{
		this->data.ll = other.data.ll;
	}
	
	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_FLOAT)
	{
		this->data.d = other.data.d;
	}

	if (other.type == SettingsLib::ConfigDataType::SETTINGS_LIB_STRING)
	{
		this->strData = other.strData;
	}

	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_BOOLEAN)
	{
		this->data.b = other.data.b;
	}

	if (this->errCode > ConfigDataErrorStatus::CONFIG_DATA_ERROR_STATUS_OK)
	{
		this->strData = other.strData;
	}

	return *this;
}

SettingsLib::ConfigData& SettingsLib::ConfigData::operator=(ConfigData&& other) noexcept
{
	this->type = other.type;
	this->idName = other.idName;
	this->errCode = other.errCode;
	this->isConfigOk = other.isConfigOk;

	if (other.exceptInfo != nullptr)
	{
		this->exceptInfo = new std::exception(*other.exceptInfo);
	}
	else
	{
		this->exceptInfo = nullptr;
	}

	if (other.type == SettingsLib::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_FAIL)
	{
		this->data.ull = 0ull;
		this->strData = other.strData;
	}

	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_EMPTY)
	{
		this->data.ull = 0ull;
	}
	
	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_UNSIGNED_INTEGER)
	{
		this->data.ull = other.data.ull;
	}
	
	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_INTERGER)
	{
		this->data.ll = other.data.ll;
	}
	
	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_FLOAT)
	{
		this->data.d = other.data.d;
	}

	if (other.type == SettingsLib::ConfigDataType::SETTINGS_LIB_STRING)
	{
		this->strData = other.strData;
	}

	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_BOOLEAN)
	{
		this->data.b = other.data.b;
	}

	if (this->errCode > ConfigDataErrorStatus::CONFIG_DATA_ERROR_STATUS_OK)
	{
		this->strData = other.strData;
	}

	other.~ConfigData();

	return *this;
}

bool SettingsLib::ConfigData::operator==(const ConfigData& other) const
{
	if (this->idName != other.idName)
	{
		return false;
	}

	if (this->isConfigOk != other.isConfigOk)
	{
		return false;
	}

	bool isEqual = true;

	// Check if types are different

	if (this->type != other.type)
	{
		isEqual = false;
	}
	else
	{
		// Check if the data is different
		switch (this->type)
		{
			case SettingsLib::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_FAIL:
			{
				if (this->errCode == other.errCode)
				{
					if (this->strData != other.strData)
					{
						isEqual = false;
					}
				}
				else
				{
					isEqual = false;
				}
				break;
			}
			case SettingsLib::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_EMPTY:
			{
				if (this->errCode != other.errCode)
				{
					isEqual = false;
				}
				break;
			}
			case SettingsLib::ConfigDataType::SETTINGS_LIB_UNSIGNED_INTEGER:
			{
				if (this->data.ull != other.data.ull)
				{
					isEqual = false;
				}
				break;
			}
			case SettingsLib::ConfigDataType::SETTINGS_LIB_INTERGER:
			{
				if (this->data.ll != other.data.ll)
				{
					isEqual = false;
				}
				break;
			}
			case SettingsLib::ConfigDataType::SETTINGS_LIB_FLOAT:
			{
				if (this->data.d != other.data.d)
				{
					isEqual = false;
				}
				break;
			}
			case SettingsLib::ConfigDataType::SETTINGS_LIB_STRING:
			{
				if (this->strData != other.strData)
				{
					isEqual = false;
				}
				break;
			}
			case SettingsLib::ConfigDataType::SETTINGS_LIB_BOOLEAN:
			{
				if (this->data.b != other.data.b)
				{
					isEqual = false;
				}
				break;
			}
			default:
			{
				isEqual = false;
				break;
			}
		}
	}

	return isEqual;
}

std::string SettingsLib::ConfigData::getConfigId()
{
	return this->idName;
}

bool SettingsLib::ConfigData::isValidConfig()
{
	return this->isConfigOk;
}

bool SettingsLib::ConfigData::isValidConfig(std::vector<std::string>* validConfigList)
{
	if (validConfigList != nullptr)
	{
		for (std::string& s : *validConfigList)
		{
			if (s == this->idName)
			{
				this->isConfigOk = true;
				break;
			}
		}
	}

	return this->isConfigOk;
}

bool SettingsLib::ConfigData::foundException()
{
	if (this->exceptInfo != nullptr)
	{
		return true;
	}

	return false;
}

std::exception SettingsLib::ConfigData::getException()
{
	if (this->foundException())
	{
		return std::exception(*this->exceptInfo);
	}

	return std::exception();
}

void SettingsLib::ConfigData::clearException()
{
	if (this->exceptInfo != nullptr)
	{
		delete this->exceptInfo;
		this->exceptInfo = nullptr;
	}
}

SettingsLib::ConfigDataType SettingsLib::ConfigData::getConfigDataType()
{
	return this->type;
}

bool SettingsLib::ConfigData::getConfigData(unsigned long long& data)
{
	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_UNSIGNED_INTEGER)
	{
		data = this->data.ull;
		return true;
	}

	return false;
}

bool SettingsLib::ConfigData::getConfigData(unsigned long long* data)
{
	if (data != nullptr)
	{
		if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_UNSIGNED_INTEGER)
		{
			*data = this->data.ull;
			return true;
		}
	}

	return false;
}

bool SettingsLib::ConfigData::getConfigData(long long& data)
{
	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_INTERGER)
	{
		data = this->data.ll;
		return true;
	}

	return false;
}

bool SettingsLib::ConfigData::getConfigData(long long* data)
{
	if (data != nullptr)
	{
		if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_INTERGER)
		{
			*data = this->data.ll;
			return true;
		}
	}

	return false;
}

bool SettingsLib::ConfigData::getConfigData(double& data)
{
	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_FLOAT)
	{
		data = this->data.d;
		return true;
	}

	return false;
}

bool SettingsLib::ConfigData::getConfigData(double* data)
{
	if (data != nullptr)
	{
		if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_FLOAT)
		{
			*data = this->data.d;
			return true;
		}
	}

	return false;
}

bool SettingsLib::ConfigData::getConfigData(bool& data)
{
	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_BOOLEAN)
	{
		data = this->data.b;
		return true;
	}

	return false;
}

bool SettingsLib::ConfigData::getConfigData(bool* data)
{
	if (data != nullptr)
	{
		if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_BOOLEAN)
		{
			*data = this->data.b;
			return true;
		}
	}

	return false;
}

bool SettingsLib::ConfigData::getConfigData(std::string& data)
{
	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_STRING)
	{
		data = this->strData;
		return true;
	}

	if (!this->strData.empty())
	{
		data = this->strData;
	}

	return false;
}

bool SettingsLib::ConfigData::getConfigData(std::string* data)
{
	if (data != nullptr)
	{
		if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_STRING)
		{
			*data = this->strData;
			return true;
		}

		//if (!this->strData.empty())
		//{
		//	*data = this->strData;
		//}
	}

	return false;
}

bool SettingsLib::ConfigData::setConfigData(unsigned long long& data)
{
	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_UNSIGNED_INTEGER)
	{
		this->data.ull = data;
		return true;
	}

	return false;
}

bool SettingsLib::ConfigData::setConfigData(unsigned long long* data)
{
	if (data != nullptr)
	{
		if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_UNSIGNED_INTEGER)
		{
			this->data.ull = *data;
			return true;
		}
	}

	return false;
}

bool SettingsLib::ConfigData::setConfigData(long long& data)
{
	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_INTERGER)
	{
		this->data.ll = data;
		return true;
	}

	return false;
}

bool SettingsLib::ConfigData::setConfigData(long long* data)
{
	if (data != nullptr)
	{
		if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_INTERGER)
		{
			this->data.ll = *data;
			return true;
		}
	}

	return false;
}

bool SettingsLib::ConfigData::setConfigData(double& data)
{
	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_FLOAT)
	{
		this->data.d = data;
		return true;
	}

	return false;
}

bool SettingsLib::ConfigData::setConfigData(double* data)
{
	if (data != nullptr)
	{
		if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_FLOAT)
		{
			this->data.d = *data;
			return true;
		}
	}

	return false;
}

bool SettingsLib::ConfigData::setConfigData(bool& data)
{
	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_BOOLEAN)
	{
		this->data.b = data;
		return true;
	}

	return false;
}

bool SettingsLib::ConfigData::setConfigData(bool* data)
{
	if (data != nullptr)
	{
		if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_BOOLEAN)
		{
			this->data.b = *data;
			return true;
		}
	}

	return false;
}

bool SettingsLib::ConfigData::setConfigData(std::string& data)
{
	if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_STRING)
	{
		this->strData = data;
		return true;
	}

	return false;
}

bool SettingsLib::ConfigData::setConfigData(std::string* data)
{
	if (data != nullptr)
	{
		if (this->type == SettingsLib::ConfigDataType::SETTINGS_LIB_STRING)
		{
			this->strData = *data;
			return true;
		}
	}

	return false;
}
