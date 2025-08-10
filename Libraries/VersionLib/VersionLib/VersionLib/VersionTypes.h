#pragma once

#ifndef VERSION_TYPES_H
#define VERSION_TYPES_H

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

/**
 * @brief Versioning Type, used to mark and ordering internal version components
 */
enum VersionLib_VersionType : unsigned char
{
	UNKNOWN_VERSION_TYPE,				// Unidentified versioning type
	SEMANTIC_VERSION_TYPE,				// Semantic Versioning type
	CALENDAR_VERSION_TYPE,				// Calendar versioning type, using ISO 8601
	HYBRID_SEMVER_CALVER_VERSION_TYPE,	// Hybrid Semantic Versioning and Calendar versioning types (Example: YY.MM)
	GENERIC_VERSION_TYPE,				// Generic versioning type
	CUSTOM_VERSION_TYPE,				// Using custom versioning type
};

#endif // !VERSION_TYPES_H