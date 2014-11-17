#-------------------------------------------------
#
# Project created by QtCreator 2014-07-22T20:48:43
#
#-------------------------------------------------

QT       += core gui webkit network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AC-R-Launcher
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mainworker.cpp \
    configdata.cpp \
    serverconsole.cpp \
    downloaddialog.cpp \
    modlistdownloader.cpp \
    modinstalldialog.cpp

HEADERS  += mainwindow.h \
    mainworker.h \
    configdata.h \
    serverconsole.h \
    downloaddialog.h \
    modlistdownloader.h \
    modinstalldialog.h

FORMS    += mainwindow.ui \
    serverconsole.ui \
    downloaddialog.ui \
    modinstalldialog.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../quazip/release/ -lquazip
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../quazip/debug/ -lquazip
else:unix: LIBS += -L$$PWD/../quazip/ -lquazip

INCLUDEPATH += $$PWD/../quazip
DEPENDPATH += $$PWD/../quazip
