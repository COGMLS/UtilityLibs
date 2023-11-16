#include "pch.h"
#include "SettingsLibTools.hpp"

std::vector<std::string> SettingsLib::Tools::chkConfigField(std::fstream& config, std::string fieldName, long long* errorStatus)
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

int SettingsLib::Tools::isConfigField(std::string& line, std::string& fieldName)
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

int SettingsLib::Tools::isLineDataExtractable(std::string& lineTest)
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

long long SettingsLib::Tools::findCommentInLine(std::string& line)
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

std::map<std::string, SettingsLib::ConfigData> SettingsLib::Tools::mapConfigData(std::vector<SettingsLib::ConfigData>& configDataV, bool ignoreCheck)
{
	std::map<std::string, SettingsLib::ConfigData> fieldConfigs;

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

std::map<std::string, SettingsLib::ConfigData> SettingsLib::Tools::mapConfigData(std::vector<std::string>& rawConfigDataV, std::vector<std::string>* validConfigList, bool ignoreCheck)
{
	std::map<std::string, SettingsLib::ConfigData> fieldConfigs;

	for (std::string& s : rawConfigDataV)
	{
		SettingsLib::ConfigData c(s, validConfigList);

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

bool SettingsLib::Tools::findSetting(std::map<std::string, SettingsLib::ConfigData>& configMap, std::string configId, SettingsLib::ConfigData* pConfigData)
{
	try
	{
		SettingsLib::ConfigData* p = &configMap.at(configId);

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