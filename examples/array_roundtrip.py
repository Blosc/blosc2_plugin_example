#######################################################################
# Copyright (c) 2019-present, Blosc Development Team <blosc@blosc.org>
# All rights reserved.
#
# This source code is licensed under a BSD-style license (found in the
# LICENSE file in the root directory of this source tree)
#######################################################################


import blosc2
import numpy as np


# Register the plugin_example
blosc2.register_filter(250, None, None, "plugin_example")

# Create blosc2 NDArray from a NumPy array
shape = [100, 100]
size = int(np.prod(shape))
nparray = np.arange(size, dtype=np.int32).reshape(shape)
blosc2_array = blosc2.asarray(nparray, cparams={"filters": [250]})

# Retrieve data and check it is the same
if np.array_equal(blosc2_array[...], nparray):
    print("Successful roundtrip!")
else:
    print("Bad roundtrip! Try setting BLOSC_TRACE=1 envvar for more info on failure.")
