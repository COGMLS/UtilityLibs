#pragma once

#ifndef TEST_HPP
#define TEST_HPP

#include <string>
#include <vector>
#include <iostream>

#include "debug.hpp"

//#define TEST_TOOLS

int testToolsExtractIniData (int i, std::string* line, std::string* section, std::string* key, std::string* value, std::string* comment);

int testToolsConvertValue (std::string* value, SettingsLib::Types::ConfigDataType* type, SettingsLib::Types::ConfigDataUnion* uData);

#endif // !TEST_HPP