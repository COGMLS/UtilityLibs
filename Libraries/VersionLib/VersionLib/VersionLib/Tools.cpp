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

VersionLib::VersionStruct VersionLib::toVersionStruct(std::string version)
{
	VersionLib::VersionStruct v;

	/** tokens - positions used:
	 * 0: Major version
	 * 1: Minor version
	 * 2; Patch version
	 * 3: Build type
	 * 4: Build Type Number
	 * 5: Build Number
	 */
	std::vector<std::string> tokens;

	version = VersionLib::tolower_str(version);

	const char delimiters[] = ".- ";
	char* cVersion = const_cast<char*>(version.c_str());
	char* token = std::strtok(cVersion, delimiters);

	size_t rcPos = version.find("release candidate");

	if (rcPos > 0 && rcPos < version.size())
	{
		std::string tmp = version.replace(rcPos, std::strlen("release candidate"), "release_candidate");
		version = tmp;
	}

	while (token)
	{
		tokens.push_back(token);
		token = std::strtok(nullptr, delimiters);
	}

	bool foundMajorVer = false;
	bool foundMinorVer = false;
	bool foundPatchVer = false;
	bool foundTypeVer = false;
	bool foundTypeNum = false;
	bool foundBuild = false;
	bool foundBuildName = false;

	unsigned int major = 0;
	unsigned int minor = 0;
	unsigned int patch = 0;
	std::string type = "";
	VersionLib::BuildType typeEnum;
	unsigned int type_num = 0;
	unsigned long long build = 0;

	for (size_t i = 0; i < tokens.size(); i++)
	{
		if (tokens[i].starts_with(' '))
		{
			tokens[i] = tokens[i].erase(0, 1);
		}

		if (tokens[i].ends_with(' '))
		{
			tokens[i] = tokens[i].erase(tokens[i].size() - 1, 1);
		}

		if (!foundBuild && (foundBuildName || foundTypeNum))
		{
			try
			{
				build = std::stoull(tokens[i]);
				foundBuild = true;
			}
			catch(const std::exception&)
			{
				
			}
		}

		if (!foundBuildName && tokens[i] == "build")
		{
			foundBuildName = true;
		}

		if ((foundPatchVer || foundTypeVer) && !foundTypeNum && (!foundBuild || !foundBuildName))
		{
			try
			{
				type_num = std::stoull(tokens[i]);
				foundTypeNum = true;
			}
			catch(const std::exception&)
			{
				
			}
		}

		if (!foundTypeVer)
		{
			if (
					tokens[i] == "alpha" || tokens[i] == "a" || 
					tokens[i] == "beta" || tokens[i] == "b" || 
					tokens[i] == "release_candidate" || tokens[i] == "rc"
				)
			{
				typeEnum = VersionLib::str2BuildType(tokens[i]);
				type = tokens[i];
				foundTypeVer = true;
			}
		}

		if (foundMajorVer && foundMinorVer && !foundPatchVer)
		{
			try
			{
				patch = std::stoul(tokens[i].c_str());
				foundPatchVer = true;
			}
			catch(const std::exception&)
			{
				
			}
		}

		if (foundMajorVer && !foundMinorVer)
		{
			try
			{
				minor = std::stoul(tokens[i].c_str());
				foundMinorVer = true;
			}
			catch(const std::exception&)
			{
				
			}
		}

		if (!foundMajorVer)
		{
			try
			{
				major = std::stoul(tokens[i].c_str());
				foundMajorVer = true;
			}
			catch(const std::exception&)
			{

			}
		}
	}

	v.major = major;
	v.minor = minor;
	v.patch = patch;
	v.build_type = typeEnum;
	v.build_type_number = type_num;
	v.build = build;

	return v;
}
