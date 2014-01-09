#-------------------------------------------------
#
# Project created by QtCreator 2014-01-08T22:59:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ACR-Launcher
TEMPLATE = app


SOURCES += main.cpp\
        launcher.cpp \
    options.cpp

HEADERS  += launcher.h \
    options.h

FORMS    += launcher.ui \
    options.ui

RESOURCES += \
    Images.qrc
