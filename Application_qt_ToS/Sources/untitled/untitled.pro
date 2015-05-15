#-------------------------------------------------
#
# Project created by QtCreator 2015-04-30T18:32:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app

LIBS += -lpng12


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    Tree.h \
    Tree.hpp \
    Span.hpp \
    Span.h \
    Node.hpp \
    Node.h \
    ImageInterpolate.hpp \
    ImageInterpolate.h \
    Image.hpp \
    Image.h

FORMS    += mainwindow.ui
