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
#include <memory>

#include "SettingsLibDataTypes.hpp"
#include "SettingsLibTools.hpp"
#include "SettingsIniErrorCodes.hpp"
#include "SettingsIniDefinitions.hpp"

namespace SettingsLib
{
	namespace Types
	{
		/// @brief Configuration Data for INI files
		class SETTINGS_LIB_API ConfigIniData
		{
			private:
				// Data type control:

				bool objWasConfig;			// Control if the object already was configured or not.
				bool usingWideData;			// Determinate if the object is configured to use wide strings or not.
				short dataStoreType;		// Determinate if will be not configured (0) or only one data (1) or a container (2).

				// Data Section:
				// Data Section only will hold string or wstring data no other data type is allowed here!

				std::unique_ptr<SettingsLib::Types::ConfigStrData> section;
				
				// Data key:
				// Data Key only will hold string or wstring data no other data type is allowed here!
				
				SettingsLib::Types::ConfigStrData key;

				// Data store:

				std::unique_ptr<SettingsLib::Types::ConfigDataStore> data;
				std::unique_ptr<std::vector<SettingsLib::Types::ConfigDataStore>> vdata;

				// Comment store:

				std::unique_ptr<SettingsLib::Types::ConfigStrData> comment;

			public:

				/**
				 * @brief Generate an empty Configuration Ini Data object
				 */
				ConfigIniData();

				/**
				 * @brief Generate a Configuration Ini Data object
				 * @param key INI configuration key
				 */
				ConfigIniData (std::string key);

				/**
				 * @brief Generate a Configuration Ini Data object
				 * @param key INI configuration key
				 */
				ConfigIniData (std::wstring key);

				ConfigIniData (const ConfigIniData& other);

				ConfigIniData (ConfigIniData&& other) noexcept;

				~ConfigIniData();

				// Operators:

				SettingsLib::Types::ConfigIniData& operator= (const SettingsLib::Types::ConfigIniData& other);
				SettingsLib::Types::ConfigIniData& operator= (SettingsLib::Types::ConfigIniData&& other) noexcept;

				// Control methods:

				/**
				 * @brief Verify if the configuration ini data is configured to hold wide strings. This configuration is defined on object's creation by the key type used, or when a key is defined for the first time on the object.
				 */
				bool isWideData();

				/**
				 * @brief Reset completely the object data and it's configuration
				 * @return If the operation was successful, will return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION.
				 * @return If fail, will return CONFIG_INI_STATUS_RESET_OBJECT_FAIL.
				 */
				int resetConfigIniData();

				/**
				 * @brief Delete the data inside the object
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED if the object was not configured. This can happen when a empty object is created or was reset and a key was not defined.
				 * @return If the operation was successful, will return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION.
				 * @return CONFIG_INI_STATUS_CLEAN_DATA_VECTOR_FAIL_UNKNOWN_ERROR on container clean fail.
				 * @return CONFIG_INI_STATUS_CLEAN_DATA_FAIL_UNKNOWN_ERROR on single data clean fail.
				 * @return If the data already was cleaned or doesn't exist, will return CONFIG_INI_STATUS_CLEAN_DATA_ALREADY_EMPTY.
				 */
				int cleanData();

				/**
				 * @brief Get the data type the object is holding.
				 * @param type Variable to receive the type.
				 * @return If the operation was successful return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION.
				 * @return If the data was not set, return CONFIG_INI_STATUS_NO_DATA_AVAILABLE.
				 * @return If the object holds a container, return CONFIG_INI_STATUS_ERROR_GET_DATA_MISSING_CONTAINER_INFO.
				 * @return If the type parameter is nullptr, return CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED if the object was not configured. This can happen when a empty object is created or was reset and a key was not defined.
				 */
				int getType(SettingsLib::Types::ConfigDataType* type);

				/**
				 * @brief Get the data type the object is holding on specify container's position.
				 * @param type Variable to receive the type.
				 * @param pos Container data position to analyze.
				 * @return If the operation was successful return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION.
				 * @return If the data was not set, return CONFIG_INI_STATUS_NO_DATA_AVAILABLE.
				 * @return If the object holds a single data, return CONFIG_INI_STATUS_NO_CONTAINER_AVAILABLE.
				 * @return If the type parameter is nullptr, return CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR.
				 * @return If the pos parameter is out of range, return CONFIG_INI_STATUS_CONTAINER_OUT_OF_RANGE.
				 * @return If an exception occur, return CONFIG_INI_STATUS_CLEAN_DATA_VECTOR_FAIL_UNKNOWN_ERROR.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED if the object was not configured. This can happen when a empty object is created or was reset and a key was not defined.
				 */
				int getType(SettingsLib::Types::ConfigDataType* type, size_t pos);

				// Section methods:

				/**
				 * @brief Verify if the object is part of a section.
				 */
				bool hasSection();

				/**
				 * @brief Remove the section information from the object.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED if the object was not configured. This can happen when a empty object is created or was reset and a key was not defined.
				 * @return If the operation was successful, return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION.
				 * @return If no section is available, CONFIG_INI_STATUS_NO_DATA_AVAILABLE.
				 * @return If an exception occur, CONFIG_INI_STATUS_CLEAN_DATA_FAIL_UNKNOWN_ERROR.
				 */
				int removeSection();

				/**
				 * @brief Get the section's name
				 * @param section Variable to receive the section's name
				 * @return If the operation was successful, return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION.
				 * @return If the section doesn't exist, return CONFIG_INI_STATUS_NO_DATA_AVAILABLE.
				 * @return If the object if configured to wstring, return CONFIG_INI_STATUS_ERROR_GET_STRING_DATA.
				 * @return If the section parameter if a nullptr, CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR.
				 * @return If get the section fail, CONFIG_INI_STATUS_GET_DATA_FAIL.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED if the object was not configured. This can happen when a empty object is created or was reset and a key was not defined.
				 */
				int getSection (std::string* section);

				/**
				 * @brief Get the section's name
				 * @param section Variable to receive the section's name
				 * @return If the operation was successful, return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION.
				 * @return If the section doesn't exist, return CONFIG_INI_STATUS_NO_DATA_AVAILABLE.
				 * @return If the object if configured to wstring, return CONFIG_INI_STATUS_ERROR_GET_WIDE_STRING_DATA.
				 * @return If the section parameter if a nullptr, CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR.
				 * @return If get the section fail, CONFIG_INI_STATUS_GET_DATA_FAIL.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED if the object was not configured. This can happen when a empty object is created or was reset and a key was not defined.
				 */
				int getSection (std::wstring* section);

				/**
				 * @brief Set a section associated with this object.
				 * @param section Variable with the section's name
				 * @return If the operation was successful, return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION.
				 * @return CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR if the section parameter is a nullptr.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED if the object was not configured. This can happen when a empty object is created or was reset and a key was not defined.
				 * @return CONFIG_INI_STATUS_ERROR_SET_STRING_DATA if the object is configured to wide string.
				 * @return CONFIG_INI_STATUS_SET_DATA_FAIL when set the data was failed.
				 * @return CONFIG_INI_STATUS_NO_DATA_TO_SET is an empty string was send.
				 * @return CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION if an exception occur in data allocation.
				 */
				int setSection (std::string section);

				/**
				 * @brief Set a section associated with this object.
				 * @param section Variable with the section's name
				 * @return If the operation was successful, return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION.
				 * @return CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR if the section parameter is a nullptr.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED if the object was not configured. This can happen when a empty object is created or was reset and a key was not defined.
				 * @return CONFIG_INI_STATUS_ERROR_SET_WIDE_STRING_DATA if the object is not configured to wide string.
				 * @return CONFIG_INI_STATUS_SET_DATA_FAIL when set the data was failed.
				 * @return CONFIG_INI_STATUS_NO_DATA_TO_SET is an empty string was send.
				 * @return CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION if an exception occur in data allocation.
				 */
				int setSection (std::wstring section);

				// Key methods:

				/**
				 * @brief Get the key's name
				 * @param key Variable to receive the key's name
				 * @return CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR if key parameter is a nullptr.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED if the object was not configured. This can happen when a empty object is created or was reset and a key was not defined.
				 * @return CONFIG_INI_STATUS_ERROR_GET_STRING_DATA if the object is configured to wide string.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION on successful operations.
				 * @return CONFIG_INI_STATUS_GET_DATA_FAIL if fail to get the key value.
				 */
				int getKey (std::string* key);

				/**
				 * @brief Get the key's name
				 * @param key Variable to receive the key's name
				 * @return CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR if key parameter is a nullptr.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED if the object was not configured. This can happen when a empty object is created or was reset and a key was not defined.
				 * @return CONFIG_INI_STATUS_ERROR_GET_WIDE_STRING_DATA if the object is configured to string.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION on successful operations.
				 * @return CONFIG_INI_STATUS_GET_DATA_FAIL if fail to get the key value.
				 */
				int getKey (std::wstring* key);

				/**
				 * @brief Set a new name for object's key or configure for the first time if a empty object was created or reset.
				 * @param key Variable to send the key's name
				 * @return CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR if key parameter is a nullptr.
				 * @return CONFIG_INI_STATUS_NO_DATA_AVAILABLE if the key is an empty string.
				 * @return CONFIG_INI_STATUS_ERROR_SET_STRING_DATA if the object is configured to wide string.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION on successful operations.
				 * @return CONFIG_INI_STATUS_SET_DATA_FAIL if fail to get the key value.
				 * @note If the object is not configured, this method, will configure it and define the wide string type as false.
				 * @note This is a function wrapper that call the method setKey(std::string* key)
				 */
				int setKey (std::string key);

				/**
				 * @brief Set a new name for object's key or configure for the first time if a empty object was created or reset.
				 * @param key Variable to send the key's name
				 * @return CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR if key parameter is a nullptr.
				 * @return CONFIG_INI_STATUS_NO_DATA_AVAILABLE if the key is an empty string.
				 * @return CONFIG_INI_STATUS_ERROR_SET_WIDE_STRING_DATA if the object is configured to string.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION on successful operations.
				 * @return CONFIG_INI_STATUS_SET_DATA_FAIL if fail to get the key value.
				 * @note If the object is not configured, this method, will configure it and define the wide string type as false.
				 * @note This is a function wrapper that call the method setKey(std::wstring* key)
				 */
				int setKey (std::wstring key);

				// Data methods:

				/**
				 * @brief Check if the object holds a data. This data can be a container or not.
				 * @note If the data is empty, it will return TRUE.
				 */
				bool hasData();

				/**
				 * @brief Get access to the data.
				 * @param data ConfigDataStore pointer
				 * @return CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR if key parameter is a nullptr.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED if the object was not configured. This can happen when a empty object is created or was reset and a key was not defined.
				 * @return CONFIG_INI_STATUS_ERROR_GET_DATA_MISSING_CONTAINER_INFO if a container is inside the object.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION in a successful operation.
				 * @return CONFIG_INI_STATUS_GET_DATA_FAIL when fail to associate the data to data parameter.
				 * @return CONFIG_INI_STATUS_NO_DATA_AVAILABLE no data available inside the object.
				 */
				int getData (SettingsLib::Types::ConfigDataStore* data);

				/**
				 * @brief Get access to the data.
				 * @param data ConfigDataStore pointer
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED if the object was not configured. This can happen when a empty object is created or was reset and a key was not defined.
				 * @return CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION when fails to allocate the new data.
				 * @return CONFIG_INI_STATUS_ERROR_GET_DATA_MISSING_CONTAINER_INFO if a container is inside the object.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION in a successful operation.
				 * @return CONFIG_INI_STATUS_SET_DATA_FAIL when fail to associate the new data.
				 * @return CONFIG_INI_STATUS_NO_DATA_AVAILABLE no data available inside the object.
				 */
				int setData (SettingsLib::Types::ConfigDataStore data);

				/**
				 * @brief Get access to the data.
				 * @param data ConfigDataStore pointer
				 * @return CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR if key parameter is a nullptr.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED if the object was not configured. This can happen when a empty object is created or was reset and a key was not defined.
				 * @return CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION when fails to allocate the new data.
				 * @return CONFIG_INI_STATUS_ERROR_GET_DATA_MISSING_CONTAINER_INFO if a container is inside the object.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION in a successful operation.
				 * @return CONFIG_INI_STATUS_SET_DATA_FAIL when fail to associate the new data.
				 * @return CONFIG_INI_STATUS_NO_DATA_AVAILABLE no data available inside the object.
				 */
				int setData (SettingsLib::Types::ConfigDataStore* data);

				// Container methods:

				/**
				 * @brief Get access to the data inside the container.
				 * @param data ConfigDataStore pointer
				 * @param pos Container's data position
				 * @return CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR if key parameter is a nullptr.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED if the object was not configured. This can happen when a empty object is created or was reset and a key was not defined.
				 * @return CONFIG_INI_STATUS_NO_CONTAINER_AVAILABLE if a container is not available inside the object.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION in a successful operation.
				 * @return CONFIG_INI_STATUS_CONTAINER_OUT_OF_RANGE if the position is out of range.
				 * @return CONFIG_INI_STATUS_GET_DATA_FAIL when fail to associate the data to data parameter.
				 * @return CONFIG_INI_STATUS_NO_DATA_AVAILABLE no data available inside the object.
				 */
				int getData (SettingsLib::Types::ConfigDataStore* data, size_t pos);

				/**
				 * @brief Get access to the all data inside the container.
				 * @param data ConfigDataStore pointer
				 * @return CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR if key parameter is a nullptr.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED if the object was not configured. This can happen when a empty object is created or was reset and a key was not defined.
				 * @return CONFIG_INI_STATUS_NO_CONTAINER_AVAILABLE if a container is not available inside the object.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION in a successful operation.
				 * @return CONFIG_INI_STATUS_GET_DATA_FAIL when fail to associate the data to data parameter.
				 * @return CONFIG_INI_STATUS_NO_DATA_AVAILABLE no data available inside the object.
				 */
				int getContainer (std::vector<SettingsLib::Types::ConfigDataStore>* vData);

				/**
				 * @brief Insert a new data into the container.
				 * @param data ConfigDataStore data
				 * @param pos Container's data position
				 * @param overwrite Overwrite the data on given position. Otherwise will reallocate the other container's data to insert the new one.
				 * @return CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR when a nullptr for data parameter was send.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED if the object was not configured. This can happen when a empty object is created or was reset and a key was not defined.
				 * @return CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION if fail to create the container.
				 * @return CONFIG_INI_STATUS_SET_DATA_FAIL if fail to set the data into the vector.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION if the operation was successful.
				 * @return CONFIG_INI_STATUS_NO_CONTAINER_AVAILABLE if no container is available.
				 * @note If overwrite was defined as FALSE and a position that is out of range, the data will be inserted in the end of the container and return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION if was successful.
				 */
				int insertData (SettingsLib::Types::ConfigDataStore data, size_t pos, bool overwrite);
				
				/**
				 * @brief Check if the object holds a container
				 */
				bool isContainer();

				/**
				 * @brief Verify the container size.
				 * @return Return the container size if exist. Otherwise, will return 0.
				 */
				size_t getContainerSize();

				// Comment methods:

				/**
				 * @brief Check if the object contain a comment.
				 */
				bool hasComment();

				/**
				 * @brief Remove the comment
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED if the object was not configured. This can happen when a empty object is created or was reset and a key was not defined.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION if the comment was removed.
				 * @return CONFIG_INI_STATUS_CLEAN_DATA_FAIL_UNKNOWN_ERROR if an exception occur.
				 * @return CONFIG_INI_STATUS_NO_DATA_AVAILABLE if no comment exist.
				 */
				int cleanComment();

				/**
				 * @brief Get the comment inside the object
				 * @param comment Variable to receive the comment.
				 * @return CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR if a nullptr was send on comment parameter.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED if the object was not configured. This can happen when a empty object is created or was reset and a key was not defined.
				 * @return CONFIG_INI_STATUS_ERROR_GET_STRING_DATA the object is configured to use wide string.
				 * @return CONFIG_INI_STATUS_NO_DATA_AVAILABLE no comment is available.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION if the comment data was copied into comment parameter pointer.
				 * @return CONFIG_INI_STATUS_GET_DATA_FAIL if an exception occur.
				 */
				int getComment (std::string* comment);

				/**
				 * @brief Get the comment inside the object
				 * @param comment Variable to receive the comment.
				 * @return CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR if a nullptr was send on comment parameter.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED if the object was not configured. This can happen when a empty object is created or was reset and a key was not defined.
				 * @return CONFIG_INI_STATUS_ERROR_GET_WIDE_STRING_DATA the object is configured to use wide string.
				 * @return CONFIG_INI_STATUS_NO_DATA_AVAILABLE no comment is available.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION if the comment data was copied into comment parameter pointer.
				 * @return CONFIG_INI_STATUS_GET_DATA_FAIL if an exception occur.
				 */
				int getComment (std::wstring* comment);

				/**
				 * @brief Get the comment inside the object
				 * @param comment Variable to receive the comment.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED if the object was not configured. This can happen when a empty object is created or was reset and a key was not defined.
				 * @return CONFIG_INI_STATUS_ERROR_SET_STRING_DATA the object is configured to use wide string.
				 * @return CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION if fail to allocate.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION if the comment data was copied into comment parameter pointer.
				 * @return CONFIG_INI_STATUS_SET_DATA_FAIL if an exception occur.
				 * @note If the comment doesn't start with a COMMENT_MARK, the function will add automatically.
				 * @note This method is a wrapper that calls setComment(std::string*).
				 */
				int setComment (std::string comment);

				/**
				 * @brief Get the comment inside the object
				 * @param comment Variable to receive the comment.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED if the object was not configured. This can happen when a empty object is created or was reset and a key was not defined.
				 * @return CONFIG_INI_STATUS_ERROR_SET_STRING_DATA the object is configured to use wide string.
				 * @return CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION if fail to allocate.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION if the comment data was copied into comment parameter pointer.
				 * @return CONFIG_INI_STATUS_SET_DATA_FAIL if an exception occur.
				 * @note If the comment doesn't start with a COMMENT_MARK, the function will add automatically.
				 * @note This method is a wrapper that calls setComment(std::wstring*).
				 */
				int setComment (std::wstring comment);
		};

		/// @brief Section Configuration Data for INI files
		class SETTINGS_LIB_API ConfigIniSectionData
		{
			private:
				// Section data:
				
				bool useWideData;					// Control the wide strings
				bool isSectionConfigured;
				SettingsLib::Types::ConfigDataStore sectionName;

				// Section data collection:

				// Section can only hold string or wstring!

				std::map<std::string, SettingsLib::Types::ConfigIniData> keyMap;
				std::map<std::wstring, SettingsLib::Types::ConfigIniData> wKeyMap;

				// Comments for the section:

				std::unique_ptr<SettingsLib::Types::ConfigDataStore> comment;

			public:
				/**
				 * @brief Create an empty object. This object can't be use as configuration section data.
				 */
				ConfigIniSectionData();

				/**
				 * @brief Create a section data
				 * @param section Section's name
				 */
				ConfigIniSectionData (std::string section);

				/**
				 * @brief Create a section with wide string support
				 * @param section Section's name
				 */
				ConfigIniSectionData (std::wstring section);

				ConfigIniSectionData (const SettingsLib::Types::ConfigIniSectionData& other);
				ConfigIniSectionData (SettingsLib::Types::ConfigIniSectionData&& other) noexcept;

				~ConfigIniSectionData();

				SettingsLib::Types::ConfigIniSectionData& operator= (const SettingsLib::Types::ConfigIniSectionData& other);
				SettingsLib::Types::ConfigIniSectionData& operator= (SettingsLib::Types::ConfigIniSectionData&& other) noexcept;

				/**
				 * @brief Get the section's name
				 * @param sectionName Pointer to string to hold the section's name
				 * @return -3 if the sectionName is a nullptr.
				 * @return -2 if the object if configured to use wstring.
				 * @return -1 if the object is not configured.
				 * @return 0 if the sectionName wasn't copied into the pointer data.
				 * @return 1 if the data was successfully copied into the pointer.
				 */
				int getSectionName (std::string* sectionName);

				/**
				 * @brief Get the section's name
				 * @param sectionName Pointer to string to hold the section's name
				 * @return -3 if the sectionName is a nullptr.
				 * @return -2 if the object if configured to use string.
				 * @return -1 if the object is not configured.
				 * @return 0 if the sectionName wasn't copied into the pointer data.
				 * @return 1 if the data was successfully copied into the pointer.
				 */
				int getSectionName (std::wstring* sectionName);

				/**
				 * @brief Get the comments from section.
				 * @param comment String that will hold the comment.
				 * @return -6 if the internal data holds another type that is not a string.
				 * @return -5 if the get comment operation failed.
				 * @return -4 if the comment if wstring.
				 * @return -3 if the internal data type was marked as CONFIG_DATA_FAIL.
				 * @return -2 if the data was marked as CONFIG_DATA_MISSING.
				 * @return -1 if the comment parameter is nullptr.
				 * @return 0 if the operation was successful.
				 * @return 1 if there is no data available in comment.
				 */
				int getComment (std::string* comment);

				/**
				 * @brief Get the comments from section.
				 * @param comment String that will hold the comment.
				 * @return -6 if the internal data holds another type that is not a string.
				 * @return -5 if the get comment operation failed.
				 * @return -4 if the comment if wstring.
				 * @return -3 if the internal data type was marked as CONFIG_DATA_FAIL.
				 * @return -2 if the data was marked as CONFIG_DATA_MISSING.
				 * @return -1 if the comment parameter is nullptr.
				 * @return 0 if the operation was successful.
				 * @return 1 if there is no data available in comment.
				 */
				int getComment (std::wstring* comment);

				/**
				 * @brief Set the comments to the section.
				 * @param comment String that holds the comment.
				 * @return -1 if the object is configured to use wstring.
				 * @return 0 if the operation was successful.
				 * @return 1 if fail to set the data.
				 * @return 2 if an exception was occur during the process. The internal data was marked as "FAIL". Use cleanComment method to reset the state.
				 */
				int setComment (std::string comment);

				/**
				 * @brief Set the comments to the section.
				 * @param comment String that holds the comment.
				 * @return -1 if the object is configured to use wstring.
				 * @return 0 if the operation was successful.
				 * @return 1 if fail to set the data.
				 * @return 2 if an exception was occur during the process. The internal data was marked as "FAIL". Use cleanComment method to reset the state.
				 */
				int setComment (std::wstring comment);

				/**
				 * @brief Clean the comment.
				 */
				bool cleanComment();

				/**
				 * @brief Verify if the section contains a comment.
				 */
				bool hasComment();

				/**
				 * @brief Get the INI data from Section's database.
				 * @param key Key name
				 * @param iniData Pointer that will holds the reference to database or a copy of the data.
				 * @return -2 if the object is configured to use wstring.
				 * @return -1 if the object is not configured.
				 * @return 0 if the key doesn't exist.
				 * @return 1 if the data was copied into the pointer or the reference address was send.
				 */
				int getIniData (std::string key, SettingsLib::Types::ConfigIniData* iniData);

				/**
				 * @brief Get the INI data from Section's database.
				 * @param key Key name
				 * @param iniData Pointer that will holds the reference to database or a copy of the data.
				 * @return -2 if the object is configured to use wstring.
				 * @return -1 if the object is not configured.
				 * @return 0 if the key doesn't exist.
				 * @return 1 if the data was copied into the pointer or the reference address was send.
				 */
				int getIniData (std::wstring key, SettingsLib::Types::ConfigIniData* iniData);

				/**
				 * @brief Get the ConfigIniData reference from the database.
				 * @param key key name. 
				 * @return Return a reference value if the key exist. Otherwise if the object if not configured, using wstring or the database is empty, the return will be nullptr.
				 * @note Careful when manipulating the data. Only call to destroy the iniData from the section class methods. If the pointer reference if not necessary anymore, set it as nullptr.
				 */
				SettingsLib::Types::ConfigIniData* getIniEntryRef (std::string key);

				/**
				 * @brief Get the ConfigIniData reference from the database.
				 * @param key key name. 
				 * @return Return a reference value if the key exist. Otherwise if the object if not configured, using wstring or the database is empty, the return will be nullptr.
				 * @note Careful when manipulating the data. Only call to destroy the iniData from the section class methods. If the pointer reference if not necessary anymore, set it as nullptr.
				 */
				SettingsLib::Types::ConfigIniData* getIniEntryRef (std::wstring key);

				/**
				 * @brief Get the INI database size. This method verify the type of configuration use (string/wstring) and select the correct database to extract the information.
				 * @return Return the size of the database used in section.
				 * @note If the object is not configured the return will be zero.
				 */
				size_t getIniDatabaseSize();

				/**
				 * @brief Check if the object is configured
				 */
				bool isConfigured();

				/**
				 * @brief Check if the object is configured to use wstring
				 */
				bool isWideData();

				/**
				 * @brief Add a new configuration ini data into the section's database
				 * @param data Configuration ini data the will be part of the section.
				 * @return -3 if the section object is not configured.
				 * @return -2 if the section is configured to use string/wstring and the new data doesn't correspond with the same configuration.
				 * @return -1 if an exception was found.
				 * @return 0 if fail to get the key information from the new ConfigIniData.
				 * @return 1 if the configuration was added as a new entry into the database.
				 * @return 2 if the configuration was found in database and was updated with the new data.
				 */
				int addData (SettingsLib::Types::ConfigIniData& data);

				/**
				 * @brief Verify if the section contains a key
				 * @param key Key name
				 * @return -3 if the object is not configured.
				 * @return -2 if the object is defined to use wstring.
				 * @return -1 if the database is empty.
				 * @return 0 if the entry wasn't found in the database.
				 * @return 1 if the entry was found in the database.
				 */
				int contains (std::string key);

				/**
				 * @brief Verify if the section contains a key
				 * @param key Key name
				 * @return -3 if the object is not configured.
				 * @return -2 if the object is defined to use string.
				 * @return -1 if the database is empty.
				 * @return 0 if the entry wasn't found in the database.
				 * @return 1 if the entry was found in the database.
				 */
				int contains (std::wstring key);

				/**
				 * @brief Remove an INI configuration data entry from section data
				 * @param key Key name
				 * @return -3 if the object is not configured.
				 * @return -2 if the object is defined to use wstring.
				 * @return -1 if an exception occur.
				 * @return 0 if the database is empty.
				 * @return 1 if the entry was found and removed from database.
				 * @return 2 if the key wasn't found in the database.
				 */
				int remData (std::string key);

				/**
				 * @brief Remove an INI configuration data entry from section data
				 * @param key Key name
				 * @return -3 if the object is not configured.
				 * @return -2 if the object is defined to use string.
				 * @return -1 if an exception occur.
				 * @return 0 if the database is empty.
				 * @return 1 if the entry was found and removed from database.
				 * @return 2 if the key wasn't found in the database.
				 */
				int remData (std::wstring key);
		};
	}
}

#endif //! SETTINGS_INI_CONFIG_DATA_HPP