# ADOL-C

# first try to find it with PkgConfig
find_package(PkgConfig REQUIRED)

pkg_check_modules(ADOLC QUIET adolc)

if (ADOLC_FOUND)
  message(STATUS "ADOL-C found: ${ADOLC_PREFIX}")
  set(3RDPARTY_ADOLC_DIR ${ADOLC_PREFIX} CACHE PATH "The directory containing ADOL-C" FORCE)
  set(3RDPARTY_ADOLC_INCLUDE_DIR ${ADOLC_INCLUDE_DIRS} CACHE PATH "The directory containing headers of ADOL-C" FORCE)
  set(3RDPARTY_ADOLC_LIBRARY_DIR ${ADOLC_LIBRARY_DIRS} CACHE PATH "The directory containing ADOL-C library" FORCE)
endif ()

# ADOL-C directory
if (NOT DEFINED 3RDPARTY_ADOLC_DIR)
  set (3RDPARTY_ADOLC_DIR "" CACHE PATH "The directory containing ADOL-C")
endif ()

# ADOL-C include directory
if (NOT DEFINED 3RDPARTY_ADOLC_INCLUDE_DIR OR NOT EXISTS ${3RDPARTY_ADOLC_INCLUDE_DIR})
  find_path(
          3RDPARTY_ADOLC_INCLUDE_DIR
          NAMES "adolc/adtl.h"
          PATHS "${3RDPARTY_ADOLC_DIR}/include" NO_DEFAULT_PATH
          DOC "The directory containing headers of ADOL-C"
  )
endif ()

# ADOL-C shared library
if (NOT DEFINED 3RDPARTY_ADOLC_LIBRARY OR NOT EXISTS ${3RDPARTY_ADOLC_LIBRARY})
  find_library(
          3RDPARTY_ADOLC_LIBRARY
          NAMES "adolc"
          PATHS "${3RDPARTY_ADOLC_DIR}" NO_DEFAULT_PATH
          PATH_SUFFIXES "lib" "lib64"
          DOC "ADOL-C library"
  )
endif ()

# ADOL-C shared library directory, extracted from the variable 3RDPARTY_ADOLC_LIBRARY
if (NOT DEFINED 3RDPARTY_ADOLC_LIBRARY_DIR OR NOT EXISTS ${3RDPARTY_ADOLC_LIBRARY_DIR})
  cmake_path(GET 3RDPARTY_ADOLC_LIBRARY PARENT_PATH 3RDPARTY_ADOLC_LIBRARY_PARENT_PATH)
  set (3RDPARTY_ADOLC_LIBRARY_DIR ${3RDPARTY_ADOLC_LIBRARY_PARENT_PATH} CACHE PATH "The directory containing ADOL-C library" FORCE)
endif ()

# include occt macros. compiler_bitness, os_wiht_bit, compiler
#OCCT_INCLUDE_CMAKE_FILE ("adm/cmake/occt_macros")
#OCCT_MAKE_COMPILER_BITNESS()
#OCCT_MAKE_COMPILER_SHORT_NAME()

# ADOL-C shared library (with absolute path)
#if (WIN32)
#  if (NOT DEFINED 3RDPARTY_ADOLC_DLL OR NOT 3RDPARTY_ADOLC_DLL_DIR)
#    set (3RDPARTY_ADOLC_DLL "" CACHE FILEPATH "ADOL-C shared library" FORCE)
#  endif()
#endif()

# ADOL-C shared library directory
#if (WIN32 AND NOT DEFINED 3RDPARTY_ADOLC_DLL_DIR)
#  set (3RDPARTY_ADOLC_DLL_DIR "" CACHE FILEPATH "The directory containing ADOL-C shared library")
#endif()


# include found paths to common variables
if (3RDPARTY_ADOLC_INCLUDE_DIR AND EXISTS "${3RDPARTY_ADOLC_INCLUDE_DIR}")
  list (APPEND 3RDPARTY_INCLUDE_DIRS "${3RDPARTY_ADOLC_INCLUDE_DIR}")
else()
  list (APPEND 3RDPARTY_NOT_INCLUDED 3RDPARTY_ADOLC_INCLUDE_DIR)
endif()

if (3RDPARTY_ADOLC_LIBRARY AND EXISTS "${3RDPARTY_ADOLC_LIBRARY}")
  list (APPEND 3RDPARTY_LIBRARY_DIRS "${3RDPARTY_ADOLC_LIBRARY_DIR}")
else()
  list (APPEND 3RDPARTY_NOT_INCLUDED 3RDPARTY_ADOLC_LIBRARY_DIR)
endif()

# optionally, include Boost
# BOOST directory that was previously used to build ADOL-C (optional)
if (NOT DEFINED 3RDPARTY_BOOST_DIR)
  set (3RDPARTY_BOOST_DIR "" CACHE PATH "The directory containing Boost used for ADOL-C (optional)")
endif()

find_path(
  3RDPARTY_BOOST_INCLUDE_DIR 
  NAMES "boost/pool/pool_alloc.hpp" 
  PATHS "${3RDPARTY_BOOST_DIR}/include" NO_DEFAULT_PATH 
  DOC "Boost include directory used by ADOL-C (Optional)"
)
if(${3RDPARTY_BOOST_INCLUDE_DIR} STREQUAL "3RDPARTY_BOOST_INCLUDE_DIR-NOTFOUND")
  message(STATUS "Info: Boost include directory not found (optional). To include it, specify 3RDPARTY_BOOST_DIR.")
else()
  message(STATUS "Info: Boost (for ADOL-C) found and is included.")
  list (APPEND 3RDPARTY_INCLUDE_DIRS "${3RDPARTY_BOOST_INCLUDE_DIR}")
endif()

#if (WIN32)
#  if (3RDPARTY_ADOLC_DLL OR EXISTS "${3RDPARTY_ADOLC_DLL}")
#    list (APPEND 3RDPARTY_DLL_DIRS "${3RDPARTY_ADOLC_DLL_DIR}")
#  else()
#    list (APPEND 3RDPARTY_NOT_INCLUDED 3RDPARTY_ADOLC_DLL_DIR)
#  endif()
#endif()

# the library directory for using by the executable
#if (WIN32)
#  set (USED_3RDPARTY_ADOLC_DIR ${3RDPARTY_ADOLC_DLL_DIR})
#else()
  set (USED_3RDPARTY_ADOLC_DIR ${3RDPARTY_ADOLC_LIBRARY_DIR})
#endif()

#mark_as_advanced (3RDPARTY_ADOLC_LIBRARY 3RDPARTY_ADOLC_DLL)
mark_as_advanced (3RDPARTY_ADOLC_LIBRARY)

