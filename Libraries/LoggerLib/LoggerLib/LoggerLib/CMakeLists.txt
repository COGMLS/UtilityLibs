###########################################################
#
# CMakeLists: LoggerLib Library
#
###########################################################

cmake_minimum_required(VERSION 3.28)

###########################################################
#
# Define the general solution settings
#
###########################################################

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define local Settings Library project root var:
set(LoggerLibRoot ${CMAKE_CURRENT_LIST_DIR})

# Define if is Windows Environment:

if(WIN32)
	add_compile_definitions(WIN32)
	add_compile_definitions(_WINDOWS)
	add_compile_definitions(_USRDLL)
	add_compile_definitions(_WINDLL)
endif()

if(DebugLoggerLib)
	add_compile_definitions(DEBUG)
endif()

add_compile_definitions(UNICODE)
add_compile_definitions(_UNICODE)

# Defined the project:
project(
			LoggerLib
			VERSION 3.1.1
			DESCRIPTION "Logger Library."
		)

###########################################################
#
# Project components settings:
#
###########################################################

# Include libraries directories source codes:
#include_directories("${ReposRoot}/Libraries/<lib>")

# Define to export the library methods if is Windows:
if(WIN32)
	# Add the export here
	add_compile_definitions(LOGGER_LIB_EXPORTS)
endif()

# Define the library build properties:
if (WIN32)
	add_library(
					LoggerLib
					SHARED
					"dllmain.cpp"
					"pch.h" "pch.cpp"
					"Logger.hpp" "Logger.cpp"
					"LoggerCommonDataTypes.hpp" "LoggerCommonDataTypes.cpp"
					"LoggerDateTime.hpp" "LoggerDateTime.cpp"
					"LoggerException.hpp" "LoggerException.cpp"
					"LoggerLibDef.hpp"
					"LoggerLibVersion.hpp"
					"LoggerLibVersionTools.hpp"
					"LogMng.hpp" "LogMng.cpp"
				)
else()
	add_library(
					LoggerLib
					SHARED
					"Logger.hpp" "Logger.cpp"
					"LoggerCommonDataTypes.hpp" "LoggerCommonDataTypes.cpp"
					"LoggerDateTime.hpp" "LoggerDateTime.cpp"
					"LoggerException.hpp" "LoggerException.cpp"
					"LoggerLibDef.hpp"
					"LoggerLibVersion.hpp"
					"LoggerLibVersionTools.hpp"
					"LogMng.hpp" "LogMng.cpp"
				)
endif()
