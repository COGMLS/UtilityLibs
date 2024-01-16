#include <iostream>

#include "SettingsLibDef.hpp"
#include "SettingsLibProperties.hpp"
#include "SettingsLib.hpp"

#define FIELD1		"Field1"
#define FIELD1W		L"Field1"

int main()
{
	std::cout << "Settings Library Test\n" << std::endl;

	std::cout << "Library version: " << SettingsLib::getSettingsLibVersion() << std::endl;

	SettingsLib::SettingsLibVersion settingsVer = SettingsLib::getSettingsLibVersionData();

	std::cout << "\nMajor ver: \t" << settingsVer.major
		<< "\nMinor ver: \t" << settingsVer.minor
		<< "\nRevision: \t" << settingsVer.revision
		<< "\nBuild Type: \t" << settingsVer.buildType
		<< "\nBuild: \t\t" << settingsVer.build
		<< "\n" << std::endl;

	return 0;
}