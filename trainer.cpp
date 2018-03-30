#include <iostream>
#include <vector>
#include <fstream>
#include "trainer.hpp"

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
void quantize(short out[6], float ball_vel[2], float ball_pos[2], float paddle_pos, short score)
{
	out[0] = int(ball_vel[0]*100);
	out[1] = int(ball_vel[1]*100);
	out[2] = int(ball_pos[0]*5);
	out[3] = int(ball_pos[1]*5);
	out[4] = int(paddle_pos*5);
	out[5] = score;
}

void Policy::train(vector<State*> states){
	short quant[6];
	short prev_score[2] = {0,0};

	for(State* s : states){
		//s->print();
		short score = (s->score[1]-prev_score[1]) - (s->score[0]-prev_score[0]);
		quantize(quant, s->ball.getVel(), s->ball.getPos(), s->left.getPos(), score);
		cout << quant[5] << endl;
		prev_score[0] = s->score[0];
		prev_score[1] = s->score[1];
	}
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

int main(int argc, char** argv){
	if(argc < 2) {cout << "requires game file " << endl; return 0;}

	string fname = argv[1];
	vector<State*> res = deserializeStore("data/" + fname + ".bin");
	Policy policy;
	policy.train(res);
	policy.save();

	return 0;
}