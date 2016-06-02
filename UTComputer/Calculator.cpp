#include <QtWidgets>
#include "OperatorManager.h"
#include <cmath>
#include "WindowException.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
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

    QHBoxLayout* errorLayout = new QHBoxLayout();
    message = new QTextEdit();
    message->setReadOnly(true);
    message->setStyleSheet("color:red;");
    message->setMinimumHeight(60);
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

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(keyBoard);

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
        if (OperatorManager::getInstance().isOperator(keyEvent->text().toStdString())) {
            command->setText(command->text()+keyEvent->text());
            calculate();
            return true;
        }
        if (keyEvent->key() == Qt::Key_Return) {
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
    viewPile->setRowCount(Manager::getInstance().getSettings().getNbLinesDisplayPile());
    refreshPile();
}

void Calculator::addOperatorToCommand() {
    Button *clickedButton = qobject_cast<Button *>(sender());
    command->setText(command->text() +" "+ clickedButton->text());
    command->setFocus();
    calculate();
}

void Calculator::calculate() {
    try {
        Manager::getInstance().handleOperandLine(command->text().toStdString());
        deleteMessage();
        command->setText(QString());
    } catch (UTException e) {
        setMessage(e);
    }
    refreshPile();
}

void Calculator::setMessage(const UTException& e) {
    //if (Manager::getInstance().getSettings().getBeepMessage()) QApplication::beep();
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

