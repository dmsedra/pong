CC=g++
CFLAGS=-std=c++11

pong:pong.cpp helper.cpp
	$(CC) -o pong pong.cpp helper.cpp $(CFLAGS)

clean: 
	rm -f pong *.o
