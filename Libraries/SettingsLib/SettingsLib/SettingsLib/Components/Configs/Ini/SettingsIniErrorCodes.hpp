#pragma once 

#ifndef SETTINGS_LIB_INI_ERROR_CODES_HPP
#define SETTINGS_LIB_INI_ERROR_CODES_HPP

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

namespace SettingsLib
{
	namespace ErrorCodes
	{
		/// @brief Line check status report for INI files
		enum IniLineCheckStatus : int
		{
			SETTINGS_INI_LINE_CHECK_UNKNOWN_ERROR = -6,
			SETTINGS_INI_LINE_CHECK_NULLPTR_ERROR = -5,
			SETTINGS_INI_LINE_CHECK_KEY_SYNTAX_ERROR = -4,
			SETTINGS_INI_LINE_CHECK_SECTION_SYNTAX_ERROR = -3,
			SETTIGNS_INI_LINE_CHECK_GENERAL_SYNTAX_ERROR = -2,
			SETTINGS_INI_LINE_CHECK_FAIL_TO_DETERMINATE = -1,
			SETTINGS_INI_LINE_CHECK_EMPTY_LINE,
			SETTINGS_INI_LINE_CHECK_COMMENTED_LINE,
			SETTINGS_INI_LINE_CHECK_SECTION,
			SETTINGS_INI_LINE_CHECK_SECTION_WITH_COMMENTS,
			SETTINGS_INI_LINE_CHECK_KEY_ONLY,
			SETTINGS_INI_LINE_CHECK_KEY_WITH_VALUE,
			SETTINGS_INI_LINE_CHECK_KEY_ONLY_WITH_COMMENTS,
			SETTINGS_INI_LINE_CHECK_KEY_WITH_VALUE_AND_COMMENTS,
			SETTINGS_INI_LINE_CHECK_KEY_WITH_CONTAINER_VALUE,
			SETTINGS_INI_LINE_CHECK_KEY_WITH_CONTAINER_VALUE_AND_COMMENTS
		};

		/// @brief Raw value status conversion codes for INI files
		enum IniRawValueConversionStatus : int
		{
			SETTINGS_INI_CONVERT_VALUE_INIT_DATA_ERROR = -5,
			SETTINGS_INI_CONVERT_VALUE_NULLPTR_ERROR = -4,
			SETTINGS_INI_CONVERT_VALUE_UNKNOWN_ERROR = -3,
			SETTINGS_INI_CONVERT_VALUE_FAIL = -2,
			SETTINGS_INI_CONVERT_VALUE_CONTAINER_TYPE = -1,
			SETTINGS_INI_CONVERT_VALUE_EMPTY,
			SETTINGS_INI_CONVERT_VALUE_UNSIGNED_INTEGER,
			SETTINGS_INI_CONVERT_VALUE_INTEGER,
			SETTINGS_INI_CONVERT_VALUE_FLOAT,
			SETTINGS_INI_CONVERT_VALUE_BOOLEAN,
			SETTINGS_INI_CONVERT_VALUE_STRING,
			SETTINGS_INI_CONVERT_VALUE_WSTRING
		};

		enum ConfigIniStatus : int
		{
			CONFIG_INI_STATUS_SUCCESSFUL_OPERATION,							// Successful operation.
			CONFIG_INI_STATUS_ERROR_SET_WIDE_STRING_DATA,					// Error when apply a wide string in a ConfigIni class that is configured to string.
			CONFIG_INI_STATUS_ERROR_SET_STRING_DATA,						// Error when apply a string in a ConfigIni class that is configured to wstring.
			CONFIG_INI_STATUS_ERROR_GET_WIDE_STRING_DATA,					// Error when try to get a wide string in a ConfigIni class that is configured to string.
			CONFIG_INI_STATUS_ERROR_GET_STRING_DATA,						// Error when try to get a string in a ConfigIni class that is configured wstring.
			CONFIG_INI_STATUS_ERROR_SET_DATA_NULLPTR,						// Error when a nullptr is send to set a new data.
			CONFIG_INI_STATUS_ERROR_GET_DATA_NULLPTR,						// Error when a nullptr is send to get a data.
			CONFIG_INI_STATUS_ERROR_GET_EMPTY_DATA,							// The data inside the class is empty or a nullptr.
			CONFIG_INI_STATUS_ERROR_SET_DATA_MISSING_CONTAINER_INFO,		// This error occur when a ConfigIniData holds a vector data and a method for singulary data was called.
			CONFIG_INI_STATUS_ERROR_GET_DATA_MISSING_CONTAINER_INFO,		// This error occur when a ConfigIniData holds a vector data and a method for singulary data was called.
			CONFIG_INI_STATUS_CLEAN_DATA_FAIL_UNKNOWN_ERROR,				// Unknown error from cleaning the data, section or comment
			CONFIG_INI_STATUS_CLEAN_DATA_VECTOR_FAIL_UNKNOWN_ERROR,			// Unknown error from cleaning the data vector
			CONFIG_INI_STATUS_CLEAN_DATA_ALREADY_EMPTY,						// Message when a ConfigIni object is not holding a data/vdata
			CONFIG_INI_STATUS_SET_DATA_FAIL,								// Fail in set the data
			CONFIG_INI_STATUS_GET_DATA_FAIL,								// Fail in get the data
			CONFIG_INI_STATUS_NO_DATA_AVAILABLE,							// The object doesn't contain a data/vdata/section/comment
			CONFIG_INI_STATUS_CONTAINER_OUT_OF_RANGE,						// The position for the container is out of range
			CONFIG_INI_STATUS_NO_CONTAINER_AVAILABLE,						// When a method for a container is called, but no container is available.
			CONFIG_INI_STATUS_RESET_OBJECT_FAIL,							// Fail in reset the object data.
			CONFIG_INI_STATUS_NO_DATA_TO_SET,								// No data is available to set or an empty data was send.
			CONFIG_INI_STATUS_OBJECT_DATA_NOT_CONFIGURED,					// The object data is not marked as configured and ready to be used.
			CONFIG_INI_STATUS_CREATE_INTERNAL_DATA_EXCEPTION				// An exception occured when a data was allocated.
		};
	}
}

#endif //! SETTINGS_LIB_INI_ERROR_CODES_HPP