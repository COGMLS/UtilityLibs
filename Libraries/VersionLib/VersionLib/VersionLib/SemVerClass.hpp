#pragma once

#ifndef SEM_VER_CLASS_HPP
#define SEM_VER_CLASS_HPP

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
#include "VersionTools.hpp"

#ifdef ENABLE_VERSION_LIBRARY_EXPERIMENTAL_FEATURES
#include "ExperimentalFeatures.hpp"
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
	#include "ExceptionComponents.hpp"
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS

	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	#include "BuildTypesExt.hpp"
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT

	#ifdef VERSION_LIB_ENABLE_BUILD_RELEASE_CLASS
	#include "BuildReleaseId.hpp"
	#endif // !VERSION_LIB_ENABLE_BUILD_RELEASE_CLASS

	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_METADATA_CLASS
	#include "BuildMetadata.hpp"
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_METADATA_CLASS
#endif // !ENABLE_VERSION_LIBRARY_EXPERIMENTAL_FEATURES

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SEMVER_CLASS
namespace VersionLib
{
	/**
	 * @brief Semantic Versioning class to create objects that verify if the rules to Semantic Versioning are followed. This class offers support to Major, Minor, Patch version numbers and Build and build type support.
	 * @note This is the old VersionData modified to work with specific Semantic Versioning rules
	 */
	class VERSION_LIB_API SemVer
	{
		private:

			unsigned int major;							// Major version number
			unsigned int minor;							// Minor version number
			unsigned int patch;							// Patch version number
			unsigned long long build;					// Build number
			#ifdef VERSION_LIB_ENABLE_BUILD_RELEASE_CLASS
			VersionLib::VersionBuildType build_type;	// Complex Build type data to store the release type and revision, including composed types
			#else
			VersionLib::BuildType build_type;	// Build type (alpha, a, beta, etc)
			unsigned int build_revision;		// Build revision (alpha.1, rc.3)
			#endif // !VERSION_LIB_ENABLE_BUILD_RELEASE_CLASS
			bool compare_build;							// Build comparison control
			#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_METADATA_CLASS
			VersionLib::BuildMetadata metadata;			// Version Metadata
			#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_METADATA_CLASS

		public:

			//
			// Constructors:
			//

			/**
			 * @brief Create an SemVer object that can represent an software version data
			 * @param versionStr String with version information
			 * @param cmpBuild Set to compare the build with other version data. By default the build is not compared.
			 * @note Before use this constructor, check the versions formats accepted by the method toVersionStruct2.
			 */
			SemVer (std::string versionStr, bool cmpBuild = false);

			/**
			 * @brief Convert a VersionStruct to a SemVer object, to represent a software version data
			 * @param version Version struct to be converted
			 */
			SemVer (VersionLib::VersionStruct version);

			/**
			 * @brief Create an SemVer object that can represent an software version data
			 * @param major Major version
			 * @param minor Minor version
			 * @param patch Patch version
			 */
			SemVer (unsigned int major, unsigned int minor, unsigned int patch);

			/**
			 * @brief Create an SemVer object that can represent an software version data
			 * @param major Major version
			 * @param minor Minor version
			 * @param patch Patch version
			 * @param build_type Build type (alpha, beta, rc, release)
			 * @throw If build_type is nullptr, will throw a exception VersionErrorCode_Invalid_Nullptr_Data_Passed
			 */
			SemVer (unsigned int major, unsigned int minor, unsigned int patch, const char* build_type);

			/**
			 * @brief Create an SemVer object that can represent an software version data
			 * @param major Major version
			 * @param minor Minor version
			 * @param patch Patch version
			 * @param build_type Build type (alpha, beta, rc, release)
			 */
			SemVer (unsigned int major, unsigned int minor, unsigned int patch, std::string build_type);

			/**
			 * @brief Create an SemVer object that can represent an software version data
			 * @param major Major version
			 * @param minor Minor version
			 * @param patch Patch version
			 * @param build_type Build type enumerator
			 */
			SemVer (unsigned int major, unsigned int minor, unsigned int patch, VersionLib::BuildType build_type);

			/**
			 * @brief Create an SemVer object that can represent an software version data
			 * @param major Major version
			 * @param minor Minor version
			 * @param patch Patch version
			 * @param build_type Build type (alpha, beta, rc, release)
			 * @param build_revision Determinate if is the first or second or other version of the same build type (like 1.9.2-rc.3). Note: If set as zero, the build_revision will be ignored.
			 * @throw If build_type is nullptr, will throw a exception VersionErrorCode_Invalid_Nullptr_Data_Passed
			 */
			SemVer (unsigned int major, unsigned int minor, unsigned int patch, const char* build_type, unsigned int build_revision);

			/**
			 * @brief Create an SemVer object that can represent an software version data
			 * @param major Major version
			 * @param minor Minor version
			 * @param patch Patch version
			 * @param build_type Build type (alpha, beta, rc, release)
			 * @param build_revision Determinate if is the first or second or other version of the same build type (like 1.9.2-rc.3). Note: If set as zero, the build_revision will be ignored.
			 */
			SemVer (unsigned int major, unsigned int minor, unsigned int patch, std::string build_type, unsigned int build_revision);

			/**
			 * @brief Create an SemVer object that can represent an software version data
			 * @param major Major version
			 * @param minor Minor version
			 * @param patch Patch version
			 * @param build_type Build type enumerator
			 * @param build_revision Determinate if is the first or second or other version of the same build type (like 1.9.2-rc.3). Note: If set as zero, the build_revision will be ignored.
			 */
			SemVer (unsigned int major, unsigned int minor, unsigned int patch, VersionLib::BuildType build_type, unsigned int build_revision);

			/**
			 * @brief Create an SemVer object that can represent an software version data
			 * @param major Major version
			 * @param minor Minor version
			 * @param patch Patch version
			 * @param build_type Build type (alpha, beta, rc, release)
			 * @param build_revision Determinate if is the first or second or other version of the same build type (like 1.9.2-rc.3). Note: If set as zero, the build_revision will be ignored.
			 * @param build Build of the version
			 * @param cmpBuild Set to compare the build with other version data. By default the build is not compared.
			 * @throw If build_type is nullptr, will throw a exception VersionErrorCode_Invalid_Nullptr_Data_Passed
			 */
			SemVer (unsigned int major, unsigned int minor, unsigned int patch, const char* build_type, unsigned int build_revision, unsigned long long build, bool cmpBuild = false);

			/**
			 * @brief Create an SemVer object that can represent an software version data
			 * @param major Major version
			 * @param minor Minor version
			 * @param patch Patch version
			 * @param build_type Build type (alpha, beta, rc, release)
			 * @param build_revision Determinate if is the first or second or other version of the same build type (like 1.9.2-rc.3). Note: If set as zero, the build_revision will be ignored.
			 * @param build Build of the version
			 * @param cmpBuild Set to compare the build with other version data. By default the build is not compared.
			 */
			SemVer (unsigned int major, unsigned int minor, unsigned int patch, std::string build_type, unsigned int build_revision, unsigned long long build, bool cmpBuild = false);

			/**
			 * @brief Create an SemVer object that can represent an software version data
			 * @param major Major version
			 * @param minor Minor version
			 * @param patch Patch version
			 * @param build_type Build type enumerator
			 * @param build_revision Determinate if is the first or second or other version of the same build type (like 1.9.2-rc.3). Note: If set as zero, the build_revision will be ignored.
			 * @param build Build of the version
			 * @param cmpBuild Set to compare the build with other version data. By default the build is not compared.
			 */
			SemVer (unsigned int major, unsigned int minor, unsigned int patch, VersionLib::BuildType build_type, unsigned int build_revision, unsigned long long build, bool cmpBuild = false);

			//
			// Wrapper Constructors:
			//

			/**
			 * @brief Create an SemVer object that can represent an software version data
			 * @param major Major version
			 * @param minor Minor version
			 * @param patch Patch version
			 * @throw Will throw an exception if one or more version data parameters is less than zero
			 * @note This constructor is a wrapper to similar constructor using unsigned int values to version information
			 */
			SemVer (int major, int minor, int patch);

			/**
			 * @brief Create an SemVer object that can represent an software version data
			 * @param major Major version
			 * @param minor Minor version
			 * @param patch Patch version
			 * @param build_type Build type (alpha, beta, rc, release)
			 * @throw Will throw an exception if one or more version data parameters is less than zero
			 * @throw If build_type is nullptr, will throw a exception VersionErrorCode_Invalid_Nullptr_Data_Passed
			 * @note This constructor is a wrapper to similar constructor using unsigned int values to version information
			 */
			SemVer (int major, int minor, int patch, const char* build_type);

			/**
			 * @brief Create an SemVer object that can represent an software version data
			 * @param major Major version
			 * @param minor Minor version
			 * @param patch Patch version
			 * @param build_type Build type (alpha, beta, rc, release)
			 * @throw Will throw an exception if one or more version data parameters is less than zero
			 * @note This constructor is a wrapper to similar constructor using unsigned int values to version information
			 */
			SemVer (int major, int minor, int patch, std::string build_type);

			/**
			 * @brief Create an SemVer object that can represent an software version data
			 * @param major Major version
			 * @param minor Minor version
			 * @param patch Patch version
			 * @param build_type Build type enumerator
			 * @throw Will throw an exception if one or more version data parameters is less than zero
			 * @note This constructor is a wrapper to similar constructor using unsigned int values to version information
			 */
			SemVer (int major, int minor, int patch, VersionLib::BuildType build_type);

			/**
			 * @brief Create an SemVer object that can represent an software version data
			 * @param major Major version
			 * @param minor Minor version
			 * @param patch Patch version
			 * @param build_type Build type (alpha, beta, rc, release)
			 * @param build_revision Determinate if is the first or second or other version of the same build type (like 1.9.2-rc.3). Note: If set as zero, the build_revision will be ignored.
			 * @throw Will throw an exception if one or more version data parameters is less than zero
			 * @throw If build_type is nullptr, will throw a exception VersionErrorCode_Invalid_Nullptr_Data_Passed
			 * @note This constructor is a wrapper to similar constructor using unsigned int values to version information
			 */
			SemVer (int major, int minor, int patch, const char* build_type, int build_revision);

			/**
			 * @brief Create an SemVer object that can represent an software version data
			 * @param major Major version
			 * @param minor Minor version
			 * @param patch Patch version
			 * @param build_type Build type (alpha, beta, rc, release)
			 * @param build_revision Determinate if is the first or second or other version of the same build type (like 1.9.2-rc.3). Note: If set as zero, the build_revision will be ignored.
			 * @throw Will throw an exception if one or more version data parameters is less than zero
			 * @note This constructor is a wrapper to similar constructor using unsigned int values to version information
			 */
			SemVer (int major, int minor, int patch, std::string build_type, int build_revision);

			/**
			 * @brief Create an SemVer object that can represent an software version data
			 * @param major Major version
			 * @param minor Minor version
			 * @param patch Patch version
			 * @param build_type Build type enumerator
			 * @param build_revision Determinate if is the first or second or other version of the same build type (like 1.9.2-rc.3). Note: If set as zero, the build_revision will be ignored.
			 * @throw Will throw an exception if one or more version data parameters is less than zero
			 * @note This constructor is a wrapper to similar constructor using unsigned int values to version information
			 */
			SemVer (int major, int minor, int patch, VersionLib::BuildType build_type, int build_revision);

			/**
			 * @brief Create an SemVer object that can represent an software version data
			 * @param major Major version
			 * @param minor Minor version
			 * @param patch Patch version
			 * @param build_type Build type (alpha, beta, rc, release)
			 * @param build_revision Determinate if is the first or second or other version of the same build type (like 1.9.2-rc.3). Note: If set as zero, the build_revision will be ignored.
			 * @param build Build of the version
			 * @param cmpBuild Set to compare the build with other version data. By default the build is not compared.
			 * @throw Will throw an exception if one or more version data parameters is less than zero
			 * @throw If build_type is nullptr, will throw a exception VersionErrorCode_Invalid_Nullptr_Data_Passed
			 * @note This constructor is a wrapper to similar constructor using unsigned int values to version information
			 */
			SemVer (int major, int minor, int patch, const char* build_type, int build_revision, long long build, bool cmpBuild = false);

			/**
			 * @brief Create an SemVer object that can represent an software version data
			 * @param major Major version
			 * @param minor Minor version
			 * @param patch Patch version
			 * @param build_type Build type (alpha, beta, rc, release)
			 * @param build_revision Determinate if is the first or second or other version of the same build type (like 1.9.2-rc.3). Note: If set as zero, the build_revision will be ignored.
			 * @param build Build of the version
			 * @param cmpBuild Set to compare the build with other version data. By default the build is not compared.
			 * @throw Will throw an exception if one or more version data parameters is less than zero
			 * @note This constructor is a wrapper to similar constructor using unsigned int values to version information
			 */
			SemVer (int major, int minor, int patch, std::string build_type, int build_revision, long long build, bool cmpBuild = false);

			/**
			 * @brief Create an SemVer object that can represent an software version data
			 * @param major Major version
			 * @param minor Minor version
			 * @param patch Patch version
			 * @param build_type Build type enumerator
			 * @param build_revision Determinate if is the first or second or other version of the same build type (like 1.9.2-rc.3). Note: If set as zero, the build_revision will be ignored.
			 * @param build Build of the version
			 * @param cmpBuild Set to compare the build with other version data. By default the build is not compared.
			 * @throw Will throw an exception if one or more version data parameters is less than zero
			 * @note This constructor is a wrapper to similar constructor using unsigned int values to version information
			 */
			SemVer (int major, int minor, int patch, VersionLib::BuildType build_type, int build_revision, long long build, bool cmpBuild = false);
			
			SemVer (const VersionLib::SemVer& other);

			SemVer (VersionLib::SemVer&& other) noexcept;

			//
			// Destructor:
			//

			~SemVer();

			//
			// Getters:
			//

			/**
			 * @brief Get the Major version
			 */
			unsigned int getMajor();

			/**
			 * @brief Get the Minor version
			 */
			unsigned int getMinor();

			/**
			 * @brief Get the patch number
			 */
			unsigned int getPatch();

			/**
			 * @brief Get the build number
			 */
			unsigned long long getBuild();

			/**
			 * @brief Get the build type (alpha, beta, etc) with C string style
			 * @param useShortStr Use the short string version
			 */
			const char* getBuildTypeCstr (bool useShortStr = true);

			/**
			 * @brief Get the build type (alpha, beta, etc).
			 * @param useShortStr Use the short string version
			 */
			std::string getBuildTypeStr (bool useShortStr = true);

			#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
			/**
			 * @brief Get the build type (alpha, beta, etc).
			 */
			VersionLib::VersionBuildType getBuildType();
			#else
			/**
			 * @brief Get the build type (alpha, beta, etc).
			 */
			VersionLib::BuildType getBuildType();

			/**
			 * @brief Get the build revision (used like alpha.2, rc.3).
			 */
			unsigned int getBuildRevision();
			#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT

			/**
			 * @brief Get the complete the build type data (like alpha.2, beta.3) with C string style
			 * @param useShortStr Use the short string version
			 * @param showReleaseType Show the "release" or "r" build type
			 */
			const char* getBuildTypeCompleteCstr (bool useShortStr = true, bool showReleaseType = false);

			/**
			 * @brief Get the complete the build type data (like alpha.2, beta.3).
			 * @param useShortStr Use the short string version
			 * @param showReleaseType Show the "release" or "r" build type
			 */
			std::string getBuildTypeComplete (bool useShortStr = true, bool showReleaseType = false);

			/**
			 * @brief Get the version data as a string
			 * @param useShortStr Use the short string version in build type
			 * @param hideBuildWord Hide the word "build" from the version string
			 * @param showReleaseType If true, the build type will be showed when is marked as RELEASE and the "release" or "r" word will be added
			 */
			std::string getVersionStr (bool useShortStr = true, bool hideBuildWord = false, bool showReleaseType = false);

			#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_METADATA_CLASS
			VersionLib::BuildMetadata getMetadata();
			#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_METADATA_CLASS

			//
			// Setters:
			//

			#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_METADATA_CLASS
			void setMetadata(std::string str_metadata);
			#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_METADATA_CLASS

			//
			// Conversion or Extraction methods:
			//

			/**
			 * @brief Convert the the SemVer object into a VersionStruct data
			 */
			VersionLib::VersionStruct toVersionStruct();

			//
			// Operators:
			//

			VersionLib::SemVer& operator= (const VersionLib::SemVer& other);

			VersionLib::SemVer& operator= (VersionLib::SemVer&& other) noexcept;

			// SemVer comparisons:

			bool operator== (const SemVer& other);
			bool operator!= (const SemVer& other);
			bool operator> (const SemVer& other);
			bool operator>= (const SemVer& other);
			bool operator< (const SemVer& other);
			bool operator<= (const SemVer& other);

			// Version Struct direct comparison operators:

			bool operator== (const VersionLib::VersionStruct& other);
			bool operator!= (const VersionLib::VersionStruct& other);
			bool operator> (const VersionLib::VersionStruct& other);
			bool operator>= (const VersionLib::VersionStruct& other);
			bool operator< (const VersionLib::VersionStruct& other);
			bool operator<= (const VersionLib::VersionStruct& other);

			// Direct version string comparisons:

			bool operator== (const std::string& verStr);
			bool operator!= (const std::string& verStr);
			bool operator> (const std::string& verStr);
			bool operator>= (const std::string& verStr);
			bool operator< (const std::string& verStr);
			bool operator<= (const std::string& verStr);
	};
}
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SEMVER_CLASS

#endif // !SEM_VER_CLASS_HPP