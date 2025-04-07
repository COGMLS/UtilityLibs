#pragma once 

#ifndef SETTINGS_LIB_VERSION_HELPER_HPP
#define SETTINGS_LIB_VERSION_HELPER_HPP

#ifdef WIN32
	#ifdef SETTINGS_LIB_EXPORTS
		#define SETTINGS_LIB_API __declspec(dllexport)
	#else
		#define SETTINGS_LIB_API __declspec(dllimport)
	#endif //!SETTINGS_LIB_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#else
	#if __GNUC__ >= 4
		#ifdef SETTINGS_LIB_EXPORTS
			#define SETTINGS_LIB_API __attribute__((visibility("default")))
		#else
			#define SETTINGS_LIB_API __attribute__((visibility("default")))
		#endif //!SETTINGS_LIB_EXPORTS
	#else
		#ifdef SETTINGS_LIB_EXPORTS
			#define SETTINGS_LIB_API
		#else
			#define SETTINGS_LIB_API
		#endif //!SETTINGS_LIB_EXPORTS
	#endif
#endif // !WIN32

#include <string>
#include <cstring>

#include "SettingsLibVersion.hpp"

namespace SettingsLib
{
	/// @brief Settings Library Version struct
	struct SettingsLibVersion
	{
		unsigned int major;
		unsigned int minor;
		unsigned int patch;
		unsigned int revision;
		unsigned long long build;
		char* type;
	};

	/// @brief Get all version and build information on struct SettingsLibVersion
	SettingsLib::SettingsLibVersion SETTINGS_LIB_API getSettingsLibVersion();

	/**
	 * @brief Transform the struct Version into a string version
	 * @param version Console Extensions Version struct
	 * @param showBuild Show the build number.
	 * @param showType Show the build type.
	 * @return Return a string version.
	 */
	std::string SETTINGS_LIB_API getVersionStr (SettingsLib::SettingsLibVersion version, bool showBuild, bool showType);
}

#endif //! SETTINGS_LIB_VERSION_HELPER_HPP