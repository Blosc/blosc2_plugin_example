/*********************************************************************
  Blosc - Blocked Shuffling and Compression Library

  Copyright (c) 2021  The Blosc Development Team <blosc@blosc.org>
  https://blosc.org
  License: BSD 3-Clause (see LICENSE.txt)

**********************************************************************/

/*********************************************************************
  @file urfilters.h
  @brief Blosc2 plugin example header file.

  This file contains the two functions and defined filter info needed
  to use the blosc2_plugin_example from Blosc2.
  @author The Blosc Development Team <blosc@blosc.org>
**********************************************************************/

#ifndef URFILTERS_H
#define URFILTERS_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "blosc2.h"


// Needed for correctly exporting the functions and symbols for Windows
#if defined(_MSC_VER)
#define EXAMPLE_EXPORT __declspec(dllexport)
#elif (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
#if defined(_WIN32) || defined(__CYGWIN__) || defined(__MINGW32__)
  #define EXAMPLE_EXPORT __attribute__((dllexport))
#else
  #define EXAMPLE_EXPORT __attribute__((visibility("default")))
#endif  /* defined(_WIN32) || defined(__CYGWIN__) */
#else
#error Cannot determine how to define EXAMPLE_EXPORT for this compiler.
#endif

#ifdef __cplusplus
extern "C" {
#endif


EXAMPLE_EXPORT int blosc2_plugin_example_forward(const uint8_t* src, uint8_t* dest, int32_t size, uint8_t meta,
                                                blosc2_cparams *cparams, uint8_t id);
EXAMPLE_EXPORT int blosc2_plugin_example_backward(const uint8_t* src, uint8_t* dest, int32_t size, uint8_t meta,
                                                  blosc2_dparams *dparams, uint8_t id);
EXAMPLE_EXPORT filter_info info = {"blosc2_plugin_example_forward", "blosc2_plugin_example_backward"};

#ifdef __cplusplus
}
#endif

#endif /* BLOSC_BLOSC2_H */
