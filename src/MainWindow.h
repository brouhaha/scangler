// binarize - Sauvola binarization of images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdint.h>
#include <QMainWindow>

#include "IntegralImage.h"
#include "BinarizeSauvola.h"
#include "ImageViewPair.h"
#include "IntControl.h"
#include "SauvolaControls.h"

class MainWindow: public QMainWindow
{
  Q_OBJECT

 public:
  MainWindow();

 private:
  QImage *image1;
  uint32_t width;
  uint32_t height;
  uint64_t pixels;

  IntegralImage *integral_image;
  BinarizeSauvola binarize;

  QImage *image2;

  ImageViewPair *ivp;
  SauvolaControls *sparm;
  IntControl *threadCount;

  void createActions();
  void createMenus();

  QMenu *fileMenu;
  QAction *openAct;
  QAction *exitAct;

  QMenu *viewMenu;
  QAction *viewHAct;
  QAction *viewVAct;
  QAction *view0Act;
  QAction *view1Act;

  void loadImage(QString fn);
  void computeIntegralImages();
  void do_binarize(int w, double k);

 private slots:
  void openFile();
  void viewH();
  void viewV();
  void view0();
  void view1();

  void sauvolaParametersChanged(double k, int w);
};

#endif
