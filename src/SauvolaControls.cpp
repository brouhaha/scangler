#include "SauvolaControls.h"

SauvolaControls::SauvolaControls (double k, int w,
				  QWidget *parent) : QGroupBox (parent)
{
  sw = new IntControl (0, 1000, w, "window size", this);
  sk = new DoubleControl (0.0, 1.0, 3, 0.01, k, "k", this);

  connect (sw,
	   SIGNAL (valueChanged (int)),
	   this,
	   SLOT (controlChanged ()));
  connect (sk,
	   SIGNAL (valueChanged (double)),
	   this,
	   SLOT (controlChanged ()));

  layout = new QHBoxLayout (this);
  layout->addWidget (sw);
  layout->addWidget (sk);
  setLayout (layout);
  setTitle ("Sauvola binarization parameters");
  setObjectName ("SauvolaGroupBox");
  setStyleSheet ("QGroupBox#SauvolaGroupBox { border: 2px solid gray; border-radius: 3px; }");
}

int SauvolaControls::getW ()
{
  return sw->getValue ();
}

double SauvolaControls::getK ()
{
  return sk->getValue ();
}

void SauvolaControls::controlChanged ()
{
  valueChanged (sk->getValue (), sw->getValue ());
}
