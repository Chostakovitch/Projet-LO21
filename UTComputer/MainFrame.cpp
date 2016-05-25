#include "MainFrame.h"
#include "Button.h"
#include "OperatorManager.h"
#include "Manager.h"
#include <QGridLayout>

MainFrame::MainFrame(QWidget *parent) : QFrame(parent) {

    // Creation des boutons
    for (int i = 0; i < NumDigitButtons; ++i) {
        digitButtons[i] = new Button(QString::number(i));
    }
    Button *pointButton = createButton(tr("."), SLOT(pointClicked()));

    // Ajout dans le Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QGridLayout *digitLayout = new QGridLayout;
    QGridLayout *opeartorLayout = new QGridLayout;

    for (int i = 1; i < NumDigitButtons; ++i) {
        int row = ((9 - i) / 3) + 2;
        int column = ((i - 1) % 3) + 1;
        digitLayout->addWidget(digitButtons[i], row, column);
    }
    digitLayout->addWidget(pointButton, 5, 1);
    digitLayout->addWidget(digitButtons[0], 5, 2);

    std::vector<std::string> symbolicOperators = Manager::getInstance().getSymbolicOperatorToString();
    unsigned int count = 0;
    for(auto o : symbolicOperators) {
        Button* operatorButton = new Button(QString::fromStdString(o));
        int row = ((9 - count) / 3) + 2;
        int column = ((count - 1) % 3) + 1;
        opeartorLayout->addWidget(operatorButton, row, column);
        count++;
    }

    mainLayout->addItem(digitLayout);
    mainLayout->addItem(opeartorLayout);
    setLayout(mainLayout);
}

Button *MainFrame::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}
