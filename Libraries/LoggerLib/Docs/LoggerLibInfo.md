# Logger Library: Project Information

This document contains the information about the future plans, known bugs, deprecated features.

## Recently Implementations:

- Sort log files by age.
- Experimental code control

## Implementations under development:

- `LogDataStore` to easily store various datatype with better memory usage
- Support to formatting log data

## Future Implementations:

- Move LoggerLib features to `LoggerLib` namespace
- Better error handling

## Known Bugs:

| Bug ID | Details | Notes/Workaround | Status |
| :----- | :-----: | :--------------: | -----: |
| 1 | ~~On Linux systems the log files are not getting in order as occurs on Windows~~ |  | **FIXED** |
| 2 | ~~Sorting log files is not working correctly~~ |  | **FIXED** |
| 3 | ~~`LogEntry` and `LogEntryW` does not make correct time check in equality operations, missing `seconds` variable check from `LoggerLocalDateTime` struct~~ |  | **FIXED** |
| 4 | ~~The standard algorithm to make the equality test between the both `logEntries` of **Logger** and **LoggerW** classes fails with new `LogDataStore`.~~ | A new algorithm as designed in `Logger` and `LoggerW` equality operator. No workaround is necessary. | **FIXED** |
| 5 | ~~Making equality of LogEntry or LogEntryW show the warning message: *C++20 says that these are ambiguous, even though the second is reversed*~~ | The GCC compiler show a warning message, but no anomaly in code functionality was found. **NOTE:** After the compilation, the warning disappears without reason. **NOTE 2:** Missing *const* in equality operators was the reason for warning messages | **FIXED** |

## Deprecated Features:

| Feature | Details | Workaround | Notes |
| :------ | :-----: | :--------: | ----: |
| Selection sort algorithm | The algorithm was falling to sort properly the log files | No workaround is necessary | The algorithm is disabled and a new algorithm is working. The code will be removed on version **3.3.0-beta** |
| `sortLogFileList2` | The function uses file age to determinate the sorted list with `std::filesystem::last_write_time`, but does not provide a reliable sorting list | Use `sortLogFileList` | This function will be removed on version **3.3.0-beta** |

## Removed Features:

| Feature | Details | Workaround | Notes |
| :------ | :-----: | :--------: | ----: |
| Experimental equality operators in `LogDataStore` | The experimental equality operators will be removed because no more workarounds are necessary to make the components to work. |  | The components was removed on version **3.3.0-alpha.10** |
