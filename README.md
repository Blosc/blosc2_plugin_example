# Plugin example

This is an example on how to create a wheel of a plugin for Blosc2.

## Create the wheel

### For Linux

```shell
python -m cibuildwheel --only 'cp311-manylinux_x86_64'
```

### For Mac

```shell
python -m cibuildwheel --only 'cp311-macosx_x86_64'
```

### For Windows

```shell
python -m cibuildwheel --only 'cp311-win_amd64'
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
cd examples/
python schunk_roundtrip.py
Successful roundtrip!
```

If you want to see that the plugin example filter its being applied
instead of any other use `BLOSC_TRACE=1`.

There is also a C example that can be compiled and run following the instructions in its `test_plugin.c` 
file.

In the future, you should be able to test that the wheel is working with this command:

```shell
blosc2_test_plugin plugin_example_name
```

That's all folks!
