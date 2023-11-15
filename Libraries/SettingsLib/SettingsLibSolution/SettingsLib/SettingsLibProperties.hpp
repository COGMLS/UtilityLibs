#pragma once

#ifndef SETTINGS_LIBRARY_PROPERTIES_HPP
#define SETTINGS_LIBRARY_PROPERTIES_HPP

#include "pch.h"
#include <string>

#define SETTINGS_LIBRARY_MAJOR_VERSION		1
#define SETTINGS_LIBRARY_MINOR_VERSION		4
#define SETTINGS_LIBRARY_REVISION_VERSION	15
#define SETTINGS_LIBRARY_BUILD_TYPE			"beta"
#define SETTINGS_LIBRARY_BUILD_VERSION		20

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

#endif // !SETTINGS_LIBRARY_PROPERTIES_HPP