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
		unsigned int major;					// Major version number
		unsigned int minor;					// Minor version number
		unsigned int patch;					// Patch version number
		unsigned long long build;			// Build number
		VersionLib::BuildType build_type;	// Build type (alpha, a, beta, etc)
		unsigned int build_type_number;		// Build type number (alpha1, rc3)
	};

	bool hasBuildTypeNumber (const VersionStruct& version);
	char* verStruct2Str (const VersionStruct& verion);
	int chkVerStruct (const VersionStruct& ver1, const VersionStruct& ver2);
}


#endif // !VERSION_STRUCT_HPP