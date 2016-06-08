#include "MainFrame.h"
#include "Button.h"
#include "OperatorManager.h"
#include "Manager.h"
#include "UTComputer.h"
#include "Calculator.h"
#include <QGridLayout>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPlainTextEdit>

MainFrame::MainFrame(QWidget *parent) : QFrame(parent) {

    // Creation des boutons
    for (int i = 0; i < NumDigitButtons; ++i) {
        digitButtons[i] = createButton(QString::number(i), SLOT(addDigitToCommand()));
    }
    Button *pointButton = createButton(tr("."), SLOT(addDigitToCommand()));
    Button *spaceButton = createButton(tr("SPACE"), SLOT(addSpaceToCommand()));
    Button *enterButton = createButton(tr("ENTER"), SLOT(calculate()));
    Button *backspaceButton = createButton(tr("BACKSPACE"), SLOT(backspaceToCommand()));

    // Ajout dans le Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QGridLayout *digitLayout = new QGridLayout;
    QGridLayout *actionLayout = new QGridLayout;
    QGridLayout *opeartorLayout = new QGridLayout;

    for (int i = 1; i < NumDigitButtons; ++i) {
        int row = ((9 - i) / 3) + 2;
        int column = ((i - 1) % 3) + 1;
        digitLayout->addWidget(digitButtons[i], row, column);
    }
    digitLayout->addWidget(pointButton, 5, 1);
    digitLayout->addWidget(digitButtons[0], 5, 2);
    digitLayout->addWidget(enterButton, 5, 3);

    actionLayout->addWidget(spaceButton, 1, 1);
    actionLayout->addWidget(backspaceButton, 1, 2);

    std::vector<std::string> symbolicOperators = Manager::getInstance().getSymbolicOperatorToString();
    unsigned int count = 1;
    for(auto o : symbolicOperators) {
        Button* operatorButton = createButton(QString::fromStdString(o), SLOT(addOperatorToCommand()));
        int row = ((symbolicOperators.size() - count) / 3) + 2;
        int column = ((count - 1) % 3) + 1;
        opeartorLayout->addWidget(operatorButton, row, column);
        count++;
    }
    Button* operatorButton = createButton("More operators", SLOT(openMoreOperatorsWindow()));

    mainLayout->addItem(digitLayout);
    mainLayout->addItem(actionLayout);
    mainLayout->addItem(opeartorLayout);
    mainLayout->addWidget(operatorButton);
    setLayout(mainLayout);
}

Button *MainFrame::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()), parent(), member);
    return button;
}

WindowMoreOperators::WindowMoreOperators(QWidget* parent) {
    QGridLayout *operatorLayout = new QGridLayout;

    std::vector<std::string> functionOperators = Manager::getInstance().getFunctionOperatorToString();
    unsigned int count = 1;
    for(const auto& o : functionOperators) {
        Button* operatorButton = new Button(QString::fromStdString(o));
        connect(operatorButton, SIGNAL(clicked()), parent, SLOT(addOperatorToCommand()));
        int row = ((functionOperators.size() - count) / 3) + 2;
        int column = ((count - 1) % 3) + 1;
        operatorLayout->addWidget(operatorButton, row, column);
        count++;
    }
    move(parent->pos());
    setLayout(operatorLayout);
}


HistoryWindow::HistoryWindow(QWidget *parent) {
    UTComputer* computer = qobject_cast<UTComputer *>(parent);
    QVBoxLayout* layout = new QVBoxLayout();

    std::vector<QString> commands = computer->getCalculator()->getCommands();
    QString final;
    for(const auto& command : commands) {
        final += command + '\n';
    }
    QPlainTextEdit* history = new QPlainTextEdit(final);

    //Police système à largeur fixe
    QFont fixedFont = QFontDatabase::systemFont((QFontDatabase::FixedFont));
    history->setFont(fixedFont);

    //Ajustement de la taille des tabulations
    QFontMetrics metrics(fixedFont);
    auto tabSize = 2 * metrics.width(' ');
    history->setTabStopWidth(tabSize);

    //Ajustement de la taille de la fenêtre au contenu en tenant compte des nouvelles tabulations
    auto textSize = metrics.size(Qt::TextExpandTabs, history->toPlainText(), tabSize);
    int textWidth = textSize.width() + 30;
    int textHeight = textSize.height();
    history->setMinimumSize(textWidth, textHeight);

    layout->addWidget(history);
    setLayout(layout);
}
