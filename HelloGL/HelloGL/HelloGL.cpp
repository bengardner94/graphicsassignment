#include "HelloGL.h"
#include "GLUTCallbacks.h"
#include <iostream>

HelloGL::HelloGL(int argc, char* argv[])
{
	rotation = 0.0f;
	camera = new Camera();
	camera->eye.x = 5.0f; camera->eye.y = 5.0f; camera->eye.z = -5.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;
	for (int i = 0; i < 200; i++)
	{
		cube[i] = new Cube(((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}
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

	glutMainLoop();
}

HelloGL::~HelloGL(void)
{
	delete camera;
	delete cube;
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < 200; i++)
	{
		cube[i]->Draw();
	}
	glFlush();
	glutSwapBuffers();
}

/*void HelloGL::DrawPolygon()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(rotation, -1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	{
		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
		glVertex2f(-0.75, 0.5);
		glVertex2f(0.75, 0.5);
		glVertex2f(0.75, -0.5);
		glVertex2f(-0.75, -0.5);
		glEnd();
	}
	glPopMatrix();
}*/

void HelloGL::Update()
{
	//resets the modelview matrix every frame
	glLoadIdentity();
	//move the camera to the points specified by the camera variable
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);

	for (int i = 0; i < 200; i++)
	{
		cube[i]->Update();
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