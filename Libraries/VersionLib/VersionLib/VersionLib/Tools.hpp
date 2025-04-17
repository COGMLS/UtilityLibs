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

#include "ExperimentalFeatures.hpp"

#include <algorithm>
#include <cctype>
#include <string>
#include <cstring>
#include <vector>
#include <regex>
#include <array>

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
	 * @brief Extract the build revision (alpha.2 or rc.3).
	 * @param buildType Build type string
	 */
	VERSION_LIB_API unsigned int extractBuildTypeNumber (const char* buildType);
	
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

	/**
	 * @brief Convert a string using Semantic Versioning
	 * @param version String with version information
	 * @return Return a VersionStruct with version data
	 * @warning This function is compatible with Semantic Versioning, but is also permissive to other values conversions. Check the Conversion Notes.
	 * @note Conversion Notes: The conversion formats accept by this method are (x: Major, y: Minor, z: Patch, t: Build Type, n: Build revision, "build": Word used to determinate the build field. b: Build number.): Semantic Versioning format: x.y.z, x.y.z-t, x.y.z-t.n, x.y-t, x.y-t.n. Other formats: x.y-t build b, x.y-t b, x.y-t.n build b, x.y.z-t.n build b, x.y.z-t.n b
	 */
	VERSION_LIB_API VersionStruct toVersionStruct2 (std::string version);
	
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_TOVERSIONSTRCUT3_METHOD
	/**
	 * @brief Convert a string using Semantic Versioning with support to combined build types and build metadata
	 * @param version String with version information
	 * @return Return a VersionStruct with version data
	 * @warning This function is compatible with Semantic Versioning, but is also permissive to other values conversions. Check the Conversion Notes.
	 * @note Conversion Notes: The conversion formats accept by this method are (x: Major, y: Minor, z: Patch, t: Build Type, n: Build revision, "build": Word used to determinate the build field. b: Build number.): Semantic Versioning format: x.y.z, x.y.z-t, x.y.z-t.n, x.y-t, x.y-t.n. Other formats: x.y-t build b, x.y-t b, x.y-t.n build b, x.y.z-t.n build b, x.y.z-t.n b
	 * @note All metadata information must be defined by the signal '+' before start in string version. If a empty space has in the metadata and the "build" word or a decimal numeric value exists after, will be considered as a build number information.
	 */
	VERSION_LIB_API VersionStruct toVersionStruct3 (std::string version);
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_TOVERSIONSTRCUT3_METHOD

	/**
	 * @brief Method to find and get the build type information, including the combined build types (alpha.beta)
	 * @param version Version string or part that contains the build type(s)
	 * @param start Predefined position to restrict the search
	 * @param end Predefined position to restrict the search
	 * @return Return the build type(s) extracted from version string.
	 * @note If start parameter is defined but not the end, it will use the final version string position and will take no restrict search effect.
	 * @exception This method throw an exception if start position is less than zero
	 * @exception This method throw an exception if end position is bigger than version string
	 */
	VERSION_LIB_API std::vector<VersionLib::VersionReleaseDataC> findAndGetBuildTypes (std::string& version, long long start = -1, long long end = -1);

	/**
	 * @brief Extract the build metadata from string version. This method must be used before any version string algorithm analysis.
	 * @param version Version string data
	 * @return Return the metadata followed by the '+' signal in Semantic Versioning. If no metadata was detect, an empty string will return.
	 */
	VERSION_LIB_API std::string extractBuildMetadata (std::string& version);

	/**
	 * @brief Identify the type of versioning type
	 * @param version Version information. This can be the raw version format or the version formatter string
	 * @param isVerFormatStr Define to detect the versioning format from string formatter
	 * @param regex Regular Expression string to detect custom formats. If leave empty (default value), will assume to try the detection of internal supported versioning formats
	 * @return Return the identified version type
	 */
	VERSION_LIB_API VersionLib::VersionType idVersionType (std::string version, bool isVerFormatStr, std::string regex = "");

	/**
	 * @brief Get the complete the build type data (like alpha.2, beta.3) with C string style
	 * @param version Version Struct data
	 * @param useShortStr Use the short string version
	 * @param showReleaseType Show the "release" or "r" build type
	 * @return Return a constant C string style of the complete build type data
	 * @warning This function is not defined!
	 */
	const char* verStruct2BuildTypeComplete (const VersionLib::VersionStruct& version, bool useShortStr = true, bool showReleaseType = false);

	/**
	 * @brief Get the version data as a string
	 * @param version Version Struct data
	 * @param useShortStr Use the short string version
	 * @param hideBuildWord 
	 * @param showReleaseType Show the "release" or "r" build type
	 * @return Return a constant C string style of the version data in the struct
	 * @warning This function is not defined!
	 */
	const char* verStruct2Str (const VersionLib::VersionStruct& version, bool useShortStr = true, bool hideBuildWord = false, bool showReleaseType = false);

	/**
	 * @brief Check each given Version Struct to determinate which one of them is greater, less or equal
	 * @param ver1 Version Struct data left reference
	 * @param ver2 Version Struct data right reference
	 * @return 
	 * @warning This function is not defined!
	 */
	int chkVerStruct (const VersionLib::VersionStruct& ver1, const VersionLib::VersionStruct& ver2);
}

#endif // !VERSION_TOOLS_HPP