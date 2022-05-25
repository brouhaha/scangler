// scangler - mangle scanned images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#ifndef DOUBLECONTROL_H
#define DOUBLECONTROL_H

#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QVBoxLayout>

#include "DoubleSlider.h"

class DoubleControl: public QGroupBox
{
  Q_OBJECT

 signals:
  void valueChanged(double val);

 public:
  DoubleControl(double min, double max,
		int decimals,
		double step,
		double initial,
		const char *title = 0,
		QWidget *parent = 0);
  void setValue(double val);
  double getValue();

 private:
  QDoubleSpinBox spinbox;
  DoubleSlider slider;
  QVBoxLayout layout;
};

#endif
