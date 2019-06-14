#include <iostream>
#include <string>

//备忘录
class Memento{
public:
	Memento(std::string state)
		: _state(state){}
	
	std::string getState(void){
		return _state;
	}
	void setState(std::string newState){
		if (_state != newState){
			_state = newState;
		}
	}
private:
	std::string _state;
};

//发起者
class Originator
{
public:
	~Originator(){
		if (_memento)
			delete _memento;
	}
	void createMemeto(void){
		_memento = new Memento(_state);
	}

	Memento* getMemento(){
		return _memento;
	}

	void setMemento(Memento* mem){
		if (_memento != mem){
			_memento = mem;
			_state = mem->getState();
		}
	}

	std::string getState(void){
		return _state;
	}
	void setState(std::string newState){
		if (_state != newState)
			_state = newState;
	}

	void displayState(){
		std::cout << "State= " << _state << std::endl;
	}
private:
	std::string _state;
	Memento* _memento = nullptr;
};
//管理者
class CareTaker{
public:
	Memento* getMemento(){
		return _memento;
	}

	void setMemento(Memento* memento){
		if (_memento != memento)
			_memento = memento;
	}
private:
	Memento* _memento = nullptr;
};
int main(int argc, char* argv[])
{
	Originator* originator = new Originator();	
	originator->setState("First");
	originator->displayState();
	
	originator->createMemeto();
	originator->setState("Second");
	originator->displayState();

	CareTaker* careTaker = new CareTaker();
	careTaker->setMemento(originator->getMemento());
	std::cout << std::endl <<  "CareTaker State = " << careTaker->getMemento()->getState() << std::endl;

	delete originator;
	delete careTaker;

	system("pause");
	return 0;
}