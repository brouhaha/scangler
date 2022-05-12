// binarize - Sauvola binarization of images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

// Sauvola, Jaakko & Seppänen, Tapio & Haapakoski, Sami & Pietikäinen, Matti.
// (1997). Adaptive Document Binarization. Pattern Recognition. 33. 147-152
// vol.1. 10.1109/ICDAR.1997.619831. 

#ifndef BINARIZE_SAUVOLA_H
#define BINARIZE_SAUVOLA_H

#include "Binarize.h"

class SauvolaParameters
{
public:
  int    w = 30;     // window width and height in pixels
  double k = 0.2;

  bool operator==(const SauvolaParameters& other);
  bool operator!=(const SauvolaParameters& other);
};

class BinarizeSauvola: public Binarize
{
 public:
  void set_params(SauvolaParameters& new_params);

  void get_params(SauvolaParameters& new_params);

  void binarize(QImage& source, IntegralImage& integral_image, QImage& dest);

 private:
  SauvolaParameters params;
};

#endif
