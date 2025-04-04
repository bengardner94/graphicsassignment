#include "HelloGL.h"
#include "GLUTCallbacks.h"
#include <iostream>
#include "MeshLoader.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	InitObjects();
	InitGL(argc, argv);

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
	Mesh* objectMesh = MeshLoader::Load((char*)"cube.txt");
	camera->eye.x = 5.0f; camera->eye.y = 5.0f; camera->eye.z = -5.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;
	for (int i = 0; i < 1000; i++)
	{
		objects[i] = new Cube(objectMesh, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}
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

	//enables back face culling
	glEnable(GL_CULL_FACE);

	glCullFace(GL_BACK);
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < 200; i++)
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

	for (int i = 0; i < 1000; i++)
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