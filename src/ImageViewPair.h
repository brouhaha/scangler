#ifndef IMAGEVIEWPAIR_H
#define IMAGEVIEWPAIR_H

#include <QtGui>
#include "ImageView.h"

class ImageViewPair: public QWidget
{
  Q_OBJECT

 public:
  enum Orientation
  {
    Horizontal,
    Vertical,
    Only0,
    Only1
  };

  ImageViewPair (QImage *i1, QImage *i2, QWidget *parent = 0, Qt::WindowFlags f = 0);
  void setImage (int n, QImage *i);
  void setOrientation (enum Orientation orientation);

 private:
  enum Orientation orientation;
  QImage *image [2];
  ImageView *imageView [2];
  QGridLayout *layout;
};

#endif
