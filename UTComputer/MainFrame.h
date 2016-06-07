#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QFrame>
#include <memory>

class Button;

class MainFrame : public QFrame
{
    Q_OBJECT
public:
    MainFrame(QWidget *parent = 0);
public slots:

private:
    Button* createButton(const QString &text, const char *member);

    enum { NumDigitButtons = 10 };
    Button* digitButtons[NumDigitButtons];
};

class WindowMoreOperators : public QWidget {
    Q_OBJECT
public :
    WindowMoreOperators(QObject* parent = 0);
};

#endif // MAINFRAME_H
