#ifndef INTCONTROL_H
#define INTCONTROL_H

#include <QtGui>

class IntControl: public QGroupBox
{
  Q_OBJECT

 signals:
  void valueChanged (int val);

 public:
  IntControl (int min, int max, int initial,
	      const char *title = 0,
	      QWidget *parent = 0);
  void setValue (int val);
  int getValue ();

 private:
  QSpinBox *spinbox;
  QSlider *slider;
  QVBoxLayout *layout;
};

#endif
