# Version Library: Version History:

This document contain the complete change history to Version Library

## Version Library History:

<!-- Version Library History Table: -->
<head>
    <link rel="stylesheet" href="Libraries/VersionLib/VersionLib/Docs/CSS/ReleaseNotes.css">
    <link rel="stylesheet" href="./CSS/ReleaseNotes.css">
</head>
<dl>
    <!-- 0.9.1-alpha.3 (2025/08/10) -->
    <dt><version-data>0.9.1-alpha.3</version-data> | Release Date: 2025/08/10</dt>
    <dd>Added <code>TokenClassifier</code> base class</dd>
    <dd>Added <code>SemVerDict</code> token classifiers for Semantic Versioning</dd>
    <dd>Added <strong>TokenDictionaries.hpp</strong> main header</dd>
    <dd><note-alert>[NOTE]</note-alert> The <code>SemVerDict</code> class contain the same algorithm from <code>toSemVerTokens</code> as part of the preparations to make the library fully compatible with token system</dd>
    <dd><strong>Moved <code>SemVer</code> and <code>VersionData</code> classes files to <i>Formats</i> subdirectory</strong></dd>
    <dd>Adapted the library files to new use <i>Formats</i> subdirectory location</dd>
    <!-- 0.9.1-alpha.2 (2025/08/07) -->
    <dt><version-data>0.9.1-alpha.2</version-data> | Release Date: 2025/08/07</dt>
    <dd>Added <code>FAIL_TO_IDENTIFY_TOKEN</code> in <strong>VersionTokenType</strong></dd>
    <dd><fix-alert>[FIX]</fix-alert> experimental algorithm <code>toSemVerTokens</code> does not identify the correct data type for build number</dd>
    <!-- 0.9.1-alpha.1 (2025/08/06) -->
    <dt><version-data>0.9.1-alpha.1</version-data> | Release Date: 2025/08/06</dt>
    <dd><fix-alert>[FIX]</fix-alert> identification of release types in <code>toSemVerTokens</code></dd>
    <dd><fix-alert>[FIX]</fix-alert> metadata with dashes and dots are not recognized correctly in <code>toSemVerTokens</code></dd>
    <dd><fix-alert>[FIX]</fix-alert> identification of build value in <code>toSemVerTokens</code></dd>
    <dd><bug-alert>[BUG]</bug-alert> build value is classified as short numerical value and not long type in <code>toSemVerTokens</code></dd>
    <dd>Removed unused variables in <code>toSemVerTokens</code></dd>
    <!-- 0.9.1-alpha (2025/08/06) -->
    <dt><version-data>0.9.1-alpha</version-data> | Release Date: 2025/08/06</dt>
    <dd>Added support to <code>unsigned short</code></dd>
    <dd>Added <code>VersionTokenType</code> enum</dd>
    <dd>Added <code>VersionTokenDataType</code> enum</dd>
    <dd>Added <code>VersionTokenData</code> class</dd>
    <dd>Added <code>VersionToken</code> class</dd>
    <dd>Added <code>toSemVerTokens</code> method</dd>
    <dd>Added auxiliary method <code>getTokenTypeStr</code></dd>
    <dd>Added new experimental feature <strong>VERSION_LIB_ENABLE_EXPERIMENTAL_TOSEMVERTOKENS_METHOD2</strong> for alternative algorithm in <i>toSemVerTokens</i></dd>
    <dd>Added <code>isRelease</code> method</dd>
    <dd>Changed <code>unsigned long long</code> to <code>unsigned long</code></dd>
    <dd>Changed <code>VersionClass</code> to <code>VersionData</code></dd>
    <dd>Removed <code>toVersionStruct3</code></dd>
    <dd><fix-alert>[FIX]</fix-alert> metadata treatment in <code>toSemVerTokens</code></dd>
    <dd><strong>Deprecated <code>VersionStruct</code></strong></dd>
    <dd><strong>NOTE:</strong> <code>VersionData</code> use temporary <code>toVersionStruct2</code></dd>
    <!-- 0.9.0-alpha.3 (2025/06/12) -->
    <dt><version-data>0.9.0-alpha.3</version-data> | Release Date: 2025/06/12</dt>
    <dd>Internal changes to prepare the Version Library to support correctly the components for C linkage.</dd>
    <dd><fix-alert>[FIX]</fix-alert> revision number of the previous release (0.9.0-alpha.2) was not updated. This release has the correct value.</dd>
    <!-- 0.9.0-alpha.2 (2025/06/06) -->
    <dt><version-data>0.9.0-alpha.2</version-data> | Release Date: 2025/06/06</dt>
    <dd>Separated methods from files <code>Tools.hpp</code> <code>Tools.cpp</code> into <code>CommonTools.hpp</code> <code>CommonTools.cpp</code>, <code>ReleaseTools.hpp</code> <code>ReleaseTools.cpp</code> and <code>VersionTools.hpp</code> <code>VersionTools.cpp</code> to reduce possible future compilation cyclic dependencies</dd>
    <!-- 0.9.0-alpha.1 (2025/04/18) -->
    <dt><version-data>0.9.0-alpha.1</version-data> | Release Date: 2025/04/18</dt>
    <dd><fix-alert>[FIX]</fix-alert> toVersionStruct2 missing revision</dd>
    <dd><fix-alert>[FIX]</fix-alert> toVersionStruct2 missing build release when no revision is available</dd>
    <dd><fix-alert>[FIX]</fix-alert> toVersionStruct2 does not store revision</dd>
    <!-- 0.9.0-alpha (2025/04/17) -->
    <dt><version-data>0.9.0-alpha</version-data> | Release Date: 2025/04/17</dt>
    <dd><strong>Redesign the internal components to bring support to new data types, support to combined release data and to provide a better support to other formats in the future</strong></dd>
    <dd>Added <code>BuildRelease</code> class to store the <code>BuildType</code> data and the revision values. It also has a flag to hold the conversion data status</dd>
    <dd>Added support to hold multiple releases in <code>VersionBuildType</code> class</dd>
    <dd>Added initial support to build metadata</dd>
    <dd>Added initial support to detect Semantic Versioning format</dd>
    <dd>Added proper Semantic Versioning class: <code>SemVer</code> using modified <code>VersionData</code> class code to work with additional flags and method checks to see if is a correct Semantic Versioning data <strong>NOTE: This class is not ready to work as expected yet</strong></dd>
    <dd>Added new struct types to make data transaction and use them to C linkage: <code>VersionBuildTypeC</code> and <code>VersionReleaseDataC</code></dd>
    <dd>Changed the <code>VersionData</code> to be a generic version data approach to all other future version formats</dd>
    <dd><strong>NOTE: THE MODIFICATIONS MADE IN THIS VERSION BREAK THE BETA CODE VERSION</strong></dd>
    <dd>Removed deprecated <code>toVersionStruct</code> function</dd>
    <dd>Added <code>VersionType</code> to determinate the versioning type used in <code>VersionStruct</code> and <code>VersionData</code></dd>
    <dd>Added <code>idVersionType</code> method to identify the supported versioning formats or custom formats and return a <code>VersionType</code> <strong>NOTE: This method is not ready to be used</strong></dd>
    <dd>Modified <code>VersionStruct</code> to support generic version formats as experimental feature</dd>
    <dd>Previous memory optimizations was removed after all redesign work. New memory optimizations will be made it in a future release</dd>
    <dd>Removed deprecated constructors in <code>VersionData</code></dd>
    <dd>Removed unnecessary or unused experimental definition guards</dd>
    <dd>Experimental constructors in <code>VersionData</code> are not marked as experimental feature</dd>
    <dd><strong>IMPORTANT: THIS NEW VERSION CONTAINS SEVERAL MODIFICATIONS THAT MAY CONTAIN NEW BUGS THAT WAS NOT TRACKED YET</strong></dd>
    <dd><strong>THE EXPERIMENTAL MODIFICATIONS MAY BREAK THE SUPPORT TO LAST BETA VERSION (0.8.7-beta).</strong> If you need to use the last beta, use the <strong>git tag - <i>VersionLib_0.8.7-beta</i></strong> to compile the library</dd>
    <!-- 0.8.7-beta (2025/03/10) -->
    <dt><version-data>0.8.7-beta</version-data> | Release Date: 2025/03/10</dt>
    <dd><strong>Changed variable <code>build_type_number</code> to <code>build_revision</code> in <code>VersionStruct</code> and <code>VersionData</code></strong></dd>
    <dd>Changed the <code>build_type_number</code> references to <code>build_revision</code></dd>
    <dd><fix-alert>[FIX]</fix-alert> <code>VersionData</code> experimental comparison operators.</dd>
    <dd><fix-alert>[FIX]</fix-alert> <code>build</code> was not set properly in <code>VersionData</code> with <i><strong>Experimental Constructors</i></strong> when build number does not appear on constructor parameters.</dd>
    <dd><strong>Added original</strong> <code>VersionData</code> <strong>constructors to deprecated features</strong></dd>
    <dd><strong>Added original</strong> <code>VersionData</code> <strong>comparison operators to deprecated features</strong></dd>
    <dd><i>Added in 2025/04/09:</i> Updated the build number after few tests.</dd>
    <dd><i>Added in 2025/04/09:</i> Removed unnecessary controls to experimental features</dd>
    <!-- 0.8.6-beta (2025/02/26) -->
    <dt><version-data>0.8.6-beta</version-data> | Release Date: 2025/02/26</dt>
    <dd>Added new experimental algorithm to fix <code>toVersionStruct2</code> function string version detection</dd>
    <dd>Added experimental memory layout to reduce memory waste in <code>VersionStruct</code> and <code>VersionData</code></dd>
    <dd>Updated VersionLib documentation</dd>
    <dd><fix-alert>[FIX]</fix-alert> some permissive formats were not being detected or partially detected by <code>toVersionStruct2</code></dd>
    <dd><fix-alert>[FIX]</fix-alert> some Semantic Versioning formats were not being fully detected or some version components were confused with others.</dd>
    <dd><i>Added in 2025/03/05:</i> <bug-alert>[BUG]</bug-alert> [Experimental Operators] Comparing with a version that has <code>major</code> as zero and another version with <code>major</code> greater than zero will always fail in comparison with the other version, when using the operators: > >= < <=</dd>
    <!-- 0.8.5-beta (2025/02/18) -->
    <dt><version-data>0.8.5-beta</version-data> | Release Date: 2025/02/18</dt>
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
    <dt><version-data>0.8.4-beta</version-data> | Release Date: 2025/02/04</dt>
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
    <dt><version-data>0.8.3-beta.2</version-data> | Release Date: 2025/01/14</dt>
    <dd>Updated <strong>Project Info.md</strong></dd>
    <dd>Marked missing attribute <i>deprecated</i> on <code>toVersionStruct</code> declaration.</dd>
    <dd><fix-alert>[FIX]</fix-alert> <code>tolower_Cstr</code> now converts the strings to C string style correctly</dd>
    <dd><fix-alert>[FIX]</fix-alert> missing instructions in <code>getBuildTypeCompleteCstr</code> method in <code>VersionData</code> class. </dd>
    <dd><fix-alert>[FIX]</fix-alert> missing instructions in <code>getBuildTypeCstr</code> method in <code>VersionData</code> class</dd>
    <!-- 0.8.3-beta (2025/01/10) -->
    <dt><version-data>0.8.3-beta</version-data> | Release Date: 2025/01/10</dt>
    <dd>Added new parameter <code>showReleaseType</code> in <code>getBuildTypeComplete</code> and <code>getVersionStr</code> methods.</dd>
    <dd><fix-alert>[FIX]</fix-alert> missing parameters for <code>getBuildTypeCompleteCstr</code> method.</dd>
    <dd><fix-alert>[FIX]</fix-alert> version string format when was marked as <strong>RELEASE</strong>.</dd>
    <dd><fix-alert>[FIX]</fix-alert> operators <strong>less</strong> than and <strong>greater</strong> than.</dd>
    <dd><fix-alert>[FIX]</fix-alert> Fixed missing "release" build type string return on <code>buildType2Str</code>.</dd>
    <!-- 0.8.2-beta (2024/10/09) -->
    <dt><version-data>0.8.2-beta</version-data> | Release Date: 2024/10/09</dt>
    <dd>Added copy and move constructors.</dd>
    <dd>Added copy and move operators.</dd>
    <dd><i>On 0.8.2-beta.2: </i>Added <code>VersionLibVersionInfo.hpp</code> file to hold the preprocessor information about the Version Library version information.</dd>
    <dd><i>On 0.8.2-beta.2: </i>Changed the name <code>internalVersionData</code> to a internal method to return the Version Library version information.</dd>
    <dd><bug-alert>[BUG]</bug-alert> <code>VersionData</code> operators <i><strong>less</strong></i>, <i><strong>less than</strong></i>, <i><strong>greater</strong></i> and <i><strong>greater than</strong></i> are not working as expected.</dd>
    <!-- 0.8.1-beta (2024/10/08) -->
    <dt><version-data>0.8.1-beta</version-data> | Release Date: 2024/10/08</dt>
    <dd><fix-alert>[FIX]</fix-alert> <code>tolower_str</code> method, using a traditional algorithm to convert the string to lowercase.</dd>
    <dd><warning-alert>[WARNING]</warning-alert> The method <code>tolower_Cstr</code> was not fixed.</dd>
    <dd>Added checking for possible quotes and double quotes use in string BUILD_TYPE.</dd>
    <dd>Added a check for situation when MAJOR.MINOR.PATCH.REVISION is available.</dd>
    <dd><bug-alert>[BUG]</bug-alert> When sending a version string on format <i>MAJOR.MINOR.PATCH.REVISION</i> to <code>VersionData</code>, the <code>build_type_number</code> or <i>revision</i> <strong>can not be detected</strong></dd>
    <!-- 0.8.0-alpha (2024/10/01) -->
    <dt><version-data>0.8.0-alpha</version-data> | Release Date: 2024/10/01</dt>
    <dd>Added <code>toVersionStruct2</code> with full Semantic Versioning support and a permissive conversion.</dd>
    <dd><bug-alert>[BUG]</bug-alert> <code>tolower_str</code> and <code>tolower_Cstr</code> contains a bug that make miss the characters that already in lowercase.</dd>
    <dd><fix-alert>[FIX]</fix-alert> <code>VersionData</code> operators for greater, greater than, less and less than fail to check correctly the complete version number.<dd>
</dl>

*Older versions was not tracked*