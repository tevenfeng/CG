#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include "ui_cgHomework.h"
#include "Transformation.h"

class cgHomework : public QMainWindow
{
	Q_OBJECT

public:
	cgHomework(QWidget *parent = Q_NULLPTR);

private:
	Ui::cgHomeworkClass ui;
};
