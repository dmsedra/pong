CC=g++
CFLAGS=-std=c++11 -lglut -lGL
OPENGL = `pkg-config opengl --cflags --libs`
LIBS = $(OPENGL)

pong: helper.cpp pong.cpp
	$(CC) -o pong helper.cpp pong.cpp $(CFLAGS)

deser:helper.cpp testDeserialize.cpp
	$(CC) -o deser helper.cpp testDeserialize.cpp $(CFLAGS)

clean: 
	rm -f pong deser
