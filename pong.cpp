#include <iostream>
#include "helper.hpp"
#include <cmath>
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include "GL/freeglut.h"
#include <GL/glut.h>

using namespace std;
State state;

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawPaddle(state.left);
	drawPaddle(state.right);
	drawBall(state.ball);
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowPosition(200, 0);
	glutInitWindowSize(1200,800);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Pong");

	State state;
	state.print();

	glutDisplayFunc(renderScene);

	// enter GLUT event processing cycle
	glutMainLoop();

  return 0;
}

