#pragma once

#ifndef RELEASE_TYPE_TOOLS_HPP
#define RELEASE_TYPE_TOOLS_HPP

#include "ExperimentalFeatures.hpp"

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT

#include "BuildTypes.hpp"

#include <cmath>
#include <vector>

namespace VersionLib
{
	/**
	 * @brief Get the BuildType weight for enumerator values
	 * @param type Build release type value
	 * @return Return the curresponding weight for the actual BuildType
	 */
	VERSION_LIB_API unsigned short getBuildTypeWeight (VersionLib::BuildType type);

	/**
	 * @brief Calculate the build release weight to mitigate the difficulty to determinate the composed releases
	 * @param build_release Build release type
	 * @param revision Release revision
	 * @param position Relative release information position. Example: alpha.beta (alpha is first position and beta is the second). If there is only one release information, it will be used 1.
	 * @return Return relative weight for release information
	 * @note The release build information is a numeric value that must be equal or higher of 2
	 * @note Revision can be zero
	 * @note Position should always be equal or higher than 1
	 * @exception If build_release is less than 2
	 * @exception If position is less than 1
	 * @note TO SEE MORE DETAILS ON HOW THE WEIGHT IS CALCULATED, CHECK THE DOCUMENTATION FILE
	 */
	VERSION_LIB_API float calcReleaseWeight (VersionLib::BuildType build_release, unsigned short revision, unsigned short position = 1);

	/**
	 * @brief Calculate the final weight of all pre calculated weights, using a arithmetic mean
	 * @param weights Weight array
	 * @return Final weight to determinate the release build
	 * @note If only one weight is available, will return the unique value to reduce CPU cycles
	 * @exception No data to process exception is returned is the vector is empty
	 */
	VERSION_LIB_API float calcFullReleaseWeight (std::vector<float> weights);
}
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT

#endif // !RELEASE_TYPE_TOOLS_HPP