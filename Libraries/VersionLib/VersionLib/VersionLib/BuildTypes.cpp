#include "BuildTypes.hpp"

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
VersionLib::VersionBuildTypeC VersionLib::initVersionBuildTypeC()
{
    VersionLib::VersionBuildTypeC buildType;

	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
	buildType.size = 1;
	buildType.releases = new VersionLib::VersionReleaseData[buildType.size];
	buildType.releases[0] = VersionLib::initVersionReleaseDataC();
	#else
	buildType.type = VERSION_LIB_DEFAULT_BUILD_RELEASE_TYPE_INIT;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE

	return buildType;
}

bool VersionLib::destroyVersionBuildTypeC(VersionLib::VersionBuildTypeC &build_type)
{
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
	try
	{
		if (build_type.releases != nullptr)
		{
			delete[] build_type.releases;
			build_type.releases = nullptr;
			build_type.size = 0;
		}
		return true;
	}
	catch(const std::exception&)
	{
		return false;
	}
	#else
	return true;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
}

bool VersionLib::setVersionBuildTypeC(VersionLib::VersionBuildTypeC &buildTypeStruct, VersionLib::BuildType build_type, unsigned short revision)
{
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
	try
	{
		if (buildTypeStruct.size != 1 || buildTypeStruct.releases == nullptr)
		{
			destroyVersionBuildTypeC(buildTypeStruct);
			buildTypeStruct.size = 1;
			buildTypeStruct.releases = new VersionLib::VersionReleaseData[buildTypeStruct.size];
		}
	
		buildTypeStruct.releases[0].release = build_type;
		buildTypeStruct.releases[0].revision = revision;
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
bool VersionLib::setVersionBuildTypeC(VersionLib::VersionBuildTypeC &buildTypeStruct, VersionLib::VersionReleaseData* build_type, unsigned short size)
{
    if (build_type == nullptr || size == 0)
	{
		return false;
	}

	if (buildTypeStruct.releases != nullptr)
	{
		VersionLib::destroyVersionBuildTypeC(buildTypeStruct);
	}

	try
	{
		if (buildTypeStruct.releases != nullptr)
		{
			return false;
		}

		buildTypeStruct.size = size;
		buildTypeStruct.releases = new VersionLib::VersionReleaseData[buildTypeStruct.size];

		for (unsigned int i = 0; i < buildTypeStruct.size; i++)
		{
			buildTypeStruct.releases[i] = build_type[i];
		}

		return true;
	}
	catch(const std::exception& e)
	{
		return false;
	}
}
VersionLib::VersionReleaseData VersionLib::initVersionReleaseDataC()
{
	VersionLib::VersionReleaseData release;

	release.release = VERSION_LIB_DEFAULT_BUILD_RELEASE_TYPE_INIT;
	release.revision = 0;
	release.releaseIdentified = false;

    return release;
}
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE

#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT