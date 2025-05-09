#pragma once

#ifndef VERSION_HPP
#define VERSION_HPP

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

#ifdef ENABLE_VERSION_LIBRARY_EXPERIMENTAL_FEATURES
#include "ExperimentalFeatures.hpp"
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
	#include "ExceptionComponents.hpp"
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
	
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	#include "BuildTypesExt.hpp"
	#include "BuildReleaseId.hpp"
	#include "ReleaseTools.hpp"
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT

	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_METADATA_CLASS
	#include "BuildMetadata.hpp"
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_METADATA_CLASS

	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SEMVER_CLASS
	#include "SemVerClass.hpp"
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SEMVER_CLASS
#endif // !ENABLE_VERSION_LIBRARY_EXPERIMENTAL_FEATURES

#include "BuildTypes.hpp"
#include "Tools.hpp"
#include "VersionClass.hpp"
#include "VersionStruct.hpp"
#include "VersionLibVersionInfo.hpp"

namespace VersionLib
{
	/**
	 * @brief Generate an VersionData object representing the Version Library version information object
	 */
	inline VersionLib::VersionData internalVersionData()
	{
		VersionLib::BuildType type = VersionLib::str2BuildType(VERSION_LIB_VERSION_INFO_BUILD_TYPE);

		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_GENERIC_VERSION_DATA
		#else
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_GENERIC_VERSION_DATA
		VersionLib::VersionData version(
											VERSION_LIB_VERSION_INFO_MAJOR_VERSION,
											VERSION_LIB_VERSION_INFO_MINOR_VERSION,
											VERSION_LIB_VERSION_INFO_PATCH_VERSION,
											type,
											VERSION_LIB_VERSION_INFO_BUILD_TYPE_NUMBER,
											VERSION_LIB_VERSION_INFO_BUILD_NUMBER
										);
		return version;
	}

	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SEMVER_CLASS
	/**
	 * @brief Generate an SemVer object representing the Version Library version information object
	 */
	inline VersionLib::SemVer internalSemVer()
	{
		VersionLib::BuildType type = VersionLib::str2BuildType(VERSION_LIB_VERSION_INFO_BUILD_TYPE);

		VersionLib::SemVer version(
											VERSION_LIB_VERSION_INFO_MAJOR_VERSION,
											VERSION_LIB_VERSION_INFO_MINOR_VERSION,
											VERSION_LIB_VERSION_INFO_PATCH_VERSION,
											type,
											VERSION_LIB_VERSION_INFO_BUILD_TYPE_NUMBER,
											VERSION_LIB_VERSION_INFO_BUILD_NUMBER
										);
		return version;
	};
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SEMVER_CLASS
}

#endif // !VERSION_HPP