#include "helper.hpp"

using namespace std;

Ball::Ball(float pos_in[2], float vel_in[2]){
	pos[0] = pos_in[0];
	pos[1] = pos_in[1];
	vel[0] = vel_in[0];
	vel[1] = vel_in[1];
}

float (&Ball::getPos()) [2]{
	return pos;
}

float (&Ball::getVel()) [2]{
	return vel;
}

Paddle::Paddle(float pos_in[2], float vel_in){
	pos[0] = pos_in[0];
	pos[1] = pos_in[1];
	vel = vel_in;
}

float (& Paddle::getPos()) [2]{
	return pos;
}

float& Paddle::getVel(){
	return vel;
}

State::State(Ball a, Paddle b, Paddle c): ball(a), left(b), right(c){
}