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
	VersionLib::VersionData test2 ("1.2.0 build 700");

	VersionLib::VersionData* vTest = &test;

	testVersionData(appVersion, *vTest);

	return 0;
}