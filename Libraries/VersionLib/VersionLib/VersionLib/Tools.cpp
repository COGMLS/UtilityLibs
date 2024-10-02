#include "Tools.hpp"

const char *VersionLib::tolower_Cstr(const std::string &value)
{
	std::string tmp;
	std::transform(value.begin(), value.end(), tmp.begin(), [](unsigned char c){return std::tolower(c);});
	return tmp.c_str();
}

std::string VersionLib::tolower_str(const std::string &value)
{
	std::string tmp;
	std::transform(value.begin(), value.end(), tmp.begin(), [](unsigned char c){return std::tolower(c);});
	return tmp;
}

unsigned int VersionLib::extractBuildTypeNumber(const char* buildType)
{
	buildType = VersionLib::tolower_Cstr(buildType);
	char* cValue = const_cast<char*>(buildType);
	const char token[] = ".";
	char* cStr = std::strtok(cValue, token);
	bool foundBuildType = false;
	unsigned int build_type_number = 0;
	while (token)
	{
		if (foundBuildType)
		{
			try
			{
				build_type_number = std::stoul(token);
			}
			catch(const std::exception&)
			{
				build_type_number = 0;
			}
		}
		if (std::strcmp(token, "alpha") == 0 || std::strcmp(token, "a") == 0)
		{
			foundBuildType = true;
		}

		if (std::strcmp(token, "beta") == 0 || std::strcmp(token, "b") == 0)
		{
			foundBuildType = true;
		}

		if (std::strcmp(token, "release candidate") == 0 || std::strcmp(token, "release_candidate") == 0 || std::strcmp(token, "rc") == 0)
		{
			foundBuildType = true;
		}

		if (std::strcmp(token, "release") == 0 || std::strcmp(token, "") == 0)
		{
			foundBuildType = true;
		}
	}

    return build_type_number;
}

unsigned int VersionLib::extractBuildTypeNumber(std::string buildType)
{
	buildType = VersionLib::tolower_str(buildType);
	char* cValue = const_cast<char*>(buildType.c_str());
	const char token[] = ".";
	char* cStr = std::strtok(cValue, token);
	bool foundBuildType = false;
	unsigned int build_type_number = 0;
	while (token)
	{
		if (foundBuildType)
		{
			try
			{
				build_type_number = std::stoul(token);
			}
			catch(const std::exception&)
			{
				build_type_number = 0;
			}
		}
		if (std::strcmp(token, "alpha") == 0 || std::strcmp(token, "a") == 0)
		{
			foundBuildType = true;
		}

		if (std::strcmp(token, "beta") == 0 || std::strcmp(token, "b") == 0)
		{
			foundBuildType = true;
		}

		if (std::strcmp(token, "release candidate") == 0 || std::strcmp(token, "release_candidate") == 0 || std::strcmp(token, "rc") == 0)
		{
			foundBuildType = true;
		}

		if (std::strcmp(token, "release") == 0 || std::strcmp(token, "") == 0)
		{
			foundBuildType = true;
		}
	}

    return build_type_number;
}

std::string VersionLib::buildType2Str(BuildType type, bool useShortStr)
{
	switch (type)
	{
		case BuildType::ALPHA:
		{
			if (useShortStr)
			{
				return std::string("a");
			}

			return std::string("alpha");
		}
		case BuildType::BETA:
		{
			if (useShortStr)
			{
				return std::string("b");
			}

			return std::string("beta");
		}
		case BuildType::RELEASE_CANDIDATE:
		{
			if (useShortStr)
			{
				return std::string("rc");
			}

			return std::string("release candidate");
		}
		default:
		{
			return std::string();
		}
	}
}

VersionLib::BuildType VersionLib::str2BuildType(std::string value)
{
	value = VersionLib::tolower_str(value);

	if (value == "alpha" || value == "a")
	{
		return BuildType::ALPHA;
	}

	if (value == "beta" || value == "b")
	{
		return BuildType::BETA;
	}

	if (value == "release candidate" || value == "release_candidate" || value == "rc")
	{
		return BuildType::RELEASE_CANDIDATE;
	}

	if (value == "" || value.empty() || value == "release")
	{
		return BuildType::RELEASE;
	}
	
	return BuildType::RELEASE;
}

[[deprecated("This function is not recommended to use. Use toVersionStrut2 with more reliable semantic versioning conversion.")]]
VersionLib::VersionStruct VersionLib::toVersionStruct(std::string version)
{
	VersionLib::VersionStruct v;

	/** tokens - positions used:
	 * 0: Major version
	 * 1: Minor version
	 * 2; Patch version
	 * 3: Build type
	 * 4: Build Type Number
	 * 5: Build Number
	 */
	std::vector<std::string> tokens;

	version = VersionLib::tolower_str(version);

	const char delimiters[] = ".- ";
	char* cVersion = const_cast<char*>(version.c_str());
	char* token = std::strtok(cVersion, delimiters);

	size_t rcPos = version.find("release candidate");

	if (rcPos > 0 && rcPos < version.size())
	{
		std::string tmp = version.replace(rcPos, std::strlen("release candidate"), "release_candidate");
		version = tmp;
	}

	while (token)
	{
		tokens.push_back(token);
		token = std::strtok(nullptr, delimiters);
	}

	bool foundMajorVer = false;
	bool foundMinorVer = false;
	bool foundPatchVer = false;
	bool foundTypeVer = false;
	bool foundTypeNum = false;
	bool foundBuild = false;
	bool foundBuildName = false;

	unsigned int major = 0;
	unsigned int minor = 0;
	unsigned int patch = 0;
	std::string type = "";
	VersionLib::BuildType typeEnum;
	unsigned int type_num = 0;
	unsigned long long build = 0;

	for (size_t i = 0; i < tokens.size(); i++)
	{
		if (tokens[i].starts_with(' '))
		{
			tokens[i] = tokens[i].erase(0, 1);
		}

		if (tokens[i].ends_with(' '))
		{
			tokens[i] = tokens[i].erase(tokens[i].size() - 1, 1);
		}

		if (!foundBuild && (foundBuildName || foundTypeNum))
		{
			try
			{
				build = std::stoull(tokens[i]);
				foundBuild = true;
			}
			catch(const std::exception&)
			{
				
			}
		}

		if (!foundBuildName && tokens[i] == "build")
		{
			foundBuildName = true;
		}

		if ((foundPatchVer || foundTypeVer) && !foundTypeNum && (!foundBuild || !foundBuildName))
		{
			try
			{
				type_num = std::stoull(tokens[i]);
				foundTypeNum = true;
			}
			catch(const std::exception&)
			{
				
			}
		}

		if (!foundTypeVer)
		{
			if (
					tokens[i] == "alpha" || tokens[i] == "a" || 
					tokens[i] == "beta" || tokens[i] == "b" || 
					tokens[i] == "release_candidate" || tokens[i] == "rc"
				)
			{
				typeEnum = VersionLib::str2BuildType(tokens[i]);
				type = tokens[i];
				foundTypeVer = true;
			}
		}

		if (foundMajorVer && foundMinorVer && !foundPatchVer)
		{
			try
			{
				patch = std::stoul(tokens[i].c_str());
				foundPatchVer = true;
			}
			catch(const std::exception&)
			{
				
			}
		}

		if (foundMajorVer && !foundMinorVer)
		{
			try
			{
				minor = std::stoul(tokens[i].c_str());
				foundMinorVer = true;
			}
			catch(const std::exception&)
			{
				
			}
		}

		if (!foundMajorVer)
		{
			try
			{
				major = std::stoul(tokens[i].c_str());
				foundMajorVer = true;
			}
			catch(const std::exception&)
			{

			}
		}
	}

	v.major = major;
	v.minor = minor;
	v.patch = patch;
	v.build_type = typeEnum;
	v.build_type_number = type_num;
	v.build = build;

	return v;
}

VersionLib::VersionStruct VersionLib::toVersionStruct2(std::string version)
{
	/// TODO: Add the Microsoft's iostream guard for Debug tests
	#if defined(DEBUG) && (defined(_GLIBCXX_IOSTREAM)/* || defined()*/)
	std::cout << "Version to convert: " << version << std::endl;
	#endif // !Check for IOSTREAM and DEBUG

	VersionLib::VersionStruct v;

	// Disabled the method: The current method contains a bug that miss the lowercase characters
	//version = VersionLib::tolower_str(version);

	size_t verStrSize = version.size();
	size_t buildTypePos = version.find("release candidate");

	if (buildTypePos > 0 && buildTypePos < verStrSize)
	{
		version.replace(buildTypePos, std::strlen("release_candidate"), "release_candidate");
	}

	//
	// Variable controls:
	//

	unsigned int major = 0;
	unsigned int minor = 0;
	unsigned int patch = 0;
	#ifdef DEBUG
	short build_type = 0;
	#endif // !DEBUG
	std::string build_type_str;
	unsigned int build_type_number = 0;
	unsigned long long build = 0;

	bool foundMajorVer = false;				// Found major version number
	bool foundMinorVer = false;				// Found minor version number
	bool foundPatchVer = false;				// Found patch version number
	bool foundBuildTypeVer = false;			// Found build type version (alpha, beta, etc)
	bool foundBuildTypeNum = false;			// Found the build type number
	bool foundBuildStr = false;				// Found the build word
	bool foundBuild = false;				// Found the build number

	short lastFieldProcessed = -1;			// 0.1.2-3.4 "5" 6
	//short lastTokenFound = 0;				// 0: None 1: Dot 2: dash 3: space 4: Index limit

	bool foundValidChar = false;			// Identified valid characters
	bool accValHasNumbers = false;			// Accumulator Value has number
	bool useAccVal = false;					// Determinate to try to convert
	char t = '\0';
	std::string tmp;						// Temporary variable accumulator

	/** Version string analysis:
	 * --------------------------------------------
	 * First, try to find the Major version. The dot
	 * is the mark that defines if is the end of the
	 * version field.
	 * 
	 * For each field X.Y.Z uses the same behavior for
	 * Major version. If the char '-' was found, try
	 * to detect if has the information about the
	 * build type (alpha, beta, rc). If detected the
	 * build type, try to find the build type number,
	 * used to identify alpha.2 beta.3, etc.
	 * 
	 * 
	*/

	for (size_t i = 0; i < verStrSize; i++)
	{
		// Get the current char:
		t = version[i];

		// Jump any space char:
		if (t != ' ' && !foundValidChar)
		{
			foundValidChar = true;
		}

		if (foundValidChar)
		{
			// Cumulate the number to try to convert:
			if (t >= '0' && t <= '9')
			{
				tmp += t;
				accValHasNumbers = true;
			}

			// Cumulate the chars, to try to detect "build", "alpha", "beta", "release_candidate", "a", "b" or "rc" words:
			if (t >= 'a' && t <= 'z' || t >= 'A' && t <= 'Z' || t == '_')
			{
				tmp += t;
			}

			// If detect the dot or the dash or the space (used for words separation). In case is the last char, make sure it will be analyzed:
			if (t == '.' || t == ' ' || t == '-' || i + 1 == verStrSize)
			{
				// Check if the build number is available, using the accValHasNumber and if the word "build" does not founded and found the space separator:
				if (accValHasNumbers && !foundBuildStr && t == ' ' && !foundMajorVer)
				{
					// There are two possible checks for this situation: the numeric accumulated value is the build number or not
					// To make sure the accumulated number is the build number, the build type version and it's number most appear or both not. Otherwise, it will fall in a false condition, confused by the build type number as the build number.
					if ((!foundBuildTypeVer && !foundBuildTypeNum) || (foundBuildTypeVer && foundBuildTypeNum))
					{
						lastFieldProcessed = 5;			// Force to go direct to convert build number
					}

					// To avoid the possibility to fall in the possible false condition, the next characters after the space separator, should be an numeric value to be a build number
					if (foundBuildTypeVer && !foundBuildTypeNum && lastFieldProcessed == 3)
					{
						if (i + 1 < verStrSize)
						{
							if (!(version[i + 1] >= '0' && version[i + 1] <= '9') && !(version[i + 1] != 'b' || version[i + 1] != 'B'))
							{
								lastFieldProcessed = 5; // Force to go direct to convert build number
							}
						}
					}
				}

				//if (
				//		(foundBuildTypeVer && !foundBuildTypeNum && accValHasNumbers && !foundBuildStr && t == ' ') || 
				//		(!foundBuildTypeVer && !foundBuildTypeNum && accValHasNumbers && !foundBuildStr && t == ' ') || 
				//		(foundBuildTypeVer && foundBuildTypeNum && accValHasNumbers && !foundBuildStr && t == ' ')
				//	)
				//{
				//	lastFieldProcessed = 5;
				//}

				// Set to use the accumulated value into the conversion instructions:
				useAccVal = true;
			}
		}

		// Try to detect the value:
		if (useAccVal)
		{
			if (accValHasNumbers)
			{
				// Clean the accValHasNumbers status:
				accValHasNumbers = false;

				// Try to detect the build version:
				//(foundMajorVer && foundMinorVer && foundPatchVer && ((foundBuildTypeVer && !foundBuildTypeNum && !foundBuild) || (foundBuildTypeVer && foundBuildTypeNum && !foundBuild) || (!foundBuildTypeVer && !foundBuildTypeNum && !foundBuild)))
				if ((!foundBuildStr && lastFieldProcessed == 5) || (!foundBuildStr && foundBuildTypeNum && lastFieldProcessed == 4) || (foundBuildStr && lastFieldProcessed == 5))
				{
					try
					{
						build = std::stoul(tmp);
						foundBuild = true;
						lastFieldProcessed = 6;
					}
					catch(const std::exception&)
					{

					}
				}
				
				// Try to detect the build type number version:
				if (foundBuildTypeVer && !foundBuildTypeNum && (lastFieldProcessed == 3))
				{
					try
					{
						build_type_number = std::stoul(tmp);
						foundBuildTypeNum = true;
						lastFieldProcessed = 4;
					}
					catch(const std::exception&)
					{

					}
				}

				// Try to detect the patch version:
				if (foundMajorVer && foundMinorVer && !foundPatchVer && !foundBuildTypeNum && !foundBuild)
				{
					try
					{
						patch = std::stoul(tmp);
						foundPatchVer = true;
						lastFieldProcessed = 2;
					}
					catch(const std::exception&)
					{

					}
				}

				// Try to detect the minor version:
				if (foundMajorVer && !foundMinorVer && !foundPatchVer && !foundBuildTypeNum && !foundBuild)
				{
					try
					{
						minor = std::stoul(tmp);
						foundMinorVer = true;
						lastFieldProcessed = 1;
					}
					catch(const std::exception&)
					{

					}
				}

				// Try to detect the major version:
				if (!foundMajorVer && !foundMinorVer && !foundPatchVer && !foundBuildTypeNum && !foundBuild)
				{
					try
					{
						major = std::stoul(tmp);
						foundMajorVer = true;
						lastFieldProcessed = 0;
					}
					catch(const std::exception&)
					{

					}
				}
			}
			else
			{
				//
				// Try to detect a valid word:
				//

				if (tmp == "build")
				{
					foundBuildStr = true;
					lastFieldProcessed = 5;
				}

				if (tmp == "alpha" || tmp == "a")
				{
					#ifdef DEBUG
					build_type = 1;
					#endif // !DEBUG
					build_type_str = tmp;
					foundBuildTypeVer = true;
					lastFieldProcessed = 3;
				}

				if (tmp == "beta" || tmp == "b")
				{
					#ifdef DEBUG
					build_type = 2;
					#endif // !DEBUG
					build_type_str = tmp;
					foundBuildTypeVer = true;
					lastFieldProcessed = 3;
				}

				if (tmp == "release_candidate" || tmp == "rc")
				{
					#ifdef DEBUG
					build_type = 3;
					#endif // !DEBUG
					build_type_str = tmp;
					foundBuildTypeVer = true;
					lastFieldProcessed = 3;
				}

				if (tmp == "release" || tmp == "r")
				{
					#ifdef DEBUG
					build_type = 4;
					#endif // !DEBUG
					build_type_str = tmp;
					foundBuildTypeVer = true;
					lastFieldProcessed = 3;
				}
			}

			// Clear the useAccVal status for the next value analysis:
			useAccVal = false;

			// Clear the accumulated value to reuse the variable:
			tmp.clear();
		}
	}

	#if defined(DEBUG) && (defined(_GLIBCXX_IOSTREAM)/* || defined()*/)
	std::cout << "Converted Version: " << major << "." << minor << "." << patch << "-" << build_type_str << "(" << build_type << ")." << build_type_number << " build " << build << std::endl << std::endl;
	#endif // !Check for IOSTREAM and DEBUG

	v.major = major;
	v.minor = minor;
	v.patch = patch;
	v.build_type = VersionLib::str2BuildType(build_type_str);
	v.build_type_number = build_type_number;
	v.build = build;

	return v;
}