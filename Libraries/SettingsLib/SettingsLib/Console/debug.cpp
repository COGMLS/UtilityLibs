#include "debug.hpp"

std::string translateIniLineCheckStatus(SettingsLib::ErrorCodes::IniLineCheckStatus code)
{
	std::string msg = "";

	switch (code)
	{
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_UNKNOWN_ERROR:
		{
			msg = "SETTINGS_INI_LINE_CHECK_UNKNOWN_ERROR";
			break;
		}
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_NULLPTR_ERROR:
		{
			msg = "SETTINGS_INI_LINE_CHECK_NULLPTR_ERROR";
			break;
		}
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_KEY_SYNTAX_ERROR:
		{
			msg = "SETTINGS_INI_LINE_CHECK_KEY_SYNTAX_ERROR";
			break;
		}
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_SECTION_SYNTAX_ERROR:
		{
			msg = "SETTINGS_INI_LINE_CHECK_SECTION_SYNTAX_ERROR";
			break;
		}
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTIGNS_INI_LINE_CHECK_GENERAL_SYNTAX_ERROR:
		{
			msg = "SETTIGNS_INI_LINE_CHECK_GENERAL_SYNTAX_ERROR";
			break;
		}
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_FAIL_TO_DETERMINATE:
		{
			msg = "SETTINGS_INI_LINE_CHECK_FAIL_TO_DETERMINATE";
			break;
		}
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_EMPTY_LINE:
		{
			msg = "SETTINGS_INI_LINE_CHECK_EMPTY_LINE";
			break;
		}
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_COMMENTED_LINE:
		{
			msg = "SETTINGS_INI_LINE_CHECK_COMMENTED_LINE";
			break;
		}
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_SECTION:
		{
			msg = "SETTINGS_INI_LINE_CHECK_SECTION";
			break;
		}
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_SECTION_WITH_COMMENTS:
		{
			msg = "SETTINGS_INI_LINE_CHECK_SECTION_WITH_COMMENTS";
			break;
		}
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_KEY_ONLY:
		{
			msg = "SETTINGS_INI_LINE_CHECK_KEY_ONLY";
			break;
		}
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_KEY_WITH_VALUE:
		{
			msg = "SETTINGS_INI_LINE_CHECK_KEY_WITH_VALUE";
			break;
		}
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_KEY_ONLY_WITH_COMMENTS:
		{
			msg = "SETTINGS_INI_LINE_CHECK_KEY_ONLY_WITH_COMMENTS";
			break;
		}
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_KEY_WITH_VALUE_AND_COMMENTS:
		{
			msg = "SETTINGS_INI_LINE_CHECK_KEY_WITH_VALUE_AND_COMMENTS";
			break;
		}
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_KEY_WITH_CONTAINER_VALUE:
		{
			msg = "SETTINGS_INI_LINE_CHECK_KEY_WITH_CONTAINER_VALUE";
			break;
		}
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_KEY_WITH_CONTAINER_VALUE_AND_COMMENTS:
		{
			msg = "SETTINGS_INI_LINE_CHECK_KEY_WITH_CONTAINER_VALUE_AND_COMMENTS";
			break;
		}
		default:
		{
			break;
		}
	}

    return msg;
}

std::string translateIniRawValueConversionStatus(SettingsLib::ErrorCodes::IniRawValueConversionStatus code)
{
    std::string msg = "";

	switch (code)
	{
		case SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_INIT_DATA_ERROR:
		{
			msg = "SETTINGS_INI_CONVERT_VALUE_INIT_DATA_ERROR";
			break;
		}
		case SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_NULLPTR_ERROR:
		{
			msg = "SETTINGS_INI_CONVERT_VALUE_NULLPTR_ERROR";
			break;
		}
		case SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_UNKNOWN_ERROR:
		{
			msg = "SETTINGS_INI_CONVERT_VALUE_UNKNOWN_ERROR";
			break;
		}
		case SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_FAIL:
		{
			msg = "SETTINGS_INI_CONVERT_VALUE_FAIL";
			break;
		}
		case SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_CONTAINER_TYPE:
		{
			msg = "SETTINGS_INI_CONVERT_VALUE_CONTAINER_TYPE";
			break;
		}
		case SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_EMPTY:
		{
			msg = "SETTINGS_INI_CONVERT_VALUE_EMPTY";
			break;
		}
		case SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_UNSIGNED_INTEGER:
		{
			msg = "SETTINGS_INI_CONVERT_VALUE_UNSIGNED_INTEGER";
			break;
		}
		case SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_INTEGER:
		{
			msg = "SETTINGS_INI_CONVERT_VALUE_INTEGER";
			break;
		}
		case SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_FLOAT:
		{
			msg = "SETTINGS_INI_CONVERT_VALUE_FLOAT";
			break;
		}
		case SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_BOOLEAN:
		{
			msg = "SETTINGS_INI_CONVERT_VALUE_BOOLEAN";
			break;
		}
		case SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_STRING:
		{
			msg = "SETTINGS_INI_CONVERT_VALUE_STRING";
			break;
		}
		case SettingsLib::ErrorCodes::IniRawValueConversionStatus::SETTINGS_INI_CONVERT_VALUE_WSTRING:
		{
			msg = "SETTINGS_INI_CONVERT_VALUE_WSTRING";
			break;
		}
		default:
		{
			break;
		}
	}

	return msg;
}

std::string convertConfigIniData2Str(SettingsLib::Types::ConfigIniData *data)
{
    std::string key;
	std::string section;
	std::string value;
	std::string comment;

	SettingsLib::Types::ConfigDataStore dataS;
	std::string line = "";
	data->getKey(&key);

	line = "Key: " + key;

	line += " | Value: ";

	if (data->hasData())
	{
		data->getData(&dataS);

		auto code = dataS.getDataType();

		std::string dataStr = "";

		switch (code)
		{
			case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_UNSIGNED_INTEGER:
			{
				unsigned long long ull = 0;
				dataS.getData(&ull);
				line += std::to_string(ull);
				break;
			}
			case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_INTEGER:
			{
				long long ll = 0;
				dataS.getData(&ll);
				line += std::to_string(ll);
				break;
			}
			case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_FLOAT:
			{
				double d = 0.0;
				dataS.getData(&d);
				line += std::to_string(d);
				break;
			}
			case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_BOOLEAN:
			{
				bool b = false;
				dataS.getData(&b);

				if (b)
				{
					line +=  "true";
				}
				else
				{
					line +=  "false";
				}
				break;
			}
			case SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING:
			{
				int vS = dataS.getData(&value);
				line += value;
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
		line +=  "NONE";
	}

	line +=  " | Comment: ";

	if (data->hasComment())
	{
		data->getComment(&comment);
		line +=  comment;
	}
	else
	{
		line +=  "NONE";
	}

	section.clear();
	key.clear();
	value.clear();
	comment.clear();

	return line;
}
