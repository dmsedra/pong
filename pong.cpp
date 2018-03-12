#include <iostream>
#include "helper.hpp"
#include <GL/glut.h>

using namespace std;


int main()
{
	
	float pos_ball[2] = {10.,11.};
	float vel_ball[2] = {0.,0.};
	Ball ball = Ball(pos_ball, vel_ball);  

	float pos_paddle[2] = {13.,14.};
	float vel_paddle = 0.;
	Paddle left = Paddle(pos_paddle, vel_paddle);

	float pos_paddle2[2] = {15.,17.};
	float vel_paddle2 = 0.;
	Paddle right = Paddle(pos_paddle2, vel_paddle2);


  return 0;
}