#include "Tools.hpp"

const char *VersionLib::tolower_Cstr(const std::string &value)
{
	std::string tmp;
	std::transform(value.begin(), value.end(), tmp.begin(), [](unsigned char c){return std::tolower(c);});
	return tmp.c_str();
}

std::string VersionLib::tolower_str(const std::string &value)
{
	std::string tmp;
	std::transform(value.begin(), value.end(), tmp.begin(), [](unsigned char c){return std::tolower(c);});
	return tmp;
}

unsigned int VersionLib::extractBuildTypeNumber(const char* buildType)
{
	buildType = VersionLib::tolower_Cstr(buildType);
	char* cValue = const_cast<char*>(buildType);
	const char token[] = ".";
	char* cStr = std::strtok(cValue, token);
	bool foundBuildType = false;
	unsigned int build_type_number = 0;
	while (token)
	{
		if (foundBuildType)
		{
			try
			{
				build_type_number = std::stoul(token);
			}
			catch(const std::exception&)
			{
				build_type_number = 0;
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

		if (std::strcmp(token, "release candidate") == 0 || std::strcmp(token, "rc") == 0)
		{
			foundBuildType = true;
		}

		if (std::strcmp(token, "release") == 0 || std::strcmp(token, "") == 0)
		{
			foundBuildType = true;
		}
	}

    return build_type_number;
}

unsigned int VersionLib::extractBuildTypeNumber(std::string buildType)
{
	buildType = VersionLib::tolower_str(buildType);
	char* cValue = const_cast<char*>(buildType.c_str());
	const char token[] = ".";
	char* cStr = std::strtok(cValue, token);
	bool foundBuildType = false;
	unsigned int build_type_number = 0;
	while (token)
	{
		if (foundBuildType)
		{
			try
			{
				build_type_number = std::stoul(token);
			}
			catch(const std::exception&)
			{
				build_type_number = 0;
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

		if (std::strcmp(token, "release candidate") == 0 || std::strcmp(token, "rc") == 0)
		{
			foundBuildType = true;
		}

		if (std::strcmp(token, "release") == 0 || std::strcmp(token, "") == 0)
		{
			foundBuildType = true;
		}
	}

    return build_type_number;
}

std::string VersionLib::buildType2Str(BuildType type, bool useShortStr)
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
		default:
		{
			return std::string();
		}
	}
}

VersionLib::BuildType VersionLib::str2BuildType(std::string value)
{
	value = VersionLib::tolower_str(value);

	if (value == "alpha" || value == "a")
	{
		return BuildType::ALPHA;
	}

	if (value == "beta" || value == "b")
	{
		return BuildType::BETA;
	}

	if (value == "release candidate" || value == "rc")
	{
		return BuildType::RELEASE_CANDIDATE;
	}

	if (value == "" || value.empty() || value == "release")
	{
		return BuildType::RELEASE;
	}
	
	return BuildType::RELEASE;
}