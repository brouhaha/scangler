// scangler - mangle scanned images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#include "IntControl.h"

IntControl::IntControl(int min, int max, int initial,
		       const char *title,
		       QWidget *parent) : QGroupBox(parent),
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

  // link the QSpinBox to the QSlider and this
  void (QSpinBox::*qspinbox_valueChanged_int)(int) = &QSpinBox::valueChanged;
  connect(& spinbox, qspinbox_valueChanged_int,
	  & slider,  & QSlider::setValue);
  connect(& spinbox, qspinbox_valueChanged_int,
	  this,      & IntControl::valueChanged);

  // link the QSlider to the QSpinBox and this
  connect(& slider,  & QSlider::valueChanged,
	  & spinbox, & QSpinBox::setValue);
  connect(& slider,  & QSlider::valueChanged,
	  this,      & IntControl::valueChanged);

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

