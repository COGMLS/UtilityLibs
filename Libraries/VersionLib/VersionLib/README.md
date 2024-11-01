# Version Library

The VersionLib is a versioning library for other libraries and applications to make easier the implementation of version number control with tests to analyze if the value greater, equal, if is a release or alpha build type. It's possible to check if the version is marked as incompatible with an application or library, using an know list of versions, provided by the dependency application or library and test it, with support to generate an exception or not.

The VersionLib contains all necessary methods and data type needed to work, allowing to consume this library without dependencies. All VersionLib methods, data types and classes, are inside the namespace `VersionLib`.

**IMPORTANT:** *This library is under development and the methods may not work as expected. It's important to be aware about possible modifications that may break or be not compatible with previous feature during the development time.*

## Using the Version Library:

The Version Library contains a main header, `VersionLib.hpp`. This header provide all features to be able to work with versioning for any library or application that is using this library to provide versioning support. To use it, version data information, there is the `VersionStruct`, a C-Style data struct for extern C linkage calling and for internal Version Library use. The most recommended version data is the `VersionData` class for C++ context. Both version structure data information holds the same values: `major`, `minor`, `patch`, `build_type`, `build_type_number` and `build` variables. The `VersionData` class contain constructors to allow to create the version object and use the internal operators to compare with other object version.

The `VersionLib.hpp` header contain a global object version available to test and check the current Version Library version with your application or library. This global object is constant and can not be modified.

> ⚠️ **Warning:** The actual development priority is to make sure the C++ functions can work properly. When the algorithms in C++ became stable and reliable, the C methods version will be the main development focus.

### Compatible string version formats:

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

| Format | Status | Example | Notes |
| ------ | ------ | ------- | ----- |
| M      | ✅️ ⚠️ | 10 | This versioning format is not part of standard versioning |
| M.m | ✅️ ⚠️ | 10.2 | This versioning format is not part of standard versioning |
| M.m.p | ✅️ | 10.2.45 | |
| M.m.p-t | ✅️ | 0.8.3-beta | |
| M.m.p-t.r | ✅️ | 3.1.7-beta.6 | |
| M.m.p-t.r b | ✅️ | 7.1.3-rc.1 752 | |
| M b | ❌️ | 10 487 | This format is not recognized |
| M build b | ❌️ | 14 build 77 | This format is not recognized |
| M.m build b | ✅️ | 14.3 build 78 | |
| M.m.p build b | ✅️ | 14.5.6 build 79 | |
| M.m.p-t build b | ✅️ | 3.1.9-rc build 54 | |
| M.m.p-t.r build b | ✅️ | 10.3.1-alpha.3 build 569 | |
| M.m.p.r build b | ⚠️ | 1.6.1.3 build 6100 | Revision is not recognized |
| M.m.p.r | ⚠️ | 2.5.8.15 | Revision is not recognized |
| M.m.p-t b | ⚠️ | 8.1.93-beta 856 | Build number is confused with Build type number |
| M-t | ✅️⚠️ | 10-b | Ok (Major and Build type are detected) |
| M.m-t | ✅️⚠️ | 10.2-alpha | Ok (Major, Minor and Build type are detected) |
| M.m.p b | ❌️ | 10.2.8 456 | Build number is not detected |
| M.m b | ❌️ | 17.5 782 | Build type number is confused with patch |
| M.m.p b | ❌️ | 17.9.5 125 | Build number is not detected |

## Future implementations:

- Full support for extern C linkage
- Support to identify version files by it's name
- Support to detect Windows Metadata version information
- Support for convert `VersionStruct` to `VersionData` and vice-versa.
- Full support for C-Style functions to better support for extern C linkage
- Include the global internal Version Library data.
- Add and update all documentation for the Version Library

## Version Library History:

<!-- Version Library History Table: -->
<dl>
    <!-- 0.8.2-beta (2024/10/09) -->
    <dt><strong>0.8.2-beta</strong></dt>
    <dd>Added copy and move constructors.</dd>
    <dd>Added copy and move operators.</dd>
    <dd><i>On 0.8.2-beta.2: </i>Added <code>VersionLibVersionInfo.hpp</code> file to hold the preprocessor information about the Version Library version information.</dd>
    <dd><i>On 0.8.2-beta.2: </i>Changed the name <code>internalVersionData</code> to a internal method to return the Version Library version information.</dd>
    <dd><strong><font color="red">[BUG]</font></strong> <code>VersionData</code> operators <i><strong>less</strong></i>, <i><strong>less than</strong></i>, <i><strong>greater</strong></i> and <i><strong>greater than</strong></i> are not working as expected.</dd>
    <!-- 0.8.1-beta (2024/10/08) -->
    <dt><strong>0.8.1-beta</strong></dt>
    <dd><strong>[FIX]</strong> <code>tolower_str</code> method, using a traditional algorithm to convert the string to lowercase.</dd>
    <dd><strong><font color="orange">[WARNING]</font></strong> The method <code>tolower_Cstr</code> was not fixed.</dd>
    <dd>Added checking for possible quotes and double quotes use in string BUILD_TYPE.</dd>
    <dd>Added a check for situation when MAJOR.MINOR.PATCH.REVISION is available.</dd>
    <dd><strong><font color="red">[BUG]</font></strong> When sending a version string on format <i>MAJOR.MINOR.PATCH.REVISION</i> to <code>VersionData</code>, the <code>build_type_number</code> or <i>revision</i> <strong>can not be detected</strong></dd>
    <!-- 0.8.0-alpha (2024/10/01) -->
    <dt><strong>0.8.0-alpha</strong></dt>
    <dd>Added <code>toVersionStruct2</code> with full Semantic Versioning support and a permissive conversion.</dd>
    <dd><strong><font color="red">[BUG]</font></strong> <code>tolower_str</code> and <code>tolower_Cstr</code> contains a bug that make miss the characters that already in lowercase.</dd>
    <dd><strong>[FIX]</strong> <code>VersionData</code> operators for greater, greater than, less and less than fail to check correctly the complete version number.<dd>
</dl>

*Older versions was not tracked*

# License

MIT License

Copyright (c) 2024 Matheus L. Silvati

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