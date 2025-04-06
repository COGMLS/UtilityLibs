#pragma once

#ifndef SETTINGS_LIB_HPP
#define SETTINGS_LIB_HPP

// Library Version components:

#include "SettingsLibVersion.hpp"
#include "SettingsLibExperimentalFeatures.hpp"
#include "SettingsLibVersionHelper.hpp"

// Main Settings Library header

#include "SettingsLibConfig.hpp"
#include "SettingsLibConfigFileStream.hpp"
#include "SettingsLibDataTypes.hpp"
#include "SettingsLibDefinitions.hpp"
#include "SettingsLibErrorCodes.hpp"
#include "SettingsLibTools.hpp"

//
// Components:
//

// Exception:

#include "Components/Exceptions/SettingsLibException.hpp"

// Ini Components:

#include "Components/Configs/Ini/SettingsIniConfig.hpp"
#include "Components/Configs/Ini/SettingsIniConfigData.hpp"
#include "Components/Configs/Ini/SettingsIniDefinitions.hpp"
#include "Components/Configs/Ini/SettingsIniErrorCodes.hpp"
#include "Components/Configs/Ini/SettingsIniTools.hpp"

#endif // !SETTINGS_LIB_HPP