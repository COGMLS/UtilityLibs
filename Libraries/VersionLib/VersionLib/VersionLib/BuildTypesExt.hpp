#pragma once

#ifndef VERSION_BUILD_TYPE_EXTENSION_HPP
#define VERSION_BUILD_TYPE_EXTENSION_HPP

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
#include "Tools.hpp"

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
#include "ExceptionComponents.hpp"
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
#include <string>
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
	#include <vector>
	#include "ReleaseTools.hpp"
	#include "BuildReleaseId.hpp"
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
namespace VersionLib
{
	/**
	 * @brief Version build type class to provide more compatibility with other values like, canary, development, etc.
	 */
	class VERSION_LIB_API VersionBuildType
	{
		private:

			std::vector<VersionLib::BuildRelease> types;

		public:

			//
			// Constructors:
			//

			/**
			 * @brief Create a empty VersionBuildType object with standard value.
			 */
			VersionBuildType();

			/**
			 * @brief Create a version build type object that contains a sequence of multiple build type information.
			 * @param combined_build_type 
			 */
			VersionBuildType (std::vector<VersionLib::BuildRelease> combined_build_type);
			
			/**
			 * @brief Create a version build type object that contains a sequence of multiple build type information.
			 * @param combined_build_type 
			 */
			VersionBuildType (VersionLib::VersionBuildTypeC& combined_build_type);
			
			/**
			 * @brief Create a build type from a string information.
			 * @param build_type_str Build type string. The accepted values are: alpha, beta, release candidate, release, canary, development and pre release.
			 * @note If other string value was send, it will be discarded.
			 * @note Canary, development and pre release has the same meaning as alpha, beta, release candidate respectively.
			 */
			VersionBuildType (std::string build_type_str);

			/**
			 * @brief Create a build type object based on VersionBuildType enumerator
			 * @param build_type Build release type
			 * @param revision Release revision
			 */
			VersionBuildType (VersionLib::BuildType build_type, unsigned short revision = 0);

			VersionBuildType (const VersionLib::VersionBuildType& other);

			VersionBuildType (VersionLib::VersionBuildType&& other) noexcept;

			//
			// Destructor:
			//

			~VersionBuildType();

			//
			// Getters and Auxiliary methods:
			//

			std::vector<VersionLib::BuildRelease> getBuildType();

			/**
			 * @brief Generate the build type string information. The string output does not contain the build type number/revision
			 * @param useShortStr Use short build type short string variant, if available.
			 */
			std::string getBuildTypeStr (bool useShortStr = true, bool showReleaseType = false);

			/**
			 * @brief Create a copy converted to VersionBuildTypeC to use in C style programs
			 */
			VersionLib::VersionBuildTypeC toStruct();

			/**
			 * @brief Calculate the total build type of the release version. Single releases like, alpha, beta and others have the same weight of BuildType values. The composed build types like, alpha.beta or x.1.y.6.z.11, have a weight calculation to determinate if is near of a pure type x or y, etc.
			 * @return 
			 */
			float getBuildTypeWeight();

			//void setRelease(std::vector<VersionLib::BuildRelease> types);

			//
			// Operators:
			//

			VersionLib::VersionBuildType& operator= (const VersionLib::VersionBuildType& other);
			VersionLib::VersionBuildType& operator= (VersionLib::VersionBuildType&& other) noexcept;

			VersionLib::VersionBuildType& operator= (const VersionLib::BuildType& type);

			VersionLib::VersionBuildType& operator= (const VersionLib::VersionBuildTypeC& types);

			VersionLib::VersionBuildType& operator= (const VersionLib::BuildRelease type);
			VersionLib::VersionBuildType& operator= (const std::vector<VersionLib::BuildRelease> types);

			//
			// Comparison operators:
			//

			// VersionBuildType:

			bool operator== (const VersionLib::VersionBuildType& other);
			bool operator!= (const VersionLib::VersionBuildType& other);

			bool operator< (const VersionLib::VersionBuildType& other);
			bool operator> (const VersionLib::VersionBuildType& other);
			bool operator<= (const VersionLib::VersionBuildType& other);
			bool operator>= (const VersionLib::VersionBuildType& other);

			#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_DIRECT_COMP_WITH_BUILDTYPE_C
			// VersionBuildTypeC:

			bool operator== (const VersionLib::VersionBuildTypeC& other);
			bool operator!= (const VersionLib::VersionBuildTypeC& other);

			bool operator< (const VersionLib::VersionBuildTypeC& other);
			bool operator> (const VersionLib::VersionBuildTypeC& other);
			bool operator<= (const VersionLib::VersionBuildTypeC& other);
			bool operator>= (const VersionLib::VersionBuildTypeC& other);
			#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_DIRECT_COMP_WITH_BUILDTYPE_C

			// BuildType:

			bool operator== (const VersionLib::BuildType& other);
			bool operator!= (const VersionLib::BuildType& other);

			bool operator< (const VersionLib::BuildType& other);
			bool operator> (const VersionLib::BuildType& other);
			bool operator<= (const VersionLib::BuildType& other);
			bool operator>= (const VersionLib::BuildType& other);
	};
}
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT

#endif // !VERSION_BUILD_TYPE_EXTENSION_HPP