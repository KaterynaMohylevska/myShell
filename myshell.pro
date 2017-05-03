#-------------------------------------------------
#
# Project created by QtCreator 2017-04-01T11:09:29
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = myshell
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11

TEMPLATE = app
LIBS += -L/usr/lib/x86_64-linux-gnu -lboost_system
LIBS += -lboost_system -lboost_filesystem


SOURCES += main.cpp \
    mkdir.cpp \
    ls.cpp \
    ls_detailed.cpp \
    remove.cpp

HEADERS += \
    mkdir.h \
    ls.h \
    ls_detailed.h \
    remove.h
