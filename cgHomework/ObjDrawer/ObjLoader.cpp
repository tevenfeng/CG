#include "ObjLoader.h"

ObjLoader::ObjLoader()
{
}

bool ObjLoader::loadObj(char* path)
{
	FILE *file = fopen(path, "r");
	if (file == NULL)
	{
		QMessageBox::about(NULL, "Error", "Can not open the obj file!");
		return false;
	}
	else
	{
		double x, y, z;
		char lineHeader[128];
		unsigned int a, b, c;
		while (1)
		{
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)
			{
				break;
			}
			if (strcmp(lineHeader, "v") == 0)
			{				
				fscanf(file, "%lf %lf %lf\n", &x, &y, &z);
				QVector3D tmp = QVector3D();
				tmp.setX(x);
				tmp.setY(y);
				tmp.setZ(z);
				this->vertexes.push_back(tmp);
			}
			else
				if (strcmp(lineHeader, "f") == 0)
				{
					int matches = fscanf(file, "%d %d %d\n", &a, &b, &c);
					if (matches != 3) {
						QMessageBox::about(NULL, "Error", "File can't be read by our simple parser.\n");
						return false;
					}
					this->indices.push_back(a);
					this->indices.push_back(b);
					this->indices.push_back(c);
				}
		}
		return true;
	}
}

ObjLoader::ObjLoader(char* path)
{
	this->vertexes = vector<QVector3D>();
	QVector3D tmp = QVector3D();
	this->vertexes.push_back(tmp);			// vertexes in obj file start from 1

	this->indices = vector<unsigned int>();

	loadObj(path);
}

ObjLoader::~ObjLoader()
{
}

const vector<QVector3D> ObjLoader::getVertices()
{
	return this->vertexes;
}

const vector<unsigned int> ObjLoader::getIndices()
{
	return this->indices;
}
