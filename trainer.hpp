#include "helper.hpp"
#include <vector>

class Model{
	public:
		virtual void train(vector<State*> states) = 0;
		virtual float action(State state) = 0;
		virtual void save() = 0;
};

class Policy:public Model{
	public:
		void train(vector<State*> states);
		float action(State state);
		void save();
};

