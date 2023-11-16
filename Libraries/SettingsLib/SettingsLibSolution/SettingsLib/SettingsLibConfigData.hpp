#pragma once

#ifndef SETTINGS_LIBRARY_CONFIG_DATA_HPP
#define SETTINGS_LIBRARY_CONFIG_DATA_HPP

#include "pch.h"

#include "SettingsLibCommonDefines.hpp"
#include "SettingsLibCommonDataTypes.hpp"

#include <cctype>
#include <fstream>
#include <string>
#include <vector>

namespace SettingsLib
{
	/// @brief Configuration Data Class to hold the Configuration ID and the Configuration Data to the application
	class SETTINGS_LIB_API ConfigData
	{
		private:

			// ConfigData data control type wrappers:
		
			/// @brief Configuration Data Union
			union ConfigDataUnion
			{
				unsigned long long ull;
				long long ll;
				double d;
				bool b;
			};

			// ConfigData variables:

			std::string idName;						// Configuration ID
			ConfigDataUnion data;					// Configuration Union data store
			ConfigDataType type;					// Configuration Data Type
			std::string strData;					// Configuration string data store

			// ConfigData control variables:

			bool isConfigOk;
			ConfigDataErrorStatus errCode;

			// Error Handling:

			std::exception* exceptInfo = nullptr;

			/// @brief Define a exception detected inside a operation
			/// @param e Exception object
			void setException(std::exception e);

		public:
			/// @brief Create a object representing the configuration data
			/// @param configLine Configuration line that will be converted
			/// @param validConfigList Valid configurations for the settings section. If a nullptr was send the configuration won't be verified.
			ConfigData(std::string configLine, std::vector<std::string>* validConfigList);

			ConfigData(const ConfigData& other);
		
			ConfigData(ConfigData&& other) noexcept;
		
			~ConfigData();

			ConfigData& operator=(const ConfigData& other);
			ConfigData& operator=(ConfigData&& other) noexcept;
			bool operator==(const ConfigData& other) const;

			/// @brief Get the configuration ID name 
			std::string getConfigId();
		
			/// @brief Check if the configuration is valid or correct
			/// @return True if is valid. NOTE: By default the value is always false, unless a valid configuration list is send to constructor or isValidConfig to test the configuration ID
			bool isValidConfig();

			/// @brief Check if the configuration is valid or correct
			/// @return True if is valid. NOTE: By default the value is always false, unless a valid configuration list is send to constructor or isValidConfig to test the configuration ID
			bool isValidConfig(std::vector<std::string>* validConfigList);

			// Error Handling Functions:

			/// @brief Detect if a exception was store in exceptInfo
			bool foundException();

			/// @brief Get the last exception available. If no exception was generated or the clearException was called, an empty exception will be returned.
			std::exception getException();

			/// @brief Clear the exception data
			void clearException();

			// Getters:

			/// @brief Get the data type the configuration data was defined
			ConfigDataType getConfigDataType();

			/// @brief Get the configuration data
			/// @param data Variable address to store the data
			/// @return True if the data was set correctly
			/// @return False if the data type is not the same or a error exist in current configuration data
			bool getConfigData(unsigned long long& data);
			bool getConfigData(unsigned long long* data);
		
			/// @brief Get the configuration data
			/// @param data Variable address to store the data
			/// @return True if the data was set correctly
			/// @return False if the data type is not the same or a error exist in current configuration data
			bool getConfigData(long long& data);
			bool getConfigData(long long* data);
		
			/// @brief Get the configuration data
			/// @param data Variable address to store the data
			/// @return True if the data was set correctly
			/// @return False if the data type is not the same or a error exist in current configuration data
			bool getConfigData(double& data);
			bool getConfigData(double* data);
		
			/// @brief Get the configuration data
			/// @param data Variable address to store the data
			/// @return True if the data was set correctly
			/// @return False if the data type is not the same or a error exist in current configuration data
			bool getConfigData(bool& data);
			bool getConfigData(bool* data);
		
			/// @brief Get the configuration data
			/// @param data Variable address to store the data
			/// @return True if the data was set correctly
			/// @return False if the data type is not the same or a error exist in current configuration data
			bool getConfigData(std::string& data);
			bool getConfigData(std::string* data);

			// Setters:

			/// @brief Set the configuration data
			/// @param data Variable address to send the data
			/// @return True if the data was set correctly
			/// @return False if the data type is not the same or a error exist in current configuration data
			bool setConfigData(unsigned long long& data);
			bool setConfigData(unsigned long long* data);
		
			/// @brief Set the configuration data
			/// @param data Variable address to send the data
			/// @return True if the data was set correctly
			/// @return False if the data type is not the same or a error exist in current configuration data
			bool setConfigData(long long& data);
			bool setConfigData(long long* data);
		
			/// @brief Set the configuration data
			/// @param data Variable address to send the data
			/// @return True if the data was set correctly
			/// @return False if the data type is not the same or a error exist in current configuration data
			bool setConfigData(double& data);
			bool setConfigData(double* data);
		
			/// @brief Set the configuration data
			/// @param data Variable address to send the data
			/// @return True if the data was set correctly
			/// @return False if the data type is not the same or a error exist in current configuration data
			bool setConfigData(bool& data);
			bool setConfigData(bool* data);
		
			/// @brief Set the configuration data
			/// @param data Variable address to send the data
			/// @return True if the data was set correctly
			/// @return False if the data type is not the same or a error exist in current configuration data
			bool setConfigData(std::string& data);
			bool setConfigData(std::string* data);
	};
}

#endif // !SETTINGS_LIBRARY_CONFIG_DATA_HPP