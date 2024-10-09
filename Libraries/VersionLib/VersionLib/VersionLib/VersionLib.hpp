#pragma once

#ifndef VERSION_HPP
#define VERSION_HPP

#ifdef WIN32
	#ifdef VERSION_LIB_EXPORTS
		#define VERSION_LIB_API __declspec(dllexport)
	#else
		#define VERSION_LIB_API __declspec(dllimport)
	#endif //!VERSION_LIB_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#else
	#if __GNUC__ >= 4
		#ifdef VERSION_LIB_EXPORTS
			#define VERSION_LIB_API __attribute__((visibility("default")))
		#else
			#define VERSION_LIB_API __attribute__((visibility("default")))
		#endif //!VERSION_LIB_EXPORTS
	#else
		#ifdef VERSION_LIB_EXPORTS
			#define VERSION_LIB_API
		#else
			#define VERSION_LIB_API
		#endif //!VERSION_LIB_EXPORTS
	#endif
#endif // !WIN32

#include "BuildTypes.hpp"
#include "Tools.hpp"
#include "VersionClass.hpp"
#include "VersionStruct.hpp"

namespace VersionLib
{
	//extern const VersionData internalVersionData(0, 8, 1, 18, VersionLib::BuildType::BETA, 0);
	inline VersionData internalVersionData()
	{
		return VersionLib::VersionData(0, 8, 2, 23, VersionLib::BuildType::BETA, 0);
	}
}

#endif // !VERSION_HPP