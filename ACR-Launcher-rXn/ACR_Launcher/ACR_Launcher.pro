#-------------------------------------------------
#
# Project created by QtCreator 2014-06-13T22:01:13
#
#-------------------------------------------------

QT       += core gui network webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ACR_Launcher
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mainworker.cpp \
    downloader.cpp

HEADERS  += mainwindow.h \
    mainworker.h \
    downloader.h

FORMS    += mainwindow.ui
