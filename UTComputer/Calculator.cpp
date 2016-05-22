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
    viewPile->setRowCount(10);
    viewPile->setStyleSheet("background-color:black; color:white;");
    topLayout->addWidget(viewPile);

    command = new QLineEdit();
    topLayout->addWidget(command);

    keyBoard = new MainFrame();
    //keyBoard->hide();

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(keyBoard);

    setLayout(mainLayout);
}

