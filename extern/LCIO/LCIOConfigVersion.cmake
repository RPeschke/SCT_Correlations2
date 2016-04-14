##############################################################################
# this file is parsed when FIND_PACKAGE is called with version argument
#
# @author Jan Engels, Desy IT
##############################################################################


SET( ${PACKAGE_FIND_NAME}_VERSION_MAJOR 2 )
SET( ${PACKAGE_FIND_NAME}_VERSION_MINOR 4 )
SET( ${PACKAGE_FIND_NAME}_VERSION_PATCH 3 )


#INCLUDE( "/MacroCheckPackageVersion.cmake" )
INCLUDE( "C:/projects/ILCSOFT_git/v01-17-05/lcio/v02-04-03/cmake/MacroCheckPackageVersion.cmake" )
CHECK_PACKAGE_VERSION( ${PACKAGE_FIND_NAME} 2.4.3 )

