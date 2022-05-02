// binarize - Sauvola binarization of images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#ifndef IMAGEVIEWPAIR_H
#define IMAGEVIEWPAIR_H

#include <QGridLayout>

#include "IntControl.h"
#include "ImageView.h"

class ImageViewPair: public QWidget
{
  Q_OBJECT

 public:
  enum Orientation
  {
    Unknown,
    Horizontal,
    Vertical,
    Only0,
    Only1
  };

  ImageViewPair(QImage *i0, QImage *i1, QWidget *parent = 0, Qt::WindowFlags f = Qt::WindowFlags());

 public slots:
  void setImage(int n, QImage *i);
  void setScale(int scale);
  void setOrientation(enum Orientation orientation);

 private:
  enum Orientation orientation;
  ImageView *imageView[2];
  IntControl scaleControl;
  QGridLayout layout;
};

#endif
