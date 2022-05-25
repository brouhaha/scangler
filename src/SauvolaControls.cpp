// scangler - mangle scanned images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#include "SauvolaControls.h"

SauvolaControls::SauvolaControls(QWidget *parent) : QGroupBox(parent),
						    sw(IntControl(0, 1000, params.w, "window size", this)),
						    sk(DoubleControl(0.0, 1.0, 3, 0.01, params.k, "k", this)),
						    layout(QHBoxLayout(this))
{
  connect(& sw, & IntControl::valueChanged,
	  this, & SauvolaControls::wChanged);
  connect(& sk, & DoubleControl::valueChanged,
	  this, & SauvolaControls::kChanged);

  layout.addWidget(& sw);
  layout.addWidget(& sk);
  setLayout(& layout);
  setTitle("Sauvola binarization parameters");
  setObjectName("SauvolaGroupBox");
  setStyleSheet("QGroupBox#SauvolaGroupBox { border: 2px solid gray; border-radius: 3px; }");
}

void SauvolaControls::set_params(SauvolaParameters& params)
{
  this->params = params;
  sw.setValue(params.w);
  sk.setValue(params.k);
}

void SauvolaControls::get_params(SauvolaParameters& params)
{
  params = this->params;
}

void SauvolaControls::wChanged(int value)
{
  params.w = value;
  valueChanged(params);
}

void SauvolaControls::kChanged(double value)
{
  params.k = value;
  valueChanged(params);
}
