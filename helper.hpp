#define PADDLE_WIDTH 0.01f
#define PADDLE_HEIGHT 0.2f 
#define BALL_RAD 0.012
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define ELLIPSE_SCALE WINDOW_WIDTH/WINDOW_HEIGHT
#define SEGMENTS 70
#define STORE_RATE 10 //capture state every 5 frames
#include <vector>
#include <string>
using namespace std;

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
		float paddle_speed = 0.02f;
		float ai_handicap = 0.25f;

		short score[2];
		void reset();
		void print();
		short (& getScore()) [2];
		void pointLeft();
		void pointRight();
		State();
};


void drawPaddle(Paddle paddle);

void drawBall(Ball ball);

void updateBall();

void updateRightPaddle();

void updateLeftPaddle();

void arrowFunc(int key, int x, int y);

void quitFunc(unsigned char key, int x, int y);

void renderScene(void);

void update(int value);

void serializeStore();

vector<State> deserializeStore(string fname);