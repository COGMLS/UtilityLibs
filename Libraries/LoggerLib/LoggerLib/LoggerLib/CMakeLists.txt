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
			VERSION 3.2.0
			DESCRIPTION "Logger Library."
		)

###########################################################
#
# Project components settings:
#
###########################################################

# Include libraries directories source codes:
#include_directories("${ReposRoot}/Libraries/<lib>")

# Define to export the library methods for all compatible systems:
add_compile_definitions(LOGGER_LIB_EXPORTS)

# Define to export the library methods if is Windows:
if(WIN32)
	# Add the export here
endif()

# Define the library build properties:
if (WIN32)
	add_library(
					LoggerLib
					SHARED
					# Windows specific headers:
					"dllmain.cpp"
					"pch.h" "pch.cpp"
					# Logger main header:
					"LoggerLib.hpp"
					# Library headers
					"Logger.hpp" "Logger.cpp"
					"LoggerCommonDataTypes.hpp" "LoggerCommonDataTypes.cpp"
					"LoggerDateTime.hpp" "LoggerDateTime.cpp"
					"LoggerException.hpp" "LoggerException.cpp"
					"LoggerLibVersion.hpp"
					"LoggerLibVersionTools.hpp"
					"LogMng.hpp" "LogMng.cpp"
				)
else()
	add_library(
					LoggerLib
					SHARED
					# Logger main header:
					"LoggerLib.hpp"
					# Library headers
					"Logger.hpp" "Logger.cpp"
					"LoggerCommonDataTypes.hpp" "LoggerCommonDataTypes.cpp"
					"LoggerDateTime.hpp" "LoggerDateTime.cpp"
					"LoggerException.hpp" "LoggerException.cpp"
					"LoggerLibVersion.hpp"
					"LoggerLibVersionTools.hpp"
					"LogMng.hpp" "LogMng.cpp"
				)
endif()
