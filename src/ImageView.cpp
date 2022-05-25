// scangler - mangle scanned images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#include <QScrollBar>

#include "ImageView.h"

ImageView::ImageView(QWidget *parent) : QGraphicsView (parent)
{
  scene.addItem(& item);
  setScene(& scene);
  connect(this->horizontalScrollBar(), & QScrollBar::valueChanged,
	  this,                        & ImageView::hScrollValueChanged);
  connect(this->verticalScrollBar(),   & QScrollBar::valueChanged,
	  this,                        & ImageView::vScrollValueChanged);
}

void ImageView::setImage(QImage& i)
{
  pixmap.convertFromImage(i);
  item.setPixmap(pixmap);
}

void ImageView::setScale(double scale)
{
  resetTransform();
  this->scale(scale, scale);
}

void ImageView::setPosition(int x, int y)
{
  this->horizontalScrollBar()->setValue(x);
  this->verticalScrollBar()->setValue(y);
}

void ImageView::hScrollValueChanged(int value)
{
  auto y = this->verticalScrollBar()->value();
  positionChanged(value, y);
}

void ImageView::vScrollValueChanged(int value)
{
  auto x = this->horizontalScrollBar()->value();
  positionChanged(x, value);
}
