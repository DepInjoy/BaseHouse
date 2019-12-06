#include <iostream>

//产品抽象
class IProduct{
public:
	virtual void process(void) = 0;
	virtual void display(void) = 0;
};

//产品族:具体的产品A1
class A1Product : public IProduct{
public:
	void process(void){
		std::cout << "A1 Product is processing." << std::endl;
	}

	void display(void){
		std::cout << "Now, A1 Product's show time." << std::endl;
	}
};

//产品族:具体的产品B1
class B1Product : public IProduct{
public:
	void process(void){
		std::cout << "B1 Product is processing." << std::endl;
	}

	void display(void){
		std::cout << "Now, B1 Product's show time." << std::endl;
	}
};

//产品族:具体的产品A2
class A2Product : public IProduct{
public:
	void process(void){
		std::cout << "A2 Product is processing." << std::endl;
	}

	void display(void){
		std::cout << "Now, A2 Product's show time." << std::endl;
	}
};

//产品族:具体的产品B2
class B2Product : public IProduct{
public:
	void process(void){
		std::cout << "B2 Product is processing." << std::endl;
	}

	void display(void){
		std::cout << "Now, B2 Product's show time." << std::endl;
	}
};

//抽象的工厂
class IFactory{
public:
	virtual IProduct* createProductA(void) = 0;
	virtual IProduct* createProductB(void) = 0;
};

//具体的工厂1
class Factory1 : public IFactory{
	IProduct* createProductA(void){
		return new A1Product();
	}
	virtual IProduct* createProductB(void){
		return new B1Product();
	}
};

//具体的工厂2
class Factory2 : public IFactory{
	IProduct* createProductA(void){
		return new A2Product();
	}
	virtual IProduct* createProductB(void){
		return new B2Product();
	}
};

int main(int argc, char* argv[])
{
	IFactory* f1 = new Factory1();
	IProduct* ap1 = f1->createProductA();
	IProduct* bp1 = f1->createProductB();
	ap1->process();
	ap1->display();
	bp1->process();
	bp1->display();
	delete ap1;
	delete bp1;
	delete f1;

	std::cout << std::endl << std::endl;

	IFactory* f2 = new Factory2();
	IProduct* ap2 = f2->createProductA();
	IProduct* bp2 = f2->createProductB();
	ap2->process();
	ap2->display();
	bp2->process();
	bp2->display();
	delete ap2;
	delete bp2;
	delete f2;
	system("pause");
	return 0;
}


