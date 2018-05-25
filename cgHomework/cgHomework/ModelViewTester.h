#pragma once
#include <QVector3D>
#include <QGenericMatrix>
#include <QMatrix3x3>
#include <QMatrix4x4>
#include <math.h>

class ModelViewTester
{
public:
	ModelViewTester();
	~ModelViewTester();

	QVector3D scaling(QVector3D vertex, QVector3D scalingVector);
	QVector3D transition(QVector3D vertex, QVector3D transionVector);
	QVector3D rotation(QVector3D vertex, QVector3D axis, double angle);
};

