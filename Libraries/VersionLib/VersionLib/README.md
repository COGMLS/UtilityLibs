# Version Library

The VersionLib is a versioning library for other libraries and applications to make easier the implementation of version number control with tests to analyze if the value greater, equal, if is a release or alpha build type. It's possible to check if the version is marked as incompatible with an application or library, using an know list of versions, provided by the dependency application or library and test it, with support to generate an exception or not.

The VersionLib contains all necessary methods and data type needed to work, allowing to consume this library without dependencies. All VersionLib methods, data types and classes, are inside the namespace `VersionLib`.

**IMPORTANT:** *This library is under development and the methods may not work as expected. It's important to be aware about possible modifications that may break or be compatible with previous feature during the development time.*

## Using the Version Library:

The Version Library contains a main header, `VersionLib.hpp`. This header provide all features to be able to work with versioning for any library or application that is using this library to provide versioning support. To use it, version data information, there is the `VersionStruct`, a C-Style data struct for extern C linkage calling and for internal Version Library use. The most recommended version data is the `VersionData` class for C++ context. Both version structure data information holds the same values: `major`, `minor`, `patch`, `build_type`, `build_type_number` and `build` variables. The `VersionData` class contain constructors to allow to create the version object and use the internal operators to compare with other object version.

The `VersionLib.hpp` header contain a global object version available to test and check the current Version Library version with your application or library. This global object is constant and can not be modified.

## Version Library History:

<dl>
    <dt><strong>0.8.0-alpha</strong></dt>
    <dd>Added <code>toVersionStruct2</code> with full Semantic Versioning support and a permissive conversion.</dd>
    <dd><strong><font color="red">[BUG]</font></strong> <code>tolower_str</code> and <code>tolower_Cstr</code> contains a bug that make miss the characters that already in lowercase.</dd>
    <dd><strong>[FIX]</strong> `VersionData` operators for greater, greater than, less and less than fail to check correctly the complete version number.<dd>
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