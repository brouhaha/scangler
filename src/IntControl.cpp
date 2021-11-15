#include "IntControl.h"

IntControl::IntControl (int min, int max, int initial,
			const char *title,
			QWidget *parent) : QGroupBox (parent)
{
  spinbox = new QSpinBox (this);
  spinbox->setMinimum (min);
  spinbox->setMaximum (max);
  spinbox->setValue (initial);

  slider = new QSlider (Qt::Horizontal, this);
  slider->setMinimum (min);
  slider->setMaximum (max);
  slider->setValue (initial);

  connect (spinbox,
	   SIGNAL (valueChanged (int)),
	   slider,
	   SLOT (setValue (int)));
  connect (slider,
	   SIGNAL (valueChanged (int)),
	   spinbox,
	   SLOT (setValue (int)));
  connect (spinbox,
	   SIGNAL (valueChanged (int)),
	   this,
	   SIGNAL (valueChanged (int)));
  connect (slider,
	   SIGNAL (valueChanged (int)),
	   this,
	   SIGNAL (valueChanged (int)));

  layout = new QVBoxLayout (this);
  layout->addWidget (slider);
  layout->addWidget (spinbox);
  setLayout (layout);

  if (title)
    setTitle (title);
}

void IntControl::setValue (int val)
{
  spinbox->setValue (val);
}

int IntControl::getValue ()
{
  return spinbox->value ();
}

