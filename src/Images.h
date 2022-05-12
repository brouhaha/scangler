// binarize - Sauvola binarization of images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#ifndef IMAGES_H
#define IMAGES_H

#include <QImage>

#include "IntegralImage.h"

class Images
{
public:
  Images(QString fn);

  QImage image1;

private:
  uint32_t width;
  uint32_t height;
  uint64_t pixel_count;

public:
  QImage image1_grayscale;
  IntegralImage integral_image;
  QImage image2;

  bool valid();

  uint32_t get_width();
  uint32_t get_height();
  uint64_t get_pixel_count();
};

#endif // IMAGES_H
