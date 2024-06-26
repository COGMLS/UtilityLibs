###########################################################
#
# CMakeLists: SettingsLib Library
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

# Define local Settings Library project root var:
set(SettingsLibraryRoot ${CMAKE_CURRENT_LIST_DIR})

# Define if is Windows Environment:

if(WIN32)
	add_compile_definitions(WIN32)
	add_compile_definitions(_WINDOWS)
	add_compile_definitions(_USRDLL)
	add_compile_definitions(_WINDLL)
endif()

if(DebugSettingsLib)
	add_compile_definitions(DEBUG)
endif()

add_compile_definitions(UNICODE)
add_compile_definitions(_UNICODE)

# Custom definition to mitigate the missing function reference by the compiler
#add_compile_definitions(MITIGATE_REF_FUNCTION)

# Defined the project:
project(SettingsLib VERSION 3.0.0 DESCRIPTION "Settings Library.")

###########################################################
#
# Project components settings:
#
###########################################################

# Include libraries directories source codes:
#include_directories("${SettingsLibReposRoot}/Libs/<lib>")
#include_directories("${SettingsLibraryRoot}/Extensions/Ini")

# Define to export the library methods if is Windows:
if(WIN32)
	# Add the export here
	add_compile_definitions(SETTINGS_LIB_EXPORTS)
endif()

# Define the library build properties:
if (WIN32)
	add_library(
					SettingsLib
					SHARED
					"dllmain.hpp" "dllmain.cpp"
					"SettingsLib.hpp" "SettingsLib.cpp"
					"SettingsLibConfig.hpp" "SettingsLibConfig.hpp"
					"SettingsLibConfigFileStream.hpp" "SettingsLibConfigFileStream.cpp"
					"SettingsLibDataTypes.hpp" "SettingsLibDataTypes.cpp"
					"SettingsLibDefinitions.hpp"
					"SettingsLibErrorCodes.hpp"
					"SettingsLibTools.hpp" "SettingsLibTools.cpp"
					"SettingsLibVersionHelper.hpp" "SettingsLibVersionHelper.cpp"
					# Ini files:
					"SettingsIniConfig.hpp" "SettingsIniConfig.cpp"
					"SettingsIniConfigData.hpp" "SettingsIniConfigData.cpp"
					"SettingsIniDefinitions.hpp"
					"SettingsIniErrorCodes.hpp"
					"SettingsIniTools.hpp" "SettingsIniTools.cpp"
				)
else()
	add_library(
					SettingsLib
					SHARED
					"SettingsLib.hpp" "SettingsLib.cpp"
					"SettingsLibConfig.hpp" "SettingsLibConfig.hpp"
					"SettingsLibConfigFileStream.hpp" "SettingsLibConfigFileStream.cpp"
					"SettingsLibDataTypes.hpp"
					"SettingsLibDefinitions.hpp"
					"SettingsLibErrorCodes.hpp"
					"SettingsLibTools.hpp" "SettingsLibTools.cpp"
					"SettingsLibVersionHelper.hpp" "SettingsLibVersionHelper.cpp"
					# Ini files:
					"SettingsIniConfigData.hpp" "SettingsIniConfigData.cpp"
					"SettingsIniDefinitions.hpp"
					"SettingsIniErrorCodes.hpp"
					"SettingsIniTools.hpp" "SettingsIniTools.cpp"
				)
endif()
