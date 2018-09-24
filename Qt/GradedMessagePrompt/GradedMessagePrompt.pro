#-------------------------------------------------
#
# Project created by QtCreator 2018-08-21T12:36:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GradedMessagePrompt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    src/Bubble.cpp

INCLUDEPATH += src \

HEADERS  += mainwindow.h \
    src/Bubble.h

FORMS   += mainwindow.ui
