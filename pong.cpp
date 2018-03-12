#include <iostream>
#include "helper.hpp"

//#include <GL/gl.h>
//#include <GL/glu.h>
//#include "GL/freeglut.h"
#include <GL/glut.h>

using namespace std;

void drawPaddle(float pos, float x_offset){
	glBegin(GL_QUADS);
	glColor3f(0.3f, 1.0f, 0.3f); 
	float x1 = x_offset-PADDLE_WIDTH;
	float y1 = pos+PADDLE_HEIGHT;
	float x2 = x_offset+PADDLE_WIDTH;
	float y2 = pos-PADDLE_HEIGHT;

	cout << x1 << y1 << x2 << y2 << endl;
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glEnd();
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawPaddle(0.f,-0.97f);
	drawPaddle(0.f,0.97f);

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

