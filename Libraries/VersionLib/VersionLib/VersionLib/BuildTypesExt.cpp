#include "BuildTypesExt.hpp"

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
VersionLib::VersionBuildType::VersionBuildType()
{
    this->types.push_back(VersionLib::ALPHA);
}

VersionLib::VersionBuildType::VersionBuildType(std::vector<VersionLib::BuildType> combined_build_type)
{
    this->types = combined_build_type;
}

VersionLib::VersionBuildType::VersionBuildType(VersionLib::VersionBuildTypeC& combined_build_type)
{
    if (combined_build_type.types != nullptr || combined_build_type.size > 0)
    {
        for (size_t i = 0; i < combined_build_type.size; i++)
        {
            this->types.push_back(combined_build_type.types[i]);
        }
    }
}
#else
VersionLib::VersionBuildType::VersionBuildType()
{
	this->type = VersionLib::BuildType::ALPHA;
}

VersionLib::VersionBuildType::VersionBuildType(std::string build_type_str)
{
	this->type = VersionLib::str2BuildType(build_type_str);
}

VersionLib::VersionBuildType::VersionBuildType(VersionLib::BuildType build_type)
{
    this->type = build_type;
}
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE

VersionLib::VersionBuildType::VersionBuildType(const VersionLib::VersionBuildType &other)
{
    #ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
    this->types = other.types;
    #else
    this->type = other.type;
    #endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
}

VersionLib::VersionBuildType::VersionBuildType(VersionLib::VersionBuildType &&other) noexcept
{
    #ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
    this->types = std::move(other.types);
    #else
    this->type = std::move(other.type);
    #endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
}

VersionLib::VersionBuildType::~VersionBuildType()
{
}

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
std::vector<VersionLib::BuildType> VersionLib::VersionBuildType::getBuildType()
{
    return this->types;
}
#else
VersionLib::BuildType VersionLib::VersionBuildType::getBuildType()
{
    return this->type;
}
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE

std::string VersionLib::VersionBuildType::getBuildTypeStr(bool useShortStr)
{
    #ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
    return std::string();
    #else
    return VersionLib::buildType2Str(this->type, useShortStr);
    #endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
}

VersionLib::VersionBuildTypeC VersionLib::VersionBuildType::toStruct()
{
    #ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
    VersionLib::VersionBuildTypeC buildType = VersionLib::initVersionBuildTypeC();
    VersionLib::setVersionBuildTypeC(buildType, this->types.data(), this->types.size());
    return buildType;
    #else
    VersionLib::VersionBuildTypeC buildType = VersionLib::initVersionBuildTypeC();
    VersionLib::setVersionBuildTypeC(buildType, this->type);
    return buildType;
    #endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
}

VersionLib::VersionBuildType &VersionLib::VersionBuildType::operator=(const VersionLib::VersionBuildType &other)
{
    #ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
    this->types = other.types;
    #else
    this->type = other.type;
    #endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
    return *this;
}

VersionLib::VersionBuildType &VersionLib::VersionBuildType::operator=(VersionLib::VersionBuildType &&other) noexcept
{
    #ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
    this->types = std::move(other.types);
    #else
    this->type = std::move(other.type);
    #endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
    return *this;
}

VersionLib::VersionBuildType &VersionLib::VersionBuildType::operator=(const VersionLib::BuildType& type)
{
    #ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
    this->types.clear();
    this->types.push_back(type);
    #else
    this->type = type;
    #endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
    return *this;
}

VersionLib::VersionBuildType &VersionLib::VersionBuildType::operator=(const VersionLib::VersionBuildTypeC &type)
{
    #ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
    #else
    #endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
    return *this;
}

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
VersionLib::VersionBuildType &VersionLib::VersionBuildType::operator=(const std::vector<VersionLib::BuildType> types)
{
    if (!types.empty())
    {
        this->types = types;
    }
    return *this;
}
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE

bool VersionLib::VersionBuildType::operator==(const VersionLib::VersionBuildType &other)
{
    #ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
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
    #else
    return this->type == other.type;
    #endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
}

bool VersionLib::VersionBuildType::operator!=(const VersionLib::VersionBuildType &other)
{
    return !(*this == other);
}

bool VersionLib::VersionBuildType::operator<(const VersionLib::VersionBuildType &other)
{
    #ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
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
    #else
    return this->type < other.type;
    #endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
}

bool VersionLib::VersionBuildType::operator>(const VersionLib::VersionBuildType &other)
{
    #ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
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
    #else
    return this->type > other.type;
    #endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
}

bool VersionLib::VersionBuildType::operator<=(const VersionLib::VersionBuildType &other)
{
    #ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
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
    #else
    return this->type <= other.type;
    #endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
}

bool VersionLib::VersionBuildType::operator>=(const VersionLib::VersionBuildType &other)
{
    #ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
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
    #else
    return this->type >= other.type;
    #endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
}

bool VersionLib::VersionBuildType::operator==(const VersionLib::BuildType &other)
{
    #ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
    if (this->types.size() > 1 || this->types.empty())
    {
        return false;
    }
    return this->types[0] == other;
    #else
    return this->type == other;
    #endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
}

bool VersionLib::VersionBuildType::operator!=(const VersionLib::BuildType &other)
{
    return !(*this == other);
}

bool VersionLib::VersionBuildType::operator<(const VersionLib::BuildType &other)
{
    #ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
    if (this->types.size() > 1 || this->types.empty())
    {
        return false;
    }
    return this->types[0] < other;
    #else
    return this->type < other;
    #endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
}

bool VersionLib::VersionBuildType::operator>(const VersionLib::BuildType &other)
{
    #ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
    if (this->types.size() > 1 || this->types.empty())
    {
        return false;
    }
    return this->types[0] > other;
    #else
    return this->type > other;
    #endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
}

bool VersionLib::VersionBuildType::operator<=(const VersionLib::BuildType &other)
{
    #ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
    if (this->types.size() > 1 || this->types.empty())
    {
        return false;
    }
    return this->types[0] <= other;
    #else
    return this->type <= other;
    #endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
}

bool VersionLib::VersionBuildType::operator>=(const VersionLib::BuildType &other)
{
    #ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
    if (this->types.size() > 1 || this->types.empty())
    {
        return false;
    }
    return this->types[0] >= other;
    #else
    return this->type >= other;
    #endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
}

#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT