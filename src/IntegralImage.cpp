// binarize - Sauvola binarization of images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#include <cmath>

#include "IntegralImage.h"

IntegralImage::IntegralImage(QImage &image) :
  width(image.width()),
  height(image.height()),
  ii(width * height, 0),
  sii(width * height, 0)
{
  // handle y=0
  uint64_t rs = 0;
  uint64_t rs2 = 0;
  for(uint32_t x = 0; x < width; x++)
    {
      uint32_t pval = image.pixelColor(x, 0).value();
      rs += pval;
      rs2 += pval * pval;
      ii[x] = rs;
      sii[x] = rs2;
    }

  // handle y>0
  for(uint32_t y = 1; y < height; y++)
    {
      long row_base = y * width;
      rs = 0;
      rs2 = 0;
      for(uint32_t x = 0; x < width; x++)
	{
	  uint32_t pval = image.pixelColor(x, y).value();
	  rs += pval;
	  rs2 += pval * pval;
	  ii[row_base + x] = rs + ii[row_base - width + x];
	  sii[row_base + x] = rs2 + sii[row_base - width + x];
	}
    }
}


void IntegralImage::compute_stats(uint32_t x, uint32_t y, uint32_t window,
				  Stats &stats)
{
  // compute window coordinates, clipping at edges
  uint32_t x_min = (x < window/2) ? 0 : x - window/2;
  uint32_t x_max = (x + window/2 >= width) ? width - 1 : x + window/2;
  uint32_t y_min = (y < window/2) ? 0 : y - window/2;
  uint32_t y_max = (y + window/2 >= width) ? width - 1 : y + window/2;

  uint64_t tl = y_min * width + x_min;
  uint64_t tr = y_min * width + x_max;
  uint64_t bl = y_max * width + x_min;
  uint64_t br = y_max * width + x_max;

  double area = ((double)(x_max + 1 - x_min)) * ((double)(y_max + 1 - y_min));

  stats.mean = (ii[tl] + ii[br] - ii[tr] - ii[bl]) / area;
  stats.variance = (sii[tl] + sii[br] -sii[tr] - sii[bl]) / area;
  stats.standard_deviation = sqrt(stats.variance);
}
