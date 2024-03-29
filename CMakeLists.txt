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

# Find blosc2.h
find_package(Python COMPONENTS Interpreter NumPy Development.Module REQUIRED)
message(STATUS "Executable: ${Python_EXECUTABLE}")
message(STATUS "NumPy found: ${Python_NumPy_FOUND}")
message(STATUS "NumPy version: ${Python_NumPy_VERSION}")
message(STATUS "Python_NumPy_INCLUDE_DIRS: ${Python_NumPy_INCLUDE_DIRS}")
if (UNIX)
    cmake_path(SET Python_ROOT NORMALIZE "${Python_NumPy_INCLUDE_DIRS}/../../../../../..")
else()
    cmake_path(SET Python_ROOT NORMALIZE "${Python_NumPy_INCLUDE_DIRS}/../../../../..")
endif()
cmake_path(SET Python_INCLUDE NORMALIZE "${Python_ROOT}/include")
message(STATUS "Found Python include: ${Python_INCLUDE}")
cmake_path(SET Python_Blosc2_INCLUDE NORMALIZE "${Python_ROOT}/include/blosc2.h")
cmake_path(HAS_FILENAME Python_Blosc2_INCLUDE HAS_BLOSC2)
if(HAS_BLOSC2)
    set(BLOSC2_INCLUDE_DIR ${Python_INCLUDE})
    message(STATUS "Found Blosc2 include: ${Python_Blosc2_INCLUDE}")
else()
    message(FATAL_ERROR "No Blosc2 includes found.  Aborting.")
endif()

include_directories("${BLOSC2_INCLUDE_DIR}")
add_subdirectory(src)
