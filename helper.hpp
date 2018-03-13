#define PADDLE_WIDTH 0.01f
#define PADDLE_HEIGHT 0.3f 
#define BALL_RAD 0.025
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define ELLIPSE_SCALE WINDOW_WIDTH/WINDOW_HEIGHT
#define SEGMENTS 70

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
		float& getOffset();
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

void drawPaddle(Paddle paddle);

void drawBall(Ball ball);