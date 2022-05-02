// binarize - Sauvola binarization of images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#include <sstream>

#include "ScaleControl.h"

ScaleControl::ScaleControl (unsigned zoom_out_max,
			    unsigned zoom_in_max,
			    unsigned initial,
			    bool initial_in,
			    const char *title,
			    QWidget *parent) : QGroupBox(parent),
					       lineedit(parent),
					       slider(Qt::Horizontal, this),
					       layout(QVBoxLayout(this))
							 
{
  lineedit.setReadOnly(true);

  assert(zoom_out_max > 0);
  assert(zoom_in_max > 0);
  assert(initial > 0);

  slider.setRange(2-zoom_out_max, zoom_in_max);

  // link the slider to this
  connect(& slider,  & QSlider::valueChanged,
	  this,      & ScaleControl::sliderValueChanged);

  slider.setValue(initial_in ? 2-initial : initial);

  layout.addWidget(& slider);
  layout.addWidget(& lineedit);
  setLayout(& layout);

  if (title)
    setTitle(title);
}

double ScaleControl::getValue()
{
  if (zoom_in)
    return zoom_factor;
  else
    return 1.0 / zoom_factor;
}

void ScaleControl::sliderValueChanged(int value)
{
  std::stringstream ss;
  if (value <= 0)
    {
      zoom_in = false;
      zoom_factor = 2 - value;
      ss << "1/" << zoom_factor;
    }
  else
    {
      zoom_in = true;
      zoom_factor = value;
      ss << zoom_factor;
    }
  lineedit.setText(QString::fromStdString(ss.str()));
  valueChanged(getValue());
}
