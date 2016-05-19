#ifndef WINDOWPARAM_H
#define WINDOWPARAM_H

#include <QWindow>
#include <QWidget>

class WindowParam : public QWidget
{
public:
    WindowParam(QWidget* parent = 0);
};

class ParamTab : public QWidget
{
public:
    ParamTab(QWidget* parent = 0);
};

class VariableTab : public QWidget
{
public:
    VariableTab(QWidget* parent = 0);
};

class ProgramTab : public QWidget
{
public:
    ProgramTab(QWidget* parent = 0);
};

#endif // WINDOWPARAM_H
