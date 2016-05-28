#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDebug>

class Button;
class Settings;
class MainFrame;
class Manager;

class Calculator : public QWidget
{
private:
    Q_OBJECT
    QLineEdit* message;
    QTableWidget* viewPile;
    QLineEdit* command;
    QVBoxLayout* layout;
    MainFrame* keyBoard;

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
    //void getNextCommande();

};

#endif // CALCULATOR_H
