// scangler - mangle scanned images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

// Integral image I of an input image G is defined
//     I(x,y) = sum(i=0 to x) sum(j=0 to y) G(i,j}
// In other words, the value of the integral image I at each pixel location
// is the sum of the values of all of the pixels above and to the left of
// that position in the original image G.
//
// Having an integral image and a integral image of the squares of the pixel
// values makes it very efficient to compupte the mean and variance of
// the pixel values of any rectangular regiong of the image.
//
// Shafait, Faisal & Keysers, Daniel & Breuel, Thomas. (2008). Efficient
// implementation of local adaptive thresholding techniques using integral
// images. Proceedings of SPIE. DOI 10.1117/12.767755. 

#ifndef INTEGRALIMAGE_H
#define INTEGRALIMAGE_H

#include <QImage>

struct Stats
{
  double mean;
  double variance;
  double standard_deviation;
};

class IntegralImage
{
 public:
  IntegralImage(QImage &image);

  void compute_stats(uint32_t x, uint32_t y, uint32_t window,
		     Stats &stats);

 private:
  uint32_t width;
  uint32_t height;

  std::vector<uint64_t> ii;  // integral image of pixel values
  std::vector<uint64_t> sii; // integral image of squared pixel values
};

#endif
