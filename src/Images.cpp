// binarize - Sauvola binarization of images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#include "Images.h"


Images::Images(QString fn) :
  image1(QImage(fn)),  // XXX What happens below if this fails and image1 is null?
  width(image1.width()),
  height(image1.height()),
  pixel_count(static_cast<uint64_t>(width) * static_cast<uint64_t>(height)),
  image1_grayscale(image1.copy()),
  integral_image(image1_grayscale),
  image2(QImage(width, height, QImage::Format_MonoLSB))
{
  image2.fill(1);  // white
}

bool Images::valid()
{
  return ((! image1.isNull()) &&
	  (! image1_grayscale.isNull()) &&
	  (! image2.isNull()));
}

uint32_t Images::get_width()
{
  return width;
}

uint32_t Images::get_height()
{
  return height;
}

uint64_t Images::get_pixel_count()
{
  return pixel_count;
}

