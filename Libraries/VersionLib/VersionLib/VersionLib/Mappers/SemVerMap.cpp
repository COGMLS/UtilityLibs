#include "SemVerMap.hpp"

#if defined(VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM) && defined(VERSION_LIB_ENABLE_EXPERIMENTAL_DICTIONARY) && defined(VERSION_LIB_ENABLE_EXPERIMENTAL_MAPPER)

//
// Semantic Versioning Mapper:
//

VersionLib::Mappers::SemVerMapper::SemVerMapper()
{
	this->classifier.reset(new VersionLib::Dictionaries::SemVerClassifier);
}

VersionLib::Mappers::SemVerMapper::~SemVerMapper()
{
	this->classifier.reset(nullptr);
}

int VersionLib::Mappers::SemVerMapper::processTokens (std::string version_str)
{
	this->clean();
	std::vector<VersionLib::VersionToken> tokens;
	tokens = this->classifier->extractTokens(version_str);
	return this->processTokens(tokens);
}

int VersionLib::Mappers::SemVerMapper::processTokens (std::vector<VersionLib::VersionToken>& tokens)
{
	this->clean();
	size_t tokens_size = tokens.size();
	VersionLib::VersionTokenType type = VersionLib::VersionTokenType::UNDEFINED_TOKEN;
	VersionLib::VersionTokenType lastType = VersionLib::VersionTokenType::UNDEFINED_TOKEN;
	std::vector<VersionLib::BuildRelease> releases;
	long lastReleasePos = -1;

	for (size_t i = 0; i < tokens_size; i++)
	{
		#if defined(DEBUG) && (defined(_GLIBCXX_IOSTREAM) || defined(_IOSTREAM_))
		std::string debug_info = "[PROCESS TOKENS]::[" + std::to_string(i) + "][" + tokens[i].getTokenData().getTypeStr() + "]::" + tokens[i].getTokenStr();
		std::cout << debug_info << std::endl;
		#endif // !Check for IOSTREAM and DEBUG
		// Get the current token:
		lastType = type;
		type = tokens[i].getType();

		// Test the numerical types:
		if (tokens[i].isNumVal())
		{
			// For numeric types, test the core components or the release version or build compilation

			// Test the core and release components:
			if (tokens[i].isShortVal() || tokens[i].isIntVal())
			{
				if (lastType == VersionLib::VersionTokenType::UNDEFINED_TOKEN || lastType == VersionLib::VersionTokenType::VERSION_TOKEN_VERSION_CORE_SEPARATOR)
				{
					this->core.push_back(tokens[i].getTokenData().getShort());
				}

				if (lastType == VersionLib::VersionTokenType::VERSION_TOKEN_RELEASE_REVISION_SEPARATOR && lastReleasePos != -1)
				{
					VersionLib::BuildRelease release(releases[lastReleasePos].getRelease(), tokens[i].getTokenData().getShort());
					releases[lastReleasePos] = release;
				}
			}

			// For build compilation data:
			if (type == VersionLib::VersionTokenType::VERSION_TOKEN_BUILD_VALUE)
			{
				this->build = tokens[i].getTokenData().getLong();
			}
		}

		// Test for release data:
		if (tokens[i].isType(VersionLib::VersionTokenType::VERSION_TOKEN_RELEASE_COMPONENT_DEFINITION))
		{
			lastReleasePos++;
			VersionLib::BuildRelease release(VersionLib::str2BuildType(tokens[lastReleasePos].getTokenData().getStr()));
			releases.push_back(release);
		}

		// Test for metadata:
		if (lastType == VersionLib::VersionTokenType::VERSION_TOKEN_METADATA_SEPARATOR && type == VersionLib::VersionTokenType::STRING_TOKEN)
		{
			this->metadata = VersionLib::BuildMetadata(tokens[i].getTokenData().getStr());
		}
	}

	this->release = releases;

	return 1;
}

#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM && !VERSION_LIB_ENABLE_EXPERIMENTAL_DICTIONARY && !VERSION_LIB_ENABLE_EXPERIMENTAL_MAPPER