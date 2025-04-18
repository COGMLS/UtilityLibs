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
			VERSION 0.8.4
			DESCRIPTION "Version Library."
		)

###########################################################
#
# Project components settings:
#
###########################################################

# Include libraries directories source codes:
#include_directories("${ReposRoot}/Libraries/<lib>")

# Define to export the library methods:
add_compile_definitions(VERSION_LIB_EXPORTS)

# Enable Version Library Experimental Features:
add_compile_definitions(ENABLE_VERSION_LIBRARY_EXPERIMENTAL_FEATURES)

# Define the library build properties:
if (WIN32)
	add_library(
					VersionLib
					SHARED
					# Windows specific headers:
					"dllmain.hpp" "dllmain.cpp"
					# Version Library main header:
					"VersionLib.hpp"
					# Version Library components:
					"BuildMetadata.hpp" 						"BuildMetadata.cpp"
					"BuildReleaseId.hpp"						"BuildReleaseId.cpp"
					"BuildTypes.hpp" 							"BuildTypes.cpp"
					"BuildTypesExt.hpp"							"BuildTypesExt.cpp"
					"ExceptionComponents.hpp"
					"ExperimentalFeatures.hpp"
					"ReleaseTools.hpp"							"ReleaseTools.cpp"
					"SemVerClass.hpp"							"SemVerClass.cpp"
					"Tools.hpp" 								"Tools.cpp"
					"VersionClass.hpp" 							"VersionClass.cpp"
					"VersionLibVersionInfo.hpp"
					"VersionStruct.hpp" 						"VersionStruct.cpp"
				)
else()
	add_library(
					VersionLib
					SHARED
					# Version Library main header:
					"VersionLib.hpp"
					# Version Library components:
					"BuildMetadata.hpp" 						"BuildMetadata.cpp"
					"BuildReleaseId.hpp"						"BuildReleaseId.cpp"
					"BuildTypes.hpp" 							"BuildTypes.cpp"
					"BuildTypesExt.hpp"							"BuildTypesExt.cpp"
					"ExceptionComponents.hpp"
					"ExperimentalFeatures.hpp"
					"ReleaseTools.hpp"							"ReleaseTools.cpp"
					"SemVerClass.hpp"							"SemVerClass.cpp"
					"Tools.hpp" 								"Tools.cpp"
					"VersionClass.hpp" 							"VersionClass.cpp"
					"VersionLibVersionInfo.hpp"
					"VersionStruct.hpp" 						"VersionStruct.cpp"
				)
endif()

###########################################################
# WARNING: About the linking libraries:
# --------------------------------------------------------
# For some reason, the methods in the libraries are not
# recognized directly, resulting in LINK2019 with MSVC or
# "undefined reference to" in GCC, but the methods are generated
# and exported. To mitigate this problem, set as "True" the
# CMake variable "UseManualTargetLinkLibs" to link then manually.
###########################################################

set(UseManualTargetLinkLibs False)

if(UseManualTargetLinkLibs)
	if (WIN32)
		if(DebugVersionLib)
			#target_link_libraries(VersionLib ${ReposRoot}/build/VersionLib/Libs/<lib>/Debug/<libfile>.lib)
		else()
			#target_link_libraries(VersionLib ${ReposRoot}/build/VersionLib/Libs/<lib>/Release/<libfile>.lib)
		endif()
	else()
		#target_link_libraries(VersionLib ${ReposRoot}/build/bin/lib<libName>.so)
	endif()
else()
	#target_link_libraries(VersionLib <librojectName>)
endif()