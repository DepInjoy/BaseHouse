/*
	Director ------> Builder
				_______|_______
				|			  |
			BuilderA       BuilderB
				|			  |
				|_____________|
						|
						v
					 Product
*/
#include <iostream>
#include <list>
#include <string>
//产品类
class Product
{
public:
	//添加部件
	void addPartA() {
		std::cout << "Add Part A " << std::endl;
		parts.push_back("A");
	}
	//展部件
	void addPartB(void) {
		std::cout << "Add Part B " << std::endl;
		parts.push_back("B");
	}

	void show(void) {
		for (auto part = parts.begin(); part != parts.end(); part++) {
			std::cout << *part << std::endl;
		}
	}
private:
	std::list<std::string> parts;
};
//抽象建造者
class Builder
{
public:
	Builder() {
		product = new Product();
	}

	~Builder() {
		delete product;
		product = NULL;
	}
	virtual void buildPartA(void) {
		std::cout << "Builder build Part A" << std::endl;
		product->addPartA();
	}
	virtual void buildPartB(void) = 0;
	virtual Product* getProduct(void) {
		return product;
	}
private:
	Product* product;
};
//具体建造者
class BuilderA : public Builder
{
public:
	BuilderA() {
		product = new Product();
	}

	~BuilderA() {
		delete product;
		product = NULL;
	}
	virtual void buildPartA(void) {
		std::cout << "BuilerA build A " << std::endl;
		product->addPartA();
	}
	virtual void buildPartB(void) {
		std::cout << "BuilerA build B" << std::endl;
		product->addPartB();
	}
	virtual Product* getProduct(void) {
		return product;
	}
private:
	Product* product;
};
//具体建造者
class BuilderB : public Builder
{
public:
	BuilderB() {
		product = new Product();
	}

	~BuilderB() {
		delete product;
		product = NULL;
	}
	virtual void buildPartA(void) final{
		std::cout << "BuilerB build A " << std::endl;
		product->addPartA();
	}
	virtual void buildPartB(void) {
		std::cout << "BuilerB build B" << std::endl;
		product->addPartB();
	}
	virtual Product* getProduct(void) final{
		return product;
	}
private:
	Product* product;
};
//指挥者
class Director
{
public:
	Director(Builder* builder) {
		this->builder = builder;
	}

	Product* constuct() {
		builder->buildPartA();
		builder->buildPartB();
		return builder->getProduct();
	}

	void setBuilder(Builder* builder) {
		if (this->builder != builder) {
			this->builder = builder;
		}
	}
private:
	Builder* builder;
};

int main(void)
{
	Builder* a = new BuilderA();
	Builder* b = new BuilderB();

	Director* director = new Director(a);
	director->constuct();
	Product* product = a->getProduct();

	std::cout << std::endl << "********************  set other build  **************************  " << std::endl;
	director->setBuilder(b);
	director->constuct();

	delete a;
	delete b;
	delete director;
	system("pause");
	return 0;
}