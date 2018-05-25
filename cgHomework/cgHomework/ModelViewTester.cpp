#include "ModelViewTester.h"



ModelViewTester::ModelViewTester()
{
}


ModelViewTester::~ModelViewTester()
{
}

QVector3D ModelViewTester::scaling(QVector3D vertex, QVector3D scalingVector)
{
	return QVector3D(
		vertex.x()*scalingVector.x(),
		vertex.y()*scalingVector.y(),
		vertex.z()*scalingVector.z()
	);
}

QVector3D ModelViewTester::transition(QVector3D vertex, QVector3D transionVector)
{
	return QVector3D(
		vertex.x() + transionVector.x(),
		vertex.y() + transionVector.y(),
		vertex.z() + transionVector.z()
	);
}

QVector3D ModelViewTester::rotation(QVector3D vertex, QVector3D axis, double angle)
{
	double tmp = 1 - cos(angle);

	const double tmpMatrix[9] = {
		cos(angle) + axis.x()*axis.x()*tmp, axis.x()*axis.y()*tmp - axis.z()*sin(angle), axis.x()*axis.z()*tmp + axis.y()*sin(angle),
		axis.x()*axis.y()*tmp + axis.z()*sin(angle), cos(angle) + axis.y()*axis.y()*tmp, axis.y()*axis.z()*tmp - axis.x()*sin(angle),
		axis.x()*axis.z()*tmp - axis.y()*sin(angle), axis.y()*axis.z()*tmp + axis.x()*sin(angle), cos(angle) + axis.x()*axis.x()*tmp
	};
	const double *tmpM = tmpMatrix;

	QGenericMatrix<3, 3, double> rotationMatrix = QGenericMatrix<3, 3, double>(tmpM);

	double tmpVertex[3] = { vertex.x(), vertex.y(), vertex.z() };
	double *tmpV = tmpVertex;

	QGenericMatrix<1, 3, double> tmpResult = rotationMatrix*QGenericMatrix<1,3, double>(tmpV);

	tmpResult.copyDataTo(tmpV);
	return QVector3D(tmpV[0], tmpV[1], tmpV[2]);
}
