#include "Transformation.h"



Transformation::Transformation()
{
}

Transformation::~Transformation()
{
}

double Transformation::dotProduct(QVector3D a, QVector3D b)
{
	return a.x()*b.x() + a.y()*b.y() + a.z()*b.z();
}

double Transformation::angle(QVector3D a, QVector3D b)
{
	return acos(dotProduct(a, b) / (a.length()*b.length()));
}

QVector3D Transformation::crossProduct(QVector3D a, QVector3D b)
{
	QVector3D result = QVector3D();

	result.setX(a.y()*b.z() - b.y()*a.z());
	result.setY(a.x()*b.z() - b.x()*a.z());
	result.setZ(a.x()*b.y() - b.x()*a.y());

	return result;
}

QVector3D Transformation::normalization(QVector3D a, QVector3D b, QVector3D c)
{
	QVector3D v1 = b - a;
	QVector3D v2 = c - a;

	QVector3D result = crossProduct(v1, v2);

	double length = result.length();
	result.setX(result.x() / length);
	result.setY(result.y() / length);
	result.setZ(result.z() / length);

	return result;
}
