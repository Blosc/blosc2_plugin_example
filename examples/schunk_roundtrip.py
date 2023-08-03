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

# Set the compression and decompression parameters
storage = {"contiguous": True, "cparams": {"filters": [250], "typesize": 4}}

# Create the SChunk
nchunks = 10
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
