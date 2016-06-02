#include "WindowException.h"
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPlainTextEdit>

WindowException::WindowException(std::string details) : QWidget()
{
    //Largeur maximale
    std::istringstream iss(details);
    std::string dest;
    std::string max;
    while(std::getline(iss, dest, '\n')) {
        if(dest.size() > max.size()) max = dest;
    }
    QVBoxLayout* layout = new QVBoxLayout();
    QPlainTextEdit* errorDetails = new QPlainTextEdit(QString::fromStdString(details));

    //Police système à largeur fixe
    QFont fixedFont = QFontDatabase::systemFont((QFontDatabase::FixedFont));
    errorDetails->setFont(fixedFont);

    //Ajustement de la taille des tabulations
    QFontMetrics metrics(fixedFont);
    auto tabSize = 2 * metrics.width(' ');
    errorDetails->setTabStopWidth(tabSize);

    //Ajustement de la taille de la fenêtre au contenu en tenant compte des nouvelles tabulations
    auto textSize = metrics.size(Qt::TextExpandTabs, errorDetails->toPlainText(), tabSize);
    int textWidth = textSize.width() + 30;
    int textHeight = textSize.height();
    errorDetails->setMinimumSize(textWidth, textHeight);

    layout->addWidget(errorDetails);
    setLayout(layout);
}
