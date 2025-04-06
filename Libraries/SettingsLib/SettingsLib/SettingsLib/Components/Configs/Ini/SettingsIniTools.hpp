#pragma once 

#ifndef SETTINGS_LIB_INI_TOOLS_HPP
#define SETTINGS_LIB_INI_TOOLS_HPP

#ifdef WIN32
	#ifdef SETTINGS_LIB_EXPORTS
		#define SETTINGS_LIB_API __declspec(dllexport)
	#else
		#define SETTINGS_LIB_API __declspec(dllimport)
	#endif //!SETTINGS_LIB_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#else
	#if __GNUC__ >= 4
		#ifdef SETTINGS_LIB_EXPORTS
			#define SETTINGS_LIB_API __attribute__((visibility("default")))
		#else
			#define SETTINGS_LIB_API __attribute__((visibility("default")))
		#endif //!SETTINGS_LIB_EXPORTS
	#else
		#ifdef SETTINGS_LIB_EXPORTS
			#define SETTINGS_LIB_API
		#else
			#define SETTINGS_LIB_API
		#endif //!SETTINGS_LIB_EXPORTS
	#endif
#endif // !WIN32

#include <fstream>
#include <cwchar>
#include <string>
#include <cstring>
#include <filesystem>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cwctype>

#include "SettingsLibDefinitions.hpp"
#include "SettingsIniDefinitions.hpp"
#include "SettingsLibErrorCodes.hpp"
#include "SettingsIniErrorCodes.hpp"
#include "SettingsIniConfigData.hpp"
#include "SettingsLibDataTypes.hpp"

namespace SettingsLib
{
	namespace Tools
	{
		/**
		 * Special tools for ini configuration data files
		 * --------------------------------------------------------------------
		 * This namespace holds specific tools for ini files and keep
		 * organized the Tools namespace from generic tools.
		 */
		namespace Ini
		{
			/**
			 * @brief Extract the INI data line, separating the section, key, value and comment, if exist. If one or more extractable data from this function fail or doesn't exist in the data line, no data will applied.
			 * @param line Line from INI file to extract the data
			 * @param sectionName Section configuration's name
			 * @param keyName Configuration key's name
			 * @param rawValue Raw configuration value (need be treated separately)
			 * @param comment Comment present in the line. If the line is a commented line, will apply only to this value
			 * @return Return a IniLineCheckStatus value from conversion value from data extraction
			 * @note If one or more sending variables doesn't have values, will return an empty string. Use the return value to check the real condition.
			 * @note When a key is returned, the section is not defined. This function only analyze one configuration line! To determinate if a key is part of a section, use another function // To-Do: Create the function to merge the key from a section into a section data.
			 * @warning If one of the variables has nullptr value, the function will return SETTINGS_INI_LINE_CHECK_NULLPTR_ERROR status code.
			 */
			SETTINGS_LIB_API int extractIniDataLine (std::string* line, std::string* sectionName, std::string* keyName, std::string* rawValue, std::string* comment);

			/**
			 * @brief Extract the INI data line, separating the section, key, value and comment, if exist. If one or more extractable data from this function fail or doesn't exist in the data line, no data will applied.
			 * @param line Line from INI file to extract the data
			 * @param sectionName Section configuration's name
			 * @param keyName Configuration key's name
			 * @param rawValue Raw configuration value (need be treated separately)
			 * @param comment Comment present in the line. If the line is a commented line, will apply only to this value
			 * @return Return a IniLineCheckStatus value from conversion value from data extraction
			 * @note If one or more sending variables doesn't have values, will return an empty string. Use the return value to check the real condition.
			 * @note When a key is returned, the section is not defined. This function only analyze one configuration line! To determinate if a key is part of a section, use another function // To-Do: Create the function to merge the key from a section into a section data.
			 * @warning If one of the variables has nullptr value, the function will return SETTINGS_INI_LINE_CHECK_NULLPTR_ERROR status code.
			 */
			SETTINGS_LIB_API int extractIniDataLine (std::wstring* line, std::wstring* sectionName, std::wstring* keyName, std::wstring* rawValue, std::wstring* comment);

			/**
			 * @brief Identify the raw value extracted from INI file line
			 * @param rawValue A raw value data extracted from INI file line
			 * @return Return a IniRawValueConversionStatus value from conversion
			 * @note This function is available for custom methods. The convertNumber and convertValue functions already analyze the value type
			 */
			SETTINGS_LIB_API int identifyValueType (std::string* rawValue);

			/**
			 * @brief Identify the raw value extracted from INI file line
			 * @param rawValue A raw value data extracted from INI file line
			 * @return Return a IniRawValueConversionStatus value from conversion
			 * @note This function is available for custom methods. The convertNumber and convertValue functions already analyze the value type
			 */
			SETTINGS_LIB_API int identifyValueType (std::wstring* rawValue);

			/**
			 * @brief Function strict to only convert raw string values into numbers.
			 * @param rawValue A raw value data extracted from INI file line
			 * @param valueStore A initialized pointer to a ConfigDataStore object
			 * @return Return a IniRawValueConversionStatus value from conversion
			 * @note This function is available for custom methods. The convertValue function already analyze the value type
			 */
			SETTINGS_LIB_API int convertNumber (std::string* rawValue, SettingsLib::Types::ConfigDataStore* valueStore);

			/**
			 * @brief Function strict to only convert raw string values into numbers.
			 * @param rawValue A raw value data extracted from INI file line
			 * @param valueStore A initialized pointer to a ConfigDataStore object
			 * @return Return a IniRawValueConversionStatus value from conversion
			 * @note This function is available for custom methods. The convertValue function already analyze the value type
			 */
			SETTINGS_LIB_API int convertNumber (std::wstring* rawValue, SettingsLib::Types::ConfigDataStore* valueStore);

			/**
			 * @brief Convert a raw value string extracted from INI configuration line into a number (unsigned integer/integer/decimal), boolean, or a literal string
			 * @param rawValue A raw value data extracted from INI file line
			 * @param valueStore A initialized pointer to a ConfigDataStore object
			 * @param trimSpaces Cut the empty spaces in the begin of the string and in the end, only if the value is a string data. Otherwise, will be ignored.
			 * @return Return a IniRawValueConversionStatus value from conversion
			 */
			SETTINGS_LIB_API int convertValue (std::string* rawValue, SettingsLib::Types::ConfigDataStore* valueStore, bool trimSpaces);

			/**
			 * @brief Convert a raw value string extracted from INI configuration line into a number (unsigned integer/integer/decimal), boolean, or a literal string
			 * @param rawValue A raw value data extracted from INI file line
			 * @param valueStore A initialized pointer to a ConfigDataStore object
			 * @param trimSpaces Cut the empty spaces in the begin of the string and in the end, only if the value is a string data. Otherwise, will be ignored.
			 * @return Return a IniRawValueConversionStatus value from conversion
			 */
			SETTINGS_LIB_API int convertValue (std::wstring* rawValue, SettingsLib::Types::ConfigDataStore* valueStore, bool trimSpaces);

			/**
			 * @brief Convert a raw value string extracted from INI configuration line into a container that can hold a number (unsigned integer/integer/decimal), boolean, or a literal string values
			 * @param rawValue A raw value data extracted from INI file line
			 * @param vData A pointer/address to an initialized object Container Data.
			 * @param trimSpaces Cut the empty spaces in the begin of the string and in the end, only if the value is a string data. Otherwise, will be ignored.
			 * @return Return a positive value when no error was found, corresponding with the number of entries was generated inside the vData.
			 * @return Return -1 if not all values was converted correctly.
			 * @return Return -2 if all values failed in conversion task.
			 */
			SETTINGS_LIB_API long long convertValue2Container (std::string* rawValue, std::vector<SettingsLib::Types::ConfigDataStore>* vData, bool trimSpaces);

			/**
			 * @brief Convert a raw value string extracted from INI configuration line into a container that can hold a number (unsigned integer/integer/decimal), boolean, or a literal string values
			 * @param rawValue A raw value data extracted from INI file line
			 * @param vData A pointer/address to an initialized object Container Data.
			 * @param trimSpaces Cut the empty spaces in the begin of the string and in the end, only if the value is a string data. Otherwise, will be ignored.
			 * @return Return a positive value when no error was found, corresponding with the number of entries was generated inside the vData.
			 * @return Return -1 if not all values was converted correctly.
			 * @return Return -2 if all values failed in conversion task.
			 */
			SETTINGS_LIB_API long long convertValue2Container (std::wstring* rawValue, std::vector<SettingsLib::Types::ConfigDataStore>* vData, bool trimSpaces);

			/**
			 * @brief Remove the spaces from the string before the begin and the end.
			 * @param rawValue Raw string.
			 * @param newStr An copy of the rawValue with removed spaces.
			 * @return 
			 */
			SETTINGS_LIB_API int trimSpaces (std::string* rawValue, std::string* newStr, bool trimBegin, bool trimEnd);

			/**
			 * @brief Remove the spaces from the string before the begin and the end.
			 * @param rawValue Raw string.
			 * @param newStr An copy of the rawValue with removed spaces.
			 * @return 
			 */
			SETTINGS_LIB_API int trimSpaces (std::wstring* rawValue, std::wstring* newStr, bool trimBegin, bool trimEnd);

			/**
			 * @brief Convert the ConfigDataStore to a string.
			 * @param data Configuration Data Store that need be converted.
			 * @param strValue String that will hold the converted value.
			 * @return -6 if a unknown type was detected.
			 * @return -5 if the data holds a wstring type.
			 * @return -4 if the data was marked as CONFIG_DATA_MISSING
			 * @return -3 if the data was marked as CONFIG_DATA_FAIL
			 * @return -2 if strValue parameter is a nullptr.
			 * @return -1 if data parameter is a nullptr.
			 * @return 0 if the operation was successful.
			 * @return 1 if the operation failed.
			 */
			SETTINGS_LIB_API int convertDataStore2Str (SettingsLib::Types::ConfigDataStore* data, std::string* strValue);

			/**
			 * @brief Convert the ConfigDataStore to a string.
			 * @param data Configuration Data Store that need be converted.
			 * @param strValue String that will hold the converted value.
			 * @return -6 if a unknown type was detected.
			 * @return -5 if the data holds a string type.
			 * @return -4 if the data was marked as CONFIG_DATA_MISSING
			 * @return -3 if the data was marked as CONFIG_DATA_FAIL
			 * @return -2 if strValue parameter is a nullptr.
			 * @return -1 if data parameter is a nullptr.
			 * @return 0 if the operation was successful.
			 * @return 1 if the operation failed.
			 */
			SETTINGS_LIB_API int convertDataStore2Str (SettingsLib::Types::ConfigDataStore* data, std::wstring* strValue);

			/**
			 * @brief Convert a ConfigIniData to a string configuration line to use in configuration files.
			 * @param iniData INI configuration object that will be converted.
			 * @param line String to hold the converted value.
			 * @return -2 if line parameter is nullptr.
			 * @return -1 if iniData parameter is nullptr.
			 * @return 0 if the operation was successful.
			 * @return 1 if the object is configured to use wstring.
			 */
			SETTINGS_LIB_API int convertObj2CfgLine (SettingsLib::Types::ConfigIniData* iniData, std::string* line);

			/**
			 * @brief Convert a ConfigIniData to a string configuration line to use in configuration files.
			 * @param iniData INI configuration object that will be converted.
			 * @param line String to hold the converted value.
			 * @return -2 if line parameter is nullptr.
			 * @return -1 if iniData parameter is nullptr.
			 * @return 0 if the operation was successful.
			 * @return 1 if the object is configured to use string.
			 */
			SETTINGS_LIB_API int convertObj2CfgLine (SettingsLib::Types::ConfigIniData* iniData, std::wstring* line);
		}
	}
}

#endif // !SETTINGS_LIB_INI_TOOLS_HPP