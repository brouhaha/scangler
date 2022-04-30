// binarize - Sauvola binarization of images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#ifndef INTCONTROL_H
#define INTCONTROL_H

#include <QGroupBox>
#include <QSpinBox>
#include <QSlider>
#include <QBoxLayout>

class IntControl: public QGroupBox
{
  Q_OBJECT

 signals:
  void valueChanged(int val);

 public:
  IntControl(int min, int max, int initial,
	     const char *title = 0,
	     QWidget *parent = 0);
  void setValue(int val);
  int getValue();

 private:
  QSpinBox spinbox;
  QSlider slider;
  QVBoxLayout layout;
};

#endif
