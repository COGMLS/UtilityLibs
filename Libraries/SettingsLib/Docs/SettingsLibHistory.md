# Settings Library History:

## About this file:

This file contain the tracked version and modifications of the Settings Library project since was included in the **UtilityLibs**. Older library versions was not tracked and will not be included in this file.

An copy or partial copy of this history table is available in the `README.md` file in the root of the project.

## Settings Library History:

<!-- Settings Library History Table: -->
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
    <!-- 3.0.0-alpha.25 (2024/11/09) -->
    <dt><version-data>3.0.0-alpha.25</version-data> | Release Date: 2024/11/09</dt>
    <dd>Added method <code>getKeys</code> to <code>ConfigIniSectionData</code></dd>
    <dd>Added auxiliary method to convert the data to string.</dd>
    <dd>Added method <code>getConfigMapStr</code>.</dd>
    <dd>Added method <code>getConfigMapWstr</code>.</dd>
    <dd>Implemented method <code>getSectionList</code>.</dd>
    <dd>Updated the <code>ConfigIni</code> class documentation.</dd>
    <dd>Added <code>isWideFileStream</code> method.</dd>
    <dd>Replaced use of <code>isWideData</code> variable to <code>isWideFileStream</code> method.</dd>
    <dd>Marked the method <code>setConfigLine</code> as <b>NOT READY</b>.</dd>
    <dd><warning-alert>[WARNING]</warning-alert> The regression detected on version <b><code>3.0.0-alpha.24</code></b> on Unix systems occur because not all methods was defined and the methods implemented was mainly with <code>std::string</code> and the compiler may get confused with the function overloading.</dd>
    <dd><bug-alert>[CAUTION]</bug-alert> <b>This version was not compiled in Unix systems. Because not all methods was implemented and the link with other applications may fail as happened with previous version.</b></dd>
    <!-- 3.0.0-alpha.24 (2024/11/07) -->
    <dt><version-data>3.0.0-alpha.24</version-data> | Release Date: 2024/11/07</dt>
    <dd><u>Added first cross-platform support</u></dd>
    <dd>Added <code>GeneralException</code> to replace Microsoft's non standard C++ <code>std::exception</code> located in <b><i>Components/Exceptions</i></b></dd>
    <dd>Reorganized <code>SettingsIni</code> components to <b><i>Components/Configs/Ini</i></b></dd>
    <dd>Revised <code>SettingsLibVersion</code></dd>
    <dd>Updated <code>SettingsLib</code> version</dd>
    <dd>Updated version methods</dd>
    <dd><bug-alert>[CAUTION]</bug-alert> This version may contain a possible regression: The <code>SettingsLib</code> compile on Unix systems but fail to link and consume it on other applications</dd>
    <!-- 3.0.0-alpha.23 (2024/09/23) -->
    <dt><version-data>3.0.0-alpha.23</version-data> | Release Date: 2024/09/23</dt>
    <dd>Added new constructor.</dd>
    <dd>Updated the documentation.</dd>
    <dd>Added <code>readLine</code>, <code>setConfigName</code> and <code>getConfigName</code>, <code>isWideData</code>, <code>isConfigFileOk</code>, <code>isUsingConfigFileStream</code> methods.</dd>
    <dd>Added <code>isConfigStreamOk</code> method.</dd>
    <!-- 3.0.0-alpha.22 (2024/09/23) -->
    <dt><version-data>3.0.0-alpha.22</version-data> | Release Date: 2024/09/23</dt>
    <dd>Added new methods into <code>ConfigIni</code> class.</dd>
    <dd>Updated the class documentation.</dd>
    <dd><note-alert>NOTE:</note-alert> only few methods are ready to be used at this moment.</dd>
    <!-- 3.0.0-alpha.21 (2024/06/31) -->
    <dt><version-data>3.0.0-alpha.21</version-data> | Release Date: 2024/06/31</dt>
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

**NOTE:** Previous versions history was not tracked