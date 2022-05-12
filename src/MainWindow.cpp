// binarize - Sauvola binarization of images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#include <chrono>
#include <iostream>

#include <QAction>
#include <QMenuBar>
#include <QFileDialog>

#include "MainWindow.h"


MainWindow::MainWindow():
  binarize()
{
  QWidget *box = new QWidget(this);

  sauvola_controls = new SauvolaControls(this);

  connect(sauvola_controls, & SauvolaControls::valueChanged,
	  this,  & MainWindow::sauvolaParametersChanged);

  ivp = nullptr;

  openFile();

  QVBoxLayout *boxLayout = new QVBoxLayout(box);

  ivp = new ImageViewPair(& images->image1, & images->image2);

  boxLayout->addWidget(ivp);
  boxLayout->addWidget(sauvola_controls);
  box->setLayout(boxLayout);

  setCentralWidget(box);

  createActions();
  createMenus();
}

void MainWindow::createActions()
{
  openAct = new QAction(tr("&Open"), this);
  connect(openAct,  & QAction::triggered,
	  this,     & MainWindow::openFile);

  exitAct = new QAction(tr("&Exit"), this);
  connect(exitAct,  & QAction::triggered,
	  this,     & MainWindow::close);

  viewHAct = new QAction(tr("&Horizontal"), this);
  connect(viewHAct, & QAction::triggered,
	  this,     & MainWindow::viewH);

  viewVAct = new QAction(tr("&Vertical"), this);
  connect(viewVAct, & QAction::triggered,
	  this,     & MainWindow::viewV);

  view0Act = new QAction(tr("&Greyscale only"), this);
  connect(view0Act, & QAction::triggered,
	  this,     & MainWindow::view0);

  view1Act = new QAction(tr("&Binarized only"), this);
  connect(view1Act, & QAction::triggered,
	  this,     & MainWindow::view1);
}

void MainWindow::createMenus()
{
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(openAct);
  fileMenu->addAction(exitAct);

  viewMenu = menuBar()->addMenu(tr("&View"));
  viewMenu->addAction(viewHAct);
  viewMenu->addAction(viewVAct);
  viewMenu->addAction(view0Act);
  viewMenu->addAction(view1Act);
}

void MainWindow::viewH()
{
  ivp->setOrientation(ImageViewPair::Horizontal);
}

void MainWindow::viewV()
{
  ivp->setOrientation(ImageViewPair::Vertical);
}

void MainWindow::view0()
{
  ivp->setOrientation(ImageViewPair::Only0);
}

void MainWindow::view1()
{
  ivp->setOrientation(ImageViewPair::Only1);
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

  if (ivp)
    ivp->setImage(0, & images->image1);

  do_binarize();
}

void MainWindow::openFile()
{
  QString fn = QFileDialog::getOpenFileName(this, 
					     tr("Open image"),
					     ".",
					     tr("Image Files(*.png *.jpg *.bmp)"));
  loadImage(fn);
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

  if (ivp)
    ivp->setImage(1, & images->image2);
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
