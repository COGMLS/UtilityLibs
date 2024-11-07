#pragma once

#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <string>

#include "SettingsLib.hpp"

std::string translateIniLineCheckStatus (SettingsLib::ErrorCodes::IniLineCheckStatus code);

std::string translateIniRawValueConversionStatus (SettingsLib::ErrorCodes::IniRawValueConversionStatus code);

std::string convertConfigIniData2Str (SettingsLib::Types::ConfigIniData* data);

#endif // !DEBUG_HPP