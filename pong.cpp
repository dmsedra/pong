#include <iostream>
#include "helper.hpp"

//#include <GL/gl.h>
//#include <GL/glu.h>
//#include "GL/freeglut.h"
#include <GL/glut.h>

using namespace std;

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_QUADS);
	glColor3f(0.3f, 1.0f, 0.3f); //You can set RGB color for you vertex
	
	float x1 = -0.98f;
	float y1 = 0.3f;
	float x2 = -0.96f;
	float y2 = -0.3f;

	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);

	glEnd();

	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(1500,800);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Pong");

	State state;
	state.print();

	glutDisplayFunc(renderScene);

	// enter GLUT event processing cycle
	glutMainLoop();

  return 0;
}

