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
    Literal.cpp \
    LiteralFactory.cpp \
    Operateurs.cpp \
    Operation.cpp \
    OperatorManager.cpp \
    Utility.cpp \
    Calculator.cpp \
    Button.cpp \
    MainFrame.cpp \
    CompositeLiteral.cpp \
    Settings.cpp \
    ExpressionParser.cpp \
    Manager.cpp \
    WindowParam.cpp \
    Pile.cpp \
    UTException.cpp \
    UTComputer.cpp

HEADERS  += \
    Literal.h \
    LiteralFactory.h \
    Operateurs.h \
    Operation.h \
    OperatorManager.h \
    Utility.h \
    Calculator.h \
    Button.h \
    Settings.h \
    MainFrame.h \
    CompositeLiteral.h \
    Settings.h \
    ExpressionParser.h \
    Manager.h \
    WindowParam.h \
    Pile.h \
    UTException.h \
    UTComputer.h \
    TypeList.h

FORMS    += utcomputer.ui
