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
#include "SettingsLibConfigFileStream.hpp"

//#include "SettingsLibConfig.hpp"
//#include "SettingsLibConfigFileStream.hpp"

#include <map>
#include <string>
#include <memory>

namespace SettingsLib
{
	namespace Types
	{
		class SETTINGS_LIB_API ConfigIni
		{
			private:

				//
				// Object controls:
				//

				bool isObjConfigured;										// Define the object as configured
				bool useWideData;											// Define the object to use wstring
				bool isModified;											// Mark the object with modified data
				bool useConfigFile;											// Determinate if the object will use the configFile. This is part of the configFileStream controls
				bool useConfigFileStream;									// Determinate if the object will use the ConfigFileStream.

				//
				// Configuration Ini Info:
				//

				std::filesystem::path configFile;
				SettingsLib::Types::ConfigDataStore configName;				// Define a name to identify the object (This name can be used to save the configuration into a file or be the file's name if already exist)

				//
				// Configuration File Stream:
				//

				std::unique_ptr<SettingsLib::Types::ConfigFileStream> cfgFileStream;

				//
				// Ini Data:
				//

				std::string lastSectionSearch;
				std::wstring lastSectionSearchW;

				std::map<std::string, SettingsLib::Types::ConfigIniSectionData*> sectionMap;
				std::map<std::wstring, SettingsLib::Types::ConfigIniSectionData*> wSectionMap;

			public:

				//
				// Constructors and destructor:
				//

				ConfigIni();
				ConfigIni (std::string configName);
				ConfigIni (std::wstring configName);
				ConfigIni (std::filesystem::path configFile, bool readonly);

				~ConfigIni();

				//
				// Methods:
				//

				int setComment (std::string comment);
				int setComment (std::wstring comment);

				int getComment (std::string* comment);
				int getComment (std::wstring* comment);

				//
				// Non managed methods by ConfigFileStream:
				//

				void readLine (std::string line);
				void readLine (std::wstring line);

				//
				// Managed methods by ConfigFileStream:
				//

				//
				// Configuration Database Methods:
				//

				int getSectionList (std::vector<std::string>& list);
				int getSectionList (std::vector<std::wstring>& list);

				int getSection (std::string sectionName, SettingsLib::Types::ConfigIniSectionData* section, bool sendCopy = true);
				int getSection (std::wstring sectionName, SettingsLib::Types::ConfigIniSectionData* section, bool sendCopy = true);

				int getEntry (std::string sectionName, std::string entryName, SettingsLib::Types::ConfigIniData* entry, bool sendCopy = true);
				int getEntry (std::wstring sectionName, std::wstring entryName, SettingsLib::Types::ConfigIniData* entry, bool sendCopy = true);

				int setSection (std::string sectionName);
				int setSection (std::wstring sectionName);

				//
				// Configuration Database Management:
				//


		};
	}
}

#endif // !SETTINGS_INI_CONFIG_HPP