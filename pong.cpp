#include <iostream>
#include "helper.hpp"
#include <cmath>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <string.h>

using namespace std;

int main(int argc, char* argv[])
{
	//init
	for(short i = 0; i < 100; i++){
		glutInit(&argc, argv);


		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
		glutInitWindowPosition(200, 0);
		glutInitWindowSize(1200,800);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
		glutCreateWindow("Pong");

		//set callback
		glutKeyboardFunc(quitFunc);
		glutDisplayFunc(renderScene);

		if(argc == 1){
			cout << "Needs run mode for right paddle: human | ai | learn" << endl;
			exit(0);
		}
		else if(strcmp(argv[1],"human") == 0){
			glutSpecialFunc(arrowFunc);
			glutTimerFunc(20, update, 0);
		}
		else if(strcmp(argv[1],"ai") == 0){
			glutTimerFunc(20, update, 1);
		}
		else if(strcmp(argv[1],"learn") == 0){
			glutTimerFunc(20, update, 2);
		}
		else{
			cout << "Invalid run mode!" << endl;
			exit(0);
		}

		// enter GLUT event processing cycle
		glutMainLoop();
	}

		cout << "done" << endl;

  return 0;
}

