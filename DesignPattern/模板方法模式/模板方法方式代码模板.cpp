#include <iostream>
//超类
class AbstractClass{
public:
	//一些抽象接口，放到子类中去实现
	virtual void primitiveOperation1(void){}
	virtual void primitiveOperation2(void){}
	/*
		模板方法，给出逻辑骨架
		逻辑组成是一些抽象的方法，这些抽象的方法推迟到子类中实现
	*/
	void templateMethod(void){
		primitiveOperation1();
		primitiveOperation2();
	}
};

class ConcreteClassA : public AbstractClass{
public:
	//实现抽象方法
	virtual void primitiveOperation1(void){
		std::cout << "ConcreteClassA::primitiveOperation1" << std::endl;
	}
	virtual void primitiveOperation2(void){
		std::cout << "ConcreteClassA::primitiveOperation2" << std::endl;
	}
};

class ConcreteClassB : public AbstractClass{
public:
	//实现抽象方法
	virtual void primitiveOperation1(void){
		std::cout << "ConcreteClassB::primitiveOperation1" << std::endl;
	}
	virtual void primitiveOperation2(void){
		std::cout << "ConcreteClassB::primitiveOperation2" << std::endl;
	}
};

int main()
{
	AbstractClass* a0 = new ConcreteClassA;
	a0->templateMethod();
	std::cout << std::endl << std::endl;
	delete a0;
	
	AbstractClass* b0 = new ConcreteClassB;
	b0->templateMethod();
	std::cout << std::endl << std::endl;
	delete b0;
	system("pause");
	return 0;
}