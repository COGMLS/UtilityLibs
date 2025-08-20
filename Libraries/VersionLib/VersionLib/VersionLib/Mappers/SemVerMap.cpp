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

int VersionLib::Mappers::SemVerMapper::processTokens (std::vector<VersionLib::VersionToken>& tokens)
{
	return 1;
}

#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_TOKEN_SYSTEM && !VERSION_LIB_ENABLE_EXPERIMENTAL_DICTIONARY && !VERSION_LIB_ENABLE_EXPERIMENTAL_MAPPER