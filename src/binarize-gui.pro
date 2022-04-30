# binarize - Sauvola binarization of images
# Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
# SPDX-License-Identifier: GPL-3.0-only

TEMPLATE = app
TARGET = binarize-gui
DEPENDPATH += .
INCLUDEPATH += .

QT += widgets

# Input
HEADERS += ImageView.h ImageViewPair.h \
	IntControl.h DoubleControl.h \
        SauvolaControls.h \
	MainWindow.h
SOURCES += ImageView.cpp ImageViewPair.cpp \
	IntControl.cpp DoubleControl.cpp \
        SauvolaControls.cpp \
	MainWindow.cpp \
	main.cpp
LIBS += -lqwt-qt5
