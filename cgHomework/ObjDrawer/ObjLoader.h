#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <QVector3D>
#include <QMessageBox>

using std::vector;
using std::string;

class ObjLoader
{
private:
	vector<QVector3D> vertexes;
	vector<unsigned int> indices;
public:
	ObjLoader();
	~ObjLoader();

	const vector<QVector3D> getVertices();
	const vector<unsigned int> getIndices();
	bool loadObj(char* path);
};

