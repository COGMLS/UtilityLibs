#include "VersionClass.hpp"

VersionLib::VersionData::VersionData(std::string versionStr)
{
	VersionLib::VersionStruct v = VersionLib::toVersionStruct2(versionStr);

	this->major = v.major;
	this->minor = v.minor;
	this->patch = v.patch;
	this->build_type = v.build_type;
	this->build_type_number = v.build_type_number;
	this->build = v.build;
}

VersionLib::VersionData::VersionData(unsigned int major, unsigned int minor, unsigned int patch)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = 0;
	this->build_type = VersionLib::BuildType::RELEASE;
	this->build_type_number = 0;
}

VersionLib::VersionData::VersionData(unsigned int major, unsigned int minor, unsigned int patch, unsigned long long build)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = build;
	this->build_type = VersionLib::BuildType::RELEASE;
	this->build_type_number = 0;
}

VersionLib::VersionData::VersionData(unsigned int major, unsigned int minor, unsigned int patch, unsigned long long build, char *build_type)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = build;
	this->build_type = VersionLib::str2BuildType(build_type);
	this->build_type_number = 0;
}

VersionLib::VersionData::VersionData(unsigned int major, unsigned int minor, unsigned int patch, unsigned long long build, std::string build_type)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = build;
	this->build_type = VersionLib::str2BuildType(build_type);
	this->build_type_number = 0;
}

VersionLib::VersionData::VersionData(unsigned int major, unsigned int minor, unsigned int patch, unsigned long long build, VersionLib::BuildType build_type)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = build;
	this->build_type = build_type;
	this->build_type_number = 0;
}

VersionLib::VersionData::VersionData(unsigned int major, unsigned int minor, unsigned int patch, unsigned long long build, char *build_type, unsigned int build_type_number)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = build;
	this->build_type = VersionLib::str2BuildType(build_type);
	this->build_type_number = build_type_number;
}

VersionLib::VersionData::VersionData(unsigned int major, unsigned int minor, unsigned int patch, unsigned long long build, std::string build_type, unsigned int build_type_number)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = build;
	this->build_type = VersionLib::str2BuildType(build_type);
	this->build_type_number = build_type_number;
}

VersionLib::VersionData::VersionData(unsigned int major, unsigned int minor, unsigned int patch, unsigned long long build, VersionLib::BuildType build_type, unsigned int build_type_number)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = build;
	this->build_type = build_type;
	this->build_type_number = build_type_number;
}

VersionLib::VersionData::VersionData(const VersionLib::VersionData &other)
{
	this->major = other.major;
	this->minor = other.minor;
	this->patch = other.patch;
	this->build = other.build;
	this->build_type = other.build_type;
	this->build_type_number = other.build_type_number;
}

VersionLib::VersionData::VersionData(VersionLib::VersionData &&other) noexcept
{
	this->major = std::move(other.major);
	this->minor = std::move(other.minor);
	this->patch = std::move(other.patch);
	this->build = std::move(other.build);
	this->build_type = std::move(other.build_type);
	this->build_type_number = std::move(other.build_type_number);
}

VersionLib::VersionData::~VersionData()
{
}

unsigned int VersionLib::VersionData::getMajor()
{
    return this->major;
}

unsigned int VersionLib::VersionData::getMinor()
{
    return this->minor;
}

unsigned int VersionLib::VersionData::getPatch()
{
    return this->patch;
}

unsigned long long VersionLib::VersionData::getBuild()
{
    return this->build;
}

const char *VersionLib::VersionData::getBuildTypeCstr(bool useShortStr)
{
	std::string verStr = this->getBuildTypeStr(useShortStr);
	size_t strLen = verStr.size();
	char* tmp = new char[strLen];
	#ifdef _MSC_VER
	std::strcpy_s(tmp, strLen, verStr.c_str());
	#else
	std::strcpy(tmp, verStr.c_str());
	#endif // !_MSC_VER
	return const_cast<const char*>(tmp);
}

std::string VersionLib::VersionData::getBuildTypeStr(bool useShortStr)
{
    return VersionLib::buildType2Str(this->build_type, useShortStr);
}

VersionLib::BuildType VersionLib::VersionData::getBuildType()
{
	return this->build_type;
}

unsigned int VersionLib::VersionData::getBuildTypeNumber()
{
    return this->build_type_number;
}

const char *VersionLib::VersionData::getBuildTypeCompleteCstr(bool useShortStr, bool showReleaseType)
{
	std::string verStr = this->getBuildTypeComplete(useShortStr, showReleaseType);
	size_t strLen = verStr.size();
	char* tmp = new char[strLen];
	#ifdef _MSC_VER
	std::strcpy_s(tmp, strLen, verStr.c_str());
	#else
	std::strcpy(tmp, verStr.c_str());
	#endif // !_MSC_VER
	return const_cast<const char*>(tmp);
}

std::string VersionLib::VersionData::getBuildTypeComplete(bool useShortStr, bool showReleaseType)
{
    std::string tmp;

	if (this->build_type == BuildType::RELEASE && !showReleaseType)
	{
		return tmp;
	}

	tmp = this->getBuildTypeStr(useShortStr);

	if (this->build_type_number > 0)
	{
		tmp += "." + std::to_string(this->build_type_number);
	}

	return tmp;
}

std::string VersionLib::VersionData::getVersionStr(bool useShortStr, bool hideBuildWord, bool showReleaseType)
{
	std::string tmp;

	tmp += std::to_string(this->major) + ".";
	tmp += std::to_string(this->minor) + ".";
	tmp += std::to_string(this->patch);
	
	if (this->build_type != BuildType::RELEASE || this->build_type == BuildType::RELEASE && showReleaseType)
	{
		tmp += "-";
	}

	tmp += this->getBuildTypeComplete(useShortStr, showReleaseType);
	tmp += " ";

	if (!hideBuildWord)
	{
		tmp += "build ";
	}

	tmp += std::to_string(this->build);

	return tmp;
}

VersionLib::VersionStruct VersionLib::VersionData::toVersionStruct()
{
	VersionLib::VersionStruct verData;

	verData.major = this->major;
	verData.minor = this->minor;
	verData.patch = this->patch;
	verData.build = this->build;
	verData.build_type = this->build_type;
	verData.build_type_number = this->build_type_number;

	return verData;
}

VersionLib::VersionData &VersionLib::VersionData::operator=(const VersionLib::VersionData &other)
{
	if (this == &other)
	{
		return *this;
	}

	this->major = other.major;
	this->minor = other.minor;
	this->patch = other.patch;
	this->build = other.build;
	this->build_type = other.build_type;
	this->build_type_number = other.build_type_number;

	return *this;
}

VersionLib::VersionData &VersionLib::VersionData::operator=(VersionLib::VersionData &&other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	this->major = std::move(other.major);
	this->minor = std::move(other.minor);
	this->patch = std::move(other.patch);
	this->build = std::move(other.build);
	this->build_type = std::move(other.build_type);
	this->build_type_number = std::move(other.build_type_number);

	return *this;
}

bool VersionLib::VersionData::operator==(const VersionData &other)
{
	if (this->major != other.major)
	{
		return false;
	}

	if (this->minor != other.minor)
	{
		return false;
	}

	if (this->patch != other.patch)
	{
		return false;
	}

	if (this->build != other.build)
	{
		return false;
	}

	if (this->build_type != other.build_type)
	{
		return false;
	}

	if (this->build_type_number != other.build_type_number)
	{
		return false;
	}

    return true;
}

bool VersionLib::VersionData::operator!=(const VersionData &other)
{
    return !(*this == other);
}

bool VersionLib::VersionData::operator>(const VersionData &other)
{
	if (this->major <= other.major && this->minor <= other.minor && this->patch <= other.patch && this->build_type <= other.build_type && this->build_type_number <= other.build_type_number) return false;
	if (this->major <= other.major && this->minor <= other.minor && this->patch <= other.patch && this->build_type < other.build_type) return false;
	if (this->major <= other.major && this->minor <= other.minor && this->patch < other.patch) return false;
	if (this->major <= other.major && this->minor < other.minor) return false;
	if (this->major < other.major) return false;
	return true;
}

bool VersionLib::VersionData::operator>=(const VersionData &other)
{
    if (this->major >= other.major)
	{
		if (this->minor >= other.minor)
		{
			if (this->patch >= other.patch)
			{
				if (this->build_type >= other.build_type)
				{
					if (this->build_type_number >= other.build_type_number)
					{
						return true;
					}
				}
			}
		}
	}

    return false;
}

bool VersionLib::VersionData::operator<(const VersionData &other)
{
	if(this->major >= other.major && this->minor >= other.minor && this->patch >= other.patch && this->build_type >= other.build_type && this->build_type_number >= other.build_type_number) return false;
	if(this->major >= other.major && this->minor >= other.minor && this->patch >= other.patch && this->build_type > other.build_type) return false;
	if(this->major >= other.major && this->minor >= other.minor && this->patch > other.patch) return false;
	if(this->major >= other.major && this->minor > other.minor) return false;
	if(this->major > other.major) return false;
	return true;
}

bool VersionLib::VersionData::operator<=(const VersionData &other)
{
    if (other.major >= this->major)
	{
		if (other.minor >= this->minor)
		{
			if (other.patch >= this->patch)
			{
				if (other.build_type >= this->build_type)
				{
					if (other.build_type_number >= this->build_type_number)
					{
						return true;
					}
				}
			}
		}
	}

    return false;
}

bool VersionLib::VersionData::operator==(const std::string &verStr)
{
    return *this == VersionLib::VersionData(verStr);
}

bool VersionLib::VersionData::operator!=(const std::string &verStr)
{
    return *this != VersionLib::VersionData(verStr);
}

bool VersionLib::VersionData::operator>(const std::string &verStr)
{
    return *this > VersionLib::VersionData(verStr);
}

bool VersionLib::VersionData::operator>=(const std::string &verStr)
{
    return *this >= VersionLib::VersionData(verStr);
}

bool VersionLib::VersionData::operator<(const std::string &verStr)
{
    return *this < VersionLib::VersionData(verStr);
}

bool VersionLib::VersionData::operator<=(const std::string &verStr)
{
    return *this <= VersionLib::VersionData(verStr);
}
