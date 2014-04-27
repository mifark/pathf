#-------------------------------------------------
#
# Project created by QtCreator 2014-03-05T10:48:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = graphics
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    universescene.cpp \
    maploader.cpp

HEADERS  += mainwindow.h \
    universescene.h \
    maploader.h \
    names.h \
    nodes.h

FORMS    += mainwindow.ui
