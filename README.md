# scangler - Sauvola binarization of images

Copyright 2012, 2022, 2023 Eric Smith <spacewar@gmail.com>

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

The program is written in C++ 17, and requires:

- Qt 6.2.3 or later
- GCC g++ 11.2.1 or later
- SCons 4.4.0 or later

To build:

- `scons`

or

- `scons target=posix`

The resulting executable is `build/posix/scangler`.

To cross-build for Windows, using mingw32 or mingw64:

- `scons target=win32`

or

- `scons target=win64`
