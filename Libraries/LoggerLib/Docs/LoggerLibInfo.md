# Logger Library: Project Information

This document contains the information about the future plans, known bugs, deprecated features.

## Recently Implementations:

- Sort log files by age.
- Experimental code control
- `LogDataStore` to easily store various datatype with better memory usage
- *(Only for development)* Version build release type to control experimental features
- Optimized `LogDataStore` to use less instructions to operate
- Fix correct time format in log file format on *nix systems *(Version 3.4.0)*
- `LogEntry` and `LogEntryW` `operator<<` **are disabled** when not using both `LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE` and `LOGGER_ENABLE_EXPERIMENTAL_LOG_ENTRY_OPERATORS` *(Version 3.3.2)*
- New library naming. Now library uses Utility Libraries Naming Standard that follows UtilLibs.*LibraryName****LibraryGeneration***. This change will prepare the project for next modifications that may push to version 4.x and break current compatibility. In this case, the programs linked with this new naming convention, will be able to use version 3.x.y and keep working without the possibility to call the incompatible library.
- Reduced memory usage *(Version 3.3.3)*

## Implementations under development:

- Support to formatting log data
- UTC time format
- High Precision date and time to all platforms

## Future Implementations:

- Move LoggerLib features to `LoggerLib` namespace. *(**NOTE:** May break the actual codes)*
- Better error handling. *(**NOTE:** Support to `wstring` may bring difficulties to make it compatible with standard C++)*
- Logger manager self guard thread to detect application abort or any other termination that does not treat correctly the Logger Manager. *(**NOTE:** This experimental feature may not work as expected)*
- New ***Date and Time*** components to replace the actual `LogFileDateTime` class and functions `getLoggerDateTime` and `convertDateTime2LogStrEntry` and, struct `LoggerLocalDateTime`.

## Project Diagrams:

### Project Roadmap:

![Project Roadmap](/Libraries/LoggerLib/Docs/Images/LoggerLibRoadmap.png)

## Known Bugs:

| Bug ID | Details | Notes/Workaround | Status |
| :----- | :-----: | :--------------: | -----: |
| 1 | ~~On Linux systems the log files are not getting in order as occurs on Windows~~ |  | **FIXED** |
| 2 | ~~Sorting log files is not working correctly~~ |  | **FIXED** |
| 3 | ~~`LogEntry` and `LogEntryW` does not make correct time check in equality operations, missing `seconds` variable check from `LoggerLocalDateTime` struct~~ |  | **FIXED** |
| 4 | ~~The standard algorithm to make the equality test between the both `logEntries` of **Logger** and **LoggerW** classes fails with new `LogDataStore`.~~ | A new algorithm was designed in `Logger` and `LoggerW` equality operator. No workaround is necessary. | **FIXED** |
| 5 | ~~Making equality of LogEntry or LogEntryW show the warning message: *C++20 says that these are ambiguous, even though the second is reversed*~~ | The GCC compiler show a warning message, but no anomaly in code functionality was found. **NOTE:** After the compilation, the warning disappears without reason. **NOTE 2:** Missing *const* in equality operators was the reason for warning messages | **FIXED** |
| 6 | ~~Autosave feature writes incorrectly the log entries when the `logEntries` vector is less than `maxLogEntries`~~ |  | **FIXED** |
| 7 | ~~Missing autosave feature when the `Logger` and `LoggerW` destructors are called~~ |  | **FIXED** |
| 8 | ~~Autosave can fail to operate if `maxLogEntries` on `setAutoSave` method's parameter is set to zero~~ | Avoid set `maxLogEntries` to zero, while a fix is not released | **FIXED** |
| 9 | ~~`getLoggerDateTime` return UTC time format in Linux and MacOS when time should be returned as local time~~ |  | **FIXED** |
| 10 | ~~Missing `highPrecision` check in Equality Operators in `Logger` and `LoggerW`~~ |  | **FIXED** |
| 11 | ~~Missing correct instruction to check data between two ``LogDataStore` objects on Windows platforms~~ |  | **FIXED** |
| 12 | ~~Missing correct compile definition to Windows platforms~~ | **NOTE:** A fix in CMakeLists.txt file was made, but the original naming will be revised in a future update | **FIXED** |
| 13 | `LogEntry` and `LogEntryW` Stream Insertion operators are causing compilation failure on Windows platforms | **NOTE:** Added new experimental guard *LOGGER_ENABLE_EXPERIMENTAL_LOG_ENTRY_OPERATORS* to enable when `LogDataStore` is enabled too. Otherwise the operators will be disabled. | Not fixed |

## Deprecated Features:

| Feature | Details | Workaround | Notes |
| :------ | :-----: | :--------: | ----: |

## Removed Features:

| Feature | Details | Workaround | Notes |
| :------ | :-----: | :--------: | ----: |
| Experimental equality operators in `LogDataStore` | The experimental equality operators will be removed because no more workarounds are necessary to make the components to work. |  | The components was removed on version **3.3.0-alpha.10** |
| Selection sort algorithm | The algorithm was falling to sort properly the log files | No workaround is necessary | The algorithm is disabled and a new algorithm is working. The code will be removed on version **3.3.0-beta** |
| `sortLogFileList2` | The function uses file age to determinate the sorted list with `std::filesystem::last_write_time`, but does not provide a reliable sorting list | Use `sortLogFileList` | This function will be removed on version **3.3.0-beta** |
