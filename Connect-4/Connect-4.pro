#-------------------------------------------------
#
# Project created by QtCreator 2018-05-17T13:52:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Connect-4
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        mainwindow.cpp\
    fields.cpp

HEADERS  += mainwindow.h\
    fields.h

FORMS    += mainwindow.ui

RESOURCES += \
    grafika/slike.qrc

DISTFILES += \
    grafika/bboard.png
