#pragma once

#ifndef VERSION_COMMON_TOOLS_HPP
#define VERSION_COMMON_TOOLS_HPP

#ifdef WIN32
	#ifdef VERSION_LIB_EXPORTS
		#define VERSION_LIB_API __declspec(dllexport)
	#else
		#define VERSION_LIB_API __declspec(dllimport)
	#endif //!VERSION_LIB_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#else
	#if __GNUC__ >= 4
		#ifdef VERSION_LIB_EXPORTS
			#define VERSION_LIB_API __attribute__((visibility("default")))
		#else
			#define VERSION_LIB_API __attribute__((visibility("default")))
		#endif //!VERSION_LIB_EXPORTS
	#else
		#ifdef VERSION_LIB_EXPORTS
			#define VERSION_LIB_API
		#else
			#define VERSION_LIB_API
		#endif //!VERSION_LIB_EXPORTS
	#endif
#endif // !WIN32

#include "ExperimentalFeatures.hpp"

#include <algorithm>
#include <cctype>
#include <string>
#include <cstring>
#include <vector>
#include <regex>
#include <array>

#include <iostream>

#include "BuildTypes.hpp"
#include "VersionStruct.hpp"

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM
	#include "VersionToken.hpp"
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM

namespace VersionLib
{
	/**
	 * @brief Transform the string to lowercase
	 * @param value String value to be transformed into lowercase
	 * @return Return a string in lowercase
	 * @bug This method is missing the characters that already are in lowercase.
	 */
	VERSION_LIB_API std::string tolower_str (const std::string& value);
	
	/**
	 * @brief Extract the build revision (alpha.2 or rc.3).
	 * @param buildType Build type string
	 */
	VERSION_LIB_API unsigned int extractBuildTypeNumber (std::string buildType);
	
	/**
	 * @brief Convert the build type into a string with option to use short string version (rc, a).
	 * @param type Build type enumerator
	 * @param useShortStr Determinate if the string will be used in short case
	 * @param showReleaseType Show the 'release' type or 'r' if short string type is defined
	 * @return Return the build type (alpha, rc) string type. No build revision is available here.
	 */
	VERSION_LIB_API std::string buildType2Str (BuildType type, bool useShortStr, bool showReleaseType);

	/**
	 * @brief Convert the string with a build type data into a BuildType enumerator
	 * @param value String with build type information
	 * @return Return a enumeration of BuildType
	 */
	VERSION_LIB_API BuildType str2BuildType (std::string value);
}

#endif // !VERSION_COMMON_TOOLS_HPP