########################################################
CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)
########################################################
# project name
PROJECT( SCT_plot )

# project version
SET( ${PROJECT_NAME}_VERSION_MAJOR 1 )
SET( ${PROJECT_NAME}_VERSION_MINOR 0 )
SET( ${PROJECT_NAME}_VERSION_PATCH 0 )

# some macros are redefined to keep compatability with CMake 2.6
include(${PROJECT_SOURCE_DIR}/cmake/CMakeCompatibility.cmake)

# Determine platform- and compiler-specific settings
include(${PROJECT_SOURCE_DIR}/cmake/Platform.cmake)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")



# set the path to which we will install later: default project home, can be changed using
# cmake -DINSTALL_PREFIX=/some/dir ..
SET(INSTALL_PREFIX "${PROJECT_SOURCE_DIR}" CACHE PATH "Prefix prepended to install directories")
SET(CMAKE_INSTALL_PREFIX "${INSTALL_PREFIX}" CACHE INTERNAL "Prefix prepended to install directories" FORCE)




# include directories
INCLUDE_DIRECTORIES( ./core_lib/includes )



set(SCT_PLOTS_INCLUDES ${PROJECT_SOURCE_DIR}/core_lib/includes)

# additional packages to be searched for by cmake
LIST( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )


IF(WIN32)
add_subdirectory(ReleaseVectorDef)
ENDIF(WIN32)
add_subdirectory(core_lib)
add_subdirectory(bin_processFile)

add_subdirectory(bin_processCollection)
add_subdirectory(bin_apix_tel_correlations)
add_subdirectory(bin_sz_correlations)

#######################################################
# Print out system information useful for bug reports #
############################################### #######
include(PrintSystemInformation)



