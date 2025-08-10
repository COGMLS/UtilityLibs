#pragma once

#ifndef VERSION_LIBRARY_HPP
#define VERSION_LIBRARY_HPP

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

	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM
	#include "VersionToken.hpp"
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM
#endif // !ENABLE_VERSION_LIBRARY_EXPERIMENTAL_FEATURES

#include "BuildTypes.hpp"
#include "CommonTools.hpp"
#include "ReleaseTools.hpp"
#include "VersionTools.hpp"
#include "VersionData.hpp"
#include "VersionStruct.hpp"
#include "InternalVersion.hpp"

#endif // !VERSION_LIBRARY_HPP