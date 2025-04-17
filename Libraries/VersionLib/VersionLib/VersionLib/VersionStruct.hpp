#pragma once

#ifndef VERSION_STRUCT_HPP
#define VERSION_STRUCT_HPP

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

#include "BuildTypes.hpp"

namespace VersionLib
{
	/**
	 * @brief Version struct used for C applications
	 */
	struct VersionStruct
	{
		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_GENERIC_VERSION_DATA
		unsigned int* numeric_components;			// Numeric version components
		unsigned short numCompSize;					// Number of components
		char* compLoc;								// Components Location (Used to Custom formats)
		#else
		unsigned int major;							// Major version number
		unsigned int minor;							// Minor version number
		unsigned int patch;							// Patch version number
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_GENERIC_VERSION_DATA

		unsigned long long build;					// Build number
		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
		VersionLib::VersionBuildTypeC build_type;	// Build type (alpha, a.1, beta, etc)
		#else
		VersionLib::BuildType build_type;	// Build type (alpha, a, beta, etc)
		unsigned int build_revision;		// Build revision (alpha.1, rc.3)
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT

		bool compare_build;							// Build comparison control
		VersionLib::VersionType versionType;		// Versioning Type Id

		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_METADATA_CLASS
		char* metadata;								// Metadata string (If nullptr, means no metadata is available)
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_METADATA_CLASS
	};

	/**
	 * @brief Initialize the VersionStruct. This function is designed to reduce the possibility of failure of new struct variables.
	 * @return Return a initialized VersionStruct
	 * @note This function resolve the uninitialized variables to other methods
	 * @warning It's recommended to use initVersionStruct method to safely destroy the internal data
	 */
	VersionLib::VersionStruct VERSION_LIB_API initVersionStruct();

	/**
	 * @brief Safe version release data information pointer destruction and set as nullptr
	 * @param versionData Version struct data
	 * @return 0: if successfully destroyed and set the pointer as nullptr
	 * @return 1: Fail to destroy the numeric values array
	 * @return 2: Fail to destroy the Component Location string data
	 * @return 4: Fail to destroy the BuildType components
	 * @return 8: Fail to destroy the build metadata string data
	 * @note Other return values are the sum of multiple listed return type errors
	 */
	int VERSION_LIB_API destroyVersionStruct(VersionLib::VersionStruct& versionData);
}

#endif // !VERSION_STRUCT_HPP