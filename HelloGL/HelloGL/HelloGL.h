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
	void InitLighting();

	void Display();
	void Update();
	void Keyboard(unsigned char key, int x, int y);

	void DrawString(const char* text, Vector3* position, Color* color);

private:
	float rotation;
	Texture2D* texture;
	Mesh* cubeMesh;
	Mesh* pyramidMesh;
	Camera* camera;
	Vector3* _position;
	Vector4* _lightPosition;
	Lighting* _lightData;

	SceneObject* objects[1000];
};

