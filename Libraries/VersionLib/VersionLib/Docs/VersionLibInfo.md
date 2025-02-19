# Version Library: Project Information

This document contains the information about the future plans, known bugs, deprecated features.

## Recent Implementations:

- Support for convert `VersionStruct` to `VersionData` and vice-versa.

## Implementations under development:

- Support to create objects versions without warning messages with wrapper constructors.
- Add support to compare versions with build information.
- Include the global internal Version Library data.
- Full support for C-Style functions to better support for extern C linkage
- Add Version Lib errors and exceptions components

## Future Implementations:

- Full support for extern C linkage
- Support to identify version files by it's name
- Support to detect Windows Metadata version information
- Add and update all documentation for the Version Library

## Known Bugs:

| Bug ID | Details | Notes/Workaround | Status |
| :----- | :-----: | :--------------: | -----: |
| 1 | ~~`tolower_str` contains a bug that make miss the characters that already in lowercase.~~ |  | Resolved |
| 2 | ~~`tolower_Cstr` contains a bug that make miss the characters that already in lowercase.~~ |  | Resolved |
| 3 | When sending a version string on format *MAJOR.MINOR.PATCH.REVISION* to `VersionData`, the `build_type_number` or *revision* **can not be detected** | The algorithm will receive a revision on **version 0.8.7** to reduce/eliminate it's defections in detect string versions. | Not resolved |
| 4 | ~~Using `VersionData` operators *less*, *less than*, *greater* and *greater than* does not work as expected~~ |  | Resolved |
| 5 | ~~VersionData method,`getBuildTypeCstr`, does not convert the C++ string data into C-style string~~ |  | Resolved |
| 6 | ~~VersionData method, `getBuildTypeCompleteCstr`, does not convert C++ string data into C-style string~~ |  | Resolved |
| 7 | ~~`VersionData` constructors not working after implementation of `cmpBuild` parameter, resulting in ambiguous reference~~ | If `VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_CONSTRUCTORS` is not defined, the modified constructors are disabled to avoid the ambiguous reference. **NOTE:** Using `VERSION_LIB_ENABLE_EXPERIMENTAL_VERSIONDATA_CONSTRUCTORS`, will **break** any code that uses original constructor parameter list. **NOTE: On version 0.9.0-alpha, the experiemental constructors will be the focus during the development** | Resolved  |
| 8 | `VersionException` fails when throw the object | Using *`catch (VersionLib::VersionException& e)`* does not fail. The workaround is not definitive. New tests and modification may happen to make sure it's working properly | **Fix in development** |

## Deprecated Features:

| Feature | Details | Workaround | Notes |
| :------ | :-----: | :--------: | ----: |
| `toVersionStruct` | Deprecated method because is not reliable to convert the version information to `VersionStruct` | Use `toVersionStrut2` with more reliable semantic versioning conversion. | On version **0.9.0-alpha** this method will be removed |

## Removed Features:

| Feature | Details | Workaround | Notes |
| :------ | :-----: | :--------: | ----: |
