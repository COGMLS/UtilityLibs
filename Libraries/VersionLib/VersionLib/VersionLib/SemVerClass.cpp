#include "SemVerClass.hpp"

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_SEMVER_CLASS

VersionLib::SemVer::SemVer(std::string versionStr, bool cmpBuild)
{
	VersionLib::VersionStruct v = VersionLib::toVersionStruct2(versionStr);

	this->major = v.major;
	this->minor = v.minor;
	this->patch = v.patch;
	this->build_type = v.build_type;
	#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->build_revision = v.build_revision;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->build = v.build;
	this->compare_build = cmpBuild;
}

VersionLib::SemVer::SemVer(VersionLib::VersionStruct version)
{
	this->major = version.major;
	this->minor = version.minor;
	this->patch = version.patch;
	this->build_type = version.build_type;
	#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->build_revision = version.build_revision;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->build = version.build;
	this->compare_build = version.compare_build;
}

VersionLib::SemVer::SemVer(unsigned int major, unsigned int minor, unsigned int patch)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = 0;
	this->build_type = VersionLib::BuildType::RELEASE;
	#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->build_revision = 0;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->compare_build = false;
}

VersionLib::SemVer::SemVer(unsigned int major, unsigned int minor, unsigned int patch, const char *build_type)
{
	if (build_type == nullptr)
	{
		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		VersionLib::VersionException e(VersionLib::VersionExceptionCode::VersionErrorCode_Invalid_Nullptr_Data_Passed);
		#else
		std::exception e;
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		throw e;
	}

	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = 0;
	this->build_type = VersionLib::str2BuildType(build_type);
	#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->build_revision = 0;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->compare_build = false;
}

VersionLib::SemVer::SemVer(unsigned int major, unsigned int minor, unsigned int patch, std::string build_type)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = 0;
	this->build_type = VersionLib::str2BuildType(build_type);
	#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->build_revision = 0;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->compare_build = false;
}

VersionLib::SemVer::SemVer(unsigned int major, unsigned int minor, unsigned int patch, VersionLib::BuildType build_type)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = 0;
	this->build_type = build_type;
	#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->build_revision = 0;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->compare_build = false;
}

VersionLib::SemVer::SemVer(unsigned int major, unsigned int minor, unsigned int patch, const char *build_type, unsigned int build_revision)
{
	if (build_type == nullptr)
	{
		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		VersionLib::VersionException e(VersionLib::VersionExceptionCode::VersionErrorCode_Invalid_Nullptr_Data_Passed);
		#else
		std::exception e;
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		throw e;
	}
	
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = 0;
	this->build_type = VersionLib::BuildRelease(VersionLib::str2BuildType(build_type), build_revision);
	#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->build_revision = build_revision;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->compare_build = false;
}

VersionLib::SemVer::SemVer(unsigned int major, unsigned int minor, unsigned int patch, std::string build_type, unsigned int build_revision)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = 0;
	this->build_type = VersionLib::BuildRelease(VersionLib::str2BuildType(build_type), build_revision);
	#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->build_revision = build_revision;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->compare_build = false;
}

VersionLib::SemVer::SemVer(unsigned int major, unsigned int minor, unsigned int patch, VersionLib::BuildType build_type, unsigned int build_revision)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = 0;
	this->build_type = VersionLib::BuildRelease(build_type, build_revision);
	#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->build_revision = build_revision;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->compare_build = false;
}

VersionLib::SemVer::SemVer(unsigned int major, unsigned int minor, unsigned int patch, const char *build_type, unsigned int build_revision, unsigned long long build, bool cmpBuild)
{
	if (build_type == nullptr)
	{
		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		VersionLib::VersionException e(VersionLib::VersionExceptionCode::VersionErrorCode_Invalid_Nullptr_Data_Passed);
		#else
		std::exception e;
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		throw e;
	}
	
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = build;
	this->build_type = VersionLib::BuildRelease(VersionLib::str2BuildType(build_type), build_revision);
	#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->build_revision = build_revision;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->compare_build = cmpBuild;
}

VersionLib::SemVer::SemVer(unsigned int major, unsigned int minor, unsigned int patch, std::string build_type, unsigned int build_revision, unsigned long long build, bool cmpBuild)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = build;
	this->build_type = VersionLib::BuildRelease(VersionLib::str2BuildType(build_type), build_revision);
	#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->build_revision = build_revision;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->compare_build = cmpBuild;
}

VersionLib::SemVer::SemVer(unsigned int major, unsigned int minor, unsigned int patch, VersionLib::BuildType build_type, unsigned int build_revision, unsigned long long build, bool cmpBuild)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = build;
	this->build_type = VersionLib::BuildRelease(build_type, build_revision);
	#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->build_revision = build_revision;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->compare_build = cmpBuild;
}

//
// Wrappers Constructors:
//

VersionLib::SemVer::SemVer(int major, int minor, int patch)
{
	if (major < 0 || minor < 0 || patch < 0)
	{
		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		VersionLib::VersionException e(VersionLib::VersionExceptionCode::VersionErrorCode_Parameter_Value_Less_Than_Zero);
		#else
		std::exception e;
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		throw e;
	}

	*this = VersionLib::SemVer(
		static_cast<unsigned int>(major),
		static_cast<unsigned int>(minor),
		static_cast<unsigned int>(patch)
	);
}

VersionLib::SemVer::SemVer(int major, int minor, int patch, const char* build_type)
{
	if (build_type == nullptr)
	{
		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		VersionLib::VersionException e(VersionLib::VersionExceptionCode::VersionErrorCode_Invalid_Nullptr_Data_Passed);
		#else
		std::exception e;
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		throw e;
	}

	if (major < 0 || minor < 0 || patch < 0)
	{
		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		VersionLib::VersionException e(VersionLib::VersionExceptionCode::VersionErrorCode_Parameter_Value_Less_Than_Zero);
		#else
		std::exception e;
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		throw e;
	}

	*this = VersionLib::SemVer(
		static_cast<unsigned int>(major),
		static_cast<unsigned int>(minor),
		static_cast<unsigned int>(patch),
		build_type
	);
}

VersionLib::SemVer::SemVer(int major, int minor, int patch, std::string build_type)
{
	if (major < 0 || minor < 0 || patch < 0)
	{
		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		VersionLib::VersionException e(VersionLib::VersionExceptionCode::VersionErrorCode_Parameter_Value_Less_Than_Zero);
		#else
		std::exception e;
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		throw e;
	}

	*this = VersionLib::SemVer(
		static_cast<unsigned int>(major),
		static_cast<unsigned int>(minor),
		static_cast<unsigned int>(patch),
		build_type
	);
}

VersionLib::SemVer::SemVer(int major, int minor, int patch, VersionLib::BuildType build_type)
{
	if (major < 0 || minor < 0 || patch < 0)
	{
		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		VersionLib::VersionException e(VersionLib::VersionExceptionCode::VersionErrorCode_Parameter_Value_Less_Than_Zero);
		#else
		std::exception e;
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		throw e;
	}

	*this = VersionLib::SemVer(
		static_cast<unsigned int>(major),
		static_cast<unsigned int>(minor),
		static_cast<unsigned int>(patch),
		build_type
	);
}

VersionLib::SemVer::SemVer(int major, int minor, int patch, const char* build_type, int build_revision)
{
	if (build_type == nullptr)
	{
		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		VersionLib::VersionException e(VersionLib::VersionExceptionCode::VersionErrorCode_Invalid_Nullptr_Data_Passed);
		#else
		std::exception e;
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		throw e;
	}

	if (major < 0 || minor < 0 || patch < 0 || build_revision < 0)
	{
		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		VersionLib::VersionException e(VersionLib::VersionExceptionCode::VersionErrorCode_Parameter_Value_Less_Than_Zero);
		#else
		std::exception e;
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		throw e;
	}

	*this = VersionLib::SemVer(
		static_cast<unsigned int>(major),
		static_cast<unsigned int>(minor),
		static_cast<unsigned int>(patch),
		build_type,
		static_cast<unsigned int>(build_revision)
	);
}

VersionLib::SemVer::SemVer(int major, int minor, int patch, std::string build_type, int build_revision)
{
	if (major < 0 || minor < 0 || patch < 0 || build_revision < 0)
	{
		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		VersionLib::VersionException e(VersionLib::VersionExceptionCode::VersionErrorCode_Parameter_Value_Less_Than_Zero);
		#else
		std::exception e;
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		throw e;
	}

	*this = VersionLib::SemVer(
		static_cast<unsigned int>(major),
		static_cast<unsigned int>(minor),
		static_cast<unsigned int>(patch),
		build_type,
		static_cast<unsigned int>(build_revision)
	);
}

VersionLib::SemVer::SemVer(int major, int minor, int patch, VersionLib::BuildType build_type, int build_revision)
{
	if (major < 0 || minor < 0 || patch < 0 || build_revision < 0)
	{
		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		VersionLib::VersionException e(VersionLib::VersionExceptionCode::VersionErrorCode_Parameter_Value_Less_Than_Zero);
		#else
		std::exception e;
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		throw e;
	}

	*this = VersionLib::SemVer(
		static_cast<unsigned int>(major),
		static_cast<unsigned int>(minor),
		static_cast<unsigned int>(patch),
		build_type,
		static_cast<unsigned int>(build_revision)
	);
}

VersionLib::SemVer::SemVer(int major, int minor, int patch, const char *build_type, int build_revision, long long build, bool cmpBuild)
{
	if (build_type == nullptr)
	{
		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		VersionLib::VersionException e(VersionLib::VersionExceptionCode::VersionErrorCode_Invalid_Nullptr_Data_Passed);
		#else
		std::exception e;
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		throw e;
	}

	if (major < 0 || minor < 0 || patch < 0 || build < 0 || build_revision < 0)
	{
		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		VersionLib::VersionException e(VersionLib::VersionExceptionCode::VersionErrorCode_Parameter_Value_Less_Than_Zero);
		#else
		std::exception e;
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		throw e;
	}

	*this = VersionLib::SemVer(
		static_cast<unsigned int>(major),
		static_cast<unsigned int>(minor),
		static_cast<unsigned int>(patch),
		build_type,
		static_cast<unsigned int>(build_revision),
		static_cast<unsigned long long>(build),
		cmpBuild
	);
}

VersionLib::SemVer::SemVer(int major, int minor, int patch, std::string build_type, int build_revision, long long build, bool cmpBuild)
{
	if (major < 0 || minor < 0 || patch < 0 || build < 0 || build_revision < 0)
	{
		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		VersionLib::VersionException e(VersionLib::VersionExceptionCode::VersionErrorCode_Parameter_Value_Less_Than_Zero);
		#else
		std::exception e;
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		throw e;
	}

	*this = VersionLib::SemVer(
		static_cast<unsigned int>(major),
		static_cast<unsigned int>(minor),
		static_cast<unsigned int>(patch),
		build_type,
		static_cast<unsigned int>(build_revision),
		static_cast<unsigned long long>(build),
		cmpBuild
	);
}

VersionLib::SemVer::SemVer(int major, int minor, int patch, VersionLib::BuildType build_type, int build_revision, long long build, bool cmpBuild)
{
	if (major < 0 || minor < 0 || patch < 0 || build < 0 || build_revision < 0)
	{
		#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		VersionLib::VersionException e(VersionLib::VersionExceptionCode::VersionErrorCode_Parameter_Value_Less_Than_Zero);
		#else
		std::exception e;
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSION_LIB_EXCEPTIONS
		throw e;
	}

	*this = VersionLib::SemVer(
		static_cast<unsigned int>(major),
		static_cast<unsigned int>(minor),
		static_cast<unsigned int>(patch),
		build_type,
		static_cast<unsigned int>(build_revision),
		static_cast<unsigned long long>(build),
		cmpBuild
	);
}

VersionLib::SemVer::SemVer(const VersionLib::SemVer &other)
{
	this->major = other.major;
	this->minor = other.minor;
	this->patch = other.patch;
	this->build = other.build;
	this->build_type = other.build_type;
	#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->build_revision = other.build_revision;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->compare_build = other.compare_build;
}

VersionLib::SemVer::SemVer(VersionLib::SemVer &&other) noexcept
{
	this->major = std::move(other.major);
	this->minor = std::move(other.minor);
	this->patch = std::move(other.patch);
	this->build = std::move(other.build);
	this->build_type = std::move(other.build_type);
	#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->build_revision = std::move(other.build_revision);
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->compare_build = std::move(other.compare_build);
}

VersionLib::SemVer::~SemVer()
{
}

unsigned int VersionLib::SemVer::getMajor()
{
    return this->major;
}

unsigned int VersionLib::SemVer::getMinor()
{
    return this->minor;
}

unsigned int VersionLib::SemVer::getPatch()
{
    return this->patch;
}

unsigned long long VersionLib::SemVer::getBuild()
{
    return this->build;
}

const char *VersionLib::SemVer::getBuildTypeCstr(bool useShortStr)
{
	std::string verStr = this->getBuildTypeStr(useShortStr);
	size_t strLen = verStr.size();
	char* tmp = new char[strLen];
	std::strcpy(tmp, verStr.c_str());
	return const_cast<const char*>(tmp);
}

std::string VersionLib::SemVer::getBuildTypeStr(bool useShortStr)
{
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
		#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
		return VersionLib::buildType2Str(this->build_type.getBuildType(), useShortStr);
		#else
		return this->build_type.getBuildTypeStr(useShortStr);
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
	#else
    return VersionLib::buildType2Str(this->build_type, useShortStr);
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
}

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
VersionLib::VersionBuildType VersionLib::SemVer::getBuildType()
{
	return this->build_type;
}
#else
VersionLib::BuildType VersionLib::SemVer::getBuildType()
{
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
		#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
		return this->build_type.getBuildType();
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
	#else
	return this->build_type;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
}

unsigned int VersionLib::SemVer::getBuildRevision()
{
	return this->build_revision;
}
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT

const char *VersionLib::SemVer::getBuildTypeCompleteCstr(bool useShortStr, bool showReleaseType)
{
	std::string verStr = this->getBuildTypeComplete(useShortStr, showReleaseType);
	size_t strLen = verStr.size();
	char* tmp = new char[strLen];
	std::strcpy(tmp, verStr.c_str());
	return const_cast<const char*>(tmp);
}

std::string VersionLib::SemVer::getBuildTypeComplete(bool useShortStr, bool showReleaseType)
{
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	return this->build_type.getBuildTypeStr(useShortStr, showReleaseType);
	#else
    std::string tmp;

	if (this->build_type == VersionLib::BuildType::RELEASE && !showReleaseType)
	{
		return tmp;
	}

	tmp = this->getBuildTypeStr(useShortStr);

	if (this->build_revision > 0)
	{
		tmp += "." + std::to_string(this->build_revision);
	}

	return tmp;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
}

std::string VersionLib::SemVer::getVersionStr(bool useShortStr, bool hideBuildWord, bool showReleaseType)
{
	std::string tmp;

	tmp += std::to_string(this->major) + ".";
	tmp += std::to_string(this->minor) + ".";
	tmp += std::to_string(this->patch);
	
	if (this->build_type != VersionLib::BuildType::RELEASE || this->build_type == VersionLib::BuildType::RELEASE && showReleaseType)
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

VersionLib::VersionStruct VersionLib::SemVer::toVersionStruct()
{
	VersionLib::VersionStruct verData = initVersionStruct();

	verData.major = this->major;
	verData.minor = this->minor;
	verData.patch = this->patch;
	verData.build = this->build;
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	verData.build_type = this->build_type.toStruct();
	#else
	verData.build_type = this->build_type;
	verData.build_revision = this->build_revision;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	verData.compare_build = this->compare_build;

	return verData;
}

VersionLib::SemVer &VersionLib::SemVer::operator=(const VersionLib::SemVer &other)
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
	#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->build_revision = other.build_revision;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->compare_build = other.compare_build;

	return *this;
}

VersionLib::SemVer &VersionLib::SemVer::operator=(VersionLib::SemVer &&other) noexcept
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
	#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->build_revision = std::move(other.build_revision);
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	this->compare_build = std::move(other.compare_build);

	return *this;
}

bool VersionLib::SemVer::operator==(const VersionLib::SemVer &other)
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

	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_COMPARISON
	if (this->compare_build || other.compare_build)
	{
		if (this->build != other.build)
		{
			return false;
		}
	}
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_BUILD_COMPARISON

	if (this->build_type != other.build_type)
	{
		return false;
	}

	#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	if (this->build_revision != other.build_revision)
	{
		return false;
	}
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT

    return true;
}

bool VersionLib::SemVer::operator!=(const VersionLib::SemVer &other)
{
    return !(*this == other);
}

bool VersionLib::SemVer::operator>(const VersionLib::SemVer &other)
{
	#ifdef VERSION_LIB_COMPARISON_OPERATORS_V2
	if (this->major > other.major)
	{
		if (this->minor > other.minor)
		{
			if (this->patch > other.patch)
			{
				if (this->build_type > other.build_type)
				{
					#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision > other.build_revision)
						{
							return true;	// Major, minor, patch, build_type and revision are higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision < other.build_revision)
						{
							return false;	// Major, minor, patch and build_type are higher. But revision is equal or less
						}
					}
					else
					{
						return true;		// Major, minor, patch and build_type are higher. Revision is disabled for both.
					}
					#else
					return true;
					#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				}

				#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				if (this->build_type == other.build_type)
				{
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision > other.build_revision)
						{
							return true;	// Major, minor, patch are higher. Build_type is equal. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision < other.build_revision)
						{
							return false;	// Major, minor, patch are higher. Build_type is equal. Revision is equal or less
						}
					}
					else
					{
						return false;		// Major, minor, patch are higher. Build_type is equal. Revision is disabled for both.
					}
				}
				#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
			}

			if (this->patch == other.patch)
			{
				if (this->build_type > other.build_type)
				{
					#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision > other.build_revision)
						{
							return true;	// Major and minor are higher. Patch is equal. Build_type is higher. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision < other.build_revision)
						{
							return false;	// Major and minor are higher. Patch is equal. Build_type is higher. Revision is equal or less
						}
					}
					else
					{
						return true;		// Major and minor are higher. Patch is equal. Build_type is higher. Revision is disabled.
					}
					#else
					return true;
					#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				}

				#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				if (this->build_type == other.build_type)
				{
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision > other.build_revision)
						{
							return true;	// Major and minor are higher. Patch and build_type are equal. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision < other.build_revision)
						{
							return false;	// Major and minor are higher. Patch and build_type are equal. Revision is equal or less
						}
					}
					else
					{
						return false;		// Major and minor are higher. Patch and build_type are equal. Revision is disabled.
					}
				}
				#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
			}
		}

		if (this->minor == other.minor)
		{
			if (this->patch > other.patch)
			{
				if (this->build_type > other.build_type)
				{
					#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision > other.build_revision)
						{
							return true;	// Major is higher. Minor is equal. Patch and build_type are higher. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision < other.build_revision)
						{
							return false;	// Major is higher. Minor is equal. Patch and build_type are higher. Revision is equal or less
						}
					}
					else
					{
						return true;		// Major is higher. Minor is equal. Patch and build_type are higher. Revision is disabled.
					}
					#else
					return true;
					#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				}

				#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				if (this->build_type == other.build_type)
				{
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision > other.build_revision)
						{
							return true;	// Major is higher. Minor is equal. Patch is higher. Build_type is equal. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision < other.build_revision)
						{
							return false;	// Major is higher. Minor is equal. Patch is higher. Build_type is equal. Revision is equal or less
						}
					}
					else
					{
						return false;		// Major is higher. Minor is equal. Patch is higher. Build_type is equal. Revision is disabled.
					}
				}
				#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
			}

			if (this->patch == other.patch)
			{
				if (this->build_type > other.build_type)
				{
					#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision > other.build_revision)
						{
							return true;	// Major is higher. Minor and Patch are equal. Build_type is higher. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision < other.build_revision)
						{
							return false;	// Major is higher. Minor and Patch are equal. Build_type is higher. Revision is equal or less
						}
					}
					else
					{
						return true;		// Major is higher. Minor and Patch are equal. Build_type is higher. Revision is disabled.
					}
					#else
					return true;
					#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				}

				#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				if (this->build_type == other.build_type)
				{
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision > other.build_revision)
						{
							return true;	// Major is higher. Minor, Patch and build_type are equal. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision < other.build_revision)
						{
							return false;	// Major is higher. Minor, Patch and build_type are equal. Revision is equal or less
						}
					}
					else
					{
						return false;		// Major is higher. Minor, Patch and build_type are equal. Revision is disabled.
					}
				}
				#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
			}
		}

		return true;	// Major is already a higher version
	}

	if (this->major == other.major)
	{
		if (this->minor > other.minor)
		{
			if (this->patch > other.patch)
			{
				if (this->build_type > other.build_type)
				{
					#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision > other.build_revision)
						{
							return true;	// Major is equal. Minor, patch, build_type and revision are higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision < other.build_revision)
						{
							return false;	// Major is equal. Minor, patch and build_type are higher. But revision is equal or less
						}
					}
					else
					{
						return true;		// Major is equal. Minor, patch and build_type are higher. Revision is disabled for both.
					}
					#else
					return true;
					#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				}

				#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				if (this->build_type == other.build_type)
				{
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision > other.build_revision)
						{
							return true;	// Major is equal. Minor, patch are higher. Build_type is equal. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision < other.build_revision)
						{
							return false;	// Major is equal. Minor, patch are higher. Build_type is equal. Revision is equal or less
						}
					}
					else
					{
						return false;		// Major is equal. Minor, patch are higher. Build_type is equal. Revision is disabled for both.
					}
				}
				#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
			}

			if (this->patch == other.patch)
			{
				if (this->build_type > other.build_type)
				{
					#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision > other.build_revision)
						{
							return true;	// Major is equal. Minor are higher. Patch is equal. Build_type is higher. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision < other.build_revision)
						{
							return false;	// Major is equal. Minor are higher. Patch is equal. Build_type is higher. Revision is equal or less
						}
					}
					else
					{
						return true;		// Major is equal. Minor are higher. Patch is equal. Build_type is higher. Revision is disabled.
					}
					#else
					return true;
					#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				}

				#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				if (this->build_type == other.build_type)
				{
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision > other.build_revision)
						{
							return true;	// Major is equal. Minor are higher. Patch and build_type are equal. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision < other.build_revision)
						{
							return false;	// Major is equal. Minor are higher. Patch and build_type are equal. Revision is equal or less
						}
					}
					else
					{
						return false;		// Major is equal. Minor are higher. Patch and build_type are equal. Revision is disabled.
					}
				}
				#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
			}
		}

		if (this->minor == other.minor)
		{
			if (this->patch > other.patch)
			{
				if (this->build_type > other.build_type)
				{
					#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision > other.build_revision)
						{
							return true;	// Major and minor are equal. Patch and build_type are higher. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision < other.build_revision)
						{
							return false;	// Major and minor are equal. Patch and build_type are higher. Revision is equal or less
						}
					}
					else
					{
						return true;		// Major and minor are equal. Patch and build_type are higher. Revision is disabled.
					}
					#else
					return true;
					#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				}

				#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				if (this->build_type == other.build_type)
				{
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision > other.build_revision)
						{
							return true;	// Major and minor are equal. Patch is higher. Build_type is equal. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision < other.build_revision)
						{
							return false;	// Major and minor are equal. Patch is higher. Build_type is equal. Revision is equal or less
						}
					}
					else
					{
						return false;		// Major and minor are equal. Patch is higher. Build_type is equal. Revision is disabled.
					}
				}
				#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
			}

			if (this->patch == other.patch)
			{
				if (this->build_type > other.build_type)
				{
					#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision > other.build_revision)
						{
							return true;	// Major, minor and patch are equal. Build_type is higher. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision < other.build_revision)
						{
							return false;	// Major, minor and patch are equal. Build_type is higher. Revision is equal or less
						}
					}
					else
					{
						return true;		// Major, minor and patch are equal. Build_type is higher. Revision is disabled.
					}
					#else
					return true;
					#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				}

				#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				if (this->build_type == other.build_type)
				{
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision > other.build_revision)
						{
							return true;	// Major, minor, patch and build_type are equal. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision < other.build_revision)
						{
							return false;	// Major, minor, patch and build_type are equal. Revision is equal or less
						}
					}
					else
					{
						return false;		// Major, minor, patch and build_type are equal. Revision is disabled.
					}
				}
				#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
			}
		}
	}

	return false;	// Failed to test all possible true conditions
	#endif // !VERSION_LIB_COMPARISON_OPERATORS_V2
}

bool VersionLib::SemVer::operator>=(const VersionLib::SemVer &other)
{
	#ifdef VERSION_LIB_COMPARISON_OPERATORS_V2
	//if (this->major >= other.major && this->minor >= other.minor && this->patch >= other.patch && this->build_type >= other.build_type && this->build_revision >= other.build_revision) return true;
	//return false;
	if (this->major < other.major) return false;
	if (this->major >= other.major && this->minor < other.minor) return false;
	if (this->major >= other.major && this->minor >= other.minor && this->patch < other.patch) return false;
	if (this->major >= other.major && this->minor >= other.minor && this->patch >= other.patch && this->build_type < other.build_type) return false;
	#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	if (this->major >= other.major && this->minor >= other.minor && this->patch >= other.patch && this->build_type >= other.build_type && this->build_revision < other.build_revision) return false;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	return true;
	#endif // !VERSION_LIB_COMPARISON_OPERATORS_V2
}

bool VersionLib::SemVer::operator<(const VersionLib::SemVer &other)
{
	#ifdef VERSION_LIB_COMPARISON_OPERATORS_V2
	//if (this->major <= other.major && this->minor <= other.minor && this->patch <= other.patch && this->build_type <= other.build_type && this->build_revision < other.build_revision) return true;
	//return false;
	if (this->major < other.major)
	{
		if (this->minor < other.minor)
		{
			if (this->patch < other.patch)
			{
				if (this->build_type < other.build_type)
				{
					#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision < other.build_revision)
						{
							return true;	// Major, minor, patch, build_type and revision are higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision > other.build_revision)
						{
							return false;	// Major, minor, patch and build_type are higher. But revision is equal or less
						}
					}
					else
					{
						return true;		// Major, minor, patch and build_type are higher. Revision is disabled for both.
					}
					#else
					return true;
					#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				}

				#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				if (this->build_type == other.build_type)
				{
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision < other.build_revision)
						{
							return true;	// Major, minor, patch are higher. Build_type is equal. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision > other.build_revision)
						{
							return false;	// Major, minor, patch are higher. Build_type is equal. Revision is equal or less
						}
					}
					else
					{
						return false;		// Major, minor, patch are higher. Build_type is equal. Revision is disabled for both.
					}
				}
				#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
			}

			if (this->patch == other.patch)
			{
				if (this->build_type < other.build_type)
				{
					#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision < other.build_revision)
						{
							return true;	// Major and minor are higher. Patch is equal. Build_type is higher. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision > other.build_revision)
						{
							return false;	// Major and minor are higher. Patch is equal. Build_type is higher. Revision is equal or less
						}
					}
					else
					{
						return true;		// Major and minor are higher. Patch is equal. Build_type is higher. Revision is disabled.
					}
					#else
					return true;
					#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				}

				#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				if (this->build_type == other.build_type)
				{
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision < other.build_revision)
						{
							return true;	// Major and minor are higher. Patch and build_type are equal. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision > other.build_revision)
						{
							return false;	// Major and minor are higher. Patch and build_type are equal. Revision is equal or less
						}
					}
					else
					{
						return false;		// Major and minor are higher. Patch and build_type are equal. Revision is disabled.
					}
				}
				#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
			}
		}

		if (this->minor == other.minor)
		{
			if (this->patch < other.patch)
			{
				if (this->build_type < other.build_type)
				{
					#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision < other.build_revision)
						{
							return true;	// Major is higher. Minor is equal. Patch and build_type are higher. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision > other.build_revision)
						{
							return false;	// Major is higher. Minor is equal. Patch and build_type are higher. Revision is equal or less
						}
					}
					else
					{
						return true;		// Major is higher. Minor is equal. Patch and build_type are higher. Revision is disabled.
					}
					#else
					return true;
					#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				}

				#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				if (this->build_type == other.build_type)
				{
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision < other.build_revision)
						{
							return true;	// Major is higher. Minor is equal. Patch is higher. Build_type is equal. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision > other.build_revision)
						{
							return false;	// Major is higher. Minor is equal. Patch is higher. Build_type is equal. Revision is equal or less
						}
					}
					else
					{
						return false;		// Major is higher. Minor is equal. Patch is higher. Build_type is equal. Revision is disabled.
					}
				}
				#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
			}

			if (this->patch == other.patch)
			{
				if (this->build_type < other.build_type)
				{
					#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision < other.build_revision)
						{
							return true;	// Major is higher. Minor and Patch are equal. Build_type is higher. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision > other.build_revision)
						{
							return false;	// Major is higher. Minor and Patch are equal. Build_type is higher. Revision is equal or less
						}
					}
					else
					{
						return true;		// Major is higher. Minor and Patch are equal. Build_type is higher. Revision is disabled.
					}
					#else
					return true;
					#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				}

				#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				if (this->build_type == other.build_type)
				{
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision < other.build_revision)
						{
							return true;	// Major is higher. Minor, Patch and build_type are equal. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision > other.build_revision)
						{
							return false;	// Major is higher. Minor, Patch and build_type are equal. Revision is equal or less
						}
					}
					else
					{
						return false;		// Major is higher. Minor, Patch and build_type are equal. Revision is disabled.
					}
				}
				#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
			}
		}

		return true;	// Major is already a higher version
	}

	if (this->major == other.major)
	{
		if (this->minor < other.minor)
		{
			if (this->patch < other.patch)
			{
				if (this->build_type < other.build_type)
				{
					#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision < other.build_revision)
						{
							return true;	// Major is equal. Minor, patch, build_type and revision are higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision > other.build_revision)
						{
							return false;	// Major is equal. Minor, patch and build_type are higher. But revision is equal or less
						}
					}
					else
					{
						return true;		// Major is equal. Minor, patch and build_type are higher. Revision is disabled for both.
					}
					#else
					return true;
					#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				}

				#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				if (this->build_type == other.build_type)
				{
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision < other.build_revision)
						{
							return true;	// Major is equal. Minor, patch are higher. Build_type is equal. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision > other.build_revision)
						{
							return false;	// Major is equal. Minor, patch are higher. Build_type is equal. Revision is equal or less
						}
					}
					else
					{
						return false;		// Major is equal. Minor, patch are higher. Build_type is equal. Revision is disabled for both.
					}
				}
				#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
			}

			if (this->patch == other.patch)
			{
				if (this->build_type < other.build_type)
				{
					#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision < other.build_revision)
						{
							return true;	// Major is equal. Minor are higher. Patch is equal. Build_type is higher. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision > other.build_revision)
						{
							return false;	// Major is equal. Minor are higher. Patch is equal. Build_type is higher. Revision is equal or less
						}
					}
					else
					{
						return true;		// Major is equal. Minor are higher. Patch is equal. Build_type is higher. Revision is disabled.
					}
					#else
					return true;
					#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				}

				#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				if (this->build_type == other.build_type)
				{
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision < other.build_revision)
						{
							return true;	// Major is equal. Minor are higher. Patch and build_type are equal. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision > other.build_revision)
						{
							return false;	// Major is equal. Minor are higher. Patch and build_type are equal. Revision is equal or less
						}
					}
					else
					{
						return false;		// Major is equal. Minor are higher. Patch and build_type are equal. Revision is disabled.
					}
				}
				#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
			}
		}

		if (this->minor == other.minor)
		{
			if (this->patch < other.patch)
			{
				if (this->build_type < other.build_type)
				{
					#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision < other.build_revision)
						{
							return true;	// Major and minor are equal. Patch and build_type are higher. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision > other.build_revision)
						{
							return false;	// Major and minor are equal. Patch and build_type are higher. Revision is equal or less
						}
					}
					else
					{
						return true;		// Major and minor are equal. Patch and build_type are higher. Revision is disabled.
					}
					#else
					return true;
					#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				}

				#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				if (this->build_type == other.build_type)
				{
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision < other.build_revision)
						{
							return true;	// Major and minor are equal. Patch is higher. Build_type is equal. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision > other.build_revision)
						{
							return false;	// Major and minor are equal. Patch is higher. Build_type is equal. Revision is equal or less
						}
					}
					else
					{
						return false;		// Major and minor are equal. Patch is higher. Build_type is equal. Revision is disabled.
					}
				}
				#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
			}

			if (this->patch == other.patch)
			{
				if (this->build_type < other.build_type)
				{
					#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision < other.build_revision)
						{
							return true;	// Major, minor and patch are equal. Build_type is higher. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision > other.build_revision)
						{
							return false;	// Major, minor and patch are equal. Build_type is higher. Revision is equal or less
						}
					}
					else
					{
						return true;		// Major, minor and patch are equal. Build_type is higher. Revision is disabled.
					}
					#else
					return true;
					#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				}

				#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
				if (this->build_type == other.build_type)
				{
					if (this->build_revision != 0 || other.build_revision != 0)
					{
						if (this->build_revision < other.build_revision)
						{
							return true;	// Major, minor, patch and build_type are equal. Revision is higher.
						}

						if (this->build_revision == other.build_revision || this->build_revision > other.build_revision)
						{
							return false;	// Major, minor, patch and build_type are equal. Revision is equal or less
						}
					}
					else
					{
						return false;		// Major, minor, patch and build_type are equal. Revision is disabled.
					}
				}
				#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
			}
		}
	}

	return false;
	#endif // !VERSION_LIB_COMPARISON_OPERATORS_V2
}

bool VersionLib::SemVer::operator<=(const VersionLib::SemVer &other)
{
	#ifdef VERSION_LIB_COMPARISON_OPERATORS_V2
	//if (this->major <= other.major && this->minor <= other.minor && this->patch <= other.patch && this->build_type <= other.build_type && this->build_revision <= other.build_revision) return true;
	//return false;
	if (this->major > other.major) return false;
	if (this->major <= other.major && this->minor > other.minor) return false;
	if (this->major <= other.major && this->minor <= other.minor && this->patch > other.patch) return false;
	if (this->major <= other.major && this->minor <= other.minor && this->patch <= other.patch && this->build_type > other.build_type) return false;
	#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	if (this->major <= other.major && this->minor <= other.minor && this->patch <= other.patch && this->build_type <= other.build_type && this->build_revision > other.build_revision) return false;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	return true;
	#endif // !VERSION_LIB_COMPARISON_OPERATORS_V2
}

bool VersionLib::SemVer::operator==(const VersionLib::VersionStruct &other)
{
    return *this == VersionLib::SemVer(other);
}

bool VersionLib::SemVer::operator!=(const VersionLib::VersionStruct& other)
{
	return *this != VersionLib::SemVer(other);
}

bool VersionLib::SemVer::operator>(const VersionLib::VersionStruct& other)
{
	return *this > VersionLib::SemVer(other);
}

bool VersionLib::SemVer::operator>=(const VersionLib::VersionStruct& other)
{
	return *this >= VersionLib::SemVer(other);
}

bool VersionLib::SemVer::operator<(const VersionLib::VersionStruct& other)
{
	return *this < VersionLib::SemVer(other);
}

bool VersionLib::SemVer::operator<=(const VersionLib::VersionStruct& other)
{
	return *this <= VersionLib::SemVer(other);
}

bool VersionLib::SemVer::operator==(const std::string &verStr)
{
    return *this == VersionLib::SemVer(verStr);
}

bool VersionLib::SemVer::operator!=(const std::string &verStr)
{
    return *this != VersionLib::SemVer(verStr);
}

bool VersionLib::SemVer::operator>(const std::string &verStr)
{
    return *this > VersionLib::SemVer(verStr);
}

bool VersionLib::SemVer::operator>=(const std::string &verStr)
{
    return *this >= VersionLib::SemVer(verStr);
}

bool VersionLib::SemVer::operator<(const std::string &verStr)
{
    return *this < VersionLib::SemVer(verStr);
}

bool VersionLib::SemVer::operator<=(const std::string &verStr)
{
    return *this <= VersionLib::SemVer(verStr);
}

#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SEMVER_CLASS