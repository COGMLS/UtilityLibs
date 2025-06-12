#include "CommonTools.hpp"

std::string VersionLib::tolower_str(const std::string &value)
{
	std::string tmp;
	char c = '\0';
	for (size_t i = 0; i < value.size(); i++)
	{
		c = value[i];

		if (std::isupper(c))
		{
			tmp += std::tolower(c);
		}
		else
		{
			tmp += c;
		}
	}
	return tmp;
}

unsigned int VersionLib::extractBuildTypeNumber(std::string buildType)
{
	buildType = VersionLib::tolower_str(buildType);
	char* cValue = const_cast<char*>(buildType.c_str());
	const char token[] = ".";
	char* cStr = std::strtok(cValue, token);
	bool foundBuildType = false;
	unsigned int build_revision = 0;
	while (token)
	{
		if (foundBuildType)
		{
			try
			{
				build_revision = std::stoul(token);
			}
			catch(const std::exception&)
			{
				build_revision = 0;
			}
		}
		if (std::strcmp(token, "alpha") == 0 || std::strcmp(token, "a") == 0)
		{
			foundBuildType = true;
		}

		if (std::strcmp(token, "beta") == 0 || std::strcmp(token, "b") == 0)
		{
			foundBuildType = true;
		}

		if (std::strcmp(token, "release candidate") == 0 || std::strcmp(token, "release_candidate") == 0 || std::strcmp(token, "rc") == 0)
		{
			foundBuildType = true;
		}

		if (std::strcmp(token, "release") == 0 || std::strcmp(token, "") == 0)
		{
			foundBuildType = true;
		}
	}

    return build_revision;
}

std::string VersionLib::buildType2Str(BuildType type, bool useShortStr, bool showReleaseType)
{
	switch (type)
	{
		case BuildType::ALPHA:
		{
			if (useShortStr)
			{
				return std::string("a");
			}

			return std::string("alpha");
		}
		case BuildType::BETA:
		{
			if (useShortStr)
			{
				return std::string("b");
			}

			return std::string("beta");
		}
		case BuildType::RELEASE_CANDIDATE:
		{
			if (useShortStr)
			{
				return std::string("rc");
			}

			return std::string("release candidate");
		}
		case BuildType::RELEASE:
		{
			if (showReleaseType)
			{
				if (useShortStr)
				{
					return std::string("r");
				}
	
				return std::string("release");
			}

			return std::string();
		}

		//
		// Non standard build types:
		//

		case BuildType::PRE_ALPHA:
		{
			return std::string("pre-alpha");
		}
		case BuildType::PRE_BETA:
		{
			return std::string("pre-beta");
		}
		case BuildType::DEVELOPMENT:
		{
			if (showReleaseType)
			{
				return std::string("dev");
			}
			return std::string("development");
		}
		case BuildType::PRE_RELEASE:
		{
			return std::string("pre-release");
		}
		default:
		{
			return std::string();
		}
	}
}

VersionLib::BuildType VersionLib::str2BuildType(std::string value)
{
	value = VersionLib::tolower_str(value);

	if (value.starts_with('"') || value.starts_with('\''))
	{
		value = value.erase(0, 1);
	}

	if (value.ends_with('"') || value.ends_with('\''))
	{
		value = value.erase(value.size() - 1, 1);
	}

	if (value == "alpha" || value == "a")
	{
		return BuildType::ALPHA;
	}

	if (value == "beta" || value == "b")
	{
		return BuildType::BETA;
	}

	if (value == "release candidate" || value == "release_candidate" || value == "rc")
	{
		return BuildType::RELEASE_CANDIDATE;
	}

	if (value == "" || value.empty() || value == "release")
	{
		return BuildType::RELEASE;
	}

	//
	// Non standard build types:
	//
	
	if (value == "pre-alpha")
	{
		return BuildType::PRE_ALPHA;
	}
	
	if (value == "pre-beta")
	{
		return BuildType::PRE_BETA;
	}

	if (value == "canary")
	{
		return BuildType::CANARY;
	}
	
	if (value == "development" || value == "dev")
	{
		return BuildType::DEVELOPMENT;
	}
	
	if (value == "pre-release")
	{
		return BuildType::PRE_RELEASE;
	}
	
	return BuildType::NOT_DETECTED;
}
