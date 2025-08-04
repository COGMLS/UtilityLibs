#pragma once

#ifndef INTERNAL_VERSION_LIB_HPP
#define INTERNAL_VERSION_LIB_HPP

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

#include "VersionLibVersionInfo.h"
#include "VersionData.hpp"
#include "SemVerClass.hpp"

namespace VersionLib
{
	/**
	 * @brief Generate an VersionData object representing the Version Library version information object
	 */
	VersionLib::VersionData internalVersionData();

	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SEMVER_CLASS
	/**
	 * @brief Generate an SemVer object representing the Version Library version information object
	 */
	VersionLib::SemVer internalSemVer();
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SEMVER_CLASS
}

#endif // !INTERNAL_VERSION_LIB_HPP