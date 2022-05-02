// binarize - Sauvola binarization of images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#include <QAction>
#include <QMenuBar>
#include <QFileDialog>

#include "MainWindow.h"

MainWindow::MainWindow():
  binarize()
{
  QWidget *box = new QWidget(this);
  sparm = new SauvolaControls(0.2, 30, box);

  connect(sparm, & SauvolaControls::valueChanged,
	  this,  & MainWindow::sauvolaParametersChanged);

  image1 = NULL;
  image2 = NULL;
  integral_image = NULL;

  ivp = NULL;

  openFile();

  QVBoxLayout *boxLayout = new QVBoxLayout(box);

  ivp = new ImageViewPair(image1, image2);

  boxLayout->addWidget(ivp);
  boxLayout->addWidget(sparm);
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
  if (image1)
    {
      delete image1;
      image1 = NULL;
    }
  if (image2)
    {
      delete image2;
      image2 = NULL;
    }

  if (integral_image)
    {
      delete integral_image;
      integral_image = NULL;
    }

  image1 = new QImage(fn);

  if (ivp)
    ivp->setImage(0, image1);

  width  = image1->width();
  height = image1->height();
  pixels = ((uint64_t) width) * ((uint64_t) height);

  image2 = new QImage(width, height, QImage::Format_MonoLSB);
  image2->fill(1);  // white

  integral_image = new IntegralImage(*image1);

  do_binarize(sparm->getW(), sparm->getK());
}

void MainWindow::openFile()
{
  QString fn = QFileDialog::getOpenFileName(this, 
					     tr("Open image"),
					     ".",
					     tr("Image Files(*.png *.jpg *.bmp)"));
  loadImage(fn);
}

void MainWindow::do_binarize(int w, double k)
{
  binarize.w = w;
  binarize.k = k;
  binarize.binarize(*image1, *image2, *integral_image);

  if (ivp)
    ivp->setImage(1, image2);
}

void MainWindow::sauvolaParametersChanged(double k, int w)
{
  do_binarize(sparm->getW(), sparm->getK());
}
