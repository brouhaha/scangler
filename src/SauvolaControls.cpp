// binarize - Sauvola binarization of images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#include "SauvolaControls.h"

SauvolaControls::SauvolaControls(double k, int w,
				 QWidget *parent) : QGroupBox(parent),
						    sw(IntControl(0, 1000, w, "window size", this)),
						    sk(DoubleControl(0.0, 1.0, 3, 0.01, k, "k", this)),
						    layout(QHBoxLayout(this))
{
  connect(& sw,
	   SIGNAL(valueChanged(int)),
	   this,
	   SLOT(controlChanged()));
  connect(& sk,
	   SIGNAL(valueChanged(double)),
	   this,
	   SLOT(controlChanged()));

  layout.addWidget(& sw);
  layout.addWidget(& sk);
  setLayout(& layout);
  setTitle("Sauvola binarization parameters");
  setObjectName("SauvolaGroupBox");
  setStyleSheet("QGroupBox#SauvolaGroupBox { border: 2px solid gray; border-radius: 3px; }");
}

int SauvolaControls::getW()
{
  return sw.getValue();
}

double SauvolaControls::getK()
{
  return sk.getValue();
}

void SauvolaControls::controlChanged()
{
  valueChanged(sk.getValue(), sw.getValue());
}
