#include <QtGui>
#include "ImageView.h"

ImageView::ImageView (QImage *i, QWidget *parent) : QGraphicsView (parent)
{
  pixmap = QPixmap::fromImage (*i);
  item = new QGraphicsPixmapItem (pixmap);
  scene = new QGraphicsScene;
  scene->addItem (item);
  setScene (scene);
}

void ImageView::setImage (QImage *i)
{
  pixmap.convertFromImage (*i);
  scene->update ();
}
