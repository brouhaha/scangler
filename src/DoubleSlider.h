// binarize - Sauvola binarization of images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#ifndef DOUBLESLIDER_H
#define DOUBLESLIDER_H

#include <QSlider>

class DoubleSlider: public QSlider
{
  Q_OBJECT

 public:
  DoubleSlider(QWidget *parent = 0, double scale = 10.0);

 signals:
  void doubleValueChanged(double value);

 public slots:
   void notifyValueChanged(int value);
   void setDoubleValue(double value);
   void setDoubleRange(double min, double max);

 private:
   double scale;
};

#endif
