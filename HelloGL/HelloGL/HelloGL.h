#pragma once
#include <Windows.h>
#define REFRESHRATE 16
#include "Structures.h"
#include "Cube.h"

class HelloGL
{
public:

	HelloGL(int argc, char* argv[]);
	~HelloGL(void);

	void Display();
	void Update();
	void Keyboard(unsigned char key, int x, int y);

private:
	float rotation;
	Camera* camera;

	Cube* cube[200];
};

