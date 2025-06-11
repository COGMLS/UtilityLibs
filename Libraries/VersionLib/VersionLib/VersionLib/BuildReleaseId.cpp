#include "BuildReleaseId.hpp"

VersionLib::BuildRelease::BuildRelease()
{
	this->release = VERSION_LIB_DEFAULT_BUILD_RELEASE_TYPE_INIT;
	this->revision = 0;
	this->releaseIdentified = true;
}

VersionLib::BuildRelease::BuildRelease(std::string release)
{
	std::vector<VersionLib::VersionReleaseData> types = VersionLib::findAndGetBuildTypes(release);
	if (types.empty())
	{
		this->release = VERSION_LIB_DEFAULT_BUILD_RELEASE_TYPE_INIT;
		this->revision = 0;
		this->releaseIdentified = false;
	}
	else
	{
		this->release = types[0].release;
		this->revision = types[0].revision;
		this->releaseIdentified = types[0].releaseIdentified;
	}
}

VersionLib::BuildRelease::BuildRelease(VersionLib::BuildType release, unsigned short revision)
{
	this->release = release;
	this->revision = revision;
	this->releaseIdentified = true;
}

VersionLib::BuildRelease::BuildRelease(VersionLib::VersionReleaseData &build_release)
{
	this->release = build_release.release;
	this->revision = build_release.revision;
	this->releaseIdentified = build_release.releaseIdentified;
}

VersionLib::BuildRelease::BuildRelease(const VersionLib::BuildRelease &other)
{
	this->release = other.release;
	this->revision = other.revision;
	this->releaseIdentified = other.releaseIdentified;
}

VersionLib::BuildRelease::BuildRelease(VersionLib::BuildRelease &&other) noexcept
{
	this->release = std::move(other.release);
	this->revision = std::move(other.revision);
	this->releaseIdentified = std::move(other.releaseIdentified);
}

VersionLib::BuildRelease::~BuildRelease()
{
}

VersionLib::BuildType VersionLib::BuildRelease::getRelease()
{
    return this->release;
}

unsigned short VersionLib::BuildRelease::getRevision()
{
    return this->revision;
}

float VersionLib::BuildRelease::getWeight(unsigned short pos)
{
	return VersionLib::calcReleaseWeight(this->release, this->revision, pos);
}

bool VersionLib::BuildRelease::isReleaseInfoOk()
{
    return this->releaseIdentified;
}

std::string VersionLib::BuildRelease::toString(bool useShortStr, bool showReleaseType)
{
	std::string tmp;

	if (this->release == VersionLib::BuildType::RELEASE && !showReleaseType)
	{
		return tmp;
	}

	tmp = VersionLib::buildType2Str(this->release, useShortStr, showReleaseType);

	if (this->revision > 0)
	{
		tmp += "." + std::to_string(this->revision);
	}

    return tmp;
}

VersionLib::VersionReleaseData VersionLib::BuildRelease::toReleaseDataC()
{
	VersionLib::VersionReleaseData tmp = VersionLib::initVersionReleaseDataC();

	tmp.release = this->release;
	tmp.revision = this->revision;
	tmp.releaseIdentified = this->releaseIdentified;

	return tmp;
}

VersionLib::BuildRelease &VersionLib::BuildRelease::operator=(const VersionLib::BuildRelease &other)
{
	this->release = other.release;
	this->revision = other.revision;
	this->releaseIdentified = other.releaseIdentified;
	return *this;
}

VersionLib::BuildRelease &VersionLib::BuildRelease::operator=(VersionLib::BuildRelease &&other) noexcept
{
    if (this == &other)
	{
		return *this;
	}

	this->release = std::move(other.release);
	this->revision = std::move(other.revision);
	this->releaseIdentified = std::move(other.releaseIdentified);
	return *this;
}

VersionLib::BuildRelease::operator bool() const
{
	return this->releaseIdentified;
}

bool VersionLib::BuildRelease::operator==(const VersionLib::BuildRelease &other)
{
	return this->release == other.release && this->revision == other.revision && this->releaseIdentified == other.releaseIdentified;
}

bool VersionLib::BuildRelease::operator!=(const VersionLib::BuildRelease &other)
{
    return !(*this == other);
}

bool VersionLib::BuildRelease::operator<(const VersionLib::BuildRelease &other)
{
	if (this->releaseIdentified != other.releaseIdentified)
	{
		return false;
	}
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_RELEASE_BUILD_WEIGHT
	return this->getWeight() < VersionLib::calcReleaseWeight(other.release, other.revision);
	#else
	if (this->release < other.release)
	{
		return true;
	}

	if (this->release == other.release && this->revision < other.revision)
	{
		return true;
	}
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_RELEASE_BUILD_WEIGHT
    return false;
}

bool VersionLib::BuildRelease::operator>(const VersionLib::BuildRelease &other)
{
    if (this->releaseIdentified != other.releaseIdentified)
	{
		return false;
	}
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_RELEASE_BUILD_WEIGHT
	return this->getWeight() > VersionLib::calcReleaseWeight(other.release, other.revision);
	#else
	if (this->release > other.release)
	{
		return true;
	}

	if (this->release == other.release && this->revision > other.revision)
	{
		return true;
	}
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_RELEASE_BUILD_WEIGHT
    return false;
}

bool VersionLib::BuildRelease::operator<=(const VersionLib::BuildRelease &other)
{
    if (this->releaseIdentified != other.releaseIdentified)
	{
		return false;
	}
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_RELEASE_BUILD_WEIGHT
	return this->getWeight() <= VersionLib::calcReleaseWeight(other.release, other.revision);
	#else
	if (this->release <= other.release)
	{
		return true;
	}

	if (this->release == other.release && this->revision <= other.revision)
	{
		return true;
	}
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_RELEASE_BUILD_WEIGHT
    return false;
}

bool VersionLib::BuildRelease::operator>=(const VersionLib::BuildRelease &other)
{
    if (this->releaseIdentified != other.releaseIdentified)
	{
		return false;
	}
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_RELEASE_BUILD_WEIGHT
	return this->getWeight() >= VersionLib::calcReleaseWeight(other.release, other.revision);
	#else
	if (this->release >= other.release)
	{
		return true;
	}

	if (this->release == other.release && this->revision >= other.revision)
	{
		return true;
	}
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_RELEASE_BUILD_WEIGHT
    return false;
}
