#include "BuildTypes.hpp"

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
VersionLib::VersionBuildTypeC VersionLib::initVersionBuildTypeC()
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

bool VersionLib::destroyVersionBuildTypeC(VersionLib::VersionBuildTypeC &build_type)
{
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
	try
	{
		if (build_type.types != nullptr)
		{
			delete[] build_type.types;
			build_type.types = nullptr;
			build_type.size = 0;
		}
		return true;
	}
	catch(const std::exception& e)
	{
		return false;
	}
	#else
	return true;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
}

bool VersionLib::setVersionBuildTypeC(VersionLib::VersionBuildTypeC &buildTypeStruct, VersionLib::BuildType build_type)
{
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
	try
	{
		if (buildTypeStruct.size != 1 || buildTypeStruct.types == nullptr)
		{
			destroyVersionBuildTypeC(buildTypeStruct);
			buildTypeStruct.size = 1;
			buildTypeStruct.types = new VersionLib::BuildType[buildTypeStruct.size];
		}
	
		buildTypeStruct.types[0] = build_type;
		return true;
	}
	catch(const std::exception& e)
	{
		return false;
	}
	#else
	buildTypeStruct.type = build_type;
	return true;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
}

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
bool VersionLib::setVersionBuildTypeC(VersionLib::VersionBuildTypeC &buildTypeStruct, VersionLib::BuildType build_type[], unsigned short size)
{
    if (size == 0)
	{
		return false;
	}

	if (buildTypeStruct.types != nullptr)
	{
		VersionLib::destroyVersionBuildTypeC(buildTypeStruct);
	}

	try
	{
		if (buildTypeStruct.types != nullptr)
		{
			return false;
		}

		buildTypeStruct.size = size;
		buildTypeStruct.types = new VersionLib::BuildType[buildTypeStruct.size];

		for (unsigned int i = 0; i < buildTypeStruct.size; i++)
		{
			buildTypeStruct.types[i] = build_type[i];
		}

		return true;
	}
	catch(const std::exception& e)
	{
		return false;
	}
}
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE

#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT