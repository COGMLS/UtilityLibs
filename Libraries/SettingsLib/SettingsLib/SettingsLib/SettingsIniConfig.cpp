#include "SettingsIniConfig.hpp"

SettingsLib::Types::ConfigIni::ConfigIni()
{
	this->isObjConfigured = false;
	this->useWideData = false;
}

SettingsLib::Types::ConfigIni::ConfigIni(std::string configName)
{
	this->useWideData = false;
	this->isObjConfigured = false;
	if (this->configName.setData(configName) == 0)
	{
		this->isObjConfigured = true;
	}
}

SettingsLib::Types::ConfigIni::ConfigIni(std::wstring configName)
{
	this->useWideData = true;
	this->isObjConfigured = false;
	if (this->configName.setData(configName) == 0)
	{
		this->isObjConfigured = true;
	}
}

SettingsLib::Types::ConfigIni::ConfigIni(std::filesystem::path configFile, bool readonly)
{
	this->useWideData = false;
	this->isObjConfigured = false;

	this->configFile = configFile;

	this->cfgFileStream.reset(new SettingsLib::Types::ConfigFileStream(this->configFile, false, readonly, true));

	if (this->cfgFileStream->isConfigStreamOk())
	{
		std::string configName = this->configFile.filename().string();
		if (this->configName.setData(configName) == 0)
		{
			this->isObjConfigured = true;
		}
	}
}

SettingsLib::Types::ConfigIni::ConfigIni(std::filesystem::path configFile, bool readonly, bool useWideString)
{
	this->useWideData = useWideString;
	this->isObjConfigured = false;

	this->configFile = configFile;

	this->cfgFileStream.reset(new SettingsLib::Types::ConfigFileStream(this->configFile, false, readonly, true));

	if (this->cfgFileStream->isConfigStreamOk())
	{
		if (this->useWideData)
		{
			std::wstring configName = this->configFile.filename().wstring();
			if (this->configName.setData(configName) == 0)
			{
				this->isObjConfigured = true;
			}
		}
		else
		{
			std::string configName = this->configFile.filename().string();
			if (this->configName.setData(configName) == 0)
			{
				this->isObjConfigured = true;
			}
		}
	}
}

SettingsLib::Types::ConfigIni::~ConfigIni()
{
	if (this->isObjConfigured)
	{
		if (this->cfgFileStream)
		{
			this->cfgFileStream->~ConfigFileStream();
			this->cfgFileStream.reset(nullptr);
		}
	}
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
			this->lastSectionSearch = section;
			break;
		}
		default:
		{
			break;
		}
	}
}

void SettingsLib::Types::ConfigIni::readLine(std::wstring line)
{
	std::wstring key;
	std::wstring section;
	std::wstring rawValue;
	std::wstring comment;

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

			isEmpty = this->wSectionMap.empty();
			foundSection = this->wSectionMap.contains(this->lastSectionSearchW);

			if (!foundSection || isEmpty)
			{
				SettingsLib::Types::ConfigIniSectionData* wSectionBuff = new SettingsLib::Types::ConfigIniSectionData(this->lastSectionSearchW);
				this->wSectionMap.insert({this->lastSectionSearchW, wSectionBuff});
				foundSection = true;
			}

			if (foundSection)
			{
				this->wSectionMap.at(this->lastSectionSearchW)->addData(iniData);
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

			isEmpty = this->wSectionMap.empty();
			foundSection = this->wSectionMap.contains(this->lastSectionSearchW);

			if (!foundSection || isEmpty)
			{
				SettingsLib::Types::ConfigIniSectionData* wSectionBuff = new SettingsLib::Types::ConfigIniSectionData(this->lastSectionSearchW);
				this->wSectionMap.insert({this->lastSectionSearchW, wSectionBuff});
				foundSection = true;
			}

			if (foundSection)
			{
				this->wSectionMap.at(this->lastSectionSearchW)->addData(iniData);
			}
			break;
		}
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_SECTION:
		case SettingsLib::ErrorCodes::IniLineCheckStatus::SETTINGS_INI_LINE_CHECK_SECTION_WITH_COMMENTS:
		{
			this->lastSectionSearchW = section;
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

			return 0;
		}
		else
		{
			// In case the configuration is empty, try to create the file or use a existing one depending on the path:
			return 6;
		}

		return 7;
	}

	return 8;
}

int SettingsLib::Types::ConfigIni::setConfigName(std::wstring newName)
{
	if (!this->isWideData())
	{
		return -1;
	}

	// Backup the data:
	std::filesystem::path originalPath = this->configFile;
	std::wstring oldName;

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
			
			std::vector<std::wstring> tmpConfigLines;
			
			if (this->cfgFileStream->getConfigLines(&tmpConfigLines) != 1)
			{
				// Restore all modifications:
				this->configName = oldName;
				return 4;		// Fail to store the configuration lines
			}
			
			this->cfgFileStream->closeConfigStream();
			this->cfgFileStream.reset(nullptr);
			
			this->configFile = newPath;
			this->cfgFileStream.reset(new SettingsLib::Types::ConfigFileStream(this->configFile, true, false, true));
			
			if (!this->cfgFileStream->isConfigStreamOpen())
			{
				if (!this->cfgFileStream->openConfigStream(true, false))
				{
					return 5;	// Fail to open the configuration stream
				}
			}

			this->cfgFileStream->refreshCfgStore(&tmpConfigLines);
			this->cfgFileStream->saveStoreOnFile();

			return 0;
		}
		else
		{
			// In case the configuration is empty, try to create the file or use a existing one depending on the path:
			return 6;
		}

		return 7;
	}

	return 8;
}

int SettingsLib::Types::ConfigIni::getConfigName(std::string *configName)
{
	if (this->isWideData())
	{
		return 1;
	}

	if (configName == nullptr)
	{
		return 2;
	}

	if (this->configName.getData(configName) == 1)
	{
		return 0;
	}

    return 3;
}

int SettingsLib::Types::ConfigIni::getConfigName(std::wstring *configName)
{
	if (!this->isWideData())
	{
		return 1;
	}

	if (configName == nullptr)
	{
		return 2;
	}

	if (this->configName.getData(configName) == 1)
	{
		return 0;
	}

    return 3;
}

bool SettingsLib::Types::ConfigIni::isWideData()
{
    return this->useWideData;
}

bool SettingsLib::Types::ConfigIni::isConfigFileOk()
{
    return this->isObjConfigured;
}

bool SettingsLib::Types::ConfigIni::isUsingConfigFileStream()
{
	if (this->cfgFileStream)
	{
		return true;
	}

	return false;
}

int SettingsLib::Types::ConfigIni::saveFile()
{
    return 0;
}

int SettingsLib::Types::ConfigIni::loadFile(bool discardChanges)
{
    return 0;
}
