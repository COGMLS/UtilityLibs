#include "TokenClassifier.hpp"

#if defined(VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM) && defined(VERSION_LIB_ENABLE_EXPERIMENTAL_DICTIONARY)

//
// Constructors:
//

/*
VersionLib::TokenClassifier::TokenClassifier()
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
}
*/

VersionLib::TokenClassifier::TokenClassifier()
{
	this->coreComponents = 0;
	this->coreSeparator = 0;
	this->hasOptionalComponents = true;
	this->optGenericSeparator = {0};
	this->releaseSeparator = 0;
	this->releaseValues = {};
	this->releaseRevSeparator = 0;
	this->acceptMultipleReleases = false;
	this->buildMetadataSeparator = 0;
	this->hasBuild = 0;
	this->buildNumberSeparator = 0;
}

VersionLib::TokenClassifier::TokenClassifier (unsigned short coreComponents, char coreSeparator, bool hasOptionalComponents, std::vector<char> optGenericSeparator, char releaseSeparator, std::vector<std::string> releaseValues, char releaseRevSeparator, bool acceptMultipleReleases, char buildMetadataSeparator, short hasBuild, char buildNumberSeparator)
{
	if (hasBuild < 0 || hasBuild > 3)
	{
		hasBuild = 0;
	}

	this->coreComponents = coreComponents;
	this->coreSeparator = coreSeparator;
	this->hasOptionalComponents = hasOptionalComponents;
	this->optGenericSeparator = optGenericSeparator;
	this->releaseSeparator = releaseSeparator;
	this->releaseValues = releaseValues;
	this->releaseRevSeparator = releaseRevSeparator;
	this->acceptMultipleReleases = acceptMultipleReleases;
	this->buildMetadataSeparator = buildMetadataSeparator;
	this->hasBuild = hasBuild;
	this->buildNumberSeparator = buildNumberSeparator;
}

VersionLib::TokenClassifier::TokenClassifier (const VersionLib::TokenClassifier &other)
{
	this->coreComponents = other.coreComponents;
	this->coreSeparator = other.coreSeparator;
	this->hasOptionalComponents = other.hasOptionalComponents;
	this->optGenericSeparator = other.optGenericSeparator;
	this->releaseSeparator = other.releaseSeparator;
	this->releaseValues = other.releaseValues;
	this->releaseRevSeparator = other.releaseRevSeparator;
	this->acceptMultipleReleases = other.acceptMultipleReleases;
	this->buildMetadataSeparator = other.buildMetadataSeparator;
	this->hasBuild = other.hasBuild;
	this->buildNumberSeparator = other.buildNumberSeparator;
	#ifdef VERSION_LIB_ENABLE_TOKEN_CLASSIFIER_FLAGS
	this->flags = other.flags;
	#else
	this->allowClassifyMethod = other.allowClassifyMethod;
	this->allowExtractTokensMethod = other.allowExtractTokensMethod;
	this->readyForUse = other.readyForUse;
	this->debugTokenClassifier = other.debugTokenClassifier;
	#endif // !VERSION_LIB_ENABLE_TOKEN_CLASSIFIER_FLAGS
}

VersionLib::TokenClassifier::TokenClassifier (VersionLib::TokenClassifier &&other) noexcept
{
	this->coreComponents = std::move(other.coreComponents);
	this->coreSeparator = std::move(other.coreSeparator);
	this->hasOptionalComponents = std::move(other.hasOptionalComponents);
	this->optGenericSeparator = std::move(other.optGenericSeparator);
	this->releaseSeparator = std::move(other.releaseSeparator);
	this->releaseValues = std::move(other.releaseValues);
	this->releaseRevSeparator = std::move(other.releaseRevSeparator);
	this->acceptMultipleReleases = std::move(other.acceptMultipleReleases);
	this->buildMetadataSeparator = std::move(other.buildMetadataSeparator);
	this->hasBuild = std::move(other.hasBuild);
	this->buildNumberSeparator = std::move(other.buildNumberSeparator);
	#ifdef VERSION_LIB_ENABLE_TOKEN_CLASSIFIER_FLAGS
	this->flags = std::move(other.flags);
	#else
	this->allowClassifyMethod = std::move(other.allowClassifyMethod);
	this->allowExtractTokensMethod = std::move(other.allowExtractTokensMethod);
	this->readyForUse = std::move(other.readyForUse);
	this->debugTokenClassifier = std::move(other.debugTokenClassifier);
	#endif // !VERSION_LIB_ENABLE_TOKEN_CLASSIFIER_FLAGS
}

//
// Destructor:
//

VersionLib::TokenClassifier::~TokenClassifier()
{
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_TOKEN_DEBUGGER
	this->dbg.reset(nullptr);
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_TOKEN_DEBUGGER
}

//
// Operators:
//

VersionLib::TokenClassifier &VersionLib::TokenClassifier::operator= (const VersionLib::TokenClassifier &other)
{
    if (this == &other)
	{
		return *this;
	}

	this->coreComponents = other.coreComponents;
	this->coreSeparator = other.coreSeparator;
	this->hasOptionalComponents = other.hasOptionalComponents;
	this->optGenericSeparator = other.optGenericSeparator;
	this->releaseSeparator = other.releaseSeparator;
	this->releaseValues = other.releaseValues;
	this->releaseRevSeparator = other.releaseRevSeparator;
	this->acceptMultipleReleases = other.acceptMultipleReleases;
	this->buildMetadataSeparator = other.buildMetadataSeparator;
	this->hasBuild = other.hasBuild;
	this->buildNumberSeparator = other.buildNumberSeparator;
	#ifdef VERSION_LIB_ENABLE_TOKEN_CLASSIFIER_FLAGS
	this->flags = other.flags;
	#else
	this->allowClassifyMethod = other.allowClassifyMethod;
	this->allowExtractTokensMethod = other.allowExtractTokensMethod;
	this->readyForUse = other.readyForUse;
	#endif // !VERSION_LIB_ENABLE_TOKEN_CLASSIFIER_FLAGS

	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_TOKEN_DEBUGGER
	*this->dbg = *other.dbg;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_TOKEN_DEBUGGER

	return *this;
}

VersionLib::TokenClassifier &VersionLib::TokenClassifier::operator= (VersionLib::TokenClassifier &&other) noexcept
{
    if (this == &other)
	{
		return *this;
	}

	this->coreComponents = std::move(other.coreComponents);
	this->coreSeparator = std::move(other.coreSeparator);
	this->hasOptionalComponents = std::move(other.hasOptionalComponents);
	this->optGenericSeparator = std::move(other.optGenericSeparator);
	this->releaseSeparator = std::move(other.releaseSeparator);
	this->releaseValues = std::move(other.releaseValues);
	this->releaseRevSeparator = std::move(other.releaseRevSeparator);
	this->acceptMultipleReleases = std::move(other.acceptMultipleReleases);
	this->buildMetadataSeparator = std::move(other.buildMetadataSeparator);
	this->hasBuild = std::move(other.hasBuild);
	this->buildNumberSeparator = std::move(other.buildNumberSeparator);
	#ifdef VERSION_LIB_ENABLE_TOKEN_CLASSIFIER_FLAGS
	this->flags = std::move(other.flags);
	#else
	this->allowClassifyMethod = std::move(other.allowClassifyMethod);
	this->allowExtractTokensMethod = std::move(other.allowExtractTokensMethod);
	this->readyForUse = std::move(other.readyForUse);
	#endif // !VERSION_LIB_ENABLE_TOKEN_CLASSIFIER_FLAGS

	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_TOKEN_DEBUGGER
	this->dbg = std::move(other.dbg);
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_TOKEN_DEBUGGER

	return *this;
}

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_TOKEN_DEBUGGER

//
// Token Classifier Debugger:
//

void VersionLib::TokenClassifier::write_log (std::string entry)
{
	if (this->dbg && this->is_logger_enabled())
	{
		this->dbg->push_log(entry);
	}
}

void VersionLib::TokenClassifier::set_logger (bool status)
{
	if (!this->is_logger_enabled() && status)
	{
		this->dbg.reset(new VersionLib::Debugger::DbgToken(VERSION_LIB_TOKEN_DEBUGGER_MAX_SIZE, false));
	}

	if (this->is_logger_enabled() && !status)
	{
		this->dbg.reset(nullptr);
	}
	
	#ifdef VERSION_LIB_ENABLE_TOKEN_CLASSIFIER_FLAGS
	this->flags = this->flags | (status << 6);
	#else
	this->debugTokenClassifier = status;
	#endif // !VERSION_LIB_ENABLE_TOKEN_CLASSIFIER_FLAGS
}

bool VersionLib::TokenClassifier::is_logger_enabled()
{
	#ifdef VERSION_LIB_ENABLE_TOKEN_CLASSIFIER_FLAGS
	return (this->flags >> 6) & 0b0000'0001;
	#else
	return this->debugTokenClassifier = status;
	#endif // !VERSION_LIB_ENABLE_TOKEN_CLASSIFIER_FLAGS
}

std::unique_ptr<std::vector<std::string>> VersionLib::TokenClassifier::export_log()
{
	std::unique_ptr<std::vector<std::string>> pLogs;

	if (this->dbg && this->is_logger_enabled())
	{
		pLogs = this->dbg->export_log();
	}

	return pLogs;
}

#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_TOKEN_DEBUGGER

//
// Getters:
//

unsigned short VersionLib::TokenClassifier::getNumCoreComponents()
{
    return this->coreComponents;
}

char VersionLib::TokenClassifier::getCoreSeparator()
{
    return this->coreSeparator;
}

bool VersionLib::TokenClassifier::getHasOptionalComponents()
{
    return this->hasOptionalComponents;
}

std::vector<char> VersionLib::TokenClassifier::getOptGenericSeparator()
{
    return this->optGenericSeparator;
}

char VersionLib::TokenClassifier::getReleaseSeparator()
{
    return this->releaseSeparator;
}

std::vector<std::string> VersionLib::TokenClassifier::getReleaseValues()
{
    return this->releaseValues;
}

char VersionLib::TokenClassifier::getReleaseRevSeparator()
{
    return this->releaseRevSeparator;
}

bool VersionLib::TokenClassifier::getAcceptMultipleReleases()
{
    return this->acceptMultipleReleases;
}

char VersionLib::TokenClassifier::getBuildMetadataSeparator()
{
    return this->buildMetadataSeparator;
}

short VersionLib::TokenClassifier::getHasBuild()
{
    return this->hasBuild;
}

char VersionLib::TokenClassifier::getBuildNumberSeparator()
{
    return this->buildNumberSeparator;
}

//
// Classifier Controls:
//

bool VersionLib::TokenClassifier::isReady()
{
	#ifdef VERSION_LIB_ENABLE_TOKEN_CLASSIFIER_FLAGS
	return (this->flags >> 5) && 0b0000'0001;
	#else
	return this->readyForUse;
	#endif // !VERSION_LIB_ENABLE_TOKEN_CLASSIFIER_FLAGS
}

short VersionLib::TokenClassifier::allowClassify()
{
	#ifdef VERSION_LIB_ENABLE_TOKEN_CLASSIFIER_FLAGS
	return this->flags & 0b0000'1111;
	#else
	return this->allowClassifyMethod;
	#endif // !VERSION_LIB_ENABLE_TOKEN_CLASSIFIER_FLAGS
}

bool VersionLib::TokenClassifier::allowExtract()
{
	#ifdef VERSION_LIB_ENABLE_TOKEN_CLASSIFIER_FLAGS
	return (this->flags >> 4) & 0b0000'0001;
	#else
	return this->allowExtractTokensMethod;
	#endif // !VERSION_LIB_ENABLE_TOKEN_CLASSIFIER_FLAGS
}

//
// Checkers:
//

VersionLib::VersionTokenType VersionLib::TokenClassifier::classify()
{
    return VersionLib::VersionTokenType::UNDEFINED_TOKEN;
}

VersionLib::VersionTokenType VersionLib::TokenClassifier::classify (char *currentChar, std::string *strAcc, VersionLib::VersionTokenType *tokenType, VersionLib::VersionTokenType *lastTokenType, bool useTmpToken, VersionLib::VersionToken* tmpData)
{
    return VersionLib::VersionTokenType::UNDEFINED_TOKEN;
}

VersionLib::VersionTokenType VersionLib::TokenClassifier::classify (size_t *index, std::string *versionStr, char *currentChar, std::string *strAcc, VersionLib::VersionTokenType *tokenType, VersionLib::VersionTokenType *lastTokenType, bool useTmpToken, VersionLib::VersionToken* tmpData)
{
    return VersionLib::VersionTokenType::UNDEFINED_TOKEN;
}

//
// Extraction methods:
//

std::vector<VersionLib::VersionToken> VersionLib::TokenClassifier::extractTokens (std::string version)
{
	return std::vector<VersionLib::VersionToken>();
}

#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM && !VERSION_LIB_ENABLE_EXPERIMENTAL_DICTIONARY