#pragma once 

#ifndef SETTINGS_INI_CONFIG_DATA_HPP
#define SETTINGS_INI_CONFIG_DATA_HPP

#ifdef WIN32
	#ifdef SETTINGS_LIB_EXPORTS
		#define SETTINGS_LIB_API __declspec(dllexport)
	#else
		#define SETTINGS_LIB_API __declspec(dllimport)
	#endif //!SETTINGS_LIB_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#endif // !WIN32

#include <map>
#include <string>
#include <vector>

#include "SettingsLibDataTypes.hpp"
#include "SettingsLibTools.hpp"
#include "SettingsIniErrorCodes.hpp"

namespace SettingsLib
{
	namespace Types
	{
		/// @brief Configuration Data for INI files
		class SETTINGS_LIB_API ConfigIniData
		{
			private:
				// Data type control:
				bool usingWideData;

				// Data Section:
				// Data Section only will hold string or wstring data!

				ConfigDataStore* section = nullptr;
				
				// Data key:
				// Data Key only will hold string or wstring data!
				
				ConfigDataStore key;

				// Data store:

				ConfigDataStore* data = nullptr;
				std::vector<ConfigDataStore>* vdata = nullptr;

				// Comment store:

				bool isEmptyComment;
				ConfigDataStore* comment = nullptr;

			public:
				ConfigIniData();
				ConfigIniData (std::string key);
				ConfigIniData (std::wstring key);

				~ConfigIniData();

				// Control methods:

				bool isWideData();

				int cleanData();

				int getType(ConfigDataType* type);

				int getType(ConfigDataType* type, size_t pos);

				// Section methods:

				bool hasSection();
				int removeSection();

				int getSection (std::string* section);
				int getSection (std::wstring* section);

				int setSection (std::string* section);
				int setSection (std::wstring* section);

				// Key methods:

				int getKey (std::string* key);
				int getKey (std::wstring* key);

				// Data methods:

				bool hasData();

				int getData (SettingsLib::Types::ConfigDataStore* data);

				int setData (SettingsLib::Types::ConfigDataStore* data);

				// Container methods:

				int getData (SettingsLib::Types::ConfigDataStore* data, size_t pos);

				int insertData (SettingsLib::Types::ConfigDataStore* data, size_t pos, bool overwrite);
				
				bool isContainer();

				// Comment methods:

				bool hasComment();
				int cleanComment();

				int getComment (std::string* comment);
				int getComment (std::wstring* comment);

				int setComment (std::string comment);
				int setComment (std::wstring comment);
				int setComment (std::string* comment);
				int setComment (std::wstring* comment);
		};

		/// @brief Section Configuration Data for INI files
		class SETTINGS_LIB_API ConfigIniSectionData
		{
			private:
				// Section data:
				
				bool useWideData;					// Control the wide strings
				ConfigDataStore sectionName;

				// Section data collection:

				// Section can only hold string or wstring!

				std::map<std::string, ConfigIniData>* section = nullptr;
				std::map<std::wstring, ConfigIniData>* wSection = nullptr;

				// Comments for the section:

				bool isEmptyComment;
				ConfigDataStore* comment = nullptr;

			public:
				ConfigIniSectionData();
				ConfigIniSectionData (std::string section);
				ConfigIniSectionData (std::wstring section);

				~ConfigIniSectionData();

				std::string getSection();
				std::wstring getSectionW();

				bool isWideData();

				int addData (ConfigIniData data);

				int remData (std::string key);
				int remData (std::wstring key);
		};
	}
}


#endif //! SETTINGS_INI_CONFIG_DATA_HPP