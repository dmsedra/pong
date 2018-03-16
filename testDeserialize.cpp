#include "helper.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char**argv){
	if(argc < 2) return 0;

	string fname = argv[1];
	cout << "data/" + fname + ".bin" << endl;
	vector<State*> res = deserializeStore("data/" + fname + ".bin");
	cout << " good so far " << endl;
	for(State* s : res)
		s->print();
		//whatever you want to do with the game here

	return 0;
}