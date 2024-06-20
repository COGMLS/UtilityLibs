#include <iostream>
#include <vector>
#include <map>

#include "SettingsIniTools.hpp"
#include "SettingsLibDataTypes.hpp"

#include "test.hpp"
#include "debug.hpp"

int main (int argc, const char* argv[], const char* argp[])
{
	std::cout << "Test Console" << std::endl;

	#ifdef TEST_TOOLS

	std::vector<std::string> lines = 
	{
		"test0=54",
		"[LOADER]",
		"DefaultProfileDelay=3000",
		"MaxLogMemEntries=10",
		"LogAutoSave = true",
		"LogMaxFiles =30",
		"ProfileLogMaxFiles= 30",
		"MaxLogMemProfileEntries=20",
		"ProfileAutoSave=true",
		"UseDefaultInternalSettings = false #Test0",
		"#Test1",
		"; Test2",
		"[Test] # Comment",
		"Test1=10",
		"Test12=Hello World",
		"test20=1.25",
		"[Test 1]",
		"test30=1,36",
		"test40= # Comment",
		"test50= ; Comment",
		"test60",
		"",
		"test 61",
		" ",
		"test 62=",
		"test 63 = ",
		"test 64 = Hello",
		"test70=Hello2#Comment",
		"test80=Hello World 2 # Comment",
		"container1={1,2,3} #comment",
		"container2= {3,4,5}",
		"container3 = {7,8,9}"
	};

	std::string line = "";
	std::string section = "";
	std::string key = "";
	std::string value = "";
	std::string comment = "";

	for (int l = 0; l < lines.size(); l++)
	{
		line = lines[l];
		
		int r = testToolsExtractIniData(l, &line, &section, &key, &value, &comment);

		SettingsLib::Types::ConfigDataType* type = nullptr;
		type = new SettingsLib::Types::ConfigDataType;
		SettingsLib::Types::ConfigDataUnion* uData = nullptr;

		int r2 = testToolsConvertValue(&value, type, uData);

		line.clear();
		section.clear();
		key.clear();
		value.clear();
		comment.clear();

		if (type != nullptr)
		{
			if (*type == SettingsLib::Types::ConfigDataType::SETTINGS_LIB_CONFIG_DATA_UNION_TYPE_STRING && uData != nullptr)
			{
				delete uData->s;
				uData->s = nullptr;
			}
		}

		if (type != nullptr)
		{
			delete type;
			type = nullptr;
		}

		if (uData != nullptr)
		{
			delete uData;
			uData = nullptr;
		}
	}


	#endif // !TEST_TOOLS

	SettingsLib::Types::ConfigDataStore s1;
	s1 = "Hi";
	s1 = 10;
	s1 = -15;
	s1 = 3.1415f;
	s1 = true;

	s1.cleanData();

	s1 = "New Data!";

	SettingsLib::Types::ConfigDataStore s2;

	s2.setData("Hello");
	s2.setData(39ull);
	s2.setData(-85ll);
	s2.setData(6.6159);
	s2.setData(true);
	s2.setData("Abc");

	SettingsLib::Types::ConfigDataStore s3;

	s3 = s1;

	SettingsLib::Types::ConfigDataStore* s4 = new SettingsLib::Types::ConfigDataStore;

	s4->setData("Test 4");

	SettingsLib::Types::ConfigDataStore** s5;

	s5 = &s4;

	SettingsLib::Types::ConfigDataStore s6 = s2;

	s6 = L"Hello World!";

	return 0;
}