#ifndef UTCOMPUTER_H
#define UTCOMPUTER_H

#include <QMainWindow>
#include <QWidget>
#include <QMenuBar>

class Calculator;

class UTComputer : public QMainWindow
{
    Q_OBJECT
    Calculator* central;

    QAction *undoAct;
    QAction *redoAct;
    QAction *paramAct;

    QMenu* paramMenu;
    QMenu* editMenu;

    void createMenus();
    void createActions();

private slots:
    void undo();
    void redo();
    void param();

public:
    explicit UTComputer(QWidget *parent = 0);
};

#endif // UTCOMPUTER_H
