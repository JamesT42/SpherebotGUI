#-------------------------------------------------
#
# Project created by QtCreator 2014-04-02T13:40:23
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpherebotGUI
TEMPLATE = app


SOURCES += main.cpp\
        spheregui.cpp \
    spherebot.cpp

HEADERS  += spheregui.h \
    spherebot.h

FORMS    += spheregui.ui
