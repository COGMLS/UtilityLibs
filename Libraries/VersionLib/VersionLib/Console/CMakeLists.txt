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

# Include libraries directories source codes:
#include_directories("${ReposRoot}/Libraries/<lib>")
include_directories("${VersionLibReposRoot}/VersionLib")

# Define the executable properties:
add_executable(
					VersionLibTestConsole
					"main.cpp"
				)

# Define manual library link:
set(UseManualTargetLinkLibs False)
				
# Link the VersionLib:
if(UseManualTargetLinkLibs)
	if (WIN32)
		if(DebugVersionLib)
			#target_link_libraries(VersionLibTestConsole ${ReposRoot}/build/VersionLib/Libs/<lib>/Debug/VersionLib.lib)
		else()
			#target_link_libraries(VersionLibTestConsole ${ReposRoot}/build/VersionLib/Libs/<lib>/Release/VersionLib.lib)
		endif()
	else()
		#target_link_libraries(VersionLibTestConsole ${ReposRoot}/build/bin/libVersionLib.so)
	endif()
else()
	target_link_libraries(VersionLibTestConsole VersionLib)
endif()

# Enable tests if DEBUG is set:

if (DEBUG)
	mkArgTest(VersionLib_FormatsTest VersionLibTestConsole "-test-formats")
	mkArgTest(VersionLib_OperatorTest VersionLibTestConsole "-test-operators")
endif()