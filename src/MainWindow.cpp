// binarize - Sauvola binarization of images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#include "MainWindow.h"

MainWindow::MainWindow ()
{
  QWidget *box = new QWidget (this);
  sparm = new SauvolaControls (0.2, 30, box);

  connect (sparm,
	   SIGNAL (valueChanged (double, int)),
	   this,
	   SLOT (sauvolaParametersChanged (double, int)));

  image1 = NULL;
  image2 = NULL;
  ii  = NULL;
  i2i = NULL;

  ivp = NULL;

  openFile ();

  QVBoxLayout *boxLayout = new QVBoxLayout (box);

  ivp = new ImageViewPair (image1, image2);

  int tc = QThread::idealThreadCount ();
  if (tc < 1)
    tc = 1;
  threadCount = new IntControl (1, 4 * tc, tc, "thread count", box);

  boxLayout->addWidget (ivp);
  boxLayout->addWidget (sparm);
  boxLayout->addWidget (threadCount);
  box->setLayout (boxLayout);

  setCentralWidget (box);

  createActions ();
  createMenus ();
}

void MainWindow::createActions ()
{
  openAct = new QAction (tr ("&Open"), this);
  connect (openAct, SIGNAL (triggered ()), this, SLOT (openFile ()));

  exitAct = new QAction (tr ("&Exit"), this);
  connect (exitAct, SIGNAL (triggered ()), this, SLOT (close ()));

  viewHAct = new QAction (tr ("&Horizontal"), this);
  connect (viewHAct, SIGNAL (triggered ()), this, SLOT (viewH ()));

  viewVAct = new QAction (tr ("&Vertical"), this);
  connect (viewVAct, SIGNAL (triggered ()), this, SLOT (viewV ()));

  view0Act = new QAction (tr ("&Greyscale only"), this);
  connect (view0Act, SIGNAL (triggered ()), this, SLOT (view0 ()));

  view1Act = new QAction (tr ("&Binarized only"), this);
  connect (view1Act, SIGNAL (triggered ()), this, SLOT (view1 ()));
}

void MainWindow::createMenus ()
{
  fileMenu = menuBar ()->addMenu (tr ("&File"));
  fileMenu->addAction (openAct);
  fileMenu->addAction (exitAct);

  viewMenu = menuBar ()->addMenu (tr ("&View"));
  viewMenu->addAction (viewHAct);
  viewMenu->addAction (viewVAct);
  viewMenu->addAction (view0Act);
  viewMenu->addAction (view1Act);
}

void MainWindow::viewH ()
{
  ivp->setOrientation (ImageViewPair::Horizontal);
}

void MainWindow::viewV ()
{
  ivp->setOrientation (ImageViewPair::Vertical);
}

void MainWindow::view0 ()
{
  ivp->setOrientation (ImageViewPair::Only0);
}

void MainWindow::view1 ()
{
  ivp->setOrientation (ImageViewPair::Only1);
}

void MainWindow::loadImage (QString fn)
{
  if (image1)
    {
      // $$$ dispose image
      image1 = NULL;
    }
  if (image2)
    {
      // $$$ dispose image
      image2 = NULL;
    }

  if (ii)
    {
      delete [] ii;
      ii = NULL;
    }

  if (i2i)
    {
      delete [] i2i;
      i2i = NULL;
    }

  image1 = new QImage(fn);

  if (ivp)
    ivp->setImage (0, image1);

  width  = image1->width ();
  height = image1->height ();
  pixels = ((long) width) * ((long) height);

  image2 = new QImage (width, height, QImage::Format_MonoLSB);
  image2->fill (1);  // white

  ii  = new uint64_t [pixels];
  i2i = new uint64_t [pixels];

  computeIntegralImages ();
  binarize ();
}

void MainWindow::openFile ()
{
  QString fn = QFileDialog::getOpenFileName (this, 
					     tr ("Open image"),
					     ".",
					     tr ("Image Files (*.png *.jpg *.bmp)"));
  loadImage (fn);
}

void MainWindow::computeIntegralImages ()
{
  // handle y=0
  int rs = 0;
  int rs2 = 0;
  for (int x = 0; x < width; x++)
    {
      uint32_t pixel = image1->pixel (x, 0) & 0xff;
      uint32_t pixel2 = pixel * pixel;
      rs += pixel;
      rs2 += pixel2;
      ii [x] = rs;
      i2i [x] = rs2;
    }

  // handle y>0
  for (int y = 1; y < height; y++)
    {
      long row_base = y * width;
      rs = 0;
      rs2 = 0;
      for (int x = 0; x < width; x++)
	{
	  uint32_t pixel = image1->pixel (x, y) & 0xff;
	  uint32_t pixel2 = pixel * pixel;
	  rs += pixel;
	  rs2 += pixel2;
	  ii [row_base + x] = rs + ii [row_base - width + x];
	  i2i [row_base + x]= rs2 + i2i [row_base - width + x];
	}
    }
}

void MainWindow::binarize ()
{
  int w = sparm->getW ();
  double k = sparm->getK ();

  for (int y = 0; y < height; y++)
    {
      int y_min, y_max;

      if (y < (w / 2))
	y_min = 0;
      else
	y_min = y - w / 2;
      if ((y + (w / 2)) >= height)
	y_max = height - 1;
      else
	y_max = y + w / 2;

      uint32_t y_min_m_1_base = (y_min - 1) * width;
      uint32_t y_max_base = y_max * width;

      uint8_t *bitmap_line = image2->scanLine (y);

      for (int x = 0; x < width; x++)
	{
	  int x_min, x_max;
	  if (x < (w / 2))
	    x_min = 0;
	  else
	    x_min = x - (w / 2);
	  if ((x + (w / 2)) >= width)
	    x_max = width - 1;
	  else
	    x_max = x + w / 2;

	  double area = ((double) (x_max + 1 - x_min)) * ((double) (y_max + 1 - y_min));
	  double sum, sum_sq;

	  if (y_min == 0)
	    if (x_min == 0)
	      {
		// upper left corner
		sum = ii [x_max + y_max_base];
		sum_sq = i2i [x_max + y_max_base];
	      }
	    else
	      {
		// top row
		sum = ii [x_max + y_max_base] - ii [(x_min - 1) + y_max_base];
		sum_sq = i2i [x_max + y_max_base] - i2i [(x_min - 1) + y_max_base];
	      }
	  else
	    if (x_min == 0)
	      {
		// leftmost column
		sum = ii [x_max + y_max_base] - ii [x_max + y_min_m_1_base];
		sum_sq = i2i [x_max + y_max_base] - i2i [x_max + y_min_m_1_base];
	      }
	    else
	      {
		// anywhere else
		long diag1 = ii [x_max + y_max_base] + 
		  ii [(x_min - 1) + y_min_m_1_base];
		long diag2 = ii [x_max + y_min_m_1_base] +
		  ii [(x_min - 1) + y_max_base];
		sum = diag1 - diag2;
		long diagsq1 = i2i [x_max + y_max_base] + 
		  i2i [(x_min - 1) + y_min_m_1_base];
		long diagsq2 = i2i [x_max + y_min_m_1_base] +
		  i2i [(x_min - 1) + y_max_base];
		sum_sq = diagsq1 - diagsq2;
	      }

	  double mean = sum / area;
	  double variance = (sum_sq - sum * sum / area) / (area - 1);
	  double std_dev = sqrt (variance);

	  double threshold = mean * (1 + k * ((std_dev / 128) - 1));

	  if ((image1->pixel (x, y) & 0xff) < threshold)
	    bitmap_line [x / 8] &= ~ (1 << (x & 7));
	  else
	    bitmap_line [x / 8] |= (1 << (x & 7));
	}
    }

  if (ivp)
    ivp->setImage (1, image2);
}

void MainWindow::sauvolaParametersChanged (double k, int w)
{
  binarize ();
}
