#pragma once

#ifndef LOGGER_LIB_VERSION_HPP
#define LOGGER_LIB_VERSION_HPP

//
// Logger Library Build Type
//

// Logger Libray build type:
// 1 - Alpha
// 2 - Beta
// 3 - Release Candidate
// 4 - Release
#define LOGGER_LIB_COMPILE_BUILD_TYPE 3

#if LOGGER_LIB_COMPILE_BUILD_TYPE == 1
	#define LOGGER_LIB_BUILD_TYPE_ALPHA					// Logger Library to compile with alpha features
#elif LOGGER_LIB_COMPILE_BUILD_TYPE == 2
	#define LOGGER_LIB_BUILD_TYPE_BETA					// Logger Library to compile with beta features
#elif LOGGER_LIB_COMPILE_BUILD_TYPE == 3
	#define LOGGER_LIB_BUILD_TYPE_RELEASE_CANDIDATE		// Logger Library to compile with release candidate features
#elif LOGGER_LIB_COMPILE_BUILD_TYPE == 4
	#define LOGGER_LIB_BUILD_TYPE_RELEASE				// Logger Library to compile with release features
#else
	#error "No LoggerLib build type is defined!"
#endif // !LOGGER_LIB_BUILD_TYPE

//
// Logger Library Build:
//

#ifdef LOGGER_LIB_BUILD_TYPE_ALPHA
	#define LOGGER_LIB_MAJOR_VERSION 3
	#define LOGGER_LIB_MINOR_VERSION 5
	#define LOGGER_LIB_PATCH_VERSION 0
	#define LOGGER_LIB_BUILD_NUMBER 93
	#define LOGGER_LIB_BUILD_TYPE "alpha"
	#define LOGGER_LIB_REVISION_NUMBER 0
#endif // !LOGGER_LIB_BUILD_TYPE_ALPHA

#ifdef LOGGER_LIB_BUILD_TYPE_BETA
	#define LOGGER_LIB_MAJOR_VERSION 3
	#define LOGGER_LIB_MINOR_VERSION 4
	#define LOGGER_LIB_PATCH_VERSION 0
	#define LOGGER_LIB_BUILD_NUMBER 93
	#define LOGGER_LIB_BUILD_TYPE "beta"
	#define LOGGER_LIB_REVISION_NUMBER 0
#endif // !LOGGER_LIB_BUILD_TYPE_BETA

#ifdef LOGGER_LIB_BUILD_TYPE_RELEASE_CANDIDATE
	#define LOGGER_LIB_MAJOR_VERSION 3
	#define LOGGER_LIB_MINOR_VERSION 4
	#define LOGGER_LIB_PATCH_VERSION 0
	#define LOGGER_LIB_BUILD_NUMBER 99
	#define LOGGER_LIB_BUILD_TYPE "release candidate"
	#define LOGGER_LIB_REVISION_NUMBER 0
#endif // !LOGGER_LIB_BUILD_TYPE_RELEASE_CANDIDATE

#ifdef LOGGER_LIB_BUILD_TYPE_RELEASE
	#define LOGGER_LIB_MAJOR_VERSION 3
	#define LOGGER_LIB_MINOR_VERSION 3
	#define LOGGER_LIB_PATCH_VERSION 1
	#define LOGGER_LIB_BUILD_NUMBER 95
	#define LOGGER_LIB_BUILD_TYPE "release"
	#define LOGGER_LIB_REVISION_NUMBER 0
#endif // !LOGGER_LIB_BUILD_TYPE_RELEASE

#endif // !LOGGER_LIB_VERSION_HPP