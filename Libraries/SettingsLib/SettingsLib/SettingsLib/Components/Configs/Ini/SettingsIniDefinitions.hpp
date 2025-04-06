#pragma once 

#ifndef SETTINGS_LIB_INI_DEFINITIONS_HPP
#define SETTINGS_LIB_INI_DEFINITIONS_HPP

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

#include "SettingsLibExperimentalFeatures.hpp"

// Settings Definitions for INI configuration files:

// Settings marks:

#define SETTINGS_INI_OPEN_SECTION					'['
#define SETTINGS_INI_CLOSE_SECTION					']'
#define SETTINGS_INI_COMMENT_MARK					';'
#define SETTINGS_INI_COMMENT_MARK2					'#'
#define SETTINGS_INI_DATA_MARK						'='
#define SETTINGS_INI_SPACE_CHAR						' '
#define SETTINGS_INI_NEW_LINE						'\n'

// Settings container marks:

#define SETTINGS_INI_CONTAINER_OPEN_MARK			'{'
#define SETTINGS_INI_CONTAINER_CLOSE_MARK			'}'
#define SETTINGS_INI_CONTAINER_VALUE_SEPARATOR		','

// Settings data types:

#define SETTINGS_INI_DATA_TYPE_STRING				'"'
#define SETTINGS_INI_DATA_TYPE_BOOL_FALSE			"false"
#define SETTINGS_INI_DATA_TYPE_BOOL_TRUE			"true"
#define SETTINGS_INI_DATA_TYPE_DECIMAL				'.'
#define SETTINGS_INI_DATA_TYPE_NEGATIVE_SIGNAL		'-'
#define SETTINGS_INI_DATA_TYPE_POSITIVE_SIGNAL		'+'
#define SETTINGS_INI_DATA_TYPE_EXPONENT_LOWER		'e'
#define SETTINGS_INI_DATA_TYPE_EXPONENT_UPPER		'E'

// Settings error messages:

#define SETTINGS_INI_CONFIG_DATA_ID_FAIL			"ID_NOT_RECOGNIZED"
#define SETTINGS_INI_CONFIG_DATA_STR_DATA_FAIL		"FAIL_TO_RECOVER_CONFIGURATION_DATA"

/// ------------------------ Wide String Marks ------------------------- ///

// Settings marks:

#define SETTINGS_INI_OPEN_SECTION_W					L'['
#define SETTINGS_INI_CLOSE_SECTION_W				L']'
#define SETTINGS_INI_COMMENT_MARK_W					L';'
#define SETTINGS_INI_COMMENT_MARK2_W				L'#'
#define SETTINGS_INI_DATA_MARK_W					L'='
#define SETTINGS_INI_SPACE_CHAR_W					L' '
#define SETTINGS_INI_NEW_LINE_W						L'\n'

// Settings container marks:

#define SETTINGS_INI_CONTAINER_OPEN_MARK_W			L'{'
#define SETTINGS_INI_CONTAINER_CLOSE_MARK_W			L'}'
#define SETTINGS_INI_CONTAINER_VALUE_SEPARATOR_W	L','

// Settings data types:

#define SETTINGS_INI_DATA_TYPE_STRING_W				L'"'
#define SETTINGS_INI_DATA_TYPE_BOOL_FALSE_W			L"false"
#define SETTINGS_INI_DATA_TYPE_BOOL_TRUE_W			L"true"
#define SETTINGS_INI_DATA_TYPE_DECIMAL_W			L'.'
#define SETTINGS_INI_DATA_TYPE_NEGATIVE_SIGNAL_W	L'-'
#define SETTINGS_INI_DATA_TYPE_POSITIVE_SIGNAL_W	L'+'
#define SETTINGS_INI_DATA_TYPE_EXPONENT_LOWER_W		L'e'
#define SETTINGS_INI_DATA_TYPE_EXPONENT_UPPER_W		L'E'

// Settings error messages:

#define SETTINGS_INI_CONFIG_DATA_ID_FAIL_W			L"ID_NOT_RECOGNIZED"
#define SETTINGS_INI_CONFIG_DATA_STR_DATA_FAIL_W	L"FAIL_TO_RECOVER_CONFIGURATION_DATA"

#endif //! SETTINGS_LIB_INI_DEFINITIONS_HPP