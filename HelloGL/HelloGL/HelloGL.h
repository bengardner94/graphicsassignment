#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#define REFRESHRATE 16

struct Vector3
{
	float x, y, z;
};

struct Camera
{
	Vector3 eye, center, up;
};

class HelloGL
{
public:

	HelloGL(int argc, char* argv[]);
	~HelloGL(void);

	void Display();
	void DrawPolygon();
	void Update();
	void Keyboard(unsigned char key, int x, int y);

private:
	float rotation;
	Camera* camera;
};

