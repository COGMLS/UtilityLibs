#pragma once

#ifndef LOGGER_EXPERIMENTAL_FEATURES_CONTROL_HPP
#define LOGGER_EXPERIMENTAL_FEATURES_CONTROL_HPP

// Determinate to use LogDataStore class:
#define LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE

// Determinate to use log data formatter:
//#define LOGGER_ENABLE_EXPERIMENTAL_DATA_FORMATTER

// Determinate to use custom exceptions:
//#define LOGGER_ENABLE_EXPERIMENTAL_CUSTOM_EXCEPTIONS

// Set to use experimental high precision time on all platforms:
//#define LOGGER_ENABLE_EXPERIMENTAL_ALL_PLATFORMS_HIGH_PRECISION_TIME

// Set to use experimental bubble sort alg v1:
#define LOGGER_ENABLE_EXPERIMENTAL_LOGGER_BUBBLE_SORT_1

// Set to use experimental bubble sort alg v2:
#define LOGGER_ENABLE_EXPERIMENTAL_LOGGER_BUBBLE_SORT_2

// Enable the experimental LogEntry date register:
#define LOGGER_ENABLE_EXPERIMENTAL_LOGENTRY_DT_REG

#endif // !LOGGER_EXPERIMENTAL_FEATURES_CONTROL_HPP