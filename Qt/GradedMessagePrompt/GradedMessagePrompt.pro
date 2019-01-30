#-------------------------------------------------
#
# Project created by QtCreator 2018-08-21T12:36:21
#
#-------------------------------------------------

QT       += core gui network qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GradedMessagePrompt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    src/Bubble.cpp \
    src/TCP/TCPLink.cpp \
    src/TCP/TCPServer.cpp

INCLUDEPATH += src \
        src/TCP \

HEADERS  += mainwindow.h \
    src/Bubble.h \
    src/TCP/TCPLink.h \
    src/TCP/TCPServer.h

FORMS   += mainwindow.ui
