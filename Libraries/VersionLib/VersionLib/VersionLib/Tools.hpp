#pragma once

#ifndef VERSION_TOOLS_HPP
#define VERSION_TOOLS_HPP

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

#include <algorithm>
#include <cctype>
#include <string>
#include <cstring>
#include <vector>

#include "BuildTypes.hpp"
#include "VersionStruct.hpp"

namespace VersionLib
{
	/**
	 * @brief Transform the string to lowercase
	 * @param value String value to be transformed into lowercase
	 * @return Return a C-Style string in lowercase
	 * @bug This method is missing the characters that already are in lowercase.
	 */
	VERSION_LIB_API const char* tolower_Cstr (const std::string& value);

	/**
	 * @brief Transform the string to lowercase
	 * @param value String value to be transformed into lowercase
	 * @return Return a string in lowercase
	 * @bug This method is missing the characters that already are in lowercase.
	 */
	VERSION_LIB_API std::string tolower_str (const std::string& value);

	/**
	 * @brief Extract the build type number (alpha.2 or rc.3).
	 * @param buildType Build type string
	 */
	VERSION_LIB_API unsigned int extractBuildTypeNumber (const char* buildType);
	
	/**
	 * @brief Extract the build type number (alpha.2 or rc.3).
	 * @param buildType Build type string
	 */
	VERSION_LIB_API unsigned int extractBuildTypeNumber (std::string buildType);
	
	/**
	 * @brief Convert the build type into a string with option to use short string version (rc, a).
	 * @param type Build type enumerator
	 * @param useShortStr Determinate if the string will be used in short case
	 * @return Return the build type (alpha, rc) string type. No build type number is available here.
	 */
	VERSION_LIB_API std::string buildType2Str (BuildType type, bool useShortStr);

	/**
	 * @brief Convert the string with a build type data into a BuildType enumerator
	 * @param value String with build type information
	 * @return Return a enumeration of BuildType
	 */
	VERSION_LIB_API BuildType str2BuildType (std::string value);

	/**
	 * @brief Convert a string using Semantic Versioning
	 * @param version String with version information
	 * @return Return a VersionStruct with version data
	 * @warning THIS FUNCTION IS NOT RELIABLE FOR NON SEMANTIC VERSIONING CONVERSION
	 * @deprecated This function is not recommended to use. Use toVersionStrut2, that allow to use a better semantic versioning conversion
	 */
	VERSION_LIB_API VersionStruct toVersionStruct (std::string version);

	/**
	 * @brief Convert a string using Semantic Versioning
	 * @param version String with version information
	 * @return Return a VersionStruct with version data
	 * @warning This function is compatible with Semantic Versioning, but is also permissive to other values conversions. Check the Conversion Notes.
	 * @note Conversion Notes: The conversion formats accept by this method are (x: Major, y: Minor, z: Patch, t: Build Type, n: Build Type Number, "build": Word used to determinate the build field. b: Build number.): Semantic Versioning format: x.y.z, x.y.z-t, x.y.z-t.n, x.y-t, x.y-t.n. Other formats: x.y-t build b, x.y-t b, x.y-t.n build b, x.y.z-t.n build b, x.y.z-t.n b
	 */
	VERSION_LIB_API VersionStruct toVersionStruct2 (std::string version);
}

#endif // !VERSION_TOOLS_HPP