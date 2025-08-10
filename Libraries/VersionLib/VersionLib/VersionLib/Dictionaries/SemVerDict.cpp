#include "SemVerDict.hpp"

#if defined(VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM) && defined(VERSION_LIB_ENABLE_EXPERIMENTAL_DICTIONARY)

//
// Semantic Versioning Dictionary:
//

VersionLib::Dictionaries::SemVerClassifier::SemVerClassifier()
{
	this->coreComponents = 3;
	this->coreSeparator = '.';
	this->hasOptionalComponents = true;
	this->optGenericSeparator = {' '};
	this->releaseSeparator = '-';
	this->releaseValues = {"alpha","a","beta","b","release candidate","release_candidate","rc","release","r",""};
	this->releaseRevSeparator = '.';
	this->acceptMultipleReleases = true;
	this->buildMetadataSeparator = '+';
	this->hasBuild = 0;
	this->buildNumberSeparator = ' ';
	#ifdef VERSION_LIB_ENABLE_TOKEN_CLASSIFIER_FLAGS
	this->flags = 0b0011'0000;
	#else
	this->allowClassifyMethod = 0;
	this->allowExtractTokensMethod = true;
	#endif // !VERSION_LIB_ENABLE_TOKEN_CLASSIFIER_FLAGS
}

VersionLib::Dictionaries::SemVerClassifier::~SemVerClassifier()
{
}

std::vector<VersionLib::VersionToken> VersionLib::Dictionaries::SemVerClassifier::extractTokens (std::string version)
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

#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM && !VERSION_LIB_ENABLE_EXPERIMENTAL_DICTIONARY