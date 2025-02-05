#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "VersionLib.hpp"
#include "formatTests.hpp"

int main(int argc, const char* argv[])
{
	std::vector<std::string> cli;

	bool testVersionStrFormats = false;
	bool testVersionOperators = false;
	bool testVersionExceptions = false;

	for (int i = 0; i < argc; i++)
	{
		cli.push_back(argv[i]);
		#ifdef DEBUG
		std::cout << cli[i] << std::endl;
		#endif // !DEBUG
	}

	for (int i = 1; i < cli.size(); i++)
	{
		if (cli[i] == "-test-formats")
		{
			testVersionStrFormats = true;
		}

		if (cli[i] == "-test-operators")
		{
			testVersionOperators = true;
		}

		if (cli[i] == "-test-exceptions")
		{
			testVersionExceptions = true;
		}
	}

	std::vector<VersionLib::VersionData> versions;
	std::unique_ptr<std::vector<VersionFormatTest>> versionTest;

	if (testVersionStrFormats)
	{
		versionTest.reset(new std::vector<VersionFormatTest>);
	}
	
	VersionLib::VersionData libVersion = VersionLib::internalVersionData();
	VersionLib::VersionData appVersion (1, 0, 0, 1, VersionLib::BuildType::BETA, 0);
	VersionLib::VersionData test0 (1, 0, 0, 1, VersionLib::BuildType::ALPHA, 0);
	VersionLib::VersionData test1 (1, 1, 0, 12, VersionLib::BuildType::RELEASE, 0);
	VersionLib::VersionData test2 (1, 2, 0, 20, VersionLib::BuildType::RELEASE, 0);

	// Add the libVersion appVersion and first test version:
	versions.push_back(libVersion);
	versions.push_back(appVersion);
	versions.push_back(test0);
	versions.push_back(test1);
	versions.push_back(test2);

	// Add other versions formats for tests:
	if (versionTest)
	{
		versionTest->push_back(VersionFormatTest ("1.2.1 build 700"));				// OK
		versionTest->push_back(VersionFormatTest ("1.6.1.3 build 6100"));			// FAIL: Revision is not recognized
		versionTest->push_back(VersionFormatTest ("2.5.8.15"));						// FAIL: Revision is not recognized.
		versionTest->push_back(VersionFormatTest ("17.5.12-a"));					// Ok
		versionTest->push_back(VersionFormatTest ("3.1.7-beta.6"));					// Ok
		versionTest->push_back(VersionFormatTest ("7.1.3-rc.1 752"));				// Ok
		versionTest->push_back(VersionFormatTest ("10.3.1-alpha.3 build 569"));		// Ok
		versionTest->push_back(VersionFormatTest ("8.1.93-beta 856"));				// FAIL: Build number is confused with Build type number
		versionTest->push_back(VersionFormatTest ("10"));							// Ok (Major is detected)
		versionTest->push_back(VersionFormatTest ("10.2"));							// Ok (Major, Minor are detected)
		versionTest->push_back(VersionFormatTest ("10.2.45"));						// Ok (Major, Minor, Patch are detected)
		versionTest->push_back(VersionFormatTest ("10-b"));							// Ok (Major and Build type are detected)
		versionTest->push_back(VersionFormatTest ("10.2-alpha"));					// Ok (Major, Minor and Build type are detected)
		versionTest->push_back(VersionFormatTest ("10.2.8 456"));					// FAIL: Build number is not detected
		versionTest->push_back(VersionFormatTest ("10 487"));						// FAIL: This format is not recognized
		versionTest->push_back(VersionFormatTest ("17.5 782"));						// FAIL: Build type number is confused with patch
		versionTest->push_back(VersionFormatTest ("17.9.5 125"));					// FAIL: Build number is not detected
		versionTest->push_back(VersionFormatTest ("14 build 77"));					// FAIL: Only build number is detected
		versionTest->push_back(VersionFormatTest ("14.3 build 78"));				// Ok
		versionTest->push_back(VersionFormatTest ("14.5.6 build 79"));				// Ok
		versionTest->push_back(VersionFormatTest ("3.1.9-rc build 54"));			// Ok
	}

	if (testVersionStrFormats)
	{
		std::cout << "\n\nPrinting version formats tests...\n" << std::endl;
		for (int i = 0; i < versionTest->size(); i++)
		{
			std::cout << versionTest->at(i).getTest() << std::endl << std::endl;
		}
	}

	if (testVersionOperators)
	{
		std::cout << "Testing version object operators:" << std::endl;
		std::cout << "Test 1:" << std::endl << std::endl;

		for (size_t i = 0; i < versions.size(); i++)
		{
			for (size_t j = 0; j < versions.size(); j++)
			{
				std::cout << testVersionData(versions[i], versions[j]) << std::endl;
			}
		}

		std::cout << std::endl << "Test 2:" << std::endl << std::endl;

		for (size_t i = versions.size() - 1; i > 0; i--)
		{
			for (size_t j = versions.size() - 1; j > 0; j--)
			{
				std::cout << testVersionData(versions[i], versions[j]) << std::endl;
			}
		}
	}

	if (testVersionExceptions)
	{
		#ifdef ENABLE_VERSION_LIBRARY_EXPERIMENTAL_FEATURES
		try
		{
			VersionLib::VersionData vTest(-1, -2, 0, 750, VersionLib::BuildType::RELEASE, 0, true);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		#else
		std::cout << "Experimental VersionLib features was not enabled in this compilation!" << std::endl;
		#endif // !ENABLE_VERSION_LIBRARY_EXPERIMENTAL_FEATURES
	}

	return 0;
}