#include "BuildReleaseId.hpp"

VersionLib::BuildRelease::BuildRelease()
{
	this->release = VERSION_LIB_DEFAULT_BUILD_RELEASE_TYPE_INIT;
	this->revision = 0;
	this->releaseIdentified = true;
}

VersionLib::BuildRelease::BuildRelease(std::string release)
{
	std::vector<VersionLib::BuildRelease> types = VersionLib::findAndGetBuildTypes(release);
	if (types.empty())
	{
		this->release = VERSION_LIB_DEFAULT_BUILD_RELEASE_TYPE_INIT;
		this->revision = 0;
		this->releaseIdentified = false;
	}
	else
	{
		this->release = types[0].release;
		this->revision = types[0].revision;
		this->releaseIdentified = types[0].releaseIdentified;
	}
}

VersionLib::BuildRelease::BuildRelease(VersionLib::BuildType release, unsigned short revision)
{
	this->release = release;
	this->revision = revision;
	this->releaseIdentified = true;
}

VersionLib::BuildRelease::BuildRelease(VersionLib::VersionReleaseData &build_release)
{
	this->release = build_release.release;
	this->revision = build_release.revision;
	this->releaseIdentified = build_release.releaseIdentified;
}

VersionLib::BuildRelease::BuildRelease(const VersionLib::BuildRelease &other)
{
	this->release = other.release;
	this->revision = other.revision;
	this->releaseIdentified = other.releaseIdentified;
}

VersionLib::BuildRelease::BuildRelease(VersionLib::BuildRelease &&other) noexcept
{
	this->release = std::move(other.release);
	this->revision = std::move(other.revision);
	this->releaseIdentified = std::move(other.releaseIdentified);
}

VersionLib::BuildRelease::~BuildRelease()
{
}

VersionLib::BuildType VersionLib::BuildRelease::getRelease()
{
    return this->release;
}

unsigned short VersionLib::BuildRelease::getRevision()
{
    return this->revision;
}

float VersionLib::BuildRelease::getWeight(unsigned short pos)
{
	return VersionLib::calcReleaseWeight(this->release, this->revision, pos);
}

bool VersionLib::BuildRelease::isReleaseInfoOk()
{
    return this->releaseIdentified;
}

std::string VersionLib::BuildRelease::toString(bool useShortStr, bool showReleaseType)
{
	std::string tmp;

	if (this->release == VersionLib::BuildType::RELEASE && !showReleaseType)
	{
		return tmp;
	}

	tmp = VersionLib::buildType2Str(this->release, useShortStr, showReleaseType);

	if (this->revision > 0)
	{
		tmp += "." + std::to_string(this->revision);
	}

    return tmp;
}

VersionLib::VersionReleaseData VersionLib::BuildRelease::toReleaseDataC()
{
	VersionLib::VersionReleaseData tmp = VersionLib::initVersionReleaseDataC();

	tmp.release = this->release;
	tmp.revision = this->revision;
	tmp.releaseIdentified = this->releaseIdentified;

	return tmp;
}

VersionLib::BuildRelease &VersionLib::BuildRelease::operator=(const VersionLib::BuildRelease &other)
{
	this->release = other.release;
	this->revision = other.revision;
	this->releaseIdentified = other.releaseIdentified;
	return *this;
}

VersionLib::BuildRelease &VersionLib::BuildRelease::operator=(VersionLib::BuildRelease &&other) noexcept
{
    if (this == &other)
	{
		return *this;
	}

	this->release = std::move(other.release);
	this->revision = std::move(other.revision);
	this->releaseIdentified = std::move(other.releaseIdentified);
	return *this;
}

VersionLib::BuildRelease::operator bool() const
{
	return this->releaseIdentified;
}

bool VersionLib::BuildRelease::operator==(const VersionLib::BuildRelease &other)
{
	return this->release == other.release && this->revision == other.revision && this->releaseIdentified == other.releaseIdentified;
}

bool VersionLib::BuildRelease::operator!=(const VersionLib::BuildRelease &other)
{
    return !(*this == other);
}

bool VersionLib::BuildRelease::operator<(const VersionLib::BuildRelease &other)
{
	if (this->releaseIdentified != other.releaseIdentified)
	{
		return false;
	}
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_RELEASE_BUILD_WEIGHT
	return this->getWeight() < VersionLib::calcReleaseWeight(other.release, other.revision);
	#else
	if (this->release < other.release)
	{
		return true;
	}

	if (this->release == other.release && this->revision < other.revision)
	{
		return true;
	}
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_RELEASE_BUILD_WEIGHT
    return false;
}

bool VersionLib::BuildRelease::operator>(const VersionLib::BuildRelease &other)
{
    if (this->releaseIdentified != other.releaseIdentified)
	{
		return false;
	}
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_RELEASE_BUILD_WEIGHT
	return this->getWeight() > VersionLib::calcReleaseWeight(other.release, other.revision);
	#else
	if (this->release > other.release)
	{
		return true;
	}

	if (this->release == other.release && this->revision > other.revision)
	{
		return true;
	}
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_RELEASE_BUILD_WEIGHT
    return false;
}

bool VersionLib::BuildRelease::operator<=(const VersionLib::BuildRelease &other)
{
    if (this->releaseIdentified != other.releaseIdentified)
	{
		return false;
	}
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_RELEASE_BUILD_WEIGHT
	return this->getWeight() <= VersionLib::calcReleaseWeight(other.release, other.revision);
	#else
	if (this->release <= other.release)
	{
		return true;
	}

	if (this->release == other.release && this->revision <= other.revision)
	{
		return true;
	}
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_RELEASE_BUILD_WEIGHT
    return false;
}

bool VersionLib::BuildRelease::operator>=(const VersionLib::BuildRelease &other)
{
    if (this->releaseIdentified != other.releaseIdentified)
	{
		return false;
	}
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_RELEASE_BUILD_WEIGHT
	return this->getWeight() >= VersionLib::calcReleaseWeight(other.release, other.revision);
	#else
	if (this->release >= other.release)
	{
		return true;
	}

	if (this->release == other.release && this->revision >= other.revision)
	{
		return true;
	}
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_RELEASE_BUILD_WEIGHT
    return false;
}

#ifdef VERSION_LIB_PURE_CPP_DATA_STRUCT
std::vector<VersionLib::BuildRelease> VersionLib::findAndGetBuildTypes(std::string &version, long long start, long long end)
#else
std::vector<VersionLib::VersionReleaseData> VersionLib::findAndGetBuildTypes(std::string &version, long long start, long long end)
#endif //!VERSION_LIB_PURE_CPP_DATA_STRUCT
{
	size_t verStrSize = version.size();

	std::string tmp;

	long releaseArrIndex = -1;
	#ifdef VERSION_LIB_PURE_CPP_DATA_STRUCT
	std::vector<VersionLib::BuildRelease> releaseArr;
	#else
	std::vector<VersionLib::VersionReleaseData> releaseArr;
	#endif // !VERSION_LIB_PURE_CPP_DATA_STRUCT
	
	bool foundBuild = false;
	bool foundBuildTypeField = false;
	bool foundMetadataField = false;
	char t = '\0';

	if (start < 0)
	{
		// Throw an exception
	}

	if (end >= version.size())
	{
		// Throw an exception
	}

	if (start > 0 && end < 0)
	{
		start = -1;
	}
	
	if (start < 0 && end < 0)
	{
		size_t buildPos = 0;

		// Keep the additional local variable restrict to if statement:
		if (!foundBuild)
		{
			std::string tmp;
			bool foundAlphaChar = false;
			long long buildStart = -1;
			long long buildEnd = -1;
	
			// Try to find the build compilation information:
			// On permissive string formats, build compilation can appear
			// as a number after a space of version or after the "build" word.
			for (size_t i = version.size() - 1; i >= 0; i--)
			{
				t = version[i];
				
				if (t >= '0' && t <= '9' && !foundAlphaChar)
				{
					buildEnd = i;
				}
	
				if (t == ' ')
				{
					if (buildEnd != -1)
					{
						buildStart = i;
					}
	
					if (foundAlphaChar)
					{
						break;
					}
				}
	
				if (!foundAlphaChar && t >= 'a' && t <= 'z' || t >= 'A' && t <= 'Z')
				{
					foundAlphaChar = true;
					tmp += t;
				}
			}
	
			// Test directly the "build" word to reduce process time:
			if (VersionLib::tolower_str(tmp) == "dliub" || buildStart > 0 && buildEnd != -1)
			{
				foundBuild = true;
				buildPos = buildStart;
			}
		}

		//buildPos = version.find(" build");
		//if (buildPos > 0 && buildPos < verStrSize)
		//{
		//	foundBuild = true;
		//}

		// If didn't found build word, check if there is a numeric build directly:
		if (!foundBuild)
		{
			for (t = '0'; t <= '9'; t++)
			{
				// Check if there is " #" pattern:
				buildPos = version.find(" " + std::to_string(t));
				if (buildPos > 0 && buildPos < verStrSize)
				{
					foundBuild = true;
					break;
				}
			}
		}

		t = '\0';
	
		for (size_t i = 0; i < verStrSize; i++)
		{
			t = version[i];
	
			if (/*foundBuildTypeField && (t >= '0' && t <= '9') || */foundBuildTypeField && (t == ' ' && i + 1 == buildPos) || t == '+')
			{
				break;
			}
	
			if ((t >= 'a' && t <= 'z' || t >= 'A' && t <= 'Z') && !(t == '.' || t == '-'))
			{
				end = i;
	
				if (!foundBuildTypeField)
				{
					foundBuildTypeField = true;
					start = i;
				}
			}
		}
	}

	// If found a possible substring that contains the build type(s) information, extract them:
	if (start > 0 && end > start)
	{
		tmp = version.substr(start, end - start + 1);

		start = -1;
		end = -1;

		std::string tmpBuildType;
		int isRev = 0;	// -1: An exception occurred, 0: Is false, 1: Is true

		for (size_t i = 0; i < tmp.size(); i++)
		{
			t = tmp[i];

			// If detect dot (build type separator) or reach the end of string, try to get the substring:
			if (t == '.' || i + 1 == tmp.size())
			{
				if (start > 0 && end > start)
				{
					if (isRev == 1)
					{
						try
						{
							int rev = std::stoi(tmp.substr(start, end - start + 1));

							if (!releaseArr.empty())
							{
								#ifdef VERSION_LIB_PURE_CPP_DATA_STRUCT
								releaseArr[releaseArrIndex] = VersionLib::BuildRelease(releaseArr[releaseArrIndex].getRelease(), static_cast<unsigned short>(rev));
								#else
								releaseArr[releaseArrIndex].revision = static_cast<unsigned short>(rev);
								releaseArr[releaseArrIndex].releaseIdentified = true;
								#endif // !VERSION_LIB_PURE_CPP_DATA_STRUCT
							}
						}
						catch(const std::exception&)
						{
							isRev = -1;
						}
					}
					
					if (isRev == 0)
					{
						tmpBuildType = tmp.substr(start, end - start + 1);
						#ifdef VERSION_LIB_PURE_CPP_DATA_STRUCT
						VersionLib::BuildRelease release = VersionLib::BuildRelease(tmpBuildType);
						#else
						VersionLib::VersionReleaseData release = VersionLib::initVersionReleaseDataC();
						release.release = VersionLib::str2BuildType(tmpBuildType);
						#endif // !VERSION_LIB_PURE_CPP_DATA_STRUCT
						releaseArr.push_back(release);
						releaseArrIndex++;
					}
					
					// Reset the status:
					start = -1;
					end = -1;
					isRev = 0;
				}
			}

			// Detect all valid characters used by build type:
			if (t >= 'a' && t <= 'z' || t >= 'A' && t <= 'Z' || t == ' ')
			{
				end = i;

				if (start < 0)
				{
					start = i;
				}
			}

			// Detect the revision:
			if (t >= '0' && t <= '9')
			{
				end = i;

				if (start < 0)
				{
					start = i;
					isRev = 1;
				}
			}
		}
	}

    return releaseArr;
}