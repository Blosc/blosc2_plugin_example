# Blosc - Blocked Shuffling and Compression Library
#
# Copyright (C) 2021  The Blosc Developers <blosc@blosc.org>
# https://blosc.org
# License: BSD 3-Clause (see LICENSE.txt)
#
# See LICENSE.txt for details about copyright and rights to use.

cmake_minimum_required(VERSION 3.20)
project(blosc2_plugin_example LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)

message("Building Blosc2 plugin example...")
include(FindPackageHandleStandardArgs)

find_path(BLOSC2_INCLUDE_DIR blosc2.h HINTS /)
find_library(BLOSC2_LIBRARY blosc2 HINTS /)

find_package_handle_standard_args(BLOSC2
 DEFAULT_MSG
  BLOSC2_INCLUDE_DIR
  BLOSC2_LIBRARY
)

mark_as_advanced(BLOSC2_LIBRARY BLOSC2_INCLUDE_DIR)

if(BLOSC2_FOUND)
  set(BLOSC2_LIBRARIES    ${BLOSC2_LIBRARY})
  set(BLOSC2_INCLUDE_DIRS ${BLOSC2_INCLUDE_DIR})
endif()

# Find blosc2.h
find_package(Python COMPONENTS Interpreter)
if(Python_Interpreter_FOUND)
    message(STATUS "Executable: ${Python_EXECUTABLE}")

    cmake_path(SET SitePACKAGES NORMALIZE "${Python3_NumPy_INCLUDE_DIRS}/../../../../../..")
    message(STATUS "Site-packages: ${SitePACKAGES}")
    message(STATUS "STDLIB: ${Python_STDLIB}")
    message(STATUS "SITELIB: ${Python_SITELIB}")
    message(STATUS "STDARCH: ${Python_STDARCH}")
    message(STATUS "Python_INCLUDE_DIR: ${Python_INCLUDE_DIR}")
    message(STATUS "Python_INCLUDE_DIRS: ${Python_INCLUDE_DIRS}")
    message(STATUS "Python_LIBRARY_DIRS: ${Python_LIBRARY_DIRS}")

    find_library(BLOSC2_LIB NAMES blosc2 PATHS ${SitePACKAGES})
    message(STATUS "BLOSC2_LIB: ${BLOSC2_LIB}")
    find_path(BLOSC2_INCLUDE_DIR NAMES blosc2.h PATHS ${SitePACKAGES})
    message(STATUS "BLOSC2_INCLUDE_DIR: ${BLOSC2_INCLUDE_DIR}")
    cmake_path(SET Python_ROOT NORMALIZE "${Python_EXECUTABLE}/../..")
    cmake_path(SET Python_INCLUDE NORMALIZE "${SitePACKAGES}/include")
    message(STATUS "Found Python include: ${Python_INCLUDE}")
    cmake_path(SET Python_LIB NORMALIZE "${Python_ROOT}/lib")
    message(STATUS "Found Python lib: ${Python_LIB}")
    cmake_path(SET Python_LIB64 NORMALIZE "${Python_ROOT}/lib64")
    message(STATUS "Found Python lib64: ${Python_LIB64}")
    cmake_path(SET Python_Blosc2_INCLUDE NORMALIZE "${SitePACKAGES}/include/blosc2.h")
    cmake_path(HAS_FILENAME Python_Blosc2_INCLUDE HAS_BLOSC2)
    if(HAS_BLOSC2)
        set(BLOSC2_INCLUDE_DIR ${Python_INCLUDE})
        message(STATUS "Found Blosc2 include: ${Python_Blosc2_INCLUDE}")
    else()
        message(FATAL_ERROR "No Blosc2 includes found.  Aborting.")
    endif()
else()
    message(FATAL_ERROR "No Python found.  Aborting.")
endif()

include_directories("${BLOSC2_INCLUDE_DIR}")
add_subdirectory(src)
