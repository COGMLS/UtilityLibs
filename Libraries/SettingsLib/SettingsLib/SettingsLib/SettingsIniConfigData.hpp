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

				bool objWasConfig;			// Control if the object already was configurated or not.
				bool usingWideData;			// Determinate if the object is configurated to use wide strings or not.

				// Data Section:
				// Data Section only will hold string or wstring data no other data type is allowed here!

				SettingsLib::Types::ConfigDataStore* section = nullptr;
				
				// Data key:
				// Data Key only will hold string or wstring data no other data type is allowed here!
				
				SettingsLib::Types::ConfigDataStore key;

				// Data store:

				SettingsLib::Types::ConfigDataStore* data = nullptr;
				std::vector<SettingsLib::Types::ConfigDataStore>* vdata = nullptr;

				// Comment store:

				SettingsLib::Types::ConfigDataStore* comment = nullptr;

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

				~ConfigIniData();

				// Control methods:

				/**
				 * @brief Verify if the configuration ini data is configurated to hold wide strings. This configuraiton is defined on object's creation by the key type used, or when a key is defined for the first time on the object.
				 */
				bool isWideData();

				/**
				 * @brief Reset completly the object data and it's configuration
				 * @return If the operation was successful, will return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION.
				 * @return If fail, will return CONFIG_INI_STATUS_RESET_OBJECT_FAIL.
				 */
				int resetConfigIniData();

				/**
				 * @brief Delete the data inside the object
				 * @return If the operation was successful, will return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION.
				 * @return CONFIG_INI_STATUS_CLEAN_DATA_VECTOR_FAIL_UNKNOWN_ERROR on container clean fail.
				 * @return CONFIG_INI_STATUS_CLEAN_DATA_FAIL_UNKNOWN_ERROR on single data clean fail.
				 * @return If the data already was cleanned or doesn't exist, will return CONFIG_INI_STATUS_CLEAN_DATA_ALREADY_EMPTY.
				 */
				int cleanData();

				/**
				 * @brief Get the data type the object is holding.
				 * @param type Variable to receave the type.
				 * @return If the operation was successful return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION.
				 * @return If the data was not set, return CONFIG_INI_STATUS_NO_DATA_AVAILABLE.
				 * @return If the object holds a container, return CONFIG_INI_STATUS_ERROR_GET_DATA_MISSING_CONTAINER_INFO.
				 * @return If the type parameter is nullptr, return CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED if the object was not configurated. This can happen when a empty object is created or was reset and a key was not defined.
				 */
				int getType(SettingsLib::Types::ConfigDataType* type);

				/**
				 * @brief Get the data type the object is holding on specify container's position.
				 * @param type Variable to receave the type.
				 * @param pos Container data position to analyze.
				 * @return If the operation was successful return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION.
				 * @return If the data was not set, return CONFIG_INI_STATUS_NO_DATA_AVAILABLE.
				 * @return If the object holds a single data, return CONFIG_INI_STATUS_NO_CONTAINER_AVAILABLE.
				 * @return If the type parameter is nullptr, return CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR.
				 * @return If the pos parameter is out of range, return CONFIG_INI_STATUS_CONTAINER_OUT_OF_RANGE.
				 * @return If an exception occur, return CONFIG_INI_STATUS_CLEAN_DATA_VECTOR_FAIL_UNKNOWN_ERROR.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED if the object was not configurated. This can happen when a empty object is created or was reset and a key was not defined.
				 */
				int getType(SettingsLib::Types::ConfigDataType* type, size_t pos);

				// Section methods:

				/**
				 * @brief Verify if the object is part of a section.
				 */
				bool hasSection();


				/**
				 * @brief Remove the section information from the object.
				 * @return If the operation was successful, return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION.
				 * @return If no section is available, CONFIG_INI_STATUS_NO_DATA_AVAILABLE.
				 * @return If an exception occur, CONFIG_INI_STATUS_CLEAN_DATA_FAIL_UNKNOWN_ERROR.
				 */
				int removeSection();

				/**
				 * @brief Get the section's name
				 * @param section Variable to receave the section's name
				 * @return If the operation was successful, return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION.
				 * @return If the section doesn't exist, return CONFIG_INI_STATUS_NO_DATA_AVAILABLE.
				 * @return If the object if configurated to wstring, return CONFIG_INI_STATUS_ERROR_GET_STRING_DATA.
				 * @return If the section parameter if a nullptr, CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR.
				 * @return If get the section fail, CONFIG_INI_STATUS_GET_DATA_FAIL.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED if the object was not configurated. This can happen when a empty object is created or was reset and a key was not defined.
				 */
				int getSection (std::string* section);

				/**
				 * @brief Get the section's name
				 * @param section Variable to receave the section's name
				 * @return If the operation was successful, return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION.
				 * @return If the section doesn't exist, return CONFIG_INI_STATUS_NO_DATA_AVAILABLE.
				 * @return If the object if configurated to wstring, return CONFIG_INI_STATUS_ERROR_GET_WIDE_STRING_DATA.
				 * @return If the section parameter if a nullptr, CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR.
				 * @return If get the section fail, CONFIG_INI_STATUS_GET_DATA_FAIL.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED if the object was not configurated. This can happen when a empty object is created or was reset and a key was not defined.
				 */
				int getSection (std::wstring* section);

				/**
				 * @brief Set a section associated with this object.
				 * @param section Variable with the section's name
				 * @return If the operation was successfull, return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION.
				 * @return CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR if the section parameter is a nullptr.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED if the object was not configurated. This can happen when a empty object is created or was reset and a key was not defined.
				 * @return CONFIG_INI_STATUS_ERROR_SET_STRING_DATA if the object is configurated to wide string.
				 * @return CONFIG_INI_STATUS_SET_DATA_FAIL when set the data was failed.
				 * @return CONFIG_INI_STATUS_NO_DATA_TO_SET is an empty string was send.
				 * @return CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION if an exception occur in data allocation.
				 */
				int setSection (std::string* section);

				/**
				 * @brief Set a section associated with this object.
				 * @param section Variable with the section's name
				 * @return If the operation was successfull, return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION.
				 * @return CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR if the section parameter is a nullptr.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED if the object was not configurated. This can happen when a empty object is created or was reset and a key was not defined.
				 * @return CONFIG_INI_STATUS_ERROR_SET_WIDE_STRING_DATA if the object is not configurated to wide string.
				 * @return CONFIG_INI_STATUS_SET_DATA_FAIL when set the data was failed.
				 * @return CONFIG_INI_STATUS_NO_DATA_TO_SET is an empty string was send.
				 * @return CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION if an exception occur in data allocation.
				 */
				int setSection (std::wstring* section);

				// Key methods:

				/**
				 * @brief Get the key's name
				 * @param key Variable to receave the key's name
				 * @return CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR if key parameter is a nullptr.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED if the object was not configurated. This can happen when a empty object is created or was reset and a key was not defined.
				 * @return CONFIG_INI_STATUS_ERROR_GET_STRING_DATA if the object is configurated to wide string.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION on successful operations.
				 * @return CONFIG_INI_STATUS_GET_DATA_FAIL if fail to get the key value.
				 */
				int getKey (std::string* key);

				/**
				 * @brief Get the key's name
				 * @param key Variable to receave the key's name
				 * @return CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR if key parameter is a nullptr.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED if the object was not configurated. This can happen when a empty object is created or was reset and a key was not defined.
				 * @return CONFIG_INI_STATUS_ERROR_GET_WIDE_STRING_DATA if the object is configurated to string.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION on successful operations.
				 * @return CONFIG_INI_STATUS_GET_DATA_FAIL if fail to get the key value.
				 */
				int getKey (std::wstring* key);

				/**
				 * @brief Set a new name for object's key or configurate for the first time if a empty object was created or reset.
				 * @param key Variable to send the key's name
				 * @return CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR if key parameter is a nullptr.
				 * @return CONFIG_INI_STATUS_NO_DATA_AVAILABLE if the key is an empty string.
				 * @return CONFIG_INI_STATUS_ERROR_SET_STRING_DATA if the object is configurated to wide string.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION on successful operations.
				 * @return CONFIG_INI_STATUS_SET_DATA_FAIL if fail to get the key value.
				 * @note If the object is not configurated, this method, will configurate it and define the wide string type as false.
				 * @note This is a function wrapper that call the method setKey(std::string* key)
				 */
				int setKey (std::string key);

				/**
				 * @brief Set a new name for object's key or configurate for the first time if a empty object was created or reset.
				 * @param key Variable to send the key's name
				 * @return CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR if key parameter is a nullptr.
				 * @return CONFIG_INI_STATUS_NO_DATA_AVAILABLE if the key is an empty string.
				 * @return CONFIG_INI_STATUS_ERROR_SET_WIDE_STRING_DATA if the object is configurated to string.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION on successful operations.
				 * @return CONFIG_INI_STATUS_SET_DATA_FAIL if fail to get the key value.
				 * @note If the object is not configurated, this method, will configurate it and define the wide string type as false.
				 * @note This is a function wrapper that call the method setKey(std::wstring* key)
				 */
				int setKey (std::wstring key);

				/**
				 * @brief Set a new name for object's key or configurate for the first time if a empty object was created or reset.
				 * @param key Variable to send the key's name
				 * @return CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR if key parameter is a nullptr.
				 * @return CONFIG_INI_STATUS_NO_DATA_AVAILABLE if the key is an empty string.
				 * @return CONFIG_INI_STATUS_ERROR_SET_STRING_DATA if the object is configurated to wide string.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION on successful operations.
				 * @return CONFIG_INI_STATUS_SET_DATA_FAIL if fail to get the key value.
				 * @note If the object is not configurated, this method, will configurate it and define the wide string type as false.
				 */
				int setKey (std::string* key);

				/**
				 * @brief Set a new name for object's key or configurate for the first time if a empty object was created or reset.
				 * @param key Variable to send the key's name
				 * @return CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR if key parameter is a nullptr.
				 * @return CONFIG_INI_STATUS_NO_DATA_AVAILABLE if the key is an empty string.
				 * @return CONFIG_INI_STATUS_ERROR_SET_WIDE_STRING_DATA if the object is configurated to string.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION on successful operations.
				 * @return CONFIG_INI_STATUS_SET_DATA_FAIL if fail to get the key value.
				 * @note If the object is not configurated, this method, will configurate it and define the wide string type as false.
				 */
				int setKey (std::wstring* key);

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
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED if the object was not configurated. This can happen when a empty object is created or was reset and a key was not defined.
				 * @return CONFIG_INI_STATUS_ERROR_GET_DATA_MISSING_CONTAINER_INFO if a container is inside the object.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION in a successful operation.
				 * @return CONFIG_INI_STATUS_GET_DATA_FAIL when fail to associate the data to data parameter.
				 * @return CONFIG_INI_STATUS_NO_DATA_AVAILABLE no data available inside the object.
				 */
				int getData (SettingsLib::Types::ConfigDataStore* data);

				/**
				 * @brief Get access to the data.
				 * @param data ConfigDataStore pointer
				 * @return CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR if key parameter is a nullptr.
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED if the object was not configurated. This can happen when a empty object is created or was reset and a key was not defined.
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
				 * @return CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURATED if the object was not configurated. This can happen when a empty object is created or was reset and a key was not defined.
				 * @return CONFIG_INI_STATUS_NO_CONTAINER_AVAILABLE if a container is not available inside the object.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION in a successful operation.
				 * @return CONFIG_INI_STATUS_CONTAINER_OUT_OF_RANGE if the position is out of range.
				 * @return CONFIG_INI_STATUS_GET_DATA_FAIL when fail to associate the data to data parameter.
				 * @return CONFIG_INI_STATUS_NO_DATA_AVAILABLE no data available inside the object.
				 */
				int getData (SettingsLib::Types::ConfigDataStore* data, size_t pos);

				/**
				 * @brief Get access to the data inside the container.
				 * @param data ConfigDataStore pointer
				 * @param pos Container's data position
				 * @param overwrite Overwrite the data on given position. Otherwise will reallocate the other container's data to insert the new one.
				 * @return CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR when a nullptr for data parameter was send.
				 * @return CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION if fail to create the container.
				 * @return CONFIG_INI_STATUS_SET_DATA_FAIL if fail to set the data into the vector.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION if the operation was successfull.
				 * @return CONFIG_INI_STATUS_NO_CONTAINER_AVAILABLE if no container is available.
				 * @note If overwrite was defined as FALSE and a position that is out of range, the data will be inserted in the end of the container and return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION if was successful.
				 */
				int insertData (SettingsLib::Types::ConfigDataStore* data, size_t pos, bool overwrite);
				
				/**
				 * @brief Check if the object holds a container
				 */
				bool isContainer();

				/**
				 * @brief Verify the container size.
				 * @return Return the container size if exist. Otherwise, will return 0.
				 */
				size_t getConainerSize();

				// Comment methods:

				/**
				 * @brief Check if the object conatain a comment.
				 */
				bool hasComment();

				/**
				 * @brief Remove the comment
				 */
				int cleanComment();

				/**
				 * @brief Get the comment inside the object
				 * @param comment Variable to receave the comment.
				 * @return CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR if a nullptr was send on comment parameter.
				 * @return CONFIG_INI_STATUS_ERROR_GET_STRING_DATA the object is configurated to use wide string.
				 * @return CONFIG_INI_STATUS_NO_DATA_AVAILABLE no comment is available.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION if the comment data was copied into comment parameter pointer.
				 * @return CONFIG_INI_STATUS_GET_DATA_FAIL if an exception occur.
				 */
				int getComment (std::string* comment);

				/**
				 * @brief Get the comment inside the object
				 * @param comment Variable to receave the comment.
				 * @return CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR if a nullptr was send on comment parameter.
				 * @return CONFIG_INI_STATUS_ERROR_GET_WIDE_STRING_DATA the object is configurated to use wide string.
				 * @return CONFIG_INI_STATUS_NO_DATA_AVAILABLE no comment is available.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION if the comment data was copied into comment parameter pointer.
				 * @return CONFIG_INI_STATUS_GET_DATA_FAIL if an exception occur.
				 */
				int getComment (std::wstring* comment);

				/**
				 * @brief Get the comment inside the object
				 * @param comment Variable to receave the comment.
				 * @return CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR if a nullptr was send on comment parameter.
				 * @return CONFIG_INI_STATUS_ERROR_SET_STRING_DATA the object is configurated to use wide string.
				 * @return CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION if fail to allocate.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION if the comment data was copied into comment parameter pointer.
				 * @return CONFIG_INI_STATUS_SET_DATA_FAIL if an exception occur.
				 * @note If the comment doesn't start with a COMMENT_MARK, the function will add automatically.
				 * @note This method is a wrapper that calls setComment(std::string*).
				 */
				int setComment (std::string comment);

				/**
				 * @brief Get the comment inside the object
				 * @param comment Variable to receave the comment.
				 * @return CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR if a nullptr was send on comment parameter.
				 * @return CONFIG_INI_STATUS_ERROR_SET_STRING_DATA the object is configurated to use wide string.
				 * @return CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION if fail to allocate.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION if the comment data was copied into comment parameter pointer.
				 * @return CONFIG_INI_STATUS_SET_DATA_FAIL if an exception occur.
				 * @note If the comment doesn't start with a COMMENT_MARK, the function will add automatically.
				 * @note This method is a wrapper that calls setComment(std::wstring*).
				 */
				int setComment (std::wstring comment);

				/**
				 * @brief Get the comment inside the object
				 * @param comment Variable to receave the comment.
				 * @return CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR if a nullptr was send on comment parameter.
				 * @return CONFIG_INI_STATUS_ERROR_SET_STRING_DATA the object is configurated to use wide string.
				 * @return CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION if fail to allocate.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION if the comment data was copied into comment parameter pointer.
				 * @return CONFIG_INI_STATUS_SET_DATA_FAIL if an exception occur.
				 * @note If the comment doesn't start with a COMMENT_MARK, the function will add automatically.
				 */
				int setComment (std::string* comment);

				/**
				 * @brief Get the comment inside the object
				 * @param comment Variable to receave the comment.
				 * @return CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR if a nullptr was send on comment parameter.
				 * @return CONFIG_INI_STATUS_ERROR_SET_STRING_DATA the object is configurated to use wide string.
				 * @return CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION if fail to allocate.
				 * @return CONFIG_INI_STATUS_SUCCESSFUL_OPERATION if the comment data was copied into comment parameter pointer.
				 * @return CONFIG_INI_STATUS_SET_DATA_FAIL if an exception occur.
				 * @note If the comment doesn't start with a COMMENT_MARK, the function will add automatically.
				 */
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