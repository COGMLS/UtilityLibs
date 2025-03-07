#pragma once

#ifndef VERSION_BUILD_TYPE_HPP
#define VERSION_BUILD_TYPE_HPP

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

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
	#include <exception>
	#include <vector>
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE

namespace VersionLib
{
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT

	/**
	 * @brief Build type identifier
	 */
	enum BuildType : unsigned short
	{
		PRE_ALPHA,
		ALPHA,
		CANARY,
		BETA,
		DEVELOPMENT,
		RELEASE_CANDIDATE,
		PRE_RELEASE,
		RELEASE
	};

	/**
	 * @brief VersionBuildType in C style
	 */
	struct VersionBuildTypeC
	{
		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
		VersionLib::BuildType* types;
		unsigned short size;
		#else
		VersionLib::BuildType type;
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
	};

	/**
	 * @brief Initialize a VersionBuildTypeC struct to work with C style code
	 * @note To set properly the value, use setVersionBuildTypeC method
	 */
	VersionLib::VersionBuildTypeC VERSION_LIB_API initVersionBuildTypeC();

	/**
	 * @brief Destroy correctly the internal data.
	 * @param build_type Reference to build type struct
	 * @note This method do nothing if VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE is disabled on Experimental Features
	 */
	bool VERSION_LIB_API destroyVersionBuildTypeC(VersionLib::VersionBuildTypeC& build_type);

	/**
	 * @brief Set correctly the build type value in the struct.
	 * @param buildTypeStruct Build type struct reference
	 * @param build_type Build type to be set
	 * @note This method applies correctly the changes on struct if VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE is enabled. Otherwise, it will set a new value in a local variable.
	 */
	bool VERSION_LIB_API setVersionBuildTypeC (VersionLib::VersionBuildTypeC& buildTypeStruct, VersionLib::BuildType build_type);

	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
	/**
	 * @brief Set correctly the build type value in the struct.
	 * @param buildTypeStruct Build type struct reference
	 * @param build_type Build types to be set
	 * @param size Size of build_type array.
	 * @note This method applies correctly the changes on struct if VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE is enabled.
	 */
	bool VERSION_LIB_API setVersionBuildTypeC (VersionLib::VersionBuildTypeC& buildTypeStruct, VersionLib::BuildType build_type[], unsigned short size);
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE

	#else
	/**
	 * @brief Build type identifier
	 */
	enum BuildType : unsigned short
	{
		ALPHA,
		BETA,
		RELEASE_CANDIDATE,
		RELEASE
	};
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
}

#endif // !VERSION_BUILD_TYPE_HPP