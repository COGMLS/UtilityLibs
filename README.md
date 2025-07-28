# Utility Libraries

## About Utility Libraries repository:

This repository is destined to store the development of important common utility libraries used in projects like settings, log reports, versioning tools, directory and file management, but also to other purposes that can be commonly used in projects.

The **Utility Libraries** repository contains some libraries that was designed first to specific projects and than adapted to a more generic approach, allowing an easy way to be used in many projects. The repository contain libraries focus on C++ development, but some libraries can contain ported versions to other languages. Check the project documentation to see more details about. Each project contain a folder *Docs* that holds their own documentations.

**IMPORTANT:** All commits, branch merging and tags are managed in a local server. The GitHub repository is a secondary place to this project and the Pull Requests are not used by the author.

> The repository is focus on development of cross-platform projects, but a few projects can may be an exception depending the platform support or their capabilities.

> [!IMPORTANT]
>
> NEW LIBRARY NAMING:
>
> Now libraries use Utility Libraries Naming Standard for binary files.
> Check the details [here](#utility-libraries-naming-convention)

## Libraries Available:

| Name | Description | Documentation | Stable Version | Last Version | Cross-platform support | Languages or Frameworks Available | Development branch | Notes |
| ---- | ----------- | ------------- | -------------- | ------------ | ---------------------- | --------------------------------- | ------------------ | ----- |
| LoggerLib | Logger library to provide support to manage in real-time the log data creation inside a application, providing support to create multiple log entries and manage them with support to autosave the entries inside the memory. This library support to cross-platform and *wide strings* (`LoggerW` class), useful on Windows systems. | [README.md](/Libraries/LoggerLib/README.md) [ReleaseNotes](/Libraries/LoggerLib/Docs/LoggerLibReleaseNotes.md) | 3.3.3-release | 3.4.0-rc | Linux, Windows, Mac | C++20 | `LoggerLibDev` | *This patch is a memory optimization update, no functional change was made* |
| LoggerLibSolution | This is a deprecated project that was part from another one. Is recommended to use `LoggerLib` that has cross-platform support and receives constant updates | *Not available* | 1.1.0 | 1.1.0 | No. **Windows only** | C++17 | `LoggerLibDev` |  |
| SettingsLib | Library to provide multiple configuration formats, allowing read, edit and write the configurations into a database and save it into a file. | [README.md](/Libraries/SettingsLib/README.md) [ReleaseNotes](/Libraries/SettingsLib/Docs/SettingsLibReleaseNotes.md) | N/A | 3.0.0-alpha | Linux, Windows, Mac | C++20 | `SettingsLibDev` | This project is under development and was not merged into `master` |
| VersionLib | Version Library is design to easily create relations between version information available in a program and other libraries, allowing to make fast tests of compatible versions. This library is focus on provide [semantic versioning](https://semver.org/spec/v2.0.0.html) support. It can also be permissive on other version formats, check the documentation for more details. | [README.md](/Libraries/VersionLib/VersionLib/README.md) [ReleaseNotes](/Libraries/VersionLib/VersionLib/Docs/VersionLibReleases.md) | 0.8.7-beta | 0.9.0-alpha.1 | Linux, Windows, Mac | C++20 | `VersionLibDev` | **NOTE: On version 0.9.0-alpha was redesign and may contain several bugs** |

> **NOTE:** The projects with cross-platform marked with *Macintosh* support was not tested, because I do not have a Mac. But they use ISO C++, ISO C, .Net, or other language/framework that has support and their features are functional on Mac, considering the documentations available.

### Utility Libraries Naming Convention:

To reduce possible incompatibility issues with libraries that are available in more than one version, all libraries will pass to use a naming convention to make a standard way to avoid the possibility to call the wrong library base on the exactly name.

The naming convention will follow the template: **UtilLibs.** *LibraryName* and *LibraryGeneration*

The *LibraryGeneration* normally will match with the library's major version, but it's possible to not be all time like this. Some libraries may offer compatibility with older features, but they may be marked as "deprecated" and can be removed in a future release. Always check the documentation available for more details.

Naming example:

LoggerLib 3th generation pre naming convention: *On Linux:* `libLoggerLib.so` *On Windows:* `LoggerLib.dll`

LoggerLib 3th generation pos naming convention: *On Linux:* `libUtilLibs.LoggerLib3.so` *On Windows:* `UtilLibs.LoggerLib3.dll`

LoggerLib 4th generation (without naming convention): *On Linux:* `libLoggerLib.so` *On Windows:* `LoggerLib.dll`

LoggerLib 4th generation (with naming convention): *On Linux:* `libUtilLibs.LoggerLib4.so` *On Windows:* `UtilLibs.LoggerLib4.dll`

Now it's possible to known the library generation and avoid possible wrong library calling, especially if both libraries are installed in PATH.

## License

A copy is available in this [file](/LICENSE.txt)

MIT License

Copyright (c) 2022-2025 Matheus L. Silvati

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