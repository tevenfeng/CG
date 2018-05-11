#include "cgHomework.h"

cgHomework::cgHomework(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	Transformation myTest = Transformation();

	QVector3D a = QVector3D(-3.5f, 46.8f, 0.13f);

	QVector3D b = QVector3D(7.9f, 6.6f, 10.35f);

	QVector3D c = QVector3D(1, 1, 1);

	double test1 = myTest.dotProduct(a, b);

	double test2 = myTest.angle(a, b);

	QVector3D test3 = myTest.crossProduct(a, b);

	QVector3D test4 = myTest.normalization(a, b, c);

	if (myTest.dotProduct(a, b) == QVector3D::dotProduct(a, b))
	{
		QMessageBox::about(NULL, "Correct", "Dot product correct!");
	}
}
