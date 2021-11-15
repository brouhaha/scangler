#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdint.h>
#include <QtGui>
#include "ImageViewPair.h"
#include "IntControl.h"
#include "SauvolaControls.h"

class MainWindow: public QMainWindow
{
  Q_OBJECT

 public:
  MainWindow ();

 private:
  QImage *image1;
  int width;
  int height;
  long pixels;

  uint64_t *ii;  // integral image
  uint64_t *i2i; // integral squared image

  QImage *image2;

  ImageViewPair *ivp;
  SauvolaControls *sparm;
  IntControl *threadCount;

  void createActions ();
  void createMenus ();

  QMenu *fileMenu;
  QAction *openAct;
  QAction *exitAct;

  QMenu *viewMenu;
  QAction *viewHAct;
  QAction *viewVAct;
  QAction *view0Act;
  QAction *view1Act;

  void loadImage (QString fn);
  void computeIntegralImages ();
  void binarize ();

 private slots:
  void openFile ();
  void viewH ();
  void viewV ();
  void view0 ();
  void view1 ();

  void sauvolaParametersChanged (double k, int w);
};

#endif
