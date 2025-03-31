#pragma once

#ifndef LOGGER_DATA_STORE_HPP
#define LOGGER_DATA_STORE_HPP

#ifdef WIN32
	#ifdef LOGGER_EXPORTS
		#define LOGGER_LIB_API __declspec(dllexport)
	#else
		#define LOGGER_LIB_API __declspec(dllimport)
	#endif //!LOGGER_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#else
	#if __GNUC__ >= 4
		#ifdef LOGGER_EXPORTS
			#define LOGGER_LIB_API __attribute__((visibility("default")))
		#else
			#define LOGGER_LIB_API __attribute__((visibility("default")))
		#endif //!LOGGER_EXPORTS
	#else
		#ifdef LOGGER_EXPORTS
			#define LOGGER_LIB_API
		#else
			#define LOGGER_LIB_API
		#endif //!LOGGER_EXPORTS
	#endif
#endif // !WIN32

#include "LoggerExperimental.hpp"

#ifdef WIN32
#include "pch.h"
#endif // !WIN32

#include <chrono>
#include <memory>
#include <string>

#include "LoggerDateTime.hpp"

#ifdef LOGGER_ENABLE_EXPERIMENTAL_CUSTOM_EXCEPTIONS
#include "LoggerException.hpp"
#endif // !LOGGER_ENABLE_EXPERIMENTAL_CUSTOM_EXCEPTIONS

/// @brief Log entry type
enum LOGGER_LIB_API LogDataType
{
	LOG_NULL_DATA_ENTRY,
	LOG_UNSIGNED_INTEGER_ENTRY,
	LOG_INTEGER_ENTRY,
	LOG_FLOAT_ENTRY,
	LOG_BOOLEAN_ENTRY,
	LOG_STRING_ENTRY,
	LOG_WSTRING_ENTRY,
	LOG_DATE_TIME_ENTRY,
	LOG_DATE_TIME_HIGH_PRECISION_ENTRY
};

/// @brief Log entry data
union LogEntryData
{
	unsigned long long LOG_ENTRY_UINT;
	long long LOG_ENTRY_INT;
	double LOG_ENTRY_FLOAT;
	bool LOG_ENTRY_BOOL;
	//LoggerLocalDateTime LOG_ENTRY_DATE_TIME;	// Disable to reduce memory consume.
};

/**
 * @brief New Log storage, focus on better memory efficiency and easier way to use different datatypes
 */
class LOGGER_LIB_API LogDataStore
{
	private:

		//
		// Flags:
		//

		LogDataType type;	// Determinate the type of data is available. If LOG_NULL_DATA_ENTRY is set, it means all data store variables are nullptrs.
		
		//
		// Data store:
		//

		std::unique_ptr<std::string> str;
		std::unique_ptr<std::wstring> wstr;
		std::unique_ptr<LogEntryData> unionVal;
		std::unique_ptr<LoggerLocalDateTime> localDt;

		/// @brief Clean the data store pointers. If set LOG_NULL_DATA_ENTRY, will preserve no data and set the 'type' flag as LOG_NULL_DATA_ENTRY.
		void cleanData(LogDataType preserve = LogDataType::LOG_NULL_DATA_ENTRY);

	public:

		//
		// Constructors:
		//

		LogDataStore();

		//
		// Single data constructors:
		//

		LogDataStore (bool data);

		LogDataStore (char data);

		LogDataStore (wchar_t data);
		
		LogDataStore (short data);
		
		LogDataStore (unsigned short data);
		
		LogDataStore (int data);
		
		LogDataStore (unsigned int data);
		
		LogDataStore (long data);
		
		LogDataStore (unsigned long data);
		
		LogDataStore (long long data);
		
		LogDataStore (unsigned long long data);
		
		LogDataStore (float data);
		
		LogDataStore (double data);

		//
		// String data constructors:
		//
		
		LogDataStore (char* data);
	
		LogDataStore (const char* data);

		LogDataStore (wchar_t* data);

		LogDataStore (const wchar_t* data);

		LogDataStore (std::string data);

		LogDataStore (std::wstring data);

		//
		// Log Date and Time struct:
		//
		
		/**
		 * @brief Create a Log Data Store to store any type of data compatible with LoggerLib
		 * @param data Data to be stored
		 * @note If the data is in high precision, the type will be automatically defined as LOG_DATE_TIME_HIGH_PRECISION_ENTRY
		 */
		LogDataStore (LoggerLocalDateTime data);

		/**
		 * @brief Create a Log Data Store to store any type of data compatible with LoggerLib
		 * @param data Data to be stored
		 * @param highPrecisionTime Define if the high precision will be preserved. If the data is not in high precision, no modifications on datatime information will be removed.
		 */
		LogDataStore (LoggerLocalDateTime data, bool highPrecisionTime);

		// ---------------------------- //

		LogDataStore (const LogDataStore& other);

		LogDataStore (LogDataStore&& other) noexcept;

		//
		// Destructor:
		//

		~LogDataStore();

		//
		// Operators:
		//

		LogDataStore& operator= (const LogDataStore& other);
		LogDataStore& operator= (LogDataStore&& other) noexcept;

		// Operators to set new data. All of them are wrappers to use setData method:

		LogDataStore& operator= (const bool& data);
		LogDataStore& operator= (const char& data);
		LogDataStore& operator= (const wchar_t& data);
		LogDataStore& operator= (const short& data);
		LogDataStore& operator= (const unsigned short& data);
		LogDataStore& operator= (const int& data);
		LogDataStore& operator= (const unsigned int& data);
		LogDataStore& operator= (const long& data);
		LogDataStore& operator= (const unsigned long& data);
		LogDataStore& operator= (const long long& data);
		LogDataStore& operator= (const unsigned long long& data);
		LogDataStore& operator= (const float& data);
		LogDataStore& operator= (const double& data);
		LogDataStore& operator= (const std::string& data);
		LogDataStore& operator= (const std::wstring& data);
		LogDataStore& operator= (const LoggerLocalDateTime& data);

		// LogDataStore equality operator:

		bool operator== (const LogDataStore& other) const;
		bool operator!= (const LogDataStore& other) const;
		
		// Test flag operator:

		bool operator== (const LogDataType type);
		bool operator!= (const LogDataType type);
		explicit operator bool() const;

		// Equality operators:

		bool operator== (const bool& data);
		bool operator== (const short& data);
		bool operator== (const unsigned short& data);
		bool operator== (const int& data);
		bool operator== (const unsigned int& data);
		bool operator== (const long& data);
		bool operator== (const unsigned long& data);
		bool operator== (const long long& data);
		bool operator== (const unsigned long long& data);
		bool operator== (const float& data);
		bool operator== (const double& data);
		bool operator== (const std::string& data);
		bool operator== (const std::wstring& data);
		bool operator== (const LoggerLocalDateTime& data);

		//
		// Getters:
		//

		/**
		 * @brief Get the type of data is available in data store
		 * @return Return a LogDataType value that can be used inside the LogEntry and Logger manager
		 */
		LogDataType getType();

		/**
		 * @brief Get the string stored. If no string is available, it will return an empty string.
		 */
		std::string getStr();

		/**
		 * @brief Get the string wide stored. If no wide string is available, it will return an empty string.
		 */
		std::wstring getWstr();

		/**
		 * @brief Get the union LogEntryData that can hold bool, long long, unsigned long long and double values. Use the getType method to get type of data is correctly stored.
		 * @return Return the union variable is available. If not, the union will be a LOG_ENTRY_INT equal to zero.
		 */
		LogEntryData getUnionData();

		/**
		 * @brief Get the local date and time information available in data store. If no data is available, it will return an empty local date and time struct, created with standard empty constructors of std::chrono.
		 */
		LoggerLocalDateTime getLocalDt();

		//
		// Setters:
		//

		/**
		 * @brief Set a new data into data store. If the datatype differs from the new one, the LogDataStore will update all internal flags and data inside.
		 * @param data New data to store
		 */
		void setData (bool data);

		/**
		 * @brief Set a new data into data store. If the datatype differs from the new one, the LogDataStore will update all internal flags and data inside.
		 * @param data New data to store
		 */
		void setData (char data);

		/**
		 * @brief Set a new data into data store. If the datatype differs from the new one, the LogDataStore will update all internal flags and data inside.
		 * @param data New data to store
		 */
		void setData (wchar_t data);

		/**
		 * @brief Set a new data into data store. If the datatype differs from the new one, the LogDataStore will update all internal flags and data inside.
		 * @param data New data to store
		 */
		void setData (short data);

		/**
		 * @brief Set a new data into data store. If the datatype differs from the new one, the LogDataStore will update all internal flags and data inside.
		 * @param data New data to store
		 */
		void setData (unsigned short data);

		/**
		 * @brief Set a new data into data store. If the datatype differs from the new one, the LogDataStore will update all internal flags and data inside.
		 * @param data New data to store
		 */
		void setData (int data);

		/**
		 * @brief Set a new data into data store. If the datatype differs from the new one, the LogDataStore will update all internal flags and data inside.
		 * @param data New data to store
		 */
		void setData (unsigned int data);

		/**
		 * @brief Set a new data into data store. If the datatype differs from the new one, the LogDataStore will update all internal flags and data inside.
		 * @param data New data to store
		 */
		void setData (long data);

		/**
		 * @brief Set a new data into data store. If the datatype differs from the new one, the LogDataStore will update all internal flags and data inside.
		 * @param data New data to store
		 */
		void setData (unsigned long data);

		/**
		 * @brief Set a new data into data store. If the datatype differs from the new one, the LogDataStore will update all internal flags and data inside.
		 * @param data New data to store
		 */
		void setData (long long data);

		/**
		 * @brief Set a new data into data store. If the datatype differs from the new one, the LogDataStore will update all internal flags and data inside.
		 * @param data New data to store
		 */
		void setData (unsigned long long data);

		/**
		 * @brief Set a new data into data store. If the datatype differs from the new one, the LogDataStore will update all internal flags and data inside.
		 * @param data New data to store
		 */
		void setData (float data);

		/**
		 * @brief Set a new data into data store. If the datatype differs from the new one, the LogDataStore will update all internal flags and data inside.
		 * @param data New data to store
		 */
		void setData (double data);

		/**
		 * @brief Set a new data into data store. If the datatype differs from the new one, the LogDataStore will update all internal flags and data inside.
		 * @param data New data to store
		 */
		void setData (char* data);

		/**
		 * @brief Set a new data into data store. If the datatype differs from the new one, the LogDataStore will update all internal flags and data inside.
		 * @param data New data to store
		 */
		void setData (const char* data);

		/**
		 * @brief Set a new data into data store. If the datatype differs from the new one, the LogDataStore will update all internal flags and data inside.
		 * @param data New data to store
		 */
		void setData (wchar_t* data);

		/**
		 * @brief Set a new data into data store. If the datatype differs from the new one, the LogDataStore will update all internal flags and data inside.
		 * @param data New data to store
		 */
		void setData (const wchar_t* data);

		/**
		 * @brief Set a new data into data store. If the datatype differs from the new one, the LogDataStore will update all internal flags and data inside.
		 * @param data New data to store
		 */
		void setData (std::string data);

		/**
		 * @brief Set a new data into data store. If the datatype differs from the new one, the LogDataStore will update all internal flags and data inside.
		 * @param data New data to store
		 */
		void setData (std::wstring data);

		/**
		 * @brief Set a new data into data store. If the datatype differs from the new one, the LogDataStore will update all internal flags and data inside.
		 * @param data New data to store
		 * @param highPrecisionTime Define if the date and time holds a high precision time information.
		 */
		void setData (LoggerLocalDateTime data, bool highPrecisionTime = true);

		//
		// Modifiers and Verifiers:
		//

		/// @brief Clean the data store
		void clean();

		/// @brief Check if the data store holds a data
		bool hasData();
};
	
#endif // !LOGGER_DATA_STORE_HPP