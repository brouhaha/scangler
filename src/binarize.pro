# binarize - Sauvola binarization of images
# Copyright 2012, 2022 Eric Smith <spacewar@gmail.com
# SPDX-License-Identifier: GPL-3.0-only

TEMPLATE = app
TARGET = binarize
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += debug

QT += widgets

# Input
HEADERS += ImageView.h ImageViewPair.h \
	IntegralImage.h \
        Binarize.h BinarizeSauvola.h \
	DoubleSlider.h \
        IntControl.h DoubleControl.h \
        ScaleControl.h \
        SauvolaControls.h \
        Images.h \
	MainWindow.h
SOURCES += ImageView.cpp ImageViewPair.cpp \
	IntegralImage.cpp \
        BinarizeSauvola.cpp \
	DoubleSlider.cpp \
        IntControl.cpp DoubleControl.cpp \
        ScaleControl.cpp \
        SauvolaControls.cpp \
        MainWindow.cpp \
        Images.cpp \
	main.cpp
