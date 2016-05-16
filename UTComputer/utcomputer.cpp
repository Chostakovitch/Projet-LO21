#include "utcomputer.h"
#include "ui_utcomputer.h"

UTComputer::UTComputer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UTComputer)
{
    ui->setupUi(this);
}

UTComputer::~UTComputer()
{
    delete ui;
}
