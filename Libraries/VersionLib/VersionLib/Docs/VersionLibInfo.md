# Version Library: Project Information

This document contains the information about the future plans, known bugs, deprecated features.

## Recent Implementations:

- Support for convert `VersionStruct` to `VersionData` and vice-versa.
- New experimental version string detection in `toVersionStrut2` method.
- New experimental memory layout of `VersionStruct` to reduce the memory size allocation. (See the details in [here](#versionstruct-and-versiondata-memory-layout))
- Support to create objects versions without warning messages with wrapper constructors.
- **CHANGED `build_type_number` VARIABLE TO `build_revision` TO A BETTER COMPREHENSION.**

## Implementations under development:

- Add support to compare versions with build information.
- Add Version Lib errors and exceptions components
- Add and update all documentation for the Version Library
- Replace `BuildType` enum to `VersionBuildType` class as main storage of version release type

## Future Implementations:

- Full support for C-Style functions to better support for extern C linkage
- Full support for extern C linkage
- Support to identify version files by it's name
- Support to detect Windows Metadata version information
- Support to combined build type information. I.e. `1.0.0-alpha.beta`
- Support to build metadata in version string

## Known Bugs:

| Bug ID | Details | Notes/Workaround | Status |
| :----- | :-----: | :--------------: | -----: |
| 1 | ~~`tolower_str` contains a bug that make miss the characters that already in lowercase.~~ |  | Fixed |
| 2 | ~~`tolower_Cstr` contains a bug that make miss the characters that already in lowercase.~~ |  | Fixed |
| 3 | ~~When sending a version string on format *MAJOR.MINOR.PATCH.REVISION* to `VersionData`, the `build_type_number` or *revision* **can not be detected**~~ | The algorithm received a new version on **version 0.8.6** to eliminate the defections in detect string versions and add more permissive formats. To enable the experimental algorithm it's necessary enable `VERSION_LIB_ENABLE_EXPERIMENTAL_FIX_VERSIONSTR_2_VERSIONSTRUCT`. **NOTE: Originally the fix was coming to version 0.8.7. In 0.8.7 the experimental algorithm will be enable by default** | **Fix in tests** |
| 4 | ~~Using `VersionData` operators *less*, *less than*, *greater* and *greater than* does not work as expected~~ |  | Fixed |
| 5 | ~~VersionData method,`getBuildTypeCstr`, does not convert the C++ string data into C-style string~~ |  | Fixed |
| 6 | ~~VersionData method, `getBuildTypeCompleteCstr`, does not convert C++ string data into C-style string~~ |  | Fixed |
| 7 | ~~`VersionData` constructors not working after implementation of `cmpBuild` parameter, resulting in ambiguous reference~~ | If `VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_CONSTRUCTORS` is not defined, the modified constructors are disabled to avoid the ambiguous reference. **NOTE:** Using `VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_CONSTRUCTORS`, will **break** any code that uses original constructor parameter list. **NOTE: On version 0.9.0-alpha, the experimental constructors will be the focus during the development** | Fixed |
| 8 | `VersionException` fails when throw the object | Using *`catch (VersionLib::VersionException& e)`* does not fail. The workaround is not definitive. New tests and modification may happen to make sure it's working properly | **Fix in development** |
| 9 | Enabling experimental optimized memory layout result in missing correct data to `build_type_number`. **NOTE: The experimental feature was only tested on Windows platforms with MSVC** | To avoid missing any data, keep `VERSION_LIB_ENABLE_EXPERIMENTAL_MEM_LAYOUT` disabled | Not fixed |
| 10 | ~~Comparing with a version that has `major` as zero and another version with `major` greater than zero will always fail in comparison with the other version, when using the operators: `> >= < <=`~~ |  | Fixed |

## Deprecated Features:

| Feature | Details | Workaround | Notes |
| :------ | :-----: | :--------: | ----: |
| `toVersionStruct` | Deprecated method because is not reliable to convert the version information to `VersionStruct` | Use `toVersionStrut2` with more reliable semantic versioning conversion. | On version **0.9.0-alpha** this method will be removed |
| Original `VersionData` comparison operators are deprecated. | The original implementation of comparison operators `> >= < <=` are deprecated because are defective | No workaround is necessary | On version **0.8.8-alpha** the original comparison operators will be removed. |
| Original `VersionData` constructors are deprecated and the *experimental constructors* are the default development. | The *experimental constructors* are enabled by default with `VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_CONSTRUCTORS`. *The constructor with string version parameter still working.* | To disable the experimental constructors, disable the `VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_CONSTRUCTORS` on `ExperimentalFeatures.hpp` | On version **1.0.0-alpha** the original constructors will be removed |

## Removed Features:

| Feature | Details | Workaround | Notes |
| :------ | :-----: | :--------: | ----: |

# Technical Information

> This section was added to provide more technical information.
>
> This section may be moved in the future to a dedicated file.

## About BuildType:

In Semantic Versioning is allowed the use of combined pre-release components like `1.0.0-alpha.beta`. In actual moment, the library does not support this format. It's expected to add the support for combined release components in **version 0.9.0-alpha** after the implementation of `VersionBuildType` class.

### `VersionBuildType` class:

The `VersionBuildType` class is a new way to store and allow tests with build type available. Using an exclusive class also allows us to make more secure modifications with less code changes in the rest of the library's components. The class is designed to use comparison operators to test between the different build types and in future implementation, with combined build types, will make the tests internally, without necessity to change the other components.

The class also allows the use *canary*, *development* and *pre release* build type words to determinate the release type. Those new terminologies have similar numeric values to *alpha*, *beta* and *release candidate* respectively. *It's important to beware the new build types words are a permissive way to declare the component, but those words are not used in Semantic Versioning and there are many different way to declare the releases.*

The implementation of this experimental feature is defined by `VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT` and combined support to `VERSION_LIB_ENABLE_EXPERIMENTAL_SUPPORT_2_COMBINED_BUILD_TYPE`. This last one only has effect if `VERSION_LIB_ENABLE_EXPERIMENTAL_CLASS_BUILD_TYPE_COMPONENT` is enabled.

> **NOTE:** THE IMPLEMENTATION OF `VersionBuildType` IS UNDER PROGRESS AND WILL NOT WORK OR COMPILE YET.

## `VersionStruct` and `VersionData` memory layout:

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