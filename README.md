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

The program requires Qt4 and Qwt5.
