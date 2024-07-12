#include <iostream>
#include <vector>
#include <map>

#include "SettingsIniTools.hpp"
#include "SettingsLibDataTypes.hpp"
#include "SettingsIniConfigData.hpp"
#include "SettingsIniConfig.hpp"

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
		"test90=\"Hello World 3\" # Comment",
		"container1={1,2,3} #comment",
		"container2= {3,4,5}",
		"container3 = {7,8,9}",
		"container4 = {\"hi\", 15}",
		"container5 = {hello\" world, hi}"
	};

	std::string line = "";
	SettingsLib::Types::ConfigIni configIni("settings.ini");

	for (int l = 0; l < lines.size(); l++)
	{
		line = lines[l];
		std::cout << "[" << l << "]::" << line << std::endl;
		configIni.readLine(line);
		line.clear();
	}

	#endif // !TEST_TOOLS

	#ifdef TEST_OBJ_STORE
	
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

	#endif // !TEST_OBJ_STORE

	return 0;
}