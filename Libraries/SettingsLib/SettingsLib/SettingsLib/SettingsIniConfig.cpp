#include "SettingsIniConfig.hpp"

SettingsLib::Types::ConfigIni::ConfigIni()
{
	this->isObjConfigured = false;
	this->useWideData = false;
}

SettingsLib::Types::ConfigIni::ConfigIni(std::string configName)
{
	this->isObjConfigured = true;
	this->useWideData = false;
	this->configName.setData(configName);
}

void SettingsLib::Types::ConfigIni::readLine(std::string line)
{
	std::string key;
	std::string section;
	std::string rawValue;
	std::string comment;

	SettingsLib::ErrorCodes::IniLineCheckStatus lineStatus = static_cast<SettingsLib::ErrorCodes::IniLineCheckStatus>(SettingsLib::Tools::Ini::extractIniDataLine(&line, &section, &key, &rawValue, &comment));

	switch (lineStatus)
	{
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_KEY_ONLY:
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_KEY_ONLY_WITH_COMMENTS:
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_KEY_WITH_VALUE:
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_KEY_WITH_VALUE_AND_COMMENTS:
		{
			/** For ini data with normal values:
			 * ------------------------------------------------------
			 * Add a ini data with normal/traditional values used in
			 * configuration files.
			 */

			SettingsLib::Types::ConfigIniData iniData(key);

			if (!rawValue.empty())
			{
				SettingsLib::Types::ConfigDataStore dataStore;
				SettingsLib::Tools::Ini::convertValue(&rawValue, &dataStore, false);
				iniData.setData(dataStore);
			}

			if (!comment.empty())
			{
				iniData.setComment(comment);
			}

			bool isEmpty = false;
			bool foundSection = false;

			isEmpty = this->sectionMap.empty();
			foundSection = this->sectionMap.contains(this->lastSectionSearch);

			if (!foundSection || isEmpty)
			{
				SettingsLib::Types::ConfigIniSectionData* sectionBuff = new SettingsLib::Types::ConfigIniSectionData(this->lastSectionSearch);
				this->sectionMap.insert({this->lastSectionSearch, sectionBuff});
				foundSection = true;
			}

			if (foundSection)
			{
				SettingsLib::Types::ConfigIniData iniTest1(iniData);
				this->sectionMap.at(this->lastSectionSearch)->addData(iniData);
			}

			break;
		}
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_KEY_WITH_CONTAINER_VALUE:
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_KEY_WITH_CONTAINER_VALUE_AND_COMMENTS:
		{
			/** For ini data with container values:
			 * ------------------------------------------------------
			 * Add a ini data that has a container, using a proper tool
			 * to filter the values and treat then correctly.
			 * ------------------------------------------------------
			 * Note: In this moment, the containers will be treated as
			 * a normal string value.
			 */

			SettingsLib::Types::ConfigIniData iniData(key);

			if (!rawValue.empty())
			{
				SettingsLib::Types::ConfigDataStore dataStore;
				SettingsLib::Tools::Ini::convertValue(&rawValue, &dataStore, false);
				iniData.setData(&dataStore);

				std::vector<SettingsLib::Types::ConfigDataStore> vData;
				SettingsLib::Tools::Ini::convertValue2Container(&rawValue, &vData, false);
			}

			if (!comment.empty())
			{
				iniData.setComment(comment);
			}
			
			bool isEmpty = false;
			bool foundSection = false;

			isEmpty = this->sectionMap.empty();
			foundSection = this->sectionMap.contains(this->lastSectionSearch);

			if (!foundSection || isEmpty)
			{
				SettingsLib::Types::ConfigIniSectionData* sectionBuff = new SettingsLib::Types::ConfigIniSectionData(this->lastSectionSearch);
				this->sectionMap.insert({this->lastSectionSearch, sectionBuff});
				foundSection = true;
			}

			if (foundSection)
			{
				this->sectionMap.at(this->lastSectionSearch)->addData(iniData);
			}
			break;
		}
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_SECTION:
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_SECTION_WITH_COMMENTS:
		{
			lastSectionSearch = section;
			break;
		}
		default:
		{
			break;
		}
	}
}
