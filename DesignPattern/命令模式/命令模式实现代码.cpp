#include <iostream>
#include <string>

//接收者，类似于餐馆点菜系统里面的负责下单的服务员
class Receiver
{
public:
	void action(void){
		std::cout << "Receiver take action " << std::endl;
	}
};

//抽象命令类
class Command
{
public:
	Command(Receiver* recv){
	}
	virtual ~Command(){}
	virtual void execute(void) = 0;
private:
};

//具体命令类，类似于下烤鸡翅单
class ConcreteCommandA : public Command{
public:
	ConcreteCommandA(Receiver* recv)
		: Command(recv)
		, _recv(recv){
		}
	void execute(void){
		std::cout << "ConcreteCommandA::execute " << std::endl;
	}
private:
	Receiver*						_recv;
};

//具体命令类，类似于下烤金针菇单
class ConcreteCommandB : public Command{
public:
	ConcreteCommandB(Receiver* recv)
		: Command(recv)
		, _recv(recv){

	}
	void execute(void){
		std::cout << "ConcreteCommandB::execute " << std::endl;
	}
private:
	Receiver*						_recv;
};

//调用者，类似于厨师，真实地执行烧烤动作
class Invoker
{
public:
	void setCommand(Command* cmd){
		_cmd = cmd;
	}
	void doCommand(void){
		if (_cmd) _cmd->execute();
		else std::cout << "Command's not setted. " << std::endl;
	}
private:
	Command*				_cmd = nullptr;
};

int main(int argc, char* argv[])
{
	Receiver* recv = new Receiver();
	ConcreteCommandA* cmdA = new ConcreteCommandA(recv);
	ConcreteCommandB* cmdB = new ConcreteCommandB(recv);
	Invoker* invoker = new Invoker();
	invoker->setCommand(cmdA);
	invoker->doCommand();

	invoker->setCommand(cmdB);
	invoker->doCommand();
	
	delete cmdA;
	delete invoker;
	delete recv;
	system("pause");
	return 0;
}