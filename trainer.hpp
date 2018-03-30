#ifndef TRAINER_H
#define TRAINER_H

#include "helper.hpp"
#include <vector>
#include <unordered_map>
#define BALL_VELOCITY_SPACE 5
#define BALL_POS_SPACE 5
#define PADDLE_POS 5
#define GAMMA 0.99424 //GAMMA^120 = 0.5

#define STATE_SPACE BALL_VELOCITY_SPACE*BALL_VELOCITY_SPACE*BALL_POS_SPACE*BALL_POS_SPACE*PADDLE_POS

using namespace std;

class Model{
	public:
		virtual void train() = 0;
		virtual float action(State state) = 0;
		virtual void save() = 0;
};

class Policy:public Model{
	public:
		float value[STATE_SPACE] = {0.};
		void train();
		float action(State state);
		void save();

		float computeBestAction(State& state);
		float computeValue(State state, short depth);
		float computeReward(State s1, short action);
		void updateState(State& s1, State& s2, short action);
		void updateN(State& s1, State& s2, short action, short n);
};

#endif