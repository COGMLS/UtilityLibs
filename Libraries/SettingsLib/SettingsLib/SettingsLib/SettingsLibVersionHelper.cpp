#include "SettingsLibVersionHelper.hpp"

std::string getSettingsLibVersion()
{
	return std::string(std::to_string(SETTINGS_LIBRARY_MAJOR_VERSION) + "." + std::to_string(SETTINGS_LIBRARY_MINOR_VERSION) + "." + std::to_string(SETTINGS_LIBRARY_REVISION_VERSION) + "-" + SETTINGS_LIBRARY_BUILD_TYPE);
}

std::string getSettingsLibBuild()
{
	return std::string("Build: ") + std::to_string(SETTINGS_LIBRARY_BUILD_VERSION);
}

std::wstring getSettingsLibVersionW()
{
	return std::wstring(std::to_wstring(SETTINGS_LIBRARY_MAJOR_VERSION) + L"." + std::to_wstring(SETTINGS_LIBRARY_MINOR_VERSION) + L"." + std::to_wstring(SETTINGS_LIBRARY_REVISION_VERSION) + L"-" + SETTINGS_LIBRARY_BUILD_TYPE_W);
}

std::wstring getSettingsLibBuildW()
{
	return std::wstring(L"Build: ") + std::to_wstring(SETTINGS_LIBRARY_BUILD_VERSION);
}

const SettingsLib::Types::SettingsLibVersion getSettingsLibVersionData()
{
	return SettingsLib::Types::SettingsLibVersion{ SETTINGS_LIBRARY_MAJOR_VERSION, SETTINGS_LIBRARY_MINOR_VERSION, SETTINGS_LIBRARY_REVISION_VERSION, SETTINGS_LIBRARY_BUILD_TYPE, SETTINGS_LIBRARY_BUILD_VERSION };
}