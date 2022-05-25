// scangler - mangle scanned images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>

class ImageView: public QGraphicsView
{
  Q_OBJECT

private:
  QPixmap pixmap;
  QGraphicsPixmapItem item;
  QGraphicsScene scene;
  QGraphicsView view;

public:
  ImageView(QWidget *parent = 0);

public slots:
  void setImage(QImage& i);
  void setScale(double scale);
  void setPosition(int x, int y);

signals:
  void positionChanged(int x, int y);

private slots:
  void hScrollValueChanged(int value);
  void vScrollValueChanged(int value);
};

#endif
