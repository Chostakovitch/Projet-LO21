#include <QtWidgets>

#include <cmath>

#include <QVBoxLayout>
#include <QString>
#include "Button.h"
#include "Calculator.h"
#include "Settings.h"
#include "MainFrame.h"
#include "utcomputer.h"
#include "Manager.h"

Calculator::Calculator(QWidget *parent)  {
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QVBoxLayout *topLayout = new QVBoxLayout;

    message = new QLineEdit();
    message->setReadOnly(true);
    message->setStyleSheet("background-color:blue;");
    topLayout->addWidget(message);

    viewPile = new QTableWidget();
    viewPile->setRowCount(Manager::getInstance().getSettings().getNbLinesDisplayPile());
    viewPile->setStyleSheet("background-color:black; color:white;");
    /*std::vector<std::string> pile = Manager::getInstance().getPileToString();
    unsigned int rowCount = Manager::getInstance().getSettings()->getNbLinesDisplayPile() > pile.size() ?
                pile.size() : Manager::getInstance().getSettings()->getNbLinesDisplayPile();
    for(int i=0; i< rowCount; i++)
    {
        std::shared_ptr<QTableWidgetItem> newItem = std::shared_ptr<QTableWidgetItem>(new QTableWidgetItem(QString::fromStdString(pile[i])));
        viewPile->setItem(i, 0, newItem.get());
    }*/
    topLayout->addWidget(viewPile);

    command = new QLineEdit();
    topLayout->addWidget(command);

    keyBoard = new MainFrame();
    keyBoard->setVisible(Manager::getInstance().getSettings().getDisplayKeyboard());

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(keyBoard);

    setLayout(mainLayout);
}

void Calculator::refresh() {
    viewPile->setRowCount(Manager::getInstance().getSettings().getNbLinesDisplayPile());
    keyBoard->setVisible(Manager::getInstance().getSettings().getDisplayKeyboard());

    // Refresh viewPile

}

