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

	bool loadObj(char* path);

public:
	ObjLoader();
	ObjLoader(char* path);
	~ObjLoader();

	const vector<QVector3D> getVertices();
	const vector<unsigned int> getIndices();
};

