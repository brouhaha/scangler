// scangler - mangle scanned images
// Copyright 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#ifndef MULTIPLEIMAGEVIEW_H
#define MULTIPEIMAGEVIEW_H

#include <vector>

#include <QGridLayout>

#include "ScaleControl.h"
#include "ImageView.h"

class MultipleImageView: public QWidget
{
  Q_OBJECT

 public:
  MultipleImageView(unsigned rows = 1,
		    unsigned cols = 1,
		    QWidget *parent = 0,
		    Qt::WindowFlags f = Qt::WindowFlags());

  ~MultipleImageView();						   

 public slots:
  void setImage(int row, int col, QImage& i);
  void setScale(double scale);

 private:
  unsigned cols;
  unsigned rows;
  unsigned size;
  std::vector<ImageView*> images;
  ScaleControl scaleControl;
  QGridLayout layout;
};

#endif
