#include <iostream>
#include "helper.hpp"
#include <cmath>
#include <GL/glut.h>

using namespace std;

int main(int argc, char* argv[])
{
	//init
	glutInit(&argc, argv);
	glutInitWindowPosition(200, 0);
	glutInitWindowSize(1200,800);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Pong");

	//set callbacks
	glutKeyboardFunc(quitFunc);
	glutSpecialFunc(arrowFunc);
	glutDisplayFunc(renderScene);
	glutTimerFunc(300, update, 0);

	// enter GLUT event processing cycle
	glutMainLoop();

  return 0;
}

