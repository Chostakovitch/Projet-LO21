#include <QtWidgets>
#include <iostream>
#include <sstream>
#include "OperatorManager.h"
#include <cmath>
#include "WindowException.h"
#include "WindowParam.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSound>
#include <QString>
#include "UTException.h"
#include "Button.h"
#include "Calculator.h"
#include "Settings.h"
#include "MainFrame.h"
#include "UTComputer.h"
#include "Manager.h"

Calculator::Calculator(QWidget *parent)  {
    QHBoxLayout *mainLayout = new QHBoxLayout;

    QVBoxLayout *rightLayout = new QVBoxLayout;
    QVBoxLayout *topLayout = new QVBoxLayout;

    QHBoxLayout* errorLayout = new QHBoxLayout();
    message = new QTextEdit();
    message->setReadOnly(true);
    message->setStyleSheet("color:red;");
    message->setMaximumHeight(60);
    errorLayout->addWidget(message);
    QPushButton* detailErrorButton = new QPushButton("More");
    connect(detailErrorButton, SIGNAL(clicked(bool)), this, SLOT(openDetailErrorWindow()));
    errorLayout->addWidget(detailErrorButton);

    topLayout->addLayout(errorLayout);

    viewPile = new QTableWidget();
    viewPile->setEditTriggers(QAbstractItemView::NoEditTriggers);
    viewPile->setColumnCount(1);
    viewPile->horizontalHeader()->hide();
    viewPile->horizontalHeader()->setStretchLastSection(true);
    //viewPile->setStyleSheet("background-color:black; color:white;");
    viewPile->setRowCount(Manager::getInstance().getSettings().getNbLinesDisplayPile());
    topLayout->addWidget(viewPile);
    refreshPile();


    command = new QLineEdit();
    command->installEventFilter(this);
    //connect(command, SIGNAL(cursorPositionChanged(int,int)), this, SLOT())
    topLayout->addWidget(command);

    keyBoard = new MainFrame(this);
    keyBoard->setVisible(Manager::getInstance().getSettings().getDisplayKeyboard());

    rightLayout->addLayout(topLayout);
    rightLayout->addWidget(keyBoard);

    //mainLayout->addLayout(operatorsLayout,10);
    mainLayout->addLayout(rightLayout);

    setLayout(mainLayout);
}

bool Calculator::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        command->setCursorPosition(command->text().size());
        return true;
    }
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Right || keyEvent->key() == Qt::Key_Left) return true;
        std::string commandStr = command->text().toStdString();
        //Opérateur arithmétique (un caractère) et guillemets fermés s'ils existent
        if (OperatorManager::getInstance().isArithmeticOperator(keyEvent->text().toStdString())
                && std::count(commandStr.begin(), commandStr.end(), '"') % 2 == 0
                && (std::count(commandStr.begin(), commandStr.end(), '[') + std::count(commandStr.begin(), commandStr.end(), ']')) % 2 == 0) {
            command->setText(command->text()+ QString(" ") + keyEvent->text());
            calculate();
            return true;
        }
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
            calculate();
            return true;
        }
        return false;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}

void Calculator::openDetailErrorWindow() {
    WindowException* window = new WindowException(messageDetail);
    window->show();
}

void Calculator::openMoreOperatorsWindow() {
    WindowMoreOperators* window = new WindowMoreOperators(this);
    window->show();
}

void Calculator::addDigitToCommand() {
    Button *clickedButton = qobject_cast<Button *>(sender());
    command->setText(command->text() + clickedButton->text());
    command->setFocus();
}

void Calculator::addSpaceToCommand() {
    command->setText(command->text() + " ");
    command->setFocus();
}

void Calculator::backspaceToCommand() {
    if(command->text().size() > 0) {
        std::string newCommand = command->text().toStdString();
        newCommand.pop_back();
        command->setText(QString::fromStdString(newCommand));
    }
    command->setFocus();
}

void Calculator::displayKeyboardChanged(int newValue) {
    Manager::getInstance().getSettings().setDisplayKeyboard(newValue);
    keyBoard->setVisible(Manager::getInstance().getSettings().getDisplayKeyboard());
}

void Calculator::nbLineDisplayPileChanged(int newValue) {
    Manager::getInstance().getSettings().setNbLinesDisplayPile(newValue);
    viewPile->setRowCount(newValue);
    refreshPile();
}

void Calculator::beepMessageChanged(int newValue) {
    Manager::getInstance().getSettings().setBeepMessage(newValue);
}

void Calculator::addOperatorToCommand() {
    Button *clickedButton = qobject_cast<Button *>(sender());
    command->setText(command->text() +" "+ clickedButton->text());
    command->setFocus();
    calculate();
}

void Calculator::calculate() {
    try {
        std::string commandString = command->text().toStdString();
        std::string word, previousWord;
        std::istringstream iss(commandString);
        while(iss >> word) {
            if (word == "EDIT") {
                if (previousWord.empty()) throw ParsingError(commandString,"EDIT must have an identifier.");
                WindowEditIdentifier* window = new WindowEditIdentifier(previousWord);
                connect(window, SIGNAL(destroyed(QObject*)),this,SLOT(calculate()));
                std::string rest;
                std::getline(iss, rest);
                command->setText(QString::fromStdString(rest));
                window->show();
                return;
            }
            previousWord = word;
        }
        Manager::getInstance().handleOperandLine(commandString);
        deleteMessage();
        command->setText(QString());
    } catch (UTException e) {
        setMessage(e);
    }
    refreshPile();
}

void Calculator::setMessage(const UTException& e) {
    if (Manager::getInstance().getSettings().getBeepMessage()) QSound::play("/Users/aureliedigeon/Documents/UTC/P16/LO21/Projet-LO21/sound.wav");
    message->setText(QString::fromStdString(e.what()));
    messageDetail = e.details();
}

void Calculator::deleteMessage() {
    message->setText(QString());
    messageDetail = "";
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

