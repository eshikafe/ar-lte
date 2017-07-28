

#from distutils.core import setup
#from Cython.Build import cythonize

from setuptools import setup
from setuptools import Extension
from Cython.Build import cythonize

setup(
    ext_modules = cythonize("lib/ts/ts36211_lte_phy_channels_modulation.pyx")
)

# python setup.py build_ext --inplace
