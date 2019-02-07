#-------------------------------------------------
#
# Project created by QtCreator 2019-02-06T22:57:29
#
#-------------------------------------------------

QT       += core gui

-std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projectpoints
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imageview.cpp

HEADERS  += mainwindow.h \
    imageview.h

FORMS    += mainwindow.ui
