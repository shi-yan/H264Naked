#-------------------------------------------------
#
# Project created by QtCreator 2015-04-20T17:28:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = H264Naked
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    H264NALListModel.cpp

HEADERS  += MainWindow.h \
    H264NALListModel.h

FORMS    += mainwindow.ui

macx:INCLUDEPATH += /usr/local/include
macx: LIBS += -L/usr/local/lib \
              -lh264bitstream
macx:ICON = H264Naked.icns

unix:!macx: LIBS += -lh264bitstream
unix:!macx: QMAKE_LFLAGS += '-Wl,-rpath=\'\$$ORIGIN\''


