# Blosc - Blocked Shuffling and Compression Library
#
# Copyright (C) 2021  The Blosc Developers <blosc@blosc.org>
# https://blosc.org
# License: BSD 3-Clause (see LICENSE.txt)
#
# See LICENSE.txt for details about copyright and rights to use.

from skbuild import setup

setup(
    name="plugin_example",
    packages=["plugin_example"],
    package_dir={"plugin_example": "plugin_example"},
)
