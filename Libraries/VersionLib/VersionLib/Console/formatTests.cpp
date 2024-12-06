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

	output += "Obj1 Info: " + obj1.getVersionStr() + "\n";
	output += "Obj2 Info: " + obj2.getVersionStr() + "\n\n";

	if (obj1 < obj2)
	{
		output += "obj1 < obj2\n";
	}

	if (obj1 <= obj2)
	{
		output += "obj1 <= obj2\n";
	}

	if (obj1 > obj2)
	{
		output += "obj1 > obj2\n";
	}

	if (obj1 >= obj2)
	{
		output += "obj1 >= obj2\n";
	}

	if (obj1 == obj2)
	{
		output += "obj1 == obj2\n";
	}

	if (obj1 != obj2)
	{
		output += "obj1 != obj2\n";
	}

	return output;
}