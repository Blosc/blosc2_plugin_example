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

find_package(PythonExtensions REQUIRED)

add_library(plugin-c111 MODULE src/urfilters.c)
python_extension_module(plugin-c111)

install(TARGETS plugin-c111 LIBRARY DESTINATION plugin_example)
