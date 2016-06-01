#include "WindowException.h"
#include <QTextEdit>
#include <QVBoxLayout>

WindowException::WindowException(std::string details) : QWidget()
{
    QVBoxLayout* layout = new QVBoxLayout();
    QTextEdit* errorDetails = new QTextEdit(QString::fromStdString(details));
    layout->addWidget(errorDetails);
    setLayout(layout);
}
