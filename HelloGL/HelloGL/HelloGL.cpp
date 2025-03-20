#include "HelloGL.h"
#include "GLUTCallbacks.h"
#include <iostream>

HelloGL::HelloGL(int argc, char* argv[])
{
	rotation = 0.0f;
	camera = new Camera();
	camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutCreateWindow("Simple OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutKeyboardFunc(GLUTCallbacks::checkKeyboard);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	//switch to different set of matrices
	glMatrixMode(GL_PROJECTION);
	//load identity matrix
	glLoadIdentity();

	//set the viewport to be the entire window
	glViewport(0, 0, 800, 800);

	//set the correct perspective
	gluPerspective(45, 1, 0, 1000);
	//45 is the field of view, 1 is the aspect ratio, the next 1 is the front clipping plane, 1000 is the far clipping plane

	//switches back to the modelview matrix
	glMatrixMode(GL_MODELVIEW);

	glutMainLoop();
}

HelloGL::~HelloGL(void)
{
	delete camera;
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//DrawPolygon();
	glPushMatrix();
		glRotatef(rotation, 1.0f, -1.0f, 1.0f);
		glutWireTeapot(0.3);
	glPopMatrix();
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

	glutPostRedisplay();

	Sleep(10);

	if (rotation >= 360.0f)
		rotation = 0.0f;
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'd')
		rotation += 10.0f;
}