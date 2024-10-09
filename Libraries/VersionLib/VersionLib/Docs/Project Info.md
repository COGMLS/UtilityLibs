# Version Library: Project Information

This document contains the information about the future plans, known bugs, deprecated features.

## Future Implementations:

- Full support for extern C linkage
- Support to identify version files by it's name
- Support to detect Windows Metadata version information
- Support for convert `VersionStruct` to `VersionData` and vice-versa.
- Full support for C-Style functions to better support for extern C linkage
- Include the global internal Version Library data.
- Add and update all documentation for the Version Library

## Known Bugs:

| Bug ID | Details | Status |
| :---   | :---:   | ---:   |
| 1 | ~~`tolower_str` contains a bug that make miss the characters that already in lowercase.~~ | Resolved |
| 2 | `tolower_Cstr` contains a bug that make miss the characters that already in lowercase. | Not resolved |
| 3 | When sending a version string on format *MAJOR.MINOR.PATCH.REVISION* to `VersionData`, the `build_type_number` or *revision* **can not be detected** | Not resolved |

## Deprecated Features:

| Feature | Details | Workaround |
| :------ | :-----: | ---------: |
| `toVersionStruct` | Deprecated method because is not reliable to convert the version information to VersionStruct | Use toVersionStrut2 with more reliable semantic versioning conversion. |

## Removed Features:

| Feature | Details | Workaround |
| :------ | :-----: | ---------: |
