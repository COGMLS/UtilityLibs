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

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

# Define if is Windows Environment:

if(WIN32)
	add_compile_definitions(WIN32)
endif()

if(WIN32)
	add_compile_definitions(_CONSOLE)
endif()

if(DebugVersionLib)
	add_compile_definitions(DEBUG)
	enable_testing()
endif()

add_compile_definitions(UNICODE)
add_compile_definitions(_UNICODE)

# Defined the project:
project(
			VersionLibTestConsole_C
			VERSION 1.0.0
			DESCRIPTION "C language version of console test"
		)

###########################################################
#
# Project components settings:
#
###########################################################

# Define library partial naming:
set(LibraryName "VersionLib")

# Define library generation (major version):
set(LibraryGen 0)

# Define test console final name:
set(TestConsoleFinalName "${UtilLibsTestConsoleBaseName}_C.${LibraryName}${LibraryGen}")

# Include libraries directories source codes:
#include_directories("${ReposRoot}/Libraries/<lib>")
include_directories("${VersionLibReposRoot}/VersionLib")

# Define the executable properties:
add_executable(
					${TestConsoleFinalName}
					"main.c"
				)

# Link the library depending on naming used:
if(UseVersionOnLibName)
	target_link_libraries(${TestConsoleFinalName} "${UtilLibsMainName}.${LibraryName}")
else()
	target_link_libraries(${TestConsoleFinalName} "${UtilLibsMainName}.${LibraryName}${LibraryGen}")
endif()

# Enable tests if DEBUG is set:

if (DebugVersionLib)
endif()