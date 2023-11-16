#pragma once

#ifndef SETTINGS_LIBRARY_PROPERTIES_HPP
#define SETTINGS_LIBRARY_PROPERTIES_HPP

#include "pch.h"
#include <string>

#define SETTINGS_LIBRARY_MAJOR_VERSION		2
#define SETTINGS_LIBRARY_MINOR_VERSION		0
#define SETTINGS_LIBRARY_REVISION_VERSION	0
#define SETTINGS_LIBRARY_BUILD_TYPE			"alpha"
#define SETTINGS_LIBRARY_BUILD_TYPE_W		L"alpha"
#define SETTINGS_LIBRARY_BUILD_VERSION		58

namespace SettingsLib
{
	/// @brief Settings Library Version struct
	struct SettingsLibVersion
	{
		unsigned int major;
		unsigned int minor;
		unsigned int revision;
		char buildType[8];
		unsigned int build;
	};

	/// @brief Get the Settings Library version string
	inline std::string getSettingsLibVersion()
	{
		return std::string(std::to_string(SETTINGS_LIBRARY_MAJOR_VERSION) + "." + std::to_string(SETTINGS_LIBRARY_MINOR_VERSION) + "." + std::to_string(SETTINGS_LIBRARY_REVISION_VERSION) + "-" + SETTINGS_LIBRARY_BUILD_TYPE);
	}

	/// @brief Get the Settings Library build string
	inline std::string getSettingsLibBuild()
	{
		return std::string("Build: ") + std::to_string(SETTINGS_LIBRARY_BUILD_VERSION);
	}

	/// @brief Get the Settings Library version wide string
	inline std::wstring getSettingsLibVersionW()
	{
		return std::wstring(std::to_wstring(SETTINGS_LIBRARY_MAJOR_VERSION) + L"." + std::to_wstring(SETTINGS_LIBRARY_MINOR_VERSION) + L"." + std::to_wstring(SETTINGS_LIBRARY_REVISION_VERSION) + L"-" + SETTINGS_LIBRARY_BUILD_TYPE_W);
	}

	/// @brief Get the Settings Library build wide string
	inline std::wstring getSettingsLibBuildW()
	{
		return std::wstring(L"Build: ") + std::to_wstring(SETTINGS_LIBRARY_BUILD_VERSION);
	}

	/// @brief Get all version and build information on struct SettingsLibVersion. NOTE: The build type is only given in ASCII.
	inline const SettingsLibVersion getSettingsLibVersionData()
	{
		return SettingsLibVersion{ SETTINGS_LIBRARY_MAJOR_VERSION, SETTINGS_LIBRARY_MINOR_VERSION, SETTINGS_LIBRARY_REVISION_VERSION, SETTINGS_LIBRARY_BUILD_TYPE, SETTINGS_LIBRARY_BUILD_VERSION };
	}
}


#endif // !SETTINGS_LIBRARY_PROPERTIES_HPP