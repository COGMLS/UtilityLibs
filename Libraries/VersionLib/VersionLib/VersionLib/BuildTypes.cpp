#include "BuildTypes.hpp"

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
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

void VersionLib::destroyVersionBuildTypeC(VersionLib::VersionBuildTypeC &build_type)
{
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
	if (build_type.types != nullptr)
	{
		delete[] build_type.types;
		build_type.types = nullptr;
		build_type.size = 0;
	}
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
}

void VersionLib::setVersionBuildTypeC(VersionLib::VersionBuildTypeC &buildTypeStruct, VersionLib::BuildType build_type)
{
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
	if (buildTypeStruct.size != 1 || buildTypeStruct.types == nullptr)
	{
		destroyVersionBuildTypeC(buildTypeStruct);
		buildTypeStruct.size = 1;
		buildTypeStruct.types = new VersionLib::BuildType[buildTypeStruct.size];
	}

	buildTypeStruct.types[0] = build_type;
	#else
	buildTypeStruct.type = build_type;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
}
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT