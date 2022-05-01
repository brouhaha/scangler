// binarize - Sauvola binarization of images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#ifndef BINARIZE_SAUVOLA_H
#define BINARIZE_SAUVOLA_H

#include "Binarize.h"

class BinarizeSauvola: public Binarize
{
 public:
  BinarizeSauvola(int w = 30,
		  double k = 0.2);

  void binarize(QImage &source, QImage &dest, IntegralImage &integral_image);

  int w;     // window size
  double k;  // 
};

#endif
