#include "HelloGL.h"
#include "GLUTCallbacks.h"
#include <iostream>

Vertex HelloGL::vertices[] = { 1, 1, 1, -1, 1, 1, -1,-1, 1, // v0-v1-v2 (front)
	-1,-1, 1, 1,-1, 1, 1, 1, 1, // v2-v3-v0
	1, 1, 1, 1,-1, 1, 1,-1,-1, // v0-v3-v4 (right)
	1,-1,-1, 1, 1,-1, 1, 1, 1, // v4-v5-v0
	1, 1, 1, 1, 1,-1, -1, 1,-1, // v0-v5-v6 (top)
	-1, 1,-1, -1, 1, 1, 1, 1, 1, // v6-v1-v0
	-1, 1, 1, -1, 1,-1, -1,-1,-1, // v1-v6-v7 (left)
	-1,-1,-1, -1,-1, 1, -1, 1, 1, // v7-v2-v1
	-1,-1,-1, 1,-1,-1, 1,-1, 1, // v7-v4-v3 (bottom)
	1,-1, 1, -1,-1, 1, -1,-1,-1, // v3-v2-v7
	1,-1,-1, -1,-1,-1, -1, 1,-1, // v4-v7-v6 (back)
	-1, 1,-1, 1, 1,-1, 1,-1,-1 }; // v6-v5-v4

Color HelloGL::colors[] = { 1, 1, 1, 1, 1, 0, 1, 0, 0, // v0-v1-v2 (front)
	1, 0, 0, 1, 0, 1, 1, 1, 1, // v2-v3-v0
	1, 1, 1, 1, 0, 1, 0, 0, 1, // v0-v3-v4 (right)
	0, 0, 1, 0, 1, 1, 1, 1, 1, // v4-v5-v0
	1, 1, 1, 0, 1, 1, 0, 1, 0, // v0-v5-v6 (top)
	0, 1, 0, 1, 1, 0, 1, 1, 1, // v6-v1-v0
	1, 1, 0, 0, 1, 0, 0, 0, 0, // v1-v6-v7 (left)
	0, 0, 0, 1, 0, 0, 1, 1, 0, // v7-v2-v1
	0, 0, 0, 0, 0, 1, 1, 0, 1, // v7-v4-v3 (bottom)
	1, 0, 1, 1, 0, 0, 0, 0, 0, // v3-v2-v7
	0, 0, 1, 0, 0, 0, 0, 1, 0, // v4-v7-v6 (back)
	0, 1, 0, 0, 1, 1, 0, 0, 1 }; // v6-v5-v4

Vertex HelloGL::indexedVertices[] = { 1, 1, 1, -1, 1, 1, // v0,v1,
	-1,-1, 1, 1,-1, 1, // v2,v3
	1,-1,-1, 1, 1,-1, // v4,v5
	-1, 1,-1, -1,-1,-1 }; // v6,v7

Color HelloGL::indexedColors[] = { 1, 1, 1, 1, 1, 0, // v0,v1,
	1, 0, 0, 1, 0, 1, // v2,v3
	0, 0, 1, 0, 1, 1, // v4,v5
	0, 1, 0, 0, 0, 0 }; //v6,v7

GLushort HelloGL::indices[] = { 0, 1, 2, 2, 3, 0, // front
	0, 3, 4, 4, 5, 0, // right
	0, 5, 6, 6, 1, 0, // top
	1, 6, 7, 7, 2, 1, // left
	7, 4, 3, 3, 2, 7, // bottom
	4, 7, 6, 6, 5, 4 }; // back

HelloGL::HelloGL(int argc, char* argv[])
{
	rotation = 0.0f;
	camera = new Camera();
	camera->eye.x = 5.0f; camera->eye.y = 5.0f; camera->eye.z = 5.0f;
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

	//enables back face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glutMainLoop();
}

HelloGL::~HelloGL(void)
{
	delete camera;
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//DrawCube();
	DrawIndexedCube();
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

void HelloGL::DrawCube()
{
	glBegin(GL_TRIANGLES);

		//face v0-v1-v2

		glColor3f(1, 1, 1);
		glVertex3f(1, 1, 1);
		glColor3f(1, 1, 0);
		glVertex3f(-1, 1, 1);
		glColor3f(1, 0, 0);
		glVertex3f(-1, -1, 1);

		// face v2-v3-v0

		glColor3f(1, 0, 0);
		glVertex3f(-1, -1, 1);
		glColor3f(1, 0, 1);
		glVertex3f(1, -1, 1);
		glColor3f(1, 1, 1);
		glVertex3f(1, 1, 1);

		// face v0-v3-v4

		glColor3f(1, 1, 1);
		glVertex3f(1, 1, 1);
		glColor3f(1, 0, 1);
		glVertex3f(1, -1, 1);
		glColor3f(0, 0, 1);
		glVertex3f(1, -1, -1);

		// face v4-v5-v0

		glColor3f(0, 0, 1);
		glVertex3f(1, -1, -1);
		glColor3f(0, 1, 1);
		glVertex3f(1, 1, -1);
		glColor3f(1, 1, 1);
		glVertex3f(1, 1, 1);

		// face v0-v5-v6

		glColor3f(1, 1, 1);
		glVertex3f(1, 1, 1);
		glColor3f(0, 1, 1);
		glVertex3f(1, 1, -1);
		glColor3f(0, 1, 0);
		glVertex3f(-1, 1, -1);

		// face v6-v1-v0

		glColor3f(0, 1, 0);
		glVertex3f(-1, 1, -1);
		glColor3f(1, 1, 0);
		glVertex3f(-1, 1, 1);
		glColor3f(1, 1, 1);
		glVertex3f(1, 1, 1);

		// face v1-v6-v7

		glColor3f(1, 1, 0);
		glVertex3f(-1, 1, 1);
		glColor3f(0, 1, 0);
		glVertex3f(-1, 1, -1);
		glColor3f(0, 0, 0);
		glVertex3f(-1, -1, -1);

		// face v7-v2-v1

		glColor3f(0, 0, 0);
		glVertex3f(-1, -1, -1);
		glColor3f(1, 0, 0);
		glVertex3f(-1, -1, 1);
		glColor3f(1, 1, 0);
		glVertex3f(-1, 1, 1);

		// face v7-v4-v3

		glColor3f(0, 0, 0);
		glVertex3f(-1, -1, -1);
		glColor3f(0, 0, 1);
		glVertex3f(1, -1, -1);
		glColor3f(1, 0, 1);
		glVertex3f(1, -1, 1);

		// face v3-v2-v7

		glColor3f(1, 0, 1);
		glVertex3f(1, -1, 1);
		glColor3f(1, 0, 0);
		glVertex3f(-1, -1, 1);
		glColor3f(0, 0, 0);
		glVertex3f(-1, -1, -1);


		// face v4-v7-v6

		glColor3f(0, 0, 1);
		glVertex3f(1, -1, -1);
		glColor3f(0, 0, 0);
		glVertex3f(-1, -1, -1);
		glColor3f(0, 1, 0);
		glVertex3f(-1, 1, -1);

		// face v6-v5-v4

		glColor3f(0, 1, 0);
		glVertex3f(-1, 1, -1);
		glColor3f(0, 1, 1);
		glVertex3f(1, 1, -1);
		glColor3f(0, 0, 1);
		glVertex3f(1, -1, -1);

	glEnd();
}

void HelloGL::DrawCubeArray()
{
	glPushMatrix();

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 36; i++)
	{
		glColor3fv(&colors[i].r);
		glVertex3fv(&vertices[i].x);
	}
}

void HelloGL::DrawIndexedCube()
{
	glPushMatrix();

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < 36; i++)
		{
			glColor3fv(&indexedColors[indices[i]].r);
			glVertex3fv(&indexedVertices[indices[i]].x);
		}
		glEnd();

	glPopMatrix();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'a')
	{
		camera->eye.x += 1.0f; camera->eye.y += 0.0f; camera->eye.z += 1.0f;
	}
	if (key == 'd')
		rotation += 10.0f;
}