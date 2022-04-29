TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

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
LIBS += -lqwt5-qt4
