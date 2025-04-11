#include "HelloGL.h"
#include "GLUTCallbacks.h"
#include <iostream>
#include "MeshLoader.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	InitGL(argc, argv);
	InitObjects();
	InitLighting();
	glutMainLoop();
}

HelloGL::~HelloGL(void)
{
	delete camera;
	delete objects;
}

void HelloGL::InitObjects()
{
	rotation = 0.0f;
	camera = new Camera();
	Mesh* cubeMesh = MeshLoader::Load((char*)"cube.txt");
	Texture2D* texture = new Texture2D();
	texture->Load((char*)"penguins.raw", 512, 512);
	camera->eye.x = 1.0f; camera->eye.y = 1.0f; camera->eye.z = -1.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;
	for (int i = 0; i < 500; i++)
	{
		objects[i] = new Cube(cubeMesh, texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}
}

void HelloGL::InitLighting()
{
	_lightPosition = new Vector4();
	_lightPosition->x = 0.0;
	_lightPosition->y = 0.0;
	_lightPosition->z = 1.0;
	_lightPosition->w = 0.0;

	_lightData = new Lighting();
	_lightData->Ambient.x = 0.2;
	_lightData->Ambient.y = 0.2;
	_lightData->Ambient.z = 0.2;
	_lightData->Ambient.w = 1.0;
	_lightData->Diffuse.x = 0.8;
	_lightData->Diffuse.y = 0.8;
	_lightData->Diffuse.z = 0.8;
	_lightData->Diffuse.w = 1.0;
	_lightData->Specular.x = 0.2;
	_lightData->Specular.y = 0.2;
	_lightData->Specular.z = 0.2;
	_lightData->Specular.w = 1.0;
}

void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Simple OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutKeyboardFunc(GLUTCallbacks::checkKeyboard);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);

	//enables depth testing
	glEnable(GL_DEPTH_TEST);

	//switch to different set of matrices
	glMatrixMode(GL_PROJECTION);
	//load identity matrix
	glLoadIdentity();

	//set the viewport to be the entire window
	glViewport(0, 0, 1800, 1800);

	//set the correct perspective
	gluPerspective(100, 1, 1, 1000);
	//45 is the field of view, 1 is the aspect ratio, the next 1 is the front clipping plane, 1000 is the far clipping plane

	//switches back to the modelview matrix
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_TEXTURE_2D);
	//enables back face culling
	glEnable(GL_CULL_FACE);

	//enables lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glCullFace(GL_BACK);
}

void HelloGL::Display()
{
	Vector3 v = { -0.5f, 0.7f, -1.0f };
	Color c = { 0.0f, 1.0f, 0.0f };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawString("wai 2 gooooo", &v, &c);
	for (int i = 0; i < 500; i++)
	{
		objects[i]->Draw();
	}
	glFlush();
	glutSwapBuffers();
}

void HelloGL::Update()
{
	//resets the modelview matrix every frame
	glLoadIdentity();
	//move the camera to the points specified by the camera variable
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);

	//changes light values during execution
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));

	for (int i = 0; i < 500; i++)
	{
		objects[i]->Update();
	}

	glutPostRedisplay();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'a')
	{
		camera->eye.x += 0.0f; camera->eye.y += 1.0f; camera->eye.z += 0.0f;
	}
	if (key == 'd')
		rotation += 10.0f;
}

void HelloGL::DrawString(const char* text, Vector3* position, Color* color)
{
	glPushMatrix();
	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(0.0f, 0.0f);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);
	glPopMatrix();
}