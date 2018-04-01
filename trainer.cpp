#include <iostream>
#include <vector>
#include <fstream>
#include "trainer.hpp"
#include <algorithm>

using namespace std;

/*
	Uses:
		Features:
			- ball velocity [-0.05,0.05]x[-0.05,0.05]
			- ball pos [-1,1]x[-1,1]
			- paddle pos [-1,1]
		Reward:
			- score {-1,0,1}, -1 if its past paddle, 0 if not, 1 if on paddle (on next step)
		Output:
			- paddle velocity {-1, 1}
*/

// s1+a = s2
void Policy::updateState(State& s1, State& s2, short action){
	s2.set(&s1);
	s2.right.setVel(action);

	updateBall(s2);
	perfectAILeft(s2);
	humanRight(s2);
}

//updateState holding the action steady for n steps
void Policy::updateN(State& s1, State& s2, short action, short n){
	updateState(s1,s2,action);

	for(short i = 0; i < n-1; i++)
		updateState(s2, s2, action);
}

float Policy::computeReward(State s1, short action){
	State next_state;
	short score;
	updateState(s1, next_state, action);

	score = (next_state.score[1]-s1.score[1]) - (next_state.score[1]-s1.score[0]);
	//cout << score << endl;
	return score;
}

void quantize(short out[5], State s)
{
	short quant[5];
	short prev_score[2] = {0,0};

	float ball_vel[2];
	ball_vel[0] = s.ball.getVel()[0];
	ball_vel[1] = s.ball.getVel()[1];

	float ball_pos[2];
	ball_pos[0] = s.ball.getPos()[0];
	ball_pos[1] = s.ball.getPos()[1];

	float paddle_pos;
	paddle_pos = s.right.getPos();
	

	out[0] = int(ball_vel[0]*40);
	out[1] = int(ball_vel[1]*40);
	out[2] = int(ball_pos[0]*2);
	out[3] = int(ball_pos[1]*2);
	out[4] = int(paddle_pos*2);
}

float Policy::computeValue(State state, short depth)
{

	float reward[3] = {computeReward(state,-1.), computeReward(state,0.), computeReward(state,1.)};
	float value[3] = {0.};
	int n = 10;
	if(depth <= 0)
		return *max_element(reward, reward+3);

	float max_val = -1.;

	for(auto i = 0; i < 3; i++){
		State s2;
		updateN(state, s2, float(i-1.), n); //convert 0,3 to -1,1
		value[i] = reward[i] + GAMMA*computeValue(s2,depth-n);
		max_val = max(max_val, value[i]);
	}

	return max_val;
}

float Policy::computeBestAction(State& state){
	float max_val = -1;
	float max_act = -100;
	float values[3] = {0.};

	for(short a = 0; a < 3; a++){
		float reward = 0;
		float gam = GAMMA;

		State s2;
		updateState(state, s2, a-1);
		for(short j = 0; j < 50; j+=1){
			updateState(s2,s2,a-1);
			reward += gam*computeReward(s2,a-1);
			gam *= GAMMA;
		}
		values[a] = reward;
		if(reward > max_val){
			max_val = reward;
			max_act = a-1;
		}
	}

	if(values[0] == values[1] || values[1] == values[2])
		max_act = 0.;

	cout << max_act << endl;
	state.right.setVel(max_act);

	return max_act;
}

void Policy::train(){
	State start;
	start.reset();

	cout << computeBestAction(start) << endl; 


}

float Policy::action(State state){
	return -1.f;
}

void Policy::save(){
	ofstream file;
	string fname = "models/policy.bin";
	file.open(fname , ofstream::binary);

	file.write((char*)this, sizeof(this));
	file.close();
}

/*
int main(int argc, char** argv){
	Policy policy;
	policy.train();
	policy.save();

	return 0;
}
*/