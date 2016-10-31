

#from distutils.core import setup
#from Cython.Build import cythonize

from setuptools import setup
from setuptools import Extension
from Cython.Build import cythonize

setup(
    ext_modules = cythonize("ts36323_lte_pdcp.pyx")
)
