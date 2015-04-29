#-------------------------------------------------
#
# Project created by QtCreator 2015-04-26T01:49:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sate_img
TEMPLATE = app


SOURCES += main.cpp\
        sate.cpp

HEADERS  += sate.h

FORMS    += sate.ui

DEPENDPATH += .
INCLUDEPATH += .
INCLUDEPATH += /usr/local/include/opencv2
LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc
