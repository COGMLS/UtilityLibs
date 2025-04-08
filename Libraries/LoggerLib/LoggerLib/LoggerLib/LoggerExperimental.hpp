#pragma once

#ifndef LOGGER_EXPERIMENTAL_FEATURES_CONTROL_HPP
#define LOGGER_EXPERIMENTAL_FEATURES_CONTROL_HPP

#include "LoggerLibVersion.hpp"

//
// Alpha Features:
//

#if LOGGER_LIB_COMPILE_BUILD_TYPE == 1
	// Enable LogDataStore:
	#define LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE

	// Determinate to use log data formatter:
	#define LOGGER_ENABLE_EXPERIMENTAL_DATA_FORMATTER

	// Determinate to use custom exceptions:
	#define LOGGER_ENABLE_EXPERIMENTAL_CUSTOM_EXCEPTIONS

	// Set to use experimental high precision time on all platforms:
	#define LOGGER_ENABLE_EXPERIMENTAL_ALL_PLATFORMS_HIGH_PRECISION_TIME

	// Enable the experimental LogEntry date register:
	#define LOGGER_ENABLE_EXPERIMENTAL_LOGENTRY_DT_REG

	// Enable UTC and Local date time. This enable the local date time on Unix systems.
	#define LOGGER_ENABLE_EXPERIMENTAL_UTC_AND_LOCAL_DT
#endif // !LOGGER_LIB_COMPILE_BUILD_TYPE

//
// Beta Features:
//

#if LOGGER_LIB_COMPILE_BUILD_TYPE == 2
	// Enable LogDataStore:
	#define LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE

	// Determinate to use log data formatter:
	//#define LOGGER_ENABLE_EXPERIMENTAL_DATA_FORMATTER

	// Determinate to use custom exceptions:
	#define LOGGER_ENABLE_EXPERIMENTAL_CUSTOM_EXCEPTIONS

	// Set to use experimental high precision time on all platforms:
	#define LOGGER_ENABLE_EXPERIMENTAL_ALL_PLATFORMS_HIGH_PRECISION_TIME

	// Enable the experimental LogEntry date register:
	#define LOGGER_ENABLE_EXPERIMENTAL_LOGENTRY_DT_REG

	// Enable UTC and Local date time. This enable the local date time on Unix systems.
	#define LOGGER_ENABLE_EXPERIMENTAL_UTC_AND_LOCAL_DT
#endif // !LOGGER_LIB_COMPILE_BUILD_TYPE

//
// Release Candidate Features:
//

#if LOGGER_LIB_COMPILE_BUILD_TYPE == 3
	// Enable LogDataStore:
	#define LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE

	// Determinate to use log data formatter:
	//#define LOGGER_ENABLE_EXPERIMENTAL_DATA_FORMATTER

	// Determinate to use custom exceptions:
	//#define LOGGER_ENABLE_EXPERIMENTAL_CUSTOM_EXCEPTIONS

	// Set to use experimental high precision time on all platforms:
	#define LOGGER_ENABLE_EXPERIMENTAL_ALL_PLATFORMS_HIGH_PRECISION_TIME

	// Enable the experimental LogEntry date register:
	#define LOGGER_ENABLE_EXPERIMENTAL_LOGENTRY_DT_REG

	// Enable UTC and Local date time. This enable the local date time on Unix systems.
	#define LOGGER_ENABLE_EXPERIMENTAL_UTC_AND_LOCAL_DT
#endif // !LOGGER_LIB_COMPILE_BUILD_TYPE

//
// Release Features:
//

#if LOGGER_LIB_COMPILE_BUILD_TYPE == 4
	// Enable LogDataStore:
	#define LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE

	// Determinate to use log data formatter:
	//#define LOGGER_ENABLE_EXPERIMENTAL_DATA_FORMATTER

	// Determinate to use custom exceptions:
	//#define LOGGER_ENABLE_EXPERIMENTAL_CUSTOM_EXCEPTIONS

	// Set to use experimental high precision time on all platforms:
	//#define LOGGER_ENABLE_EXPERIMENTAL_ALL_PLATFORMS_HIGH_PRECISION_TIME

	// Enable the experimental LogEntry date register:
	#define LOGGER_ENABLE_EXPERIMENTAL_LOGENTRY_DT_REG

	// Enable UTC and Local date time. This enable the local date time on Unix systems.
	//#define LOGGER_ENABLE_EXPERIMENTAL_UTC_AND_LOCAL_DT
#endif // !LOGGER_LIB_COMPILE_BUILD_TYPE

#endif // !LOGGER_EXPERIMENTAL_FEATURES_CONTROL_HPP