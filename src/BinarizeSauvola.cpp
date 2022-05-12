// binarize - Sauvola binarization of images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#include "BinarizeSauvola.h"


bool SauvolaParameters::operator==(const SauvolaParameters& other)
{
  return (w == other.w) && (k == other.k);
}

bool SauvolaParameters::operator!=(const SauvolaParameters& other)
{
  return (w != other.w) || (k != other.k);
}


void BinarizeSauvola::set_params(SauvolaParameters &new_params)
{
  this->params = new_params;
}


void BinarizeSauvola::get_params(SauvolaParameters &params)
{
  params = this->params;
}


void BinarizeSauvola::binarize(QImage &source,
			       IntegralImage &integral_image,
			       QImage &dest)
{
  // source must be 8-bit grayscale
  assert(source.format() == QImage::Format_Grayscale8);
  assert(source.depth() == 8);

  // destination must be bitmap
  assert(dest.format() == QImage::Format_MonoLSB);
  assert(dest.depth() == 1);

  uint32_t height = source.height();
  uint32_t width = source.width();

  for(uint32_t y = 0; y < height; y++)
    {
      uint8_t *gray_line = source.scanLine(y);
      uint8_t *bitmap_line = dest.scanLine(y);
      for(uint32_t x = 0; x < width; x++)
	{
	  Stats stats;

	  integral_image.compute_stats(x, y, params.w, stats);

	  double threshold = stats.mean *(1 + params.k *((stats.standard_deviation / 128) - 1));

	  if (gray_line[x] < threshold)
	    bitmap_line [x / 8] &= ~(1 <<(x & 7));
	  else
	    bitmap_line [x / 8] |=(1 <<(x & 7));
	}
    }
}
