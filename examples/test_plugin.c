/*
  Copyright (C) 2021  The Blosc Developers <blosc@blosc.org>
  https://blosc.org
  License: BSD 3-Clause (see LICENSE.txt)

   Example program to test the plugin.
   Since it won't be registered yet as a filter/codec in Blosc2, it will
   be registered as user-defined. So it's id must be between 160-255.

   To compile and run this test:
   cd examples
   gcc test_plugin.c -o test_plugin -I /Users/martaiborra/miniforge3/envs/plugin_example_arm64/include \
   -L /Users/martaiborra/miniforge3/envs/plugin_example_arm64/lib -lblosc2
   # For MacOS
   DYLD_LIBRARY_PATH=/Users/martaiborra/miniforge3/envs/plugin_example_arm64/lib/ ./test_plugin
   # For linux
   LD_LIBRARY_PATH=path_to_blosc2_lib ./test_plugin

   To check that it is actually running the defined filter you can use BLOSC_TRACE=1.
   BLOSC_TRACE=1 LD_LIBRARY_PATH=path_to_blosc2_lib ./test_plugin

   Expected output:
    Blosc version info: 2.10.0 ($Date:: 2023-07-04 #$)
    Compression ratio: 381.5 MB -> 2.9 MB (130.8x)
    Compression time: 0.265 s, 1437.0 MB/s
    Decompression time: 0.152 s, 2506.6 MB/s
    Successful roundtrip data <-> schunk !

   Expected output with BLOSC_TRACE=1:
    Blosc version info: 2.10.0 ($Date:: 2023-07-04 #$)
    [info] - libpath for plugin blosc2_plugin_example: /Users/martaiborra/miniconda3/envs/plugin_example/lib/python3.11/site-packages/blosc2_plugin_example/libblosc2_plugin_example.so
     (/Users/runner/work/python-blosc2/python-blosc2/blosc2/c-blosc2/blosc/blosc-private.h:265)
    Inside plugin_example forward function
              ...
    Compression ratio: 381.5 MB -> 2.9 MB (130.8x)
    Compression time: 0.25 s, 1523.0 MB/s
    Inside plugin_example backward function
              ...
    Decompression time: 0.156 s, 2444.7 MB/s
    Inside plugin_example backward function
              ...
    Successful roundtrip data <-> schunk !
 */


#include "stdio.h"
#include "blosc2.h"

#define KB  1024.
#define MB  (1024*KB)
#define GB  (1024*MB)

#define CHUNKSIZE (1000 * 1000)
#define NCHUNKS 100
#define NTHREADS 4


int main(void) {
  static int32_t data[CHUNKSIZE];
  static int32_t data_dest[CHUNKSIZE];
  int32_t isize = CHUNKSIZE * sizeof(int32_t);
  int dsize;
  int64_t nbytes, cbytes;

  blosc2_init();

  // Only need to register the filter in case the plugin is not registered in Blosc2
  blosc2_filter urfilter;
  urfilter.id = 250;
  urfilter.name = "plugin_example";
  urfilter.version = 1;
  urfilter.forward = NULL;
  urfilter.backward = NULL;
  blosc2_register_filter(&urfilter);

  blosc2_cparams cparams = BLOSC2_CPARAMS_DEFAULTS;
  cparams.filters[4] = 250;
  cparams.filters_meta[4] = 0;

  blosc2_dparams dparams = BLOSC2_DPARAMS_DEFAULTS;

  blosc2_schunk* schunk;
  int i, nchunk;
  blosc_timestamp_t last, current;
  double ttotal;

  printf("Blosc version info: %s (%s)\n", blosc2_get_version_string(), BLOSC2_VERSION_DATE);

  /* Create a super-chunk container */
  cparams.typesize = sizeof(int32_t);
  cparams.clevel = 9;
  blosc2_storage storage = {.cparams=&cparams, .dparams=&dparams};
  schunk = blosc2_schunk_new(&storage);
  if (schunk == NULL) {
    printf("Could not create schunk");
    return -1;
  }

  blosc_set_timestamp(&last);
  for (nchunk = 0; nchunk < NCHUNKS; nchunk++) {
    for (i = 0; i < CHUNKSIZE; i++) {
      data[i] = i * nchunk;
    }
    int64_t nchunks = blosc2_schunk_append_buffer(schunk, data, isize);
    if (nchunks != nchunk + 1) {
      printf("Unexpected nchunks!");
      return -1;
    }
  }
  /* Gather some info */
  nbytes = schunk->nbytes;
  cbytes = schunk->cbytes;
  blosc_set_timestamp(&current);
  ttotal = blosc_elapsed_secs(last, current);
  printf("Compression ratio: %.1f MB -> %.1f MB (%.1fx)\n",
         (double)nbytes / MB, (double)cbytes / MB, (1. * (double)nbytes) / (double)cbytes);
  printf("Compression time: %.3g s, %.1f MB/s\n",
         ttotal, (double)nbytes / (ttotal * MB));

  /* Retrieve and decompress the chunks (0-based count) */
  blosc_set_timestamp(&last);
  for (nchunk = NCHUNKS-1; nchunk >= 0; nchunk--) {
    dsize = blosc2_schunk_decompress_chunk(schunk, nchunk, data_dest, isize);
    if (dsize < 0) {
      printf("Decompression error.  Error code: %d\n", dsize);
      return dsize;
    }
  }
  blosc_set_timestamp(&current);
  ttotal = blosc_elapsed_secs(last, current);
  printf("Decompression time: %.3g s, %.1f MB/s\n",
         ttotal, (double)nbytes / (ttotal * MB));

  /* Check integrity of the second chunk (made of non-zeros) */
  blosc2_schunk_decompress_chunk(schunk, 1, data_dest, isize);
  for (i = 0; i < CHUNKSIZE; i++) {
    if (data_dest[i] != i) {
      printf("Decompressed data differs from original %d, %d!\n",
             i, data_dest[i]);
      return -1;
    }
  }

  printf("Successful roundtrip data <-> schunk !\n");

  /* Free resources */
  /* Destroy the super-chunk */
  blosc2_schunk_free(schunk);
  blosc2_destroy();

  return 0;
}
