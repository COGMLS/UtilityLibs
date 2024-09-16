###########################################################
#
# CMakeLists: LoggerLib Root
#
###########################################################

cmake_minimum_required(VERSION 3.28)

###########################################################
#
# Define the general solution settings
#
###########################################################

# Define local Settings Library project root var:
set(LoggerSolutionRoot ${CMAKE_CURRENT_LIST_DIR})

###########################################################
#
# Sub projects:
#
###########################################################

add_subdirectory("LoggerLib")