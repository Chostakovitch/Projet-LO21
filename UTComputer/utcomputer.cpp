#include "utcomputer.h"
#include "Settings.h"
#include "calculator.h"
#include "WindowParam.h"
#include "Manager.h"
#include <QMenuBar>
#include <QtWidgets>

UTComputer::UTComputer(QWidget *parent) : QMainWindow(parent){
    central = new Calculator(this);

    setCentralWidget(central);

    createActions();
    createMenus();

    setWindowTitle(tr("Calculator"));
}

void UTComputer::undo() {
    Manager::getInstance().undo();
}
void UTComputer::redo() {
    Manager::getInstance().redo();
}

void UTComputer::param() {
    WindowParam* window = new WindowParam(central);
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

    paramAct = new QAction(tr("&Preferences"), this);
    paramAct->setShortcut(QKeySequence(tr("Ctrl+,")));
    paramAct->setStatusTip(tr("Open the preferences"));
    connect(paramAct, &QAction::triggered, this, &UTComputer::param);
}

void UTComputer::createMenus() {
    paramMenu = menuBar()->addMenu(tr("&Parameters"));
    paramMenu->addAction(paramAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
}

