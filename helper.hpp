class Ball{
	private:
		float pos[2];
		float vel[2];
	public:
		Ball(float pos_in[2], float vel_in[2]);
		float (& getPos()) [2];
		float (& getVel()) [2];
};

class Paddle{
	private:
		float pos[2];
		float vel;
	public:
		Paddle(float pos_in[2], float vel_in);
		float (& getPos()) [2];
		float& getVel();
};

class State{
	private:
		Ball ball;
		Paddle left, right;
	public:
		State(Ball a, Paddle b, Paddle c);
};