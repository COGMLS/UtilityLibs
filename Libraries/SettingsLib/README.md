# Settings Library

## About

The Settings Library is designed to facilitate developers to implement configuration file and configuration flags. The library create an database in the memory when a configuration file is opened and offer support to *add*, *remove*, *search*, *get* and *set* entries and values for the database.

> **NOTE:** **This project is under development and the datatype, classes, methods and algorithms may not work as expected or may not be complete implemented.**

The **SettingsLib** is focus on cross-platform development and use the maximum of ISO C++ as possible. The library uses **C++20** and **other languages support plans was dropped**.

> **NOTE:** The SettingsLibSolution contains an exported settings library version from another project. The actual **SettingsLib** contains a generic version with improvements that can be better for some projects and with cross-platform support.

## About deprecated versions:

The actual **UtilityLibs** repository contain previous versions of **SettingsLib**, located in [SettingsLibSolution](./SettingsLibSolution). This directory contain the version `2.0.0` and was **deprecated** during the development time. This version only support the Microsoft Visual C++ implementations, specially because it uses `std::exception` implementation from Microsoft's.

The deprecated library was never finished, but was used with a few personal projects and, for this reason was keep it in the repository. The version **3.0.0** was started with a complete different approach and following the configurations standards like `ini` configurations.

## Support for Configuration Files:

| Configuration | Status |
| ------------- | ------ |
| Ini           | In development |
| JSON          | Planned to implement |
| Binary format | Planned to implement |

## Settings Library project:

### Future implementations:

* Support to JSON
* Support to binary format
* Complete support for cross-platform

### Version history:

<dl>
    <!-- 3.0.0-alpha.24 (2024/11/07) -->
    <dt><strong>3.0.0-alpha.24</strong></dt>
    <dd><u>Added first cross-platform support</u></dd>
    <dd>Added <code>GeneralException</code> to replace Microsoft's non standard C++ <code>std::exception</code> located in <b><i>Components/Exceptions</i></b></dd>
    <dd>Reorganized <code>SettingsIni</code> components to <b><i>Components/Configs/Ini</i></b></dd>
    <dd>Revised <code>SettingsLibVersion</code></dd>
    <dd>Updated <code>SettingsLib</code> version</dd>
    <dd>Updated version methods</dd>
    <dd><b><font color="red">[CAUTION]</font></b> This version may contain a possible regression: The <code>SettingsLib</code> compile on Unix systems but fail to link and consume it on other applications</dd>
    <!-- 3.0.0-alpha.23 (2024/09/23) -->
    <dt><strong>3.0.0-alpha.23</strong></dt>
    <dd>Added new constructor.</dd>
    <dd>Updated the documentation.</dd>
    <dd>Added <code>readLine</code>, <code>setConfigName</code> and <code>getConfigName</code>, <code>isWideData</code>, <code>isConfigFileOk</code>, <code>isUsingConfigFileStream</code> methods.</dd>
    <dd>Added <code>isConfigStreamOk</code> method.</dd>
    <!-- 3.0.0-alpha.22 (2024/09/23) -->
    <dt><strong>3.0.0-alpha.22</strong></dt>
    <dd>Added new methods into <code>ConfigIni</code> class.</dd>
    <dd>Updated the class documentation.</dd>
    <dd><b>NOTE:</b> only few methods are ready to be used at this moment.</dd>
    <!-- 3.0.0-alpha.21 (2024/06/31) -->
    <dt><strong>3.0.0-alpha.21</strong></dt>
    <dd>Added declarations for comment methods.</dd>
    <dd>Changed the comment data to use <code>std::unique_ptr</code>.</dd>
    <dd>Added <code>getComment</code> and <code>setComment</code> methods.</dd>
    <dd>Updated the copy constructor and operator.</dd>
    <dd>Added new object control variables.</dd>
    <dd>Added new methods declarations.</dd>
    <dd>Updated the documentation.</dd>
    <dd>Added functions declarations for wide strings.</dd>
    <dd>Added <code>convertDataStore2Str</code>.</dd>
    <dd>Added <code>convertObj2CfgLine</code>.</dd>
</dl>

**NOTE:** Previous version history was not tracked

## License

A copy is available in this [file](./LICENSE.txt)

MIT License

Copyright (c) 2022-2024 Matheus L. Silvati

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