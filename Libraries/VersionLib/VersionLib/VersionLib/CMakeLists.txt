###########################################################
#
# CMakeLists: VersionLib Library
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
set(VersionLibRoot ${CMAKE_CURRENT_LIST_DIR})

# Define if is Windows Environment:

if(WIN32)
	add_compile_definitions(WIN32)
	add_compile_definitions(_WINDOWS)
	add_compile_definitions(_USRDLL)
	add_compile_definitions(_WINDLL)
endif()

if(DebugVersionLib)
	add_compile_definitions(DEBUG)
endif()

add_compile_definitions(UNICODE)
add_compile_definitions(_UNICODE)

# Defined the project:
project(
			VersionLib
			VERSION 0.9.0
			DESCRIPTION "Version Library."
		)

###########################################################
#
# Project components settings:
#
###########################################################

# Define library partial naming:
set(LibraryName "VersionLib")

# Define library generation (major version):
set(LibraryGen 0)

# Define library final name:
if(UseVersionOnLibName)
	set(LibraryFinalName "${UtilLibsMainName}.${LibraryName}")
else()
	set(LibraryFinalName "${UtilLibsMainName}.${LibraryName}${LibraryGen}")
endif()

# Include libraries directories source codes:
#include_directories("${ReposRoot}/Libraries/<lib>")

# Define to export the library methods:
add_compile_definitions(VERSION_LIB_EXPORTS)

# Enable Version Library Experimental Features:
add_compile_definitions(ENABLE_VERSION_LIBRARY_EXPERIMENTAL_FEATURES)

# Define the library build properties:
if (WIN32)
	add_library(
					${LibraryFinalName}
					SHARED
					# Windows specific headers:
					"dllmain.hpp" "dllmain.cpp"
					# Version Library main header:
					"VersionLib.hpp"
					# Version Library internal version header:
					"VersionLibVersionInfo.h"
					"InternalVersion.hpp"						"InternalVersion.cpp"
					# Version Library components:
					"BuildMetadata.hpp" 						"BuildMetadata.cpp"
					"BuildReleaseId.hpp"						"BuildReleaseId.cpp"
					"BuildTypes.hpp" 							"BuildTypes.cpp"
					"BuildTypesExt.hpp"							"BuildTypesExt.cpp"
					"CommonTools.hpp"							"CommonTools.cpp"
					"ExceptionComponents.hpp"
					"ExperimentalFeatures.hpp"
					"ReleaseTools.hpp"							"ReleaseTools.cpp"
					"SemVerClass.hpp"							"SemVerClass.cpp"
					"VersionClass.hpp" 							"VersionClass.cpp"
					"VersionStruct.hpp" 						"VersionStruct.cpp"
					"VersionToken.hpp"							"VersionToken.cpp"
					"VersionTools.hpp"							"VersionTools.cpp"
				)
else()
	add_library(
					${LibraryFinalName}
					SHARED
					# Version Library main header:
					"VersionLib.hpp"
					# Version Library internal version header:
					"VersionLibVersionInfo.h"
					"InternalVersion.hpp"						"InternalVersion.cpp"
					# Version Library components:
					"BuildMetadata.hpp" 						"BuildMetadata.cpp"
					"BuildReleaseId.hpp"						"BuildReleaseId.cpp"
					"BuildTypes.hpp" 							"BuildTypes.cpp"
					"BuildTypesExt.hpp"							"BuildTypesExt.cpp"
					"CommonTools.hpp"							"CommonTools.cpp"
					"ExceptionComponents.hpp"
					"ExperimentalFeatures.hpp"
					"ReleaseTools.hpp"							"ReleaseTools.cpp"
					"SemVerClass.hpp"							"SemVerClass.cpp"
					"VersionClass.hpp" 							"VersionClass.cpp"
					"VersionStruct.hpp" 						"VersionStruct.cpp"
					"VersionToken.hpp"							"VersionToken.cpp"
					"VersionTools.hpp"							"VersionTools.cpp"
				)
endif()

# Define the version properties on binary component:
if(UseVersionOnLibName)
	set_target_properties(${LibraryFinalName} PROPERTIES VERSION ${PROJECT_VERSION})
	set_target_properties(${LibraryFinalName} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
endif()
