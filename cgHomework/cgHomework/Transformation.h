#pragma once
#include <QVector3D>
#include <math.h>

class Transformation
{
public:
	Transformation();
	~Transformation();
	
	double dotProduct(QVector3D a, QVector3D b);
	double angle(QVector3D a, QVector3D b);
	QVector3D crossProduct(QVector3D a, QVector3D b);
	QVector3D normalization(QVector3D a, QVector3D b, QVector3D c);
};

