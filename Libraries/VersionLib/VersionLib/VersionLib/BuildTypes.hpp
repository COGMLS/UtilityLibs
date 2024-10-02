#pragma once

#ifndef VERSION_BUILD_TYPE_HPP
#define VERSION_BUILD_TYPE_HPP

namespace VersionLib
{
	/**
	 * @brief Build type identifier
	 */
	enum BuildType : unsigned short
	{
		ALPHA,
		BETA,
		RELEASE_CANDIDATE,
		RELEASE
	};
}

#endif // !VERSION_BUILD_TYPE_HPP