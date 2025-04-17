#include "BuildTypes.hpp"

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
VersionLib::VersionBuildTypeC VersionLib::initVersionBuildTypeC()
{
    VersionLib::VersionBuildTypeC buildType;

	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
	buildType.size = 1;
	buildType.releases = new VersionLib::VersionReleaseDataC[buildType.size];
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
			buildTypeStruct.releases = new VersionLib::VersionReleaseDataC[buildTypeStruct.size];
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
bool VersionLib::setVersionBuildTypeC(VersionLib::VersionBuildTypeC &buildTypeStruct, VersionLib::VersionReleaseDataC* build_type, unsigned short size)
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
		buildTypeStruct.releases = new VersionLib::VersionReleaseDataC[buildTypeStruct.size];

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
VersionLib::VersionReleaseDataC VersionLib::initVersionReleaseDataC()
{
	VersionLib::VersionReleaseDataC release;

	release.release = VERSION_LIB_DEFAULT_BUILD_RELEASE_TYPE_INIT;
	release.revision = 0;
	release.releaseIdentified = false;

    return release;
}

unsigned short VersionLib::getBuildTypeWeight(VersionLib::BuildType type)
{
	switch (type)
	{
		case VersionLib::BuildType::PRE_ALPHA:
		{
			return 2;
		}
		case VersionLib::BuildType::ALPHA:
		case VersionLib::BuildType::CANARY:
		{
			return 3;
		}
		case VersionLib::BuildType::PRE_BETA:
		{
			return 4;
		}
		case VersionLib::BuildType::BETA:
		case VersionLib::BuildType::DEVELOPMENT:
		{
			return 5;
		}
		case VersionLib::BuildType::RELEASE_CANDIDATE:
		case VersionLib::BuildType::PRE_RELEASE:
		{
			return 6;
		}
		default:
		{
			return 7;	// Release
		}
	}
}
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE

#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT