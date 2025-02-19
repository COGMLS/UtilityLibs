# Utility Libraries

## About Utility Libraries repository:

This repository is destined to store the development of important common utility libraries used in projects like settings, log reports, versioning tools, directory and file management, but also to other purposes that can be commonly used in projects.

The **Utility Libraries** repository contains some libraries that was designed first to specific projects and than adapted to a more generic approach, allowing an easy way to be used in many projects. The repository contain libraries focus on C++ development, but some libraries can contain ported versions to other languages. Check the project documentation to see more details about. Each project contain a folder *Docs* that holds their own documentations.

> The repository is focus on development of cross-platform projects, but a few projects can may be an exception depending the platform support or their capabilities.

## Libraries Available:

| Name | Documentation | Version | Cross-platform support | Development branch | Notes |
| ---- | ------------- | ------- | ---------------------- | ------------------ | ----- |
| LoggerLib | [README.md](/Libraries/LoggerLib/README.md) | 3.3.0-alpha.9 | Linux, Windows, Mac | `LoggerLibDev` | Redesigned LoggerLibSolution with support to cross-platform and *wide strings* (`LoggerW` class), useful on Windows systems. **NOTE: From version 3.3.0-alpha.9 introduces a new methodology to store the log data, using `LogDataStore` to store different datatype with a better memory management. This feature uses experimental guard definitions, disabling it will make the library work as the old version, check the documentation to see more details.** |
| LoggerLibSolution | *Not available* | 1.1.0 | No. **Windows only** | `LoggerLibDev` | This is a deprecated project that was part from another one. Is recommended to use `LoggerLib` that has cross-platform support and receives constant updates |
| SettingsLib | [README.md](/Libraries/SettingsLib/README.md) | 3.0.0-alpha | Linux, Windows, Mac | `SettingsLibDev` | This project is under development and was not merged into `master` |
| VersionLib | [README.md](/Libraries/VersionLib/VersionLib/README.md) | 0.8.5-beta | Linux, Windows, Mac | `VersionLibDev` | Version Library is design to easily create relations between version information available in a program and other libraries, allowing to make fast tests of compatible versions. This library is focus on provide [semantic versioning](https://semver.org/spec/v2.0.0.html) support. It can also be permissive on other version formats, check the documentation for more details. **NOTE: The version 0.8.5-beta introduces experimental constructors in `VersionData` class with different parameter positions. This modification can break programs that consume the older versions of this library. It's possible to disable the experimental features and make it work as the older version. Check the documentation to see more details.** |

> **NOTE:** The projects with cross-platform marked with *Macintosh* support was not tested, because I do not have a Mac. But they use ISO C++, ISO C, .Net, or other language/framework that has support and their features are functional on Mac, considering the documentations.

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