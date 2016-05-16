#include <QtWidgets>

#include <cmath>

#include <QVBoxLayout>
#include "Button.h"
#include "Calculator.h"
#include "Settings.h"
#include "MainFrame.h"

Calculator::Calculator(QWidget *parent) {
    settings = new Settings();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QVBoxLayout *topLayout = new QVBoxLayout;

    message = new QLineEdit();
    message->setReadOnly(true);
    message->setStyleSheet("background-color:blue;");
    topLayout->addWidget(message);

    viewPile = new QTableWidget();
    topLayout->addWidget(viewPile);

    command = new QLineEdit();
    topLayout->addWidget(command);

    mainFrame = new MainFrame();

    mainLayout->addWidget(mainFrame);
    mainLayout->addLayout(topLayout);

    setLayout(mainLayout);
    setWindowTitle(tr("Calculator"));
}

