#include <iostream>
#include <string>

//实现类，提供统一的接口
class Implementor{
public:
	virtual void operation(void) = 0;
};
//具体实现类
class ImplementorA : public Implementor{
public:
	void operation(void){
		std::cout << "ImplementorA Operation " << std::endl;
	}
};

class ImplementorB : public Implementor{
public:
	void operation(void){
		std::cout << "ImplementorB Operation " << std::endl;
	}
};

//抽象类
class Abstraction{
public:
	void setImplement(Implementor* imp){
		_implementor = imp;
	}
	virtual void operation(void){};
protected:
	Implementor*					_implementor = nullptr;
};

class RedefinedAbstractionA : public Abstraction
{
public:
	void operation(void){
		if (_implementor)
			_implementor->operation();
		else
			std::cout << "Implementor is NULL, Please confirm !" << std::endl;
	}
};

//客户端调用
int main(int argc, char* argv[])
{
	RedefinedAbstractionA* toolA = new RedefinedAbstractionA();
	toolA->operation();
	//构造抽象类
	ImplementorA* _impA = new ImplementorA();
	ImplementorB* _impB = new ImplementorB();
	
	toolA->setImplement(_impA);
	toolA->operation();

	toolA->setImplement(_impB);
	toolA->operation();

	delete toolA;
	delete _impA;
	delete _impB;
	system("pause");
	return 0;
}