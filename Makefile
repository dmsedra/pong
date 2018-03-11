CC=g++
CFLAGS=-std=c++11 -lglut -lGL
OPENGL = `pkg-config opengl --cflags --libs`
LIBS = $(OPENGL)

pong:pong.cpp helper.cpp
	$(CC) -o pong pong.cpp helper.cpp $(CFLAGS)

clean: 
	rm -f pong 
