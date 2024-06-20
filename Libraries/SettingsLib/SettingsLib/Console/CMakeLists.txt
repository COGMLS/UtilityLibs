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

if(DebugSettingsLib)
	add_compile_definitions(DEBUG)
endif()

add_compile_definitions(UNICODE)
add_compile_definitions(_UNICODE)

# Defined the project:
project(SettingsLibTestConsole VERSION 0.0.1 DESCRIPTION "Console to test the Settings Library.")

###########################################################
#
# Project components settings:
#
###########################################################

# Include libraries directories source codes:
#include_directories("${SettingsLibReposRoot}/Libs/<lib>")
include_directories("${SettingsLibReposRoot}/SettingsLib")

# Define the executable properties:
add_executable(SettingsLibTestConsole "main.cpp" "test.hpp" "test.cpp" "debug.hpp" "debug.cpp")

# Link the SettingsLibV2:
target_link_libraries(SettingsLibTestConsole SettingsLib)
