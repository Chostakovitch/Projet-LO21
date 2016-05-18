#include "WindowParam.h"
#include <QTableWidget>
#include <QVBoxLayout>

WindowParam::WindowParam(){
    QTabWidget* tab = new QTabWidget();
    tab->addTab(new QWidget(), "Paramétres");
    tab->addTab(new QWidget(), "Identificateurs de variable");
    tab->addTab(new QWidget(), "Identificateurs de programme");

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(tab);
    setLayout(layout);

}
