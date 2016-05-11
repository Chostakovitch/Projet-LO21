#ifndef UTCOMPUTER_H
#define UTCOMPUTER_H

#include <QMainWindow>

namespace Ui {
class UTComputer;
}

class UTComputer : public QMainWindow
{
    Q_OBJECT

public:
    explicit UTComputer(QWidget *parent = 0);
    ~UTComputer();

private:
    Ui::UTComputer *ui;
};

#endif // UTCOMPUTER_H
