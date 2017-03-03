#-------------------------------------------------
#
# Project created by QtCreator 2017-03-02T20:37:44
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = timelapse
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Camera.cpp \
    ImageProcessor.cpp \
    CameraFrameGrabber.cpp

HEADERS  += MainWindow.h \
    Camera.h \
    ImageProcessor.h \
    CameraFrameGrabber.h

FORMS    += MainWindow.ui
