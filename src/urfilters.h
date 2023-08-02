/*********************************************************************
  Blosc - Blocked Shuffling and Compression Library

  Copyright (c) 2021  The Blosc Development Team <blosc@blosc.org>
  https://blosc.org
  License: BSD 3-Clause (see LICENSE.txt)

  See LICENSE.txt for details about copyright and rights to use.
**********************************************************************/

/*********************************************************************
  @file blosc2.h
  @brief Blosc2 header file.

  This file contains Blosc2 public API and the structures needed to use it.
  @author The Blosc Development Team <blosc@blosc.org>
**********************************************************************/

#ifndef URFILTERS_H
#define URFILTERS_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "blosc2.h"


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


/*#if defined(__GNUC__) || defined(__clang__)
  #define BLOSC_NO_EXPORT __attribute__((visibility("hidden")))
#else
  #define BLOSC_NO_EXPORT
#endif */ /* defined(__GNUC__) || defined(__clang__) */


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the Blosc library environment.
 *
 * You must call this previous to any other Blosc call, unless you want
 * Blosc to be used simultaneously in a multi-threaded environment, in
 * which case you can use the #blosc2_compress_ctx #blosc2_decompress_ctx pair.
 *
 * @sa #blosc2_destroy
 */
EXAMPLE_EXPORT int blosc2_plugin_example_forward(const uint8_t* src, uint8_t* dest, int32_t size, uint8_t meta,
            blosc2_cparams *cparams, uint8_t id);


/**
 * @brief Destroy the Blosc library environment.
 *
 * You must call this after to you are done with all the Blosc calls,
 * unless you have not used blosc2_init() before.
 *
 * @sa #blosc2_init
 */
EXAMPLE_EXPORT int blosc2_plugin_example_backward(const uint8_t* src, uint8_t* dest, int32_t size, uint8_t meta, blosc2_dparams *dparams,
                            uint8_t id);


/**
 * @brief Default struct for decompression params meant for user initialization.
 */
EXAMPLE_EXPORT filter_info info = {"blosc2_plugin_example_forward", "blosc2_plugin_example_backward"};

#ifdef __cplusplus
}
#endif

#endif /* BLOSC_BLOSC2_H */
