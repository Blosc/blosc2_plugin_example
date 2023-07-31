# Plugin example

This is an example on how to create a wheel of a plugin for Blosc2.

## Create the wheel

```shell
python setup.py bdist_wheel
```

## Verify the wheel is working

```shell
pip install dist/blosc2_plugin_example-*.whl
```

And then simulate that you are going to uninstall.  You will be presented where the plugin has been installed:

```shell
pip uninstall blosc2_plugin_example
```

For example, the shared library should appear somewhere like:

```shell
ls -l /Users/faltet/miniconda3/lib/python3.9/site-packages/blosc2_plugin_example
total 112
-rw-r--r--  1 faltet  staff   258B Mar  6 13:45 __init__.py
drwxr-xr-x  3 faltet  staff    96B Mar  6 13:45 __pycache__/
-rwxr-xr-x  1 faltet  staff    48K Mar  6 13:45 libblosc2_plugin_example.so*
```

To test that the wheel has been installed and works properly.

```shell
cd _skbuild/*/cmake-build/examples/
./test_plugin
Blosc version info: 2.10.0 ($Date:: 2023-07-04 #$)
Compression ratio: 381.5 MB -> 2.9 MB (130.8x)
Compression time: 0.265 s, 1437.0 MB/s
Decompression time: 0.152 s, 2506.6 MB/s
Successful roundtrip data <-> schunk !
```
If you created the wheel with cibuildwheel use 
`DYLD_LIBRARY_PATH=/Users/martaiborra/miniforge3/envs/plugin_example_arm64/lib/`
on Mac or `LD_LIBRARY_PATH=/Users/martaiborra/miniforge3/envs/plugin_example_arm64/lib/`
on linux.

If you want to see that the plugin example filter its being applied
instead of any other use `BLOSC_TRACE=1`.

```shell
BLOSC_TRACE=1 ./test_plugin
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
```

In the future, you should be able to test that the wheel is working with this command:

```shell
blosc2_test_plugin plugin_example_name
```

That's all folks!
