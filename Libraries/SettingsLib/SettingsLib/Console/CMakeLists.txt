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
project(
			SettingsLibTestConsole
			VERSION 1.0.0
			DESCRIPTION "Console to test the Settings Library."
		)

###########################################################
#
# Project components settings:
#
###########################################################

# Define library partial naming:
set(LibraryName "SettingsLib")

# Define library generation (major version):
set(LibraryGen 3)

# Define test console final name:
set(TestConsoleFinalName "${UtilLibsTestConsoleBaseName}.${LibraryName}${LibraryGen}")

# Include libraries directories source codes:
#include_directories("${SettingsLibReposRoot}/Libs/<lib>")
#include_directories("${SettingsLibReposRoot}/SettingsLib")
#include_directories("${SettingsLibReposRoot}/SettingsLib/Components/Exception")
#include_directories("${SettingsLibReposRoot}/SettingsLib/Components/Configs/Ini")

if(UseVersionOnLibName)
	target_include_directories("${UtilLibsMainName}.${LibraryName}" PUBLIC "${SettingsLibReposRoot}/SettingsLib")
	target_include_directories("${UtilLibsMainName}.${LibraryName}" PUBLIC "${SettingsLibReposRoot}/SettingsLib"/Components/Exception)
	target_include_directories("${UtilLibsMainName}.${LibraryName}" PUBLIC "${SettingsLibReposRoot}/SettingsLib/Configs/Ini")
else()
	target_include_directories("${UtilLibsMainName}.${LibraryName}${LibraryGen}" PUBLIC "${SettingsLibReposRoot}/SettingsLib")
	target_include_directories("${UtilLibsMainName}.${LibraryName}${LibraryGen}" PUBLIC "${SettingsLibReposRoot}/SettingsLib"/Components/Exception)
	target_include_directories("${UtilLibsMainName}.${LibraryName}${LibraryGen}" PUBLIC "${SettingsLibReposRoot}/SettingsLib/Configs/Ini")
endif()

# Define the executable properties:
add_executable(
					${TestConsoleFinalName}
					"main.cpp"
					"test.hpp" "test.cpp"
					"debug.hpp" "debug.cpp"
				)

# Link the library depending on naming used:
if(UseVersionOnLibName)
	target_link_libraries(${TestConsoleFinalName} "${UtilLibsMainName}.${LibraryName}")
else()
	target_link_libraries(${TestConsoleFinalName} "${UtilLibsMainName}.${LibraryName}${LibraryGen}")
endif()