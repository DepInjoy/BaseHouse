#pragma once
#include <iostream>
class Operation
{
public:
	void setNumA(float a) { numA = a; }
	void setNumB(float b) { numB = b; }
	virtual float getResult(void) { return 0; }
protected:
	float numA;
	float numB;
};
class SimpleFactoryDemo
{
public:
	static Operation* createFactory(char op);
	/* Calculator without oop.*/
	static void simplestCalculator(void);
};

