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
			VERSION 3.3.2
			DESCRIPTION "Logger Library."
		)

###########################################################
#
# Project components settings:
#
###########################################################

# Define library partial naming:
set(LibraryName "LoggerLib")

# Define library generation (major version):
set(LibraryGen 3)

# Define library final name:
if(UseVersionOnLibName)
	set(LibraryFinalName "${UtilLibsMainName}.${LibraryName}")
else()
	set(LibraryFinalName "${UtilLibsMainName}.${LibraryName}${LibraryGen}")
endif()

# Include libraries directories source codes:
#include_directories("${ReposRoot}/Libraries/<lib>")

# Define to export the library methods to all compatible systems:
add_compile_definitions(LOGGER_EXPORTS)

# Define to export the library methods if is Windows:
if(WIN32)
	# Add the export here
endif()

# Define the library build properties:
if (WIN32)
	add_library(
					${LibraryFinalName}
					SHARED
					# Windows specific headers:
					"dllmain.cpp"
					"pch.h" "pch.cpp"
					# Logger main header:
					"LoggerLib.hpp"
					# Library headers
					"LogDataStore.hpp" "LogDataStore.cpp"
					"Logger.hpp" "Logger.cpp"
					"LoggerCommonDataTypes.hpp" "LoggerCommonDataTypes.cpp"
					"LoggerDateTime.hpp" "LoggerDateTime.cpp"
					"LoggerException.hpp" "LoggerException.cpp"
					"LoggerExperimental.hpp"
					"LoggerInfoFormatter.hpp"	"LoggerInfoFormatter.cpp"
					"LoggerLibVersion.hpp"
					"LoggerLibVersionTools.hpp" "LoggerLibVersionTools.cpp"
					"LogMng.hpp" "LogMng.cpp"
				)
else()
	add_library(
					${LibraryFinalName}
					SHARED
					# Logger main header:
					"LoggerLib.hpp"
					# Library headers
					"LogDataStore.hpp" "LogDataStore.cpp"
					"Logger.hpp" "Logger.cpp"
					"LoggerCommonDataTypes.hpp" "LoggerCommonDataTypes.cpp"
					"LoggerDateTime.hpp" "LoggerDateTime.cpp"
					"LoggerException.hpp" "LoggerException.cpp"
					"LoggerExperimental.hpp"
					"LoggerInfoFormatter.hpp"	"LoggerInfoFormatter.cpp"
					"LoggerLibVersion.hpp"
					"LoggerLibVersionTools.hpp" "LoggerLibVersionTools.cpp"
					"LogMng.hpp" "LogMng.cpp"
				)
endif()

# Define the version properties on binary component:
if(UseVersionOnLibName)
	set_target_properties(${LibraryFinalName} PROPERTIES VERSION ${PROJECT_VERSION})
	set_target_properties(${LibraryFinalName} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
endif()