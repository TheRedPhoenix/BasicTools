#-------------------------------------------------
#
# Project created by QtCreator 2017-07-17T21:32:32
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UdpSender
TEMPLATE = app


SOURCES += main.cpp\
    udpsender.cpp \
    networkwidget.cpp

HEADERS  += \
    udpsender.h \
    networkwidget.h

FORMS += \
    networkwidget.ui
