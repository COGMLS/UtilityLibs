# Version Library: Version History:

## Version Library History:

<!-- Version Library History Table: -->
<dl>
    <!-- 0.8.2-beta (2024/10/09) -->
    <dt><strong>0.8.2-beta</strong></dt>
    <dd>Added copy and move constructors.</dd>
    <dd>Added copy and move operators.</dd>
    <dd><i>On 0.8.2-beta.2: </i>Added <code>VersionLibVersionInfo.hpp</code> file to hold the preprocessor information about the Version Library version information.</dd>
    <dd><i>On 0.8.2-beta.2: </i>Changed the name <code>internalVersionData</code> to a internal method to return the Version Library version information.</dd>
    <!-- 0.8.1-beta (2024/10/08) -->
    <dt><strong>0.8.1-beta</strong></dt>
    <dd><strong>[FIX]</strong> <code>tolower_str</code> method, using a traditional algorithm to convert the string to lowercase.</dd>
    <dd><strong><font color="orange">[WARNING]</font></strong> The method <code>tolower_Cstr</code> was not fixed.</dd>
    <dd>Added checking for possible quotes and double quotes use in string BUILD_TYPE.</dd>
    <dd>Added a check for situation when MAJOR.MINOR.PATCH.REVISION is available.</dd>
    <dd><strong><font color="red">[BUG]</font></strong> When sending a version string on format <i>MAJOR.MINOR.PATCH.REVISION</i> to <code>VersionData</code>, the <code>build_type_number</code> or <i>revision</i> <strong>can not be detected</strong></dd>
    <!-- 0.8.0-alpha (2024/10/01) -->
    <dt><strong>0.8.0-alpha</strong></dt>
    <dd>Added <code>toVersionStruct2</code> with full Semantic Versioning support and a permissive conversion.</dd>
    <dd><strong><font color="red">[BUG]</font></strong> <code>tolower_str</code> and <code>tolower_Cstr</code> contains a bug that make miss the characters that already in lowercase.</dd>
    <dd><strong>[FIX]</strong> <code>VersionData</code> operators for greater, greater than, less and less than fail to check correctly the complete version number.<dd>
</dl>