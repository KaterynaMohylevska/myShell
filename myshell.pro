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
LIBS += -L/usr/lib/x86_64-linux-gnu -lboost_regex
LIBS += -lboost_regex


SOURCES += main.cpp \
    mkdir.cpp \
    ls.cpp \
    ls_detailed.cpp \
    remove.cpp \
    cp.cpp \
    copy_files.cpp \
    rename.cpp \
    move.cpp \
    sort_name.cpp \
    sort_time.cpp \
    sort_size.cpp \
    sort_type.cpp

HEADERS += \
    mkdir.h \
    ls.h \
    ls_detailed.h \
    remove.h \
    cp.h \
    copy_files.h \
    rename.h \
    move.h \
    sort_name.h \
    sort_size.h \
    sort_time.h \
    sort_type.h
