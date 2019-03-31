#include "SimpleFactoryDemo.h"


class OperationAdd : public Operation
{
public:
	float getResult(void) { return numA + numB; }
};

class OperationSub : public Operation
{
public:
	float getResult(void) { return numA - numB; }
};

class OperationMulti : public Operation
{
public:
	float getResult(void) { return numA * numB; }
};

class OperationDiv : public Operation
{
public:
	float getResult(void) {
		if (numB == 0)	return FLT_MAX;
		else return numA / numB;
	}

};

Operation* SimpleFactoryDemo::createFactory(char op)
{
	Operation* operation = NULL;
	switch (op)
	{
	case '+':
		operation = new OperationAdd();
		break;
	case '-':
		operation = new OperationSub();
		break;
	case '*':
		operation = new OperationMulti();
		break;
	case '/':
		operation = new OperationDiv();
		break;
	default:
		break;
	}
	return operation;
}

void SimpleFactoryDemo::simplestCalculator(void)
{
	float a, b, res;
	char op;
	std::cout << "Please input first number: " << std::endl;
	std::cin >> a;
	std::cout << "Please select operation(+, -, *, /)" << std::endl;
	std::cin >> op;
	std::cout << "Please input second number: " << std::endl;
	std::cin >> b;
	switch (op)
	{
	case '+':
		res = a + b;
		break;
	case '-':
		res = a - b;
		break;
	case '*':
		res = a * b;
		break;
	case '/':
		if (b == 0) res = FLT_MAX;
		else res = a / b;
		break;
	default:
		break;
	}
	std::cout << a << " " << op << " " << b << " = " << res << std::endl;
}