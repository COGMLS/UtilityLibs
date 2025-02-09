#include "VersionStruct.hpp"

VersionLib::VersionStruct VersionLib::initVersionStruct()
{
	VersionLib::VersionStruct v;
	
	v.major = 0u;
	v.minor = 0u;
	v.patch = 0u;
	v.build = 0ull;
	v.build_type_number = 0u;
	v.build_type = VersionLib::BuildType::ALPHA;
	v.compare_build = false;
    
	return v;
}