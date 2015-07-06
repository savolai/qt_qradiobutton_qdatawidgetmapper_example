#-------------------------------------------------
#
# Project created by QtCreator 2015-06-24T14:21:01
#
#-------------------------------------------------

QT       += core gui sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qradiobutton_qdatawidgetmapper_example
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    buttongroup.cpp \
    radiobuttondelegate.cpp

HEADERS  += mainwindow.h \
    buttongroup.h \
    radiobuttondelegate.h

FORMS    += mainwindow.ui
