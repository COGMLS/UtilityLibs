# Version Library: Version History:

This document contain the complete change history to Version Library

## Version Library History:

<!-- Version Library History Table: -->
<style>
    version-data
    {
        font-weight: bold;
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
    <!-- 0.8.6-beta (2025/02/26) -->
    <dt><version-data>0.8.6-beta</version-data></dt>
    <dd>Added new experimental algorithm to fix <code>toVersionStruct2</code> function string version detection</dd>
    <dd>Added experimental memory layout to reduce memory waste in <code>VersionStruct</code> and <code>VersionData</code></dd>
    <dd>Updated VersionLib documentation</dd>
    <dd><fix-alert>[FIX]</fix-alert> some permissive formats were not being detected or partially detected by <code>toVersionStruct2</code></dd>
    <dd><fix-alert>[FIX]</fix-alert> some Semantic Versioning formats were not being fully detected or some version components were confused with others.</dd>
    <!-- 0.8.5-beta (2025/02/18) -->
    <dt><version-data>0.8.5-beta</version-data></dt>
    <dd>Added <code>getErrorMessage</code> function to translate the <code>VersionExceptionCode</code> into error messages</dd>
    <dd>Added support to <code>internalVersionData</code> to use experimental constructors when enabled</dd>
    <dd>Added wrapper constructors to avoid compilation warnings when using integers in <code>VersionData</code></dd>
    <dd>Added new <code>VersionException</code> throws in few unaccepted conditions</dd>
    <dd>Renamed to <code>VersionExceptionCode</code></dd>
    <dd>Renamed <code>VersionExceptionCode</code> values</dd>
    <dd>Renamed experimental guards</dd>
    <dd>Renamed definitions for experimental features</dd>
    <dd>Changed experimental constructors parameters</dd>
    <dd>Changed <code>msg_val</code> to std::string to avoid missing control on memory block</dd>
    <dd><fix-alert>[FIX]</fix-alert> <code>VersionException</code> class</dd>
    <dd><fix-alert>[FIX]</fix-alert> <code>what</code> method in VersionException</dd>
    <dd><warning-alert>[WARNING]</warning-alert> These modifications may break any code that uses experimental constructors</dd>
    <!-- 0.8.4-beta (2025/02/04) -->
    <dt><version-data>0.8.4-beta</version-data></dt>
    <dd></dd>
    <dd>Added preprocessor to disable the original comparison operators</dd>
    <dd><fix-alert>[FIX]</fix-alert> <code>VersionData</code> comparison operators</dd>
    <dd>Added <code>compare_build</code> to control the build comparison in <code>VersionData</code></dd>
    <dd>Added experimental features compilation control</dd>
    <dd>Moved preprocessor definitions to <code>ExperimentalFeatures.hpp</code></dd>
    <dd>Added experimental features compilation control</dd>
    <dd>Added <code>compare_build</code> control variable into <code>VersionStruct</code></dd>
    <dd>Added <code>cmpBuild</code> parameter into constructors to enable/disable build comparison</dd>
    <dd>Added wrapper constructors to avoid constructor ambiguous failure</dd>
    <dd>Declared <code>VersionStruct</code> comparison operators in <code>VersionData</code></dd>
    <dd>Small code writing changes</dd>
    <dd>Small changes on documentation</dd>
    <!-- 0.8.3-beta.2 (2025/01/14) -->
    <dt><version-data>0.8.3-beta.2</version-data></dt>
    <dd>Updated <strong>Project Info.md</strong></dd>
    <dd>Marked missing attribute <i>deprecated</i> on <code>toVersionStruct</code> declaration.</dd>
    <dd><fix-alert>[FIX]</fix-alert> <code>tolower_Cstr</code> now converts the strings to C string style correctly</dd>
    <dd><fix-alert>[FIX]</fix-alert> missing instructions in <code>getBuildTypeCompleteCstr</code> method in <code>VersionData</code> class. </dd>
    <dd><fix-alert>[FIX]</fix-alert> missing instructions in <code>getBuildTypeCstr</code> method in <code>VersionData</code> class</dd>
    <!-- 0.8.3-beta (2025/01/10) -->
    <dt><version-data>0.8.3-beta</version-data></dt>
    <dd>Added new parameter <code>showReleaseType</code> in <code>getBuildTypeComplete</code> and <code>getVersionStr</code> methods.</dd>
    <dd><fix-alert>[FIX]</fix-alert> missing parameters for <code>getBuildTypeCompleteCstr</code> method.</dd>
    <dd><fix-alert>[FIX]</fix-alert> version string format when was marked as <strong>RELEASE</strong>.</dd>
    <dd><fix-alert>[FIX]</fix-alert> operators <strong>less</strong> than and <strong>greater</strong> than.</dd>
    <dd><fix-alert>[FIX]</fix-alert> Fixed missing "release" build type string return on <code>buildType2Str</code>.</dd>
    <!-- 0.8.2-beta (2024/10/09) -->
    <dt><version-data>0.8.2-beta</version-data></dt>
    <dd>Added copy and move constructors.</dd>
    <dd>Added copy and move operators.</dd>
    <dd><i>On 0.8.2-beta.2: </i>Added <code>VersionLibVersionInfo.hpp</code> file to hold the preprocessor information about the Version Library version information.</dd>
    <dd><i>On 0.8.2-beta.2: </i>Changed the name <code>internalVersionData</code> to a internal method to return the Version Library version information.</dd>
    <dd><bug-alert>[BUG]</bug-alert> <code>VersionData</code> operators <i><strong>less</strong></i>, <i><strong>less than</strong></i>, <i><strong>greater</strong></i> and <i><strong>greater than</strong></i> are not working as expected.</dd>
    <!-- 0.8.1-beta (2024/10/08) -->
    <dt><version-data>0.8.1-beta</version-data></dt>
    <dd><fix-alert>[FIX]</fix-alert> <code>tolower_str</code> method, using a traditional algorithm to convert the string to lowercase.</dd>
    <dd><strong><font color="orange">[WARNING]</font></strong> The method <code>tolower_Cstr</code> was not fixed.</dd>
    <dd>Added checking for possible quotes and double quotes use in string BUILD_TYPE.</dd>
    <dd>Added a check for situation when MAJOR.MINOR.PATCH.REVISION is available.</dd>
    <dd><bug-alert>[BUG]</bug-alert> When sending a version string on format <i>MAJOR.MINOR.PATCH.REVISION</i> to <code>VersionData</code>, the <code>build_type_number</code> or <i>revision</i> <strong>can not be detected</strong></dd>
    <!-- 0.8.0-alpha (2024/10/01) -->
    <dt><version-data>0.8.0-alpha</version-data></dt>
    <dd>Added <code>toVersionStruct2</code> with full Semantic Versioning support and a permissive conversion.</dd>
    <dd><bug-alert>[BUG]</bug-alert> <code>tolower_str</code> and <code>tolower_Cstr</code> contains a bug that make miss the characters that already in lowercase.</dd>
    <dd><fix-alert>[FIX]</fix-alert> <code>VersionData</code> operators for greater, greater than, less and less than fail to check correctly the complete version number.<dd>
</dl>

*Older versions was not tracked*