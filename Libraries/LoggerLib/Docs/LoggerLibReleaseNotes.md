# Logger Library History/Release Notes:

## About this file:

This file contain the tracked version and modifications of the Logger Library project since was included in the **UtilityLibs**. Older library versions was not tracked and will not be included in this file.

An copy or partial copy of this history table is available in the `README.md` file in the root of the project.

## Logger Library Release History:

<!-- Logger Library History Table: -->
<head>
    <link rel="stylesheet" href="./CSS/ReleaseNotes.css">
</head>
<dl>
    <!-- 3.3.3-release (2025/07/28) -->
    <dt><version-data>3.3.3-release</version-data> | Release Date: 2025/07/28</dt>
    <dd><strong>Optimized memory usage, removing unnecessary/redundant components</strong></dd>
    <!-- 3.3.2-release (2025/05/13) -->
    <dt><version-data>3.3.2-release</version-data> | Release Date: 2025/05/13</dt>
    <dd><fix-alert>[FIX]</fix-alert> <strong>Windows platform library compilation</strong></dd>
    <dd><fix-alert>[FIX]</fix-alert> Missing correct compile definition to Windows platforms</dd>
    <dd><fix-alert>[FIX]</fix-alert> Missing correct instruction to check data between two <code>LogDataStore</code> objects, leading to compilation fail on Windows platform</dd>
    <dd>Added new experimental feature control: <i>LOGGER_ENABLE_EXPERIMENTAL_LOG_ENTRY_OPERATORS</i></dd>
    <dd><strong>Disabled <code>operator<<</code> when <code>LogDataStore</code> is only enabled to avoid compilation failure on Windows platforms</strong></dd>
    <dd><strong>IMPORTANT NOTE:</strong> On last release version introduced LogDataStore feature, and the testing process was not correctly followed. Before launching a release version of the library, all platforms that I have (Windows and Linux) <strong>must pass</strong> through the console test. The same console used to present the library functionalities. I did not test correctly on Windows platform. This patch fixes this mistake with almost the same expected behavior, except with <code>LogEntry</code> and <code>LogEntryW</code> Stream Insertion operators (<code>operator<<</code>) that was disabled to avoid compilation failures.</dd>
    <dd><i>(Added in 2025/06/27)</i> <strong>Second release: </strong><strong>New library naming.</strong> Now library uses Utility Libraries Naming Standard that follows UtilLibs.<i>LibraryName<strong>LibraryGeneration</strong></i>. This change will prepare the project for next modifications that may push to version 4.x and break current compatibility. In this case, the programs linked with this new naming convention, will be able to use version 3.x.y and keep working without the possibility to call the incompatible library. <i><strong>This new release does not modify any internal components</i></strong></dd>
    <!-- 3.4.0-release candidate (2025/04/08) -->
    <dt><version-data>3.4.0-release candidate</version-data> | Release Date: 2025/04/08</dt>
    <dd>Changed private method <code>cleanData</code> to <code>setDataStore</code> in <strong>LogDataStore</strong></dd>
    <dd>Optimized <code>LogDataStore</code> using less instructions to operate</dd>
    <dd>Added <code>LOG_DATA_FAIL</code> in <strong>LogDataType</strong> to determinate when <i>LogDataStore</i> fail to set the data correctly</dd>
    <dd><fix-alert>[FIX]</fix-alert> Added experimental log file name in UTC time on Linux and MacOS platforms</dd>
    <dd><code>LogDataStore</code> is now the new way to store data in Logger Library</dd>
    <!-- 3.3.1-release (2025/03/31) -->
    <dt><version-data>3.3.1-release</version-data> | Release Date: 2025/03/31</dt>
    <dd>Added support to UTC format</dd>
    <dd>Added new constructor in <code>LogDataStore</code> with support to automatically define time precision</dd>
    <dd><fix-alert>[FIX]</fix-alert> Local datetime on Linux and MacOS</dd>
    <dd><fix-alert>[FIX]</fix-alert> missing highPrecision check in Equality Operators in <code>Logger</code> and <code>LoggerW</code></dd>
    <!-- 3.3.0-release (2025/03/26) -->
    <dt><version-data>3.3.0-release</version-data> | Release Date: 2025/03/26</dt>
    <dd>Removed <code>sortLogFileList2</code></dd>
    <dd>Added experimental feature guards</dd>
    <dd><fix-alert>[FIX]</fix-alert> missing autosave feature when destructor is called.</dd>
    <dd><fix-alert>[FIX]</fix-alert> autosave writing log entries.</dd>
    <dd><fix-alert>[FIX]</fix-alert> missing autosave treatment when logEntries not reach max entries.</dd>
    <dd><fix-alert>[FIX]</fix-alert> missing treatment when maxLogEntries is zero.</dd>
    <dd><note-alert>NOTE:</note-alert> This release version does not implement the <code>LogDataStore</code> and does not provide a better memory management to store the data</dd>
    <dd><strong>The <i>alpha</i> version features will be moved to next version 3.x</strong></dd>
    <dd><strong>Some <i>beta</i> version features will be moved to next version 3.3.x or 3.4.x</strong></dd>
    <!-- 3.3.0-alpha.10 (2025/03/14) -->
    <dt><version-data>3.3.0-alpha.10</version-data> | Release Date: 2025/03/14</dt>
    <dd>Added getLogDtReg</dd>
    <dd>Added missing treatment to export <code>LogDataStore</code> information</dd>
    <dd>Updated <code>operator<<</code></dd>
    <dd>Added documentation about experimental preprocessor definition guards</dd>
    <dd>Removed experimental <code>LogDataStore</code> equality operator</dd>
    <!-- 3.3.0-alpha.9 (2025/02/18) -->
    <dt><version-data>3.3.0-alpha.9</version-data> | Release Date: 2025/02/18</dt>
    <dd><note-alert>[NOTE]</note-alert> THE PREVIOUS ALPHA VERSIONS WAS NOT DOCUMENTED.</dd>
    <dd><warning-alert>[IMPORTANT]</warning-alert> <b>THIS VERSION CONTAINS SEVERAL MODIFICATIONS INSIDE THE MAIN COMPONENTS</b></dd>
    <dd>Added new experimental definition flags.</dd>
    <dd>Moved <code>dtReg</code> in <code>LogEntry</code> and <code>LogEntryW</code> to it’s own experimental code portion. Now it's possible to control this experimental feature independently</dd>
    <dd>Added full support to <code>LogDataStore</code> in a experimental code part. Allowing use less memory and various datatype without need convert it's values to string.</dd>
    <dd><note-alert>[NOTE]</note-alert> The data exportation from <code>LogDataStore</code> was not fully tested</dd>
    <dd>Added partial support to <code>dtReg</code> in a experimental code part. Now each log entry contains it's own date and time registry. Coping the objects will copy the registry.</dd>
    <dd>Added equality operators to <code>LogDataStore</code></dd>
    <dd><note-alert>[NOTE]</note-alert> <code>LogDataStore</code> received experimental <i>friend</i> equality operators during tests to mitigate a compiler warning. These operators are disabled by default</dd>
    <dd><fix-alert>[FIX]</fix-alert> coping data on MoveConstructor.</dd>
    <dd><fix-alert>[FIX]</fix-alert> missing <code>seconds</code> equality verification from <code>LoggerLocalDateTime</code> union in <code>LogEntry</code> and <code>LogEntryW</code> in equality operations, when LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE is <b>disabled</b></dd>
    <dd><fix-alert>[FIX]</fix-alert> The standard algorithm to make the equality test between the both <code>logEntries</code> of <b>Logger</b> and <b>LoggerW</b> classes fails when <code>LogDataStore</code> is enabled</dd>
    <dd><fix-alert>[FIX]</fix-alert> Making equality of <code>LogEntry</code> or <code>LogEntryW</code> show the warning message: <i>C++20 says that these are ambiguous, even though the second is reversed</i> on GCC from equality operators</dd>
    <!-- 3.3.0-alpha.5 (2025/02/17) -->
    <dt><version-data>3.3.0-alpha.5</version-data> | Release Date: 2025/02/17</dt>
    <dd>Added experimental code control guards to enable/disable experimental features</dd>
    <dd>Added <code>highPrecision</code> flag in <code>LoggerLocalDateTime</code>.</dd>
    <dd>Added <code>useHighPrecision</code> parameter in <code>getLoggerDateTime</code> function.</dd>
    <dd>Removed warning message on documentation.</dd>
    <dd>Moved preprocessor definition to control the experimental sorting algorithm to LoggerExperimental.hpp</dd>
    <dd>Added experimental <code>LogDataStore</code> class.</dd>
    <dd>Moved and enhanced the LogDataType enum to LogDataStore.hpp</dd>
    <dd>Moved and modified the LogEntryData union to LogDataStore.hpp</dd>
    <dd><warning-alert>[WARNING]</warning-alert> The <code>LogDataStore</code> is under development and may contain bugs.</dd>
    <dd>Added support to experimental <code>LogDataStore</code> in <code>LogEntry</code> and <code>LogEntryW</code>.</dd>
    <dd>Added to <code>LogEntry</code> and <code>LogEntryW</code> <code>getTitle</code>, <code>getMessage</code>, <code>getType</code>, <code>getData</code> methods.</dd>
    <dd>Added to <code>LogEntry</code> and <code>LogEntryW</code> <code>getStrData</code> method for non-experimental code.</dd>
    <dd><note-alert>[NOTE]</note-alert> Using experimental <code>LogDataStore</code> compatible code, will make some methods not work as expected at this moment</dd>
    <dd>Added experimental <code>LogFormat</code> class</dd>
    <dd>Added experimental <code>LogFormatToken</code> class</dd>
    <dd><note-alert>[NOTE]</note-alert> The LogFormatToken and LogFormat classes are not ready for use yet</dd>
    <!-- 3.3.0-alpha.2 (2025/02/08) -->
    <dt><version-data>3.3.0-alpha.2</version-data> | Release Date: 2025/02/08</dt>
    <dd>Modified the <code>LoggerException</code> to include custom error messages.</dd>
    <dd><note-alert>[NOTE]</note-alert> <code>LoggerException</code> is an experimental feature and it is not been used by the library yet.</dd>
    <dd><fix-alert>[FIX]</fix-alert> Added definition of inline methods <code>getLibVersion</code> and <code>getVersionStr</code> to resolve Visual Studio link fail.</dd>
    <!-- 3.3.0-alpha.1 (2025/01/27) -->
    <dt><version-data>3.3.0-alpha.1</version-data> | Release Date: 2025/01/27</dt>
    <dd><code>sortLogFileList2</code> marked as deprecated</dd>
    <dd><fix-alert>[FIX]</fix-alert> Added missing stream output for date and time information in <code>LogEntry</code> and <code>LogEntryW</code> classes</dd>
    <!-- 3.3.0-alpha (2025/01/15) -->
    <dt><version-data>3.3.0-alpha</version-data> | Release Date: 2025/01/15</dt>
    <dd>Cleaned unused code</dd>
    <dd>Added alternative algorithm for sorting, using the bubble sort instead of selection sort. <strong>The selection sort is disabled by a preprocessor directive and is marked as deprecated</strong></dd>
    <dd><fix-alert>[FIX]</fix-alert> string copy <code>LOGGER_LIB_BUILD_TYPE</code> to version build type</dd>
    <dd>Updated constructor parameters when receiving a <code>std::filesystem::path</code> to control if will use the file date time and will apply the timezone correction.</dd>
    <dd><fix-alert>[FIX]</fix-alert> sorting <code>LogFileDateTime</code> objects in descending and ascending order</dd>
    <dd><fix-alert>[FIX]</fix-alert> missing last date time character from string information in <code>LogFileDateTime</code> constructor.</dd>
    <dd><note-alert>[NOTE]</note-alert> This version of Logger Library appears to be very stable, but no tests with sorting log files was made on Windows systems. Considering the lack of tests to one important platform, the LoggerLib will be marked as <code>alpha</code></dd>
    <dd><i>(Added in 2025/01/20) </i>Add <code>LoggerLib.hpp</code>a main header to include all library components on build 64</dd>
    <!-- 3.2.0-alpha (2024/12/18) -->
    <dt><version-data>3.2.0-alpha</version-data> | Release Date: 2024/12/18</dt>
    <dd>Added <code>LogFileDateTime</code> class to focus on log file date time information report (not based on Last Time Write or Creation Time)</dd>
    <dd>Added <code>sortLogFileList</code> and <code>sortLogFileList2</code> to sort the log file list returned by <code>getLogFileList</code> method</dd>
    <dd><note-alert>[NOTE]</note-alert> The methods <code>sortLogFileList</code> and <code>sortLogFileList2</code> still in development and are not sorting correctly, missing some files from correct order. These functions may receive a new name or new version. Use with caution.</dd>
    <dd><fix-alert>[FIX]</fix-alert>Compiling the <code>LoggerLib</code> won't result in a ISO C++ forbidden warning when converting a <code>const char*</code> string to <code>char*</code></dd>
    <!-- 3.1.2-release (2024/10/08) -->
    <dt><version-data>3.1.2-release<version-data> | Release Date: 2024/10/08</dt>
    <dd>Changed the getVersionStr parameter to accept an copy and not the variable address any more.</dd>
    <dd>Added missing <code>PATCH number</code></dd>
    <dd>Added better <code>const char[]</code> conversion to <code>char*</code></dd>
    <dd><fix-alert>[FIX]</fix-alert> Version string conversion when <code>BUILD_TYPE</code> is marked as <code>release</code>.</dd>
    <dd><fix-alert>[FIX]</fix-alert> Revision number position when converting version to string.</dd>
    <dd>New tests with LoggerLib.</dd>
    <dd><i>(Added in 2024/12/06) </i><bug-alert>[BUG]</bug-alert> On Unix systems the log files entries are not added following the naming order as happens on Windows systems.</dd>
    <!-- 3.1.1-release (2024/10/07) -->
    <dt><version-data>3.1.1-release<version-data> | Release Date: 2024/10/07</dt>
    <dd>Added LoggerLib API in all header files, removing the necessity to use <code>LoggerLibDef.hpp</code></dd>
    <dd>Disabled the use of <code>pch.h</code> for non Windows builds</dd>
    <dd><fix-alert>[FIX]</fix-alert> the use of non C++ Standard from Microsoft for <code>std::fstream</code> and <code>std::wstream</code> constructors</dd>
    <dd>Added <code>LoggerLibVersion.hpp</code> and <code>LoggerLibVersionTools.hpp</code> to allow a compatible way to communicate with <code>VersionLib</code> from UtilityLibs with string version conversion or use the raw version values</dd>
    <!-- 3.1.0-beta (2024/09/23) -->
    <dt><version-data>3.1.0-beta</version-data> | Release Date: 2024/09/23</dt>
    <dd>Added <code>LoggerW</code> and <code>LogEntryW</code> classes</dd>
    <dd>Added <code>convertDateTime2LogStrEntryW</code></dd>
    <dd>Update CMakeLists.txt</dd>
    <dd>Added <code>LoggerException.cpp</code> and <code>LoggerException.hpp</code></dd>
    <!-- 3.0.0-alpha (2024/09/16) -->
    <dt><version-data>3.0.0-alpha</version-data> | Release Date: 2024/09/16</dt>
    <dd>Added <strong><i>LoggerLib V1</i></strong> migrated for CMake</dd>
    <dd>Added console for tests</dd>
    <dd>Added <strong>LoggerLib V1</strong></dd>
    <dd><note-alert>[NOTE]</note-alert> The LoggerLib contains the same C++ code from Visual Studio Solution (LoggerLibSolution)</dd>
    <dd><note-alert>[NOTE]</note-alert> This code was tested with <strong>C++20</strong> and <strong>C++17</strong></dd>
    <dd><note-alert>[NOTE]</note-alert> Some compiler parameters wasn't set on CMakeLists like Spectre Mitigation</dd>
</dl>

*Older versions was not tracked*