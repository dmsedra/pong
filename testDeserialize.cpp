#include "helper.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main(){
	
	vector<State> res = deserializeStore("data/969464.bin");
	cout << " good so far " << endl;
	for(State s : res)
		s.print();
	return 0;
}