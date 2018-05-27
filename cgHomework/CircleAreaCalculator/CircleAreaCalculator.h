#pragma once

#include <string>
#include <QtWidgets/QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QWidget>
#include "ui_CircleAreaCalculator.h"


class CircleAreaCalculator : public QMainWindow
{
	Q_OBJECT

public:
	CircleAreaCalculator(QWidget *parent = Q_NULLPTR);

private:
	Ui::CircleAreaCalculatorClass ui;

	QLineEdit *radiusLineEdit;
	QLabel *radiusLabel, *areaLabel;
	QGridLayout *layout;
	QWidget *centralWidget;
	QPushButton *calculateBtn;

private slots:
	void showArea();
};
