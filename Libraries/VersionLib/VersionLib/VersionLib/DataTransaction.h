#pragma once

#ifndef DATA_TRANSACTION_H
#define DATA_TRANSACTION_H

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

#ifndef __cplusplus
#include <stdbool.h>
#endif

#include "BuildTypes.h"
#include "VersionTypes.h"

#if defined(__cplusplus)
extern "C"
{
#endif

	/**
	 * @brief Version Release Data struct for data transaction with C Programs
	 */
	struct VersionLib_VersionReleaseData
	{
		VersionLib_BuildType release;		// Build release type
		unsigned short revision;			// Build release revision
		bool releaseIdentified;				// Identification status flag
	};

	/**
	 * @brief Version Release struct for data transaction for C Programs
	 */
	struct VersionLib_Release
	{
		VersionLib_VersionReleaseData* releases;	// Release data struct array
		unsigned short size;						// Size of releases array
	};

	/**
	 * @brief Version Data struct for data transaction for C Programs
	 */
	struct VersionLib_VersionData
	{
		unsigned int flags;							// VersionData Flag Controls

		unsigned int major;							// Major version number
		unsigned int minor;							// Minor version number
		unsigned int patch;							// Patch version number
		unsigned long long build;					// Build number

		VersionLib_Release release;					// Release version data
		VersionLib_VersionType versionType;			// Versioning Type Id

		char* metadata;								// Metadata string (If nullptr, means no metadata is available)
	};

#if defined(__cplusplus)
}
#endif

#endif // !DATA_TRANSACTION_H