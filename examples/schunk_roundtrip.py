#######################################################################
# Copyright (c) 2019-present, Blosc Development Team <blosc@blosc.org>
# All rights reserved.
#
# This source code is licensed under a BSD-style license (found in the
# LICENSE file in the root directory of this source tree)
#######################################################################

import numpy as np

import blosc2

blosc2.register_filter(250, None, None, "plugin_example")
nchunks = 10
# Set the compression and decompression parameters
cparams = {"filters": [250], "filters_meta": [0], "typesize": 4, "nthreads": 1}
dparams = {"nthreads": 1}
contiguous = True

storage = {"contiguous": contiguous, "cparams": cparams, "dparams": dparams}

# Create the SChunk
data = np.arange(200 * 1000 * nchunks, dtype=np.int32)
schunk = blosc2.SChunk(chunksize=200 * 1000 * 4, data=data, **storage)

cframe = schunk.to_cframe()

schunk2 = blosc2.schunk_from_cframe(cframe, False)
data2 = np.empty(data.shape, dtype=data.dtype)
schunk2.get_slice(out=data2)
if np.array_equal(data, data2):
    print("Successful roundtrip!")
else:
    print("Bad roundtrip! Try setting BLOSC_TRACE=1 envvar for more info on failure.")
