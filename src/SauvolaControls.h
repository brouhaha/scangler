// binarize - Sauvola binarization of images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#ifndef SAUVOLACONTROLS_H
#define SAUVOLACONTROLS_H

#include <QtGui>
#include "IntControl.h"
#include "DoubleControl.h"

class SauvolaControls: public QGroupBox
{
  Q_OBJECT

 public:
  SauvolaControls (double k = 0.2, int w = 30,
		   QWidget *parent = 0);
  int getW ();
  double getK ();

 signals:
  void valueChanged (double k, int w);

 private:
  IntControl *sw;
  DoubleControl *sk;
  QHBoxLayout *layout;

  private slots:
   void controlChanged ();
};

#endif
