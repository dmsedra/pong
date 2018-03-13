#include "helper.hpp"
#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <linux/input.h>
#include <fstream>

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

void Ball::setRad(float rad_in){
	rad = rad_in;
}

float (&Ball::getPos()) [2]{
	return pos;
}

float (&Ball::getVel()) [2]{
	return vel;
}

float Ball::getRad(){
	return rad;
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
	float velBall[2] = {0.01,0.};

	ball.setPos(posBall);

	left.setPos(0.,-0.97f);
	right.setPos(0., 0.97f);

	ball.setVel(velBall);
	ball.setRad(BALL_RAD);
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

void drawBall(Ball ball){ 
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

void updateBall(State state){
	float* pos = state.ball.getPos();
	float rad = state.ball.getRad();

	//upper right counter clockwise
	float ball_corners[4][2] = {{pos[0]+rad,pos[1]+rad}, {pos[0]-rad,pos[1]+rad}, {pos[0]-rad,pos[1]-rad}, {pos[0]+rad,pos[1]-rad}};

	float left_upper[2] = {state.left.getOffset()+PADDLE_WIDTH, state.left.getPos()+PADDLE_HEIGHT}; 
	float left_lower[2] = {state.left.getOffset()+PADDLE_WIDTH, state.left.getPos()-PADDLE_HEIGHT};

	float right_upper[2] = {state.right.getOffset()-PADDLE_WIDTH, state.right.getPos()+PADDLE_HEIGHT}; 
	float right_lower[2] = {state.right.getOffset()-PADDLE_WIDTH, state.right.getPos()-PADDLE_HEIGHT};

	

	//Hit right paddle
	if((ball_corners[0][0] >= right_upper[0]) && (ball_corners[3][1] <= right_upper[1]) && (ball_corners[0][1] >= right_lower[1])){
		float* vel = state.ball.getVel();
		float new_vel[2] = {-vel[0], vel[1]};
		state.ball.setVel(new_vel);
	}

	//TODO add more

	float* vel = state.ball.getVel();
	float new_pos[2] = {pos[0]+1.f*vel[0], pos[1]+1.f*vel[1]};
	state.ball.setPos(new_pos); 
}

void updatePaddle(State state){
	float pos = state.right.getPos();

	
	float new_pos = min(1.f, pos + state.right.getVel());
	float offset = state.right.getOffset();
	new_pos = max(-1.f, new_pos);
	state.right.setPos(new_pos, offset);
}

void arrowFunc(int key, int x, int y){
	switch(key){
		case GLUT_KEY_UP:
			cout << "UP" << endl;
			break;
		case GLUT_KEY_DOWN:
			cout << "DOWN" << endl;
			break;
	}
}

void quitFunc(unsigned char key, int x, int y){
	if(key == 'q')
		exit(0);
}