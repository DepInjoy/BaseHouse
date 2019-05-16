#include <iostream>
#include <string>

class Compnent
{
public:
	virtual void Action(void){}
};

//一个具体的装饰对象
class CompentA : public Compnent
{
	void Action(void){
		std::cout << "CompentA:Action" << std::endl;
	}
};

class Decorator : public Compnent
{
public:
	Decorator(void) : compent(NULL){}
	/*
		对对象进行包装
			实现将每个装饰对象的实现和如何使用这个对象分离开
			每个装饰对象值关注自己如何实现而无需关心，如何添加到对象链中
	*/
	void setCompnent(Compnent* compent){
		this->compent = compent;
	}
	void Action(void){
		if (compent) compent->Action();
	}
protected:
	Compnent* compent;
};

class DecoratorA : public Decorator
{
public:
	void Action(void){
		Decorator::Action();
		std::cout << "DecoratorA::Action" << std::endl;
	}
};

class DecoratorB : public Decorator
{
public:
	void Action(void){
		Decorator::Action();
		std::cout << "DecoratorB::Action" << std::endl;
	}
};

int main()
{
	CompentA* ca = new CompentA();
	DecoratorA* da = new DecoratorA();
	DecoratorB* db = new DecoratorB();

	da->setCompnent(ca);
	db->setCompnent(da);
	db->Action();

	delete ca;
	delete da;
	delete db;
	system("pause");
	return 0;
}