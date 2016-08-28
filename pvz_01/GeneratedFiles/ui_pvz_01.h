/********************************************************************************
** Form generated from reading UI file 'pvz_01.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PVZ_01_H
#define UI_PVZ_01_H

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

class Ui_pvz_01Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *pvz_01Class)
    {
        if (pvz_01Class->objectName().isEmpty())
            pvz_01Class->setObjectName(QStringLiteral("pvz_01Class"));
        pvz_01Class->resize(600, 400);
        menuBar = new QMenuBar(pvz_01Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        pvz_01Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(pvz_01Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        pvz_01Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(pvz_01Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pvz_01Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(pvz_01Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        pvz_01Class->setStatusBar(statusBar);

        retranslateUi(pvz_01Class);

        QMetaObject::connectSlotsByName(pvz_01Class);
    } // setupUi

    void retranslateUi(QMainWindow *pvz_01Class)
    {
        pvz_01Class->setWindowTitle(QApplication::translate("pvz_01Class", "pvz_01", 0));
    } // retranslateUi

};

namespace Ui {
    class pvz_01Class: public Ui_pvz_01Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PVZ_01_H
