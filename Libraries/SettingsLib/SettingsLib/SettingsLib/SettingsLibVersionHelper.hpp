#pragma once 

#ifndef SETTINGS_LIB_VERSION_HELPER_HPP
#define SETTINGS_LIB_VERSION_HELPER_HPP

#ifdef WIN32
	#ifdef SETTINGS_LIB_EXPORTS
		#define SETTINGS_LIB_API __declspec(dllexport)
	#else
		#define SETTINGS_LIB_API __declspec(dllimport)
	#endif //!SETTINGS_LIB_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#endif // !WIN32

/**
 * @note This file was originally called "SettingsLibProperties.hpp"
 * @note Originally all functions were inline
*/

#include <string>

#include "SettingsLibDataTypes.hpp"

#define SETTINGS_LIBRARY_MAJOR_VERSION		3
#define SETTINGS_LIBRARY_MINOR_VERSION		0
#define SETTINGS_LIBRARY_REVISION_VERSION	0
#define SETTINGS_LIBRARY_BUILD_TYPE			"alpha"
#define SETTINGS_LIBRARY_BUILD_TYPE_W		L"alpha"
#define SETTINGS_LIBRARY_BUILD_VERSION		0

namespace SettingsLib
{
	/// @brief Get the Settings Library version string
	SETTINGS_LIB_API std::string getSettingsLibVersion();

	/// @brief Get the Settings Library build string
	SETTINGS_LIB_API std::string getSettingsLibBuild();

	/// @brief Get the Settings Library version wide string
	SETTINGS_LIB_API std::wstring getSettingsLibVersionW();

	/// @brief Get the Settings Library build wide string
	SETTINGS_LIB_API std::wstring getSettingsLibBuildW();

	/// @brief Get all version and build information on struct SettingsLibVersion. NOTE: The build type is only given in ASCII.
	SETTINGS_LIB_API const SettingsLib::Types::SettingsLibVersion getSettingsLibVersionData();
}

#endif //! SETTINGS_LIB_VERSION_HELPER_HPP