#include "WindowParam.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QWidget>
#include <QSpinBox>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QDialog>
#include <QHeaderView>
#include <QPushButton>

WindowParam::WindowParam(QWidget* parent): QWidget(parent){
    QTabWidget* tab = new QTabWidget();
    tab->addTab(new ParamTab(), "Paramétres");
    tab->addTab(new VariableTab(), "Variable");
    tab->addTab(new ProgramTab(), "Programmes");

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(tab);
    layout->addWidget(buttonBox);
    setLayout(layout);
}

ParamTab::ParamTab(QWidget* parent) : QWidget(parent) {
    QSpinBox *nbLineInViewPile = new QSpinBox();
    nbLineInViewPile->setMinimum(0);
    nbLineInViewPile->setValue(6);

    QCheckBox *beepMessage = new QCheckBox("");
    QCheckBox *displayKeyboard = new QCheckBox("");

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(tr("&Nombre de ligne affichées pour la pile :"), nbLineInViewPile);
    formLayout->addRow(tr("&Signal sonore signalant un message :"), beepMessage);
    formLayout->addRow(tr("&Afficher le clavier :"), displayKeyboard);
    setLayout(formLayout);
}

VariableTab::VariableTab(QWidget* parent) : QWidget(parent) {
    QTableWidget *viewVariable = new QTableWidget();
    viewVariable->setColumnCount(2);
    viewVariable->setRowCount(5);
    viewVariable->horizontalHeader()->hide();
    viewVariable->setSelectionBehavior(QAbstractItemView::SelectRows);
    QTableWidgetItem *newItem1 = new QTableWidgetItem(tr("PI"));
    QTableWidgetItem *newItem2 = new QTableWidgetItem(tr("3.14"));
    viewVariable->setItem(0,0, newItem1);
    viewVariable->setItem(0,1, newItem2);

    QPushButton *buttonAdd = new QPushButton("&Add", this);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(buttonAdd);
    layout->addWidget(viewVariable);
    setLayout(layout);
}

ProgramTab::ProgramTab(QWidget* parent) : QWidget(parent) {
    QTableWidget *viewProgram = new QTableWidget();
    viewProgram->setColumnCount(1);
    viewProgram->setRowCount(5);
    viewProgram->horizontalHeader()->hide();
    viewProgram->setSelectionBehavior(QAbstractItemView::SelectRows);
    QTableWidgetItem *newItem1 = new QTableWidgetItem(tr("YOLOPROG"));
    viewProgram->setItem(0,0, newItem1);

    QPushButton *buttonAdd = new QPushButton("&Add", this);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(buttonAdd);
    layout->addWidget(viewProgram);
    setLayout(layout);
}
