#include <QtWidgets>

#include <cmath>

#include <QVBoxLayout>
#include <QString>
#include "UTException.h"
#include "Button.h"
#include "Calculator.h"
#include "Settings.h"
#include "MainFrame.h"
#include "UTComputer.h"
#include "Manager.h"

Calculator::Calculator(QWidget *parent)  {
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QVBoxLayout *topLayout = new QVBoxLayout;

    message = new QLineEdit();
    message->setReadOnly(true);
    message->setStyleSheet("background-color:blue;");
    //connect(message, SIGNAL(returnPressed()), this, SLOT(keyPressedCommandLine()));
    topLayout->addWidget(message);

    viewPile = new QTableWidget();
    viewPile->setColumnCount(1);
    viewPile->horizontalHeader()->hide();
    //viewPile->setStyleSheet("background-color:black; color:white;");
    viewPile->setRowCount(Manager::getInstance().getSettings().getNbLinesDisplayPile());
    topLayout->addWidget(viewPile);
    refreshPile();


    command = new QLineEdit();
    topLayout->addWidget(command);

    keyBoard = new MainFrame(this);
    keyBoard->setVisible(Manager::getInstance().getSettings().getDisplayKeyboard());

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(keyBoard);

    setLayout(mainLayout);

}

void Calculator::addDigitToCommand() {
    Button *clickedButton = qobject_cast<Button *>(sender());
    command->setText(command->text() + clickedButton->text());
}

void Calculator::addSpaceToCommand() {
    command->setText(command->text() + " ");
}

void Calculator::backspaceToCommand() {
    std::string newCommand = command->text().toStdString();
    newCommand.pop_back();
    command->setText(QString::fromStdString(newCommand));
}

void Calculator::displayKeyboardChanged(int newValue) {
    Manager::getInstance().getSettings().setDisplayKeyboard(newValue);
    keyBoard->setVisible(Manager::getInstance().getSettings().getDisplayKeyboard());
}

void Calculator::nbLineDisplayPileChanged(int newValue) {
    Manager::getInstance().getSettings().setNbLinesDisplayPile(newValue);
    viewPile->setRowCount(Manager::getInstance().getSettings().getNbLinesDisplayPile());
    refreshPile();
}

void Calculator::addOperatorToCommand() {
    Button *clickedButton = qobject_cast<Button *>(sender());
    command->setText(command->text() +" "+ clickedButton->text());
    calculate();
}

void Calculator::calculate() {
    try {
        Manager::getInstance().handleOperandLine(command->text().toStdString());
        message->setText(QString());
        command->setText(QString());
    } catch (UTException e) {
        message->setText(QString::fromStdString(e.what()));
    }
    refreshPile();
}

void Calculator::refreshPile() {
    std::vector<std::string> pile = Manager::getInstance().getPileToString();
    unsigned int rowCount = Manager::getInstance().getSettings().getNbLinesDisplayPile() > pile.size() ?
                pile.size() : Manager::getInstance().getSettings().getNbLinesDisplayPile();
    for(unsigned int i=0; i < rowCount; i++)
    {
        QTableWidgetItem* newItem = new QTableWidgetItem(QString::fromStdString(pile[i]));
        viewPile->setItem(i, 0, newItem);
    }
    for(unsigned int i=rowCount; i < Manager::getInstance().getSettings().getNbLinesDisplayPile(); i++)
    {
        viewPile->takeItem(i,0);
    }
}

