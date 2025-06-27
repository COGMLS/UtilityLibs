###########################################################
#
# CMakeLists: Console
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

# Define if is Windows Environment:

if(WIN32)
	add_compile_definitions(WIN32)
endif()

if(WIN32)
	add_compile_definitions(_CONSOLE)
endif()

if(DebugLoggerLib)
	add_compile_definitions(DEBUG)
endif()

add_compile_definitions(UNICODE)
add_compile_definitions(_UNICODE)

# Defined the project:
project(
			LoggerLibTestConsole
			VERSION 1.5.1
			DESCRIPTION "Console to test the Settings Library."
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

# Define test console final name:
set(TestConsoleFinalName "${UtilLibsTestConsoleBaseName}.${LibraryName}${LibraryGen}")

# Include libraries directories source codes:
#include_directories("${ReposRoot}/Libraries/<lib>")
#include_directories("${LoggerLibReposRoot}/LoggerLib")
if(UseVersionOnLibName)
	target_include_directories("${UtilLibsMainName}.${LibraryName}" PUBLIC "${LoggerLibReposRoot}/LoggerLib")
else()
	target_include_directories("${UtilLibsMainName}.${LibraryName}${LibraryGen}" PUBLIC "${LoggerLibReposRoot}/LoggerLib")
endif()

# Define the executable properties:
add_executable(
					${TestConsoleFinalName}
					"main.cpp"
				)

# Link the library depending on naming used:
if(UseVersionOnLibName)
	target_link_libraries(${TestConsoleFinalName} "${UtilLibsMainName}.${LibraryName}")
else()
	target_link_libraries(${TestConsoleFinalName} "${UtilLibsMainName}.${LibraryName}${LibraryGen}")
endif()
