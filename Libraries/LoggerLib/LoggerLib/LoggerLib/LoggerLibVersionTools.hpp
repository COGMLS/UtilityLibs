#pragma once

#ifndef LOGGER_LIB_VERSION_TOOL_HPP
#define LOGGER_LIB_VERSION_TOOL_HPP

#ifdef WIN32
	#ifdef LOGGER_EXPORTS
		#define LOGGER_LIB_API __declspec(dllexport)
	#else
		#define LOGGER_LIB_API __declspec(dllimport)
	#endif //!LOGGER_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#else
	#if __GNUC__ >= 4
		#ifdef LOGGER_EXPORTS
			#define LOGGER_LIB_API __attribute__((visibility("default")))
		#else
			#define LOGGER_LIB_API __attribute__((visibility("default")))
		#endif //!LOGGER_EXPORTS
	#else
		#ifdef LOGGER_EXPORTS
			#define LOGGER_LIB_API
		#else
			#define LOGGER_LIB_API
		#endif //!LOGGER_EXPORTS
	#endif
#endif // !WIN32

#ifdef WIN32
#include "pch.h"
#endif // !WIN32

#include "LoggerLibVersion.hpp"

#include <string>

namespace LoggerLib
{
	/**
	 * @brief Console Extensions Version number
	 */
	struct Version
	{
		unsigned int major;
		unsigned int minor;
		unsigned int revision;
		unsigned int build;
		char* type;
	};

	/**
	 * @brief Get the Console Extensions Library version
	 * @return Return a Version struct
	 */
	LOGGER_LIB_API inline LoggerLib::Version getLibVersion()
	{
		Version v;
		v.major = LOGGER_LIB_MAJOR_VERSION;
		v.minor = LOGGER_LIB_MINOR_VERSION;
		v.revision = LOGGER_LIB_REVISION_NUMBER;
		v.build = LOGGER_LIB_BUILD_NUMBER;
		v.type = LOGGER_LIB_BUILD_TYPE;
		return v;
	}

	/**
	 * @brief Transform the struct Version into a string version
	 * @param version Console Extensions Version struct
	 * @param showBuild Show the build number.
	 * @param showType Show the build type.
	 * @return Return a string version.
	 */
	LOGGER_LIB_API inline std::string getVersionStr (LoggerLib::Version& version, bool showBuild, bool showType)
	{
		std::string s;
		s = std::to_string(version.major) + "." + std::to_string(version.minor) + "." + std::to_string(version.revision);

		if (showType)
		{
			s += "-" + std::string(version.type);
		}

		if (showBuild)
		{
			s += " build " + std::to_string(version.build);
		}

		return s;
	}
}

#endif // !LOGGER_LIB_VERSION_TOOL_HPP