#define PADDLE_WIDTH 0.02f
#define PADDLE_HEIGHT 0.6f 

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
		float pos;
		float vel;
		float x_offset; //left or right paddle
	public:
		Paddle();
		void setPos(float pos, float x_offset);
		void setVel(float vel);
		float& getPos();
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

