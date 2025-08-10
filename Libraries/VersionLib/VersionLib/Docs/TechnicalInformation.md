# Technical Information

The Version Library is composed by internal components that allow create version object that can allow test then between others and check if a version satisfy a specifics conditions to make a program run or execute a code depending the version. The library offer basic two ways to create version objects, applying numerical values to constructors parameters or using a string version value. This last one can use values that came from outside the application, like a server or a informational file, offering a the possibility to convert it's value into known versions with a dictionary versioning list or using a custom one. By default, the Version Library **always** use Semantic Versioning, including internal library version is reported in same format.

The version objects are separated by *Version Core*, *Version Release*, *Version Revision*, *Build Metadata*, *Build number*. These components are very common in various versioning formats and can be easily reused with a dictionary system and a tokenization system. Those systems allow the Version Library use complex formats and also help to keep a high flexibility to test multiple formats. **It is important to known that different formats can not be tested between then!**

Version Library offers predefined formats with custom and specialized classes that make the implementation easier for well known formats like: `SemVer` (Semantic Versioning), `CalVer` (Calendar Versioning), `SemCalVer` (Hybrid Semantic and Calendar Versioning), `WinVer` (Windows Versioning). All those classes are specializations to make the implementation easier of the version objects.

## About Diagrams:

Part of the documentation of the Version Library is done with diagram pages that helps to understand the process behind and known how to create custom formats.

### Diagrams

#### Version Library C++ and C Linkage Components
![Version Library C++ and C Linkage Components](/Libraries/VersionLib/VersionLib/Docs/Images/Diagram_Cpp_and_C_Linkage.png)

#### Version Library VersionData diagram
![Version Library VersionData diagram](/Libraries/VersionLib/VersionLib/Docs/Images/Diagram_VersionDataClass.png)

***IMPORTANT: THE TechnicalInformation FILE IS BEEN UPDATED***

## About BuildType:

In Semantic Versioning is allowed the use of combined pre-release components like `1.0.0-alpha.beta`. In actual moment, the library does not support this format. It's expected to add the support for combined release components in **version 0.9.0-alpha** after the implementation of `VersionBuildType` class.

### `VersionBuildType` class:

The `VersionBuildType` class is a new way to store and allow tests with build type available. Using an exclusive class also allows us to make more secure modifications with less code changes in the rest of the library's components. The class is designed to use comparison operators to test between the different build types and in future implementation, with combined build types, will make the tests internally, without necessity to change the other components.

The class also allows the use *canary*, *development* and *pre release* build type words to determinate the release type. Those new terminologies have similar numeric values to *alpha*, *beta* and *release candidate* respectively. *It's important to beware the new build types words are a permissive way to declare the component, but those words are not used in Semantic Versioning and there are many different way to declare the releases.*

The implementation of this experimental feature is defined by `VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT` and combined support to `VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE`. This last one only has effect if `VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT` is enabled.

> **NOTE:** THE IMPLEMENTATION OF `VersionBuildType` IS UNDER PROGRESS AND WILL NOT WORK OR COMPILE YET.

## `VersionStruct` and `VersionData` memory layout:

> **ALL EXPERIMENTAL NEW MEMORY LAYOUT WAS REMOVED IN DETRIMENT OF 0.9.0-alpha VERSION FEATURE DEVELOPMENT**
>
> A new optimized memory layout will be developed when the features become stable.

> **NOTE:** The new memory layout is available as experimental feature. To enable, set `VERSION_LIB_ENABLE_EXPERIMENTAL_MEM_LAYOUT`.
>
> **NOTE:** Experimental memory layout will not be part of the main experimental features development.

Before version **0.8.6**, the original construction of the `VersionStruct` was:

```C
struct VersionStruct
{
    unsigned int major;                     // Major version number
    unsigned int minor;                     // Minor version number
    unsigned int patch;                     // Patch version number
    unsigned long long build;               // Build number
    VersionLib::BuildType build_type;       // Build type (alpha, a, beta, etc)
    unsigned int build_revision;            // Build revision (alpha.1, rc.3)
    bool compare_build;	                    // Build comparison control
};
```

The original declarations make the struct use 40 bytes in memory allocation, following the layout:

```
------------------------------------------------------------------------------------
   | 0 bytes |         |         |         | 4 bytes |         |         |         |
 0 | ############## Major ################ | ################ Minor ############## |
 8 | ############## Patch ################ |                                       |
24 | ################################## Build #################################### |
16 | ## Build Type ##  |                   | ########### build_revision ########## |
32 | Compare |                             |                                       |
------------------------------------------------------------------------------------
```

On version **0.8.6** the `VersionStruct` will be declared differently when `VERSION_LIB_ENABLE_EXPERIMENTAL_MEM_LAYOUT` is enabled:

```C
struct VersionStruct
{
    unsigned int major;                     // Major version number
    unsigned int minor;                     // Minor version number
    unsigned int patch;                     // Patch version number
    unsigned int build_revision;            // Build revision (alpha.1, rc.3)
    unsigned long long build;               // Build number
    VersionLib::BuildType build_type;       // Build type (alpha, a, beta, etc)
    bool compare_build;                     // Build comparison control
};
```

The memory layout will be different, using the 4 bytes that was being wasted, to allocate revision data. Making the revised struct to use only 32 bytes.

```
------------------------------------------------------------------------------------
   | 0 bytes |         |         |         | 4 bytes |         |         |         |
 0 | ############## Major ################ | ################ Minor ############## |
 8 | ############## Patch ################ | ########### build_revision ########## |
24 | ################################## Build #################################### |
16 | ## Build Type ##  | Compare |         |                                       |
------------------------------------------------------------------------------------
```

> `VersionData` it's also affected to the same memory waste scenario, because uses the same declarations found in `VersionStruct`.

### First tests with new memory layout:

| Test | Total program memory use | Snapshot at the final of program |
| ---- | ------------------------ | -------------------------------- |
| Original memory layout | 420 KB | 9,63 KB |
| Optimized memory layout | 461 KB | 9,42 KB |