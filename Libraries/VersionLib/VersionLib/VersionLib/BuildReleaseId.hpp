#pragma once

#ifndef VERSION_BUILD_RELEASE_ID_HPP
#define VERSION_BUILD_RELEASE_ID_HPP

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

#include "Tools.hpp"
#include "BuildTypes.hpp"
#include "ReleaseTools.hpp"

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
#include "ExceptionComponents.hpp"
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS

#include <string>

namespace VersionLib
{
	/**
	 * @brief Build release identifier class, to provide more advanced capacities with build type identifier, including revision's release and combined releases (alpha.beta, alpha.1.beta, etc)
	 * @note This class does not allow change the values after the object creation
	 */
	class VERSION_LIB_API BuildRelease
	{
		private:

			bool releaseIdentified;					// Control if the release contains a valid information
			unsigned short revision;				// Release revision
			VersionLib::BuildType release;			// Release type id (old build type)

		public:

			//
			// Constructors:
			//

			/**
			 * @brief Create an object representing a build release or pre-release using the default value defined in the VersionLib
			 */
			BuildRelease();

			/**
			 * @brief Create an object representing a build release information, using a string to provide the information.
			 * @param release String with the information about the release type. It can be: alpha, alpha.1.
			 * @note This method only identify the FIRST occurrence of release and revision information. If you are using a combined release informations, use the method to create a vector of releases.
			 */
			BuildRelease (std::string release);

			/**
			 * @brief Create an object representing a build release information, using the BuildType and a optional revision.
			 * @param release Release type
			 * @param revision Revision of the release or pre-release build.
			 * @note Using 'revision' as zero, will disable the revision check and string output conversion.
			 */
			BuildRelease (VersionLib::BuildType release, unsigned short revision = 0);

			/**
			 * @brief Create an object representing a build release information, using the VersionReleaseDataC struct.
			 * @param build_release Release data
			 */
			BuildRelease (VersionLib::VersionReleaseDataC& build_release);

			BuildRelease (const VersionLib::BuildRelease& other);

			BuildRelease (VersionLib::BuildRelease&& other) noexcept;

			//
			// Destructor:
			//

			~BuildRelease();

			//
			// Getters and other methods:
			//

			/**
			 * @brief Get the release build id
			 */
			VersionLib::BuildType getRelease();
			
			/**
			 * @brief Get the revision
			 */
			unsigned short getRevision();

			/**
			 * @brief Calculate the build release weight
			 * @param pos Position of the release type. The minimum acceptable value is 1.
			 * @note To see more details about the mathematical methods used here, check the documentation file
			 */
			float getWeight (unsigned short pos = 1);

			/**
			 * @brief Get the release information status.
			 * @return True if the information used to create the object was correctly identified, otherwise will be false.
			 */
			bool isReleaseInfoOk();
			
			/**
			 * @brief Transform the release and revision data into a string format.
			 * @param useShortStr
			 * @param showReleaseType
			 * @note If the revision is zero, no revision will be added.
			 */
			std::string toString (bool useShortStr = true, bool showReleaseType = false);

			/**
			 * @brief Export the internal data to VersionReleaseDataC struct
			 */
			VersionLib::VersionReleaseDataC toReleaseDataC();

			//
			// Build Release Operators:
			//

			// Assign operators:

			VersionLib::BuildRelease& operator= (const VersionLib::BuildRelease& other);
			VersionLib::BuildRelease& operator= (VersionLib::BuildRelease&& other) noexcept;

			// Test operators:

			explicit operator bool() const;

			bool operator== (const VersionLib::BuildRelease& other);
			bool operator!= (const VersionLib::BuildRelease& other);

			bool operator< (const VersionLib::BuildRelease& other);
			bool operator> (const VersionLib::BuildRelease& other);
			bool operator<= (const VersionLib::BuildRelease& other);
			bool operator>= (const VersionLib::BuildRelease& other);
	};
}

#endif // !VERSION_BUILD_RELEASE_ID_HPP