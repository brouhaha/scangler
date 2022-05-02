// binarize - Sauvola binarization of images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#include <iostream>

#include <QScrollBar>

#include "ImageViewPair.h"


static bool debug = false;


ImageViewPair::ImageViewPair(QImage *i0, QImage *i1, QWidget *parent, Qt::WindowFlags f) : QWidget (parent, f),
											   scaleControl(1, 64, 1, "zoom factor", this),
											   layout(QGridLayout(this))
{
  imageView[0] = new ImageView(i0, this);
  imageView[1] = new ImageView(i1, this);

  for (int i = 0; i < 2; i++)
    {
      connect(imageView[  i]->horizontalScrollBar(), & QScrollBar::valueChanged,
	      imageView[! i]->horizontalScrollBar(), & QScrollBar::setValue);
      connect(imageView[  i]->verticalScrollBar(),   & QScrollBar::valueChanged,
	      imageView[! i]->verticalScrollBar(),   & QScrollBar::setValue);
    }

  connect(& scaleControl, & IntControl::valueChanged,
	  this,           & ImageViewPair::setScale);

  orientation = Unknown;
  setOrientation(Horizontal);
  setLayout(& layout);
}

void ImageViewPair::setImage(int n, QImage *i)
{
  imageView[n]->setImage(i);
}

void ImageViewPair::setScale(int scale)
{
  for (int i = 0; i <= 1; i++)
    imageView[i]->setScale(scale);
}

void ImageViewPair::setOrientation(enum Orientation orientation)
{
  if (orientation == this->orientation)
    return;
  switch (this->orientation)
    {
    case Unknown:
      break;
    case Horizontal:
    case Vertical:
      if (debug)
	std::cout << "removing image 0\n";
      layout.removeWidget(imageView[0]);
      if (debug)
	std::cout << "removing image 1\n";
      layout.removeWidget(imageView[1]);
      layout.removeWidget(&scaleControl);
      break;
    case Only0:
      if (debug)
	std::cout << "removing image 0\n";
      layout.removeWidget(imageView[0]);
      layout.removeWidget(&scaleControl);
      break;
    case Only1:
      if (debug)
	std::cout << "removing image 1\n";
      layout.removeWidget(imageView[1]);
      layout.removeWidget(&scaleControl);
      break;
    }

  switch (orientation)
    {
    case Unknown:
      break;
    case Horizontal:
      if (debug)
	std::cout << "adding 0 at row 0 col 0\n";
      layout.addWidget(imageView[0], 0, 0);
      if (debug)
	std::cout << "adding 1 at row 0 col 1\n";
      layout.addWidget(imageView[1], 0, 1);
      layout.addWidget(&scaleControl, 1, 0);
      break;
    case Vertical:
      if (debug)
	std::cout << "adding 0 at row 0 col 0\n";
      layout.addWidget(imageView[0], 0, 0);
      if (debug)
	std::cout << "adding 1 at row 1 col 0\n";
      layout.addWidget(imageView[1], 1, 0);
      layout.addWidget(&scaleControl, 2, 0);
      break;
    case Only0:
      if (debug)
	std::cout << "adding 0 at row 0 col 0\n";
      layout.addWidget(imageView[0], 0, 0);
      layout.addWidget(&scaleControl, 1, 0);
      break;
    case Only1:
      if (debug)
	std::cout << "adding 1 at row 0 col 0\n";
      layout.addWidget(imageView[1], 0, 0);
      layout.addWidget(&scaleControl, 1, 0);
      break;
    }

  for (int i = 0; i <= 1; i++)
    if (debug)
      std::cout << "image " << i << " at index " << layout.indexOf(imageView[i]) << "\n";

  this->orientation = orientation;
}
