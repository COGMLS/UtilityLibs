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

std::string VersionLib::buildType2Str(BuildType type, bool useShortStr, bool showReleaseType)
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
			if (showReleaseType)
			{
				if (useShortStr)
				{
					return std::string("r");
				}
	
				return std::string("release");
			}

			return std::string();
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

VersionLib::VersionStruct VersionLib::toVersionStruct2(std::string version)
{
	#if defined(DEBUG) && (defined(_GLIBCXX_IOSTREAM) || defined(_IOSTREAM_))
	std::cout << "Version to convert: " << version << std::endl;
	#endif // !Check for IOSTREAM and DEBUG

	VersionLib::VersionStruct v = VersionLib::initVersionStruct();

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
		short type 				= -2;		// Type of value 0: Major, 1: minor, 2: patch, 3: type, 4: number, 5: "build word", 6: build number
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

				// Test for "build" word:
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
						if (!foundBuildTypeRev && !foundBuildStr && l == ' ')	// Case: found major, minor, type. No patch, revision and "build" word was found
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
						if (!foundBuildTypeRev && !foundBuildStr && l == ' ')	// Case: found major, minor, patch. No type, revision and "build" word was found
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
						if (foundBuildTypeRev && !foundBuildStr && l == ' ')	// Case: found all components but no "build" word was found
						{
							setBuild = true;
						}
						if (!foundBuildTypeRev && foundBuildStr)				// Case: found Major, minor, patch, type and revision components
						{
							setBuild = true;
						}
						if (!foundBuildTypeRev && !foundBuildStr && l == ' ')	// Case: found major, minor, patch, type. No revision and "build" word was found
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
						if (!foundBuildTypeRev && !foundBuildStr && l == ' ')	// Case: found major, minor, patch. No type, revision and "build" word was found
						{
							setBuild = true;
						}
					}
				}

				// Test for build number after found the "build" word:
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

	#if defined(VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT) && defined(VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE)
	bool processedType = false;
	bool processedRevision = false;
	std::vector<VersionLib::VersionReleaseDataC> build_types;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT && !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE

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
		#if defined(VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT) && defined(VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE)
		if (tokens[i].type == 3 && !processedType)
		#else
		if (tokens[i].type == 3)
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT && !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
		{
			#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
				// Convert the build types in string format to BuildType enumerator:
				
				if (!processedRevision)
				{
					build_types.push_back(VersionLib::initVersionReleaseDataC());
				}

				build_types[0].release = VersionLib::str2BuildType(tokens[i].str);
				build_types[0].releaseIdentified = true;
				processedType = true;

				//std::vector<VersionLib::VersionReleaseDataC> buildTypes = VersionLib::findAndGetBuildTypes(tokens[i].str);
				//VersionLib::setVersionBuildTypeC(v.build_type, buildTypes.data(), static_cast<unsigned short>(buildTypes.size()));
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

		#if defined(VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT) && defined(VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE)
		if (tokens[i].type == 4 && !processedRevision)
		{
			if (!processedType)
			{
				build_types.push_back(VersionLib::initVersionReleaseDataC());
			}

			build_types[0].revision = tokens[i].ul;
			build_types[0].releaseIdentified = true;
			processedRevision = true;
		}
		#else
		// Set revision:
		if (tokens[i].type == 4)
		{
			v.build_revision = tokens[i].ul;
			#if DEBUG
			build_revision = tokens[i].ul;
			#endif // !DEBUG
		}
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT && !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE

		// Set build:
		if (tokens[i].type == 6)
		{
			v.build = tokens[i].ull;
			#if DEBUG
			build = tokens[i].ull;
			#endif // !DEBUG
		}
	}

	#if defined(VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT) && defined(VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE)
	if (processedType || processedRevision)
	{
		VersionLib::setVersionBuildTypeC(v.build_type, build_types.data(), static_cast<unsigned short>(build_types.size()));
	}
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT && !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE

	#if defined(DEBUG) && (defined(_GLIBCXX_IOSTREAM) || defined(_IOSTREAM_))
	std::cout << "Converted Version: " << major << "." << minor << "." << patch << "-" << build_type_str << "(" << build_type << ")." << build_revision << " build " << build << std::endl << std::endl;
	#endif // !Check for IOSTREAM and DEBUG

	return v;
}

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_TOVERSIONSTRCUT3_METHOD
VersionLib::VersionStruct VersionLib::toVersionStruct3(std::string version)
{
	#if defined(DEBUG) && (defined(_GLIBCXX_IOSTREAM) || defined(_IOSTREAM_))
	std::cout << "Version to convert: " << version << std::endl;
	#endif // !Check for IOSTREAM and DEBUG

	VersionLib::VersionStruct v = initVersionStruct();

	// Make sure the version string is complete in lowercase:
	version = VersionLib::tolower_str(version);

	size_t verStrSize = version.size();

	//
	// Variable controls:
	//

	struct token_struct
	{
		short type 				= -2;		// Type of value 0: Major, 1: minor, 2: patch, 3: type, 4: number, 5: "build word", 6: build number
		std::string str 		= "";		// String token
		union 								// Union to reduce memory usage
		{
			unsigned int ul;				// Value for major, minor, patch, revision
			unsigned long long ull;			// Value for build number
		} numVal;
	};

	std::vector<token_struct> tokens;		// Version tokens
	std::vector<VersionLib::VersionReleaseDataC> buildTypes;	// Build types (include combined ones)

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
			if (t == '.' || t == ' ' || t == '-' || t == '+' || i + 1 == verStrSize)
			{
				// Set to use the accumulated value into the conversion instructions:
				useAccVal = true;
				
				// Check if is necessary verify for combined build types:
				if (i + 1 < verStrSize && !foundBuildTypeVer)
				{
					char tNext = version[i + 1];
					if ((t == '.' || t == ' ') && (l >= 'a' && l <= 'z' || l >= 'A' && l <= 'Z') && (tNext >= 'a' && tNext <= 'z' || tNext >= 'A' && tNext <= 'Z'))
					{
						useAccVal = false;	// If is under condition to possible combined build types, keep accumulating the temporary string
					}
				}
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
					token.numVal.ull = std::stoull(tmp);
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
					token.numVal.ul = std::stoul(tmp);
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

				// Test for "build" word:
				if (tmp == "build")
				{
					foundBuildStr = true;
					lastFieldProcessed = 5;
					goto JumpComponentDetection;
				}

				#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
				// Test to identify any valid build type:
				buildTypes = findAndGetBuildTypes(tmp);

				if (!buildTypes.empty())
				{
					//foundBuildTypeVer = true;
					lastFieldProcessed = 3;
					goto JumpComponentDetection;
				}
				#else
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
				#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
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
						if (!foundBuildTypeRev && !foundBuildStr && l == ' ')	// Case: found major, minor, type. No patch, revision and "build" word was found
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
						if (!foundBuildTypeRev && !foundBuildStr && l == ' ')	// Case: found major, minor, patch. No type, revision and "build" word was found
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
						if (foundBuildTypeRev && !foundBuildStr && l == ' ')	// Case: found all components but no "build" word was found
						{
							setBuild = true;
						}
						if (!foundBuildTypeRev && foundBuildStr)				// Case: found Major, minor, patch, type and revision components
						{
							setBuild = true;
						}
						if (!foundBuildTypeRev && !foundBuildStr && l == ' ')	// Case: found major, minor, patch, type. No revision and "build" word was found
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
						if (!foundBuildTypeRev && !foundBuildStr && l == ' ')	// Case: found major, minor, patch. No type, revision and "build" word was found
						{
							setBuild = true;
						}
					}
				}

				// Test for build number after found the "build" word:
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
			v.major = tokens[i].numVal.ul;
			#if DEBUG
			major = tokens[i].numVal.ul;
			#endif // !DEBUG
		}

		// Set minor:
		if (tokens[i].type == 1)
		{
			v.minor = tokens[i].numVal.ul;
			#if DEBUG
			minor = tokens[i].numVal.ul;
			#endif // !DEBUG
		}

		// Set patch:
		if (tokens[i].type == 2)
		{
			v.patch = tokens[i].numVal.ul;
			#if DEBUG
			patch = tokens[i].numVal.ul;
			#endif // !DEBUG
		}

		// Set build type:
		if (tokens[i].type == 3)
		{
			#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
				VersionLib::setVersionBuildTypeC(v.build_type, buildTypes.data(), static_cast<unsigned short>(buildTypes.size()));
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
			//v.build_revision = tokens[i].numVal.ul;
			#if DEBUG
			build_revision = tokens[i].numVal.ul;
			#endif // !DEBUG
		}

		// Set build:
		if (tokens[i].type == 6)
		{
			v.build = tokens[i].numVal.ull;
			#if DEBUG
			build = tokens[i].numVal.ull;
			#endif // !DEBUG
		}
	}

	#if defined(DEBUG) && (defined(_GLIBCXX_IOSTREAM) || defined(_IOSTREAM_))
	std::cout << "Converted Version: " << major << "." << minor << "." << patch << "-" << build_type_str << "(" << build_type << ")." << build_revision << " build " << build << std::endl << std::endl;
	#endif // !Check for IOSTREAM and DEBUG

	return v;
}
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_TOVERSIONSTRCUT3_METHOD

std::vector<VersionLib::VersionReleaseDataC> VersionLib::findAndGetBuildTypes(std::string &version, long long start, long long end)
{
	size_t verStrSize = version.size();

	std::string tmp;

	long releaseArrIndex = -1;
	std::vector<VersionLib::VersionReleaseDataC> releaseArr;
	
	bool foundBuild = false;
	bool foundBuildTypeField = false;
	bool foundMetadataField = false;
	char t = '\0';

	if (start < 0)
	{
		// Throw an exception
	}

	if (end >= version.size())
	{
		// Throw an exception
	}

	if (start > 0 && end < 0)
	{
		start = -1;
	}
	
	if (start < 0 && end < 0)
	{
		size_t buildPos = 0;

		// Keep the additional local variable restrict to if statement:
		if (!foundBuild)
		{
			std::string tmp;
			bool foundAlphaChar = false;
			long long buildStart = -1;
			long long buildEnd = -1;
	
			// Try to find the build compilation information:
			// On permissive string formats, build compilation can appear
			// as a number after a space of version or after the "build" word.
			for (size_t i = version.size() - 1; i >= 0; i--)
			{
				t = version[i];
				
				if (t >= '0' && t <= '9' && !foundAlphaChar)
				{
					buildEnd = i;
				}
	
				if (t == ' ')
				{
					if (buildEnd != -1)
					{
						buildStart = i;
					}
	
					if (foundAlphaChar)
					{
						break;
					}
				}
	
				if (!foundAlphaChar && t >= 'a' && t <= 'z' || t >= 'A' && t <= 'Z')
				{
					foundAlphaChar = true;
					tmp += t;
				}
			}
	
			// Test directly the "build" word to reduce process time:
			if (VersionLib::tolower_str(tmp) == "dliub" || buildStart > 0 && buildEnd != -1)
			{
				foundBuild = true;
				buildPos = buildStart;
			}
		}

		//buildPos = version.find(" build");
		//if (buildPos > 0 && buildPos < verStrSize)
		//{
		//	foundBuild = true;
		//}

		// If didn't found build word, check if there is a numeric build directly:
		if (!foundBuild)
		{
			for (t = '0'; t <= '9'; t++)
			{
				// Check if there is " #" pattern:
				buildPos = version.find(" " + std::to_string(t));
				if (buildPos > 0 && buildPos < verStrSize)
				{
					foundBuild = true;
					break;
				}
			}
		}

		t = '\0';
	
		for (size_t i = 0; i < verStrSize; i++)
		{
			t = version[i];
	
			if (/*foundBuildTypeField && (t >= '0' && t <= '9') || */foundBuildTypeField && (t == ' ' && i + 1 == buildPos) || t == '+')
			{
				break;
			}
	
			if ((t >= 'a' && t <= 'z' || t >= 'A' && t <= 'Z') && !(t == '.' || t == '-'))
			{
				end = i;
	
				if (!foundBuildTypeField)
				{
					foundBuildTypeField = true;
					start = i;
				}
			}
		}
	}

	// If found a possible substring that contains the build type(s) information, extract them:
	if (start > 0 && end > start)
	{
		tmp = version.substr(start, end - start + 1);

		start = -1;
		end = -1;

		int isRev = 0;	// -1: An exception occurred, 0: Is false, 1: Is true

		for (size_t i = 0; i < tmp.size(); i++)
		{
			t = tmp[i];

			// If detect dot (build type separator) or reach the end of string, try to get the substring:
			if (t == '.' || i + 1 == tmp.size())
			{
				if (start > 0 && end > start)
				{
					if (isRev == 1)
					{
						try
						{
							int rev = std::stoi(tmp.substr(start, end - start + 1));

							if (!releaseArr.empty())
							{
								releaseArr[releaseArrIndex].revision = static_cast<unsigned short>(rev);
								releaseArr[releaseArrIndex].releaseIdentified = true;
							}
						}
						catch(const std::exception&)
						{
							isRev = -1;
						}
					}
					
					if (isRev == 0)
					{
						VersionLib::VersionReleaseDataC release = VersionLib::initVersionReleaseDataC();
						release.release = VersionLib::str2BuildType(tmp.substr(start, end - start + 1));
						releaseArr.push_back(release);
						releaseArrIndex++;
					}
					
					// Reset the status:
					start = -1;
					end = -1;
					isRev = 0;
				}
			}

			// Detect all valid characters used by build type:
			if (t >= 'a' && t <= 'z' || t >= 'A' && t <= 'Z' || t == ' ')
			{
				end = i;

				if (start < 0)
				{
					start = i;
				}
			}

			// Detect the revision:
			if (t >= '0' && t <= '9')
			{
				end = i;

				if (start < 0)
				{
					start = i;
					isRev = 1;
				}
			}
		}
	}

    return releaseArr;
}

std::string VersionLib::extractBuildMetadata(std::string &version)
{
	size_t verStrSize = version.size();

	char t = '\0';
	char l = '\0';
	bool keepMetadataSearch = true;
	bool actualCharIsMetadata = false;
	bool lastCharWasMetadata = false;
	long long plusCharPos = -1;
	long long foundBuildTypeStart = -1;
	long long foundBuildTypeEnd = -1;

	std::string metadataStr;

	for (size_t i = 0; i < verStrSize; i++)
	{
		if (!keepMetadataSearch)
		{
			break;
		}

		// Update the last char status and clean the actual char status:
		lastCharWasMetadata = actualCharIsMetadata;
		actualCharIsMetadata = false;

		// Get the current char:
		t = version[i];

		// Detect '+' signal to remove from version string:
		if (t == '+' && plusCharPos < 0)
		{
			plusCharPos = i;
		}
		
		// Update the last char used to mark and try to detect if next character is the start of metadata if '+' was founded:
		if (l == '+' && foundBuildTypeStart == -1)
		{
			if (t >= 'a' && t <= 'z' || t >= 'A' && t <= 'Z' || t == '-' || t >= '0' || t <= '9')
			{
				foundBuildTypeStart = i;	// Define the start position
			}
		}

		l = t;	// Update last char
		
		// Detect if the next char is valid for metadata:
		if (foundBuildTypeStart >= 0)
		{
			// Update the last valid position for metadata:
			if (t >= 'a' && t <= 'z' || t >= 'A' && t <= 'Z' || t == '-' || t >= '0' && t <= '9')
			{
				foundBuildTypeEnd = i;
				actualCharIsMetadata = true;
			}
	
			// Check if has a next valid char:
			if (i + 1 < verStrSize)
			{
				char tNext = version[i + 1];
				if (!(actualCharIsMetadata && lastCharWasMetadata && (tNext >= 'a' && tNext <= 'z' || tNext >= 'A' && tNext <= 'Z' || tNext == '-' || tNext >= '0' && tNext <= '9')))
				{
					keepMetadataSearch = false;
				}
			}
		}
	}

	// If found the start and end positions and they are not the same, recover from version string and remove from it:
	if (foundBuildTypeStart > 0 && foundBuildTypeEnd > 0 && foundBuildTypeEnd > foundBuildTypeStart && plusCharPos >= 0)
	{
		metadataStr = version.substr(foundBuildTypeStart, (foundBuildTypeEnd - foundBuildTypeStart + 1));
		version.erase(plusCharPos, (foundBuildTypeEnd - plusCharPos + 1));
	}

	return metadataStr;
}

VersionLib::VersionType VersionLib::idVersionType(std::string version, bool isVerFormatStr, std::string regex)
{
	VersionLib::VersionType type = VersionLib::VersionType::UNKNOWN_VERSION_TYPE;

	std::regex ver_regex;

	if (isVerFormatStr)
	{
		if (regex.empty())
		{

		}
		else
		{
			
		}
	}
	else
	{
		if (regex.empty())
		{

		}
		else
		{
			struct knownVer
			{
				std::string verRegex;
				VersionLib::VersionType type;
			};

			std::array<knownVer, 3> known_ver = {
				{
					"",
					VersionLib::VersionType::SEMANTIC_VERSION_TYPE
				}
			};

			for (size_t i = 0; i < known_ver.size(); i++)
			{
			}
		}
	}

    return type;
}
