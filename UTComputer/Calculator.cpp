#include <QtWidgets>

#include <cmath>

#include <QVBoxLayout>
#include "Button.h"
#include "Calculator.h"
#include "Settings.h"
#include "MainFrame.h"
#include "utcomputer.h"

Calculator::Calculator(QWidget *parent)  {
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QVBoxLayout *topLayout = new QVBoxLayout;

    message = new QLineEdit();
    message->setReadOnly(true);
    message->setStyleSheet("background-color:blue;");
    topLayout->addWidget(message);

    viewPile = new QTableWidget();
    viewPile->setRowCount(dynamic_cast<UTComputer*>(parent)->getSettings()->getNbLinesDisplayPile());
    viewPile->setStyleSheet("background-color:black; color:white;");
    topLayout->addWidget(viewPile);

    command = new QLineEdit();
    topLayout->addWidget(command);

    mainFrame = new MainFrame();

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(mainFrame);

    setLayout(mainLayout);
}

