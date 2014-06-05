#-------------------------------------------------
#
# Project created by QtCreator 2014-04-24T17:58:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WSN
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    EABase.cpp \
    Field.cpp \
    MOEAD.cpp \
    NSGA2.cpp \
    controller.cpp \
    dashboard.cpp \
    diagrampoint.cpp \
    diagram.cpp \
    eaworker.cpp \
    fieldsimulator.cpp \
    setdialog.cpp

HEADERS  += widget.h \
    EABase.h \
    Field.h \
    MOEAD.h \
    NSGA2.h \
    controller.h \
    dashboard.h \
    Constants.h \
    diagrampoint.h \
    diagram.h \
    eaworker.h \
    fieldsimulator.h \
    setdialog.h

FORMS    += widget.ui
