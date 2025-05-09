#include "formatTests.hpp"

VersionFormatTest::VersionFormatTest (std::string version)
{
	#if VERSION_LIB_VERSION_INFO_MINOR_VERSION <= 8
	this->verData.reset(new VersionLib::VersionData(version));
	#else
	this->verData.reset(new VersionLib::SemVer(version));
	#endif // !VERSION_LIB_VERSION_INFO_MINOR_VERSION
	this->strData = version;
}

VersionFormatTest::VersionFormatTest (const VersionFormatTest& other)
{
	#if VERSION_LIB_VERSION_INFO_MINOR_VERSION <= 8
	this->verData.reset(new VersionLib::VersionData(other.strData));
	#else
	this->verData.reset(new VersionLib::SemVer(other.strData));
	#endif // !VERSION_LIB_VERSION_INFO_MINOR_VERSION
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

std::string testVersionData (VersionLib::VersionData& obj1, VersionLib::VersionData& obj2, bool testStructOnObj2)
{
	std::string output;
	std::string ver1 = obj1.getVersionStr(true, false, true);
	std::string ver2 = obj2.getVersionStr(true, false, true);

	output += "VerObj1 Info: " + ver1 + "\n";
	output += "VerObj2 Info: " + ver2 + "\n\n";

	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_OPERATOR_STRUCT_COMPARISON

	if (testStructOnObj2)
	{
		VersionLib::VersionStruct obj2Struct = obj2.toVersionStruct();

		if (obj1 < obj2Struct)
		{
			output += ver1 + " < " + ver2 + "\n";
		}
	
		if (obj1 <= obj2Struct)
		{
			output += ver1 + " <= " + ver2 + "\n";
		}
	
		if (obj1 > obj2Struct)
		{
			output += ver1 + " > " + ver2 + "\n";
		}
	
		if (obj1 >= obj2Struct)
		{
			output += ver1 + " >= " + ver2 + "\n";
		}
	
		if (obj1 == obj2Struct)
		{
			output += ver1 + " == " + ver2 + "\n";
		}
	
		if (obj1 != obj2Struct)
		{
			output += ver1 + " != " + ver2 + "\n";
		}
	}
	else
	{
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
	}
	#else
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
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_OPERATOR_STRUCT_COMPARISON

	return output;
}

std::string testVersionData(VersionLib::VersionData &obj, std::string verStr)
{
    std::string output;
	std::string ver = obj.getVersionStr(true, false, true);

	output += "VerObj1 Info: " + ver + "\n";
	output += "VerObj2 Info: " + verStr + "\n\n";

	if (obj < verStr)
	{
		output += ver + " < " + verStr + "\n";
	}

	if (obj <= verStr)
	{
		output += ver + " <= " + verStr + "\n";
	}

	if (obj > verStr)
	{
		output += ver + " > " + verStr + "\n";
	}

	if (obj >= verStr)
	{
		output += ver + " >= " + verStr + "\n";
	}

	if (obj == verStr)
	{
		output += ver + " == " + verStr + "\n";
	}

	if (obj != verStr)
	{
		output += ver + " != " + verStr + "\n";
	}

	return output;
}

#if VERSION_LIB_VERSION_INFO_MINOR_VERSION >= 9
std::string testVersionData (VersionLib::SemVer& obj1, VersionLib::SemVer& obj2, bool testStructOnObj2)
{
	std::string output;
	std::string ver1 = obj1.getVersionStr(true, false, true);
	std::string ver2 = obj2.getVersionStr(true, false, true);

	output += "VerObj1 Info: " + ver1 + "\n";
	output += "VerObj2 Info: " + ver2 + "\n\n";

	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_OPERATOR_STRUCT_COMPARISON

	if (testStructOnObj2)
	{
		VersionLib::VersionStruct obj2Struct = obj2.toVersionStruct();

		if (obj1 < obj2Struct)
		{
			output += ver1 + " < " + ver2 + "\n";
		}
	
		if (obj1 <= obj2Struct)
		{
			output += ver1 + " <= " + ver2 + "\n";
		}
	
		if (obj1 > obj2Struct)
		{
			output += ver1 + " > " + ver2 + "\n";
		}
	
		if (obj1 >= obj2Struct)
		{
			output += ver1 + " >= " + ver2 + "\n";
		}
	
		if (obj1 == obj2Struct)
		{
			output += ver1 + " == " + ver2 + "\n";
		}
	
		if (obj1 != obj2Struct)
		{
			output += ver1 + " != " + ver2 + "\n";
		}
	}
	else
	{
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
	}
	#else
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
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_OPERATOR_STRUCT_COMPARISON

	return output;
}

std::string testVersionData(VersionLib::SemVer &obj, std::string verStr)
{
    std::string output;
	std::string ver = obj.getVersionStr(true, false, true);

	output += "VerObj1 Info: " + ver + "\n";
	output += "VerObj2 Info: " + verStr + "\n\n";

	if (obj < verStr)
	{
		output += ver + " < " + verStr + "\n";
	}

	if (obj <= verStr)
	{
		output += ver + " <= " + verStr + "\n";
	}

	if (obj > verStr)
	{
		output += ver + " > " + verStr + "\n";
	}

	if (obj >= verStr)
	{
		output += ver + " >= " + verStr + "\n";
	}

	if (obj == verStr)
	{
		output += ver + " == " + verStr + "\n";
	}

	if (obj != verStr)
	{
		output += ver + " != " + verStr + "\n";
	}

	return output;
}
#endif // !VERSION_LIB_VERSION_INFO_MINOR_VERSION
