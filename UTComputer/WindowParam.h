#ifndef WINDOWPARAM_H
#define WINDOWPARAM_H

#include <QWindow>
#include <QWidget>

class WindowParam : public QWidget
{
    Q_OBJECT
public:
    WindowParam(QWidget* parent = 0);
};

class ParamTab : public QWidget
{
    Q_OBJECT
public:
    ParamTab(QWidget* parent = 0);
};

class VariableTab : public QWidget
{
    Q_OBJECT
public:
    VariableTab(QWidget* parent = 0);
};

class ProgramTab : public QWidget
{
    Q_OBJECT
public:
    ProgramTab(QWidget* parent = 0);
};

#endif // WINDOWPARAM_H
