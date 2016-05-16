/********************************************************************************
** Form generated from reading UI file 'utcomputer.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UTCOMPUTER_H
#define UI_UTCOMPUTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UTComputer
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *UTComputer)
    {
        if (UTComputer->objectName().isEmpty())
            UTComputer->setObjectName(QStringLiteral("UTComputer"));
        UTComputer->resize(400, 300);
        menuBar = new QMenuBar(UTComputer);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        UTComputer->setMenuBar(menuBar);
        mainToolBar = new QToolBar(UTComputer);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        UTComputer->addToolBar(mainToolBar);
        centralWidget = new QWidget(UTComputer);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        UTComputer->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(UTComputer);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        UTComputer->setStatusBar(statusBar);

        retranslateUi(UTComputer);

        QMetaObject::connectSlotsByName(UTComputer);
    } // setupUi

    void retranslateUi(QMainWindow *UTComputer)
    {
        UTComputer->setWindowTitle(QApplication::translate("UTComputer", "UTComputer", 0));
    } // retranslateUi

};

namespace Ui {
    class UTComputer: public Ui_UTComputer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UTCOMPUTER_H
