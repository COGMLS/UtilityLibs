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

		std::unique_ptr<VersionLib::VersionData> verData;
		std::string strData;

	public:

		VersionFormatTest (std::string version);

		VersionFormatTest (const VersionFormatTest& other);

		VersionFormatTest (VersionFormatTest&& other) noexcept;

		~VersionFormatTest();

		std::string getTest();
};

std::string testVersionData (VersionLib::VersionData& obj1, VersionLib::VersionData& obj2);

#endif // !VERSION_FORMAT_TEST