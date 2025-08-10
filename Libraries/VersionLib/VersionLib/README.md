# Version Library

> **UPDATE 2025/06/06:**
>
> **WARNING:** on version 0.9.x, the VersionLib is now receiving the preparations to bring the definitive 1.0.0 with several modifications of internal methods and data structs.
>
> ***All internal methods created or just declared to C linkage will be moved into another file***
>
> The C linkage components will be calling the C++ internal components. All files for C programs will use a `*.h` extension file. A proper version of `version.hpp` file, for C programs, will be called `version.h` and will not use the namespace `VersionLib` to make easier to other developers to call the C linkage methods. All these functions will use the naming with `VersionLib_`
>
> The components used to data transaction will be redesigned and the structures with "C" on naming will be moved to only C language files.
>
> ***As part of the definitive design for Version Library, all structures will only be used by C linkage, as data transaction, and internal components will focus on classes and C++ code.***

> **NOTE:** *The README.md file will be fully updated in 2025/08/10*

The VersionLib is a versioning library to provide to other libraries and applications a easier way the implementation of version number control and tests to analyze if the version value is greater, equal, etc. The library also check if the *version core* is a release, beta or alpha build type. It's possible to check if the version is marked as incompatible with an application or library, using an known list of versions, provided by the dependency application or library and test it, with support to generate an exception or not.

The VersionLib contains all necessary methods and data type needed to work, allowing to consume this library without dependencies. All VersionLib methods, data types and classes, are inside the namespace `VersionLib`.

This library was developed using ISO C++ 20 and the internal code works with all platforms where this C++ version can be compiled. Platforms tested with the actual development stage: **Linux** and **Windows**.

**IMPORTANT:** *This library is under development and the methods may not work as expected. It's important to be aware about possible modifications that may break or be not compatible with previous feature during the development time.*

## Using the Version Library:

The Version Library contains a main header, `VersionLib.hpp`. This header provide all features to be able to work with versioning for any library or application that is consuming this library to provide versioning support. To use it, the version information must be used in one of available classes: `VersionData` or `SemVer`. The version can be in numeric values to the constructors or use a string that is formatted in one of supported formats (See the formats [here](#compatible-string-version-formats))

The library was designed to work finking on C++ and to work with C external linkage (*C linkage is not ready*). To make it available, there is the `VersionStruct`, a C-Style data struct used inside the library. This struct is used as data transaction between classes and functions to avoid possible cyclic compilation problems and can also offer a way to convert a internal data into another (this is not recommended). The library also offers multiple version data types, a generic one, called `VersionData` and the most recommended type, `SemVer` class for C++ context. Both libraries can work with Semantic Versioning but, `SemVer` class is specialized to make sure all rules for Semantic Versioning will be followed. The `VersionStruct`, `VersionData` and `SemVer` types holds the same information: `major`, `minor`, `patch`, `build_type` (on `VersionStruct` is used `VersionBuildTypeC` struct), `build` variables a flag control `cmpBuild` and the versioning type ID (`VersionType`) variable `type` to identify the type of version. The version type can be: UNKNOWN, SEMANTIC_VERSIONING, CALENDAR_VERSIONING or GENERIC_VERSION. Some `VersionType` values are reserved to future updates.

The redesigned Version Library (starting from version 0.9.0-alpha) now contains two new types, `BuildRelease`, and `VersionBuildType` classes. The type `BuildRelease` holds now both, release type (*old build_type variable*) and the revision number. While the `VersionBuildType` holds an array or vector of `BuildRelease` to support rare cases of combined release information, like *alpha.beta*. ***On version 0.9.0-alpha.1 all structures was deprecated to use in C++ code and will be used only for data transaction to C linkage***.

The generic `VersionData` and `SemVer` classes contains multiple constructors to allow the easiest object creation of the version object and use the internal operators to compare with other object version.

> **NOTE: `VersionData` and `SemVer` can work holding the same data, but no compatibility between them was made**

The `VersionLib.hpp` header contain a function called `internalVersionData` that return the library version object, using a `VersionData` type, which can be used to test and check the current Version Library version with your application or other library. If necessary use the proper Semantic Versioning class, use the function `internalSemVer` that will return a `SemVer` object type.

> ⚠️ **Warning:** The actual development priority is to make sure the C++ functions can work properly. When the algorithms and components in C++ become stable and reliable, the C methods version will be the main development focus.

## About other documentation:

This project contains other documentation files available in [Docs folder](./Docs/).

| File | Documentation | Path |
| ---- | ------------- | ---- |
| VersionLibInfo | Information about the project, known bugs, future implementations, deprecated and removed features | [VersionLibInfo.md](./Docs/VersionLibInfo.md)
| VersionLibReleases | Complete version history about this project. In the README.md file only contains part of the version changes | [VersionLibReleases.md](./Docs/VersionLibReleases.md)
| TechnicalInformation | Technical information document to offer the details of the implementations | [TechnicalInformation.md](./Docs/TechnicalInformation.md)
| VersionLibComponentsDiagram | Version Library components relationship diagram | [VersionLibComponentsDiagram.pdf](./Docs/VersionLibComponentsDiagram.pdf)

> Other documentation files will be added in a future.

### Compatible string version formats:

The `VersionLib` was designed to work primary with [Semantic Versioning](https://semver.org/), but also offer other version compatibility with a permissive algorithm. When using a non semantic versioning, the **custom format is not preserved, at least this time**. If you export the string version, it will be exported in semantic versioning format.

> *Note: the generic `VersionData` class will receive an update to support a better generic approach for other formats, including custom versioning*

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

> **WARNING: ON VERSION 0.9.0-alpha SEVERAL MODIFICATIONS WAS MADE AND TO PROVIDE SUPPORT TO THE ADDITIONAL AUXILIARY DATA TYPES AND SOME METHODS HAVE THEIR DATA TYPES RETURN MODIFIED. THOSE MODIFICATIONS CAN BREAK YOUR CODE IF YOU USE THOSE FUNCTIONS.**

### Recent Implementations:

- Support for convert `VersionStruct` to `VersionData` and vice-versa.
- New experimental version string detection in `toVersionStrut2` method.
- ~~New experimental memory layout of `VersionStruct` to reduce the memory size allocation. (See the details in [here](#versionstruct-and-versiondata-memory-layout))~~
- Support to create objects versions without warning messages with wrapper constructors.
- **CHANGED `build_type_number` VARIABLE TO `build_revision` TO A BETTER COMPREHENSION.**
- Add support to compare versions with build information.
- Replace `BuildType` enum to `VersionBuildType` class as main storage of version release type
    - *Only Alpha:* Experimental support to `VersionBuildType`
    - *Only Alpha:* Experimental `VersionBuildType` can now hold a vector of multiple release data using `BuildRelease` objects
- *Only Alpha:* Experimental support to new `BuildType` entries: `PRE_ALPHA`, `CANARY`, `DEVELOPMENT`, `PRE_RELEASE`. **NOTE: Those new entries are not part of Semantic Versioning and can be removed in other development versions if they do not stand for a better permissive approach.**
- Add `BuildRelease` class to store `BuildType` and `revision` in same place.
- **Redesign the internal components to support correctly the new data types**

### Implementations under development:

- Add Version Lib errors and exceptions components
- Add and update all documentation for the Version Library
- Complete support to Semantic Versioning (including combined releases - alpha.beta and others)
- Support to mathematical approach to determinate the release and revision information data is higher, lower or equal to another.
- Support to combined build type information. I.e. `1.0.0-alpha.beta`
- Support to build metadata in version string
- Add `VersionType` to identify the versioning type
- Add `idVersionType` method to identify the type of versioning
- Add generic approach to `VersionData`
- Add official library Semantic Versioning (`SemVer`) class
- Add updated ~~`toVersionStruct3`~~ `toSemVerTokens` method, to identify a better component detection
- Add `BuildMetadata` class to store the build metadata
- Add VersionToken
- Add VersionTokenData

### Future Implementations:

- Full support for C-Style functions to better support for extern C linkage
- Full support for extern C linkage
- Support to identify version files by it's name
- Support to detect Windows Metadata version information
- Support to Calendar Versioning
- Support to Hybrid Calendar Versioning with Semantic Versioning
- Complete support to custom versioning formats

## Version Library History:

<!-- Version Library History Table: -->
<head>
    <link rel="stylesheet" href="./Docs/CSS/ReleaseNotes.css">
    <link rel="stylesheet" href="Libraries/VersionLib/VersionLib/Docs/CSS/ReleaseNotes.css">
</head>
<dl>
    <!-- 0.9.1-alpha.3 (2025/08/10) -->
    <dt><version-data>0.9.1-alpha.3</version-data> | Release Date: 2025/08/10</dt>
    <dd>Added <code>TokenClassifier</code> base class</dd>
    <dd>Added <code>SemVerDict</code> token classifiers for Semantic Versioning</dd>
    <dd>Added <strong>TokenDictionaries.hpp</strong> main header</dd>
    <dd><note-alert>[NOTE]</note-alert> The <code>SemVerDict</code> class contain the same algorithm from <code>toSemVerTokens</code> as part of the preparations to make the library fully compatible with token system</dd>
    <dd><strong>Moved <code>SemVer</code> and <code>VersionData</code> classes files to <i>Formats</i> subdirectory</strong></dd>
    <dd>Adapted the library files to new use <i>Formats</i> subdirectory location</dd>
    <!-- 0.9.1-alpha.2 (2025/08/07) -->
    <dt><version-data>0.9.1-alpha.2</version-data> | Release Date: 2025/08/07</dt>
    <dd>Added <code>FAIL_TO_IDENTIFY_TOKEN</code> in <strong>VersionTokenType</strong></dd>
    <dd><fix-alert>[FIX]</fix-alert> experimental algorithm <code>toSemVerTokens</code> does not identify the correct data type for build number</dd>
    <!-- 0.9.1-alpha.1 (2025/08/06) -->
    <dt><version-data>0.9.1-alpha.1</version-data> | Release Date: 2025/08/06</dt>
    <dd><fix-alert>[FIX]</fix-alert> identification of release types in <code>toSemVerTokens</code></dd>
    <dd><fix-alert>[FIX]</fix-alert> metadata with dashes and dots are not recognized correctly in <code>toSemVerTokens</code></dd>
    <dd><fix-alert>[FIX]</fix-alert> identification of build value in <code>toSemVerTokens</code></dd>
    <dd><bug-alert>[BUG]</bug-alert> build value is classified as short numerical value and not long type in <code>toSemVerTokens</code></dd>
    <dd>Removed unused variables in <code>toSemVerTokens</code></dd>
    <!-- 0.9.1-alpha (2025/08/06) -->
    <dt><version-data>0.9.1-alpha</version-data> | Release Date: 2025/08/06</dt>
    <dd>Added support to <code>unsigned short</code></dd>
    <dd>Added <code>VersionTokenType</code> enum</dd>
    <dd>Added <code>VersionTokenDataType</code> enum</dd>
    <dd>Added <code>VersionTokenData</code> class</dd>
    <dd>Added <code>VersionToken</code> class</dd>
    <dd>Added <code>toSemVerTokens</code> method</dd>
    <dd>Added auxiliary method <code>getTokenTypeStr</code></dd>
    <dd>Added new experimental feature <strong>VERSION_LIB_ENABLE_EXPERIMENTAL_TOSEMVERTOKENS_METHOD2</strong> for alternative algorithm in <i>toSemVerTokens</i></dd>
    <dd>Added <code>isRelease</code> method</dd>
    <dd>Changed <code>unsigned long long</code> to <code>unsigned long</code></dd>
    <dd>Changed <code>VersionClass</code> to <code>VersionData</code></dd>
    <dd>Removed <code>toVersionStruct3</code></dd>
    <dd><fix-alert>[FIX]</fix-alert> metadata treatment in <code>toSemVerTokens</code></dd>
    <dd><strong>Deprecated <code>VersionStruct</code></strong></dd>
    <dd><strong>NOTE:</strong> <code>VersionData</code> use temporary <code>toVersionStruct2</code></dd>
    <!-- 0.9.0-alpha.3 (2025/06/12) -->
    <dt><version-data>0.9.0-alpha.3</version-data> | Release Date: 2025/06/12</dt>
    <dd>Internal changes to prepare the Version Library to support correctly the components for C linkage.</dd>
    <dd><fix-alert>[FIX]</fix-alert> revision number of the previous release (0.9.0-alpha.2) was not updated. This release has the correct value.</dd>
    <!-- 0.9.0-alpha.2 (2025/06/06) -->
    <dt><version-data>0.9.0-alpha.2</version-data> | Release Date: 2025/06/06</dt>
    <dd>Separated methods from files <code>Tools.hpp</code> <code>Tools.cpp</code> into <code>CommonTools.hpp</code> <code>CommonTools.cpp</code>, <code>ReleaseTools.hpp</code> <code>ReleaseTools.cpp</code> and <code>VersionTools.hpp</code> <code>VersionTools.cpp</code> to reduce possible future compilation cyclic dependencies</dd>
    <!-- 0.9.0-alpha.1 (2025/04/18) -->
    <dt><version-data>0.9.0-alpha.1</version-data> | Release Date: 2025/04/18</dt>
    <dd><fix-alert>[FIX]</fix-alert> toVersionStruct2 missing revision</dd>
    <dd><fix-alert>[FIX]</fix-alert> toVersionStruct2 missing build release when no revision is available</dd>
    <dd><fix-alert>[FIX]</fix-alert> toVersionStruct2 does not store revision</dd>
    <!-- 0.9.0-alpha (2025/04/17) -->
    <dt><version-data>0.9.0-alpha</version-data> | Release Date: 2025/04/17</dt>
    <dd><strong>Redesign the internal components to bring support to new data types, support to combined release data and to provide a better support to other formats in the future</strong></dd>
    <dd>Added <code>BuildRelease</code> class to store the <code>BuildType</code> data and the revision values. It also has a flag to hold the conversion data status</dd>
    <dd>Added support to hold multiple releases in <code>VersionBuildType</code> class</dd>
    <dd>Added initial support to build metadata</dd>
    <dd>Added initial support to detect Semantic Versioning format</dd>
    <dd>Added proper Semantic Versioning class: <code>SemVer</code> using modified <code>VersionData</code> class code to work with additional flags and method checks to see if is a correct Semantic Versioning data <strong>NOTE: This class is not ready to work as expected yet</strong></dd>
    <dd>Added new struct types to make data transaction and use them to C linkage: <code>VersionBuildTypeC</code> and <code>VersionReleaseDataC</code></dd>
    <dd>Changed the <code>VersionData</code> to be a generic version data approach to all other future version formats</dd>
    <dd><strong>NOTE: THE MODIFICATIONS MADE IN THIS VERSION BREAK THE BETA CODE VERSION</strong></dd>
    <dd>Removed deprecated <code>toVersionStruct</code> function</dd>
    <dd>Added <code>VersionType</code> to determinate the versioning type used in <code>VersionStruct</code> and <code>VersionData</code></dd>
    <dd>Added <code>idVersionType</code> method to identify the supported versioning formats or custom formats and return a <code>VersionType</code> <strong>NOTE: This method is not ready to be used</strong></dd>
    <dd>Modified <code>VersionStruct</code> to support generic version formats as experimental feature</dd>
    <dd>Previous memory optimizations was removed after all redesign work. New memory optimizations will be made it in a future release</dd>
    <dd>Removed deprecated constructors in <code>VersionData</code></dd>
    <dd>Removed unnecessary or unused experimental definition guards</dd>
    <dd>Experimental constructors in <code>VersionData</code> are not marked as experimental feature</dd>
    <dd><strong>IMPORTANT: THIS NEW VERSION CONTAINS SEVERAL MODIFICATIONS THAT MAY CONTAIN NEW BUGS THAT WAS NOT TRACKED YET</strong></dd>
    <dd><strong>THE EXPERIMENTAL MODIFICATIONS MAY BREAK THE SUPPORT TO LAST BETA VERSION (0.8.7-beta).</strong> If you need to use the last beta, use the <strong>git tag - <i>VersionLib_0.8.7-beta</i></strong> to compile the library</dd>
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