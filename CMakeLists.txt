###########################################################
#
# CMakeLists: Utility Libraries Solution
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
set(ReposRoot ${CMAKE_CURRENT_LIST_DIR})
set(FinalBinDir "${ReposRoot}/build/bin")

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${FinalBinDir})

if (NOT WIN32)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${FinalBinDir})
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FinalBinDir})

# Utility Libraries Solution:
project(
			UtilLibsSln
			VERSION 0.0.1
			DESCRIPTION "Complete solution for Utility Libraries Solution repository."
		)

###########################################################
#
# Project naming standards:
#
###########################################################

# Define global partial names:

# Define the repository's name for partial library naming:
set(UtilLibsMainName "UtilLibs")

# Define the test consoles base name:
set(UtilLibsTestConsoleBaseName "TestConsole")

###########################################################
#
# Global projects custom settings:
#
###########################################################

# Define if will compile test consoles:
set(CompileTestConsole True)

# Define if will export version into library's name:
set(UseVersionOnLibName False)

###########################################################
#
# Functions:
#
###########################################################

# Make a test with specific arguments:
function(mkArgTest test target arg)
	add_test(NAME ${test} COMMAND ${target} ${arg})
endfunction()

###########################################################
#
# Sub projects:
#
###########################################################

add_subdirectory("Libraries")