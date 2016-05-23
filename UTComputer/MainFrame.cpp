#include "MainFrame.h"
#include "Button.h"
#include <QGridLayout>

MainFrame::MainFrame(QWidget *parent) : QFrame(parent) {
    QGridLayout *mainLayout = new QGridLayout;
    // Creation des boutons
    for (int i = 0; i < NumDigitButtons; ++i) {
        digitButtons[i] = std::shared_ptr<Button>(new Button(QString::number(i)));
    }

    // Ajout dans le Layout
    for (int i = 1; i < NumDigitButtons; ++i) {
        int row = ((9 - i) / 3) + 2;
        int column = ((i - 1) % 3) + 1;
        mainLayout->addWidget(digitButtons[i].get(), row, column);
    }
    mainLayout->addWidget(digitButtons[0].get(), 5, 1);
    setLayout(mainLayout);
}
