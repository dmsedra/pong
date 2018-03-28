#include <iostream>
#include <vector>
#include <fstream>
#include "trainer.hpp"

using namespace std;


void Policy::train(vector<State*> states){
	cout << states.size() << endl;
}

float Policy::action(State state){
	return -1.f;
}

void Policy::save(){
	ofstream file;
	string fname = "models/policy.bin";
	file.open(fname , ofstream::binary);

	file.write((char*)this, sizeof(this));
	cout << "serializing " << sizeof(this) << " bytes" << endl;
	file.close();
}

int main(int argc, char** argv){
	if(argc < 2) {cout << "requires game file " << endl; return 0;}

	string fname = argv[1];
	vector<State*> res = deserializeStore("data/" + fname + ".bin");
	Policy policy;
	policy.train(res);
	policy.save();

	return 0;
}