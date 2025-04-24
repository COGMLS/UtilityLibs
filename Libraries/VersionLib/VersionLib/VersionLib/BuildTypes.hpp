#pragma once

#ifndef VERSION_BUILD_TYPE_HPP
#define VERSION_BUILD_TYPE_HPP

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

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
	#include <exception>
	#include <vector>
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE

// Default build release type initialization
#define VERSION_LIB_DEFAULT_BUILD_RELEASE_TYPE_INIT VersionLib::BuildType::ALPHA

namespace VersionLib
{
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT

	/**
	 * @brief Build type identifier
	 */
	enum BuildType : unsigned short
	{
		NOT_DETECTED,
		PRE_ALPHA,
		ALPHA,
		CANARY,
		PRE_BETA,
		BETA,
		DEVELOPMENT,
		RELEASE_CANDIDATE,
		PRE_RELEASE,
		RELEASE
	};

	/**
	 * @brief Versioning Type, used to mark and ordering internal version components
	 */
	enum VersionType : unsigned char
	{
		UNKNOWN_VERSION_TYPE,				// Unidentified versioning type
		SEMANTIC_VERSION_TYPE,				// Semantic Versioning type
		CALENDAR_VERSION_TYPE,				// Calendar versioning type, using ISO 8601
		HYBRID_SEMVER_CALVER_VERSION_TYPE,	// Hybrid Semantic Versioning and Calendar versioning types (Example: YY.MM)
		GENERIC_VERSION_TYPE,				// Generic versioning type
		CUSTOM_VERSION_TYPE,				// Using custom versioning type
	};

	/**
	 * @brief Build release data, contains the BuildType information and the build type revision together. This struct include a flag to detect if the data was correctly identified.
	 */
	struct VersionReleaseDataC
	{
		VersionLib::BuildType release;		// Build release type
		unsigned short revision;			// Build release revision
		bool releaseIdentified;				// Identification status flag
	};

	/**
	 * @brief VersionBuildType in C style
	 */
	struct VersionBuildTypeC
	{
		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
		VersionLib::VersionReleaseDataC* releases;	// Build releases
		unsigned short size;						// Size of releases array
		#else
		VersionLib::BuildType type;		// Build release data
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
	};

	/**
	 * @brief Initialize a VersionBuildTypeC struct to work with C style code
	 * @note To set properly the value, use setVersionBuildTypeC method
	 */
	VERSION_LIB_API VersionLib::VersionBuildTypeC initVersionBuildTypeC();

	/**
	 * @brief Destroy correctly the internal data.
	 * @param build_type Reference to build type struct
	 * @note This method do nothing if VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE is disabled on Experimental Features
	 */
	VERSION_LIB_API bool destroyVersionBuildTypeC(VersionLib::VersionBuildTypeC& build_type);

	/**
	 * @brief Set correctly the build type value in the struct.
	 * @param buildTypeStruct Build type struct reference
	 * @param build_type Build type to be set
	 * @note This method applies correctly the changes on struct if VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE is enabled. Otherwise, it will set a new value in a local variable.
	 */
	VERSION_LIB_API bool setVersionBuildTypeC (VersionLib::VersionBuildTypeC& buildTypeStruct, VersionLib::BuildType build_type, unsigned short revision = 0);

	/**
	 * @brief Set correctly the build type value in the struct.
	 * @param buildTypeStruct Build type struct reference
	 * @param build_type Build types to be set
	 * @param size Size of build_type array.
	 * @note This method applies correctly the changes on struct if VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE is enabled.
	 */
	VERSION_LIB_API bool setVersionBuildTypeC (VersionLib::VersionBuildTypeC& buildTypeStruct, VersionLib::VersionReleaseDataC* build_type, unsigned short size);

	/**
	 * @brief Initialize a VersionReleaseDataC struct with default values
	 * @note The struct initialization set the flag 'releaseIdentified' as false
	 */
	VERSION_LIB_API VersionLib::VersionReleaseDataC initVersionReleaseDataC();

	/**
	 * @brief Get the BuildType weight for enumerator values
	 * @param type Build release type value
	 * @return Return the curresponding weight for the actual BuildType
	 */
	VERSION_LIB_API unsigned short getBuildTypeWeight (VersionLib::BuildType type);

	#else
	/**
	 * @brief Build type identifier
	 */
	enum BuildType : unsigned short
	{
		ALPHA,
		BETA,
		RELEASE_CANDIDATE,
		RELEASE
	};
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
}

#endif // !VERSION_BUILD_TYPE_HPP