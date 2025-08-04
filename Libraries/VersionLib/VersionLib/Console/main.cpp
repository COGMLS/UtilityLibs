#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "VersionLib.hpp"
#include "formatTests.hpp"

int main(int argc, const char* argv[])
{
	#ifdef TEST_LIBRARY_COMPONENTS

	std::string verStr = "1.2.3.15-beta.5";
	std::string metadata = "+abcde";
	std::string build = " build 9501";

	std::string version = verStr + metadata + build;

	std::vector<VersionLib::VersionToken> data = VersionLib::toSemVerTokens(version);

	#else
	std::vector<std::string> cli;

	bool testVersionStrFormats = false;
	bool testVersionOperators = false;
	bool testVersionExceptions = false;
	bool testVersionStrComp = false;
	bool testVersionStructComp = false;
	bool test_toSemVerTokens = false;

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

		if (cli[i] == "-test-string-comparison")
		{
			testVersionStrComp = true;
		}

		if (cli[i] == "-test-struct-comparison")
		{
			testVersionStructComp = true;
		}

		if (cli[i] == "-test2semvertokens")
		{
			test_toSemVerTokens = true;
		}
	}

	#if VERSION_LIB_VERSION_INFO_MINOR_VERSION <= 8
	std::vector<VersionLib::VersionData> versions;
	#else
	std::vector<VersionLib::SemVer> versions;
	#endif // !VERSION_LIB_VERSION_INFO_MINOR_VERSION

	std::unique_ptr<std::vector<std::string>> versionString;
	std::unique_ptr<std::vector<VersionFormatTest>> versionTest;
	
	if (testVersionStrFormats)
	{
		versionString.reset(new std::vector<std::string>);
		versionTest.reset(new std::vector<VersionFormatTest>);
	}
	
	#if VERSION_LIB_VERSION_INFO_MINOR_VERSION <= 8
	VersionLib::VersionData libVersion = VersionLib::internalVersionData();
	#else
	VersionLib::SemVer libVersion = VersionLib::internalSemVer();
	#endif // !VERSION_LIB_VERSION_INFO_MINOR_VERSION

	#if VERSION_LIB_VERSION_INFO_MINOR_VERSION < 9
	VersionLib::VersionData appVersion (1, 0, 0, 153, VersionLib::BuildType::BETA, 0);
	VersionLib::VersionData test0 (1, 0, 0, 120, VersionLib::BuildType::ALPHA, 0);
	VersionLib::VersionData test1 (1, 1, 0, 12, VersionLib::BuildType::RELEASE, 0);
	VersionLib::VersionData test2 (2, 2, 0, 20, VersionLib::BuildType::RELEASE, 0);
	#else
	VersionLib::SemVer appVersion (1, 0, 160, VersionLib::BuildType::BETA, 0);
	VersionLib::SemVer test0 (1, 0, 120, VersionLib::BuildType::ALPHA, 0);
	VersionLib::SemVer test1 (1, 1, 12, VersionLib::BuildType::RELEASE, 0);
	VersionLib::SemVer test2 (2, 2, 20, VersionLib::BuildType::RELEASE, 0);
	#endif // !VERSION_LIB_VERSION_INFO_MINOR_VERSION

	// Add the libVersion appVersion and first test version:
	versions.push_back(libVersion);
	versions.push_back(appVersion);
	versions.push_back(test0);
	versions.push_back(test1);
	versions.push_back(test2);

	// Add the strings into version strings:
	if (versionString)
	{
		versionString->push_back("1.2.1 build 700");				// OK
		versionString->push_back("1.6.1.3 build 6100");				// FAIL: Revision is not recognized; Ok on experimental fix; FAIL ON 0.9.0-alpha: Missing revision
		versionString->push_back("2.5.8.15");						// FAIL: Revision is not recognized; Ok on experimental fix. FAIL ON 0.9.0-alpha: Missing revision
		versionString->push_back("17.5.12-b");						// Ok; FAIL ON 0.9.0-alpha: Missing build type
		versionString->push_back("3.1.7-beta.6");					// Ok
		versionString->push_back("7.1.3-rc.1 752");					// Ok
		versionString->push_back("10.3.1-beta.3 build 569");		// Ok
		versionString->push_back("8.1.93-beta 856");				// FAIL: Build number is confused with Build revision; Ok on experimental fix; FAIL ON 0.9.0-alpha: Missing build type
		versionString->push_back("10");								// Ok (Major is detected)
		versionString->push_back("10.2");							// Ok (Major, Minor are detected)
		versionString->push_back("10.2.45");						// Ok (Major, Minor, Patch are detected)
		versionString->push_back("10-b");							// Ok (Major and Build type are detected); FAIL ON EXPERIMENTAL FIX: Build type is not detected. THIS BEHAVIOUR WON'T BE FIXED!
		versionString->push_back("10.2-beta");						// Ok (Major, Minor and Build type are detected); FAIL ON 0.9.0-alpha: Missing build type
		versionString->push_back("10.2.8 456");						// FAIL: Build number is not detected; Ok on experimental fix.
		versionString->push_back("10 487");							// FAIL: This format is not recognized; FAIL ON EXPERIMENTAL FIX: build number is confused with minor. THIS BEHAVIOUR WON'T BE FIXED!
		versionString->push_back("17.5 782");						// FAIL: Build revision is confused with patch; Ok on experimental fix.
		versionString->push_back("17.9.5 125");						// FAIL: Build number is not detected; Ok on experimental fix.
		versionString->push_back("14 build 77");					// FAIL: Only build number is detected; Ok on experimental fix.
		versionString->push_back("14.3 build 78");					// Ok
		versionString->push_back("14.5.6 build 79");				// Ok
		versionString->push_back("3.1.9-rc build 54");				// Ok; FAIL ON 0.9.0-alpha: Missing build type
	}

	// Add other versions formats for tests:
	if (versionTest && versionString)
	{
		/** // ---------------- Version String Format Test Results ----------------------- //
		 * 1.2.1 build 700				// OK
		 * 1.6.1.3 build 6100			// FAIL: Revision is not recognized; Ok on experimental fix; FAIL ON 0.9.0-alpha: Missing revision
		 * 2.5.8.15						// FAIL: Revision is not recognized; Ok on experimental fix; FAIL ON 0.9.0-alpha: Missing revision
		 * 17.5.12-b					// Ok; FAIL ON 0.9.0-alpha: Missing build type
		 * 3.1.7-beta.6					// Ok
		 * 7.1.3-rc.1 752				// Ok
		 * 10.3.1-beta.3 build 569		// Ok
		 * 8.1.93-beta 856				// FAIL: Build number is confused with Build revision; Ok on experimental fix; FAIL ON 0.9.0-alpha: Missing build type
		 * 10							// Ok (Major is detected)
		 * 10.2							// Ok (Major, Minor are detected)
		 * 10.2.45						// Ok (Major, Minor, Patch are detected)
		 * 10-b							// Ok (Major and Build type are detected); FAIL ON EXPERIMENTAL FIX: Build type is not detected. THIS BEHAVIOUR WON'T BE FIXED!
		 * 10.2-beta					// Ok (Major, Minor and Build type are detected); FAIL ON 0.9.0-alpha: Missing build type
		 * 10.2.8 456					// FAIL: Build number is not detected; Ok on experimental fix.
		 * 10 487						// FAIL: This format is not recognized; FAIL ON EXPERIMENTAL FIX: build number is confused with minor. THIS BEHAVIOUR WON'T BE FIXED!
		 * 17.5 782						// FAIL: Build revision is confused with patch; Ok on experimental fix.
		 * 17.9.5 125					// FAIL: Build number is not detected; Ok on experimental fix.
		 * 14 build 77					// FAIL: Only build number is detected; Ok on experimental fix.
		 * 14.3 build 78				// Ok
		 * 14.5.6 build 79				// Ok
		 * 3.1.9-rc build 54			// Ok; FAIL ON 0.9.0-alpha: Missing build type
		 * // ---------------------------------------------------------------------------- //
		*/

		// Add the string versions to test:
		for (size_t i = 0; i < versionString->size(); i++)
		{
			versionTest->push_back(VersionFormatTest(versionString->at(i)));
		}
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

	if (testVersionStructComp)
	{
		std::cout << "Testing version object operators with VersionStruct datatype:" << std::endl;
		std::cout << "Test 1:" << std::endl << std::endl;

		for (size_t i = 0; i < versions.size(); i++)
		{
			for (size_t j = 0; j < versions.size(); j++)
			{
				std::cout << testVersionData(versions[i], versions[j], true) << std::endl;
			}
		}

		std::cout << std::endl << "Test 2:" << std::endl << std::endl;

		for (size_t i = versions.size() - 1; i > 0; i--)
		{
			for (size_t j = versions.size() - 1; j > 0; j--)
			{
				std::cout << testVersionData(versions[i], versions[j], true) << std::endl;
			}
		}
	}

	if (testVersionStrComp)
	{
		std::cout << "Testing version object operators with direct Version String:" << std::endl;
		std::cout << "Test 1:" << std::endl << std::endl;

		for (size_t i = 0; i < versions.size(); i++)
		{
			for (size_t j = 0; j < versions.size(); j++)
			{
				std::cout << testVersionData(versions[i], versions[j].getVersionStr()) << std::endl;
			}
		}

		std::cout << std::endl << "Test 2:" << std::endl << std::endl;

		for (size_t i = versions.size() - 1; i > 0; i--)
		{
			for (size_t j = versions.size() - 1; j > 0; j--)
			{
				std::cout << testVersionData(versions[i], versions[j].getVersionStr()) << std::endl;
			}
		}
	}

	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_TOSEMVERTOKENS_METHOD
	if (test_toSemVerTokens)
	{
		std::vector<std::vector<VersionLib::VersionToken>> vData3;

		vData3.push_back(VersionLib::toSemVerTokens("1.2.3-alpha.15+ab1c2d-e build 9200"));
		vData3.push_back(VersionLib::toSemVerTokens("1.2.3-alpha.15+ab1c2d-e 9200"));
		vData3.push_back(VersionLib::toSemVerTokens("1.2.3-alpha.15+ab1c2de build 9200"));
		vData3.push_back(VersionLib::toSemVerTokens("1.2.3-alpha.15+ab1c2d-e 9200"));
		vData3.push_back(VersionLib::toSemVerTokens("1.2.3-alpha.15.beta+ab1c2d-e build 9200"));
		vData3.push_back(VersionLib::toSemVerTokens("1.2.3-alpha.15.beta.2+ab1c2d-e build 9200"));
		vData3.push_back(VersionLib::toSemVerTokens("1.2.3-alpha.beta.2+ab1c2d-e build 9200"));

		std::cout << "End of toSemVerTokens test" << std::endl;
	}
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_TOSEMVERTOKENS_METHOD

	if (testVersionExceptions)
	{
		#ifdef ENABLE_VERSION_LIBRARY_EXPERIMENTAL_FEATURES
		// Test with negative values:
		try
		{
			VersionLib::VersionData vTest(-1, -2, 0, VersionLib::BuildType::RELEASE, 0, 750, true);
		}
		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		catch(const VersionLib::VersionException& e)	// Works with explicit VersionException
		#else
		catch (const std::exception& e)
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		{
			std::cerr << e.what() << '\n';
		}
		// Test with nullptr
		try
		{
			VersionLib::VersionData vTest(-1, -2, 0, nullptr, 0, 750, true);
		}
		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		catch(const VersionLib::VersionException& e)	// Works with explicit VersionException
		#else
		catch (const std::exception& e)
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		{
			std::cerr << e.what() << '\n';
		}

		#else
		std::cout << "Experimental VersionLib features was not enabled in this compilation!" << std::endl;
		#endif // !ENABLE_VERSION_LIBRARY_EXPERIMENTAL_FEATURES
	}

	#ifdef ENABLE_VERSION_LIBRARY_EXPERIMENTAL_FEATURES
		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_CONSTRUCTORS
		VersionLib::VersionData ver0("1.0.5-alpha.4 build 700", true);
		VersionLib::VersionData ver1(1, 0, 5);
		VersionLib::VersionData ver2(1, 0, 5, VersionLib::BuildType::BETA);
		VersionLib::VersionData ver3(1, 2, 3, VersionLib::BuildType::BETA, 3);
		VersionLib::VersionData ver4(2, 5, 9, VersionLib::BuildType::RELEASE, 5, 800);
		VersionLib::VersionData ver5(7, 8, 1, VersionLib::BuildType::RELEASE_CANDIDATE, 3, 1000, true);
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_CONSTRUCTORS
	#endif // !ENABLE_VERSION_LIBRARY_EXPERIMENTAL_FEATURES

	#endif // !TEST_LIBRARY_COMPONENTS

	return 0;
}