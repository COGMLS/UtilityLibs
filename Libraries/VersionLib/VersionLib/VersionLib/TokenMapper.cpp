#include "TokenMapper.hpp"

#if defined(VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM) && defined(VERSION_LIB_ENABLE_EXPERIMENTAL_DICTIONARY) && defined(VERSION_LIB_ENABLE_EXPERIMENTAL_MAPPER)

//
// Protected methods:
//

void VersionLib::TokenMapper::setBuildCompilation(unsigned long build)
{
	if (this->useBuild != 0)
	{
		this->build = build;
	}
}

//
// Constructors:
//

VersionLib::TokenMapper::TokenMapper() {}

VersionLib::TokenMapper::TokenMapper (VersionLib::TokenClassifier classifier)
{
	this->classifier.reset(new VersionLib::TokenClassifier(classifier));
}

VersionLib::TokenMapper::TokenMapper (const VersionLib::TokenMapper& other)
{
	*this->classifier = *other.classifier;
	this->core = other.core;
	this->release = other.release;
	this->metadata = other.metadata;
	this->useBuild = other.useBuild;
	this->build = other.build;
}

VersionLib::TokenMapper::TokenMapper (VersionLib::TokenMapper&& other) noexcept
{
	this->classifier = std::move(other.classifier);
	this->core = std::move(other.core);
	this->release = std::move(other.release);
	this->metadata = std::move(other.metadata);
	this->useBuild = std::move(other.useBuild);
	this->build = std::move(other.build);
}

//
// Destructor:
//

VersionLib::TokenMapper::~TokenMapper()
{
	this->classifier.reset(nullptr);
}

//
// Operators:
//

VersionLib::TokenMapper& VersionLib::TokenMapper::operator= (const VersionLib::TokenMapper& other)
{
	if (this == &other)
	{
		return *this;
	}

	*this->classifier = *other.classifier;
	this->core = other.core;
	this->release = other.release;
	this->metadata = other.metadata;
	this->useBuild = other.useBuild;
	this->build = other.build;

	return *this;
}

VersionLib::TokenMapper& VersionLib::TokenMapper::operator= (VersionLib::TokenMapper&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	this->classifier = std::move(other.classifier);
	this->core = std::move(other.core);
	this->release = std::move(other.release);
	this->metadata = std::move(other.metadata);
	this->useBuild = std::move(other.useBuild);
	this->build = std::move(other.build);

	return *this;
}

//
// Classifier Direct Access:
//

VersionLib::TokenClassifier* VersionLib::TokenMapper::access()
{
	if (this->classifier) return this->classifier.get();
	return nullptr;
}

//
// Token components:
//

//VersionLib::VersionToken VersionLib::TokenMapper::getToken (size_t pos)
//{
//	return VersionLib::VersionToken();
//}

int VersionLib::TokenMapper::processTokens (std::string version_str)
{
	return -1;
}

int VersionLib::TokenMapper::processTokens (std::vector<VersionLib::VersionToken>& tokens)
{
	return -1;
}

int VersionLib::TokenMapper::processTokens (VersionLib::TokenClassifier* classifier, std::string version_str)
{
    return -1;
}

//
// Checkers:
//

bool VersionLib::TokenMapper::hasCoreSeq()
{
	return !this->core.empty();
}

bool VersionLib::TokenMapper::hasVersionBuildType()
{
	return !this->release.isEmpty();
}

bool VersionLib::TokenMapper::hasMetadata()
{
	return !this->metadata.isEmpty();
}

short VersionLib::TokenMapper::hasBuildCompilation()
{
	return this->useBuild;
}

//
// Getters for classified version tokens:
//

std::vector<unsigned short> VersionLib::TokenMapper::getCoreNumSeq()
{
	return this->core;
}

VersionLib::VersionBuildType VersionLib::TokenMapper::getBuildTypeComponents()
{
	return this->release;
}

VersionLib::BuildMetadata VersionLib::TokenMapper::getBuildMetadata()
{
	return this->metadata;
}

unsigned long VersionLib::TokenMapper::getBuildCompilation()
{
	if (this->useBuild == 2)
	{
		return this->build;
	}
	return 0ul;
}

void VersionLib::TokenMapper::clean()
{
	this->core.clear();
	this->release = VersionLib::VersionBuildType();
	this->metadata = VersionLib::BuildMetadata();
	//this->useBuild = false;	// Build should not be changed
	this->build = 0ul;
}

#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM && !VERSION_LIB_ENABLE_EXPERIMENTAL_DICTIONARY && !VERSION_LIB_ENABLE_EXPERIMENTAL_MAPPER
