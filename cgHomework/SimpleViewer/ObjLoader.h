#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <QVector3D>
#include <QMessageBox>

using std::vector;
using std::string;

struct VertexData {
	QVector3D position;
	QVector3D normal;
};

class ObjLoader
{
public:
	ObjLoader();
	~ObjLoader();

	bool loadObj(char* path);

	VertexData vertexes[10000];
	unsigned int vertexNum, indiceNum;
	unsigned int indices[10000 * 3];
	
};

