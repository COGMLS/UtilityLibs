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
	VersionLib::VersionData libVersion = VersionLib::internalVersionData();
	VersionLib::VersionData appVersion (1, 0, 0, 1, VersionLib::BuildType::BETA, 0);
	VersionLib::VersionData test (1, 0, 0, 1, VersionLib::BuildType::ALPHA, 0);
	VersionLib::VersionData test2 ("1.2.1 build 700");				// OK
	VersionLib::VersionData test3 ("1.6.1.3 build 6100");			// FAIL: Revision is not recognized
	VersionLib::VersionData test4 ("2.5.8.15");						// FAIL: Revision is not recognized.
	VersionLib::VersionData test5 ("17.5.12-a");					// Ok
	VersionLib::VersionData test6 ("3.1.7-beta.6");					// Ok
	VersionLib::VersionData test7 ("7.1.3-rc.1 752");				// Ok
	VersionLib::VersionData test8 ("10.3.1-alpha.3 build 569");		// Ok
	VersionLib::VersionData test9 ("8.1.93-beta 856");				// FAIL: Build number is confused with Build type number
	VersionLib::VersionData test10 ("10");							// Ok (Major is detected)
	VersionLib::VersionData test11 ("10.2");						// Ok (Major, Minor are detected)
	VersionLib::VersionData test12 ("10.2.45");						// Ok (Major, Minor, Patch are detected)
	VersionLib::VersionData test13 ("10-b");						// Ok (Major and Build type are detected)
	VersionLib::VersionData test14 ("10.2-alpha");					// Ok (Major, Minor and Build type are detected)
	VersionLib::VersionData test15 ("10.2.8 456");					// FAIL: Build number is not detected
	VersionLib::VersionData test16 ("10 487");						// FAIL: This format is not recognized
	VersionLib::VersionData test17 ("17.5 782");					// FAIL: Build type number is confused with patch
	VersionLib::VersionData test18 ("17.9.5 125");					// FAIL: Build number is not detected
	VersionLib::VersionData test19 ("14 build 77");					// FAIL: Only build number is detected
	VersionLib::VersionData test20 ("14.3 build 78");				// Ok
	VersionLib::VersionData test21 ("14.5.6 build 79");				// Ok
	VersionLib::VersionData test22 ("3.1.9-rc build 54");			// Ok

	VersionLib::VersionData* vTest = &test;

	testVersionData(appVersion, *vTest);

	return 0;
}