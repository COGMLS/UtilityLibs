# Logger Library History:

## About this file:

This file contain the tracked version and modifications of the Logger Library project since was included in the **UtilityLibs**. Older library versions was not tracked and will not be included in this file.

An copy or partial copy of this history table is available in the `README.md` file in the root of the project.

## Logger Library History:

<!-- Logger Library History Table: -->
<style>
    version-data
    {
        font-weight: bold;
    }
    note-alert
    {
        font-weight: bold;
        color: blue;
    }
    fix-alert
    {
        font-weight: bold;
    }
    bug-alert
    {
        font-weight: bold;
        color: red;
    }
    warning-alert
    {
        font-weight: bold;
        color: orange;
    }
</style>
<dl>
    <!-- 3.3.0-alpha (2025/01/15) -->
    <dt><version-data>3.3.0-alpha</version-data></dt>
    <dd>Cleaned unused code</dd>
    <dd>Added alternative algorithm for sorting, using the bubble sort instead of selection sort. <strong>The selection sort is disabled by a preprocessor directive and is marked as deprecated</strong></dd>
    <dd><fix-alert>[FIX]</fix-alert> string copy <code>LOGGER_LIB_BUILD_TYPE</code> to version build type</dd>
    <dd>Updated constructor parameters when receiving a <code>std::filesystem::path</code> to control if will use the file date time and will apply the timezone correction.</dd>
    <dd><fix-alert>[FIX]</fix-alert> sorting <code>LogFileDateTime</code> objects in descending and ascending order</dd>
    <dd><fix-alert>[FIX]</fix-alert> missing last date time character from string information in <code>LogFileDateTime</code> constructor.</dd>
    <dd><note-alert>[NOTE]</note-alert> This version of Logger Library appears to be very stable, but no tests with sorting log files was made on Windows systems. Considering the lack of tests to one important platform, the LoggerLib will be marked as <code>alpha</code></dd>
    <dd><i>(Added in 2025/01/20) </i>Add <code>LoggerLib.hpp</code>a main header to include all library components on build 64</dd>
    <!-- 3.2.0-alpha (2024/12/18) -->
    <dt><version-data>3.2.0-alpha</version-data></dt>
    <dd>Added <code>LogFileDateTime</code> class to focus on log file date time information report (not based on Last Time Write or Creation Time)</dd>
    <dd>Added <code>sortLogFileList</code> and <code>sortLogFileList2</code> to sort the log file list returned by <code>getLogFileList</code> method</dd>
    <dd><note-alert>[NOTE]</note-alert> The methods <code>sortLogFileList</code> and <code>sortLogFileList2</code> still in development and are not sorting correctly, missing some files from correct order. These functions may receive a new name or new version. Use with caution.</dd>
    <dd><fix-alert>[FIX]</fix-alert>Compiling the <code>LoggerLib</code> won't result in a ISO C++ forbidden warning when converting a <code>const char*</code> string to <code>char*</code></dd>
    <!-- 3.1.2-release (2024/10/08) -->
    <dt><version-data>3.1.2-release<version-data></dt>
    <dd>Changed the getVersionStr parameter to accept an copy and not the variable address any more.</dd>
    <dd>Added missing <code>PATCH number</code></dd>
    <dd>Added better <code>const char[]</code> conversion to <code>char*</code></dd>
    <dd><fix-alert>[FIX]</fix-alert> Version string conversion when <code>BUILD_TYPE</code> is marked as <code>release</code>.</dd>
    <dd><fix-alert>[FIX]</fix-alert> Revision number position when converting version to string.</dd>
    <dd>New tests with LoggerLib.</dd>
    <dd><i>(Added in 2024/12/06) </i><bug-alert>[BUG]</bug-alert> On Unix systems the log files entries are not added following the naming order as happens on Windows systems.</dd>
    <!-- 3.1.1-release (2024/10/07) -->
    <dt><version-data>3.1.1-release<version-data></dt>
    <dd>Added LoggerLib API in all header files, removing the necessity to use <code>LoggerLibDef.hpp</code></dd>
    <dd>Disabled the use of <code>pch.h</code> for non Windows builds</dd>
    <dd><fix-alert>[FIX]</fix-alert> the use of non C++ Standard from Microsoft for <code>std::fstream</code> and <code>std::wstream</code> constructors</dd>
    <dd>Added <code>LoggerLibVersion.hpp</code> and <code>LoggerLibVersionTools.hpp</code> to allow a compatible way to communicate with <code>VersionLib</code> from UtilityLibs with string version conversion or use the raw version values</dd>
    <!-- 3.1.0-beta (2024/09/23) -->
    <dt><version-data>3.1.0-beta</version-data></dt>
    <dd>Added <code>LoggerW</code> and <code>LogEntryW</code> classes</dd>
    <dd>Added <code>convertDateTime2LogStrEntryW</code></dd>
    <dd>Update CMakeLists.txt</dd>
    <dd>Added <code>LoggerException.cpp</code> and <code>LoggerException.hpp</code></dd>
    <!-- 3.0.0-alpha (2024/09/16) -->
    <dt><version-data>3.0.0-alpha</version-data></dt>
    <dd>Added <strong><i>LoggerLib V1</i></strong> migrated for CMake</dd>
    <dd>Added console for tests</dd>
    <dd>Added <strong>LoggerLib V1</strong></dd>
    <dd><note-alert>[NOTE]</note-alert> The LoggerLib contains the same C++ code from Visual Studio Solution (LoggerLibSolution)</dd>
    <dd><note-alert>[NOTE]</note-alert> This code was tested with <strong>C++20</strong> and <strong>C++17</strong></dd>
    <dd><note-alert>[NOTE]</note-alert> Some compiler parameters wasn't set on CMakeLists like Spectre Mitigation</dd>
</dl>

*Older versions was not tracked*