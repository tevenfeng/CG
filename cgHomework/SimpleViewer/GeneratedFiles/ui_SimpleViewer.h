/********************************************************************************
** Form generated from reading UI file 'SimpleViewer.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMPLEVIEWER_H
#define UI_SIMPLEVIEWER_H

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

class Ui_SimpleViewerClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SimpleViewerClass)
    {
        if (SimpleViewerClass->objectName().isEmpty())
            SimpleViewerClass->setObjectName(QStringLiteral("SimpleViewerClass"));
        SimpleViewerClass->resize(600, 400);
        menuBar = new QMenuBar(SimpleViewerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        SimpleViewerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SimpleViewerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SimpleViewerClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(SimpleViewerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        SimpleViewerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SimpleViewerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SimpleViewerClass->setStatusBar(statusBar);

        retranslateUi(SimpleViewerClass);

        QMetaObject::connectSlotsByName(SimpleViewerClass);
    } // setupUi

    void retranslateUi(QMainWindow *SimpleViewerClass)
    {
        SimpleViewerClass->setWindowTitle(QApplication::translate("SimpleViewerClass", "SimpleViewer", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SimpleViewerClass: public Ui_SimpleViewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMPLEVIEWER_H
