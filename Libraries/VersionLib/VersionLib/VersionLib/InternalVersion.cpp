#include "InternalVersion.hpp"

VersionLib::VersionData VersionLib::internalVersionData()
{
	VersionLib::BuildType type = VersionLib::str2BuildType(VERSION_LIB_VERSION_INFO_BUILD_TYPE);

	VersionLib::VersionData version(
										VERSION_LIB_VERSION_INFO_MAJOR_VERSION,
										VERSION_LIB_VERSION_INFO_MINOR_VERSION,
										VERSION_LIB_VERSION_INFO_PATCH_VERSION,
										type,
										VERSION_LIB_VERSION_INFO_BUILD_TYPE_NUMBER,
										VERSION_LIB_VERSION_INFO_BUILD_NUMBER
									);
	return version;
}

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SEMVER_CLASS
VersionLib::SemVer VersionLib::internalSemVer()
{
	VersionLib::BuildType type = VersionLib::str2BuildType(VERSION_LIB_VERSION_INFO_BUILD_TYPE);

	VersionLib::SemVer version(
										VERSION_LIB_VERSION_INFO_MAJOR_VERSION,
										VERSION_LIB_VERSION_INFO_MINOR_VERSION,
										VERSION_LIB_VERSION_INFO_PATCH_VERSION,
										type,
										VERSION_LIB_VERSION_INFO_BUILD_TYPE_NUMBER,
										VERSION_LIB_VERSION_INFO_BUILD_NUMBER
									);
	return version;
};
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SEMVER_CLASS