#include "helper.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <GL/glut.h>
#include <GL/freeglut.h>

using namespace std;
vector<State*> res;
extern State state;

void playUpdate(int value){
	if(value < res.size())
		state.set(res[value]);
	else
		exit(0);

	glutTimerFunc(25, playUpdate, value+1);
	glutPostRedisplay();
}

int main(int argc, char**argv){
	if(argc < 2) return 0;

	string fname = argv[1];
	res = deserializeStore("data/" + fname + ".bin");

	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	glutInitWindowPosition(200, 0);
	glutInitWindowSize(1200,800);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Pong Playback");

	//set callbacks
	glutKeyboardFunc(quitFunc);
	//glutSpecialFunc(arrowFunc);
	glutDisplayFunc(renderScene);
	glutTimerFunc(10, playUpdate, 0);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}