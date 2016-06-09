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
    QAction *saveAct;
    QAction *loadAct;
    QAction *historyAct;

    QMenu* paramMenu;
    QMenu* editMenu;

    void createMenus();
    void createActions();

private slots:
    void undo();
    void redo();
    void param();
    void save();
    void load();
    void history();
public:
    explicit UTComputer(QWidget *parent = 0);
    Calculator* getCalculator() { return central; }
    static int const EXIT_CODE_REBOOT;
    ~UTComputer() { save(); }
};

#endif // UTCOMPUTER_H
