#include "CircleAreaCalculator.h"

CircleAreaCalculator::CircleAreaCalculator(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	this->centralWidget = new QWidget();
	this->setCentralWidget(this->centralWidget);

	this->radiusLabel = new QLabel(tr("Radius:"));
	this->areaLabel = new QLabel();
	this->calculateBtn = new QPushButton(tr("Calculate"), this);
	this->radiusLineEdit = new QLineEdit();

	this->layout = new QGridLayout();
	this->layout->addWidget(this->radiusLabel, 1, 1);
	this->layout->addWidget(this->radiusLineEdit, 1, 2);
	this->layout->addWidget(this->areaLabel, 2, 1);
	this->layout->addWidget(this->calculateBtn, 2, 2);
	this->centralWidget->setLayout(this->layout);

	QObject::connect(this->calculateBtn, &QPushButton::clicked, this, &CircleAreaCalculator::showArea);
}

void CircleAreaCalculator::showArea() 
{
	double radius = this->radiusLineEdit->displayText().toDouble();
	double result = radius * radius * 3.14;

	QString label = QString::fromStdString(std::to_string(result));

	this->areaLabel->setText(label);
}