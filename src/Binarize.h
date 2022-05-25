// scangler - mangle scanned images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#ifndef BINARIZE_H
#define BINARIZE_H

#include <QImage>

#include "IntegralImage.h"

class Binarize
{
 public:
  virtual void binarize(QImage& source,
			IntegralImage& integral_image,
			QImage& dest) = 0;
};

#endif // BINARIZE_H
