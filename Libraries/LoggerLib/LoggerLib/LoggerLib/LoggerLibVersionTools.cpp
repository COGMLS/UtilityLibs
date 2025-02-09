#include "LoggerLibVersionTools.hpp"

LoggerLib::Version LoggerLib::getLibVersion()
{
	LoggerLib::Version v;
	v.major = LOGGER_LIB_MAJOR_VERSION;
	v.minor = LOGGER_LIB_MINOR_VERSION;
	v.patch = LOGGER_LIB_PATCH_VERSION;
	v.build = LOGGER_LIB_BUILD_NUMBER;
	v.revision = LOGGER_LIB_REVISION_NUMBER;
	v.type = new char[std::strlen(LOGGER_LIB_BUILD_TYPE)];
	std::strcpy(v.type, LOGGER_LIB_BUILD_TYPE);
	return v;
}

std::string LoggerLib::getVersionStr(LoggerLib::Version version, bool showBuild, bool showType)
{
	std::string s;
	s = std::to_string(version.major) + "." + std::to_string(version.minor) + "." + std::to_string(version.patch);

	if (showType && !(std::strcmp(version.type, "release") == 0 || std::strcmp(version.type, "RELEASE") == 0))
	{
		s += "-" + std::string(version.type);
	}

	if (version.revision > 0)
	{
		s += "." + std::to_string(version.revision);
	}

	if (showBuild)
	{
		s += " build " + std::to_string(version.build);
	}

	return s;
}
