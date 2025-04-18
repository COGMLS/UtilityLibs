#include "ReleaseTools.hpp"

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT

float VersionLib::calcReleaseWeight(VersionLib::BuildType build_release, unsigned short revision, unsigned short position)
{
	if (position == 0)
	{
		// Throw exception
	}

	unsigned short base = VersionLib::getBuildTypeWeight(build_release);

	if (base < 2)
	{
		// Throw exception
	}

	float k = std::pow(revision + 1.0f / std::pow(position, -1.0f), (1.0f / base));
	
	if (k == 1.0f)
	{
		k = 0.0f;
	}

	float w = std::log(std::pow(base, base) + k) / std::log(base);

	return w;
}

float VersionLib::calcFullReleaseWeight(std::vector<float> weights)
{
	if (weights.empty())
	{
		// throw exception 
	}

	if (weights.size() == 1)
	{
		return weights[0];
	}

	float sum = 0.0f;

	for (float& w : weights)
	{
		sum += w;
	}

	return sum / static_cast<float>(weights.size());
}

#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT