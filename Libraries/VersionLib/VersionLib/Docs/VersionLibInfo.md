# Version Library: Project Information

This document contains the information about the future plans, known bugs, deprecated features.

## Recent Implementations:

- Support for convert `VersionStruct` to `VersionData` and vice-versa.
- New experimental version string detection in ``toVersionStrut2` method.
- New experimental memory layout of `VersionStruct` to reduce the memory size allocation. (See the details in [here](#versionstruct-and-versiondata-memory-layout))
- Support to create objects versions without warning messages with wrapper constructors.

## Implementations under development:

- Add support to compare versions with build information.
- Include the global internal Version Library data.
- Full support for C-Style functions to better support for extern C linkage
- Add Version Lib errors and exceptions components
- Add and update all documentation for the Version Library

## Future Implementations:

- Full support for extern C linkage
- Support to identify version files by it's name
- Support to detect Windows Metadata version information

## Known Bugs:

| Bug ID | Details | Notes/Workaround | Status |
| :----- | :-----: | :--------------: | -----: |
| 1 | ~~`tolower_str` contains a bug that make miss the characters that already in lowercase.~~ |  | Resolved |
| 2 | ~~`tolower_Cstr` contains a bug that make miss the characters that already in lowercase.~~ |  | Resolved |
| 3 | ~~When sending a version string on format *MAJOR.MINOR.PATCH.REVISION* to `VersionData`, the `build_type_number` or *revision* **can not be detected**~~ | The algorithm received a new version on **version 0.8.6** to eliminate the defections in detect string versions and add more permissive formats. To enable the experimental algorithm it's necessary enable `VERSION_LIB_ENABLE_EXPERIMENTAL_FIX_VERSIONSTR_2_VERSIONSTRUCT`. **NOTE: Originally the fix was coming to version 0.8.7. In 0.8.7 the experimental algorithm will be enable by default** | **Fix in tests** |
| 4 | ~~Using `VersionData` operators *less*, *less than*, *greater* and *greater than* does not work as expected~~ |  | Resolved |
| 5 | ~~VersionData method,`getBuildTypeCstr`, does not convert the C++ string data into C-style string~~ |  | Resolved |
| 6 | ~~VersionData method, `getBuildTypeCompleteCstr`, does not convert C++ string data into C-style string~~ |  | Resolved |
| 7 | ~~`VersionData` constructors not working after implementation of `cmpBuild` parameter, resulting in ambiguous reference~~ | If `VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_CONSTRUCTORS` is not defined, the modified constructors are disabled to avoid the ambiguous reference. **NOTE:** Using `VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_CONSTRUCTORS`, will **break** any code that uses original constructor parameter list. **NOTE: On version 0.9.0-alpha, the experimental constructors will be the focus during the development** | Resolved  |
| 8 | `VersionException` fails when throw the object | Using *`catch (VersionLib::VersionException& e)`* does not fail. The workaround is not definitive. New tests and modification may happen to make sure it's working properly | **Fix in development** |
| 9 | Enabling experimental optimized memory layout result in missing correct data to `build_type_number`. **NOTE: The experimental feature was only tested on Windows platforms with MSVC** | To avoid missing any data, keep `VERSION_LIB_ENABLE_EXPERIMENTAL_MEM_LAYOUT` disabled | Not resolved |

## Deprecated Features:

| Feature | Details | Workaround | Notes |
| :------ | :-----: | :--------: | ----: |
| `toVersionStruct` | Deprecated method because is not reliable to convert the version information to `VersionStruct` | Use `toVersionStrut2` with more reliable semantic versioning conversion. | On version **0.9.0-alpha** this method will be removed |

## Removed Features:

| Feature | Details | Workaround | Notes |
| :------ | :-----: | :--------: | ----: |

# Technical Information

> This section was added to provide more technical information.
>
> This section may be moved in the future to a dedicated file.

## `VersionStruct` and `VersionData` memory layout:

> **NOTE:** The new memory layout is available as experimental feature. To enable, set `VERSION_LIB_ENABLE_EXPERIMENTAL_MEM_LAYOUT`.
>
> **NOTE:** Experimental memory layout will not be part of the main experimental features development.

Before version **0.8.6**, the original construction of the `VersionStruct` was:

```C
struct VersionStruct
{
    unsigned int major;					// Major version number
    unsigned int minor;					// Minor version number
    unsigned int patch;					// Patch version number
    unsigned long long build;			// Build number
    VersionLib::BuildType build_type;	// Build type (alpha, a, beta, etc)
    unsigned int build_type_number;		// Build type number (alpha1, rc3)
    bool compare_build;					// Build comparison control
};
```

The original declarations make the struct use 40 bytes in memory allocation, following the layout:

```
------------------------------------------------------------------------------------
   | 0 bytes |         |         |         | 4 bytes |         |         |         |
 0 | ############## Major ################ | ################ Minor ############## |
 8 | ############## Patch ################ |                                       |
24 | ################################## Build #################################### |
16 | ## Build Type ##  |                   | ######### build_type_number ######### |
32 | Compare |                             |                                       |
------------------------------------------------------------------------------------
```

On version **0.8.6** the `VersionStruct` will be declared differently when `VERSION_LIB_ENABLE_EXPERIMENTAL_MEM_LAYOUT` is enabled:

```C
struct VersionStruct
{
    unsigned int major;					// Major version number
    unsigned int minor;					// Minor version number
    unsigned int patch;					// Patch version number
    unsigned int build_type_number;		// Build type number (alpha1, rc3)
    unsigned long long build;			// Build number
    VersionLib::BuildType build_type;	// Build type (alpha, a, beta, etc)
    bool compare_build;					// Build comparison control
};
```

The memory layout will be different, using the 4 bytes that was being wasted, to allocate revision data. Making the revised struct to use only 32 bytes.

```
------------------------------------------------------------------------------------
   | 0 bytes |         |         |         | 4 bytes |         |         |         |
 0 | ############## Major ################ | ################ Minor ############## |
 8 | ############## Patch ################ | ######### build_type_number ######### |
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