#include "Cube.h"
#include <iostream>
#include <string>
#include <fstream>

Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
	_rotation = 0.0f;
}

Cube::~Cube()
{

}

void Cube::Draw()
{
	if ((_mesh->Vertices != nullptr) && (_mesh->Normals != nullptr) && (_mesh->Indices != nullptr))
	{
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glNormalPointer(GL_FLOAT, 0, _mesh->Normals);
		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);
	
		_material = new Material();
		_material->Ambient.x = 0.8; _material->Ambient.y = 0.05; _material->Ambient.z = 0.05; _material->Ambient.z = 1.0;
		_material->Diffuse.x = 0.8; _material->Diffuse.y = 0.05; _material->Diffuse.z = 0.05; _material->Diffuse.z = 1.0;
		_material->Specular.x = 0.8; _material->Specular.y = 0.05; _material->Specular.z = 0.05; _material->Specular.z = 1.0;
		_material->Shininess = 100.0f;

		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 1.0f, 0.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();

		glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
		glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->Diffuse.x));
		glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->Specular.x));
		glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);

		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

void Cube::Update()
{
	_rotation += 2.0f;

	if (_rotation >= 360.0f)
		_rotation = 0.0f;

	if (_position.z <= 100.0f)
		_position.z += 0.2f;
	else
		_position.z = 0.0f;

}
