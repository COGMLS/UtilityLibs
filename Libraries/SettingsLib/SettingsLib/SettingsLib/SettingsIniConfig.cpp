#include "SettingsIniConfig.hpp"

SettingsLib::Types::ConfigIni::ConfigIni()
{
	this->isObjConfigurated = false;
	this->useWideData = false;
}

SettingsLib::Types::ConfigIni::ConfigIni(std::string configName)
{
	this->isObjConfigurated = true;
	this->useWideData = false;
	this->configName.setData(configName);
	this->sectionMap = new std::map<std::string, SettingsLib::Types::ConfigIniSectionData>;
}

void SettingsLib::Types::ConfigIni::readLine(std::string line)
{
	std::string key;
	std::string section;
	std::string rawValue;
	std::string comment;

	SettingsLib::ErrorCodes::IniLineCheckStatus lineStatus = static_cast<SettingsLib::ErrorCodes::IniLineCheckStatus>( SettingsLib::Tools::Ini::extractIniDataLine(&line, &section, &key, &rawValue, &comment));

	switch (lineStatus)
	{
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_KEY_ONLY:
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_KEY_ONLY_WITH_COMMENTS:
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_KEY_WITH_VALUE:
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_KEY_WITH_VALUE_AND_COMMENTS:
		{
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

			isEmpty = this->sectionMap->empty();
			foundSection = this->sectionMap->contains(this->lastSectionSearch);

			if (!foundSection || isEmpty)
			{
				SettingsLib::Types::ConfigIniSectionData sectionBuff(this->lastSectionSearch);
				this->sectionMap->insert({this->lastSectionSearch, sectionBuff});
				foundSection = true;
			}

			if (foundSection)
			{
				this->sectionMap->at(this->lastSectionSearch).addData(iniData);
			}

			break;
		}
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_KEY_WITH_CONTAINER_VALUE:
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_KEY_WITH_CONTAINER_VALUE_AND_COMMENTS:
		{
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

			isEmpty = this->sectionMap->empty();
			foundSection = this->sectionMap->contains(this->lastSectionSearch);

			if (!foundSection || isEmpty)
			{
				this->sectionMap->insert({this->lastSectionSearch, SettingsLib::Types::ConfigIniSectionData(this->lastSectionSearch)});
				foundSection = true;
			}

			if (foundSection)
			{
				SettingsLib::Types::ConfigIniSectionData* pSection = &this->sectionMap->at(this->lastSectionSearch);
				pSection->addData(iniData);
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
