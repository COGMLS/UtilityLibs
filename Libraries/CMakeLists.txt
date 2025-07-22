###########################################################
#
# CMakeLists: Libraries
#
###########################################################

cmake_minimum_required(VERSION 3.28)

# Define local Libraries root var:
set(LibsRoot ${CMAKE_CURRENT_LIST_DIR})

###########################################################
#
# Sub projects:
#
###########################################################

if(EXISTS "${LibsRoot}/SettingsLib/CMakeLists.txt")
	add_subdirectory("SettingsLib")
endif()

if(EXISTS "${LibsRoot}/LoggerLib/CMakeLists.txt")
	add_subdirectory("LoggerLib")
endif()

if(EXISTS "${LibsRoot}/VersionLib/CMakeLists.txt")
	add_subdirectory("VersionLib")
endif()