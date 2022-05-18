// binarize - Sauvola binarization of images
// Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
// SPDX-License-Identifier: GPL-3.0-only

#include <QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app (argc, argv);

    QCommandLineParser parser;
    parser.addPositionalArgument("source", QCoreApplication::translate("main", "source image"));
    //parser.addPositionalArgument("destination", QCoreApplication::translate("main", "destination image"));

    parser.addOptions({
        {{"b", "batch"},
	 QCoreApplication::translate("main", "batch process file (no GUI).")},
      });

    parser.process(app);

    bool batch = parser.isSet("batch");

    if (batch)
      {
	QString source_image = parser.positionalArguments()[0];
      }
    else
      {
	MainWindow mw;
	mw.show ();
	return app.exec();
      }

}
