/*
  Copyright (C) 2021  The Blosc Developers <blosc@blosc.org>
  https://blosc.org
  License: BSD 3-Clause (see LICENSE.txt)

 */


#include "stdio.h"
#include "string.h"
#include "blosc2.h"

#define FILTER_ID 250
#define FILTER_NAME "plugin_example"


int plugin_example_forward(const uint8_t* src, uint8_t* dest, int32_t size, uint8_t meta, blosc2_cparams *cparams,
                           uint8_t id) {
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


int plugin_example_backward(const uint8_t* src, uint8_t* dest, int32_t size, uint8_t meta, blosc2_dparams *dparams,
                            uint8_t id) {
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


void check_filter(blosc2_filter *filter) {
  if (filter->id != FILTER_ID) {
    BLOSC_TRACE_ERROR("Wrong library for filter with expected id %d, found %d", FILTER_ID, filter->id);
    return;
  }
  /* Uncomment this when Blosc2 version includes name field in filters
  if (strcmp(filter->name, FILTER_NAME) != 0) {
    BLOSC_TRACE_ERROR("Wrong library for filter with expected name %s, found %s", FILTER_NAME, filter->name);
    return;
  }
  */
}
