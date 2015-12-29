# - Find freediameter
# Find the native FreeDiameter includes and libraries
#
#  FREEDIAMETER_FOUND - True if FreeDiameter found.
#  FREEDIAMETER_INCLUDE_DIR - where to find gnutls.h, etc.
#  FREEDIAMETER_LIBRARIES - List of libraries when using gnutls.
#  FREEDIAMETER_HSS_S6A_ENABLED - true if FreeDiameter enabled for S6A interface 


if (FREEDIAMETER_INCLUDE_DIR AND FREEDIAMETER_LIBRARIES)
  set(FREEDIAMETER_FIND_QUIETLY TRUE)
endif (FREEDIAMETER_INCLUDE_DIR AND FREEDIAMETER_LIBRARIES)

# Include dir
find_path(FREEDIAMETER_INCLUDE_DIR
    NAMES
    freeDiameter/freeDiameter-host.h
    freeDiameter/libfdcore.h
    freeDiameter/libfdproto.h
)

# Library
find_library(FREEDIAMETER_LIBRARY 
  NAMES fdcore
)

# handle the QUIETLY and REQUIRED arguments and set FREEDIAMETER_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(FREEDIAMETER DEFAULT_MSG FREEDIAMETER_LIBRARY FREEDIAMETER_INCLUDE_DIR)

IF(FREEDIAMETER_FOUND)
  SET( FREEDIAMETER_LIBRARIES ${FREEDIAMETER_LIBRARY} )
ELSE(FREEDIAMETER_FOUND)
  SET( FREEDIAMETER_LIBRARIES )
ENDIF(FREEDIAMETER_FOUND)

find_library(FREEDIAMETER_LIBRARY2 
  NAMES fdproto
)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(FREEDIAMETER2 DEFAULT_MSG FREEDIAMETER_LIBRARY2 FREEDIAMETER_INCLUDE_DIR)
IF(FREEDIAMETER2_FOUND)
  SET( FREEDIAMETER_LIBRARIES ${FREEDIAMETER_LIBRARIES} ${FREEDIAMETER_LIBRARY2} )
ELSE(FREEDIAMETER2_FOUND)
  SET( FREEDIAMETER_LIBRARIES )
ENDIF(FREEDIAMETER2_FOUND)


# Lastly make it so that the FREEDIAMETER_LIBRARY and FREEDIAMETER_INCLUDE_DIR variables
# only show up under the advanced options in the gui cmake applications.
MARK_AS_ADVANCED( FREEDIAMETER_LIBRARY FREEDIAMETER_INCLUDE_DIR )

# Now check if the library is patched for OPENAIR HSS S6A.
IF(FREEDIAMETER_FOUND)
  IF( FREEDIAMETER_INCLUDE_DIR )
    # Extract FD_PROJECT_VERSION_MAJOR, FD_PROJECT_VERSION_MINOR from freeDiameter-host.h
    # Read the whole file:
    #
    FILE(READ "${FREEDIAMETER_INCLUDE_DIR}/freeDiameter/freeDiameter-host.h" _freeDiameter_HOST_H_CONTENTS)

    STRING(REGEX REPLACE ".*#define FD_PROJECT_VERSION_MAJOR ([0-9]+).*" "\\1" FD_PROJECT_VERSION_MAJOR "${_freeDiameter_HOST_H_CONTENTS}")
    STRING(REGEX REPLACE ".*#define FD_PROJECT_VERSION_MINOR ([0-9]+).*" "\\1" FD_PROJECT_VERSION_MINOR "${_freeDiameter_HOST_H_CONTENTS}")

    IF(FD_PROJECT_VERSION_MAJOR GREATER 0)
      MATH(EXPR FREEDIAMETER_VERSION_VALUE "${FD_PROJECT_VERSION_MAJOR} * 100 + ${FD_PROJECT_VERSION_MINOR} * 10")
      SET(FREEDIAMETER_VERSION "${FREEDIAMETER_VERSION_VALUE}" CACHE INTERNAL "Freediameter release version")
      MESSAGE(STATUS "freeDiameter version found ${FREEDIAMETER_VERSION}")
    ENDIF(FD_PROJECT_VERSION_MAJOR GREATER 0)
  ENDIF( FREEDIAMETER_INCLUDE_DIR )
  GET_FILENAME_COMPONENT(FREEDIAMETER_PATH ${FREEDIAMETER_LIBRARY} PATH)
  IF( NOT( "${FREEDIAMETER_VERSION_TEST_FOR}" STREQUAL "${FREEDIAMETER_LIBRARIES}" ))
    INCLUDE (CheckLibraryExists) 
    MESSAGE(STATUS "Checking freeDiameter patched for S6A")
    UNSET(FREEDIAMETER_HSS_S6A_ENABLED)
    UNSET(FREEDIAMETER_HSS_S6A_ENABLED CACHE)
    UNSET(DICT_S6A_FOUND)
    UNSET(DICT_S6A_FOUND CACHE)


    FIND_FILE(DICT_S6A_FOUND NAMES dict_s6a.fdx PATHS ${FREEDIAMETER_PATH} ${FREEDIAMETER_PATH}/freeDiameter)
    IF(DICT_S6A_FOUND)
        SET( FREEDIAMETER_HSS_S6A_ENABLED TRUE CACHE INTERNAL "dict_s6a.fdx Found")
    ELSE(DICT_S6A_FOUND)
        SET( FREEDIAMETER_HSS_S6A_ENABLED FALSE CACHE INTERNAL "dict_s6a.fdx not Found")
    ENDIF(DICT_S6A_FOUND)
    SET( FREEDIAMETER_VERSION_TEST_FOR ${FREEDIAMETER_LIBRARIES} CACHE INTERNAL "Version the test was made against" )
  ENDIF (NOT( "${FREEDIAMETER_VERSION_TEST_FOR}" STREQUAL "${FREEDIAMETER_LIBRARIES}" ))
ENDIF(FREEDIAMETER_FOUND)

