# -*- coding: utf-8 -*-
"""
python-ftgl
========

Usage:

    import ftgl
    font = ftgl.FTGLPixmapFont("Arial.ttf")
    font.FaceSize(72)
    font.Render("Hello World!")

"""

import os, sys

from distutils.core import setup, Extension
from distutils.command import build_ext

include_dirs = ["/usr/include", "/usr/include/freetype2"]
libraries = ["ftgl", "boost_python"]
library_dirs = ["/usr/lib"]
sources = []
for (root, dirs, files) in os.walk('src'):
    for name in files:
        if name.endswith(".cpp"):
            sources.append("{}/{}".format(root,name))

ext = Extension(name = "ftgl.__ftgl",
                include_dirs = include_dirs,
                libraries = libraries,
                library_dirs = library_dirs,
                sources = sources,
                extra_compile_args = ["-std=c++11"])

# ccache
for path in os.environ["PATH"].split(os.pathsep):
    path = path.strip('"')
    exe = os.path.join(path, "ccache")
    if os.path.isfile(exe) and os.access(exe, os.X_OK):
        os.environ["CC"] = "ccache gcc"
        break

setup(name = "python-ftgl",
      long_description = __doc__,
      version = "0.1.0",
      description = "python-ftgl: Python FTGL binding",
      author = "mugwort_rc",
      author_email = "mugwort rc at gmail com",
      url = "https://github.com/mugwort-rc/python-ftgl",
      classifiers = [
        "Development Status :: 4 - Beta",
        "Intended Audience :: Developers",
        "License :: OSI Approved :: MIT License",
        "Programming Language :: C++",
        "Programming Language :: Python",
        "Programming Language :: Python :: 2.7",
      ],
      license = "MIT License",
      packages = ["ftgl"],

      ext_modules = [ext])

