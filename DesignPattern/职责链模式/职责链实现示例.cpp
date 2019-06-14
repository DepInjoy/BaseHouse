#include <iostream>
#include <string>

class Manager{
public:
	Manager(std::string name) : _name(name){}
	//审批请求处理
	virtual void handleRequest(std::string cmd, int number){
		std::cout << "Without authority to " << cmd << "("<< number << ")" << std::endl;
	}
	//设置上级
	virtual void setSuperior(Manager* superior){
		_superior = superior;
	}
protected:
	Manager*						_superior = nullptr;
private:
	std::string						_name;
};

//经理
class CommonManager : public Manager
{
public:
	CommonManager(std::string name)
		: Manager(name)
		, _name(name){}
	void handleRequest(std::string cmd, int number){
		if (cmd == "rest" && number < 5){	//5天以下休假申请审批
			std::cout << _name << " allowe Number of " << number << " of " << cmd << " !" << std::endl;
		}else{
			if (_superior) _superior->handleRequest(cmd, number);
		}
	}
private:
	std::string					_name;
};

//总监
class Majordomo : public Manager
{
public:
	Majordomo(std::string name)
		: Manager(name)
		, _name(name){}
	void handleRequest(std::string cmd, int number){
		if (cmd == "rest" && number >= 5){	//5天以上休假申请审批
			std::cout << _name << " allowe  Number of " << number << " of " << cmd << " !" << std::endl;
		}else{
			if (_superior) _superior->handleRequest(cmd, number);
		}
	}
private:
	std::string					_name;
};

//高级经理
class GeneralManager : public Manager
{
public:
	GeneralManager(std::string name)
		: Manager(name)
		, _name(name){}
	
	void handleRequest(std::string cmd, int number){
		if (cmd == "rest"){									//有权审批任意天数的休假
			std::cout << _name << " allowe Number of " << number << " of " << cmd << " !" << std::endl;
		}else if (cmd == "RaiseSalary" && number <= 500){	//500元以下加薪审批
			std::cout << _name << " allowe  Number of " << number << " of " << cmd << " !" << std::endl;
		}else if (cmd == "RaiseSalary" && number > 500){	//500元以上加薪审批
			std::cout << _name << " refuse  Number of " << number << " of " << cmd << " !" << std::endl;
		}else{
			if (_superior) _superior->handleRequest(cmd, number);
		}
	}
private:
	std::string					_name;
};

int main(int argc, char* argv[])
{
	Manager* _manager0 = new CommonManager("ZhangSan");
	Manager* _manager1 = new Majordomo("LiSi");
	Manager* _manager2 = new GeneralManager("WangWu");
	_manager0->setSuperior(_manager1);
	_manager1->setSuperior(_manager2);

	_manager0->handleRequest("rest", 2);
	_manager0->handleRequest("rest", 10);
	_manager0->handleRequest("RaiseSalary", 300);
	_manager0->handleRequest("RaiseSalary", 1000);

	std::cout << std::endl;
	_manager1->handleRequest("rest", 10);
	std::cout << std::endl;

	delete _manager0;
	delete _manager1;
	delete _manager2;
	system("pause");
	return 0;
}