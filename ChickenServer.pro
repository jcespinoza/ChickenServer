#-------------------------------------------------
#
# Project created by QtCreator 2013-03-01T10:19:22
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChickenServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    server.cpp \
    connection.cpp

HEADERS  += mainwindow.h \
    server.h \
    connection.h

FORMS    += mainwindow.ui \

RESOURCES += \
