#include "VersionTools.hpp"

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

	#ifdef VERSION_LIB_PURE_CPP_DATA_STRUCT
	bool processedType = false;
	bool processedRevision = false;
	VersionLib::BuildRelease build_type_data;
	#else
	#if defined(VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT) && defined(VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE)
	bool processedType = false;
	bool processedRevision = false;
	std::vector<VersionLib::VersionReleaseData> build_types;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT && !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
	#endif // !VERSION_LIB_PURE_CPP_DATA_STRUCT

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
		#if defined(VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT) && defined(VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE) || defined(VERSION_LIB_PURE_CPP_DATA_STRUCT)
		if (tokens[i].type == 3 && !processedType)
		#else
		if (tokens[i].type == 3)
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT && !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE || !VERSION_LIB_PURE_CPP_DATA_STRUCT
		{
			#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
				// Convert the build types in string format to BuildType enumerator:
				
				#ifdef VERSION_LIB_PURE_CPP_DATA_STRUCT
				// Recreate the object reusing the revision data and applying a new build type:
				build_type_data = VersionLib::BuildRelease(VersionLib::str2BuildType(tokens[i].str), build_type_data.getRevision());
				#else
				if (!processedRevision)
				{
					build_types.push_back(VersionLib::initVersionReleaseDataC());
				}

				build_types[0].release = VersionLib::str2BuildType(tokens[i].str);
				build_types[0].releaseIdentified = true;
				#endif // !VERSION_LIB_PURE_CPP_DATA_STRUCT
				processedType = true;

				//std::vector<VersionLib::VersionReleaseData> buildTypes = VersionLib::findAndGetBuildTypes(tokens[i].str);
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

		#if defined(VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT) && defined(VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE) || defined(VERSION_LIB_PURE_CPP_DATA_STRUCT)
		if (tokens[i].type == 4 && !processedRevision)
		{
			#ifdef VERSION_LIB_PURE_CPP_DATA_STRUCT
			// Recreate the object applying a new revision information:
			build_type_data = VersionLib::BuildRelease(build_type_data.getRelease(), tokens[i].ul);
			#else
			if (!processedType)
			{
				build_types.push_back(VersionLib::initVersionReleaseDataC());
			}
			
			build_types[0].revision = tokens[i].ul;
			build_types[0].releaseIdentified = true;
			#endif // !VERSION_LIB_PURE_CPP_DATA_STRUCT
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
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT && !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE || !VERSION_LIB_PURE_CPP_DATA_STRUCT

		// Set build:
		if (tokens[i].type == 6)
		{
			v.build = tokens[i].ull;
			#if DEBUG
			build = tokens[i].ull;
			#endif // !DEBUG
		}
	}

	#ifdef VERSION_LIB_PURE_CPP_DATA_STRUCT
	// Insert the object into the vector:
	v.build_type = build_type_data;
	#else
	#if defined(VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT) && defined(VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE)
	if (processedType || processedRevision)
	{
		VersionLib::setVersionBuildTypeC(v.build_type, build_types.data(), static_cast<unsigned short>(build_types.size()));
	}
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT && !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
	#endif // !VERSION_LIB_PURE_CPP_DATA_STRUCT

	#if defined(DEBUG) && (defined(_GLIBCXX_IOSTREAM) || defined(_IOSTREAM_))
	std::cout << "Converted Version: " << major << "." << minor << "." << patch << "-" << build_type_str << "(" << build_type << ")." << build_revision << " build " << build << std::endl << std::endl;
	#endif // !Check for IOSTREAM and DEBUG

	return v;
}

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_TOSEMVERTOKENS_METHOD
std::vector<VersionLib::VersionToken> VersionLib::toSemVerTokens(std::string version)
{
	#if defined(DEBUG) && (defined(_GLIBCXX_IOSTREAM) || defined(_IOSTREAM_))
	std::cout << "Version to convert: " << version << std::endl;
	#endif // !Check for IOSTREAM and DEBUG

	// Make sure the version string is complete in lowercase:
	version = VersionLib::tolower_str(version);

	size_t verStrSize = version.size();

	//
	// Variable controls:
	//

	std::vector<VersionLib::VersionToken> tokens;	// Vector of tokens

	short foundMetadata = -1;					// Found the metadata info position (-1 is unknown position), 0: Current separator, 1: Metadata part, 2 >= Not metadata part
	bool isMandatoryToken = false;				// Determinate if the token is mandatory
	
	bool addToken = false;						// Add the new token into the token vector
	bool analyzeVerStr = true;					// Enable the analyzing loop
	bool isVerCore = true;						// Is Version Core

	char t = '\0';								// Current char in analysis
	std::string tmp;							// Temporary variable accumulator
	
	int position = 0;							// Token position counter
	VersionLib::VersionToken tmpToken;			// Temporary token
	VersionLib::VersionTokenData tmpData;		// Temporary token data
	VersionLib::VersionTokenType tokenType;		// Temporary token type ID
	VersionLib::VersionTokenType lastTokenType;	// Last temporary token type ID

	tokenType = VersionLib::VersionTokenType::UNDEFINED_TOKEN;	// Set the token type as undefined
	lastTokenType = tokenType;

	/** Generate tokens from version string:
	 * ----------------------------------------
	 * The algorithm will create sets of data
	 * separating the components by the separators,
	 * numbers, alphanumerical values and spaces
	 * 
	 */
	size_t i = 0;
	while (analyzeVerStr)
	{
		if (i < verStrSize)
		{
			t = version[i];		// Get the current char to analyze
		}

		// Test if the current char is alphabetical char and classify as string
		if (t >= 'a' && t <= 'z' || t >= 'A' && t <= 'Z')
		{
			tmp += t;
			// Set to string classification when is not metadata. This overwrite numerical classification
			if (
					tokenType == VersionLib::VersionTokenType::SHORT_NUMERIC_TOKEN || 
					tokenType == VersionLib::VersionTokenType::NUMERIC_TOKEN || 
					tokenType == VersionLib::VersionTokenType::LONG_NUMBER_TOKEN || 
					tokenType == VersionLib::VersionTokenType::UNDEFINED_TOKEN || 
					tokenType == VersionLib::VersionTokenType::VERSION_TOKEN_GENERIC_VALUE
				)
				{
					tokenType = VersionLib::VersionTokenType::STRING_TOKEN;
					isVerCore = false;	// Version core appears only before the string components
				}
		}

		// Test if current char is numerical char
		if (t >= '0' && t <= '9')
		{
			tmp += t;
			// If the first char is between 0 to 9 of if the accumulator still only holding numbers
			if (
					tokenType == VersionLib::VersionTokenType::UNDEFINED_TOKEN || 
					tokenType == VersionLib::VersionTokenType::SHORT_NUMERIC_TOKEN || 
					tokenType == VersionLib::VersionTokenType::NUMERIC_TOKEN || 
					tokenType == VersionLib::VersionTokenType::LONG_NUMBER_TOKEN
				)
			{
				// Test if the content is convertible:
				try
				{
					unsigned int a = static_cast<unsigned int>(std::stoi(tmp));
					tmpData = VersionLib::VersionTokenData(a);
					tokenType = VersionLib::VersionTokenType::NUMERIC_TOKEN;
					if (tmpData.getInt() < USHRT_MAX)
					{
						unsigned short b = static_cast<unsigned short>(a);
						tmpData = VersionLib::VersionTokenData(b);
						tokenType = VersionLib::VersionTokenType::SHORT_NUMERIC_TOKEN;
					}
				}
				catch(const std::exception&)
				{
					try
					{
						unsigned long c = std::stoul(tmp);
						tmpData = VersionLib::VersionTokenData(c);
						tokenType = VersionLib::VersionTokenType::LONG_NUMBER_TOKEN;
					}
					catch(const std::exception&)
					{
						// Do not generate an output or throw an error
						/// NOTE: tokenType to GENERIC VALUE while catching exception
						tokenType = VersionLib::VersionTokenType::VERSION_TOKEN_GENERIC_VALUE;
					}
				}
			}
		}

		// Test if the next char is a separator
		if (i + 1 < verStrSize)
		{
			if (version[i + 1] == '.' || version[i + 1] == ' ' || version[i + 1] == '-' || version[i + 1] == '+')
			{
				// If is in metadata segment, jump these characters:
				if (!((version[i + 1] == '.' || version[i + 1] == '-') && foundMetadata == 1))
				{
					addToken = true;
				}
			}
		}

		// If is the last char, make sure the last analyzed component can be added into token list
		if (i + 1 == verStrSize)
		{
			addToken = true;
		}

		// If is a string, test if is a release or build word
		if (tokenType == VersionLib::VersionTokenType::STRING_TOKEN)
		{
			if (VersionLib::isReleaseStr(tmp))
			{
				tokenType = VersionLib::VersionTokenType::VERSION_TOKEN_RELEASE_COMPONENT_DEFINITION;
			}

			if (tmp == "build")
			{
				tokenType = VersionLib::VersionTokenType::VERSION_TOKEN_BUILD_WORD;
			}
		}

		// Metadata allows to use alphanumerical values, dashes and dots
		if (lastTokenType == VersionLib::VersionTokenType::VERSION_TOKEN_METADATA_SEPARATOR)
		{
			tokenType = VersionLib::VersionTokenType::STRING_TOKEN;
		}

		// Test for separators
		if ((t == '.' || t == ' ' || t == '-' || t == '+') && !addToken)
		{
			// Test if is space separator and is in metadata segment:
			if (t == ' ' && foundMetadata == 1)
			{
				foundMetadata = 2;	// Make the metadata status is out of segment
				addToken = true;
			}
			else
			{
				// Test if is dot or dash and the last token was metadata separator to determinate the metadata segment:
				if ((t == '.' || t == '-') && foundMetadata == 1)
				{
					tmp += t;
				}
				else
				{
					tmp += t;	// If all other tests fail, treat as separator
				}
			}

			// If is not in metadata segment:
			if (foundMetadata != 1)
			{
				// Check possible separators: Version Core or Revision separator
				if (t == '.')
				{
					tokenType = VersionLib::VersionTokenType::VERSION_TOKEN_VERSION_CORE_SEPARATOR;
					if (lastTokenType == VersionLib::VersionTokenType::VERSION_TOKEN_RELEASE_COMPONENT_DEFINITION)
					{
						tokenType = VersionLib::VersionTokenType::VERSION_TOKEN_RELEASE_REVISION_SEPARATOR;
					}
					addToken = true;
				}
	
				// Check for generic separator
				if (t == ' ')
				{
					if (
							lastTokenType == VersionLib::VersionTokenType::VERSION_TOKEN_BUILD_WORD || 
							lastTokenType == VersionLib::VersionTokenType::VERSION_TOKEN_RELEASE_COMPONENT_DEFINITION || 
							lastTokenType == VersionLib::VersionTokenType::SHORT_NUMERIC_TOKEN || 
							lastTokenType == VersionLib::VersionTokenType::NUMERIC_TOKEN || 
							lastTokenType == VersionLib::VersionTokenType::LONG_NUMBER_TOKEN
						)
					{
						tokenType = VersionLib::VersionTokenType::VERSION_TOKEN_BUILD_SEPARATOR;
					}
					else
					{
						tokenType = VersionLib::VersionTokenType::VERSION_TOKEN_GENERIC_SEPARATOR;
					}
					addToken = true;
				}
	
				// Check if is version release separator
				if (t == '-')
				{
					tokenType = VersionLib::VersionTokenType::VERSION_TOKEN_RELEASE_SEPARATOR;
					addToken = true;
				}
			}

			// Check for metadata separator
			if (t == '+' && foundMetadata == -1)
			{
				tokenType = VersionLib::VersionTokenType::VERSION_TOKEN_METADATA_SEPARATOR;
				foundMetadata = 0;	// Set the metadata separator
				addToken = true;
			}
		}

		// Check if must be mandatory component
		if (lastTokenType == VersionLib::VersionTokenType::VERSION_TOKEN_VERSION_CORE_SEPARATOR)
		{
			isMandatoryToken = true;
		}

		// If passed in all tests, check if must to add the token:
		if (addToken)
		{
			// Add the non numeric components
			if (
					!(tokenType == VersionLib::VersionTokenType::SHORT_NUMERIC_TOKEN || 
					tokenType == VersionLib::VersionTokenType::NUMERIC_TOKEN || 
					tokenType == VersionLib::VersionTokenType::LONG_NUMBER_TOKEN)
				)
			{
				tmpData = VersionLib::VersionTokenData(tmp);
			}

			// Possibles situations to detect the build value:
			// After "build" word
			// After a space and current token is a numerical
			if (
					(
						lastTokenType == VersionLib::VersionTokenType::VERSION_TOKEN_BUILD_WORD || 
						lastTokenType == VersionLib::VersionTokenType::VERSION_TOKEN_GENERIC_SEPARATOR || 
						lastTokenType == VersionLib::VersionTokenType::VERSION_TOKEN_BUILD_SEPARATOR
					) && (
						tokenType == VersionLib::VersionTokenType::SHORT_NUMERIC_TOKEN || 
						tokenType == VersionLib::VersionTokenType::NUMERIC_TOKEN || 
						tokenType == VersionLib::VersionTokenType::LONG_NUMBER_TOKEN
					)
				)
			{
				// Build value must be a unsigned long type:

				// For short type:
				if (tokenType == VersionLib::VersionTokenType::SHORT_NUMERIC_TOKEN)
				{
					tmpData = VersionLib::VersionTokenData(static_cast<unsigned long>(tmpData.getShort()));
				}
				// For int type:
				if (tokenType == VersionLib::VersionTokenType::NUMERIC_TOKEN)
				{
					tmpData = VersionLib::VersionTokenData(static_cast<unsigned long>(tmpData.getInt()));
				}

				tokenType = VersionLib::VersionTokenType::VERSION_TOKEN_BUILD_VALUE;
			}

			tmpToken = VersionLib::VersionToken(tmpData, tokenType, position, isMandatoryToken);
			tokens.push_back(tmpToken);

			// If the token was a metadata separator, the next component is the metadata it self
			if (tokenType == VersionLib::VersionTokenType::VERSION_TOKEN_METADATA_SEPARATOR)
			{
				foundMetadata = 1;	// Set the next token component is metadata
			}

			lastTokenType = tokenType;
			tokenType = VersionLib::VersionTokenType::UNDEFINED_TOKEN;
			addToken = false;
			isMandatoryToken = false;
			tmp.clear();
			position++;
		}

		i++;

		// If next position is out of limit, disable the next char acquisition
		if (i == verStrSize)
		{
			analyzeVerStr = false;
		}
	}

	#if defined(DEBUG) && (defined(_GLIBCXX_IOSTREAM) || defined(_IOSTREAM_))
	std::cout << "Detected Tokens:" << std::endl;
	for (size_t j = 0; j < tokens.size(); j++)
	{
		std::cout << "[" << j << "][" << VersionLib::getTokenTypeStr(tokens[j].getType()) << "]::";
		
		switch (tokens[j].getTokenData().getDataType())
		{
			case VersionLib::VersionTokenDataType::NULL_TYPE:
			{
				std::cout << "NULL_TOKEN_DATA";
				break;
			}
			case VersionLib::VersionTokenDataType::STRING_TYPE:
			{
				std::cout << tokens[j].getTokenData().getStr();
				break;
			}
			case VersionLib::VersionTokenDataType::UNSIGNED_SHORT_TYPE:
			{
				std::cout << tokens[j].getTokenData().getShort();
				break;
			}
			case VersionLib::VersionTokenDataType::UNSIGNED_INT_TYPE:
			{
				std::cout << tokens[j].getTokenData().getInt();
				break;
			}
			case VersionLib::VersionTokenDataType::UNSIGNED_LONG_TYPE:
			{
				std::cout << tokens[j].getTokenData().getLong();
				break;
			}
			default:
			{
				std::cout << "EMPTY_TOKEN_DATA";
				break;
			}
		}
		
		std::cout << std::endl;
	}
	std::cout << "----------------" << std::endl;
	#endif // !Check for IOSTREAM and DEBUG

	return tokens;
}
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_TOSEMVERTOKENS_METHOD

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
			else
			{
				break;
			}
	
			//// Check if has a next valid char:
			//if (i + 1 < verStrSize)
			//{
			//	char tNext = version[i + 1];
			//	if (!(actualCharIsMetadata && lastCharWasMetadata && !(tNext >= 'a' && tNext <= 'z' || tNext >= 'A' && tNext <= 'Z' || tNext == '-' || tNext >= '0' && tNext <= '9')))
			//	{
			//		keepMetadataSearch = false;
			//	}
			//}
		}
	}

	// If found the start and end positions and they are not the same, recover from version string and remove from it:
	if (foundBuildTypeStart > 0 && foundBuildTypeEnd > 0 && foundBuildTypeEnd > foundBuildTypeStart && plusCharPos >= 0)
	{
		metadataStr = version.substr(foundBuildTypeStart, (foundBuildTypeEnd - foundBuildTypeStart + 1));
		version = version.erase(plusCharPos, (foundBuildTypeEnd - plusCharPos + 1));
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
