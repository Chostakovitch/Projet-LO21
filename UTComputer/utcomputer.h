#ifndef UTCOMPUTER_H
#define UTCOMPUTER_H

#include <QMainWindow>
#include <QWidget>
#include <QMenuBar>

class Settings;
class Manager;

class UTComputer : public QMainWindow
{
    Q_OBJECT
    Manager* manager;
    Settings* settings;

    QWidget* central;
    QMenuBar *menu;

    QAction *undoAct;
    QAction *redoAct;
    QAction *paramAct;

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
