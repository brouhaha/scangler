// scangler - mangle scanned images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#include "DoubleSlider.h"


DoubleSlider::DoubleSlider(Qt::Orientation orientation,
			   QWidget *parent,
			   double scale) : QSlider(orientation, parent),
					   scale(scale)
{
  connect(this, & DoubleSlider::valueChanged,
	  this, & DoubleSlider::notifyValueChanged);
}

void DoubleSlider::notifyValueChanged(int value)
{
  double doubleValue = value / scale;
  emit doubleValueChanged(doubleValue);
}

void DoubleSlider::setDoubleValue(double value)
{
  setValue(value * scale);
}

void DoubleSlider::setDoubleRange(double min, double max)
{
  setRange(min * scale, max * scale);
}
