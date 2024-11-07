#pragma once 

#ifndef SETTINGS_LIB_DATA_TYPES_HPP
#define SETTINGS_LIB_DATA_TYPES_HPP

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

#include <string>
#include <vector>
#include <utility>
#include <memory>

namespace SettingsLib
{
	namespace Types
	{
		/// @brief Settings Library Version struct
		struct SettingsLibVersion
		{
			unsigned int major;
			unsigned int minor;
			unsigned int revision;
			char buildType[8];
			unsigned int build;
		};

		/// @brief Configuration Data for Container Type
		enum ConfigDataContainerType : int
		{
			SETTINGS_LIB_CONFIG_DATA_CONTAINER_NO_CONTAINER,	// Used for ConfigDataType union or any other data that's no a container type
			SETTINGS_LIB_CONFIG_DATA_CONTAINER_VECTOR,
			SETTINGS_LIB_CONFIG_DATA_CONTAINER_ARRAY,			// Reserved for future use
			SETTINGS_LIB_CONFIG_DATA_CONTAINER_TREE,			// Reserved for future use
			SETTINGS_LIB_CONFIG_DATA_CONTAINER_OTHER			// Reserved for types that didn't match any other in ConfigDataContainerType
		};

		/// @brief Configuration Data Type control
		enum ConfigDataType : int
		{
			SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_MISSING = -1,
			SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_FAIL,
			SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY,
			SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_UNSIGNED_INTEGER,
			SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_INTEGER,
			SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_FLOAT,
			SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING,
			SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_BOOLEAN,
			SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_WSTRING
		};

		/// @brief Configuration Data Union
		union ConfigDataUnion
		{
			unsigned long long ull;
			long long ll;
			double d;
			bool b;
		};

		/// @brief Configuration String Data store
		class SETTINGS_LIB_API ConfigStrData
		{
			private:

				//
				// Configuration String Data:
				//

				SettingsLib::Types::ConfigDataType type;
				std::unique_ptr<std::string> s;
				std::unique_ptr<std::wstring> w;

			public:

				ConfigStrData();
				ConfigStrData (std::string str);
				ConfigStrData (std::wstring str);

				ConfigStrData (const SettingsLib::Types::ConfigStrData& other);

				ConfigStrData (SettingsLib::Types::ConfigStrData&& other) noexcept;

				~ConfigStrData();

				SettingsLib::Types::ConfigStrData& operator= (std::string str);
				SettingsLib::Types::ConfigStrData& operator= (std::wstring str);
				SettingsLib::Types::ConfigStrData& operator= (const SettingsLib::Types::ConfigStrData& other);
				SettingsLib::Types::ConfigStrData& operator= (SettingsLib::Types::ConfigStrData&& other) noexcept;
				
				friend bool operator== (const SettingsLib::Types::ConfigStrData& lhs, const SettingsLib::Types::ConfigStrData& rhs);
				friend bool operator!= (const SettingsLib::Types::ConfigStrData& lhs, const SettingsLib::Types::ConfigStrData& rhs);

				SettingsLib::Types::ConfigDataType getDataType();

				std::string getStr();
				std::wstring getStrW();

				bool setStr(std::string str);
				bool setStr(std::wstring str);

				bool cleanData();
		};

		/// @brief Configuration Data Store to hold the data type and union data with all data set and get controls
		class SETTINGS_LIB_API ConfigDataStore
		{
			private:
				
				//
				// Configuration Data Store variables:
				//

				// Data type: By default the type should be always defined as EMPTY when creating the object data store
				SettingsLib::Types::ConfigDataType type = SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_CONFIG_DATA_EMPTY;

				SettingsLib::Types::ConfigDataUnion data;
				std::unique_ptr<SettingsLib::Types::ConfigStrData> strData;
				
				/**
				 * @brief String data cleaner. If a string or wstring was set in the data store, the method will remove it. Otherwise will do nothing.
				 * @return Return TRUE in successful operations.
				 */
				bool cleanStringData();

				bool allocStringData();

			public:

				/**
				 * @brief Create a ConfigDataStore object marked as "EMPTY".
				 */
				ConfigDataStore();

				/**
				 * @brief Copy constructor
				 * @param other Other ConfigDataStore object
				 */
				ConfigDataStore (const SettingsLib::Types::ConfigDataStore& other);

				/**
				 * @brief Move constructor
				 * @param other Other ConfigDataStore object
				 */
				ConfigDataStore (SettingsLib::Types::ConfigDataStore&& other) noexcept;

				/**
				 * @brief Create a ConfigDataStore object that will hold a unsigned long long.
				 * @param data Data that should be set in data store
				 */
				ConfigDataStore (unsigned long long data);

				/**
				 * @brief Create a ConfigDataStore object that will hold a long long.
				 * @param data Data that should be set in data store
				 */
				ConfigDataStore (long long data);

				/**
				 * @brief Create a ConfigDataStore object that will hold a double.
				 * @param data Data that should be set in data store
				 */
				ConfigDataStore (double data);

				/**
				 * @brief Create a ConfigDataStore object that will hold a bool.
				 * @param data Data that should be set in data store
				 */
				ConfigDataStore (bool data);

				/**
				 * @brief Create a ConfigDataStore object that will hold a string.
				 * @param data Data that should be set in data store
				 */
				ConfigDataStore (std::string data);

				/**
				 * @brief Create a ConfigDataStore object that will hold a wstring.
				 * @param data Data that should be set in data store
				 */
				ConfigDataStore (std::wstring data);

				~ConfigDataStore();

				/// @brief Get the current data type the data store is holding
				SettingsLib::Types::ConfigDataType getDataType() const;

				/**
				 * @brief Clean the data store
				 * @return Return TRUE if the data was cleaned with success and marked as "EMPTY".
				 */
				bool cleanData();

				// Assign data operators:
				
				SettingsLib::Types::ConfigDataStore& operator= (unsigned short data);
				SettingsLib::Types::ConfigDataStore& operator= (unsigned int data);
				SettingsLib::Types::ConfigDataStore& operator= (unsigned long data);
				SettingsLib::Types::ConfigDataStore& operator= (unsigned long long data);
				SettingsLib::Types::ConfigDataStore& operator= (short data);
				SettingsLib::Types::ConfigDataStore& operator= (int data);
				SettingsLib::Types::ConfigDataStore& operator= (long data);
				SettingsLib::Types::ConfigDataStore& operator= (long long data);
				SettingsLib::Types::ConfigDataStore& operator= (float data);
				SettingsLib::Types::ConfigDataStore& operator= (double data);
				SettingsLib::Types::ConfigDataStore& operator= (bool data);
				SettingsLib::Types::ConfigDataStore& operator= (char data);
				SettingsLib::Types::ConfigDataStore& operator= (char data[]);
				SettingsLib::Types::ConfigDataStore& operator= (const char data[]);
				SettingsLib::Types::ConfigDataStore& operator= (wchar_t data);
				SettingsLib::Types::ConfigDataStore& operator= (wchar_t data[]);
				SettingsLib::Types::ConfigDataStore& operator= (const wchar_t data[]);
				SettingsLib::Types::ConfigDataStore& operator= (std::string data);
				SettingsLib::Types::ConfigDataStore& operator= (std::wstring data);

				// Copy and Move operators:

				SettingsLib::Types::ConfigDataStore& operator= (const SettingsLib::Types::ConfigDataStore& other);
				SettingsLib::Types::ConfigDataStore& operator= (SettingsLib::Types::ConfigDataStore&& other) noexcept;
				
				
				/**
				 * @brief Get the data value
				 * @param data Variable to store a copy of the data
				 * @return -2: If a exception occur. This could be happen when a nullptr was send.
				 * @return -1: When the data type was marked as "FAIL". The data stored was lost.
				 * @return 0: When the ConfigDataStore object is marked as "EMPTY".
				 * @return 1: The data was successfully copied into data variable.
				 * @return 2: The data store has another data type.
				 */
				int getData (unsigned long long* data);

				/**
				 * @brief Get the data value
				 * @param data Variable to store a copy of the data
				 * @return -2: If a exception occur. This could be happen when a nullptr was send.
				 * @return -1: When the data type was marked as "FAIL". The data stored was lost.
				 * @return 0: When the ConfigDataStore object is marked as "EMPTY".
				 * @return 1: The data was successfully copied into data variable.
				 * @return 2: The data store has another data type.
				 */
				int getData (long long* data);

				/**
				 * @brief Get the data value
				 * @param data Variable to store a copy of the data
				 * @return -2: If a exception occur. This could be happen when a nullptr was send.
				 * @return -1: When the data type was marked as "FAIL". The data stored was lost.
				 * @return 0: When the ConfigDataStore object is marked as "EMPTY".
				 * @return 1: The data was successfully copied into data variable.
				 * @return 2: The data store has another data type.
				 */
				int getData (double* data);

				/**
				 * @brief Get the data value
				 * @param data Variable to store a copy of the data
				 * @return -2: If a exception occur. This could be happen when a nullptr was send.
				 * @return -1: When the data type was marked as "FAIL". The data stored was lost.
				 * @return 0: When the ConfigDataStore object is marked as "EMPTY".
				 * @return 1: The data was successfully copied into data variable.
				 * @return 2: The data store has another data type.
				 */
				int getData (bool* data);

				/**
				 * @brief Get the data value
				 * @param data Variable to store a copy of the data
				 * @return -3: If the string data is missing.
				 * @return -2: If a exception occur. This could be happen when a nullptr was send.
				 * @return -1: When the data type was marked as "FAIL". The data stored was lost.
				 * @return 0: When the ConfigDataStore object is marked as "EMPTY".
				 * @return 1: The data was successfully copied into data variable.
				 * @return 2: The data store has another data type.
				 */
				int getData (std::string* data);

				/**
				 * @brief Get the data value
				 * @param data Variable to store a copy of the data
				 * @return -3: If the string data is missing.
				 * @return -2: If a exception occur. This could be happen when a nullptr was send.
				 * @return -1: When the data type was marked as "FAIL". The data stored was lost.
				 * @return 0: When the ConfigDataStore object is marked as "EMPTY".
				 * @return 1: The data was successfully copied into data variable.
				 * @return 2: The data store has another data type.
				 */
				int getData (std::wstring* data);
				
				/**
				 * @brief Set the data into the Data Store
				 * @param data Variable to send a copy of the data
				 * @return 0: The data was successfully copied into data store.
				 * @return 1: Fail to clean the previous data (clean string data value fail).
				 * @return 2: An exception occur. The data store type was marked as "FAIL" and the value was lost.
				 */
				int setData (unsigned short data);
				int setData (unsigned int data);
				int setData (unsigned long data);
				int setData (unsigned long long data);

				/**
				 * @brief Set the data into the Data Store
				 * @param data Variable to send a copy of the data
				 * @return 0: The data was successfully copied into data store.
				 * @return 1: Fail to clean the previous data (clean string data value fail).
				 * @return 2: An exception occur. The data store type was marked as "FAIL" and the value was lost.
				 */
				int setData (short data);
				int setData (int data);
				int setData (long data);
				int setData (long long data);

				/**
				 * @brief Set the data into the Data Store
				 * @param data Variable to send a copy of the data
				 * @return 0: The data was successfully copied into data store.
				 * @return 1: Fail to clean the previous data (clean string data value fail).
				 * @return 2: An exception occur. The data store type was marked as "FAIL" and the value was lost.
				 */
				int setData (float data);
				int setData (double data);

				/**
				 * @brief Set the data into the Data Store
				 * @param data Variable to send a copy of the data
				 * @return 0: The data was successfully copied into data store.
				 * @return 1: Fail to clean the previous data (clean string data value fail).
				 * @return 2: An exception occur. The data store type was marked as "FAIL" and the value was lost.
				 */
				int setData (bool data);

				/**
				 * @brief Set the data into the Data Store
				 * @param data Variable to send a copy of the data
				 * @return 0: The data was successfully copied into data store.
				 * @return 1: Fail to clean the previous data (clean string data value fail).
				 * @return 2: An exception occur. The data store type was marked as "FAIL" and the value was lost.
				 */
				int setData (char data);

				/**
				 * @brief Set the data into the Data Store
				 * @param data Variable to send a copy of the data
				 * @return 0: The data was successfully copied into data store.
				 * @return 1: Fail to clean the previous data (clean string data value fail).
				 * @return 2: An exception occur. The data store type was marked as "FAIL" and the value was lost.
				 * @return 3: The value is a nullptr.
				 */
				int setData (char data[]);
				int setData (const char data[]);

				/**
				 * @brief Set the data into the Data Store
				 * @param data Variable to send a copy of the data
				 * @return 0: The data was successfully copied into data store.
				 * @return 1: Fail to clean the previous data (clean string data value fail).
				 * @return 2: An exception occur. The data store type was marked as "FAIL" and the value was lost.
				 */
				int setData (wchar_t data);

				/**
				 * @brief Set the data into the Data Store
				 * @param data Variable to send a copy of the data
				 * @return 0: The data was successfully copied into data store.
				 * @return 1: Fail to clean the previous data (clean string data value fail).
				 * @return 2: An exception occur. The data store type was marked as "FAIL" and the value was lost.
				 * @return 3: The value is a nullptr.
				 */
				int setData (wchar_t data[]);
				int setData (const wchar_t data[]);

				/**
				 * @brief Set the data into the Data Store
				 * @param data Variable to send a copy of the data
				 * @return 0: The data was successfully copied into data store.
				 * @return 1: Fail to clean the previous data (clean string data value fail).
				 * @return 2: An exception occur. The data store type was marked as "FAIL" and the value was lost.
				 */
				int setData (std::string data);

				/**
				 * @brief Set the data into the Data Store
				 * @param data Variable to send a copy of the data
				 * @return 0: The data was successfully copied into data store.
				 * @return 1: Fail to clean the previous data (clean string data value fail).
				 * @return 2: An exception occur. The data store type was marked as "FAIL" and the value was lost.
				 */
				int setData (std::wstring data);
		};
	}
}

#endif //! SETTINGS_LIB_DATA_TYPES_HPP