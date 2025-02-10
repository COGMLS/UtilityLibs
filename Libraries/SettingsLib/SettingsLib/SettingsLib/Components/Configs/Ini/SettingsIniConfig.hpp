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
#else
	#if __GNUC__ >= 4
		#ifdef SETTINGS_LIB_EXPORTS
			#define SETTINGS_LIB_API __attribute__((visibility("default")))
		#else
			#define SETTINGS_LIB_API __attribute__((visibility("default")))
		#endif //!SETTINGS_LIB_EXPORTS
	#else
		#ifdef SETTINGS_LIB_EXPORTS
			#define SETTINGS_LIB_API
		#else
			#define SETTINGS_LIB_API
		#endif //!SETTINGS_LIB_EXPORTS
	#endif
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
				// Ini Database:
				//

				std::string lastSectionSearch;
				std::wstring lastSectionSearchW;

				std::map<std::string, SettingsLib::Types::ConfigIniSectionData*> sectionMap;
				std::map<std::wstring, SettingsLib::Types::ConfigIniSectionData*> wSectionMap;

			public:

				//
				// Constructors and destructor:
				//

				/**
				 * @brief Create an empty INI configuration object
				 */
				ConfigIni();

				/**
				 * @brief Create an INI configuration object with an specific name
				 * @param configName Configuration name for INI object.
				 */
				ConfigIni (std::string configName);

				/**
				 * @brief Create an INI configuration object with an specific name with wide strings
				 * @param configName Configuration name for INI object.
				 */
				ConfigIni (std::wstring configName);

				/**
				 * @brief Create an INI configuration object with an specific name
				 * @param configFile Configuration file's path
				 * @param readonly Define if the configuration file will be able to accept modifications
				 * @note If the file doesn't exist, it will be created and if readonly was set as true, will be set to false.
				 * @note The object will be created using strings.
				 */
				ConfigIni (std::filesystem::path configFile, bool readonly);

				/**
				 * @brief Create an INI configuration object with an specific name
				 * @param configFile Configuration file's path
				 * @param readonly Define if the configuration file will be able to accept modifications
				 * @param useWideString Define to use wide strings
				 * @note If the file doesn't exist, it will be created and if readonly was set as true, will be set to false.
				 */
				ConfigIni (std::filesystem::path configFile, bool readonly, bool useWideString);

				~ConfigIni();

				//
				// Methods:
				//

				//
				// Non managed methods by ConfigFileStream:
				//

				/**
				 * @brief Read an INI configuration line
				 */
				void readLine (std::string line);

				/**
				 * @brief Read an INI configuration line
				 * @note If the object wasn't set to work with wide strings, the line won't be read.
				 */
				void readLine (std::wstring line);

				//
				// Managed methods by ConfigFileStream:
				//

				/**
				 * @brief Get direct access to the configuration file stream
				 * @return Return a ConfigurationFileStream pointer if the file is opened
				 */
				SettingsLib::Types::ConfigFileStream* getConfigFileStream();

				//
				// Configuration Database Methods:
				//

				/**
				 * @brief Define the configuration name
				 * @param newName New name for the object
				 * @return -1: If the object is configured to use wide string
				 * @return 0: The configuration name was successful changed
				 * @return 1: Fail to get the original name to fallback in case of fail the operation
				 * @return 2: The path already exists
				 * @return 3: Fail to set a new configuration file
				 * @return 4: Fail to store the configuration name, restoring the original name
				 * @return 5: Fail to open the configuration stream
				 * @return 6: The configuration is empty, try to create the file or use a existing one
				 * @return 7: Fail to change the name
				 */
				int setConfigName (std::string newName);

				/**
				 * @brief Define the configuration name
				 * @param newName New name for the object
				 * @return -1: If the object is configured to use string
				 * @return 0: The configuration name was successful changed
				 * @return 1: Fail to get the original name to fallback in case of fail the operation
				 * @return 2: The path already exists
				 * @return 3: Fail to set a new configuration file
				 * @return 4: Fail to store the configuration name, restoring the original name
				 * @return 5: Fail to open the configuration stream
				 * @return 6: The configuration is empty, try to create the file or use a existing one
				 * @return 7: Fail to change the name
				 */
				int setConfigName (std::wstring newName);

				/**
				 * @brief Get the name defined to the object
				 * @param configName String to hold the configuration name
				 * @return 0: Successful return the configuration name
				 * @return 1: The object is configured to use wide string
				 * @return 2: configName is nullptr
				 * @return 3: Fail to return the configuration name
				 */
				int getConfigName (std::string* configName);

				/**
				 * @brief Get the name defined to the object
				 * @param configName String to hold the configuration name
				 * @return 0: Successful return the configuration name
				 * @return 1: The object is configured to use string
				 * @return 2: configName is nullptr
				 * @return 3: Fail to return the configuration name
				 */
				int getConfigName (std::wstring* configName);

				/**
				 * @brief Get object status to work with wide strings
				 */
				bool isWideData();

				/**
				 * @brief Check if the configuration file object is configured
				 */
				bool isConfigFileOk();

				/**
				 * @brief Check if is using the ConfigFileStream
				 */
				bool isUsingConfigFileStream();

				/**
				 * @brief Save the database in the memory into the configuration file
				 * @return 
				 */
				int saveFile(); // NOT READY

				/**
				 * @brief Load the database inside the file into the memory.
				 * @param discardChanges If the database was marked as "modified" set it as true to discard the unsaved changes. If no changed was made, it won't take any effect.
				 * @return 
				 */
				int loadFile(bool discardChanges); // NOT READY

				/**
				 * @brief Convert the INI database to a vector string with a similar INI file format, allowing to consult using standard C++ or using to write the content in another file.
				 * @param exportValues Export the vector string with database values
				 * @param exportComments Export the vector string with database comments
				 * @return Return the vector string with similar format used in a INI file
				 */
				std::vector<std::string> getConfigMapStr (bool exportValues = true, bool exportComments = true);

				/**
				 * @brief Convert the INI database to a vector string with a similar INI file format, allowing to consult using standard C++ or using to write the content in another file.
				 * @param exportValues Export the vector string with database values
				 * @param exportComments Export the vector string with database comments
				 * @return Return the vector string with similar format used in a INI file
				 */
				std::vector<std::wstring> getConfigMapWstr (bool exportValues = true, bool exportComments = true);

				//
				// Configuration Database Management:
				//

				/**
				 * @brief Get the section list available in the INI database
				 * @param list Pointer to a vector string to store the section list
				 * @return 0: If the operation was successful
				 * @return 1: If the pointer is nullptr
				 * @return 2: If the object was not configured
				 * @return 3: If the object is configured to use wide strings
				 * @return 4: If an exception was found
				 */
				int getSectionList (std::vector<std::string>* list);

				/**
				 * @brief Get the section list available in the INI database
				 * @param list Pointer to a vector string to store the section list
				 * @return 0: If the operation was successful
				 * @return 1: If the pointer is nullptr
				 * @return 2: If the object was not configured
				 * @return 3: If the object is configured to use wide strings
				 * @return 4: If an exception was found
				 */
				int getSectionList (std::vector<std::wstring>* list);

				/**
				 * @brief Get the section data from the INI database
				 * @param sectionName Section name to search and copy to section
				 * @param section Section variable to store a copy of INI section database
				 * @return 0: Found and copied to section variable
				 * @return 1: Section is nullptr
				 * @return 2: Configuration file is not ready to use
				 * @return 3: Object is configured to use wide string
				 * @return 4: Found an exception
				 * @return 5: Not found
				 */
				int getSection (std::string sectionName, SettingsLib::Types::ConfigIniSectionData* section);
				
				/**
				 * @brief Get the section data from the INI database
				 * @param sectionName Section name to search and copy to section
				 * @param section Section variable to store a copy of INI section database
				 * @return 0: Found and copied to section variable
				 * @return 1: Section is nullptr
				 * @return 2: Configuration file is not ready to use
				 * @return 3: Object is configured to use string
				 * @return 4: Found an exception
				 * @return 5: Not found
				 */
				int getSection (std::wstring sectionName, SettingsLib::Types::ConfigIniSectionData* section);

				/**
				 * @brief Get an INI database entry from a section
				 * @param sectionName Database section
				 * @param keyName Key from section database
				 * @param entry Config INI data entry
				 * @return 0: Found and copied the INI entry
				 * @return 1: Section is nullptr
				 * @return 2: Configuration file is not ready to use
				 * @return 3: Object is configured to use wide string
				 * @return 4: Found an exception
				 * @return 5: Not found
				 * @return 6: Entry is not configured to use string
				 */
				int getEntry (std::string sectionName, std::string keyName, SettingsLib::Types::ConfigIniData* entry);
				
				/**
				 * @brief Get an INI database entry from a section
				 * @param sectionName Database section
				 * @param keyName Key from section database
				 * @param entry Config INI data entry
				 * @return 0: Found and copied the INI entry
				 * @return 1: Section is nullptr
				 * @return 2: Configuration file is not ready to use
				 * @return 3: Object is configured to use string
				 * @return 4: Found an exception
				 * @return 5: Not found
				 * @return 6: Entry is not configured to use wide string
				 */
				int getEntry (std::wstring sectionName, std::wstring keyName, SettingsLib::Types::ConfigIniData* entry);

				/**
				 * @brief Set a configuration INI section
				 * @param section Section to add or overwrite if already exists
				 * @return 0: Section was found/new entry was added into the section database
				 * @return 2: Configuration file is not ready to use
				 * @return 3: Object is configured to use wide string
				 * @return 4: Found an exception
				 * @return 5: Section to add is not configured
				 * @return 6: Fail to identify the section name
				 */
				int setSection (SettingsLib::Types::ConfigIniSectionData section);
				
				/**
				 * @brief Set a configuration INI section
				 * @param section Section to add or overwrite if already exists
				 * @return 0: Section was found/new entry was added into the section database
				 * @return 1: Section is nullptr
				 * @return 2: Configuration file is not ready to use
				 * @return 3: Object is configured to use wide string
				 * @return 4: Found an exception
				 * @return 5: Section to add is not configured
				 * @return 6: Fail to identify the section name
				 */
				int setSection (SettingsLib::Types::ConfigIniSectionData* section);

				/**
				 * @brief Add or update an existing entry in the configuration database
				 * @param entry Configuration entry. The entry section data is used to determinate which section will be stored
				 * @return 0: Successfully added or updated the entry
				 * @return 2: Configuration object is not ready to be used or has internal failure
				 * @return 3: The configuration object string setting and entry string setting does not match
				 * @return 4: Catch an exception during the operation
				 * @return 5: Fail to get the section information from entry
				 * @return 6: Section database fail
				 * @return 7: Fail to add the database section to store the new entry data
				 */
				int setEntry (SettingsLib::Types::ConfigIniData entry);

				/**
				 * @brief Add or update an existing entry in the configuration database
				 * @param entry Configuration entry. The entry section data is used to determinate which section will be stored
				 * @return 0: Successfully added or updated the entry
				 * @return 1: Entry is nullptr
				 * @return 2: Configuration object is not ready to be used or has internal failure
				 * @return 3: The configuration object string setting and entry string setting does not match
				 * @return 4: Catch an exception during the operation
				 * @return 5: Fail to get the section information from entry
				 * @return 6: Section database fail
				 * @return 7: Fail to add the database section to store the new entry data
				 */
				int setEntry (SettingsLib::Types::ConfigIniData* entry);
				
				/**
				 * @brief Add an entry overwriting the section and key name. If an entry with the same section and key already exist, the current entry will be updated.
				 * @param sectionName New section name
				 * @param keyName New key name
				 * @param entry Configuration entry. The entry section and key name will be overwrite.
				 * @return 0: Successfully added or updated the entry
				 * @return 2: Configuration object is not ready to be used or has internal failure
				 * @return 3: The configuration object string setting and entry string setting does not match
				 * @return 4: Catch an exception during the operation
				 * @return 5: Fail to get the section information from entry
				 * @return 6: Section database fail
				 * @return 7: Fail to add the database section to store the new entry data
				 * @return 8: Fail to overwrite the section name
				 * @return 9: Fail to overwrite the key name
				 */
				int setEntry (std::string sectionName, std::string keyName, SettingsLib::Types::ConfigIniData entry);
				
				/**
				 * @brief Add an entry overwriting the section and key name. If an entry with the same section and key already exist, the current entry will be updated.
				 * @param sectionName New section name
				 * @param keyName New key name
				 * @param entry Configuration entry. The entry section and key name will be overwrite.
				 * @return 0: Successfully added or updated the entry
				 * @return 1: Entry is nullptr
				 * @return 2: Configuration object is not ready to be used or has internal failure
				 * @return 3: The configuration object string setting and entry string setting does not match
				 * @return 4: Catch an exception during the operation
				 * @return 5: Fail to get the section information from entry
				 * @return 6: Section database fail
				 * @return 7: Fail to add the database section to store the new entry data
				 * @return 8: Fail to overwrite the section name
				 * @return 9: Fail to overwrite the key name
				 */
				int setEntry (std::string sectionName, std::string keyName, SettingsLib::Types::ConfigIniData* entry);

				/**
				 * @brief Add an entry allowing to overwriting the section and/or key name. If an entry with the same section and key already exist, the current entry will be updated. If a section does not exist, a new section will be created.
				 * @param sectionName New section name to entry. If a nullptr is set, the section won't be overwrite.
				 * @param keyName New key name to entry. If a nullptr is set, the key's name won't be overwrite.
				 * @param entry Configuration entry. The entry section and/or key name will be overwrite.
				 * @return 0: Successfully added or updated the entry.
				 * @return 1: Entry is nullptr
				 * @return 2: Configuration object is not ready to be used or has internal failure
				 * @return 3: The configuration object string setting and entry string setting does not match
				 * @return 4: Catch an exception during the operation
				 * @return 5: Fail to get the section information from entry
				 * @return 6: Section database fail
				 * @return 7: Fail to add the database section to store the new entry data
				 * @return 8: Fail to overwrite the section name
				 * @return 9: Fail to overwrite the key name
				 */
				int setEntry (std::string* sectionName, std::string* keyName, SettingsLib::Types::ConfigIniData* entry);
				
				/**
				 * @brief Add an entry overwriting the section and key name. If an entry with the same section and key already exist, the current entry will be updated.
				 * @param sectionName New section name
				 * @param keyName New key name
				 * @param entry Configuration entry. The entry section and key name will be overwrite.
				 * @return 0: Successfully added or updated the entry
				 * @return 2: Configuration object is not ready to be used or has internal failure
				 * @return 3: The configuration object string setting and entry string setting does not match
				 * @return 4: Catch an exception during the operation
				 * @return 5: Fail to get the section information from entry
				 * @return 6: Section database fail
				 * @return 7: Fail to add the database section to store the new entry data
				 * @return 8: Fail to overwrite the section name
				 * @return 9: Fail to overwrite the key name
				 */
				int setEntry (std::wstring sectionName, std::wstring keyName, SettingsLib::Types::ConfigIniData entry);
				
				/**
				 * @brief Add an entry allowing to overwriting the section and/or key name. If an entry with the same section and key already exist, the current entry will be updated. If a section does not exist, a new section will be created.
				 * @param sectionName New section name to entry. If a nullptr is set, the section won't be overwrite.
				 * @param keyName New key name to entry. If a nullptr is set, the key's name won't be overwrite.
				 * @param entry Configuration entry. The entry section and/or key name will be overwrite.
				 * @return 0: Successfully added or updated the entry.
				 * @return 1: Entry is nullptr
				 * @return 2: Configuration object is not ready to be used or has internal failure
				 * @return 3: The configuration object string setting and entry string setting does not match
				 * @return 4: Catch an exception during the operation
				 * @return 5: Fail to get the section information from entry
				 * @return 6: Section database fail
				 * @return 7: Fail to add the database section to store the new entry data
				 * @return 8: Fail to overwrite the section name
				 * @return 9: Fail to overwrite the key name
				 */
				int setEntry (std::wstring sectionName, std::wstring keyName, SettingsLib::Types::ConfigIniData* entry);
				
				/**
				 * @brief Add an entry allowing to overwriting the section and/or key name. If an entry with the same section and key already exist, the current entry will be updated. If a section does not exist, a new section will be created.
				 * @param sectionName New section name to entry. If a nullptr is set, the section won't be overwrite.
				 * @param keyName New key name to entry. If a nullptr is set, the key's name won't be overwrite.
				 * @param entry Configuration entry. The entry section and/or key name will be overwrite.
				 * @return 0: Successfully added or updated the entry.
				 * @return 1: Entry is nullptr
				 * @return 2: Configuration object is not ready to be used or has internal failure
				 * @return 3: The configuration object string setting and entry string setting does not match
				 * @return 4: Catch an exception during the operation
				 * @return 5: Fail to get the section information from entry
				 * @return 6: Section database fail
				 * @return 7: Fail to add the database section to store the new entry data
				 * @return 8: Fail to overwrite the section name
				 * @return 9: Fail to overwrite the key name
				 */
				int setEntry (std::wstring* sectionName, std::wstring* keyName, SettingsLib::Types::ConfigIniData* entry);

				/**
				 * @brief Remove a section from configuration database
				 * @param sectionName Section name to search and remove it
				 * @return 0: If the section was removed with success
				 * @return 1: Configuration object is not ready to use
				 * @return 2: The configuration object is defined to use wide string
				 * @return 3: The configuration database is empty
				 * @return 4: An exception occurred
				 * @return 5: The database does not contain the section
				 */
				int removeSection (std::string sectionName);

				/**
				 * @brief Remove a section from configuration database
				 * @param sectionName Section name to search and remove it
				 * @return 0: If the section was removed with success
				 * @return 1: Configuration object is not ready to use
				 * @return 2: The configuration object is not defined to use wide string
				 * @return 3: The configuration database is empty
				 * @return 4: An exception occurred
				 * @return 5: The database does not contain the section
				 */
				int removeSection (std::wstring sectionName);

				int removeEntry (std::string sectionName, std::string keyName);
				int removeEntry (std::wstring sectionName, std::wstring keyName);

				bool hasSection (std::string sectionName);
				bool hasSection (std::wstring sectionName);

				bool hasEntry (std::string sectionName, std::string keyName);
				bool hasEntry (std::wstring sectionName, std::wstring keyName);
				
				/**
				 * @brief Get the number of sections stored in database
				 */
				size_t numSections();

				/**
				 * @brief Get the number of keys stored in the database
				 */
				size_t numKeys();

				/**
				 * @brief Get the number of keys stored in the section
				 * @param sectionName Section name to search for the number of keys
				 * @note If the configuration object is configured to use wide string, it will return 0
				 */
				size_t numSectionKeys (std::string sectionName);

				/**
				 * @brief Get the number of keys stored in the section
				 * @param sectionName Section name to search for the number of keys
				 * @note If the configuration object is configured to use string, it will return 0
				 */
				size_t numSectionKeys (std::wstring sectionName);
		};
	}
}

#endif // !SETTINGS_INI_CONFIG_HPP