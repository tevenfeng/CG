#include "cgHomework.h"

cgHomework::cgHomework(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// test Transformation
	//Transformation myTest = Transformation();

	//QVector3D a = QVector3D(-3.5f, 46.8f, 0.13f);

	//QVector3D b = QVector3D(7.9f, 6.6f, 10.35f);

	//QVector3D c = QVector3D(1, 1, 1);

	//double test1 = myTest.dotProduct(a, b);

	//double test2 = myTest.angle(a, b);

	//QVector3D test3 = myTest.crossProduct(a, b);

	//QVector3D test4 = myTest.normalization(a, b, c);

	//if (myTest.dotProduct(a, b) == QVector3D::dotProduct(a, b))
	//{
	//	QMessageBox::about(NULL, "Correct", "Dot product correct!");
	//}

	// test ModelView
	//QVector3D vertex(1.0, 1.0, 0);
	//QVector3D scale(2, 1, 1);
	//QVector3D transite(2.3, 4.5, 0);
	//QVector3D rotateAxis(1,0,0);
	//double angle = 90 * 3.1415 / 180.0;

	//ModelViewTester myTest = ModelViewTester();
	//QVector3D scaleResult = myTest.scaling(vertex, scale);
	//QVector3D transiteResult = myTest.transition(scaleResult, transite);
	//QVector3D rotateResult = myTest.rotation(transiteResult, rotateAxis, angle);
}
