// binarize - Sauvola binarization of images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#include <cmath>

#include "DoubleControl.h"

DoubleControl::DoubleControl (double min, double max,
			      int decimals,
			      double step,
			      double initial,
			      const char *title,
			      QWidget *parent) : QGroupBox (parent),
						 spinbox(QDoubleSpinBox(this)),
						 slider(DoubleSlider(this, pow(10, decimals))),
						 layout(QVBoxLayout(this))
							 
{
  spinbox.setMinimum(min);
  spinbox.setMaximum(max);
  spinbox.setDecimals(decimals);
  spinbox.setSingleStep(step);
  spinbox.setValue(initial);

  slider.setDoubleRange(min, max);
  slider.setDoubleValue(initial);

  connect(& spinbox,
	  SIGNAL(valueChanged (double)),
	  & slider,
	  SLOT(setValue (double)));
  connect(& slider,
	  SIGNAL(valueChanged (double)),
	  & spinbox,
	  SLOT(setValue (double)));
  connect(& spinbox,
	  SIGNAL(valueChanged (double)),
	  this,
	  SIGNAL(valueChanged (double)));
  connect(& slider,
	  SIGNAL(valueChanged (double)),
	  this,
	  SIGNAL(valueChanged (double)));

  layout.addWidget(& slider);
  layout.addWidget(& spinbox);
  setLayout(& layout);

  if (title)
    setTitle(title);
}

void DoubleControl::setValue(double val)
{
  spinbox.setValue(val);
}

double DoubleControl::getValue()
{
  return spinbox.value();
}
