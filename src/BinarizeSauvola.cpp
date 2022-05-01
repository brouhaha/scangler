// binarize - Sauvola binarization of images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#include "BinarizeSauvola.h"


BinarizeSauvola::BinarizeSauvola(int w, double k) : w(w), k(k)
{
}


void BinarizeSauvola::binarize(QImage &source,
			       QImage &dest,
			       IntegralImage &integral_image)
{
  assert(dest.depth() == 1);  // destination must be bitmap

  uint32_t height = source.height();
  uint32_t width = source.width();

  for(uint32_t y = 0; y < height; y++)
    {
      uint8_t *bitmap_line = dest.scanLine(y);
      for(uint32_t x = 0; x < width; x++)
	{
	  Stats stats;

	  integral_image.compute_stats(x, y, w, stats);

	  double threshold = stats.mean *(1 + k *((stats.standard_deviation / 128) - 1));

	  // should use constScanline() in outr loop, then index to get
	  // pixel data
	  if (source.pixelColor(x, y).value() < threshold)
	    bitmap_line [x / 8] &= ~(1 <<(x & 7));
	  else
	    bitmap_line [x / 8] |=(1 <<(x & 7));
	}
    }
}
