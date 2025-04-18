# Version Library: Project Information

This document contains the information about the future plans, known bugs, deprecated features.

## Recent Implementations:

- Support for convert `VersionStruct` to `VersionData` and vice-versa.
- New experimental version string detection in `toVersionStrut2` method.
- ~~New experimental memory layout of `VersionStruct` to reduce the memory size allocation. (See the details in [here](#versionstruct-and-versiondata-memory-layout))~~
- Support to create objects versions without warning messages with wrapper constructors.
- **CHANGED `build_type_number` VARIABLE TO `build_revision` TO A BETTER COMPREHENSION.**
- Add support to compare versions with build information.

## Implementations under development:

- Add Version Lib errors and exceptions components
- Add and update all documentation for the Version Library
- Replace `BuildType` enum to `VersionBuildType` class as main storage of version release type
    - *Only Alpha:* Experimental support to `VersionBuildType`
    - *Only Alpha:* Experimental `VersionBuildType` can now hold a vector of multiple release data using `BuildRelease` objects
- *Only Alpha:* Experimental support to new `BuildType` entries: `PRE_ALPHA`, `CANARY`, `DEVELOPMENT`, `PRE_RELEASE`. **NOTE: Those new entries are not part of Semantic Versioning and can be removed in other development versions if they do not stand for a better permissive approach.**
- Complete support to Semantic Versioning (including combined releases - alpha.beta and others)
- Support to mathematical approach to determinate the release and revision information data is higher, lower or equal to another.
- Add `BuildRelease` class to store `BuildType` and `revision` in same place.
- Support to combined build type information. I.e. `1.0.0-alpha.beta`
- Support to build metadata in version string
- **Redesign the internal components to support correctly the new data types**
- Add `VersionType` to identify the versioning type
- Add `idVersionType` method to identify the type of versioning
- Add generic approach to `VersionData`
- Add official library Semantic Versioning (`SemVer`) class
- Add updated `toVersionStruct3` method, to identify a better component detection
- Add `BuildMetadata` class to store the build metadata

## Future Implementations:

- Full support for C-Style functions to better support for extern C linkage
- Full support for extern C linkage
- Support to identify version files by it's name
- Support to detect Windows Metadata version information
- Support to Calendar Versioning
- Support to Hybrid Calendar Versioning with Semantic Versioning
- Complete support to custom versioning formats

## Known Bugs:

| Bug ID | Details | Notes/Workaround | Status |
| :----- | :-----: | :--------------: | -----: |
| 1 | ~~`tolower_str` contains a bug that make miss the characters that already in lowercase.~~ |  | FIXED |
| 2 | ~~`tolower_Cstr` contains a bug that make miss the characters that already in lowercase.~~ |  | FIXED |
| 3 | ~~When sending a version string on format *MAJOR.MINOR.PATCH.REVISION* to `VersionData`, the `build_type_number` or *revision* **can not be detected**~~ | The algorithm received a new version on **version 0.8.6** to eliminate the defections in detect string versions and add more permissive formats. To enable the experimental algorithm it's necessary enable `VERSION_LIB_ENABLE_EXPERIMENTAL_FIX_VERSIONSTR_2_VERSIONSTRUCT`. **NOTE: Originally the fix was coming to version 0.8.7. In 0.8.7 the experimental algorithm will be enable by default** | FIXED |
| 4 | ~~Using `VersionData` operators *less*, *less than*, *greater* and *greater than* does not work as expected~~ |  | FIXED |
| 5 | ~~VersionData method,`getBuildTypeCstr`, does not convert the C++ string data into C-style string~~ |  | FIXED |
| 6 | ~~VersionData method, `getBuildTypeCompleteCstr`, does not convert C++ string data into C-style string~~ |  | FIXED |
| 7 | ~~`VersionData` constructors not working after implementation of `cmpBuild` parameter, resulting in ambiguous reference~~ | If `VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_CONSTRUCTORS` is not defined, the modified constructors are disabled to avoid the ambiguous reference. **NOTE:** Using `VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_CONSTRUCTORS`, will **break** any code that uses original constructor parameter list. **NOTE: On version 0.9.0-alpha, the experimental constructors will be the focus during the development** | FIXED |
| 8 | `VersionException` fails when throw the object | Using *`catch (VersionLib::VersionException& e)`* does not fail. The workaround is not definitive. New tests and modification may happen to make sure it's working properly | **Fix in development** |
| 9 | ~~Enabling experimental optimized memory layout result in missing correct data to `build_type_number`. **NOTE: The experimental feature was only tested on Windows platforms with MSVC**~~ | **REMOVED THE EXPERIMENTAL MEMORY LAYOUT OPTIMIZATION IN DETRIMENT OF 0.9.0-alpha VERSION FEATURE DEVELOPMENT** | REMOVED |
| 10 | ~~Comparing with a version that has `major` as zero and another version with `major` greater than zero will always fail in comparison with the other version, when using the operators: `> >= < <=`~~ |  | FIXED |
| 11 | ~~On **ALPHA** version, the `initVersionBuildTypeC` method make the **MSVC** show *error LNK2005: "struct VersionLib::VersionBuildTypeC __cdecl VersionLib::initVersionBuildTypeC(void)"* and *error LNK2005: "struct VersionLib::VersionBuildTypeC __cdecl VersionLib::initVersionBuildTypeC(void)"* **NOTE: No tests was made with GCC and Linux systems**~~ | After an investigation of the last modifications, was detected the `initVersionBuildTypeC` was defined two times in `BuildTypes.cpp` and `BuildTypesExt.cpp`. The definition on last file, was removed to solve the multiple definition. | FIXED |
| 12 | ~~`build` was not set properly in `VersionData` with ***Experimental Constructors*** when build number does not appear on constructor parameters.~~ |  | FIXED |
| 13 | Creating `VersionData` and `SemVer` objects crash the library, with "String out of range" exception | Downgrade to version **0.8.7-beta** | **Fix in development** |
| 14 | `findAndGetBuildTypes` method is not working as expected | Downgrade to version **0.8.7-beta** | **Fix in development** |
| 15 | `VersionStruct2` does not store revision | Downgrade to version **0.8.7-beta** | **Fix in development** |
| 16 | `VersionStruct2` does not recognizes build type/release when revision does not appear in string data | Downgrade to version **0.8.7-beta** | **Fix in development** |
| 17 | `VersionStruct2` does not recognizes revision | Downgrade to version **0.8.7-beta** | **Fix in development** |

## Deprecated Features:

| Feature | Details | Workaround | Notes |
| :------ | :-----: | :--------: | ----: |

## Removed Features:

| Feature | Details | Workaround | Notes |
| :------ | :-----: | :--------: | ----: |
| `toVersionStruct` | Deprecated method because is not reliable to convert the version information to `VersionStruct` | Use `toVersionStrut2` with more reliable semantic versioning conversion. | Removed on version **0.9.0-alpha** |
| Original `VersionData` comparison operators are deprecated. | The original implementation of comparison operators `> >= < <=` are deprecated because are defective | No workaround is necessary | Removed on version **0.9.0-alpha** |
| Original `VersionData` constructors are deprecated and the *experimental constructors* are the default development. | The *experimental constructors* are enabled by default with `VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_CONSTRUCTORS`. *The constructor with string version parameter still working.* | To disable the experimental constructors, disable the `VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_CONSTRUCTORS` on `ExperimentalFeatures.hpp` | Removed on version **0.9.0-alpha** |

