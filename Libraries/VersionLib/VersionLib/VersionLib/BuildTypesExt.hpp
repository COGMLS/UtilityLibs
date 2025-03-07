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
#include <cctype>
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
	#include <vector>
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

			#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
			std::vector<VersionLib::BuildType> types;
			#else
			VersionLib::BuildType type;
			#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE

		public:

			//
			// Constructors:
			//

			/**
			 * @brief Create a empty VersionBuildType object with standard value.
			 */
			VersionBuildType();

			#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
			/**
			 * @brief Create a version build type object that contains a sequence of multiple build type information.
			 * @param combined_build_type 
			 */
			VersionBuildType (std::vector<VersionLib::BuildType> combined_build_type);
			
			/**
			 * @brief Create a version build type object that contains a sequence of multiple build type information.
			 * @param combined_build_type 
			 */
			VersionBuildType (VersionLib::VersionBuildTypeC& combined_build_type);
			#else
			/**
			 * @brief Create a build type from a string information.
			 * @param build_type_str Build type string. The accepted values are: alpha, beta, release candidate, release, canary, development and pre release.
			 * @note If other string value was send, it will be discarded.
			 * @note Canary, development and pre release has the same meaning as alpha, beta, release candidate respectively.
			 */
			VersionBuildType (std::string build_type_str);

			/**
			 * @brief Create a build type object based on VersionBuildType enumerator
			 * @param build_type 
			 */
			VersionBuildType (VersionLib::BuildType build_type);
			#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE

			VersionBuildType (const VersionLib::VersionBuildType& other);

			VersionBuildType (VersionLib::VersionBuildType&& other) noexcept;

			//
			// Destructor:
			//

			~VersionBuildType();

			//
			// Getters and Auxiliary methods:
			//

			#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
			std::vector<VersionLib::BuildType> getBuildType();
			#else
			VersionLib::BuildType getBuildType();
			#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE

			/**
			 * @brief Generate the build type string information. The string output does not contain the build type number/revision
			 * @param useShortStr Use short build type short string variant, if available.
			 */
			std::string getBuildTypeStr(bool useShortStr = true);

			/**
			 * @brief Create a copy converted to VersionBuildTypeC to use in C style programs
			 */
			VersionLib::VersionBuildTypeC toStruct();

			//
			// Operators:
			//

			VersionLib::VersionBuildType& operator= (const VersionLib::VersionBuildType& other);
			VersionLib::VersionBuildType& operator= (VersionLib::VersionBuildType&& other) noexcept;

			VersionLib::VersionBuildType& operator= (const VersionLib::BuildType& type);

			VersionLib::VersionBuildType& operator= (const VersionLib::VersionBuildTypeC& type);

			#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
			VersionLib::VersionBuildType& operator= (const std::vector<VersionLib::BuildType> types);
			#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE

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