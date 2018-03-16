#include "helper.hpp"
#include <iostream>
#include <cmath>
#include <ctime>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <linux/input.h>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

State state;
vector<State> store;

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
	cout << "reset" << endl;
	score[0] = 0;
	score[1] = 0;
	ai_handicap = 0.7f;
	paddle_speed = 0.02f;
	begin = clock();
	float posBall[2] = {0.,0.};
	srand (time(NULL));
	float ball_dir = (rand()%365)*2.f*M_PI/365.f;

	float x = cosf(ball_dir)*0.05f;
	float y = sinf(ball_dir)*0.05f;

	float velBall[2] = {x,y};

	ball.setPos(posBall);

	left.setPos(0.,-0.99f);
	right.setPos(0., 0.99f);

	ball.setVel(velBall);
	ball.setRad(BALL_RAD);
	left.setVel(0.);
	right.setVel(0.);
}

short (&State::getScore()) [2]{
	return score;
}

void State::pointLeft(){
	score[0] += 1;
}

void State::pointRight(){
	score[1] += 1;
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

	glBegin(GL_LINES); 
	glColor3f(1.0f, 1.0f, 1.0f); 
	for(int ii = 0; ii < SEGMENTS; ii++) 
	{ 
		//apply radius and offset
		glVertex2f(pos[0], pos[1]);
		glVertex2f(x * rx + cx, y * ry + cy);//output vertex 

		//apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	} 
	glEnd(); 
}

void drawScore(){
	glColor3f(1.0f, 0.7f, 0.7f); 
	short* score = state.getScore();

	glRasterPos2f(0., 0.9f);
	string text = to_string(score[0]) + ":" + to_string(score[1]);
  glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)text.c_str());
}

void updateBall(){
	float* pos = state.ball.getPos();
	float* vel = state.ball.getVel();
	float rad = state.ball.getRad();

	
	//upper right counter clockwise
	float ball_corners[4][2] = {{pos[0]+rad,pos[1]+rad}, {pos[0]-rad,pos[1]+rad}, {pos[0]-rad,pos[1]-rad}, {pos[0]+rad,pos[1]-rad}};

	float left_upper[2] = {state.left.getOffset()+PADDLE_WIDTH, state.left.getPos()+PADDLE_HEIGHT}; 
	float left_lower[2] = {state.left.getOffset()+PADDLE_WIDTH, state.left.getPos()-PADDLE_HEIGHT};

	float right_upper[2] = {state.right.getOffset()-PADDLE_WIDTH, state.right.getPos()+PADDLE_HEIGHT}; 
	float right_lower[2] = {state.right.getOffset()-PADDLE_WIDTH, state.right.getPos()-PADDLE_HEIGHT};

	float new_vel[2] = {vel[0], vel[1]};
	

	//Hit right paddle
	if((ball_corners[0][0] >= right_upper[0]) && (ball_corners[3][1] <= right_upper[1]) && (ball_corners[0][1] >= right_lower[1]))
		new_vel[0] *= -1.f;
	else if((ball_corners[1][0] <= left_upper[0]) && (ball_corners[2][1] <= left_upper[1]) && (ball_corners[1][1] >= left_lower[1]))
		new_vel[0] *= -1.f;
	else	if (ball_corners[0][0] >= 1.f){
		state.pointLeft();
		new_vel[0] *= -1.f;
	}
	else	if (ball_corners[1][0] <= -1.f){
		state.pointRight();
		new_vel[0] *= -1.f;
	}

	if (ball_corners[0][1] >= 1.f)
		new_vel[1] *= -1.f;
	if (ball_corners[3][1] <= -1.f)
		new_vel[1] *= -1.f;

	state.ball.setVel(new_vel);

	vel = state.ball.getVel();
	float new_pos[2] = {pos[0]+1.f*vel[0], pos[1]+1.f*vel[1]};
	state.ball.setPos(new_pos); 
}

void humanRight(){
	float pos = state.right.getPos();
	float offset = state.right.getOffset();
	float new_pos = max(-1.f+PADDLE_HEIGHT, min(1.f-PADDLE_HEIGHT, pos + state.paddle_speed*state.right.getVel()));
	state.right.setPos(new_pos, offset);
	//state.right.setVel(0.f); //Allows continuous movement
}

void perfectAIRight(){
	float* ball_pos = state.ball.getPos();
	float* ball_vel = state.ball.getVel();
	float paddle_pos = state.right.getPos();

 	float intercept = ball_pos[1] + ball_vel[1] * ((ball_pos[0]+1.f)/ball_vel[0]);

 	//going right
	if(ball_vel[0] >= 0){
		if(intercept > paddle_pos)
			state.right.setVel(1.f);
		else if(intercept < paddle_pos)
			state.right.setVel(-1.f);
		else
			state.right.setVel(0.f);
	}
	else if (abs(paddle_pos)>state.paddle_speed)
		state.right.setVel((paddle_pos>0)?-1.f:1.f);
	else
		state.right.setVel(0.f);

	float offset = state.right.getOffset();
	float new_pos = max(-1.f+PADDLE_HEIGHT, min(1.f-PADDLE_HEIGHT, paddle_pos + state.ai_handicap*state.paddle_speed*state.right.getVel()));
	state.right.setPos(new_pos, offset);
}

void perfectAILeft(){
	float* ball_pos = state.ball.getPos();
	float* ball_vel = state.ball.getVel();
	float paddle_pos = state.left.getPos();

 	float intercept = ball_pos[1] - ball_vel[1] * ((ball_pos[0]+1.f)/ball_vel[0]);

 	//going left
	if(ball_vel[0] <= 0){
		if(intercept > paddle_pos)
			state.left.setVel(1.f);
		else if(intercept < paddle_pos)
			state.left.setVel(-1.f);
		else
			state.left.setVel(0.f);
	}
	else if (abs(paddle_pos)>state.paddle_speed)
		state.left.setVel((paddle_pos>0)?-1.f:1.f);
	else
		state.left.setVel(0.f);

	float offset = state.left.getOffset();
	float new_pos = max(-1.f+PADDLE_HEIGHT, min(1.f-PADDLE_HEIGHT, paddle_pos + state.ai_handicap*state.paddle_speed*state.left.getVel()));
	state.left.setPos(new_pos, offset);
}

void arrowFunc(int key, int x, int y){
	switch(key){
		case GLUT_KEY_UP:
			state.right.setVel(1.f);
			break;
		case GLUT_KEY_DOWN:
			state.right.setVel(-1.f);
			break;
	}
}

void quitFunc(unsigned char key, int x, int y){
	if(key == 'q'){
		exit(0);
	}
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawScore();
	drawPaddle(state.left);
	drawPaddle(state.right);
	drawBall(state.ball);
	
	glutSwapBuffers();
}

void updateStore(int value){
	if(value%STORE_RATE == 0){
		State copy_state = state;
		store.push_back(copy_state);
	}
}

void serializeStore(){

	ofstream file;
	string fname = "data/" + to_string(rand()%1000000) + ".bin";
	state.binary_file = fname;
	file.open(fname , ofstream::binary);
	cout << store.size() << " beginning" << endl;
	State buffer[store.size()];

	copy(store.begin(), store.end(), buffer);
	file.write((char*)buffer, store.size()*sizeof(State));
	cout << "serializing " << store.size() << " " << sizeof(State) << buffer << endl;
	file.close();

	state.reset();
	store.clear();
}

vector<State*> deserializeStore(string fname){
	vector<State*> res;
	ifstream file;
	file.open(fname, ifstream::binary);

	if(!file.is_open()){cout << "bad file " << endl;return res;}
	char buffer[sizeof(State)];

	file.read(buffer, sizeof(State));

	while(file){
		char* s = new char[sizeof(State)];
		copy(buffer, buffer+sizeof(State), s);
		
		res.push_back(((State*)s));
		file.read(buffer, sizeof(State));
	}

	file.close();
	return res;
}

void update(int value) {
	if (max(state.score[0],state.score[1]) == 11){
		serializeStore();
		glutLeaveMainLoop();
	}
	else if(double(clock()-state.begin)/CLOCKS_PER_SEC > 20){
		cout << "time out" << endl;
		state.reset();
		store.clear();
		glutLeaveMainLoop();
	}
	updateStore(value);
	updateBall();
	perfectAILeft();
	perfectAIRight();
	glutTimerFunc(25, update, value);
	glutPostRedisplay();
}