#ifndef HELPER_H
#define HELPER_H

#endif

#define PADDLE_WIDTH 0.01f
#define PADDLE_HEIGHT 0.3f 
#define BALL_RAD 0.025
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define ELLIPSE_SCALE WINDOW_WIDTH/WINDOW_HEIGHT
#define SEGMENTS 70
#define SQRT2 sqrt(2)
#define VK_UP 0x26
#define VK_DOWN 0x28

class Ball{
	private:
		float pos[2];
		float vel[2];
		float rad;
	public:
		Ball();
		void setPos(float pos[2]);
		void setVel(float vel[2]);
		void setRad(float rad);
		float (& getPos()) [2];
		float (& getVel()) [2];
		float getRad();
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

extern State state;

void drawPaddle(Paddle paddle);

void drawBall(Ball ball);

void updateBall(State state);

void updatePaddle(State state);

void arrowFunc(int key, int x, int y);

void quitFunc(unsigned char key, int x, int y);

void renderScene(void);

void update(int value);