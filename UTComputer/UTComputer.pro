#-------------------------------------------------
#
# Project created by QtCreator 2016-05-11T15:45:07
#
#-------------------------------------------------

QT       += core gui
CONFIG   -= x86_64

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UTComputer
TEMPLATE = app


SOURCES += main.cpp\
        utcomputer.cpp \
    Literal.cpp \
    LiteralFactory.cpp \
    Operateurs.cpp \
    Operation.cpp \
    OperatorManager.cpp \
    Utility.cpp \
    Calculator.cpp \
    Button.cpp \
    Settings.cpp
    CompositeLiteral.cpp

HEADERS  += utcomputer.h \
    Literal.h \
    LiteralFactory.h \
    Operateurs.h \
    Operation.h \
    OperatorManager.h \
    Utility.h \
    Calculator.h \
    Button.h \
    Settings.h
    CompositeLiteral.h

FORMS    += utcomputer.ui
