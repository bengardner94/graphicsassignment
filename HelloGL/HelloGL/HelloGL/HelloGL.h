#pragma once
#include <Windows.h>
#define REFRESHRATE 16
#include "Structures.h"
class HelloGL
{
public:

	HelloGL(int argc, char* argv[]);
	~HelloGL(void);

	void Display();
	void DrawPolygon();
	void Update();
	void DrawCube();
	void DrawCubeArray();
	void DrawIndexedCube();
	void Keyboard(unsigned char key, int x, int y);

private:
	float rotation;
	Camera* camera;

	static Vertex vertices[];
	static Color colors[];
	static Vertex indexedVertices[];
	static Color indexedColors[];
	static GLushort indices[];
};

