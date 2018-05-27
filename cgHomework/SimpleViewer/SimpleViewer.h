#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SimpleViewer.h"

class SimpleViewer : public QMainWindow
{
	Q_OBJECT

public:
	SimpleViewer(QWidget *parent = Q_NULLPTR);

private:
	Ui::SimpleViewerClass ui;
};
