#include <iostream>
//运算操作，父类
class Operation
{
public:
    //设置第一运算数
	void setNumA(float a) { numA = a; }	
	//设置第二运算数
    void setNumB(float b) { numB = b; }	
    //返回运算结果
	virtual float getResult(void) { return 0; }
protected:
	float numA;						// 第一运算数
	float numB;						// 第二运算数
};
//加法类
class OperationAdd : public Operation
{
public:
	float getResult(void) { return numA + numB; }
};
//减法类
class OperationSub : public Operation
{
public:
	float getResult(void) { return numA - numB; }
};
//乘法类
class OperationMulti : public Operation
{
public:
	float getResult(void) { return numA * numB; }
};
//除法类
class OperationDiv : public Operation
{
public:
	float getResult(void) {
		if (numB == 0)	return FLT_MAX;
		else return numA / numB;
	}

};

class SimpleFactoryDemo
{
public:
	static Operation* createFactory(char op);
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

int main(void)
{
	float a, b;
	std::cout << "Please input your first number : " << std::endl;
	std::cin >> a ;
	std::cout << "Please input your second number : " << std::endl;
	std::cin >> b;
	//创建一个加法运算符
	Operation* opAdd =  SimpleFactoryDemo::createFactory('+');
	opAdd->setNumA(a);											//2
	opAdd->setNumB(b);											//8
	std::cout << opAdd->getResult() << std::endl;				//10
	return 0;
}