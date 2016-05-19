#include "utcomputer.h"
#include "Settings.h"
#include "calculator.h"
#include "WindowParam.h"
#include <QMenuBar>
#include <QtWidgets>

UTComputer::UTComputer(QWidget *parent) : QMainWindow(parent){
    settings = new Settings();

    central = new Calculator(this);
    menu = new QMenuBar(central);

    setCentralWidget(central);

    createActions();
    createMenus();

    setWindowTitle(tr("Calculator"));
}

void UTComputer::undo() { }
void UTComputer::redo() { }
void UTComputer::param() {
    WindowParam* window = new WindowParam();
    window->show();
}

void UTComputer::createActions() {
    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo the last operation"));
    connect(undoAct, &QAction::triggered, this, &UTComputer::undo);

    redoAct = new QAction(tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo the last operation"));
    connect(redoAct, &QAction::triggered, this, &UTComputer::redo);

    paramAct = new QAction(tr("&Parameters"), this);
    paramAct->setShortcuts(QKeySequence::Preferences);
    paramAct->setStatusTip(tr("Open the preferences"));
    connect(paramAct, &QAction::triggered, this, &UTComputer::param);
}

void UTComputer::createMenus() {
    QMenu* paramMenu = new QMenu(tr("&Parameters"));
    paramMenu->addAction(paramAct);

    QMenu* editMenu = new QMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);

    menu->addMenu(paramMenu);
    menu->addMenu(editMenu);
}

