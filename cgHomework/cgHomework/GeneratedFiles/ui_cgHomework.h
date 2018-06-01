/********************************************************************************
** Form generated from reading UI file 'cgHomework.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CGHOMEWORK_H
#define UI_CGHOMEWORK_H

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

class Ui_cgHomeworkClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *cgHomeworkClass)
    {
        if (cgHomeworkClass->objectName().isEmpty())
            cgHomeworkClass->setObjectName(QStringLiteral("cgHomeworkClass"));
        cgHomeworkClass->resize(600, 400);
        menuBar = new QMenuBar(cgHomeworkClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        cgHomeworkClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(cgHomeworkClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        cgHomeworkClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(cgHomeworkClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        cgHomeworkClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(cgHomeworkClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        cgHomeworkClass->setStatusBar(statusBar);

        retranslateUi(cgHomeworkClass);

        QMetaObject::connectSlotsByName(cgHomeworkClass);
    } // setupUi

    void retranslateUi(QMainWindow *cgHomeworkClass)
    {
        cgHomeworkClass->setWindowTitle(QApplication::translate("cgHomeworkClass", "cgHomework", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class cgHomeworkClass: public Ui_cgHomeworkClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CGHOMEWORK_H
