#pragma once

#ifndef VERSION_BASE_CLASS_HPP
#define VERSION_BASE_CLASS_HPP

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

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_BASE_CLASS

#include <array>
#include <string>

#include "BuildTypesExt.hpp"
#include "BuildMetadata.hpp"

namespace VersionLib
{
	/**
	 * @brief Version Base class for base definitions for all Version classes
	 * @tparam core_num Number of version core components
	 */
	template<unsigned short core_num>
	class VERSION_LIB_API VersionBase
	{
		protected:

			std::array<unsigned short, core_num> core;	// Version core components
			VersionLib::VersionBuildType build_type;	// Version release component
			bool compare_build;							// Check if the version build is configured to compare during the version test with other object
			unsigned long build;						// Build compilation
			VersionLib::BuildMetadata metadata;			// Version build metadata

		public:

			//
			// Constructor:
			//

			virtual VersionBase();

			//
			// Destructor:
			//

			~VersionBase() {};	// Empty constructor. All internal data is local.

			//
			// Operators:
			//

			VersionLib::VersionBase<core_num>& operator= (const VersionLib::VersionBase<core_num>& other);
			VersionLib::VersionBase<core_num>& operator= (VersionLib::VersionBase<core_num>&& other) noexcept;

			//
			// Getters:
			//
			
			std::array<unsigned short, core_num> getCore();

			VersionLib::VersionBuildType getRelease();

			unsigned long getBuildCompilation();

			bool getCompareBuild();

			VersionLib::BuildMetadata getBuildMetadata();

			virtual std::string getVersionStr();

			virtual std::string getVersionStr (bool useShortStr, bool hideBuildWord, bool showReleaseType);

			virtual std::string getReleaseStr (bool useShortStr = true);

			//
			// Setters:
			//

			void setCompareBuild (bool compare_build);
	};
}

//
// Operators:
//

template<unsigned short core_num> VersionLib::VersionBase<core_num>& VersionLib::VersionBase<core_num>::operator= (const VersionLib::VersionBase<core_num>& other)
{
	if (this == &other)
	{
		return *this;
	}

	this->core = other.core;
	this->build_type = other.build_type;
	this->compare_build = other.compare_build;
	this->build = other.build;
	this->metadata = other.metadata;

	return *this;
}

template<unsigned short core_num> VersionLib::VersionBase<core_num>& VersionLib::VersionBase<core_num>::operator= (VersionLib::VersionBase<core_num>&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	this->core = std::move(other.core);
	this->build_type = std::move(other.build_type);
	this->compare_build = std::move(other.compare_build);
	this->build = std::move(other.build);
	this->metadata = std::move(other.metadata);

	return *this;
}

//
// Getters:
//

template<unsigned short core_num> std::array<unsigned short, core_num> VersionLib::VersionBase<core_num>::getCore()
{
	return this->core;
}

template<unsigned short core_num> VersionLib::VersionBuildType VersionLib::VersionBase<core_num>::getRelease()
{
	return this->build_type;
}

template<unsigned short core_num> unsigned long VersionLib::VersionBase<core_num>::getBuildCompilation()
{
	return this->build;
}

template<unsigned short core_num> bool VersionLib::VersionBase<core_num>::getCompareBuild()
{
	return this->compare_build;
}

template<unsigned short core_num> VersionLib::BuildMetadata VersionLib::VersionBase<core_num>::getBuildMetadata()
{
	return this->metadata;
}

template<unsigned short core_num> std::string VersionLib::VersionBase<core_num>::getVersionStr()
{
	return std::string();
}

template<unsigned short core_num> std::string VersionLib::VersionBase<core_num>::getVersionStr (bool useShortStr, bool hideBuildWord, bool showReleaseType)
{
	return std::string();
}

template<unsigned short core_num> std::string VersionLib::VersionBase<core_num>::getReleaseStr (bool useShortStr)
{
	return std::string();
}

//
// Setters:
//

template<unsigned short core_num> void VersionLib::VersionBase<core_num>::setCompareBuild (bool compare_build)
{
	this->compare_build = compare_build;
}

#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_BASE_CLASS

#endif // !VERSION_BASE_CLASS_HPP