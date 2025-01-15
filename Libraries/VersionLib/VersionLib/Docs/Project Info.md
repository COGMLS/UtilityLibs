# Version Library: Project Information

This document contains the information about the future plans, known bugs, deprecated features.

## Implementations under development:

- Support for convert `VersionStruct` to `VersionData` and vice-versa.
- Include the global internal Version Library data.
- Full support for C-Style functions to better support for extern C linkage

## Future Implementations:

- Full support for extern C linkage
- Support to identify version files by it's name
- Support to detect Windows Metadata version information
- Add and update all documentation for the Version Library

## Known Bugs:

| Bug ID | Details | Status |
| :---   | :---:   | ---:   |
| 1 | ~~`tolower_str` contains a bug that make miss the characters that already in lowercase.~~ | Resolved |
| 2 | ~~`tolower_Cstr` contains a bug that make miss the characters that already in lowercase.~~ | Resolved |
| 3 | When sending a version string on format *MAJOR.MINOR.PATCH.REVISION* to `VersionData`, the `build_type_number` or *revision* **can not be detected** | Not resolved |
| 4 | ~~Using `VersionData` operators *less*, *less than*, *greater* and *greater than* does not work as expected~~ | Resolved |
| 5 | ~~VersionData method,`getBuildTypeCstr`, does not convert the C++ string data into C-style string~~ | Resolved |
| 6 | ~~VersionData method, `getBuildTypeCompleteCstr`, does not convert C++ string data into C-style string~~ | Resolved |

## Deprecated Features:

| Feature | Details | Workaround | Notes |
| :------ | :-----: | :--------: | ----: |
| `toVersionStruct` | Deprecated method because is not reliable to convert the version information to `VersionStruct` | Use `toVersionStrut2` with more reliable semantic versioning conversion. | On version **0.9.0-alpha** this method will be removed |

## Removed Features:

| Feature | Details | Workaround | Notes |
| :------ | :-----: | :--------: | ----: |
