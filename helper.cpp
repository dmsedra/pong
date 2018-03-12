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

void Paddle::setPos(float pos_in[2]){
	pos[0] = pos_in[0];
	pos[1] = pos_in[1];
}

void Paddle::setVel(float vel_in){
	vel = vel_in;
}

float (& Paddle::getPos()) [2]{
	return pos;
}

float& Paddle::getVel(){
	return vel;
}

State::State(){
	this->reset();
}

void State::reset(){
	float pos[2] = {100.,100.};
	float velBall[2] = {0.,0.};
	float velPaddle = 0.;

	ball.setPos(pos);
	pos[0] = 0.; pos[1] = 100;
	left.setPos(pos);
	pos[0] = 100; pos[1] = 200;
	right.setPos(pos);

	ball.setVel(velBall);
	left.setVel(velPaddle);
	right.setVel(velPaddle);
}

void State::print(){
	cout << "Ball (" << ball.getPos()[0] << "," << ball.getPos()[1];
	cout << ") (" << ball.getVel()[0] << "," << ball.getVel()[1] << ")  ";

	cout << "Left (" << left.getPos()[0] << "," << left.getPos()[1];
	cout << ") (" << left.getVel() << ")  ";

	cout << "Right (" << right.getPos()[0] << "," << right.getPos()[1];
	cout << ") (" << right.getVel() << ")";

	cout << endl;
}