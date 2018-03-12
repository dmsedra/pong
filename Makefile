CC=g++
CFLAGS=-std=c++11 -lglut -lGL
OPENGL = `pkg-config opengl --cflags --libs`
LIBS = $(OPENGL)

pong: helper.cpp pong.cpp
	$(CC) -o pong helper.cpp pong.cpp $(CFLAGS)

clean: 
	rm -f pong 
