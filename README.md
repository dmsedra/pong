# Pong in C++
Simple game of pong implemented completely in C++ and Glut. The purpose of this project is twofold. 

1. Learn C++ with a minimum of external libraries and packages. This means that only what is *absolutely required* is included.
2. Implement some basic AI opponents against the human player. 

## Screenshots
![Screen shot of gameplay](images/screen2.png)

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