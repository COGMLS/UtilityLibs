#include "VersionStruct.hpp"

VersionLib::VersionStruct VersionLib::initVersionStruct()
{
	VersionLib::VersionStruct v;

	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_GENERIC_VERSION_DATA
	v.numCompSize = 3;
	v.numeric_components = new unsigned int[v.numCompSize];
	v.compLoc = nullptr;
	#else
	v.major = 0u;
	v.minor = 0u;
	v.patch = 0u;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_GENERIC_VERSION_DATA

	v.build = 0ull;
	#ifndef VERSION_LIB_PURE_CPP_DATA_STRUCT
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	v.build_type = VersionLib::initVersionBuildTypeC();
	#else
	v.build_revision = 0u;
	v.build_type = VERSION_LIB_DEFAULT_BUILD_RELEASE_TYPE_INIT;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	#endif // !VERSION_LIB_PURE_CPP_DATA_STRUCT

	v.compare_build = false;
	v.versionType = VersionLib::VersionType::UNKNOWN_VERSION_TYPE;

	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_METADATA_CLASS
	v.metadata = nullptr;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_METADATA_CLASS
    
	return v;
}

int VERSION_LIB_API VersionLib::destroyVersionStruct(VersionLib::VersionStruct &versionData)
{
	int status = 0;

	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_GENERIC_VERSION_DATA
	// Delete the numeric values:
	if (versionData.numeric_components != nullptr)
	{
		try
		{
			delete[] versionData.numeric_components;
			versionData.numeric_components = nullptr;
			versionData.numCompSize = 0;
		}
		catch(const std::exception&)
		{
			status += 1;
		}
	}

	// Delete the components location:
	if (versionData.compLoc != nullptr)
	{
		try
		{
			delete[] versionData.compLoc;
			versionData.compLoc = nullptr;
		}
		catch(const std::exception&)
		{
			status += 2;
		}
	}
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_GENERIC_VERSION_DATA

	#ifndef VERSION_LIB_PURE_CPP_DATA_STRUCT
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	if (versionData.build_type.releases != nullptr)
	{
		if (!VersionLib::destroyVersionBuildTypeC(versionData.build_type))
		{
			status += 4;
		}
	}
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	#endif // !VERSION_LIB_PURE_CPP_DATA_STRUCT

	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_METADATA_CLASS
	if (versionData.metadata != nullptr)
	{
		try
		{
			#ifdef VERSION_LIB_PURE_CPP_DATA_STRUCT
			delete versionData.metadata;
			#else
			delete[] versionData.metadata;
			#endif // !VERSION_LIB_PURE_CPP_DATA_STRUCT
			versionData.metadata = nullptr;
		}
		catch(const std::exception&)
		{
			status += 8;
		}
	}
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_METADATA_CLASS

	versionData.versionType = VersionLib::VersionType::UNKNOWN_VERSION_TYPE;

	return status;
}
