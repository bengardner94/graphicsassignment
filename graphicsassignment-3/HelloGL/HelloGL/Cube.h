#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"

class Cube
{
private:
	static Vertex* indexedVertices;
	static Color* indexedColors;
	static GLushort* indices;

	GLfloat _rotation;

	Vector3 _position;

	static int numVertices, numColors, numIndices;

public:
	Cube(int x, int y, int z);
	~Cube();

	void Draw();
	void Update();

	static bool Load(char* path);
};

