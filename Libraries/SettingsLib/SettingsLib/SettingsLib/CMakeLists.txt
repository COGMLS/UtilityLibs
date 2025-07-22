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
project(
			SettingsLib
			VERSION 3.0.0
			DESCRIPTION "Settings Library."
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

# Define library final name:
if(UseVersionOnLibName)
	set(LibraryFinalName "${UtilLibsMainName}.${LibraryName}")
else()
	set(LibraryFinalName "${UtilLibsMainName}.${LibraryName}${LibraryGen}")
endif()

# Include libraries directories source codes:
#include_directories("${SettingsLibReposRoot}/Libs/<lib>")
include_directories("${SettingsLibraryRoot}")
include_directories("${SettingsLibraryRoot}/Components/Exceptions")
include_directories("${SettingsLibraryRoot}/Components/Configs/Ini")

# Define to export the library methods to all compatible systems:
add_compile_definitions(SETTINGS_LIB_EXPORTS)

if(WIN32)
	# Add the export here
endif()

# Define the library build properties:
if (WIN32)
	add_library(
					${LibraryFinalName}
					SHARED
					# Library Windows headers:
					"dllmain.hpp" 										"dllmain.cpp"
					# Settings Library main header:
					"SettingsLib.hpp" 									"SettingsLib.cpp"
					# Settings Library Version and Features headers:
					"SettingsLibExperimentalFeatures.hpp"
					"SettingsLibVersion.hpp"
					"SettingsLibVersionHelper.hpp" 						"SettingsLibVersionHelper.cpp"
					# Settings Library headers:
					"SettingsLibConfig.hpp" 							"SettingsLibConfig.hpp"
					"SettingsLibConfigFileStream.hpp" 					"SettingsLibConfigFileStream.cpp"
					"SettingsLibDataTypes.hpp" 							"SettingsLibDataTypes.cpp"
					"SettingsLibDefinitions.hpp"
					"SettingsLibErrorCodes.hpp"
					"SettingsLibTools.hpp" 								"SettingsLibTools.cpp"
					# Error and Exceptions:
					"Components/Exceptions/SettingsLibException.hpp" 	"Components/Exceptions/SettingsLibException.cpp"
					# Ini files:
					"Components/Configs/Ini/SettingsIniConfig.hpp" 		"Components/Configs/Ini/SettingsIniConfig.cpp"
					"Components/Configs/Ini/SettingsIniConfigData.hpp" 	"Components/Configs/Ini/SettingsIniConfigData.cpp"
					"Components/Configs/Ini/SettingsIniDefinitions.hpp"
					"Components/Configs/Ini/SettingsIniErrorCodes.hpp"
					"Components/Configs/Ini/SettingsIniTools.hpp" 		"Components/Configs/Ini/SettingsIniTools.cpp"
				)
else()
	add_library(
					${LibraryFinalName}
					SHARED
					# Settings Library main header:
					"SettingsLib.hpp" 									"SettingsLib.cpp"
					# Settings Library Version and Features headers:
					"SettingsLibExperimentalFeatures.hpp"
					"SettingsLibVersion.hpp"
					"SettingsLibVersionHelper.hpp" 						"SettingsLibVersionHelper.cpp"
					# Settings Library headers:
					"SettingsLibConfig.hpp" 							"SettingsLibConfig.hpp"
					"SettingsLibConfigFileStream.hpp" 					"SettingsLibConfigFileStream.cpp"
					"SettingsLibDataTypes.hpp" 							"SettingsLibDataTypes.cpp"
					"SettingsLibDefinitions.hpp"
					"SettingsLibErrorCodes.hpp"
					"SettingsLibTools.hpp" 								"SettingsLibTools.cpp"
					# Error and Exceptions:
					"Components/Exceptions/SettingsLibException.hpp" 	"Components/Exceptions/SettingsLibException.cpp"
					# Ini files:
					"Components/Configs/Ini/SettingsIniConfig.hpp" 		"Components/Configs/Ini/SettingsIniConfig.cpp"
					"Components/Configs/Ini/SettingsIniConfigData.hpp" 	"Components/Configs/Ini/SettingsIniConfigData.cpp"
					"Components/Configs/Ini/SettingsIniDefinitions.hpp"
					"Components/Configs/Ini/SettingsIniErrorCodes.hpp"
					"Components/Configs/Ini/SettingsIniTools.hpp" 		"Components/Configs/Ini/SettingsIniTools.cpp"
				)
endif()

# Define the version properties on binary component:
if(UseVersionOnLibName)
	set_target_properties(${LibraryFinalName} PROPERTIES VERSION ${PROJECT_VERSION})
	set_target_properties(${LibraryFinalName} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
endif()