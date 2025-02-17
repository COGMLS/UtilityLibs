#pragma once

#ifndef LOGGER_LIBRARY_HPP
#define LOGGER_LIBRARY_HPP

#include "LoggerExperimental.hpp"

#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE
#include "LogDataStore.hpp"
#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_STORE

#ifdef LOGGER_ENABLE_EXPERIMENTAL_DATA_FORMATTER
#include "LoggerInfoFormatter.hpp"
#endif // !LOGGER_ENABLE_EXPERIMENTAL_DATA_FORMATTER

#include "Logger.hpp"
#include "LoggerCommonDataTypes.hpp"
#include "LoggerDateTime.hpp"

#ifdef LOGGER_ENABLE_EXPERIMENTAL_CUSTOM_EXCEPTIONS
#include "LoggerException.hpp"
#endif // !LOGGER_ENABLE_EXPERIMENTAL_CUSTOM_EXCEPTIONS

#include "LoggerLibVersion.hpp"
#include "LoggerLibVersionTools.hpp"
#include "LogMng.hpp"

#endif // !LOGGER_LIBRARY_HPP