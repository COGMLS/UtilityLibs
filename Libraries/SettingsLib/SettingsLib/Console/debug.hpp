#pragma once

#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <string>

#include "SettingsIniTools.hpp"

std::string translateIniLineCheckStatus (SettingsLib::ErrorCodes::IniLineCheckStatus code);

std::string translateIniRawValueConversionStatus (SettingsLib::ErrorCodes::IniRawValueConversionStatus code);

#endif // !DEBUG_HPP