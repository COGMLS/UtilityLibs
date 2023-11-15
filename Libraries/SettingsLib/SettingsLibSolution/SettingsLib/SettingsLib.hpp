#pragma once

#ifndef SETTINGS_LIBRARY_HPP
#define SETTINGS_LIBRARY_HPP

#include "pch.h"

#include <string>
#include <cctype>
#include <vector>
#include <map>
#include <fstream>

// Settings marks:

#define SETTINGS_OPEN_FIELD			'['
#define SETTINGS_CLOSE_FIELD		']'
#define SETTINGS_COMMENT_MARK		';'
#define SETTINGS_COMMENT_MARK2		'#'
#define SETTINGS_DATA_MARK			'='
#define SETTINGS_SPACE_CHAR			' '
#define SETTINGS_NEW_LINE			'\n'

// Settings data types:

#define SETTINGS_DATA_TYPE_STRING				'"'
#define SETTINGS_DATA_TYPE_BOOL_FALSE			"false"
#define SETTINGS_DATA_TYPE_BOOL_TRUE			"true"
#define SETTINGS_DATA_TYPE_DECIMAL				'.'
#define SETTINGS_DATA_TYPE_NEGATIVE_SIGNAL		'-'
#define SETTINGS_DATA_TYPE_EXPONENT_LOWER		'e'
#define SETTINGS_DATA_TYPE_EXPONENT_UPPER		'E'

// Settings error messages:

#define SETTINGS_CONFIG_DATA_ID_FAIL			"ID_NOT_RECOGNIZED"
#define SETTINGS_CONFIG_DATA_STR_DATA_FAIL		"FAIL_TO_RECOVER_CONFIGURATION_DATA"

/// @brief Settings Field Error Status for Check Field function.
/// @note All error will be treated with zero or negative values
enum SettingsFieldErrorStatus : long long
{
	SETTINGS_FIELD_STATUS_NO_VALID_INDEX = 0ll,
	SETTINGS_FIELD_STATUS_COMMENTED_LINE = -1ll,
	SETTINGS_FIELD_STATUS_FILE_NOT_OPENED = -2ll,
	SETTINGS_FIELD_STATUS_CAN_NOT_FIND_FIELD = -3ll,
	SETTINGS_FIELD_STATUS_OK_NO_DATA_START_POINT = -4ll,
	SETTINGS_FIELD_STATUS_OK_DATA_START_POINT_OK_NO_DATA_END_MARK = -5ll,
	SETTINGS_FIELD_STATUS_OPENED_NOT_CLOSED = -6ll,
	SETTINGS_FIELD_STATUS_NOT_OPEN = -7ll,
	SETTINGS_FIELD_STATUS_NOT_THE_CORRECT_FIELD = -8ll,
	SETTINGS_FIELD_STATUS_NO_DATA_AFTER_FIELD = -9ll,
	SETTINGS_FIELD_STATUS_CAN_NOT_FIND_SUBFIELD = -10ll,
	SETTINGS_FIELD_STATUS_POSSIBLE_CONFIG_LINE = -11ll,
	SETTINGS_FIELD_STATUS_UNKNOWN_ERROR = -12ll
};

enum ConfigDataErrorStatus : unsigned long long
{
	CONFIG_DATA_ERROR_STATUS_OK,
	CONFIG_DATA_ERROR_STATUS_CONFIG_COMMENTED,
	CONFIG_DATA_ERROR_STATUS_CONFIG_ID_FAIL,
	CONFIG_DATA_ERROR_STATUS_CONFIG_DATA_FAIL,
	CONFIG_DATA_ERROR_STATUS_CONFIG_DATA_EMPTY
};

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

		/// @brief Configuration Data Type control
		enum ConfigDataType
		{
			CONFIG_DATA_FAIL,
			CONFIG_DATA_EMPTY,
			UNSIGNED_INTEGER,
			INTERGER,
			FLOAT,
			STRING,
			BOOLEAN
		};

		// ConfigData variables:

		std::string idName;						// Configuration ID
		ConfigDataUnion data;					// Configuration Union data store
		ConfigDataType type;					// Configuration Data Type
		std::string strData;					// Configuration string data store

		// ConfigData control variables:

		bool isConfigOk;
		ConfigDataErrorStatus errCode;
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

		// Getters:

		/// @brief Get the data type the configuration data was defined
		/// @return 
		int getConfigDataType();

		/// @brief Get the configuration data
		/// @param data Variable address to store the data
		/// @return True if the data was set correctly
		/// @return False if the data type is not the same or a error exist in current configuration data
		bool getConfigData(unsigned long long& data);
		
		/// @brief Get the configuration data
		/// @param data Variable address to store the data
		/// @return True if the data was set correctly
		/// @return False if the data type is not the same or a error exist in current configuration data
		bool getConfigData(long long& data);
		
		/// @brief Get the configuration data
		/// @param data Variable address to store the data
		/// @return True if the data was set correctly
		/// @return False if the data type is not the same or a error exist in current configuration data
		bool getConfigData(double& data);
		
		/// @brief Get the configuration data
		/// @param data Variable address to store the data
		/// @return True if the data was set correctly
		/// @return False if the data type is not the same or a error exist in current configuration data
		bool getConfigData(bool& data);
		
		/// @brief Get the configuration data
		/// @param data Variable address to store the data
		/// @return True if the data was set correctly
		/// @return False if the data type is not the same or a error exist in current configuration data
		bool getConfigData(std::string& data);

		// Setters:

		/// @brief Set the configuration data
		/// @param data Variable address to send the data
		/// @return True if the data was set correctly
		/// @return False if the data type is not the same or a error exist in current configuration data
		bool setConfigData(unsigned long long& data);
		
		/// @brief Set the configuration data
		/// @param data Variable address to send the data
		/// @return True if the data was set correctly
		/// @return False if the data type is not the same or a error exist in current configuration data
		bool setConfigData(long long& data);
		
		/// @brief Set the configuration data
		/// @param data Variable address to send the data
		/// @return True if the data was set correctly
		/// @return False if the data type is not the same or a error exist in current configuration data
		bool setConfigData(double& data);
		
		/// @brief Set the configuration data
		/// @param data Variable address to send the data
		/// @return True if the data was set correctly
		/// @return False if the data type is not the same or a error exist in current configuration data
		bool setConfigData(bool& data);
		
		/// @brief Set the configuration data
		/// @param data Variable address to send the data
		/// @return True if the data was set correctly
		/// @return False if the data type is not the same or a error exist in current configuration data
		bool setConfigData(std::string& data);
};

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

SETTINGS_LIB_API bool findSetting(std::map<std::string, ConfigData>& configMap, std::string configId, ConfigData* pConfigData);

#endif // !SETTINGS_LIBRARY_HPP