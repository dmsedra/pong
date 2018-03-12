class Ball{
	private:
		float pos[2];
		float vel[2];
	public:
		Ball();
		void setPos(float pos[2]);
		void setVel(float vel[2]);
		float (& getPos()) [2];
		float (& getVel()) [2];
};

class Paddle{
	private:
		float pos[2];
		float vel;
	public:
		Paddle();
		void setPos(float pos[2]);
		void setVel(float vel);
		float (& getPos()) [2];
		float& getVel();
};

class State{
	public:
		Ball ball;
		Paddle left, right;
		void reset();
		void print();
		State();
};

