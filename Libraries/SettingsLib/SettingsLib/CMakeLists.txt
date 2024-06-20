###########################################################
#
# CMakeLists: Settings Library V2 Solution
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

# Define final location for binary files output:
set(SettingsLibReposRoot ${CMAKE_CURRENT_LIST_DIR})
#set(SettingsLibFinalBinDir "${SettingsLibReposRoot}/build/bin")
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SettingsLibFinalBinDir})
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SettingsLibFinalBinDir})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SettingsLibFinalBinDir})

# Define the DEBUG preprocessor definition:
set(DebugSettingsLib True)

project(SettingsLibProject VERSION 3.0.0 DESCRIPTION "Settings Library solution with a console for tests.")

###########################################################
#
# Sub projects:
#
###########################################################

add_subdirectory("SettingsLib")
add_subdirectory("Console")