
# Pong in C++
## Screenshots
![Screen shot of gameplay](images/screen2.png)

## Description
Simple game of pong implemented completely in C++ and Glut. The purpose of this project is twofold. 

1. Learn C++ with a minimum of external libraries and packages. This means that only what is *absolutely required* is included.
2. Implement some basic AI opponents against the human player. 

As such, there are two modes of controlling the paddles.

1. Human control using the UP and DOWN arrow keys to control the paddle (only enabled for right paddle).
2. Perfect AI, which has access to the ball's position and speed. It is a simple calculation that yields the intercept point with the wall. Based on the paddle's current position, the direction of motion can be computed. 
3. Learned AI, which does not *know* the formula for ball intercepts and must learn it. 

## Playground
To facilitate learning algorithms, the game has the option to play with Perfect AI on both paddles, recording each state of the game in a binary file. These files can then be used to train a variety of algorithms to learn to play for Learned AI.

## Prerequisites 
* OpenGL
* Freeglut
* GCC

## Install + Run (for Linux, see Notes)
```
$make
$./pong
```

## How to play
Simply use up and down arrow keys on keyboard to control the right paddle. The left player is controlled by the AI, which is easily substituted. Currently the perfect solution is implemented where the paddle has access to the ball trajectory. In order to make thing more fair, a "handicap" is implemented for the AI (basically forcing it to play at a slower speed).

## Notes
Since C++ is platform dependent, the functionality may vary. As far as I know, I used standard Glut components which should make it operate across platforms. **I haven't tested this!**