#pragma once

#ifndef VERSION_LIBRARY_EXPERIMENTAL_FEATURES_CONTROL_HPP
#define VERSION_LIBRARY_EXPERIMENTAL_FEATURES_CONTROL_HPP

#include "VersionLibVersionInfo.hpp"

#ifdef VERSION_LIB_USE_VERSION_TYPE_CONTROL

//
// Alpha Features:
//

#if VERSION_LIB_BUILD_TYPE == 1
	// Enable experimental comparison operator for VersionData class
	#define VERSION_LIB_COMPARISON_OPERATORS_V2

	// Enable experimental build number comparison in VersionData class comparison operators
	#define VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_COMPARISON

	// Enable experimental VersionData class constructors
	#define VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_CONSTRUCTORS

	// Enable VersionLib Exceptions report class
	#define VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS

	// Enable experimental VersionData comparison operators with VersionStruct data
	#define VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_OPERATOR_STRUCT_COMPARISON

	// Enable experimental fix to toVersionStruct2 function
	#define VERSION_LIB_ENABLE_EXPERIMENTAL_FIX_VERSIONSTR_2_VERSIONSTRUCT

	// Enable experimental optimized memory layout
	//#define VERSION_LIB_ENABLE_EXPERIMENTAL_MEM_LAYOUT

	// Enable experimental build type class instead of enumerator values
	#define VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT

	// Enable experimental combined build type information
	//#define VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE

	// Enable experimental build metadata on version string
	//#define VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_STR_BUILD_METADATA
#endif // !VERSION_LIB_BUILD_TYPE is Alpha

//
// Beta Features:
//

#if VERSION_LIB_BUILD_TYPE == 2
	// Enable experimental comparison operator for VersionData class
	#define VERSION_LIB_COMPARISON_OPERATORS_V2

	// Enable experimental build number comparison in VersionData class comparison operators
	#define VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_COMPARISON

	// Enable experimental VersionData class constructors
	#define VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_CONSTRUCTORS

	// Enable VersionLib Exceptions report class
	#define VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS

	// Enable experimental VersionData comparison operators with VersionStruct data
	#define VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_OPERATOR_STRUCT_COMPARISON

	// Enable experimental fix to toVersionStruct2 function
	#define VERSION_LIB_ENABLE_EXPERIMENTAL_FIX_VERSIONSTR_2_VERSIONSTRUCT

	// Enable experimental optimized memory layout
	//#define VERSION_LIB_ENABLE_EXPERIMENTAL_MEM_LAYOUT

	// Enable experimental build type class instead of enumerator values
	//#define VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT

	// Enable experimental combined build type information
	//#define VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE

	// Enable experimental build metadata on version string
	//#define VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_STR_BUILD_METADATA
#endif // !VERSION_LIB_BUILD_TYPE is Beta

//
// Release Candidate Features:
//

#if VERSION_LIB_BUILD_TYPE == 3
	// Enable experimental comparison operator for VersionData class
	#define VERSION_LIB_COMPARISON_OPERATORS_V2

	// Enable experimental build number comparison in VersionData class comparison operators
	//#define VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_COMPARISON

	// Enable experimental VersionData class constructors
	#define VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_CONSTRUCTORS

	// Enable VersionLib Exceptions report class
	//#define VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS

	// Enable experimental VersionData comparison operators with VersionStruct data
	//#define VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_OPERATOR_STRUCT_COMPARISON

	// Enable experimental fix to toVersionStruct2 function
	#define VERSION_LIB_ENABLE_EXPERIMENTAL_FIX_VERSIONSTR_2_VERSIONSTRUCT

	// Enable experimental optimized memory layout
	//#define VERSION_LIB_ENABLE_EXPERIMENTAL_MEM_LAYOUT

	// Enable experimental build type class instead of enumerator values
	//#define VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT

	// Enable experimental combined build type information
	//#define VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE

	// Enable experimental build metadata on version string
	//#define VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_STR_BUILD_METADATA
#endif // !VERSION_LIB_BUILD_TYPE is Release Candidate

//
// Experimental Features for Release version:
//

#if VERSION_LIB_BUILD_TYPE == 4

#endif // !VERSION_LIB_BUILD_TYPE is Release

#else

// Enable experimental comparison operator for VersionData class
//#define VERSION_LIB_COMPARISON_OPERATORS_V1

// Enable experimental comparison operator for VersionData class
#define VERSION_LIB_COMPARISON_OPERATORS_V2

// Enable experimental build number comparison in VersionData class comparison operators
#define VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_COMPARISON

// Enable experimental VersionData class constructors
#define VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_CONSTRUCTORS

// Enable VersionLib Exceptions report class
#define VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS

// Enable experimental VersionData comparison operators with VersionStruct data
#define VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_OPERATOR_STRUCT_COMPARISON

// Enable experimental fix to toVersionStruct2 function
#define VERSION_LIB_ENABLE_EXPERIMENTAL_FIX_VERSIONSTR_2_VERSIONSTRUCT

// Enable experimental optimized memory layout
//#define VERSION_LIB_ENABLE_EXPERIMENTAL_MEM_LAYOUT

// Enable experimental build type class instead of enumerator values
//#define VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT

// Enable experimental combined build type information
//#define VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE

// Enable experimental build metadata on version string
//#define VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_STR_BUILD_METADATA

#endif // !VERSION_LIB_USE_VERSION_TYPE_CONTROL

#endif // !VERSION_LIBRARY_EXPERIMENTAL_FEATURES_CONTROL_HPP