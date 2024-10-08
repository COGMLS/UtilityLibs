###########################################################
#
# CMakeLists: Logger Library V1 Solution
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
set(LoggerLibReposRoot ${CMAKE_CURRENT_LIST_DIR})
#set(LoggerLibFinalBinDir "${LoggerLibReposRoot}/build/bin")

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LoggerLibFinalBinDir})
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LoggerLibFinalBinDir})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LoggerLibFinalBinDir})

# Define the DEBUG preprocessor definition:
set(DebugLoggerLib True)

project(LoggerLibProject VERSION 1.0.0 DESCRIPTION "Logger Library solution with a console for tests.")

###########################################################
#
# Sub projects:
#
###########################################################

add_subdirectory("LoggerLib")
add_subdirectory("Console")