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
	inline VersionData internalVersionData()
	{
		VersionLib::BuildType type = VersionLib::str2BuildType(VERSION_LIB_VERSION_INFO_BUILD_TYPE);

		VersionLib::VersionData version(
											VERSION_LIB_VERSION_INFO_MAJOR_VERSION,
											VERSION_LIB_VERSION_INFO_MINOR_VERSION,
											VERSION_LIB_VERSION_INFO_PATCH_VERSION,
											VERSION_LIB_VERSION_INFO_BUILD,
											type,
											VERSION_LIB_VERSION_INFO_BUILD_TYPE_NUMBER
										);

		return version;
	}
}

#endif // !VERSION_HPP