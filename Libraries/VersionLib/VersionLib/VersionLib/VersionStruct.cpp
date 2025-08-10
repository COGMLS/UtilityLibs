#include "VersionStruct.hpp"

VersionLib::VersionStruct VersionLib::initVersionStruct()
{
	VersionLib::VersionStruct v;

	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_GENERIC_VERSION_DATA
	v.compLoc = nullptr;
	#else
	v.major = 0u;
	v.minor = 0u;
	v.patch = 0u;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_GENERIC_VERSION_DATA

	v.build = 0ull;

	v.compare_build = false;
	v.versionType = VersionLib::VersionType::UNKNOWN_VERSION_TYPE;
    
	return v;
}

int VERSION_LIB_API VersionLib::destroyVersionStruct(VersionLib::VersionStruct &versionData)
{
	int status = 0;

	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_GENERIC_VERSION_DATA
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

	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_METADATA_CLASS
	//if (versionData.metadata != nullptr)
	//{
	//	try
	//	{
	//		versionData.metadata.reset(nullptr);
	//	}
	//	catch(const std::exception&)
	//	{
	//		status += 8;
	//	}
	//}
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_METADATA_CLASS

	versionData.versionType = VersionLib::VersionType::UNKNOWN_VERSION_TYPE;

	return status;
}

bool VersionLib::chkVersionStructFlg(const VersionLib::VersionStruct &versionData, std::bitset<4> flags)
{
	return (versionData.flags & flags).to_ulong() > 0ul;
}

void VersionLib::enableVersionStructFlg(VersionLib::VersionStruct &versionData, std::bitset<4> flags)
{
	versionData.flags = versionData.flags & flags;
}

void VersionLib::disableVersionStructFlg(VersionLib::VersionStruct &versionData, std::bitset<4> flags)
{
	versionData.flags =  versionData.flags & ~flags;
}

void VersionLib::applyVersionStructFlg(VersionLib::VersionStruct &versionData, std::bitset<4> flags)
{
	versionData.flags = flags;
}
