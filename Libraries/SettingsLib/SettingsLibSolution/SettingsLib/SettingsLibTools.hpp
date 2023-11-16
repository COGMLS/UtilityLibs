#pragma once

#ifndef SETTINGS_LIBRARY_TOOLS_HPP
#define SETTINGS_LIBRARY_TOOLS_HPP

#include "pch.h"

#include "SettingsLibConfigData.hpp"

#include <vector>
#include <string>
#include <fstream>
#include <map>

namespace SettingsLib
{
	namespace Tools
	{
		/// @brief Make a raw information extraction from field settings file
		/// @param config Configuration file
		/// @param fieldName Field name used to extract the data
		/// @param errorStatus Error status pointer
		/// @return Vector with raw valid strings from the file that can be treated as configurations
		SETTINGS_LIB_API std::vector<std::string> chkConfigField(std::fstream& config, std::string fieldName, long long* errorStatus);

		/// @brief Check if the line is a field
		/// @param line Configuration file line
		/// @param fieldName Configuration file field name
		/// @return 0 if fail to test the field
		/// @return 1 if not the correct field
		/// @return 2 if found correct field
		int isConfigField(std::string& line, std::string& fieldName);

		/// @brief Verify if the line has a extractable data to be used as configuration
		/// @param lineTest Raw configuration line to be tested
		/// @return 0 if the line doesn't have a possible data to extract
		/// @return 1 if the line has a invalid value data to extract
		/// @return 2 if the line has a extractable data
		int isLineDataExtractable(std::string& lineTest);

		/// @brief Search for comment mark
		/// @param line Configuration line to be tested
		/// @return A zero or positive number will result in a index that correspond with the first comment mark found
		/// @return -1 if no comment mark was found
		long long findCommentInLine(std::string& line);

		/// @brief Extract the configurations to a map that can be used to find fast the configurations by the subfield name and get the configuration value
		/// @param configDataV Vector with the Configuration Data Vector
		/// @param ignoreCheck Ignore the isValidConfig result and send to map
		/// @return Return a map object with the names for subfield used as keys to get the configuration values
		SETTINGS_LIB_API std::map<std::string, ConfigData> mapConfigData(std::vector<ConfigData>& configDataV, bool ignoreCheck = false);

		/// @brief Extract the configurations from raw data and map them with ConfigData objects that can be used to find fast the configurations by the subfield name and get the configuration value
		/// @param rawConfigDataV Vector with the lines extracted from configuration file
		/// @param validConfigList A valid configurations list that can be used as configurations
		/// @param ignoreCheck Ignore the isValidConfig result and send to map
		/// @return Return a map object with the names for subfield used as keys to get the configuration values
		SETTINGS_LIB_API std::map<std::string, ConfigData> mapConfigData(std::vector<std::string>& rawConfigDataV, std::vector<std::string>* validConfigList, bool ignoreCheck = false);

		/// @brief Find the configuration ID inside the mapped configurations and set the configData
		/// @param configMap Configuration Map
		/// @param configId Configuration ID
		/// @param pConfigData Configuration Data Object
		/// @return True if found the configID and set the ConfigData
		SETTINGS_LIB_API bool findSetting(std::map<std::string, ConfigData>& configMap, std::string configId, ConfigData* pConfigData);
	}
}

#endif // !SETTINGS_LIBRARY_TOOLS_HPP