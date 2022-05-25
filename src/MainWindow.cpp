// scangler - mangle scanned images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#include <chrono>
#include <iostream>

#include <QAction>
#include <QErrorMessage>
#include <QMenuBar>
#include <QFileDialog>

#include "MainWindow.h"


MainWindow::MainWindow():
  box(this),
  boxLayout(& box),
  sauvola_controls(this),
  binarize(),
  imageViews(2, 1, this)
{
  connect(& sauvola_controls, & SauvolaControls::valueChanged,
	  this,  & MainWindow::sauvolaParametersChanged);

  openFile();

  boxLayout.addWidget(& imageViews);
  boxLayout.addWidget(& sauvola_controls);
  box.setLayout(& boxLayout);

  setCentralWidget(& box);

  createMenus();
}

void MainWindow::createMenus()
{
  QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

  auto openAct = new QAction(tr("&Open"), this);
  connect(openAct,  & QAction::triggered,
	  this,     & MainWindow::openFile);
  fileMenu->addAction(openAct);

  auto saveAsAct = new QAction(tr("&Save As..."), this);
  connect(saveAsAct,  & QAction::triggered,
	  this,       & MainWindow::saveFile);
  fileMenu->addAction(saveAsAct);

  fileMenu->addSeparator();

  auto exitAct = new QAction(tr("&Exit"), this);
  connect(exitAct,  & QAction::triggered,
	  this,     & MainWindow::close);
  fileMenu->addAction(exitAct);
}

void MainWindow::loadImage(QString fn)
{
  Images *new_images = new Images(fn);
  if (! new_images->valid())
    {
      // XXX need to report the error
      delete new_images;
      return;
    }

  if (images)
    delete(images);
  images = new_images;

  imageViews.setImage(0, 0, images->image1);

  do_binarize();
}

void MainWindow::saveImage(QString fn)
{
  if (! images->image2.save(fn))
    {
      std::cout << "File save failed.\n";
      QErrorMessage::qtHandler()->showMessage("File save failed.");
    }
}

void MainWindow::openFile()
{
  QString fn = QFileDialog::getOpenFileName(this, 
					     tr("Open image"),
					     ".",
					     tr("Image Files(*.png *.jpg *.bmp)"));
  if (fn.isNull())
    return;
  loadImage(fn);
}

void MainWindow::saveFile()
{
  QString fn = QFileDialog::getSaveFileName(this, 
					     tr("Save image"),
					     ".",
					     tr("Image Files(*.png *.jpg *.bmp *.tiff)"));
  if (fn.isNull())
    return;
  saveImage(fn);
}

void MainWindow::do_binarize()
{
  auto start_time = std::chrono::steady_clock::now();
  binarize.binarize(images->image1_grayscale,
		    images->integral_image,
		    images->image2);
  auto end_time = std::chrono::steady_clock::now();
  auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
  std::cout << "binarize time " << elapsed_ms.count() << " ms\n";

  imageViews.setImage(0, 1, images->image2);
}

void MainWindow::sauvolaParametersChanged(SauvolaParameters& new_params)
{
  SauvolaParameters current_params;
  binarize.get_params(current_params);
  if (new_params != current_params)
  {
    binarize.set_params(new_params);
    std::cout << "k: " << new_params.k << "  w: " << new_params.w << "\n";
    do_binarize();
  }
}
