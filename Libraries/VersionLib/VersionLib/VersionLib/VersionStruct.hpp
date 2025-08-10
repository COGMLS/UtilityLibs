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

#include "ExperimentalFeatures.hpp"

#include "BuildTypes.hpp"

#ifdef VERSION_LIB_PURE_CPP_DATA_STRUCT
	#include <bitset>
	#include <cstdint>
	#include <vector>
	#include "BuildReleaseId.hpp"
	#include "BuildTypesExt.hpp"
#endif // !VERSION_LIB_PURE_CPP_DATA_STRUCT

namespace VersionLib
{
	enum VersionStructFlags : uint8_t
	{
		VERSION_STRUCT_READY_FOR_USE 					= 1,
		VERSION_STRUCT_COMPARE_BUILD_COMPILATION 		= 2,
		VERSION_STRUCT_HAS_METADATA 					= 4,
		VERSION_STRUCT_USING_CUSTOM_FORMAT_STRING_REF 	= 8
	};

	/**
	 * @brief Version struct used for C applications
	 */
	struct VersionStruct
	{
		/** Version Struct control flags
		 * ======================================
		 * 
		 * Bit fields:
		 * ------------------
		 * 
		 * 0: Ready for use
		 * 1: Compare build compilation
		 * 2: Use metadata
		 * 3: Use custom format string reference
		*/
		std::bitset<4> flags;

		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_GENERIC_VERSION_DATA
		std::vector<unsigned int> num_components;	// Numeric version components
		char* compLoc;								// Components Location (Used to Custom formats)
		#else
		unsigned int major;							// Major version number
		unsigned int minor;							// Minor version number
		unsigned int patch;							// Patch version number
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_GENERIC_VERSION_DATA

		unsigned long long build;					// Build number
		VersionLib::VersionBuildType build_type;	// Vector to hold multiple build type and revision data

		bool compare_build;							// Build comparison control
		VersionLib::VersionType versionType;		// Versioning Type Id

		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_METADATA_CLASS
		std::string metadata;						// Metadata string (Controlled by VersionStructFlags)
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_METADATA_CLASS
	};

	/**
	 * @brief Initialize the VersionStruct. This function is designed to reduce the possibility of failure of new struct variables.
	 * @return Return a initialized VersionStruct
	 * @note This function resolve the uninitialized variables to other methods
	 * @warning It's recommended to use destroyVersionStruct method to safely delete the internal data
	 */
	VersionLib::VersionStruct VERSION_LIB_API initVersionStruct();

	/**
	 * @brief Safe version release data information pointer destruction and set as nullptr
	 * @param versionData Version struct data
	 * @return 0: if successfully destroyed and set the pointer as nullptr
	 * @return 1: Fail to destroy the numeric values array
	 * @return 2: Fail to destroy the Component Location string data
	 * @return 4: Fail to destroy the BuildType components
	 * @return 8: Fail to destroy the build metadata string data
	 * @note Other return values are the sum of multiple listed return type errors
	 */
	int VERSION_LIB_API destroyVersionStruct (VersionLib::VersionStruct& versionData);

	/**
	 * @brief Check Version Struct data flags
	 * @param versionData Version struct to test
	 * @param flags Flags to test the control components
	 * @return True if all tested flags are enabled
	 */
	bool VERSION_LIB_API chkVersionStructFlg (const VersionLib::VersionStruct& versionData, std::bitset<4> flags);

	/**
	 * @brief Enable VersionStruct flags without modifing previous modifications
	 * @param versionData VersionStruct data
	 * @param flags Flag or flags that will be applied
	 */
	void VERSION_LIB_API enableVersionStructFlg (VersionLib::VersionStruct& versionData, std::bitset<4> flags);

	/**
	 * @brief Disable VersionStruct flags
	 * @param versionData VersionStruct data
	 * @param flags Flag or flags that will be disabled
	 */
	void VERSION_LIB_API disableVersionStructFlg (VersionLib::VersionStruct& versionData, std::bitset<4> flags);

	/**
	 * @brief Set all flags in VersionStruct
	 * @param versionData VersionStruct data
	 * @param flags Flags that will be enabled
	 * @warning It will overwrite previous flag modifications
	 */
	void VERSION_LIB_API applyVersionStructFlg (VersionLib::VersionStruct& versionData, std::bitset<4> flags);
}

#endif // !VERSION_STRUCT_HPP