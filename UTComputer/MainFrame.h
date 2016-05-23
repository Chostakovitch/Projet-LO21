#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QFrame>

class Button;

class MainFrame : public QFrame
{
    Q_OBJECT
public:
    MainFrame(QWidget *parent = 0);
private:
    std::shared_ptr<Button> createButton(const QString &text, const char *member);

    enum { NumDigitButtons = 10 };
    std::shared_ptr<Button> digitButtons[NumDigitButtons];
};

#endif // MAINFRAME_H
