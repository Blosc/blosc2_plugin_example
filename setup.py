# from setuptools import setup
from skbuild import setup


setup(
    name="plugin_example",
    packages=["plugin_example"],
    package_dir={"plugin_example": "plugin_example"},
)


if __name__ == "__main__":
    setup()
