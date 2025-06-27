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

if(DebugVersionLib)
	add_compile_definitions(DEBUG)
	enable_testing()
endif()

add_compile_definitions(UNICODE)
add_compile_definitions(_UNICODE)

# Defined the project:
project(
			VersionLibTestConsole
			VERSION 1.0.0
			DESCRIPTION "Console to test the Settings Library."
		)

###########################################################
#
# Project components settings:
#
###########################################################

# Define test console partial naming:
set(TestConsole "")

# Define library partial naming:
set(LibraryName "VersionLib")

# Define library generation (major version):
set(LibraryGen 0)

# Define test console final name:
set(TestConsoleFinalName "${UtilLibsTestConsoleBaseName}.${LibraryName}${LibraryGen}")

# Include libraries directories source codes:
#include_directories("${ReposRoot}/Libraries/<lib>")
include_directories("${VersionLibReposRoot}/VersionLib")

# Define the executable properties:
add_executable(
					${TestConsoleFinalName}
					"main.cpp"
					"formatTests.hpp" "formatTests.cpp"
				)

# Define manual library link:
set(UseManualTargetLinkLibs False)
				
# Link the library depending on naming used:
if(UseVersionOnLibName)
	target_link_libraries(${TestConsoleFinalName} "${UtilLibsMainName}.${LibraryName}")
else()
	target_link_libraries(${TestConsoleFinalName} "${UtilLibsMainName}.${LibraryName}${LibraryGen}")
endif()

# Enable tests if DEBUG is set:

if (DebugVersionLib)
	mkArgTest(VersionLib_FormatsTest ${TestConsoleFinalName} "-test-formats")
	mkArgTest(VersionLib_OperatorTest ${TestConsoleFinalName} "-test-operators")
	mkArgTest(VersionLib_ExceptionTest ${TestConsoleFinalName} "-test-exceptions")
endif()