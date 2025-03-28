#include "Tools.hpp"

const char *VersionLib::tolower_Cstr(const std::string &value)
{
	size_t strlen = value.size();
	char* tmp = new char[strlen];
	char c = '\0';
	for (size_t i = 0; i < strlen; i++)
	{
		c = value[i];

		if (std::isupper(c))
		{
			tmp[i] = std::tolower(c);
		}
		else
		{
			tmp[i] = c;
		}
	}
	return const_cast<const char*>(tmp);
}

std::string VersionLib::tolower_str(const std::string &value)
{
	std::string tmp;
	char c = '\0';
	for (size_t i = 0; i < value.size(); i++)
	{
		c = value[i];

		if (std::isupper(c))
		{
			tmp += std::tolower(c);
		}
		else
		{
			tmp += c;
		}
	}
	return tmp;
}

unsigned int VersionLib::extractBuildTypeNumber(const char* buildType)
{
	buildType = VersionLib::tolower_Cstr(buildType);
	char* cValue = const_cast<char*>(buildType);
	const char token[] = ".";
	char* cStr = std::strtok(cValue, token);
	bool foundBuildType = false;
	unsigned int build_revision = 0;
	while (token)
	{
		if (foundBuildType)
		{
			try
			{
				build_revision = std::stoul(token);
			}
			catch(const std::exception&)
			{
				build_revision = 0;
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

    return build_revision;
}

unsigned int VersionLib::extractBuildTypeNumber(std::string buildType)
{
	buildType = VersionLib::tolower_str(buildType);
	char* cValue = const_cast<char*>(buildType.c_str());
	const char token[] = ".";
	char* cStr = std::strtok(cValue, token);
	bool foundBuildType = false;
	unsigned int build_revision = 0;
	while (token)
	{
		if (foundBuildType)
		{
			try
			{
				build_revision = std::stoul(token);
			}
			catch(const std::exception&)
			{
				build_revision = 0;
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

    return build_revision;
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
		case BuildType::RELEASE:
		{
			if (useShortStr)
			{
				return std::string("r");
			}

			return std::string("release");
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

	if (value.starts_with('"') || value.starts_with('\''))
	{
		value = value.erase(0, 1);
	}

	if (value.ends_with('"') || value.ends_with('\''))
	{
		value = value.erase(value.size() - 1, 1);
	}

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

#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
[[deprecated("This function is not recommended to use. Use toVersionStrut2 with more reliable semantic versioning conversion.")]]
VersionLib::VersionStruct VersionLib::toVersionStruct(std::string version)
{
	VersionLib::VersionStruct v = initVersionStruct();

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
	VersionLib::BuildType typeEnum = VersionLib::BuildType::RELEASE;
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
	v.build_revision = type_num;
	v.build = build;

	return v;
}
#endif // VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_FIX_VERSIONSTR_2_VERSIONSTRUCT
VersionLib::VersionStruct VersionLib::toVersionStruct2(std::string version)
{
	#if defined(DEBUG) && (defined(_GLIBCXX_IOSTREAM) || defined(_IOSTREAM_))
	std::cout << "Version to convert: " << version << std::endl;
	#endif // !Check for IOSTREAM and DEBUG

	VersionLib::VersionStruct v = initVersionStruct();

	// Make sure the version string is complete in lowercase:
	version = VersionLib::tolower_str(version);

	size_t verStrSize = version.size();
	size_t buildTypePos = version.find("release candidate");

	if (buildTypePos > 0 && buildTypePos < verStrSize)
	{
		version.replace(buildTypePos, std::strlen("release_candidate"), "release_candidate");
	}

	//
	// Variable controls:
	//

	struct token_struct
	{
		short type 				= -2;		// Type of value 0: Major, 1: minor, 2: patch, 3: type, 4: number, 5: "build world", 6: build number
		std::string str 		= "";		// String token
		unsigned int ul 		= 0;		// Value for major, minor, patch, revision
		unsigned long long ull 	= 0;		// Value for build number
	};

	std::vector<token_struct> tokens;		// Version tokens

	bool foundMajorVer = false;				// Found major version number
	bool foundMinorVer = false;				// Found minor version number
	bool foundPatchVer = false;				// Found patch version number
	bool foundBuildTypeVer = false;			// Found build type version (alpha, beta, etc)
	bool foundBuildTypeRev = false;			// Found the build type number
	bool foundBuildStr = false;				// Found the build word
	bool foundBuild = false;				// Found the build number

	short lastFieldProcessed = -1;			// 0.1.2-3.4 "5" 6

	bool foundValidChar = false;			// Identified valid characters
	bool accValHasNumbers = false;			// Accumulator Value has number
	bool useAccVal = false;					// Determinate to try to convert
	char t = '\0';							// Current char in analysis
	char l = '\0';							// Last terminal char analyzed to detect the component
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
		// Update the last char used to mark:
		if (t == '.' || t == ' ' || t == '-')
		{
			l = t;
		}

		// Get the current char:
		t = version[i];

		// Jump any space char:
		if (t != ' ' && !foundValidChar)
		{
			foundValidChar = true;
		}

		if (foundValidChar)
		{
			// Accumulate the number to try to convert:
			if (t >= '0' && t <= '9')
			{
				tmp += t;
				accValHasNumbers = true;
			}

			// Accumulate the chars, to try to detect "build", "alpha", "beta", "release_candidate", "a", "b" or "rc" words:
			if (t >= 'a' && t <= 'z' || t >= 'A' && t <= 'Z' || t == '_')
			{
				tmp += t;
			}

			// If detect the dot or the dash or the space (used for words separation). In case is the last char, make sure it will be analyzed:
			if (t == '.' || t == ' ' || t == '-' || i + 1 == verStrSize)
			{
				// Set to use the accumulated value into the conversion instructions:
				useAccVal = true;
			}
		}

		// Try to detect the value:
		if (useAccVal)
		{
			// Create the token structure:
			token_struct token;

			// If the string contain numbers, try to detect the component:
			if (accValHasNumbers)
			{
				// Clean the accValHasNumbers status:
				accValHasNumbers = false;

				//
				// Try to set the value to unsigned long long. This only used to build number:
				//

				try
				{
					token.ull = std::stoull(tmp);
				}
				catch (const std::exception& e)
				{
					// Do not generate error output
				}

				//
				// Try yo set the numeric value to unsigned long. This field is used by all other version components that are not build:
				//

				try
				{
					token.ul = std::stoul(tmp);
				}
				catch (const std::exception& e)
				{
					// Do not generate error output
				}
			}
			else
			{
				//
				// Try to detect a valid word:
				//

				// Test for "build" world:
				if (tmp == "build")
				{
					foundBuildStr = true;
					lastFieldProcessed = 5;
					goto JumpComponentDetection;
				}

				// Test for "alpha" build type:
				if (tmp == "alpha" || tmp == "a")
				{
					//foundBuildTypeVer = true;
					lastFieldProcessed = 3;
					goto JumpComponentDetection;
				}

				// Test for "beta" build type:
				if (tmp == "beta" || tmp == "b")
				{
					//foundBuildTypeVer = true;
					lastFieldProcessed = 3;
					goto JumpComponentDetection;
				}

				// Test for "release candidate" build type:
				if (tmp == "release_candidate" || tmp == "rc")
				{
					//foundBuildTypeVer = true;
					lastFieldProcessed = 3;
					goto JumpComponentDetection;
				}

				// Test for "release" build type:
				if (tmp == "release" || tmp == "r")
				{
					//foundBuildTypeVer = true;
					lastFieldProcessed = 3;
					goto JumpComponentDetection;
				}
			}

			//
			// Jump to component detection: This reduce the test of unnecessary conditional statements.
			//

			JumpComponentDetection:

			//
			// Try to detect the version components:
			//

			// Build number:
			if (foundMajorVer && (foundBuildStr || l == ' ') && !foundBuild)
			{
				bool setBuild = false;

				// If only minor was found:
				if (foundMinorVer && !foundPatchVer)
				{
					// If type was found:
					if (foundBuildTypeVer)
					{
						if (!foundBuildTypeRev && foundBuildStr)				// Case: found Major, minor, type and revision components
						{
							setBuild = true;
						}
						if (!foundBuildTypeRev && !foundBuildStr && l == ' ')	// Case: found major, minor, type. No patch, revision and "build" world was found
						{
							setBuild = true;
						}
					}
					else
					{
						if (!foundBuildTypeRev && foundBuildStr)				// Case: found major, minor, patch. No type, revision, but "build" was found
						{
							setBuild = true;
						}
						if (!foundBuildTypeRev && !foundBuildStr && l == ' ')	// Case: found major, minor, patch. No type, revision and "build" world was found
						{
							setBuild = true;
						}
					}
				}

				// If minor and patch was found:
				if (foundMinorVer && foundPatchVer)
				{
					// If type was found:
					if (foundBuildTypeVer)
					{
						if (foundBuildTypeRev && foundBuildStr)					// Case: found all components in version string
						{
							setBuild = true;
						}
						if (foundBuildTypeRev && !foundBuildStr && l == ' ')	// Case: found all components but no "build" world was found
						{
							setBuild = true;
						}
						if (!foundBuildTypeRev && foundBuildStr)				// Case: found Major, minor, patch, type and revision components
						{
							setBuild = true;
						}
						if (!foundBuildTypeRev && !foundBuildStr && l == ' ')	// Case: found major, minor, patch, type. No revision and "build" world was found
						{
							setBuild = true;
						}
					}
					else
					{
						if (!foundBuildTypeRev && foundBuildStr)				// Case: found major, minor, patch. No type, revision, but "build" was found
						{
							setBuild = true;
						}
						if (!foundBuildTypeRev && !foundBuildStr && l == ' ')	// Case: found major, minor, patch. No type, revision and "build" world was found
						{
							setBuild = true;
						}
					}
				}

				// Test for build number after found the "build" world:
				if (foundBuildStr || lastFieldProcessed == 5)
				{
					setBuild = true;
				}

				// Set the build number:
				if (setBuild)
				{
					foundBuild = true;
					lastFieldProcessed = 6;
					goto JumpAccValAnalysis;
				}
			}

			// Revision version:
			if (foundMajorVer && foundMinorVer && foundPatchVer && !foundBuildTypeRev && !foundBuildStr && !foundBuild)
			{
				// Detect the revision if no build type was detected yet but a revision number was:
				if (!foundBuildTypeVer && lastFieldProcessed == 2)
				{
					foundBuildTypeRev = true;
					lastFieldProcessed = 4;
					goto JumpAccValAnalysis;
				}

				// Detect the revision when testing for Semantic Versioning:
				if (foundBuildTypeVer)
				{
					foundBuildTypeRev = true;
					lastFieldProcessed = 4;
					goto JumpAccValAnalysis;
				}
			}

			// Build type version:
			if (foundMajorVer && lastFieldProcessed == 3 && !foundBuildTypeRev && !foundBuildStr && !foundBuild)
			{
				// Found minor and type:
				if (foundMinorVer && !foundPatchVer)
				{
					foundBuildTypeVer = true;
					goto JumpAccValAnalysis;
				}

				// Found minor, patch and type:
				if (foundMinorVer && foundPatchVer)
				{
					foundBuildTypeVer = true;
					goto JumpAccValAnalysis;
				}
			}

			// Test for Minor or Patch:
			if (foundMajorVer && !foundBuildTypeVer && !foundBuildTypeRev && !foundBuildStr && !foundBuild)
			{
				// Patch version:
				if (foundMinorVer && !foundPatchVer)
				{
					foundPatchVer = true;
					lastFieldProcessed = 2;
					goto JumpAccValAnalysis;
				}

				// Minor version:
				if (!foundMinorVer && !foundPatchVer)
				{
					foundMinorVer = true;
					lastFieldProcessed = 1;
					goto JumpAccValAnalysis;
				}
			}

			// Major version. It must be the first component:
			if (!foundMajorVer && !foundMinorVer && !foundPatchVer && !foundBuildTypeVer && !foundBuildTypeRev && !foundBuildStr && !foundBuild)
			{
				foundMajorVer = true;
				lastFieldProcessed = 0;
				goto JumpAccValAnalysis;
			}

			//
			// Jump point:
			//

			JumpAccValAnalysis:

			// Clear the useAccVal status for the next value analysis:
			useAccVal = false;

			// Include the component as a token in the vector:
			token.type = lastFieldProcessed;
			token.str = tmp;
			tokens.push_back(token);

			// Clear the accumulated value to reuse the variable:
			tmp.clear();
		}
	}

	//
	// Set the token in to variables:
	//

	// Set the debug variables for tests:
	#ifdef DEBUG
	unsigned int major = 0;
	unsigned int minor = 0;
	unsigned int patch = 0;
	short build_type = 0;
	std::string build_type_str;
	unsigned int build_revision = 0;
	unsigned long long build = 0;
	#endif // !DEBUG

	for (size_t i = 0; i < tokens.size(); i++)
	{
		// Set major:
		if (tokens[i].type == 0)
		{
			v.major = tokens[i].ul;
			#if DEBUG
			major = tokens[i].ul;
			#endif // !DEBUG
		}

		// Set minor:
		if (tokens[i].type == 1)
		{
			v.minor = tokens[i].ul;
			#if DEBUG
			minor = tokens[i].ul;
			#endif // !DEBUG
		}

		// Set patch:
		if (tokens[i].type == 2)
		{
			v.patch = tokens[i].ul;
			#if DEBUG
			patch = tokens[i].ul;
			#endif // !DEBUG
		}

		// Set build type:
		if (tokens[i].type == 3)
		{
			#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
				#error "No compatible implementation of EXPERIMENTAL SUPPORT TO COMBINED BUILD TYPE to toVersionStruct2 function!"
				#else
				VersionLib::setVersionBuildTypeC(v.build_type, VersionLib::str2BuildType(tokens[i].str));
				#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
			#else
			v.build_type = VersionLib::str2BuildType(tokens[i].str);
			#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
			#if DEBUG
			build_type_str = tokens[i].str;
			build_type = VersionLib::str2BuildType(tokens[i].str);
			#endif // !DEBUG
		}

		// Set revision:
		if (tokens[i].type == 4)
		{
			v.build_revision = tokens[i].ul;
			#if DEBUG
			build_revision = tokens[i].ul;
			#endif // !DEBUG
		}

		// Set build:
		if (tokens[i].type == 6)
		{
			v.build = tokens[i].ull;
			#if DEBUG
			build = tokens[i].ull;
			#endif // !DEBUG
		}
	}

	#if defined(DEBUG) && (defined(_GLIBCXX_IOSTREAM) || defined(_IOSTREAM_))
	std::cout << "Converted Version: " << major << "." << minor << "." << patch << "-" << build_type_str << "(" << build_type << ")." << build_revision << " build " << build << std::endl << std::endl;
	#endif // !Check for IOSTREAM and DEBUG

	return v;
}
#else
VersionLib::VersionStruct VersionLib::toVersionStruct2(std::string version)
{
	#if defined(DEBUG) && (defined(_GLIBCXX_IOSTREAM) || defined(_IOSTREAM_))
	std::cout << "Version to convert: " << version << std::endl;
	#endif // !Check for IOSTREAM and DEBUG

	VersionLib::VersionStruct v = initVersionStruct();

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
	unsigned int build_revision = 0;
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
				if ((foundBuildTypeVer && !foundBuildTypeNum && (lastFieldProcessed == 3)) || (foundMajorVer && foundMinorVer && foundPatchVer && !foundBuildTypeNum && !foundBuildTypeVer && (lastFieldProcessed == 2 && std::isalpha(tmp[0]) != 0)))
				{
					try
					{
						build_revision = std::stoul(tmp);
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

	#if defined(DEBUG) && (defined(_GLIBCXX_IOSTREAM) || defined(_IOSTREAM_))
	std::cout << "Converted Version: " << major << "." << minor << "." << patch << "-" << build_type_str << "(" << build_type << ")." << build_revision << " build " << build << std::endl << std::endl;
	#endif // !Check for IOSTREAM and DEBUG

	v.major = major;
	v.minor = minor;
	v.patch = patch;
	v.build_type = VersionLib::str2BuildType(build_type_str);
	v.build_revision = build_revision;
	v.build = build;

	return v;
}
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_FIX_VERSIONSTR_2_VERSIONSTRUCT