# Utility Libraries

## About Utility Libraries repository:

This repository is destined to store the development of important common utility libraries used in projects like settings, log reports, versioning tools, directory and file management, but also to other purposes that can be commonly used in projects.

The **Utility Libraries** repository contains some libraries that was designed first to specific projects and than adapted to a more generic approach, allowing an easy way to be used in many projects. The repository contain libraries focus on C++ development, but some libraries can contain ported versions to other languages. Check the project documentation to see more details about. Each project contain a folder *Docs* that holds their own documentations.

**IMPORTANT:** All commits, branch merging and tags are managed in a local server. The GitHub repository is a secondary place to this project and the Pull Requests are not used by the author.

> The repository is focus on development of cross-platform projects, but a few projects can may be an exception depending the platform support or their capabilities.

## Libraries Available:

| Name | Description | Documentation | Stable Version | Last Version | Cross-platform support | Languages or Frameworks Available | Development branch | Notes |
| ---- | ----------- | ------------- | -------------- | ------------ | ---------------------- | --------------------------------- | ------------------ | ----- |
| LoggerLib | Logger library to provide support to manage in real-time the log data creation inside a application, providing support to create multiple log entries and manage them with support to autosave the entries inside the memory. This library support to cross-platform and *wide strings* (`LoggerW` class), useful on Windows systems. | [README.md](/Libraries/LoggerLib/README.md) [ReleaseNotes](/Libraries/LoggerLib/Docs/LoggerLibReleaseNotes.md) | 3.3.1-release | 3.4.0-rc | Linux, Windows, Mac | C++20 | `LoggerLibDev` |  |
| LoggerLibSolution | This is a deprecated project that was part from another one. Is recommended to use `LoggerLib` that has cross-platform support and receives constant updates | *Not available* | 1.1.0 | 1.1.0 | No. **Windows only** | C++17 | `LoggerLibDev` |  |
| SettingsLib | Library to provide multiple configuration formats, allowing read, edit and write the configurations into a database and save it into a file. | [README.md](/Libraries/SettingsLib/README.md) [ReleaseNotes](/Libraries/SettingsLib/Docs/SettingsLibReleaseNotes.md) | N/A | 3.0.0-alpha | Linux, Windows, Mac | C++20 | `SettingsLibDev` | This project is under development and was not merged into `master` |
| VersionLib | Version Library is design to easily create relations between version information available in a program and other libraries, allowing to make fast tests of compatible versions. This library is focus on provide [semantic versioning](https://semver.org/spec/v2.0.0.html) support. It can also be permissive on other version formats, check the documentation for more details. | [README.md](/Libraries/VersionLib/VersionLib/README.md) [ReleaseNotes](/Libraries/VersionLib/VersionLib/Docs/VersionLibReleases.md) | N/A | 0.8.7-beta | Linux, Windows, Mac | C++20 | `VersionLibDev` | **NOTE: The version 0.8.5-beta introduces experimental constructors in `VersionData` class with different parameter positions. This modification can break programs that consume the older versions. It's possible to disable the experimental features and make it work to previous version of 0.8.5-beta. Check the documentation to see more details.** |

> **NOTE:** The projects with cross-platform marked with *Macintosh* support was not tested, because I do not have a Mac. But they use ISO C++, ISO C, .Net, or other language/framework that has support and their features are functional on Mac, considering the documentations available.

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