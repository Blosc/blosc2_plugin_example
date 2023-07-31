/*
  Copyright (C) 2021  The Blosc Developers <blosc@blosc.org>
  https://blosc.org
  License: BSD 3-Clause (see LICENSE.txt)

 */


#include "stdio.h"
#include "string.h"
#include "blosc2.h"
#include "blosc2/filters-registry.h"

#define FILTER_ID 250
#define FILTER_NAME "plugin_example"

#define FORWARD_NAME "blosc2_plugin_example_forward"
#define BACKWARD_NAME "blosc2_plugin_example_backward"


int blosc2_plugin_example_forward(const uint8_t* src, uint8_t* dest, int32_t size, uint8_t meta, blosc2_cparams *cparams,
                           uint8_t id) {
  char* blosc_trace = getenv("BLOSC_TRACE");
  if (blosc_trace != NULL) {
    printf("Inside plugin_example forward function\n");
  }

  blosc2_schunk *schunk = NULL;
  if (cparams != NULL && cparams->schunk != NULL) {
    schunk = cparams->schunk;
  }
  else {
    BLOSC_TRACE_ERROR("Cannot get schunk from cparams");
    return BLOSC2_ERROR_CODEC_PARAM;
  }

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


int blosc2_plugin_example_backward(const uint8_t* src, uint8_t* dest, int32_t size, uint8_t meta, blosc2_dparams *dparams,
                            uint8_t id) {
  char* blosc_trace = getenv("BLOSC_TRACE");
  if (blosc_trace != NULL) {
    printf("Inside plugin_example backward function\n");
  }

  blosc2_schunk *schunk = NULL;
  if (dparams != NULL && dparams->schunk != NULL) {
    schunk = dparams->schunk;
  }
  else {
    BLOSC_TRACE_ERROR("Cannot get schunk from dparams");
    return BLOSC2_ERROR_CODEC_PARAM;
  }

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


filter_info info  = {.forward=FORWARD_NAME, .backward=BACKWARD_NAME};
