#include "helper.hpp"
#include <iostream>

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

float& Paddle::getVel(){
	return vel;
}

State::State(){
	reset();
}

void State::reset(){
	float posBall[2] = {100.,100.};
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