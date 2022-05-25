# scangler - Sauvola binarization of images

Copyright 2012, 2022 Eric Smith <spacewar@gmail.com>

SPDX-License-Identifier: GPL-3.0-only

scangler development is hosted at the
[scangler Github repository](https://github.com/brouhaha/scangler/).

## Introduction

In 2012 I spent some time investigating binarization algorithms, which
convert a gray-scale image into a bilevel (strictly black and white)
image. I wrote this program to evaluate the Sauvola algorithm, and allow
experimentation with its paramters. The binarize-gui program loads an image,
displays the original image and the binarized image, and has sliders for the
Suavola algorithm's window size and k parameters.

## Building from source

The program requires Qt 6, which requires C++ 17. It has been tested
with the GCC 11.2.1 compiler and Qt 6.2.3.

Make sure `qmake` is the right executable for use with qt6. It's possible
that the qt6 qmake might be installed under another name, e.g. on systems
that allow parallel installation of multiple major versions of qmake. If
necessary, substitute the correct name or path for Qt6 qmake in the command
listed below.

To build:

- `cd src`
- `qmake`
- `make`

The resulting executable is named scangler.
