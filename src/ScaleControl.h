// binarize - Sauvola binarization of images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#ifndef SCALECONTROL_H
#define SCALECONTROL_H

#include <QLineEdit>
#include <QGroupBox>
#include <QVBoxLayout>

#include "DoubleSlider.h"

class ScaleControl: public QGroupBox
{
  Q_OBJECT

 signals:
  void valueChanged(double val);

 public:
  ScaleControl(unsigned zoom_out_max,
	       unsigned zoom_in_max,
	       unsigned initial,
	       bool initial_in,
	       const char *title = 0,
	       QWidget *parent = 0);
  double getValue();

 private:
  bool zoom_in;
  unsigned zoom_factor;
  QLineEdit lineedit;
  QSlider slider;
  QVBoxLayout layout;

 private slots:
  void sliderValueChanged(int value);
};

#endif
