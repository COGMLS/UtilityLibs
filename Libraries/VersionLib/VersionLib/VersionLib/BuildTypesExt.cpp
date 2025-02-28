#include "BuildTypesExt.hpp"

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
VersionLib::VersionBuildType::VersionBuildType()
{

}

VersionLib::VersionBuildType::VersionBuildType(std::string build_type_str)
{

}
VersionLib::VersionBuildType::VersionBuildType(VersionLib::BuildType build_type)
{

}
#else
VersionLib::VersionBuildType::VersionBuildType()
{
	this->type = VersionLib::BuildType::ALPHA;
}

VersionLib::VersionBuildType::VersionBuildType(std::string build_type_str)
{
	
}
VersionLib::VersionBuildType::VersionBuildType(VersionLib::BuildType build_type)
{

}
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE

VersionLib::VersionBuildType::~VersionBuildType()
{
}

VersionLib::BuildType VersionLib::VersionBuildType::getBuildType()
{
    return VersionLib::BuildType();
}

std::string VersionLib::VersionBuildType::getBuildTypeStr(bool useShortStr)
{
    return std::string();
}

VersionLib::VersionBuildTypeC VersionLib::VersionBuildType::toStruct()
{
    return VersionLib::VersionBuildTypeC();
}

bool VersionLib::VersionBuildType::operator==(VersionLib::VersionBuildType &other)
{
    return false;
}

bool VersionLib::VersionBuildType::operator!=(VersionLib::VersionBuildType &other)
{
    return false;
}

bool VersionLib::VersionBuildType::operator<(VersionLib::VersionBuildType &other)
{
    return false;
}

bool VersionLib::VersionBuildType::operator>(VersionLib::VersionBuildType &other)
{
    return false;
}

bool VersionLib::VersionBuildType::operator<=(VersionLib::VersionBuildType &other)
{
    return false;
}

bool VersionLib::VersionBuildType::operator>=(VersionLib::VersionBuildType &other)
{
    return false;
}

VersionLib::VersionBuildTypeC VERSION_LIB_API VersionLib::initVersionBuildTypeC()
{
    VersionLib::VersionBuildTypeC buildType;

	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
	buildType.size = 1;
	buildType.types = new VersionLib::BuildType[buildType.size];
	buildType.types[0] = VersionLib::BuildType::ALPHA;
	#else
	buildType.type = VersionLib::BuildType::ALPHA;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE

	return buildType;
}

#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT