#pragma once

#ifndef BUILD_TYPES_H
#define BUILD_TYPES_H

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

// Default build release type initialization
#define VERSION_LIB_DEFAULT_BUILD_RELEASE_TYPE_INIT VersionLib_BuildType::ALPHA

/**
 * @brief Build type identifier
 */
enum VersionLib_BuildType : unsigned short
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

#endif // !BUILD_TYPES_H