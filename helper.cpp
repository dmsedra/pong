#include "helper.hpp"
#include <iostream>
#include <cmath>
#include <GL/glut.h>

using namespace std;

Ball::Ball(){

}

void Ball::setPos(float pos_in[2]){
	pos[0] = pos_in[0];
	pos[1] = pos_in[1];
}

void Ball::setVel(float vel_in[2]){
	vel[0] = vel_in[0];
	vel[1] = vel_in[1];
}

float (&Ball::getPos()) [2]{
	return pos;
}

float (&Ball::getVel()) [2]{
	return vel;
}

Paddle::Paddle(){
}

void Paddle::setPos(float pos_in,  float x){
	pos = pos_in;
	x_offset = x;
}

void Paddle::setVel(float vel_in){
	vel = vel_in;
}

float& Paddle::getPos(){
	return pos;
}

float& Paddle::getOffset(){
	return x_offset;
}

float& Paddle::getVel(){
	return vel;
}

State::State(){
	reset();
}

void State::reset(){
	float posBall[2] = {0.,0.};
	float velBall[2] = {0.,0.};

	ball.setPos(posBall);

	left.setPos(0.,-0.97f);
	right.setPos(0., 0.97f);

	ball.setVel(velBall);
	left.setVel(0.);
	right.setVel(0.);
}

void State::print(){
	cout << "Ball (" << ball.getPos()[0] << "," << ball.getPos()[1];
	cout << ") (" << ball.getVel()[0] << "," << ball.getVel()[1] << ")  ";

	cout << "Left (" << left.getPos();
	cout << ") (" << left.getVel() << ")  ";

	cout << "Right (" << right.getPos();
	cout << ") (" << right.getVel() << ")";

	cout << endl;
}

void drawPaddle(Paddle paddle){
	float x_offset = paddle.getOffset();
	float pos = paddle.getPos();

	glBegin(GL_QUADS);
	glColor3f(0.3f, 1.0f, 0.3f); 
	float x1 = x_offset-PADDLE_WIDTH;
	float y1 = pos+PADDLE_HEIGHT;
	float x2 = x_offset+PADDLE_WIDTH;
	float y2 = pos-PADDLE_HEIGHT;

	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glEnd();
}

void drawBall(Ball ball)
	//float cx, float cy, float rx, float ry, int num_segments) 
{ 
	float* pos = ball.getPos();
	float cx = pos[0];
	float cy = pos[1];
	float rx = BALL_RAD;
	float ry = BALL_RAD*ELLIPSE_SCALE;

	float theta = 2 * 3.1415926 / float(SEGMENTS); 
	float c = cosf(theta);//precalculate the sine and cosine
	float s = sinf(theta);
	float t;

	float x = 1;//we start at angle = 0 
	float y = 0; 

	glBegin(GL_LINE_LOOP); 
	glColor3f(1.0f, 0.7f, 0.7f); 
	for(int ii = 0; ii < SEGMENTS; ii++) 
	{ 
	    //apply radius and offset
	    glVertex2f(x * rx + cx, y * ry + cy);//output vertex 

	    //apply the rotation matrix
	    t = x;
	    x = c * x - s * y;
	    y = s * t + c * y;
	} 
	glEnd(); 
}