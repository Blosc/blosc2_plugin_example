/*
  Copyright (C) 2021  The Blosc Developers <blosc@blosc.org>
  https://blosc.org
  License: BSD 3-Clause (see LICENSE.txt)

   Example program demonstrating use of the Blosc filter from C code.

  To compile this program:

  $ gcc urfilters.c -o urfilters -lblosc2

  To run:

  $ ./urfilters

 */


#include "stdio.h"
#include "blosc2.h"

enum {
    FILTER_ID = 250,
};



int filter_forward(const uint8_t* src, uint8_t* dest, int32_t size, uint8_t meta, blosc2_cparams *cparams,
                   uint8_t id) {
  //BLOSC_UNUSED_PARAM(meta);
  //BLOSC_UNUSED_PARAM(id);
  if (id != FILTER_ID) {
    printf("ie subnormal, què fas?");
    return BLOSC2_ERROR_FAILURE;
  }
  blosc2_schunk *schunk = cparams->schunk;

  for (int i = 0; i < size / schunk->typesize; ++i) {
    switch (schunk->typesize) {
      case 8:
        ((int64_t *) dest)[i] = ((int64_t *) src)[i] + 1;
        break;
      case 4:
        ((int32_t *) dest)[i] = ((int32_t *) src)[i] + 1;
        break;
      case 2:
        ((int16_t *) dest)[ i] = (int16_t)(((int16_t *) src)[i] + 1);
        break;
      default:
        BLOSC_TRACE_ERROR("Item size %d not supported", schunk->typesize);
        return BLOSC2_ERROR_FAILURE;
    }
  }
  return BLOSC2_ERROR_SUCCESS;
}


int filter_backward(const uint8_t* src, uint8_t* dest, int32_t size, uint8_t meta, blosc2_dparams *dparams,
                    uint8_t id) {
  //BLOSC_UNUSED_PARAM(meta);
  //BLOSC_UNUSED_PARAM(id);
  if (id != FILTER_ID) {
    printf("ie subnormal, què fas? xa, perlamordedeu");
    return BLOSC2_ERROR_FAILURE;
  }
  blosc2_schunk *schunk = dparams->schunk;

  for (int i = 0; i < size / schunk->typesize; ++i) {
    switch (schunk->typesize) {
      case 8:
        ((int64_t *) dest)[i] = ((int64_t *) src)[i] - 1;
        break;
      case 4:
        ((int32_t *) dest)[i] = ((int32_t *) src)[i] - 1;
        break;
      case 2:
        ((int16_t *) dest)[i] = (int16_t)(((int16_t *) src)[i] - 1);
        break;
      default:
        BLOSC_TRACE_ERROR("Item size %d not supported", schunk->typesize);
        return BLOSC2_ERROR_FAILURE;
    }
  }
  return BLOSC2_ERROR_SUCCESS;
}

blosc2_filter filter = {.id=FILTER_ID, .forward=filter_forward, .backward=filter_backward};
