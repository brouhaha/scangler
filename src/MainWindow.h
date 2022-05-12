// binarize - Sauvola binarization of images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdint.h>

#include <QMainWindow>

#include "Images.h"
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
  Images *images = nullptr;
  ImageViewPair *ivp;

  BinarizeSauvola binarize;
  SauvolaControls *sauvola_controls;

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
  void do_binarize();

 private slots:
  void openFile();
  void viewH();
  void viewV();
  void view0();
  void view1();

  void sauvolaParametersChanged(SauvolaParameters& new_params);
};

#endif
