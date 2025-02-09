# Logger Library: Project Information

This document contains the information about the future plans, known bugs, deprecated features.

## Implementations under development:

- Sort log files by age.
- Support to formatting log data

## Future Implementations:

- Move LoggerLib features to `LoggerLib` namespace
- Better error handling

## Known Bugs:

| Bug ID | Details | Status |
| :---   | :---:   | ---:   |
| 1 | On Linux systems the log files are not getting in order as occurs on Windows | Improvements under tests |
| 2 | Sorting log files is not working correctly | On first tests, the new algorithm is sorting as expected on Linux systems. Tests on Windows platform are needed |

## Deprecated Features:

| Feature | Details | Workaround | Notes |
| :------ | :-----: | :--------: | ----: |
| Selection sort algorithm | The algorithm was falling to sort properly the log files | No workaround is necessary | The algorithm is disabled and a new algorithm is working. The code will be removed on future update |
| `sortLogFileList2` | The function uses file age to determinate the sorted list with `std::filesystem::last_write_time`, but does not provide a reliable sorting list | Use `sortLogFileList` | This function will be removed in a future update |

## Removed Features:

| Feature | Details | Workaround | Notes |
| :------ | :-----: | :--------: | ----: |
