###########################################################
#
# CMakeLists: Version Library Solution
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
set(VersionLibReposRoot ${CMAKE_CURRENT_LIST_DIR})

#set(VersionLibFinalBinDir "${VersionLibReposRoot}/build/bin")

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${VersionLibFinalBinDir})

if (NOT WIN32)
	#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${VersionLibFinalBinDir})
endif()

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${VersionLibFinalBinDir})

# Define the DEBUG preprocessor definition:
set(DebugVersionLib True)

# Enable Version Library Experimental Features:
add_compile_definitions(ENABLE_VERSION_LIBRARY_EXPERIMENTAL_FEATURES)

project(
			VersionLibProject
			VERSION 1.0.0
			DESCRIPTION "Version Library solution with a console for tests."
		)

###########################################################
#
# Sub projects:
#
###########################################################

add_subdirectory("VersionLib")
add_subdirectory("Console")