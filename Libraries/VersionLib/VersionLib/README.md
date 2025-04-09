# Version Library

The VersionLib is a versioning library to provide to other libraries and applications a easier way the implementation of version number control and tests to analyze if the version value is greater, equal, etc. The library also check if the *version core* is a release, beta or alpha build type. It's possible to check if the version is marked as incompatible with an application or library, using an know list of versions, provided by the dependency application or library and test it, with support to generate an exception or not.

The VersionLib contains all necessary methods and data type needed to work, allowing to consume this library without dependencies. All VersionLib methods, data types and classes, are inside the namespace `VersionLib`.

This library was developed using ISO C++ 20 and the internal code works with all platforms where this C++ version can be compiled. Platforms tested with the actual development stage: **Linux** and **Windows**.

**IMPORTANT:** *This library is under development and the methods may not work as expected. It's important to be aware about possible modifications that may break or be not compatible with previous feature during the development time.*

## Using the Version Library:

The Version Library contains a main header, `VersionLib.hpp`. This header provide all features to be able to work with versioning for any library or application that is using this library to provide versioning support. To use it, version data information, there is the `VersionStruct`, a C-Style data struct for extern C linkage calling and for internal Version Library use. The most recommended version data is the `VersionData` class for C++ context. Both version structure data information holds the same values: `major`, `minor`, `patch`, `build_type`, `build_type_number` and `build` variables. The `VersionData` class contain constructors to allow to create the version object and use the internal operators to compare with other object version.

The `VersionLib.hpp` header contain a function called `internalVersionData` that return the library version object, which can be used to test and check the current Version Library version with your application or other library.

> ⚠️ **Warning:** The actual development priority is to make sure the C++ functions can work properly. When the algorithms and components in C++ became stable and reliable, the C methods version will be the main development focus.

## About other documentation:

This project contains other documentation files available in [Docs folder](./Docs/).

| File | Documentation | Path |
| ---- | ------------- | ---- |
| VersionLibInfo | Information about the project, known bugs, future implementations, deprecated and removed features | [VersionLibInfo.md](./Docs/VersionLibInfo.md)
| VersionLibReleases | Complete version history about this project. In the README.md file only contains part of the version changes | [VersionLibReleases.md](./Docs/VersionLibReleases.md)

> Other documentation files will be added in a future.

### Compatible string version formats:

The `VersionLib` was designed to work primary with [Semantic Versioning](https://semver.org/), but also offer other version compatibility with a permissive algorithm. When using a non semantic versioning, the **custom format is not preserved**. If you export the string version, it will be exported in semantic versioning format.

To use a string as the source of the versioning information, the string must follow a sequence of numbers and use the dots between **major**, **minor**, **patch** and **revision** (if applicable - only after build type). The type of your build can be **alpha** (**a** for short), **beta** (**b** for short), **release candidate** or **release_candidate** (**rc** for short) or **release** (**r** for short). The type is set by hyphen `-` character. If no type was used, will assume **release**. The build number can be set after all those information, it can be used the word `build` before the number, it helps to avoid the algorithm to make sure is the build number field.

#### Legend:

| Letter | Version component |
| ------ | ----------------- |
| **M** | Major |
| **m** | minor |
| **p** | patch |
| **r** | Revision/Build type number |
| **b** | build number |
| **t** | Build type |

| Symbol | Description |
| ------ | ----------- |
| ✅️ | Format recognized |
| ⚠️ | Format partially recognized |
| ❕ | Not part of Semantic Versioning |
| ❌️ | Format not recognized |

| Format | Status | Experimental Detection | Example | Notes |
| ------ | ------ | ---------------------- | ------- | ----- |
| M      | ✅️ ⚠️ ❕ | ✅️ ❕ | 10 | This versioning format is not part of Semantic Versioning |
| M.m | ✅️ ⚠️ ❕ | ✅️ ❕ | 10.2 | This versioning format is not part of Semantic Versioning |
| M.m.p | ✅️ | ✅️ | 10.2.45 | |
| M.m.p-t | ✅️ | ✅️ | 0.8.3-beta | |
| M.m.p-t.r | ✅️ | ✅️ | 3.1.7-beta.6 | |
| M.m.p-t.r b | ✅️ | ✅️ | 7.1.3-rc.1 752 | |
| M b | ❌️ ❕  | ❌️ ❕  | 10 487 | This format is not recognized |
| M build b | ❌️ ❕  | ✅️ ❕  | 14 build 77 | This format is not recognized |
| M.m build b | ✅️ ❕  | ✅️ ❕  | 14.3 build 78 | **This format is not recommended** |
| M.m.p build b | ✅️ | ✅️ | 14.5.6 build 79 | |
| M.m.p-t build b | ✅️ | ✅️ | 3.1.9-rc build 54 | |
| M.m.p-t.r build b | ✅️ | ✅️ | 10.3.1-alpha.3 build 569 | |
| M.m.p.r build b | ⚠️ ❕ | ✅️ ❕ | 1.6.1.3 build 6100 | Revision is not recognized. |
| M.m.p.r | ⚠️ ❕ | ✅️ ❕ | 2.5.8.15 | Revision is not recognized. |
| M.m.p-t b | ⚠️ ❕ | ✅️ ❕ | 8.1.93-beta 856 | Build number is confused with Build revision. |
| M-t | ✅️⚠️ ❕ | ❌️ ❕ | 10-b | Ok (Major and Build type are detected) **NOTE:** This format will not be recognized any more by the algorithm. |
| M.m-t | ✅️⚠️ | ✅️ | 10.2-alpha | Ok (Major, Minor and Build type are detected) |
| M.m.p b | ❌️ | ✅️ | 10.2.8 456 | Build number is not detected. |
| M.m b | ❌️ | ✅️ | 17.5 782 | Build revision is confused with patch |
| M.m.p b | ❌️ | ✅️ | 17.9.5 125 | Build number is not detected |

## Project components implementations:

> **WARNING:** From version **0.8.5-beta** the `VersionData` class will be using the experimental constructors. Which contain different parameter list after the `patch` parameter position, moving the `build` parameter to final position.
>
> This decision resolves the ambiguous constructor call failure and make the reading of the parameter list identical with the *Semantic Versioning*.
>
> E.g. `VersionLib::VersionData myAppVer(2, 5, 9, VersionLib::BuildType::RELEASE, 5, 800);` we are creating a `myAppVer` object with version **2.5.9-rc.5 build 800**.
>
> Before the experimental constructors the code was `VersionLib::VersionData myAppVer(2, 5, 9, 800, VersionLib::BuildType::RELEASE, 5);` which is not so intuitive.
>
> Using the experimental constructors combined with old constructor style, **may break your code**. Unless you only used the string constructor or the `VersionData (major, minor, patch)` constructor.
>
> **TO DISABLE THE EXPERIMENTAL FEATURES, COMMENT THE LINES IN `ExperimentalFeatures.hpp`**

### Recent Implementations:

- Support for convert `VersionStruct` to `VersionData` and vice-versa.
- New experimental version string detection in `toVersionStrut2` method.
- New experimental memory layout of `VersionStruct` to reduce the memory size allocation. (See the details in [here](./Docs/VersionLibInfo.md#versionstruct-and-versiondata-memory-layout))
- Support to create objects versions without warning messages with wrapper constructors.
- **CHANGED `build_type_number` VARIABLE TO `build_revision` TO A BETTER COMPREHENSION.**

### Implementations under development:

- Add support to compare versions with build information.
- Add Version Lib errors and exceptions components
- Add and update all documentation for the Version Library
- Replace `BuildType` enum to `VersionBuildType` class as main storage of version release type
    - *Only Alpha:* Experimental support to `VersionBuildType`
- *Only Alpha:* Experimental support to new `BuildType` entries: `PRE_ALPHA`, `CANARY`, `DEVELOPMENT`, `PRE_RELEASE`. **NOTE: Those new entries are not part of Semantic Versioning and can be removed in other development versions if they do not stand for a better permissive approach.**

### Future Implementations:

- Full support for C-Style functions to better support for extern C linkage
- Full support for extern C linkage
- Support to identify version files by it's name
- Support to detect Windows Metadata version information
- Support to combined build type information. I.e. `1.0.0-alpha.beta`
- Support to build metadata in version string

## Version Library History:

<!-- Version Library History Table: -->
<head>
    <link rel="stylesheet" href="./Docs/CSS/ReleaseNotes.css">
</head>
<dl>
    <!-- 0.8.7-beta (2025/03/10) -->
    <dt><version-data>0.8.7-beta</version-data> | Release Date: 2025/03/10</dt>
    <dd><strong>Changed variable <code>build_type_number</code> to <code>build_revision</code> in <code>VersionStruct</code> and <code>VersionData</code></strong></dd>
    <dd>Changed the <code>build_type_number</code> references to <code>build_revision</code></dd>
    <dd><fix-alert>[FIX]</fix-alert> <code>VersionData</code> experimental comparison operators.</dd>
    <dd><fix-alert>[FIX]</fix-alert> <code>build</code> was not set properly in <code>VersionData</code> with <i><strong>Experimental Constructors</i></strong> when build number does not appear on constructor parameters.</dd>
    <dd><strong>Added original</strong> <code>VersionData</code> <strong>constructors to deprecated features</strong></dd>
    <dd><strong>Added original</strong> <code>VersionData</code> <strong>comparison operators to deprecated features</strong></dd>
    <dd><i>Added in 2025/04/09:</i> Updated the build number after few tests.</dd>
    <dd><i>Added in 2025/04/09:</i> Removed unnecessary controls to experimental features</dd>
    <!-- 0.8.6-beta (2025/02/26) -->
    <dt><version-data>0.8.6-beta</version-data> | Release Date: 2025/02/26</dt>
    <dd>Added new experimental algorithm to fix <code>toVersionStruct2</code> function string version detection</dd>
    <dd>Added experimental memory layout to reduce memory waste in <code>VersionStruct</code> and <code>VersionData</code></dd>
    <dd>Updated VersionLib documentation</dd>
    <dd><fix-alert>[FIX]</fix-alert> some permissive formats were not being detected or partially detected by <code>toVersionStruct2</code></dd>
    <dd><fix-alert>[FIX]</fix-alert> some Semantic Versioning formats were not being fully detected or some version components were confused with others.</dd>
    <dd><i>Added in 2025/03/05:</i> <bug-alert>[BUG]</bug-alert> [Experimental Operators] Comparing with a version that has <code>major</code> as zero and another version with <code>major</code> greater than zero will always fail in comparison with the other version, when using the operators: > >= < <=</dd>
    <!-- 0.8.5-beta (2025/02/18) -->
    <dt><version-data>0.8.5-beta</version-data> | Release Date: 2025/02/18</dt>
    <dd>Added <code>getErrorMessage</code> function to translate the <code>VersionExceptionCode</code> into error messages</dd>
    <dd>Added support to <code>internalVersionData</code> to use experimental constructors when enabled</dd>
    <dd>Added wrapper constructors to avoid compilation warnings when using integers in <code>VersionData</code></dd>
    <dd>Added new <code>VersionException</code> throws in few unaccepted conditions</dd>
    <dd>Renamed to <code>VersionExceptionCode</code></dd>
    <dd>Renamed <code>VersionExceptionCode</code> values</dd>
    <dd>Renamed experimental guards</dd>
    <dd>Renamed definitions for experimental features</dd>
    <dd>Changed experimental constructors parameters</dd>
    <dd>Changed <code>msg_val</code> to std::string to avoid missing control on memory block</dd>
    <dd><fix-alert>[FIX]</fix-alert> <code>VersionException</code> class</dd>
    <dd><fix-alert>[FIX]</fix-alert> <code>what</code> method in VersionException</dd>
    <dd><warning-alert>[WARNING]</warning-alert> These modifications may break any code that uses experimental constructors</dd>
    <!-- 0.8.4-beta (2025/02/04) -->
    <dt><version-data>0.8.4-beta</version-data> | Release Date: 2025/02/04</dt>
    <dd></dd>
    <dd>Added preprocessor to disable the original comparison operators</dd>
    <dd><fix-alert>[FIX]</fix-alert> <code>VersionData</code> comparison operators</dd>
    <dd>Added <code>compare_build</code> to control the build comparison in <code>VersionData</code></dd>
    <dd>Added experimental features compilation control</dd>
    <dd>Moved preprocessor definitions to <code>ExperimentalFeatures.hpp</code></dd>
    <dd>Added experimental features compilation control</dd>
    <dd>Added <code>compare_build</code> control variable into <code>VersionStruct</code></dd>
    <dd>Added <code>cmpBuild</code> parameter into constructors to enable/disable build comparison</dd>
    <dd>Added wrapper constructors to avoid constructor ambiguous failure</dd>
    <dd>Declared <code>VersionStruct</code> comparison operators in <code>VersionData</code></dd>
    <dd>Small code writing changes</dd>
    <dd>Small changes on documentation</dd>
    <!-- 0.8.3-beta.2 (2025/01/14) -->
    <dt><version-data>0.8.3-beta.2</version-data> | Release Date: 2025/01/14</dt>
    <dd>Updated <strong>Project Info.md</strong></dd>
    <dd>Marked missing attribute <i>deprecated</i> on <code>toVersionStruct</code> declaration.</dd>
    <dd><fix-alert>[FIX]</fix-alert> <code>tolower_Cstr</code> now converts the strings to C string style correctly</dd>
    <dd><fix-alert>[FIX]</fix-alert> missing instructions in <code>getBuildTypeCompleteCstr</code> method in <code>VersionData</code> class. </dd>
    <dd><fix-alert>[FIX]</fix-alert> missing instructions in <code>getBuildTypeCstr</code> method in <code>VersionData</code> class</dd>
    <!-- 0.8.3-beta (2025/01/10) -->
    <dt><version-data>0.8.3-beta</version-data> | Release Date: 2025/01/10</dt>
    <dd>Added new parameter <code>showReleaseType</code> in <code>getBuildTypeComplete</code> and <code>getVersionStr</code> methods.</dd>
    <dd><fix-alert>[FIX]</fix-alert> missing parameters for <code>getBuildTypeCompleteCstr</code> method.</dd>
    <dd><fix-alert>[FIX]</fix-alert> version string format when was marked as <strong>RELEASE</strong>.</dd>
    <dd><fix-alert>[FIX]</fix-alert> operators <strong>less</strong> than and <strong>greater</strong> than.</dd>
    <dd><fix-alert>[FIX]</fix-alert> Fixed missing "release" build type string return on <code>buildType2Str</code>.</dd>
    <!-- 0.8.2-beta (2024/10/09) -->
    <dt><version-data>0.8.2-beta</version-data> | Release Date: 2024/10/09</dt>
    <dd>Added copy and move constructors.</dd>
    <dd>Added copy and move operators.</dd>
    <dd><i>On 0.8.2-beta.2: </i>Added <code>VersionLibVersionInfo.hpp</code> file to hold the preprocessor information about the Version Library version information.</dd>
    <dd><i>On 0.8.2-beta.2: </i>Changed the name <code>internalVersionData</code> to a internal method to return the Version Library version information.</dd>
    <dd><bug-alert>[BUG]</bug-alert> <code>VersionData</code> operators <i><strong>less</strong></i>, <i><strong>less than</strong></i>, <i><strong>greater</strong></i> and <i><strong>greater than</strong></i> are not working as expected.</dd>
    <!-- 0.8.1-beta (2024/10/08) -->
    <dt><version-data>0.8.1-beta</version-data> | Release Date: 2024/10/08</dt>
    <dd><fix-alert>[FIX]</fix-alert> <code>tolower_str</code> method, using a traditional algorithm to convert the string to lowercase.</dd>
    <dd><warning-alert>[WARNING]</warning-alert> The method <code>tolower_Cstr</code> was not fixed.</dd>
    <dd>Added checking for possible quotes and double quotes use in string BUILD_TYPE.</dd>
    <dd>Added a check for situation when MAJOR.MINOR.PATCH.REVISION is available.</dd>
    <dd><bug-alert>[BUG]</bug-alert> When sending a version string on format <i>MAJOR.MINOR.PATCH.REVISION</i> to <code>VersionData</code>, the <code>build_type_number</code> or <i>revision</i> <strong>can not be detected</strong></dd>
    <!-- 0.8.0-alpha (2024/10/01) -->
    <dt><version-data>0.8.0-alpha</version-data> | Release Date: 2024/10/01</dt>
    <dd>Added <code>toVersionStruct2</code> with full Semantic Versioning support and a permissive conversion.</dd>
    <dd><bug-alert>[BUG]</bug-alert> <code>tolower_str</code> and <code>tolower_Cstr</code> contains a bug that make miss the characters that already in lowercase.</dd>
    <dd><fix-alert>[FIX]</fix-alert> <code>VersionData</code> operators for greater, greater than, less and less than fail to check correctly the complete version number.<dd>
</dl>

*Older versions was not tracked*

# License

A copy of the license is available [here](./LICENSE.txt)

MIT License

Copyright (c) 2024-2025 Matheus L. Silvati

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.