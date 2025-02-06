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
	}

	return 7;
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
	}

	return 7;
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

std::vector<std::string> SettingsLib::Types::ConfigIni::getConfigMapStr(bool exportValues, bool exportComments)
{
    std::vector<std::string> mapStr;

	if (this->isConfigFileOk() && !this->isWideData())
	{
		std::string actualSection = "";

		for (std::pair<std::string, SettingsLib::Types::ConfigIniSectionData*> sectionPair : this->sectionMap)
		{
			actualSection = sectionPair.first;

			std::vector<std::string> keys;

			std::string line;
			std::string section;
			std::string key;
			std::string valStr;
			std::string comment;
			
			if (sectionPair.second->getSectionName(&section) == 1)
			{
				line = "[" + section + "]";

				if (sectionPair.second->hasComment() && exportComments)
				{
					if (sectionPair.second->getComment(&comment) == 0)
					{
						line += " #" + comment;
					}
				}

				mapStr.push_back(line);

				// Clear for reuse
				line.clear();
				comment.clear();
			}

			if (sectionPair.second->getKeys(&keys) == 0)
			{
				for (size_t i = 0; i < keys.size(); i++)
				{
					key = keys[i];
					SettingsLib::Types::ConfigIniData iniData;

					if (sectionPair.second->getIniData(key, &iniData) == 1)
					{
						line = key + "=";
						
						if (iniData.hasData() && exportValues)
						{
							SettingsLib::Types::ConfigDataStore data;
							
							if (iniData.getData(&data) == SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION)
							{
								if (data.getDataStr(&valStr) == 0)
								{
									line += valStr;
								}
							}
						}

						if (iniData.hasComment() && exportComments)
						{
							if (iniData.getComment(&comment) == SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION)
							{
								line += " #" + comment;
							}
						}

						mapStr.push_back(line);
					}

					// Clear all temporary variables to reuse:
					line.clear();
					key.clear();
					valStr.clear();
					comment.clear();
				}
			}
		}
	}

	return mapStr;
}

std::vector<std::wstring> SettingsLib::Types::ConfigIni::getConfigMapWstr(bool exportValues, bool exportComments)
{
	std::vector<std::wstring> mapWstr;

	if (this->isConfigFileOk() && this->isWideData())
	{
		std::wstring actualSection = L"";

		for (std::pair<std::wstring, SettingsLib::Types::ConfigIniSectionData*> sectionPair : this->wSectionMap)
		{
			actualSection = sectionPair.first;

			std::vector<std::wstring> keys;

			std::wstring line;
			std::wstring section;
			std::wstring key;
			std::wstring valStr;
			std::wstring comment;
			
			if (sectionPair.second->getSectionName(&section) == 1)
			{
				line = L"[" + section + L"]";

				if (sectionPair.second->hasComment() && exportComments)
				{
					if (sectionPair.second->getComment(&comment) == 0)
					{
						line += L" #" + comment;
					}
				}

				mapWstr.push_back(line);

				// Clear for reuse
				line.clear();
				comment.clear();
			}

			if (sectionPair.second->getKeys(&keys) == 0)
			{
				for (size_t i = 0; i < keys.size(); i++)
				{
					key = keys[i];
					SettingsLib::Types::ConfigIniData iniData;

					if (sectionPair.second->getIniData(key, &iniData) == 1)
					{
						line = key + L"=";
						
						if (iniData.hasData() && exportValues)
						{
							SettingsLib::Types::ConfigDataStore data;
							
							if (iniData.getData(&data) == SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION)
							{
								if (data.getDataStr(&valStr) == 0)
								{
									line += valStr;
								}
							}
						}

						if (iniData.hasComment() && exportComments)
						{
							if (iniData.getComment(&comment) == SettingsLib::ErrorCodes::ConfigIniStatus::CONFIG_INI_STATUS_SUCCESSFUL_OPERATION)
							{
								line += L" #" + comment;
							}
						}

						mapWstr.push_back(line);
					}

					// Clear all temporary variables to reuse:
					line.clear();
					key.clear();
					valStr.clear();
					comment.clear();
				}
			}
		}
	}

	return mapWstr;
}

int SettingsLib::Types::ConfigIni::getSectionList(std::vector<std::string> *list)
{
	if (list == nullptr)
	{
		return 1;
	}

	if (!this->isConfigFileOk())
	{
		return 2;
	}

	if (this->isWideData())
	{
		return 3;
	}

	std::vector<std::string> sectionList;

	try
	{
		for (std::pair<std::string, SettingsLib::Types::ConfigIniSectionData*> sectionPair : this->sectionMap)
		{
			sectionList.push_back(sectionPair.first);
		}

		*list = sectionList;
	}
	catch(const std::exception&)
	{
		return 4;
	}

    return 0;
}

int SettingsLib::Types::ConfigIni::getSectionList(std::vector<std::wstring> *list)
{
	if (list == nullptr)
	{
		return 1;
	}

	if (!this->isConfigFileOk())
	{
		return 2;
	}

	if (!this->isWideData())
	{
		return 3;
	}

	std::vector<std::wstring> sectionList;

	try
	{
		for (std::pair<std::wstring, SettingsLib::Types::ConfigIniSectionData*> sectionPair : this->wSectionMap)
		{
			sectionList.push_back(sectionPair.first);
		}

		*list = sectionList;
	}
	catch(const std::exception&)
	{
		return 4;
	}

    return 0;
}

int SettingsLib::Types::ConfigIni::getSection(std::string sectionName, SettingsLib::Types::ConfigIniSectionData *section)
{
	if (section == nullptr)
	{
		return 1;	// Section is nullptr
	}

	if (!this->isConfigFileOk())
	{
		return 2;	// ConfigIni is not ready to use
	}

	if (this->isWideData())
	{
		return 3;	// ConfigIni is configured to use wide strings
	}

	try
	{
		if (this->hasSection(sectionName))
		{
			for (std::pair<std::string, SettingsLib::Types::ConfigIniSectionData*> sectionPair : this->sectionMap)
			{
				if (sectionPair.first == sectionName)
				{
					*section = *sectionPair.second;
					return 0;	// Found and copied to section variable
				}
			}
		}
	}
	catch(const std::exception&)
	{
		return 4;	// Found an exception
	}
	
    return 5;	// Not found
}

int SettingsLib::Types::ConfigIni::getSection(std::wstring sectionName, SettingsLib::Types::ConfigIniSectionData *section)
{
    if (section == nullptr)
	{
		return 1;	// Section is nullptr
	}

	if (!this->isConfigFileOk())
	{
		return 2;	// ConfigIni is not ready to use
	}

	if (!this->isWideData())
	{
		return 3;	// ConfigIni is not configured to use wide strings
	}

	try
	{
		if (this->hasSection(sectionName))
		{
			for (std::pair<std::wstring, SettingsLib::Types::ConfigIniSectionData*> wSectionPair : this->wSectionMap)
			{
				if (wSectionPair.first == sectionName)
				{
					*section = *wSectionPair.second;
					return 0;	// Found and copied to section variable
				}
			}
		}
	}
	catch(const std::exception&)
	{
		return 4;	// Found an exception
	}
	
    return 5;	// Not found
}

int SettingsLib::Types::ConfigIni::getEntry(std::string sectionName, std::string keyName, SettingsLib::Types::ConfigIniData *entry)
{
	if (entry == nullptr)
	{
		return 1;	// Section entry is nullptr
	}

	if (!this->isConfigFileOk())
	{
		return 2;	// ConfigIni is not ready to use
	}

	if (this->isWideData())
	{
		return 3;	// ConfigIni is configured to use wide strings
	}

	if (!entry->isWideData())
	{
		return 6;	// The entry is configured to use wide string
	}

	try
	{
		if (this->hasSection(sectionName))
		{
			SettingsLib::Types::ConfigIniSectionData* pSection = nullptr;

			for (std::pair<std::string, SettingsLib::Types::ConfigIniSectionData*> sectionPair : this->sectionMap)
			{
				if (sectionPair.first == sectionName)
				{
					pSection = sectionPair.second;
					break;
				}
			}

			if (pSection != nullptr)
			{
				if (pSection->getIniData(keyName, entry) == 1)
				{
					return 0;	// Found and copied the INI entry
				}
			}
		}
	}
	catch(const std::exception&)
	{
		return 4;	// Found an exception
	}
	
    return 5;	// Not found
}

int SettingsLib::Types::ConfigIni::getEntry(std::wstring sectionName, std::wstring keyName, SettingsLib::Types::ConfigIniData *entry)
{
    if (entry == nullptr)
	{
		return 1;	// Section entry is nullptr
	}

	if (!this->isConfigFileOk())
	{
		return 2;	// ConfigIni is not ready to use
	}

	if (!this->isWideData())
	{
		return 3;	// ConfigIni is not configured to use wide strings
	}

	if (!entry->isWideData())
	{
		return 6;	// The entry is not configured to use wide string
	}

	try
	{
		if (this->hasSection(sectionName))
		{
			SettingsLib::Types::ConfigIniSectionData* pSection = nullptr;

			for (std::pair<std::wstring, SettingsLib::Types::ConfigIniSectionData*> sectionPair : this->wSectionMap)
			{
				if (sectionPair.first == sectionName)
				{
					pSection = sectionPair.second;
					break;
				}
			}

			if (pSection != nullptr)
			{
				if (pSection->getIniData(keyName, entry) == 1)
				{
					return 0;	// Found and copied the INI entry
				}
			}
		}
	}
	catch(const std::exception&)
	{
		return 4;	// Found an exception
	}
	
    return 5;	// Not found
}

int SettingsLib::Types::ConfigIni::setSection(SettingsLib::Types::ConfigIniSectionData section)
{
	if (!this->isConfigFileOk())
	{
		return 2;
	}

	if (this->isWideData() && !section.isWideData() || !this->isWideData() && section.isWideData())
	{
		return 3;
	}

	if (!section.isConfigured())
	{
		return 5;
	}

	try
	{
		bool foundSection = false;
		bool wideData = section.isWideData();
		std::string sectionName;
		std::wstring wSectionName;

		if (wideData)
		{
			if (section.getSectionName(&wSectionName) == 1)
			{
				return 6;
			}
		}
		else
		{
			if (section.getSectionName(&sectionName) == 1)
			{
				return 6;
			}
		}

		if (wideData)
		{
			for (std::pair<std::wstring, SettingsLib::Types::ConfigIniSectionData*> wSectionPair : this->wSectionMap)
			{
				if (wSectionPair.first == wSectionName)
				{
					foundSection = true;
					break;
				}
			}
		}
		else
		{
			for (std::pair<std::string, SettingsLib::Types::ConfigIniSectionData*> sectionPair : this->sectionMap)
			{
				if (sectionPair.first == sectionName)
				{
					foundSection = true;
					break;
				}
			}
		}

		if (wideData)
		{
			if (foundSection)
			{
				*this->wSectionMap.at(wSectionName) = section;
			}
			else
			{
				this->wSectionMap.insert({wSectionName, &section});
			}
		}
		else
		{
			if (foundSection)
			{
				*this->sectionMap.at(sectionName) = section;
			}
			else
			{
				this->sectionMap.insert({sectionName, &section});
			}
		}

		return 0;
	}
	catch(const std::exception& e)
	{
		return 4;
	}
}

int SettingsLib::Types::ConfigIni::setSection(SettingsLib::Types::ConfigIniSectionData *section)
{
    if (!this->isConfigFileOk())
	{
		return 2;
	}

	if (this->isWideData() && !section->isWideData() || !this->isWideData() && section->isWideData())
	{
		return 3;
	}

	if (!section->isConfigured())
	{
		return 5;
	}

	try
	{
		bool foundSection = false;
		bool wideData = section->isWideData();
		std::string sectionName;
		std::wstring wSectionName;

		if (wideData)
		{
			if (section->getSectionName(&wSectionName) == 1)
			{
				return 6;
			}
		}
		else
		{
			if (section->getSectionName(&sectionName) == 1)
			{
				return 6;
			}
		}

		if (wideData)
		{
			for (std::pair<std::wstring, SettingsLib::Types::ConfigIniSectionData*> wSectionPair : this->wSectionMap)
			{
				if (wSectionPair.first == wSectionName)
				{
					foundSection = true;
					break;
				}
			}
		}
		else
		{
			for (std::pair<std::string, SettingsLib::Types::ConfigIniSectionData*> sectionPair : this->sectionMap)
			{
				if (sectionPair.first == sectionName)
				{
					foundSection = true;
					break;
				}
			}
		}

		if (wideData)
		{
			if (foundSection)
			{
				*this->wSectionMap.at(wSectionName) = *section;
			}
			else
			{
				this->wSectionMap.insert({wSectionName, section});
			}
		}
		else
		{
			if (foundSection)
			{
				*this->sectionMap.at(sectionName) = *section;
			}
			else
			{
				this->sectionMap.insert({sectionName, section});
			}
		}

		return 0;
	}
	catch(const std::exception& e)
	{
		return 4;
	}
}

size_t SettingsLib::Types::ConfigIni::numSections()
{
	if (this->isWideData())
	{
		return this->wSectionMap.size();
	}
	else
	{
		return this->sectionMap.size();
	}
}

size_t SettingsLib::Types::ConfigIni::numKeys()
{
    size_t numKeys = 0;
	if (this->isWideData())
	{
		for (std::pair<std::wstring, SettingsLib::Types::ConfigIniSectionData*> section : this->wSectionMap)
		{
			std::vector<std::wstring> keys;
			if (section.second->getKeys(&keys) == 0)
			{
				numKeys += keys.size();
			}
		}
	}
	else
	{
		for (std::pair<std::string, SettingsLib::Types::ConfigIniSectionData*> section : this->sectionMap)
		{
			std::vector<std::string> keys;
			if (section.second->getKeys(&keys) == 0)
			{
				numKeys += keys.size();
			}
		}
	}
	return numKeys;
}

size_t SettingsLib::Types::ConfigIni::numSectionKeys(std::string sectionName)
{
	if (this->isWideData())
	{
		return 0;
	}

	if (this->sectionMap.contains(sectionName))
	{
		SettingsLib::Types::ConfigIniSectionData* section = this->sectionMap.at(sectionName);
		std::vector<std::string> keys;
		if (section->getKeys(&keys) == 0)
		{
			return keys.size();
		}
	}

	return 0;
}

size_t SettingsLib::Types::ConfigIni::numSectionKeys(std::wstring sectionName)
{
    if (!this->isWideData())
	{
		return 0;
	}

	if (this->wSectionMap.contains(sectionName))
	{
		SettingsLib::Types::ConfigIniSectionData* section = this->wSectionMap.at(sectionName);
		std::vector<std::wstring> keys;
		if (section->getKeys(&keys) == 0)
		{
			return keys.size();
		}
	}

	return 0;
}
