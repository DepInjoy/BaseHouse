#pragma once
#include <iostream>
#include <list>
#include <string>
class Product
{
public:
	void addPartA() {
		std::cout << "Add Part A " << std::endl;
		parts.push_back("A");
	}

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

/* **************************** Unit Test ******************************* */
class BuilderDemo
{
public:
	static void builderTest(void);
};