#pragma once

#ifndef VERSION_FORMAT_TEST
#define VERSION_FORMAT_TEST

#include <string>
#include <memory>
#include <vector>

#include "VersionLib.hpp"

class VersionFormatTest
{
	private:

		#if VERSION_LIB_VERSION_INFO_MINOR_VERSION <= 8
		std::unique_ptr<VersionLib::VersionData> verData;
		#else
		std::unique_ptr<VersionLib::SemVer> verData;
		#endif // !VERSION_LIB_VERSION_INFO_MINOR_VERSION
		std::string strData;

	public:

		VersionFormatTest (std::string version);

		VersionFormatTest (const VersionFormatTest& other);

		VersionFormatTest (VersionFormatTest&& other) noexcept;

		~VersionFormatTest();

		std::string getTest();
};

std::string testVersionData (VersionLib::VersionData& obj1, VersionLib::VersionData& obj2, bool testStructOnObj2 = false);

std::string testVersionData (VersionLib::VersionData& obj, std::string verStr);

#if VERSION_LIB_VERSION_INFO_MINOR_VERSION >= 9

std::string testVersionData (VersionLib::SemVer& obj1, VersionLib::SemVer& obj2, bool testStructOnObj2 = false);

std::string testVersionData (VersionLib::SemVer& obj, std::string verStr);

#endif // !VERSION_LIB_VERSION_INFO_MINOR_VERSION

#endif // !VERSION_FORMAT_TEST