#include "WindowParam.h"
#include "Manager.h"
#include "calculator.h"
#include "Button.h"
#include "UTException.h"
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
#include <iostream>
#include <QTextBlock>

WindowParam::WindowParam(QWidget* parent) : QWidget(){
    QTabWidget* tab = new QTabWidget();
    paramTab = new ParamTab(parent);
    tab->addTab(paramTab, "Settings");
    variableTab = new VariableTab(this);
    tab->addTab(variableTab, "Variables");
    programTab = new ProgramTab(this);
    tab->addTab(programTab, "Programs");

    QPushButton *buttonCancel = new QPushButton("&Close", this);
    connect(buttonCancel, SIGNAL(clicked(bool)), this, SLOT(close()));

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(tab);
    layout->addWidget(buttonCancel);
    setLayout(layout);
}

void VariableTab::deleteIdentifier() {
    ButtonIdentifier *button = qobject_cast<ButtonIdentifier *>(sender());
    Manager::getInstance().deleteIdentifier(button->getKeyIdentifier());
    Manager::getInstance().saveState();
    refresh();
}

void ProgramTab::deleteIdentifier() {
    ButtonIdentifier *button = qobject_cast<ButtonIdentifier *>(sender());
    Manager::getInstance().deleteIdentifier(button->getKeyIdentifier());
    Manager::getInstance().saveState();
    refresh();
}

void WindowParam::editIdentifier() {
    ButtonIdentifier *button = qobject_cast<ButtonIdentifier *>(sender());
    WindowEditProgramIdentifier* window = new WindowEditProgramIdentifier(button->getKeyIdentifier(), this);
    window->show();
}

void WindowParam::addIdentifier() {
    ButtonIdentifier *button = qobject_cast<ButtonIdentifier *>(sender());
    WindowAddIdentifier* window = new WindowAddIdentifier(this);
    window->show();
}

void WindowParam::refreshVariable() {
    variableTab->refresh();
}

void WindowParam::refreshProgram() {
    programTab->refresh();
}

void VariableTab::refresh() {
    while (viewVariable->rowCount() > 0)
    {
        viewVariable->removeRow(0);
    }
    auto variables = Manager::getInstance().getVariablesIdentifiers();
    viewVariable->setRowCount(variables.size());
    unsigned int count = 0;
    for(auto v : variables) {
        viewVariable->setItem(count, 0, new QTableWidgetItem(QString::fromStdString(v.first)));
        viewVariable->setItem(count, 1, new QTableWidgetItem(QString::fromStdString(v.second->toString())));
        ButtonIdentifier *deleteButton = new ButtonIdentifier("X", v.first);
        connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteIdentifier()));
        viewVariable->setCellWidget(count, 2, deleteButton);
        count++;
    }
}

void ProgramTab::refresh() {
    while (viewProgram->rowCount() > 0)
    {
        viewProgram->removeRow(0);
    }
    auto variables = Manager::getInstance().getProgramsIdentifiers();
    viewProgram->setRowCount(variables.size());
    unsigned int count = 0;
    for(auto v : variables) {
        viewProgram->setItem(count, 0, new QTableWidgetItem(QString::fromStdString(v.first)));
        ButtonIdentifier *deleteButton = new ButtonIdentifier("X", v.first);
        connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteIdentifier()));
        ButtonIdentifier *editButton = new ButtonIdentifier("&Edit", v.first);
        connect(editButton, SIGNAL(clicked(bool)), this, SLOT(editIdentifier()));
        viewProgram->setCellWidget(count, 2, deleteButton);
        viewProgram->setCellWidget(count, 1, editButton);
        count++;
    }
}

ParamTab::ParamTab(QWidget* calculator) : QWidget() {
    QSpinBox *nbLineInViewPile = new QSpinBox();
    nbLineInViewPile->setMinimum(0);
    nbLineInViewPile->setValue(Manager::getInstance().getSettings().getNbLinesDisplayPile());
    connect(nbLineInViewPile, SIGNAL(valueChanged(int)), calculator, SLOT(nbLineDisplayPileChanged(int)));

    QCheckBox *beepMessage = new QCheckBox("");
    beepMessage->setChecked(Manager::getInstance().getSettings().getBeepMessage());
    connect(beepMessage, SIGNAL(stateChanged(int)), calculator, SLOT(beepMessageChanged(int)));

    QCheckBox *displayKeyboard = new QCheckBox("");
    displayKeyboard->setChecked(Manager::getInstance().getSettings().getDisplayKeyboard());
    connect(displayKeyboard, SIGNAL(stateChanged(int)), calculator, SLOT(displayKeyboardChanged(int)));

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(tr("&Nombre de ligne affichées pour la pile :"), nbLineInViewPile);
    formLayout->addRow(tr("&Signal sonore signalant un message :"), beepMessage);
    formLayout->addRow(tr("&Afficher le clavier :"), displayKeyboard);
    setLayout(formLayout);
}

VariableTab::VariableTab(WindowParam* parent) : QWidget(parent) {
    auto variables = Manager::getInstance().getVariablesIdentifiers();
    viewVariable = new QTableWidget();
    viewVariable->setColumnCount(3);
    viewVariable->setRowCount(variables.size());
    viewVariable->horizontalHeader()->hide();
    viewVariable->setSelectionBehavior(QAbstractItemView::SelectRows);

    unsigned int count = 0;
    for(auto v : variables) {
        QTableWidgetItem* key = new QTableWidgetItem(QString::fromStdString(v.first));
        key->setFlags(key->flags() ^ Qt::ItemIsEditable);
        viewVariable->setItem(count, 0, key);
        QTableWidgetItem* value = new QTableWidgetItem(QString::fromStdString(v.second->toString()));
        viewVariable->setItem(count, 1, value);
        ButtonIdentifier *deleteButton = new ButtonIdentifier("X", v.first);
        connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteIdentifier()));
        viewVariable->setCellWidget(count, 2, deleteButton);
        count++;
    }
    QPushButton *buttonAdd = new QPushButton("&Add", this);
    connect(buttonAdd, SIGNAL(clicked(bool)), parent, SLOT(addIdentifier()));

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(buttonAdd);
    layout->addWidget(viewVariable);
    setLayout(layout);
}

ProgramTab::ProgramTab(WindowParam* parent) : QWidget(parent) {
    auto variables = Manager::getInstance().getProgramsIdentifiers();
    viewProgram = new QTableWidget();
    viewProgram->setColumnCount(3);
    viewProgram->setRowCount(variables.size());
    viewProgram->horizontalHeader()->hide();
    viewProgram->setSelectionBehavior(QAbstractItemView::SelectRows);

    unsigned int count = 0;
    for(auto v : variables) {
        viewProgram->setItem(count, 0, new QTableWidgetItem(QString::fromStdString(v.first)));
        ButtonIdentifier *deleteButton = new ButtonIdentifier("X", v.first);
        connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteIdentifier()));
        ButtonIdentifier *editButton = new ButtonIdentifier("&Edit", v.first);
        connect(editButton, SIGNAL(clicked(bool)), parent, SLOT(editIdentifier()));
        viewProgram->setCellWidget(count, 2, deleteButton);
        viewProgram->setCellWidget(count, 1, editButton);

        count++;
    }

    QPushButton *buttonAdd = new QPushButton("&Add", this);
    connect(buttonAdd, SIGNAL(clicked(bool)), parent, SLOT(addIdentifier()));

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(buttonAdd);
    layout->addWidget(viewProgram);
    setLayout(layout);
}

WindowAddIdentifier::WindowAddIdentifier(WindowParam* parent) : QWidget(){
    QVBoxLayout* mainLayout = new QVBoxLayout();

    keyLineEdit = new QLineEdit();
    valueTextEdit = new QTextEdit();

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(tr("&Key : "), keyLineEdit);
    formLayout->addRow(tr("&Value : "), valueTextEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    messageError = new QLabel();
    QPushButton* saveButton = new QPushButton("&Save");
    connect(saveButton, SIGNAL(clicked(bool)), this, SLOT(save()));
    QPushButton* cancelButton = new QPushButton("&Cancel");
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(this, SIGNAL(needRefresh()), parent, SLOT(refreshVariable()));
    connect(this, SIGNAL(needRefresh()), parent, SLOT(refreshProgram()));
    buttonLayout->addWidget(messageError);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addItem(formLayout);
    mainLayout->addItem(buttonLayout);
    setLayout(mainLayout);
}

void WindowAddIdentifier::save() {
    if (valueTextEdit->toPlainText().isEmpty() || keyLineEdit->text().isEmpty()) messageError->setText("Please enter a key and a value");
    //TO DO : Verifier si l'identifier n'existe pas déja.
    else {
        try {
            Manager::getInstance().addIdentifier(keyLineEdit->text().toStdString(), valueTextEdit->toPlainText().toStdString());
            Manager::getInstance().saveState();
            emit needRefresh();
            close();
        } catch (UTException e) {
            messageError->setText(e.what());
        }
    }
}



WindowEditProgramIdentifier::WindowEditProgramIdentifier(std::string key, WindowParam* parent) : QWidget(), key (key){
    QVBoxLayout* mainLayout = new QVBoxLayout();

    QLabel* keyLabel = new QLabel(QString::fromStdString(key));
    valueTextEdit = new QTextEdit();
    valueTextEdit->setText(QString::fromStdString(Manager::getInstance().getIdentifier(key)->toString()));
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(tr("&Value : "), valueTextEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    messageError = new QLabel();
    QPushButton* saveButton = new QPushButton("&Save");
    connect(saveButton, SIGNAL(clicked(bool)), this, SLOT(save()));
    QPushButton* cancelButton = new QPushButton("&Cancel");
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(this, SIGNAL(needRefresh()), parent, SLOT(refreshVariable()));
    connect(this, SIGNAL(needRefresh()), parent, SLOT(refreshProgram()));

    buttonLayout->addWidget(messageError);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addWidget(keyLabel);
    mainLayout->addItem(formLayout);
    mainLayout->addItem(buttonLayout);
    setLayout(mainLayout);
}

void WindowEditProgramIdentifier::save() {
    if (valueTextEdit->toPlainText().isEmpty()) messageError->setText("Please a value");
    //TO DO : Verifier si l'identifier n'existe pas déja.
    else {
        try {
            Manager::getInstance().addIdentifier(key, valueTextEdit->toPlainText().toStdString());
            Manager::getInstance().saveState();
            emit needRefresh();
            close();
        } catch (UTException e) {
            messageError->setText(e.what());
        }
    }
}
