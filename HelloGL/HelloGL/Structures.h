#pragma once

#include "GL/freeglut.h"

struct Vector3
{
	float x, y, z;
};

struct Camera
{
	Vector3 eye, center, up;
};

struct Color
{
	GLfloat r, g, b;
};

struct Vertex
{
	GLfloat x, y, z;
};

struct TexCoord
{
	GLfloat u, v;
};

struct Mesh
{
	Vertex* Vertices;
	Color* Colors;
	GLushort* Indices;
	TexCoord* TexCoords;
	int VertexCount, ColorCount, IndexCount, TexCoordCount;
};