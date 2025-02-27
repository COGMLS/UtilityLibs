#pragma once

#ifndef VERSION_LIBRARY_EXPERIMENTAL_FEATURES_CONTROL_HPP
#define VERSION_LIBRARY_EXPERIMENTAL_FEATURES_CONTROL_HPP

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
//#define VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_OPERATOR_STRUCT_COMPARISON

// Enable experimental fix to toVersionStruct2 function
#define VERSION_LIB_ENABLE_EXPERIMENTAL_FIX_VERSIONSTR_2_VERSIONSTRUCT

// Enable experimental optimized memory layout:
//#define VERSION_LIB_ENABLE_EXPERIMENTAL_MEM_LAYOUT

// Enable experimental build type class instead of enumerator values
//#define VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT

#endif // !VERSION_LIBRARY_EXPERIMENTAL_FEATURES_CONTROL_HPP