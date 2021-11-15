#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QtGui>

class ImageView: public QGraphicsView
{
  Q_OBJECT

 private:
  QPixmap pixmap;
  QGraphicsPixmapItem *item;
  QGraphicsScene *scene;
  QGraphicsView *view;

 public:
  ImageView (QImage *i, QWidget *parent = 0);
  void setImage (QImage *i);
};

#endif
