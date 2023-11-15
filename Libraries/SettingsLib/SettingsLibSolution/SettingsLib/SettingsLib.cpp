#include "pch.h"
#include "SettingsLib.hpp"

std::vector<std::string> chkConfigField(std::fstream& config, std::string fieldName, long long* errorStatus)
{
	std::vector<std::string> configFieldData;

	if (!config.is_open())
	{
		if (errorStatus != nullptr)
		{
			*errorStatus = SettingsFieldErrorStatus::SETTINGS_FIELD_STATUS_FILE_NOT_OPENED;
		}

		return configFieldData;
	}

	bool isCorrectField = false;
	bool isActualLineField = false;
	bool isActualLineComment = false;
	bool isActualLineConfigFieldData = false;

	std::string line;
	std::string field = SETTINGS_OPEN_FIELD + fieldName + SETTINGS_CLOSE_FIELD;
	while (std::getline(config, line))
	{
		isActualLineField = false;
		isActualLineComment = false;
		isActualLineConfigFieldData = false;

		// Check for commented line
		long long commentIndex = findCommentInLine(line);

		if (commentIndex == 0)
		{
			isActualLineComment = true;
		}

		if (!isActualLineComment)
		{
			// Check if the current line is the field that is locking for or is another field
			switch (isConfigField(line, fieldName))
			{
				case 1:			// Found another field
				{
					isCorrectField = false;
					isActualLineField = true;
					break;
				}
				case 2:			// Found correct field
				{
					isCorrectField = true;
					isActualLineField = true;
					break;
				}
				default:		// Assume a possible line with configuration data
				{
					break;
				}
			}

			// If the field was found and no other field was detected, verify if is possible to extract the data
			if (isCorrectField && !isActualLineField)
			{
				if (commentIndex > 0)
				{
					line = line.substr(0, commentIndex);
				}

				int dataStatus = isLineDataExtractable(line);

				if (dataStatus == 2)
				{
					isActualLineConfigFieldData = true;
				}
			}

			// If the data is extractable:
			if (isActualLineConfigFieldData && !isActualLineField)
			{
				configFieldData.push_back(line);
			}
		}
	}

	return configFieldData;
}

int isConfigField(std::string& line, std::string& fieldName)
{
	bool hasFieldOpenMark = false;
	bool hasFieldCloseMark = false;
	size_t open = 0;
	size_t close = 0;

	for (size_t i = 0; i < line.size(); i++)
	{
		if (line[i] == SETTINGS_OPEN_FIELD)
		{
			hasFieldOpenMark = true;
			open = i + 1;	// Go to first char inside the field
		}

		if (line[i] == SETTINGS_CLOSE_FIELD)
		{
			hasFieldCloseMark = true;
			close = i - 1;	// Go to last char inside the field
		}
	}

	if (hasFieldOpenMark && hasFieldCloseMark)
	{
		if (open >= 0 && close > 0 && close > open)
		{
			std::string testFieldName = line.substr(open, close);

			if (fieldName == testFieldName)
			{
				return 2;						// Found correct field
			}

			return 1;							// Not the correct field
		}
	}

	return 0;									// Fail to test the field
}

int isLineDataExtractable(std::string& lineTest)
{
	bool foundDataMark = false;
	std::string dataTest;

	for (size_t i = 0; i < lineTest.size(); i++)
	{
		if (foundDataMark)
		{
			dataTest = lineTest.substr(i);
		}

		if (lineTest[i] == SETTINGS_DATA_MARK)
		{
			foundDataMark = true;
		}
	}

	if (!dataTest.empty())
	{
		return 2;
		//try
		//{
		//	[[maybe_unused]] long long l = std::stoll(dataTest);
		//	return 2;	// The line has a extractable data
		//}
		//catch (const std::invalid_argument& e)
		//{
		//	return 1;	// The line has a invalid value data to extract
		//}
	}

	return 0;			// The line doesn't have a possible data to extract
}

long long findCommentInLine(std::string& line)
{
	//bool foundValidChar = false;
	bool foundNonSpaceChar = false;
	bool foundCommentMark = false;
	//bool isLineCompletedCommented = false;

	long long result = -1;

	for (size_t i = 0; i < line.size(); i++)
	{
		if (line[i] != ' ' && !foundNonSpaceChar)
		{
			foundNonSpaceChar = true;
		}
		
		if (foundNonSpaceChar)
		{
			if (line[i] == SETTINGS_COMMENT_MARK || line[i] == SETTINGS_COMMENT_MARK2)
			{
				foundCommentMark = true;
				result = i;
			}
		}
	}

	return result;	// Return the comment mark if exist or -1 if was not found
}

std::map<std::string, ConfigData> mapConfigData(std::vector<ConfigData>& configDataV, bool ignoreCheck)
{
	std::map<std::string, ConfigData> fieldConfigs;

	for (size_t i = 0; i < configDataV.size(); i++)
	{
		if (configDataV[i].isValidConfig() && !ignoreCheck)
		{
			fieldConfigs.insert({configDataV[i].getConfigId(), configDataV[i]});
		}
		else
		{
			fieldConfigs.insert({configDataV[i].getConfigId(), configDataV[i]});
		}
	}

	return fieldConfigs;
}

std::map<std::string, ConfigData> mapConfigData(std::vector<std::string>& rawConfigDataV, std::vector<std::string>* validConfigList, bool ignoreCheck)
{
	std::map<std::string, ConfigData> fieldConfigs;

	for (std::string& s : rawConfigDataV)
	{
		ConfigData c(s, validConfigList);

		if (c.isValidConfig() && !ignoreCheck)
		{
			fieldConfigs.insert({c.getConfigId(), c});
		}
		
		if (ignoreCheck)
		{
			fieldConfigs.insert({c.getConfigId(), c});
		}
	}

	return fieldConfigs;
}

bool findSetting(std::map<std::string, ConfigData>& configMap, std::string configId, ConfigData* pConfigData)
{
	try
	{
		ConfigData* p = &configMap.at(configId);

		if (pConfigData != nullptr)
		{
			pConfigData = p;
		}

		return true;
	}
	catch (const std::out_of_range&)
	{
		return false;
	}
}

ConfigData::ConfigData(std::string configLine, std::vector<std::string>* validConfigList)
{
	this->errCode = ConfigDataErrorStatus::CONFIG_DATA_ERROR_STATUS_OK;
	this->isConfigOk = false;
	this->data.ull = 0ull;

	std::string data;

	bool foundDataSetMark = false;
	bool chkForId = true;
	bool chkForData = false;
	bool foundComment = false;
	bool foundValidChar = false;

	for (size_t i = 0; i < configLine.size(); i++)
	{
		// Jump the first chars with space
		if (configLine[i] != ' ' && !foundValidChar)
		{
			foundValidChar = true;
		}

		// Can't have space in configuration id
		if (configLine[i] == ' ' && foundValidChar && !foundComment && !foundDataSetMark && chkForId)
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
					this->type = ConfigData::ConfigDataType::INTERGER;
					this->data.ll = std::stoll(data);
				}
				catch (const std::invalid_argument& e)
				{
					this->type = ConfigData::ConfigDataType::CONFIG_DATA_FAIL;
					this->data.ll = 0ll;
					this->strData = e.what();
				}
			}
			else if (isFpNumber)
			{
				try
				{
					// Convert to float point number:
					this->type = ConfigData::ConfigDataType::FLOAT;
					this->data.d = std::stod(data);
				}
				catch (const std::invalid_argument& e)
				{
					this->type = ConfigData::ConfigDataType::CONFIG_DATA_FAIL;
					this->data.d = 0.0;
					this->strData = e.what();
				}
			}
			else
			{
				// Fail to identify correctly, keep it as string:
				this->type = ConfigData::ConfigDataType::STRING;
				this->strData = data;
			}
		}
		else
		{
			this->type = ConfigData::ConfigDataType::STRING;
			this->strData = data;
			isString = true;	// Test if the string contains a possible boolean information
		}
	}
	else if (isString)
	{
		this->type = ConfigData::ConfigDataType::STRING;
		this->strData = data;
	}
	else
	{
		this->type = ConfigData::ConfigDataType::CONFIG_DATA_EMPTY;
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
			this->type = ConfigData::ConfigDataType::BOOLEAN;
			this->strData.clear();
			this->data.b = false;
		}

		if (std::strcmp(bTest.data(), SETTINGS_DATA_TYPE_BOOL_TRUE) == 0)
		{
			this->type = ConfigData::ConfigDataType::BOOLEAN;
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

ConfigData::ConfigData(const ConfigData& other)
{
	this->type = other.type;
	this->idName = other.idName;
	this->errCode = other.errCode;
	this->isConfigOk = other.isConfigOk;

	if (this->type == ConfigData::ConfigDataType::CONFIG_DATA_FAIL)
	{
		this->data.ull = 0ull;
		this->strData = other.strData;
	}

	if (this->type == ConfigData::ConfigDataType::CONFIG_DATA_EMPTY)
	{
		this->data.ull = 0ull;
	}
	
	if (this->type == ConfigData::ConfigDataType::UNSIGNED_INTEGER)
	{
		this->data.ull = other.data.ull;
	}
	
	if (this->type == ConfigData::ConfigDataType::INTERGER)
	{
		this->data.ll = other.data.ll;
	}
	
	if (this->type == ConfigData::ConfigDataType::FLOAT)
	{
		this->data.d = other.data.d;
	}

	if (this->type == ConfigData::ConfigDataType::STRING)
	{
		this->strData = other.strData;
	}

	if (this->type == ConfigData::ConfigDataType::BOOLEAN)
	{
		this->data.b = other.data.b;
	}

	if (this->errCode > ConfigDataErrorStatus::CONFIG_DATA_ERROR_STATUS_OK)
	{
		this->strData = other.strData;
	}
}

ConfigData::ConfigData(ConfigData&& other) noexcept
{
	this->type = other.type;
	this->idName = other.idName;
	this->errCode = other.errCode;
	this->isConfigOk = other.isConfigOk;

	if (other.type == ConfigData::ConfigDataType::CONFIG_DATA_FAIL)
	{
		this->data.ull = 0ull;
		this->strData = other.strData;
	}

	if (this->type == ConfigData::ConfigDataType::CONFIG_DATA_EMPTY)
	{
		this->data.ull = 0ull;
	}
	
	if (this->type == ConfigData::ConfigDataType::UNSIGNED_INTEGER)
	{
		this->data.ull = other.data.ull;
	}
	
	if (this->type == ConfigData::ConfigDataType::INTERGER)
	{
		this->data.ll = other.data.ll;
	}
	
	if (this->type == ConfigData::ConfigDataType::FLOAT)
	{
		this->data.d = other.data.d;
	}

	if (other.type == ConfigData::ConfigDataType::STRING)
	{
		this->strData = other.strData;
	}

	if (this->type == ConfigData::ConfigDataType::BOOLEAN)
	{
		this->data.b = other.data.b;
	}

	if (this->errCode > ConfigDataErrorStatus::CONFIG_DATA_ERROR_STATUS_OK)
	{
		this->strData = other.strData;
	}

	other.~ConfigData();
}

ConfigData::~ConfigData()
{
}

ConfigData& ConfigData::operator=(const ConfigData& other)
{
	this->type = other.type;
	this->idName = other.idName;
	this->errCode = other.errCode;
	this->isConfigOk = other.isConfigOk;

	if (other.type == ConfigData::ConfigDataType::CONFIG_DATA_FAIL)
	{
		this->data.ull = 0ull;
		this->strData = other.strData;
	}

	if (this->type == ConfigData::ConfigDataType::CONFIG_DATA_EMPTY)
	{
		this->data.ull = 0ull;
	}
	
	if (this->type == ConfigData::ConfigDataType::UNSIGNED_INTEGER)
	{
		this->data.ull = other.data.ull;
	}
	
	if (this->type == ConfigData::ConfigDataType::INTERGER)
	{
		this->data.ll = other.data.ll;
	}
	
	if (this->type == ConfigData::ConfigDataType::FLOAT)
	{
		this->data.d = other.data.d;
	}

	if (other.type == ConfigData::ConfigDataType::STRING)
	{
		this->strData = other.strData;
	}

	if (this->type == ConfigData::ConfigDataType::BOOLEAN)
	{
		this->data.b = other.data.b;
	}

	if (this->errCode > ConfigDataErrorStatus::CONFIG_DATA_ERROR_STATUS_OK)
	{
		this->strData = other.strData;
	}

	return *this;
}

ConfigData& ConfigData::operator=(ConfigData&& other) noexcept
{
	this->type = other.type;
	this->idName = other.idName;
	this->errCode = other.errCode;
	this->isConfigOk = other.isConfigOk;

	if (other.type == ConfigData::ConfigDataType::CONFIG_DATA_FAIL)
	{
		this->data.ull = 0ull;
		this->strData = other.strData;
	}

	if (this->type == ConfigData::ConfigDataType::CONFIG_DATA_EMPTY)
	{
		this->data.ull = 0ull;
	}
	
	if (this->type == ConfigData::ConfigDataType::UNSIGNED_INTEGER)
	{
		this->data.ull = other.data.ull;
	}
	
	if (this->type == ConfigData::ConfigDataType::INTERGER)
	{
		this->data.ll = other.data.ll;
	}
	
	if (this->type == ConfigData::ConfigDataType::FLOAT)
	{
		this->data.d = other.data.d;
	}

	if (other.type == ConfigData::ConfigDataType::STRING)
	{
		this->strData = other.strData;
	}

	if (this->type == ConfigData::ConfigDataType::BOOLEAN)
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

bool ConfigData::operator==(const ConfigData& other) const
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
			case ConfigData::ConfigDataType::CONFIG_DATA_FAIL:
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
			case ConfigData::ConfigDataType::CONFIG_DATA_EMPTY:
			{
				if (this->errCode != other.errCode)
				{
					isEqual = false;
				}
				break;
			}
			case ConfigData::ConfigDataType::UNSIGNED_INTEGER:
			{
				if (this->data.ull != other.data.ull)
				{
					isEqual = false;
				}
				break;
			}
			case ConfigData::ConfigDataType::INTERGER:
			{
				if (this->data.ll != other.data.ll)
				{
					isEqual = false;
				}
				break;
			}
			case ConfigData::ConfigDataType::FLOAT:
			{
				if (this->data.d != other.data.d)
				{
					isEqual = false;
				}
				break;
			}
			case ConfigData::ConfigDataType::STRING:
			{
				if (this->strData != other.strData)
				{
					isEqual = false;
				}
				break;
			}
			case ConfigData::ConfigDataType::BOOLEAN:
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

std::string ConfigData::getConfigId()
{
	return this->idName;
}

bool ConfigData::isValidConfig()
{
	return this->isConfigOk;
}

bool ConfigData::isValidConfig(std::vector<std::string>* validConfigList)
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

int ConfigData::getConfigDataType()
{
	return this->type;
}

bool ConfigData::getConfigData(unsigned long long& data)
{
	if (this->type == ConfigData::ConfigDataType::UNSIGNED_INTEGER)
	{
		data = this->data.ull;
		return true;
	}

	return false;
}

bool ConfigData::getConfigData(long long& data)
{
	if (this->type == ConfigData::ConfigDataType::INTERGER)
	{
		data = this->data.ll;
		return true;
	}

	return false;
}

bool ConfigData::getConfigData(double& data)
{
	if (this->type == ConfigData::ConfigDataType::FLOAT)
	{
		data = this->data.d;
		return true;
	}

	return false;
}

bool ConfigData::getConfigData(bool& data)
{
	if (this->type == ConfigData::ConfigDataType::BOOLEAN)
	{
		data = this->data.b;
		return true;
	}

	return false;
}

bool ConfigData::getConfigData(std::string& data)
{
	if (this->type == ConfigData::ConfigDataType::STRING)
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

bool ConfigData::setConfigData(unsigned long long& data)
{
	if (this->type == ConfigData::ConfigDataType::UNSIGNED_INTEGER)
	{
		this->data.ull = data;
		return true;
	}

	return false;
}

bool ConfigData::setConfigData(long long& data)
{
	if (this->type == ConfigData::ConfigDataType::INTERGER)
	{
		this->data.ll = data;
		return true;
	}

	return false;
}

bool ConfigData::setConfigData(double& data)
{
	if (this->type == ConfigData::ConfigDataType::FLOAT)
	{
		this->data.d = data;
		return true;
	}

	return false;
}

bool ConfigData::setConfigData(bool& data)
{
	if (this->type == ConfigData::ConfigDataType::BOOLEAN)
	{
		this->data.b = data;
		return true;
	}

	return false;
}

bool ConfigData::setConfigData(std::string& data)
{
	if (this->type == ConfigData::ConfigDataType::STRING)
	{
		this->strData = data;
		return true;
	}

	return false;
}
