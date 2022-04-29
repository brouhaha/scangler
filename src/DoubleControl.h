#ifndef DOUBLECONTROL_H
#define DOUBLECONTROL_H

#include <QtGui>
#include <qwt5-qt4/qwt_slider.h>

class DoubleControl: public QGroupBox
{
  Q_OBJECT

 signals:
  void valueChanged (double val);

 public:
  DoubleControl (double min, double max,
		 int decimals,
		 double step,
		 double initial,
		 const char *title = 0,
		 QWidget *parent = 0);
  void setValue (double val);
  double getValue ();

 private:
  QDoubleSpinBox *spinbox;
  QwtSlider *slider;
  QVBoxLayout *layout;
};

#endif
