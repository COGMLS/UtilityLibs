#pragma once

#ifndef SETTINGS_INI_CONFIG_HPP
#define SETTINGS_INI_CONFIG_HPP

#ifdef WIN32
	#ifdef SETTINGS_LIB_EXPORTS
		#define SETTINGS_LIB_API __declspec(dllexport)
	#else
		#define SETTINGS_LIB_API __declspec(dllimport)
	#endif //!SETTINGS_LIB_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#endif // !WIN32

#include "SettingsIniDefinitions.hpp"
#include "SettingsIniErrorCodes.hpp"
#include "SettingsIniTools.hpp"
#include "SettingsIniConfigData.hpp"

#include <map>
#include <string>
#include <iostream>

namespace SettingsLib
{
	namespace Types
	{
		class SETTINGS_LIB_API ConfigIni
		{
			protected:
				bool isObjConfigured;
				bool useWideData;

				SettingsLib::Types::ConfigDataStore configName;

				std::string lastSectionSearch;

				std::map<std::string, SettingsLib::Types::ConfigIniSectionData*> sectionMap;
				std::map<std::wstring, SettingsLib::Types::ConfigIniSectionData*> wSectionMap;

			public:
				ConfigIni();
				ConfigIni (std::string configName);

				void readLine(std::string line);
		};
	}
}

#endif // !SETTINGS_INI_CONFIG_HPP