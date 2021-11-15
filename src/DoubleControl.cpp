#include "DoubleControl.h"

DoubleControl::DoubleControl (double min, double max,
			      int decimals,
			      double step,
			      double initial,
			      const char *title,
			      QWidget *parent) : QGroupBox (parent)
{
  spinbox = new QDoubleSpinBox (this);
  spinbox->setMinimum (min);
  spinbox->setMaximum (max);
  spinbox->setDecimals (decimals);
  spinbox->setSingleStep (step);
  spinbox->setValue (initial);

  slider = new QwtSlider (this, Qt::Horizontal, QwtSlider::BottomScale);
  slider->setRange (min, max);
  slider->setValue (initial);

  connect (spinbox,
	   SIGNAL (valueChanged (double)),
	   slider,
	   SLOT (setValue (double)));
  connect (slider,
	   SIGNAL (valueChanged (double)),
	   spinbox,
	   SLOT (setValue (double)));
  connect (spinbox,
	   SIGNAL (valueChanged (double)),
	   this,
	   SIGNAL (valueChanged (double)));
  connect (slider,
	   SIGNAL (valueChanged (double)),
	   this,
	   SIGNAL (valueChanged (double)));

  layout = new QVBoxLayout (this);
  layout->addWidget (slider);
  layout->addWidget (spinbox);
  setLayout (layout);

  if (title)
    setTitle (title);
}

void DoubleControl::setValue (double val)
{
  spinbox->setValue (val);
}

double DoubleControl::getValue ()
{
  return spinbox->value ();
}
