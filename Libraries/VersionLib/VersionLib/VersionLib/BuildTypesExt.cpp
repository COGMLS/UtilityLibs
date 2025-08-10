#include "BuildTypesExt.hpp"

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT

VersionLib::VersionBuildType::VersionBuildType()
{
    this->types.push_back(VersionLib::BuildRelease());
}

VersionLib::VersionBuildType::VersionBuildType(std::vector<VersionLib::BuildRelease> combined_build_type)
{
    this->types = combined_build_type;
}

VersionLib::VersionBuildType::VersionBuildType(VersionLib::VersionBuildTypeC& combined_build_type)
{
    if (combined_build_type.releases != nullptr || combined_build_type.size > 0)
    {
        for (size_t i = 0; i < combined_build_type.size; i++)
        {
            this->types.push_back(combined_build_type.releases[i]);
        }
    }
}

VersionLib::VersionBuildType::VersionBuildType(std::string build_type_str)
{
    if (build_type_str.empty())
    {
        this->types.push_back(VERSION_LIB_DEFAULT_BUILD_RELEASE_TYPE_INIT);
    }
    else
    {
        std::vector<VersionLib::BuildRelease> releases = VersionLib::findAndGetBuildTypes(build_type_str);
        for (size_t i = 0; i < releases.size(); i++)
        {
            this->types.push_back(releases[i]);
        }
    }
}

VersionLib::VersionBuildType::VersionBuildType(VersionLib::BuildType build_type, unsigned short revision)
{
    this->types.push_back(VersionLib::BuildRelease(build_type, revision));
}

VersionLib::VersionBuildType::VersionBuildType(const VersionLib::VersionBuildType &other)
{
    this->types = other.types;
}

VersionLib::VersionBuildType::VersionBuildType(VersionLib::VersionBuildType &&other) noexcept
{
    this->types = std::move(other.types);
}

VersionLib::VersionBuildType::~VersionBuildType()
{
}

std::vector<VersionLib::BuildRelease> VersionLib::VersionBuildType::getBuildType()
{
    return this->types;
}

std::string VersionLib::VersionBuildType::getBuildTypeStr(bool useShortStr, bool showReleaseType)
{
    std::string tmpBuildTypeStr;

    for (size_t i = 0; i < this->types.size(); i++)
    {
        if (i == 0 || i + 1 < this->types.size())
        {
            tmpBuildTypeStr += VersionLib::buildType2Str(this->types[i].getRelease(), useShortStr, showReleaseType);
        }
        else
        {
            tmpBuildTypeStr += "." + VersionLib::buildType2Str(this->types[i].getRelease(), useShortStr, showReleaseType);
        }

        if (this->types[i].getRevision() > 0)
        {
            tmpBuildTypeStr += "." + std::to_string(this->types[i].getRevision());
        }
    }

    return tmpBuildTypeStr;
}

VersionLib::VersionBuildTypeC VersionLib::VersionBuildType::toStruct()
{
    VersionLib::VersionBuildTypeC buildType = VersionLib::initVersionBuildTypeC();
    std::vector<VersionLib::VersionReleaseData> tmp;
    for (size_t i = 0; i < this->types.size(); i++)
    {
        tmp.push_back(this->types[i].toReleaseDataC());
    }
    VersionLib::setVersionBuildTypeC(buildType, tmp.data(), tmp.size());
    return buildType;
}

float VersionLib::VersionBuildType::getBuildTypeWeight()
{
    std::vector<float> weights;

    for (VersionLib::BuildRelease& release : this->types)
    {
        weights.push_back(release.getWeight());
    }

    return VersionLib::calcFullReleaseWeight(weights);
}

VersionLib::VersionBuildType &VersionLib::VersionBuildType::operator=(const VersionLib::VersionBuildType &other)
{
    this->types = other.types;
    return *this;
}

VersionLib::VersionBuildType &VersionLib::VersionBuildType::operator=(VersionLib::VersionBuildType &&other) noexcept
{
    this->types = std::move(other.types);
    return *this;
}

VersionLib::VersionBuildType &VersionLib::VersionBuildType::operator=(const VersionLib::BuildType& type)
{
    this->types.clear();
    this->types.push_back(type);
    return *this;
}

VersionLib::VersionBuildType &VersionLib::VersionBuildType::operator=(const VersionLib::VersionBuildTypeC &types)
{
    #ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
    if (types.releases != nullptr && types.size > 0)
    {
        this->types.clear();
        for (size_t i = 0; i < types.size; i++)
        {
            this->types.push_back(types.releases[i]);
        }
    }
    #else
    this->types.clear();
    this->types.push_back(types.type)
    #endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
    return *this;
}

VersionLib::VersionBuildType &VersionLib::VersionBuildType::operator=(const VersionLib::BuildRelease type)
{
    this->types.clear();
    this->types.push_back(type);
    return *this;
}

VersionLib::VersionBuildType &VersionLib::VersionBuildType::operator=(const std::vector<VersionLib::BuildRelease> types)
{
    this->types = types;
    return *this;
}

bool VersionLib::VersionBuildType::operator==(const VersionLib::VersionBuildType &other)
{
    if ((this->types.size() == 0 || other.types.size() == 0) || (this->types.size() != other.types.size()))
    {
        return false;
    }

    for (size_t i = 0; i < this->types.size(); i++)
    {
        if (this->types[i] != other.types[i])
        {
            return false;
        }
    }

    return true;
}

bool VersionLib::VersionBuildType::operator!=(const VersionLib::VersionBuildType &other)
{
    return !(*this == other);
}

bool VersionLib::VersionBuildType::operator<(const VersionLib::VersionBuildType &other)
{
    if ((this->types.size() == 0 || other.types.size() == 0) || (this->types.size() != other.types.size()))
    {
        return false;
    }

    for (size_t i = 0; i < this->types.size(); i++)
    {
        if (this->types[i] >= other.types[i])
        {
            return false;
        }
    }

    return true;
}

bool VersionLib::VersionBuildType::operator>(const VersionLib::VersionBuildType &other)
{
    if ((this->types.size() == 0 || other.types.size() == 0) || (this->types.size() != other.types.size()))
    {
        return false;
    }

    for (size_t i = 0; i < this->types.size(); i++)
    {
        if (this->types[i] <= other.types[i])
        {
            return false;
        }
    }

    return true;
}

bool VersionLib::VersionBuildType::operator<=(const VersionLib::VersionBuildType &other)
{
    if ((this->types.size() == 0 || other.types.size() == 0) || (this->types.size() != other.types.size()))
    {
        return false;
    }

    for (size_t i = 0; i < this->types.size(); i++)
    {
        if (this->types[i] > other.types[i])
        {
            return false;
        }
    }

    return true;
}

bool VersionLib::VersionBuildType::operator>=(const VersionLib::VersionBuildType &other)
{
    if ((this->types.size() == 0 || other.types.size() == 0) || (this->types.size() != other.types.size()))
    {
        return false;
    }

    for (size_t i = 0; i < this->types.size(); i++)
    {
        if (this->types[i] < other.types[i])
        {
            return false;
        }
    }

    return true;
}

bool VersionLib::VersionBuildType::operator==(const VersionLib::BuildType &other)
{
    if (this->types.size() > 1 || this->types.empty())
    {
        return false;
    }
    return this->types[0] == other;
}

bool VersionLib::VersionBuildType::operator!=(const VersionLib::BuildType &other)
{
    return !(*this == other);
}

bool VersionLib::VersionBuildType::operator<(const VersionLib::BuildType &other)
{
    if (this->types.size() > 1 || this->types.empty())
    {
        return false;
    }
    return this->types[0] < other;
}

bool VersionLib::VersionBuildType::operator>(const VersionLib::BuildType &other)
{
    if (this->types.size() > 1 || this->types.empty())
    {
        return false;
    }
    return this->types[0] > other;
}

bool VersionLib::VersionBuildType::operator<=(const VersionLib::BuildType &other)
{
    if (this->types.size() > 1 || this->types.empty())
    {
        return false;
    }
    return this->types[0] <= other;
}

bool VersionLib::VersionBuildType::operator>=(const VersionLib::BuildType &other)
{
    if (this->types.size() > 1 || this->types.empty())
    {
        return false;
    }
    return this->types[0] >= other;
}

#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT