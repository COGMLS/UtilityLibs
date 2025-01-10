#include "formatTests.hpp"

VersionFormatTest::VersionFormatTest (std::string version)
{
	this->verData.reset(new VersionLib::VersionData(version));
	this->strData = version;
}

VersionFormatTest::VersionFormatTest (const VersionFormatTest& other)
{
	this->verData.reset(new VersionLib::VersionData(other.strData));
	this->strData = other.strData;
}

VersionFormatTest::VersionFormatTest (VersionFormatTest&& other) noexcept
{
	this->verData.swap(other.verData);
	this->strData = std::move(other.strData);
}

VersionFormatTest::~VersionFormatTest()
{
	this->verData.reset(nullptr);
}

std::string VersionFormatTest::getTest()
{
	std::string output;

	output += "String Version: " + this->strData;
	output += "\nVersion Data: " + this->verData->getVersionStr(false, false);

	return output;
}

std::string testVersionData (VersionLib::VersionData& obj1, VersionLib::VersionData& obj2)
{
	std::string output;
	std::string ver1 = obj1.getVersionStr(true, false, true);
	std::string ver2 = obj2.getVersionStr(true, false, true);

	output += "VerObj1 Info: " + ver1 + "\n";
	output += "VerObj2 Info: " + ver2 + "\n\n";

	if (obj1 < obj2)
	{
		output += ver1 + " < " + ver2 + "\n";
	}

	if (obj1 <= obj2)
	{
		output += ver1 + " <= " + ver2 + "\n";
	}

	if (obj1 > obj2)
	{
		output += ver1 + " > " + ver2 + "\n";
	}

	if (obj1 >= obj2)
	{
		output += ver1 + " >= " + ver2 + "\n";
	}

	if (obj1 == obj2)
	{
		output += ver1 + " == " + ver2 + "\n";
	}

	if (obj1 != obj2)
	{
		output += ver1 + " != " + ver2 + "\n";
	}

	return output;
}