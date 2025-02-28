#include "VersionStruct.hpp"

VersionLib::VersionStruct VersionLib::initVersionStruct()
{
	VersionLib::VersionStruct v;
	
	v.major = 0u;
	v.minor = 0u;
	v.patch = 0u;
	v.build = 0ull;
	v.build_type_number = 0u;
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	v.build_type = VersionLib::initVersionBuildTypeC();
	#else
	v.build_type = VersionLib::BuildType::ALPHA;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	v.compare_build = false;
    
	return v;
}