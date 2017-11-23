#-------------------------------------------------
#
# Project created by QtCreator 2017-11-23T00:13:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RealMultiDevice
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    stdafx.h \
    CommonFunctions.h

FORMS    += mainwindow.ui \
    targetpath.ui

win32:LIBS += -lole32

win32: LIBS += -L$$PWD/'../../../../../Program Files (x86)/Windows Kits/10/Lib/10.0.15063.0/um/x64/' -lPortableDeviceGuids

INCLUDEPATH += $$PWD/'../../../../../Program Files (x86)/Windows Kits/10/Lib/10.0.15063.0/um/x64'
DEPENDPATH += $$PWD/'../../../../../Program Files (x86)/Windows Kits/10/Lib/10.0.15063.0/um/x64'
