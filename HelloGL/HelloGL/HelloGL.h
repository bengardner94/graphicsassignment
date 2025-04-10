#pragma once
#include <Windows.h>
#define REFRESHRATE 16
#include "Structures.h"
#include "Cube.h"
#include "Pyramid.h"

class HelloGL
{
public:

	HelloGL(int argc, char* argv[]);
	~HelloGL(void);

	void InitObjects();
	void InitGL(int argc, char* argv[]);

	void Display();
	void Update();
	void Keyboard(unsigned char key, int x, int y);

private:
	float rotation;
	Camera* camera;

	SceneObject* objects[1000];
};

