#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDebug>
#include <QEvent>
#include <QObject>
#include <QKeyEvent>

class UTException;
class Button;
class Settings;
class MainFrame;
class Manager;

class Calculator : public QWidget
{
private:
    Q_OBJECT
    QTextEdit* message;
    QTableWidget* viewPile;
    QLineEdit* command;
    QVBoxLayout* layout;
    MainFrame* keyBoard;
    std::string messageDetail;

    void setMessage(const UTException&);
    void deleteMessage();
protected:
    bool eventFilter (QObject *obj, QEvent *event);
public:
    explicit Calculator(QWidget *parent = 0);

public slots:
    void refreshPile();
    void addDigitToCommand();
    void addSpaceToCommand();
    void addOperatorToCommand();
    void backspaceToCommand();
    void calculate();
    void nbLineDisplayPileChanged(int newValue);
    void displayKeyboardChanged(int newValue);
    void beepMessageChanged(int newValue);
    void openDetailErrorWindow();
    //void getNextCommande();

};

#endif // CALCULATOR_H
