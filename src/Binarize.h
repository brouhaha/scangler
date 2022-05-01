// binarize - Sauvola binarization of images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#ifndef BINARIZE_H
#define BINARIZE_H

#include <QImage>

#include "IntegralImage.h"

class Binarize
{
 public:
  virtual void binarize(QImage &source,
			QImage &dest,
			IntegralImage &integral_image) = 0;
};

#endif
