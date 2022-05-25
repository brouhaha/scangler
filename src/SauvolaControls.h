// scangler - mangle scanned images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#ifndef SAUVOLACONTROLS_H
#define SAUVOLACONTROLS_H

#include <QtGui>

#include "BinarizeSauvola.h"
#include "IntControl.h"
#include "DoubleControl.h"

class SauvolaControls: public QGroupBox
{
  Q_OBJECT

 public:
  SauvolaControls(QWidget *parent = 0);

  void set_params(SauvolaParameters& params);

  void get_params(SauvolaParameters& params);

 signals:
  void valueChanged(SauvolaParameters& params);

 private:
  SauvolaParameters params;
  IntControl sw;
  DoubleControl sk;
  QHBoxLayout layout;

 private slots:
  void kChanged(double value);
  void wChanged(int value);
};

#endif
