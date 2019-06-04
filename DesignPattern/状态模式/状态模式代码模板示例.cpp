#include <iostream>
#include <string>
class State
{
public:
	virtual void handle(void) {
		std::cout << "- - " << std::endl;
	}
};

class StateA : public State
{
public:
	void handle(void) {
		std::cout << "A handler！" << std::endl;
	}
};

class StateB : public State
{
public:
	void handle(void) {
		std::cout << "B handler ！" << std::endl;
	}
};

class Context
{
public:
	Context(State* state):_state(state) {};
	~Context() {
		if (_state) {
			delete _state;
			_state = NULL;
		}
	};

	State* getState(void) { return _state; }
	void setState(State* state) {
		if (_state != state)
			_state = state;
	}

	void request(void) {
		if(_state)
			_state->handle();
	}
private:
	State* _state;
};

int main(int argc, char*argv[])
{
	char c = '\0';
	State* tmp = NULL;
	Context* context = new Context(tmp);
	while ((c != 'q') || (c != 'Q')) {
		std::cout << "Please select your choose : " << std::endl;
		std::cin >> c;
		switch (c)
		{
			case 'A':
			case 'a':
				tmp = new StateA();
				break;
			case 'b':
			case 'B':
				tmp = new StateB();
				break;
			default:
				std::cout << "Invalid input, please input q or Q to quit !" << std::endl;
				return 0;
				break;
		}
		context->setState(tmp);
		context->request();
		delete tmp;
		tmp = NULL;
	}
	delete context;
	if(tmp) delete tmp;
	system("pause");
	return 0;
}