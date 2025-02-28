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
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_MEM_LAYOUT
	/**
	 * @brief Version struct used for C applications
	 * @note In version 0.8.6-beta the build_type_number (or revision) was moved below patch to redesign the memory allocation. See details in VersionLibInfo
	 */
	struct VersionStruct
	{
		unsigned int major;					// Major version number
		unsigned int minor;					// Minor version number
		unsigned int patch;					// Patch version number
		unsigned int build_type_number;		// Build type number (alpha1, rc3)
		unsigned long long build;			// Build number
		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
		VersionLib::VersionBuildTypeC build_type;	// Build type (alpha, a, beta, etc)
		#else
		VersionLib::BuildType build_type;	// Build type (alpha, a, beta, etc)
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
		bool compare_build;					// Build comparison control
	};
	#else
	/**
	 * @brief Version struct used for C applications
	 */
	struct VersionStruct
	{
		unsigned int major;					// Major version number
		unsigned int minor;					// Minor version number
		unsigned int patch;					// Patch version number
		unsigned long long build;			// Build number
		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
		VersionLib::VersionBuildTypeC build_type;	// Build type (alpha, a, beta, etc)
		#else
		VersionLib::BuildType build_type;	// Build type (alpha, a, beta, etc)
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
		unsigned int build_type_number;		// Build type number (alpha1, rc3)
		bool compare_build;					// Build comparison control
	};
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_MEM_LAYOUT

	/**
	 * @brief Initialize the VersionStruct. This function is designed to reduce the possibility of failure of new struct variables.
	 * @return Return a initialized VersionStruct
	 * @note This function resolve the uninitialized compare_build variable in other methods
	 */
	VersionLib::VersionStruct VERSION_LIB_API initVersionStruct();
}

#endif // !VERSION_STRUCT_HPP