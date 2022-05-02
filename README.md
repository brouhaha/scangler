# binarize - Sauvola binarization of images

Copyright 2012, 2022 Eric Smith <spacewar@gmail.com>

SPDX-License-Identifier: GPL-3.0-only

binarize development is hosted at the
[binarize Github repository](https://github.com/brouhaha/binarize/).

## Introduction

In 2012 I spent some time investigating binarization algorithms, which
convert a gray-scale image into a bilevel (strictly black and white)
image. I wrote this program to evaluate the Sauvola algorithm, and allow
experimentation with its paramters. The binarize-gui program loads an image,
displays the original image and the binarized image, and has sliders for the
Suavola algorithm's window size and k parameters.

At the time, this was the first C++ program I'd written since an employer
sent me to C++ training in 1990, and the first program I'd written using
Qt.

## Building from source

The program requires Qt 6, and has been tested with Qt 6.2.3.

Make sure `qmake` is the right executable for use with qt6. It's possible
that the qt6 qmake might be installed under another name, e.g. on systems
that allow parallel installation of multiple major versions of qmake. If
necessary, substitute the correct name or path for Qt6 qmake in the command
listed below.

To build:

- `cd src`
- `qmake`
- `make`

The resulting executable is named binarize-gui.
