#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh, Texture2D* texture)
{
	_mesh = mesh;
	_texture = texture;
}

SceneObject::~SceneObject()
{

}

void SceneObject::Draw()
{

}

void SceneObject::Update()
{

}

void SceneObject::EditPosition(int newPosition)
{

}

Vector3* SceneObject::GetPosition()
{
	Vector3 _position = { 0,0,0 };
	return &_position;
}