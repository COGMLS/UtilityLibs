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
#endif // !WIN32

#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <stdexcept>
#include <algorithm>

#include "SettingsLibDefinitions.hpp"
#include "SettingsIniDefinitions.hpp"
#include "SettingsLibErrorCodes.hpp"
#include "SettingsIniErrorCodes.hpp"
#include "SettingsIniConfigData.hpp"

namespace SettingsLib
{
	namespace Tools
	{
		/**
		 * Special tool for ini configuration data files
		 * --------------------------------------------------------------------
		 * This namespace holds specific tools for ini files and keep
		 * organized the Tools namespce for generic tools.
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
			 * @return Return a IniLineCheckStatus value from convertion value from data extraction
			 * @note If one or more sending variables doesn't have values, will return an empty string. Use the return value to check the real condition.
			 * @note When a key is returned, the section is not defined. This function only analyze one configuration line! To determinate if a key is part of a section, use another function // To-Do: Create the function to merge the key from a section into a section data.
			 * @warning If one of the variables has nullptr value, the function will return SETTINGS_INI_LINE_CHECK_NULLPTR_ERROR status code.
			 */
			SETTINGS_LIB_API int extractIniDataLine (std::string* line, std::string* sectionName, std::string* keyName, std::string* rawValue, std::string* comment);

			/**
			 * @brief Identify the raw value extracted from INI file line
			 * @param rawValue A raw value data extracted from INI file line
			 * @return Return a IniRawValueConversionStatus value from convertion
			 * @note This function is available for custom methods. The convertNumber and convertValue functions already analyze the value type
			 */
			SETTINGS_LIB_API int identifyValueType (std::string* rawValue);

			/**
			 * @brief Function stricted to only convert raw string values into numbers.
			 * @param rawValue A raw value data extracted from INI file line
			 * @param type Identify the type of value is inside the ConfigDataUnion
			 * @param uValue Holds the converted value. This pointer should be a nullptr!
			 * @return Return a IniRawValueConversionStatus value from convertion
			 * @note This function is available for custom methods. The convertValue function already analyze the value type
			 */
			SETTINGS_LIB_API int convertNumber (std::string* rawValue, SettingsLib::Types::ConfigDataType* type, SettingsLib::Types::ConfigDataUnion* uValue);

			/**
			 * @brief Convert a raw value string extracted from INI configuration line into a number (unsigned integer/integer/decimal), boolean, or a literal string
			 * @param rawValue A raw value data extracted from INI file line
			 * @param type Identify the type of value is inside the ConfigDataUnion
			 * @param uValue Holds the converted value. This pointer should be a nullptr!
			 * @param trimSpaces Cut the empty spaces in the beging of the string end in the end, only if the value is a string data. Otherwise, will be ignored.
			 * @return Return a IniRawValueConversionStatus value from convertion
			 */
			SETTINGS_LIB_API int convertValue (std::string* rawValue, SettingsLib::Types::ConfigDataType* type, SettingsLib::Types::ConfigDataUnion* uValue, bool trimSpaces);

			//SETTINGS_LIB_API int convertValue (std::string* rawValue, SettingsLib::Types::ConfigDataType* type, SettingsLib::Types::ConfigDataContainerType* containerType, std::vector<SettingsLib::Types::ConfigDataUnion>* vData, bool trimSpaces);
		}
	}
}

#endif // !SETTINGS_LIB_INI_TOOLS_HPP