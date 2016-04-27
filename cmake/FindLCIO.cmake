# - Try to find LCIO used in native reader library for exporting RAW to LCIO format needed for reconstruction
# Once done this will define
#  LCIO_FOUND - System has LCIO
#  LCIO_INCLUDE_DIRS - The LCIO include directories
#  LCIO_LIBRARIES - The libraries needed to use LCIO
#  LCIO_DEFINITIONS - Compiler switches required for using LCIO

  find_path(LCIO_INCLUDE_DIR lcio.h
    HINTS "${LCIO}/include" "$ENV{LCIO}/include" "${PROJECT_SOURCE_DIR}/extern/LCIO/include")

  find_library(LCIO_LIBRARY NAMES lcio
    HINTS "${LCIO}/lib" "$ENV{LCIO}/lib" "${PROJECT_SOURCE_DIR}/extern/LCIO/lib")

IF (${LCIO_LIBRARY} MATCHES "LCIO_LIBRARY-NOTFOUND")
  MESSAGE( "LCIO not found")
ELSE (${LCIO_LIBRARY} MATCHES "LCIO_LIBRARY-NOTFOUND")
MESSAGE("LCIO found")
set(LCIO_DEFINITIONS "-DUSE_LCIO" )
ENDIF (${LCIO_LIBRARY} MATCHES "LCIO_LIBRARY-NOTFOUND")


set(LCIO_LIBRARIES ${LCIO_LIBRARY} )
set(LCIO_INCLUDE_DIRS ${LCIO_INCLUDE_DIR} )


include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LCIO_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(LCIO  DEFAULT_MSG
                                  LCIO_LIBRARY LCIO_INCLUDE_DIR)

mark_as_advanced(LCIO_INCLUDE_DIR LCIO_LIBRARY )