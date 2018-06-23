#include "ObjLoader.h"

ObjLoader::ObjLoader()
{
	this->vertexNum = 0;
	this->indiceNum = 0;
}

bool ObjLoader::loadObj(char* path)
{
	FILE *file = fopen(path, "r");
	if (file == NULL)
	{
		return false;
	}
	else
	{
		float x, y, z;
		float normalX, normalY, normalZ;
		char lineHeader[128];
		unsigned int a, b, c, d, e, f;
		while (1)
		{
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)
			{
				break;
			}
			if (strcmp(lineHeader, "v") == 0)
			{
				fscanf(file, "%f %f %f\n", &x, &y, &z);
				vertexes[vertexNum].position = QVector3D(x, y, z);
				vertexNum++;
			}
			else
				if (strcmp(lineHeader, "vn") == 0)
				{
					fscanf(file, "%f %f %f\n", &normalX, &normalY, &normalZ);
					vertexes[vertexNum].normal = QVector3D(normalX, normalY, normalZ);
				}
				else
					if (strcmp(lineHeader, "f") == 0)
					{
						int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &a, &b, &c, &d, &e, &f);
						if (matches != 6) {
							return false;
						}
						indices[indiceNum++] = a - 1;
						indices[indiceNum++] = c - 1;
						indices[indiceNum++] = e - 1;
					}
		}
		return true;
	}
}

ObjLoader::~ObjLoader()
{
}
