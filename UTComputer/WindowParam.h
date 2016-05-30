#ifndef WINDOWPARAM_H
#define WINDOWPARAM_H

#include <QWindow>
#include <QWidget>
#include <QTableWidget>

class WindowParam;

class ParamTab : public QWidget
{
    Q_OBJECT
public:
    ParamTab(QWidget* parent = 0);
};

class VariableTab : public QWidget
{
    Q_OBJECT
    QTableWidget *viewVariable;
public slots:
    void deleteIdentifier();
public:
    VariableTab(WindowParam* parent = 0);
    void refresh();
};

class ProgramTab : public QWidget
{
    Q_OBJECT
    QTableWidget *viewProgram;
public slots:
    void deleteIdentifier();
public:
    ProgramTab(WindowParam* parent = 0);
    void refresh();
};

class WindowParam : public QWidget
{
    Q_OBJECT
    ParamTab *paramTab;
    VariableTab *variableTab;
    ProgramTab *programTab;
public slots:
    void quit();
public:
    WindowParam(QWidget* parent = 0);
};

#endif // WINDOWPARAM_H
