// scangler - mangle scanned images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdint.h>

#include <QMainWindow>

#include "Images.h"
#include "BinarizeSauvola.h"
#include "MultipleImageView.h"
#include "IntControl.h"
#include "SauvolaControls.h"


class MainWindow: public QMainWindow
{
  Q_OBJECT

 public:
  MainWindow();

 private:
  QWidget box;
  QVBoxLayout boxLayout;
  SauvolaControls sauvola_controls;
  BinarizeSauvola binarize;

  Images *images = nullptr;
  MultipleImageView imageViews;

  void createMenus();

  void loadImage(QString fn);
  void saveImage(QString fn);

  void computeIntegralImages();
  void do_binarize();

 private slots:
  void openFile();
  void saveFile();

  void sauvolaParametersChanged(SauvolaParameters& new_params);
};

#endif
