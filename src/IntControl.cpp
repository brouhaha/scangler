// binarize - Sauvola binarization of images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#include "IntControl.h"

IntControl::IntControl(int min, int max, int initial,
		       const char *title,
		       QWidget *parent) : QGroupBox (parent),
					  spinbox(QSpinBox(this)),
					  slider(QSlider(Qt::Horizontal, this)),
					  layout(QVBoxLayout(this))
{
  spinbox.setMinimum(min);
  spinbox.setMaximum(max);
  spinbox.setValue(initial);

  slider.setMinimum(min);
  slider.setMaximum(max);
  slider.setValue(initial);

  connect(& spinbox,
	  SIGNAL(valueChanged (int)),
	  & slider,
	  SLOT(setValue (int)));
  connect(& slider,
	  SIGNAL (valueChanged (int)),
	  & spinbox,
	  SLOT (setValue (int)));
  connect(& spinbox,
	  SIGNAL (valueChanged (int)),
	  this,
	  SIGNAL (valueChanged (int)));
  connect(& slider,
	  SIGNAL (valueChanged (int)),
	  this,
	  SIGNAL (valueChanged (int)));

  layout.addWidget(& slider);
  layout.addWidget(& spinbox);
  setLayout(& layout);

  if (title)
    setTitle(title);
}

void IntControl::setValue(int val)
{
  spinbox.setValue(val);
}

int IntControl::getValue()
{
  return spinbox.value();
}

