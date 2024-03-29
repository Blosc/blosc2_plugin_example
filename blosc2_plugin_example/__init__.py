# Blosc - Blocked Shuffling and Compression Library
#
# Copyright (C) 2021  The Blosc Developers <blosc@blosc.org>
# https://blosc.org
# License: BSD 3-Clause (see LICENSE.txt)
#
# See LICENSE.txt for details about copyright and rights to use.


import os
import platform
from pathlib import Path


def print_libpath():
    system = platform.system()
    if system in ["Linux", "Darwin"]:
        libname = "libblosc2_plugin_example.so"
    elif system == "Windows":
        libname = "blosc2_plugin_example.dll"
    else:
        raise RuntimeError("Unsupported system: ", system)
    libpath = os.path.abspath(Path(__file__).parent / libname)
    print(libpath, end="")


if __name__ == "__main__":
    print_libpath()
