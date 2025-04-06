#include "SettingsLibVersionHelper.hpp"

SettingsLib::SettingsLibVersion getSettingsLibVersion()
{
	SettingsLib::SettingsLibVersion version;

	version.major = SETTINGS_LIBRARY_MAJOR_VERSION;
	version.minor = SETTINGS_LIBRARY_MINOR_VERSION;
	version.patch = SETTINGS_LIBRARY_PATCH_VERSION;
	version.revision = SETTINGS_LIBRARY_REVISION_NUMBER;
	version.build = SETTINGS_LIBRARY_BUILD_NUMBER;
	version.type = new char[std::strlen(SETTINGS_LIBRARY_BUILD_TYPE)];
	std::strcpy(version.type, SETTINGS_LIBRARY_BUILD_TYPE);

	return version;
}

std::string SettingsLib::getVersionStr(SettingsLib::SettingsLibVersion version, bool showBuild, bool showType)
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