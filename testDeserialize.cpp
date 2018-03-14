#include "helper.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main(){
	vector<State> res = deserializeStore("data/game1.bin");
	for(State s : res)
		s.print();
	return 0;
}