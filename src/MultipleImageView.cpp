// scangler - mangle scanned images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#include <QScrollBar>

#include "MultipleImageView.h"


MultipleImageView::MultipleImageView(unsigned cols,
				     unsigned rows,
				     QWidget *parent,
				     Qt::WindowFlags f) :
	QWidget (parent, f),
	cols(cols),
	rows(rows),
	size(rows * cols),
	scaleControl(16, 16, 1, false, "zoom factor", this),
	layout(QGridLayout(this))
{
  images.reserve(size);

  for (unsigned i = 0; i < size; i++)
    images[i] = new ImageView(parent);

  for (unsigned i = 0; i < size; i++)
  {
    unsigned row = i / cols;
    unsigned col = i % cols;
    layout.addWidget(images[i], row, col);
    for (unsigned j = 0; j < cols; j++)
    {
      if (i != j)
	connect(images[i], & ImageView::positionChanged,
		images[j], & ImageView::setPosition);
    }
  }

  layout.addWidget(& scaleControl, rows, 0);
  connect(& scaleControl, & ScaleControl::valueChanged,
	  this,           & MultipleImageView::setScale);

  setLayout(& layout);
}

MultipleImageView::~MultipleImageView()
{
  for (unsigned i = 0; i < size; i++)
    delete images[i];
}

void MultipleImageView::setImage(int row, int col, QImage& i)
{
  images[row * cols + col]->setImage(i);
}

void MultipleImageView::setScale(double scale)
{
  for (unsigned i = 0; i < size; i++)
    images[i]->setScale(scale);
}
