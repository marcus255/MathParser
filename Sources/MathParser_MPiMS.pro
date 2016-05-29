#-------------------------------------------------
#
# Project created by QtCreator 2016-05-02T19:32:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MathParser_MPiMS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    TChar.cpp \
    TParser.cpp \
    TList.cpp

HEADERS  += mainwindow.h \
    TChar.h \
    TList.h \
    TParser.h

FORMS    += mainwindow.ui

CONFIG+= static