#include <iostream>

#include "VersionLib.hpp"

void testVersionData (VersionLib::VersionData& obj1, VersionLib::VersionData& obj2)
{
	std::cout << "Obj1 Info: " << obj1.getVersionStr() << std::endl;
	std::cout << "Obj2 Info: " << obj2.getVersionStr() << std::endl << std::endl;

	if (obj1 < obj2)
	{
		std::cout << "obj1 < obj2" << std::endl;
	}

	if (obj1 <= obj2)
	{
		std::cout << "obj1 <= obj2" << std::endl;
	}

	if (obj1 > obj2)
	{
		std::cout << "obj1 > obj2" << std::endl;
	}

	if (obj1 >= obj2)
	{
		std::cout << "obj1 >= obj2" << std::endl;
	}

	if (obj1 == obj2)
	{
		std::cout << "obj1 == obj2" << std::endl;
	}

	if (obj1 != obj2)
	{
		std::cout << "obj1 != obj2" << std::endl;
	}
}

int main()
{
	VersionLib::VersionData appVersion (1, 0, 0, 1, VersionLib::BuildType::BETA, 0);
	VersionLib::VersionData test (1, 0, 0, 1, VersionLib::BuildType::ALPHA, 0);
	VersionLib::VersionData test2 ("1.2.1 build 700");
	VersionLib::VersionData test3 ("1.6.1.3 build 6100");
	VersionLib::VersionData test4 ("2.5.8.15");
	VersionLib::VersionData test5 ("17.5.12-a");
	VersionLib::VersionData test6 ("3.1.7-beta.6");
	VersionLib::VersionData test7 ("7.1.3-rc.1 752");
	VersionLib::VersionData test8 ("10.3.1-alpha.3 build 569");

	VersionLib::VersionData* vTest = &test;

	testVersionData(appVersion, *vTest);

	return 0;
}