#pragma once

#ifndef SETTINGS_LIBRARY_MANAGER_HPP
#define SETTINGS_LIBRARY_MANAGER_HPP

#include "pch.h"

#include "SettingsLibConfigData.hpp"
#include "SettingsLibConfigDataW.hpp"

#include <filesystem>
#include <fstream>
#include <map>
#include <string>
#include <vector>

namespace SettingsLib
{
	class SETTINGS_LIB_API SettingsData
	{
		private:
			std::filesystem::path filePath;
			std::map<std::string, SettingsLib::ConfigData>* mapConfigData;
			std::map<std::wstring, SettingsLib::ConfigDataW>* mapConfigDataW;

			// Controls the file status: 0 - exist, 1 - created, 2 - fail to open, 3 - fail to create
			unsigned short fileExist;

			// Define if a configuration data was changed
			bool configMod;

			long long errorStatus;

		public:
			SettingsData(std::filesystem::path configFilePath, std::string field, std::vector<std::string>* validConfigList);
			SettingsData(std::filesystem::path configFilePath, std::string field, std::vector<std::string>* validConfigList, bool ignoreCheck);
			SettingsData(std::filesystem::path configFilePath, std::wstring field, std::vector<std::wstring>* validConfigList);
			SettingsData(std::filesystem::path configFilePath, std::wstring field, std::vector<std::wstring>* validConfigList, bool ignoreCheck);

			SettingsData(const SettingsData& other);

			SettingsData(SettingsData&& other) noexcept;

			~SettingsData();

			SettingsData& operator=(const SettingsData& other);
			SettingsData& operator=(SettingsData&& other) noexcept;
			bool operator==(const SettingsData& other) const;

			bool isWideConfigs();

			bool getConfig(std::string configID, ConfigData* pCfgData);
			bool getConfig(std::wstring configID, const ConfigDataW* pCfgDataW);

			bool setConfig(ConfigData* pCfgData);
			bool setConfig(ConfigDataW* pCfgDataW);
	};
}

#endif // !SETTINGS_LIBRARY_MANAGER_HPP