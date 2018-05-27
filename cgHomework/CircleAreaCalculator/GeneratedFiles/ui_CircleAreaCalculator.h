/********************************************************************************
** Form generated from reading UI file 'CircleAreaCalculator.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CIRCLEAREACALCULATOR_H
#define UI_CIRCLEAREACALCULATOR_H

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

class Ui_CircleAreaCalculatorClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CircleAreaCalculatorClass)
    {
        if (CircleAreaCalculatorClass->objectName().isEmpty())
            CircleAreaCalculatorClass->setObjectName(QStringLiteral("CircleAreaCalculatorClass"));
        CircleAreaCalculatorClass->resize(600, 400);
        menuBar = new QMenuBar(CircleAreaCalculatorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        CircleAreaCalculatorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CircleAreaCalculatorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CircleAreaCalculatorClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(CircleAreaCalculatorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CircleAreaCalculatorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CircleAreaCalculatorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CircleAreaCalculatorClass->setStatusBar(statusBar);

        retranslateUi(CircleAreaCalculatorClass);

        QMetaObject::connectSlotsByName(CircleAreaCalculatorClass);
    } // setupUi

    void retranslateUi(QMainWindow *CircleAreaCalculatorClass)
    {
        CircleAreaCalculatorClass->setWindowTitle(QApplication::translate("CircleAreaCalculatorClass", "CircleAreaCalculator", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CircleAreaCalculatorClass: public Ui_CircleAreaCalculatorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CIRCLEAREACALCULATOR_H
