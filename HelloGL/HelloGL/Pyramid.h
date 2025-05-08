#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "SceneObject.h"

class Pyramid : public SceneObject
{
public:
	Pyramid(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Pyramid();

	void Draw();
	void Update();
private:
	Vector3 _position;

	Material* _material;
};


