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

void update(int value) {
	cout << "update" << endl;
   // input handling
   updateBall(state);

   // update ball
   updatePaddle(state);

   // Call update() again in 'interval' milliseconds
   glutTimerFunc(300, update, 0);

   // Redisplay frame
   glutPostRedisplay();
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
	glutKeyboardFunc(quitFunc);
	glutSpecialFunc(arrowFunc);
	glutDisplayFunc(renderScene);
	glutTimerFunc(300, update, 0);

	// enter GLUT event processing cycle
	glutMainLoop();

  return 0;
}

