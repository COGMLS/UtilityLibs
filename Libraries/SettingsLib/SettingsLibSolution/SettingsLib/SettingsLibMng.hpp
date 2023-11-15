#pragma once

#ifndef SETTINGS_LIBRARY_MANAGER_HPP
#define SETTINGS_LIBRARY_MANAGER_HPP

#include "pch.h"
#include "SettingsLib.hpp"

#include <filesystem>
#include <fstream>
#include <map>
#include <string>
#include <vector>

class SETTINGS_LIB_API ConfigDataMng
{
	private:
		std::vector<std::string> rawFileContent;
		std::filesystem::path filePath;
	public:
		ConfigDataMng(std::filesystem::path configFilePath);


};

#endif // !SETTINGS_LIBRARY_MANAGER_HPP