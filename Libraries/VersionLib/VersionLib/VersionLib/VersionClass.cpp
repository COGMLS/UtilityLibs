#include "VersionClass.hpp"

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_CONSTRUCTORS
VersionLib::VersionData::VersionData(std::string versionStr, bool cmpBuild)
{
	VersionLib::VersionStruct v = VersionLib::toVersionStruct2(versionStr);

	this->major = v.major;
	this->minor = v.minor;
	this->patch = v.patch;
	this->build_type = v.build_type;
	this->build_revision = v.build_revision;
	this->build = v.build;
	this->compare_build = cmpBuild;
}
#else
VersionLib::VersionData::VersionData(std::string versionStr)
{
	VersionLib::VersionStruct v = VersionLib::toVersionStruct2(versionStr);

	this->major = v.major;
	this->minor = v.minor;
	this->patch = v.patch;
	this->build_type = v.build_type;
	this->build_revision = v.build_revision;
	this->build = v.build;
	this->compare_build = false;
}
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_CONSTRUCTORS

VersionLib::VersionData::VersionData(VersionLib::VersionStruct version)
{
	this->major = version.major;
	this->minor = version.minor;
	this->patch = version.patch;
	this->build_type = version.build_type;
	this->build_revision = version.build_revision;
	this->build = version.build;
	this->compare_build = version.compare_build;
}

VersionLib::VersionData::VersionData(unsigned int major, unsigned int minor, unsigned int patch)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = 0;
	this->build_type = VersionLib::BuildType::RELEASE;
	this->build_revision = 0;
	this->compare_build = false;
}

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_CONSTRUCTORS
VersionLib::VersionData::VersionData(unsigned int major, unsigned int minor, unsigned int patch, const char *build_type)
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
	this->build_type = VersionLib::str2BuildType(build_type);
	this->build_revision = 0;
	this->compare_build = false;
}

VersionLib::VersionData::VersionData(unsigned int major, unsigned int minor, unsigned int patch, std::string build_type)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = build;
	this->build_type = VersionLib::str2BuildType(build_type);
	this->build_revision = 0;
	this->compare_build = false;
}

VersionLib::VersionData::VersionData(unsigned int major, unsigned int minor, unsigned int patch, VersionLib::BuildType build_type)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = build;
	this->build_type = build_type;
	this->build_revision = 0;
	this->compare_build = false;
}

VersionLib::VersionData::VersionData(unsigned int major, unsigned int minor, unsigned int patch, const char *build_type, unsigned int build_revision)
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
	this->build_type = VersionLib::str2BuildType(build_type);
	this->build_revision = build_revision;
	this->compare_build = false;
}

VersionLib::VersionData::VersionData(unsigned int major, unsigned int minor, unsigned int patch, std::string build_type, unsigned int build_revision)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = build;
	this->build_type = VersionLib::str2BuildType(build_type);
	this->build_revision = build_revision;
	this->compare_build = false;
}

VersionLib::VersionData::VersionData(unsigned int major, unsigned int minor, unsigned int patch, VersionLib::BuildType build_type, unsigned int build_revision)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = build;
	this->build_type = build_type;
	this->build_revision = build_revision;
	this->compare_build = false;
}

VersionLib::VersionData::VersionData(unsigned int major, unsigned int minor, unsigned int patch, const char *build_type, unsigned int build_revision, unsigned long long build, bool cmpBuild)
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
	this->build_type = VersionLib::str2BuildType(build_type);
	this->build_revision = build_revision;
	this->compare_build = cmpBuild;
}

VersionLib::VersionData::VersionData(unsigned int major, unsigned int minor, unsigned int patch, std::string build_type, unsigned int build_revision, unsigned long long build, bool cmpBuild)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = build;
	this->build_type = VersionLib::str2BuildType(build_type);
	this->build_revision = build_revision;
	this->compare_build = cmpBuild;
}

VersionLib::VersionData::VersionData(unsigned int major, unsigned int minor, unsigned int patch, VersionLib::BuildType build_type, unsigned int build_revision, unsigned long long build, bool cmpBuild)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = build;
	this->build_type = build_type;
	this->build_revision = build_revision;
	this->compare_build = cmpBuild;
}

//
// Wrappers Constructors:
//

VersionLib::VersionData::VersionData(int major, int minor, int patch)
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

	*this = VersionLib::VersionData(
		static_cast<unsigned int>(major),
		static_cast<unsigned int>(minor),
		static_cast<unsigned int>(patch)
	);
}

VersionLib::VersionData::VersionData(int major, int minor, int patch, const char* build_type)
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

	*this = VersionLib::VersionData(
		static_cast<unsigned int>(major),
		static_cast<unsigned int>(minor),
		static_cast<unsigned int>(patch),
		build_type
	);
}

VersionLib::VersionData::VersionData(int major, int minor, int patch, std::string build_type)
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

	*this = VersionLib::VersionData(
		static_cast<unsigned int>(major),
		static_cast<unsigned int>(minor),
		static_cast<unsigned int>(patch),
		build_type
	);
}

VersionLib::VersionData::VersionData(int major, int minor, int patch, VersionLib::BuildType build_type)
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

	*this = VersionLib::VersionData(
		static_cast<unsigned int>(major),
		static_cast<unsigned int>(minor),
		static_cast<unsigned int>(patch),
		build_type
	);
}

VersionLib::VersionData::VersionData(int major, int minor, int patch, const char* build_type, int build_revision)
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

	*this = VersionLib::VersionData(
		static_cast<unsigned int>(major),
		static_cast<unsigned int>(minor),
		static_cast<unsigned int>(patch),
		build_type,
		static_cast<unsigned int>(build_revision)
	);
}

VersionLib::VersionData::VersionData(int major, int minor, int patch, std::string build_type, int build_revision)
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

	*this = VersionLib::VersionData(
		static_cast<unsigned int>(major),
		static_cast<unsigned int>(minor),
		static_cast<unsigned int>(patch),
		build_type,
		static_cast<unsigned int>(build_revision)
	);
}

VersionLib::VersionData::VersionData(int major, int minor, int patch, VersionLib::BuildType build_type, int build_revision)
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

	*this = VersionLib::VersionData(
		static_cast<unsigned int>(major),
		static_cast<unsigned int>(minor),
		static_cast<unsigned int>(patch),
		build_type,
		static_cast<unsigned int>(build_revision)
	);
}

VersionLib::VersionData::VersionData(int major, int minor, int patch, const char *build_type, int build_revision, long long build, bool cmpBuild)
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

	*this = VersionLib::VersionData(
		static_cast<unsigned int>(major),
		static_cast<unsigned int>(minor),
		static_cast<unsigned int>(patch),
		build_type,
		static_cast<unsigned int>(build_revision),
		static_cast<unsigned long long>(build),
		cmpBuild
	);
}

VersionLib::VersionData::VersionData(int major, int minor, int patch, std::string build_type, int build_revision, long long build, bool cmpBuild)
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

	*this = VersionLib::VersionData(
		static_cast<unsigned int>(major),
		static_cast<unsigned int>(minor),
		static_cast<unsigned int>(patch),
		build_type,
		static_cast<unsigned int>(build_revision),
		static_cast<unsigned long long>(build),
		cmpBuild
	);
}

VersionLib::VersionData::VersionData(int major, int minor, int patch, VersionLib::BuildType build_type, int build_revision, long long build, bool cmpBuild)
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

	*this = VersionLib::VersionData(
		static_cast<unsigned int>(major),
		static_cast<unsigned int>(minor),
		static_cast<unsigned int>(patch),
		build_type,
		static_cast<unsigned int>(build_revision),
		static_cast<unsigned long long>(build),
		cmpBuild
	);
}
#else

VersionLib::VersionData::VersionData(unsigned int major, unsigned int minor, unsigned int patch, unsigned long long build)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = build;
	this->build_type = VersionLib::BuildType::RELEASE;
	this->build_revision = 0;
	this->compare_build = false;
}

VersionLib::VersionData::VersionData(unsigned int major, unsigned int minor, unsigned int patch, unsigned long long build, char *build_type)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = build;
	this->build_type = VersionLib::str2BuildType(build_type);
	this->build_revision = 0;
	this->compare_build = false;
}

VersionLib::VersionData::VersionData(unsigned int major, unsigned int minor, unsigned int patch, unsigned long long build, std::string build_type)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = build;
	this->build_type = VersionLib::str2BuildType(build_type);
	this->build_revision = 0;
	this->compare_build = false;
}

VersionLib::VersionData::VersionData(unsigned int major, unsigned int minor, unsigned int patch, unsigned long long build, VersionLib::BuildType build_type)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = build;
	this->build_type = build_type;
	this->build_revision = 0;
	this->compare_build = false;
}

VersionLib::VersionData::VersionData(unsigned int major, unsigned int minor, unsigned int patch, unsigned long long build, char *build_type, unsigned int build_revision)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = build;
	this->build_type = VersionLib::str2BuildType(build_type);
	this->build_revision = build_revision;
	this->compare_build = false;
}

VersionLib::VersionData::VersionData(unsigned int major, unsigned int minor, unsigned int patch, unsigned long long build, std::string build_type, unsigned int build_revision)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = build;
	this->build_type = VersionLib::str2BuildType(build_type);
	this->build_revision = build_revision;
	this->compare_build = false;
}

VersionLib::VersionData::VersionData(unsigned int major, unsigned int minor, unsigned int patch, unsigned long long build, VersionLib::BuildType build_type, unsigned int build_revision)
{
	this->major = major;
	this->minor = minor;
	this->patch = patch;
	this->build = build;
	this->build_type = build_type;
	this->build_revision = build_revision;
	this->compare_build = false;
}
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_CONSTRUCTORS

VersionLib::VersionData::VersionData(const VersionLib::VersionData &other)
{
	this->major = other.major;
	this->minor = other.minor;
	this->patch = other.patch;
	this->build = other.build;
	this->build_type = other.build_type;
	this->build_revision = other.build_revision;
	this->compare_build = other.compare_build;
}

VersionLib::VersionData::VersionData(VersionLib::VersionData &&other) noexcept
{
	this->major = std::move(other.major);
	this->minor = std::move(other.minor);
	this->patch = std::move(other.patch);
	this->build = std::move(other.build);
	this->build_type = std::move(other.build_type);
	this->build_revision = std::move(other.build_revision);
	this->compare_build = std::move(other.compare_build);
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
	std::strcpy(tmp, verStr.c_str());
	return const_cast<const char*>(tmp);
}

std::string VersionLib::VersionData::getBuildTypeStr(bool useShortStr)
{
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
		#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
		return VersionLib::buildType2Str(this->build_type.getBuildType(), useShortStr);
		#else
		#error "No support to VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE"
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
	#else
    return VersionLib::buildType2Str(this->build_type, useShortStr);
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
}

VersionLib::BuildType VersionLib::VersionData::getBuildType()
{
	#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
		#ifndef VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
		return this->build_type.getBuildType();
		#else
		#error "No support to VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE"
		#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE
	#else
	return this->build_type;
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
}

unsigned int VersionLib::VersionData::getBuildRevision()
{
    return this->build_revision;
}

const char *VersionLib::VersionData::getBuildTypeCompleteCstr(bool useShortStr, bool showReleaseType)
{
	std::string verStr = this->getBuildTypeComplete(useShortStr, showReleaseType);
	size_t strLen = verStr.size();
	char* tmp = new char[strLen];
	std::strcpy(tmp, verStr.c_str());
	return const_cast<const char*>(tmp);
}

std::string VersionLib::VersionData::getBuildTypeComplete(bool useShortStr, bool showReleaseType)
{
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
}

std::string VersionLib::VersionData::getVersionStr(bool useShortStr, bool hideBuildWord, bool showReleaseType)
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

VersionLib::VersionStruct VersionLib::VersionData::toVersionStruct()
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
	#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT
	verData.build_revision = this->build_revision;
	verData.compare_build = this->compare_build;

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
	this->build_revision = other.build_revision;
	this->compare_build = other.compare_build;

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
	this->build_revision = std::move(other.build_revision);
	this->compare_build = std::move(other.compare_build);

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

	if (this->build_revision != other.build_revision)
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
	#ifdef VERSION_LIB_COMPARISON_OPERATORS_V1
	if (this->major <= other.major && this->minor <= other.minor && this->patch <= other.patch && this->build_type <= other.build_type && this->build_revision <= other.build_revision) return false;
	if (this->major <= other.major && this->minor <= other.minor && this->patch <= other.patch && this->build_type < other.build_type) return false;
	if (this->major <= other.major && this->minor <= other.minor && this->patch < other.patch) return false;
	if (this->major <= other.major && this->minor < other.minor) return false;
	if (this->major <= other.major) return false;
	return true;
	#endif // !VERSION_LIB_COMPARISON_OPERATORS_V1
	
	#ifdef VERSION_LIB_COMPARISON_OPERATORS_V2
	if (this->major > other.major)
	{
		if (this->minor > other.minor)
		{
			if (this->patch > other.patch)
			{
				if (this->build_type > other.build_type)
				{
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
				}

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
			}

			if (this->patch == other.patch)
			{
				if (this->build_type > other.build_type)
				{
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
				}

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
			}
		}

		if (this->minor == other.minor)
		{
			if (this->patch > other.patch)
			{
				if (this->build_type > other.build_type)
				{
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
				}

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
			}

			if (this->patch == other.patch)
			{
				if (this->build_type > other.build_type)
				{
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
				}

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
				}

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
			}

			if (this->patch == other.patch)
			{
				if (this->build_type > other.build_type)
				{
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
				}

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
			}
		}

		if (this->minor == other.minor)
		{
			if (this->patch > other.patch)
			{
				if (this->build_type > other.build_type)
				{
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
				}

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
			}

			if (this->patch == other.patch)
			{
				if (this->build_type > other.build_type)
				{
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
				}

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
			}
		}
	}

	return false;	// Failed to test all possible true conditions
	#endif // !VERSION_LIB_COMPARISON_OPERATORS_V2
}

bool VersionLib::VersionData::operator>=(const VersionData &other)
{
	#ifdef VERSION_LIB_COMPARISON_OPERATORS_V1
    if (this->major <= other.major && this->minor <= other.minor && this->patch <= other.patch && this->build_type <= other.build_type && this->build_revision < other.build_revision) return false;
	if (this->major <= other.major && this->minor <= other.minor && this->patch <= other.patch && this->build_type < other.build_type) return false;
	if (this->major <= other.major && this->minor <= other.minor && this->patch < other.patch) return false;
	if (this->major <= other.major && this->minor < other.minor) return false;
	if (this->major < other.major) return false;
	return true;
	#endif // !VERSION_LIB_COMPARISON_OPERATORS_V1

	#ifdef VERSION_LIB_COMPARISON_OPERATORS_V2
	//if (this->major >= other.major && this->minor >= other.minor && this->patch >= other.patch && this->build_type >= other.build_type && this->build_revision >= other.build_revision) return true;
	//return false;
	if (this->major < other.major) return false;
	if (this->major >= other.major && this->minor < other.minor) return false;
	if (this->major >= other.major && this->minor >= other.minor && this->patch < other.patch) return false;
	if (this->major >= other.major && this->minor >= other.minor && this->patch >= other.patch && this->build_type < other.build_type) return false;
	if (this->major >= other.major && this->minor >= other.minor && this->patch >= other.patch && this->build_type >= other.build_type && this->build_revision < other.build_revision) return false;
	return true;
	#endif // !VERSION_LIB_COMPARISON_OPERATORS_V2
}

bool VersionLib::VersionData::operator<(const VersionData &other)
{
	#ifdef VERSION_LIB_COMPARISON_OPERATORS_V1
	if(this->major >= other.major && this->minor >= other.minor && this->patch >= other.patch && this->build_type >= other.build_type && this->build_revision >= other.build_revision) return false;
	if(this->major >= other.major && this->minor >= other.minor && this->patch >= other.patch && this->build_type > other.build_type) return false;
	if(this->major >= other.major && this->minor >= other.minor && this->patch > other.patch) return false;
	if(this->major >= other.major && this->minor > other.minor) return false;
	if(this->major >= other.major) return false;
	return true;
	#endif // !VERSION_LIB_COMPARISON_OPERATORS_V1

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
				}

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
			}

			if (this->patch == other.patch)
			{
				if (this->build_type < other.build_type)
				{
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
				}

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
			}
		}

		if (this->minor == other.minor)
		{
			if (this->patch < other.patch)
			{
				if (this->build_type < other.build_type)
				{
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
				}

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
			}

			if (this->patch == other.patch)
			{
				if (this->build_type < other.build_type)
				{
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
				}

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
				}

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
			}

			if (this->patch == other.patch)
			{
				if (this->build_type < other.build_type)
				{
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
				}

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
			}
		}

		if (this->minor == other.minor)
		{
			if (this->patch < other.patch)
			{
				if (this->build_type < other.build_type)
				{
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
				}

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
			}

			if (this->patch == other.patch)
			{
				if (this->build_type < other.build_type)
				{
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
				}

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
			}
		}
	}

	return false;
	#endif // !VERSION_LIB_COMPARISON_OPERATORS_V2
}

bool VersionLib::VersionData::operator<=(const VersionData &other)
{
	#ifdef VERSION_LIB_COMPARISON_OPERATORS_V1
    if(this->major >= other.major && this->minor >= other.minor && this->patch >= other.patch && this->build_type >= other.build_type && this->build_revision > other.build_revision) return false;
	if(this->major >= other.major && this->minor >= other.minor && this->patch >= other.patch && this->build_type > other.build_type) return false;
	if(this->major >= other.major && this->minor >= other.minor && this->patch > other.patch) return false;
	if(this->major >= other.major && this->minor > other.minor) return false;
	if(this->major > other.major) return false;
	return true;
	#endif // !VERSION_LIB_COMPARISON_OPERATORS_V1

	#ifdef VERSION_LIB_COMPARISON_OPERATORS_V2
	//if (this->major <= other.major && this->minor <= other.minor && this->patch <= other.patch && this->build_type <= other.build_type && this->build_revision <= other.build_revision) return true;
	//return false;
	if (this->major > other.major) return false;
	if (this->major <= other.major && this->minor > other.minor) return false;
	if (this->major <= other.major && this->minor <= other.minor && this->patch > other.patch) return false;
	if (this->major <= other.major && this->minor <= other.minor && this->patch <= other.patch && this->build_type > other.build_type) return false;
	if (this->major <= other.major && this->minor <= other.minor && this->patch <= other.patch && this->build_type <= other.build_type && this->build_revision > other.build_revision) return false;
	return true;
	#endif // !VERSION_LIB_COMPARISON_OPERATORS_V2
}

#ifdef VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_OPERATOR_STRUCT_COMPARISON
bool VersionLib::VersionData::operator==(const VersionLib::VersionStruct &other)
{
    return *this == VersionLib::VersionData(other);
}

bool VersionLib::VersionData::operator!=(const VersionLib::VersionStruct& other)
{
	return *this != VersionLib::VersionData(other);
}

bool VersionLib::VersionData::operator>(const VersionLib::VersionStruct& other)
{
	return *this > VersionLib::VersionData(other);
}

bool VersionLib::VersionData::operator>=(const VersionLib::VersionStruct& other)
{
	return *this >= VersionLib::VersionData(other);
}

bool VersionLib::VersionData::operator<(const VersionLib::VersionStruct& other)
{
	return *this < VersionLib::VersionData(other);
}

bool VersionLib::VersionData::operator<=(const VersionLib::VersionStruct& other)
{
	return *this <= VersionLib::VersionData(other);
}
#endif // !VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_OPERATOR_STRUCT_COMPARISON

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
