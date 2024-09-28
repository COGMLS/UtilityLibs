#pragma once

#ifndef VERSION_HPP
#define VERSION_HPP

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
#include "Tools.hpp"

namespace VersionLib
{
	/**
	 * @brief Version Data class with support to Major, Minor, Patch version numbers and Build and build type support.
	 */
	class VERSION_LIB_API VersionData
	{
		private:

			unsigned int major;					// Major version number
			unsigned int minor;					// Minor version number
			unsigned int patch;					// Patch version number
			unsigned long long build;			// Build number
			VersionLib::BuildType build_type;	// Build type (alpha, a, beta, etc
			unsigned int build_type_number;		// Build type number (alpha1, rc3)

		public:

			//
			// Constructors:
			//

			//VersionData (std::string versionStr);
			VersionData (unsigned int major, unsigned int minor, unsigned int patch);
			VersionData (unsigned int major, unsigned int minor, unsigned int patch, unsigned long long build);
			VersionData (unsigned int major, unsigned int minor, unsigned int patch, unsigned long long build, char* build_type);
			VersionData (unsigned int major, unsigned int minor, unsigned int patch, unsigned long long build, std::string build_type);
			VersionData (unsigned int major, unsigned int minor, unsigned int patch, unsigned long long build, VersionLib::BuildType build_type);
			VersionData (unsigned int major, unsigned int minor, unsigned int patch, unsigned long long build, char* build_type, unsigned int build_type_number);
			VersionData (unsigned int major, unsigned int minor, unsigned int patch, unsigned long long build, std::string build_type, unsigned int build_type_number);
			VersionData (unsigned int major, unsigned int minor, unsigned int patch, unsigned long long build, VersionLib::BuildType build_type, unsigned int build_type_number);
			
			//
			// Destructor:
			//

			~VersionData();

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
			const char* getBuildTypeCstr(bool useShortStr);

			/**
			 * @brief Get the build type (alpha, beta, etc).
			 * @param useShortStr Use the short string version
			 */
			std::string getBuildType(bool useShortStr);

			/**
			 * @brief Get the build type number (used like alpha2, rc3).
			 */
			unsigned int getBuildTypeNumber();

			/**
			 * @brief Get the complete the build type data (like alpha2, beta3) with C string style
			 */
			const char* getBuildTypeCompleteCstr();

			/**
			 * @brief Get the complete the build type data (like alpha2, beta3).
			 */
			std::string getBuildTypeComplete();

			//
			// Operators:
			//

			bool operator==(const VersionData& other);
			bool operator!=(const VersionData& other);
			bool operator>(const VersionData& other);
			bool operator>=(const VersionData& other);
			bool operator<(const VersionData& other);
			bool operator<=(const VersionData& other);

			//bool operator==(const std::string& other);
			//bool operator!=(const std::string& other);
			//bool operator>(const std::string& other);
			//bool operator>=(const std::string& other);
			//bool operator<(const std::string& other);
			//bool operator<=(const std::string& other);
	};
}

#endif // !VERSION_HPP