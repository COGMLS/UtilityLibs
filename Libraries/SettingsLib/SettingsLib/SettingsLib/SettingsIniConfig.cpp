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

SettingsLib::Types::ConfigIni::ConfigIni(std::wstring configName)
{

}

SettingsLib::Types::ConfigIni::ConfigIni(std::filesystem::path configFile, bool readonly)
{
	
}

SettingsLib::Types::ConfigIni::~ConfigIni()
{
	
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
				//SettingsLib::Types::ConfigDataStore dataStore;
				//SettingsLib::Tools::Ini::convertValue(&rawValue, &dataStore, false);
				//iniData.setData(&dataStore);

				std::vector<SettingsLib::Types::ConfigDataStore> vData;
				SettingsLib::Tools::Ini::convertValue2Container(&rawValue, &vData, false);

				if (!vData.empty())
				{
					for (size_t i = 0; i < vData.size(); i++)
					{
						iniData.insertData(vData[i], i, false);
					}
				}
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

SettingsLib::Types::ConfigFileStream *SettingsLib::Types::ConfigIni::getConfigFileStream()
{
	if (this->isUsingConfigFileStream())
	{
		return this->cfgFileStream.get();
	}

    return nullptr;
}

int SettingsLib::Types::ConfigIni::setConfigName(std::string newName)
{
	if (this->isWideData())
	{
		return -1;
	}

	// Check if the newName is also a path. Otherwise, use current path:

	std::filesystem::path test = newName;
	std::filesystem::path currentPath = std::filesystem::current_path();

	///TODO: MAKE A PATH TEST TO DETECT IF THE NEW NAME HAS A PATH OR USE CURRENT PATH

	// Backup the data:
	std::filesystem::path originalPath = this->configFile;
	std::string oldName;

	int strNameStatus = this->configName.getData(&oldName);

	if (strNameStatus < 0 && strNameStatus == 2)
	{
		return 1;	// Fail or it is another datatype
	}

	// If set the data was successful, check if the configuration path is used:
	if (this->configName.setData(newName) == 0)
	{
		if (!this->configFile.empty())
		{
			std::filesystem::path newPath = this->configFile.parent_path() / std::filesystem::path(newName);

			// Test if the new path already exits
			if (std::filesystem::exists(newPath))
			{
				return 2;		// The path already exists
			}

			// Set the new name:
			if (this->configName.setData(newName) != 0)
			{
				return 3;	// Fail to set a new configuration file
			}

			this->cfgFileStream->setKeepCfgStore(true);
			
			std::vector<std::string> tmpConfigLines;
			
			if (this->cfgFileStream->getConfigLines(&tmpConfigLines) != 1)
			{
				// Restore all modifications:
				this->configName = oldName;
				return 4;		// Fail to store the configuration lines
			}
			
			this->cfgFileStream->closeConfigStream();
			this->cfgFileStream.reset(nullptr);
			
			this->configFile = newPath;
			this->cfgFileStream.reset(new SettingsLib::Types::ConfigFileStream(this->configFile, false, false, true));
			
			if (!this->cfgFileStream->isConfigStreamOpen())
			{
				if (!this->cfgFileStream->openConfigStream(true, false))
				{
					return 5;	// Fail to open the configuration stream
				}
			}

			this->cfgFileStream->refreshCfgStore(&tmpConfigLines);
			this->cfgFileStream->saveStoreOnFile();
		}
		else
		{
			// In case the configuration is empty, try to create the file or use a existing one depending on the path:
		}
	}

    return 0;
}
