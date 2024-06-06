#pragma once 

#ifndef SETTINGS_LIB_DEFINITIONS_HPP
#define SETTINGS_LIB_DEFINITIONS_HPP

#ifdef WIN32
	#ifdef SETTINGS_LIB_EXPORTS
		#define SETTINGS_LIB_API __declspec(dllexport)
	#else
		#define SETTINGS_LIB_API __declspec(dllimport)
	#endif //!SETTINGS_LIB_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#endif // !WIN32

// Settings marks:

#define SETTINGS_OPEN_FIELD						'['
#define SETTINGS_CLOSE_FIELD					']'
#define SETTINGS_COMMENT_MARK					';'
#define SETTINGS_COMMENT_MARK2					'#'
#define SETTINGS_DATA_MARK						'='
#define SETTINGS_SPACE_CHAR						' '
#define SETTINGS_NEW_LINE						'\n'

// Settings container marks:

#define SETTINGS_CONTAINER_OPEN_MARK			'{'
#define SETTINGS_CONTAINER_CLOSE_MARK			'}'
#define SETTINGS_CONTAINER_VALUE_SEPARATOR		','

// Settings data types:

#define SETTINGS_DATA_TYPE_STRING				'"'
#define SETTINGS_DATA_TYPE_BOOL_FALSE			"false"
#define SETTINGS_DATA_TYPE_BOOL_TRUE			"true"
#define SETTINGS_DATA_TYPE_DECIMAL				'.'
#define SETTINGS_DATA_TYPE_NEGATIVE_SIGNAL		'-'
#define SETTINGS_DATA_TYPE_EXPONENT_LOWER		'e'
#define SETTINGS_DATA_TYPE_EXPONENT_UPPER		'E'

// Settings error messages:

#define SETTINGS_CONFIG_DATA_ID_FAIL			"ID_NOT_RECOGNIZED"
#define SETTINGS_CONFIG_DATA_STR_DATA_FAIL		"FAIL_TO_RECOVER_CONFIGURATION_DATA"

/// ------------------------ Wide String Marks ------------------------- ///

// Settings marks:

#define SETTINGS_OPEN_FIELD_W					L'['
#define SETTINGS_CLOSE_FIELD_W					L']'
#define SETTINGS_COMMENT_MARK_W					L';'
#define SETTINGS_COMMENT_MARK2_W				L'#'
#define SETTINGS_DATA_MARK_W					L'='
#define SETTINGS_SPACE_CHAR_W					L' '
#define SETTINGS_NEW_LINE_W						L'\n'

// Settings container marks:

#define SETTINGS_CONTAINER_OPEN_MARK_W			L'{'
#define SETTINGS_CONTAINER_CLOSE_MARK_W			L'}'
#define SETTINGS_CONTAINER_VALUE_SEPARATOR_W	L','

// Settings data types:

#define SETTINGS_DATA_TYPE_STRING_W				L'"'
#define SETTINGS_DATA_TYPE_BOOL_FALSE_W			L"false"
#define SETTINGS_DATA_TYPE_BOOL_TRUE_W			L"true"
#define SETTINGS_DATA_TYPE_DECIMAL_W			L'.'
#define SETTINGS_DATA_TYPE_NEGATIVE_SIGNAL_W	L'-'
#define SETTINGS_DATA_TYPE_EXPONENT_LOWER_W		L'e'
#define SETTINGS_DATA_TYPE_EXPONENT_UPPER_W		L'E'

// Settings error messages:

#define SETTINGS_CONFIG_DATA_ID_FAIL_W			L"ID_NOT_RECOGNIZED"
#define SETTINGS_CONFIG_DATA_STR_DATA_FAIL_W	L"FAIL_TO_RECOVER_CONFIGURATION_DATA"

#endif //! SETTINGS_LIB_DEFINITIONS_HPP