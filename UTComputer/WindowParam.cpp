#include "WindowParam.h"
#include "Manager.h"
#include "calculator.h"
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

WindowParam::WindowParam(QWidget* parent) : QWidget(){
    QTabWidget* tab = new QTabWidget();
    tab->addTab(new ParamTab(parent), "Paramètres");
    tab->addTab(new VariableTab(parent), "Variable");
    tab->addTab(new ProgramTab(parent), "Programmes");

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(tab);
    layout->addWidget(buttonBox);
    setLayout(layout);
}

ParamTab::ParamTab(QWidget* calculator) : QWidget() {
    QSpinBox *nbLineInViewPile = new QSpinBox();
    nbLineInViewPile->setMinimum(0);
    nbLineInViewPile->setValue(Manager::getInstance().getSettings().getNbLinesDisplayPile());
    connect(nbLineInViewPile, SIGNAL(valueChanged(int)), calculator, SLOT(nbLineDisplayPileChanged(int)));

    QCheckBox *beepMessage = new QCheckBox("");
    beepMessage->setChecked(Manager::getInstance().getSettings().getBeepMessage());

    QCheckBox *displayKeyboard = new QCheckBox("");
    displayKeyboard->setChecked(Manager::getInstance().getSettings().getDisplayKeyboard());
    connect(displayKeyboard, SIGNAL(stateChanged(int)), calculator, SLOT(displayKeyboardChanged(int)));

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

    QPushButton *buttonAdd = new QPushButton("&Add", this);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(buttonAdd);
    layout->addWidget(viewProgram);
    setLayout(layout);
}
