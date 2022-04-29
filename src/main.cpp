// binarize - Sauvola binarization of images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#include <QtGui>
#include "ImageView.h"
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app (argc, argv);
    MainWindow mw;
    mw.show ();
    return app.exec();
}
