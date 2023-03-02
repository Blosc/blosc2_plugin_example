# Blosc - Blocked Shuffling and Compression Library
#
# Copyright (C) 2021  The Blosc Developers <blosc@blosc.org>
# https://blosc.org
# License: BSD 3-Clause (see LICENSE.txt)
#
# See LICENSE.txt for details about copyright and rights to use.

cmake_minimum_required(VERSION 3.20)

project(plugin_example LANGUAGES C CXX)

message("Building plugin example")

# find_package(PythonExtensions REQUIRED)

# Find blosc2.h. First in the Python environment (via python-blosc2 wheel).
find_package (Python COMPONENTS Interpreter)
if(Python_Interpreter_FOUND)
    message(STATUS "Found Python stdlib: ${Python_STDLIB}")
    cmake_path(SET Python_INCLUDE NORMALIZE "${Python_STDLIB}/../../include")
    message(STATUS "Found Python include: ${Python_INCLUDE}")
    cmake_path(SET Python_BLOSC2H NORMALIZE "${Python_INCLUDE}/blosc2.h")
    cmake_path(HAS_FILENAME Python_BLOSC2H HAS_BLOSC2)
    if(HAS_BLOSC2)
        set(BLOSC2_INCLUDE_DIR ${Python_INCLUDE})
        message(STATUS "Found BLOSC2 include (Python dir): ${BLOSC2_INCLUDE_DIR}")
    else()
        # Then try to find blosc2.h in the system
        find_path(BLOSC2_INCLUDE_DIR blosc2.h)
        if(BLOSC2_INCLUDE_DIR)
            message(STATUS "Found BLOSC2 include (system dir): ${BLOSC2_INCLUDE_DIR}")
        else()
            message(FATAL_ERROR "No BLOSC2 includes found.  Aborting.")
        endif()
    endif()
else()
    message(FATAL_ERROR "No Python found.  Aborting.")
endif()


add_library(plugin-c111 MODULE src/urfilters.c)
target_include_directories(plugin-c111 PUBLIC "${BLOSC2_INCLUDE_DIR}")
# python_extension_module(plugin-c111)

install(TARGETS plugin-c111 LIBRARY DESTINATION plugin_example)
