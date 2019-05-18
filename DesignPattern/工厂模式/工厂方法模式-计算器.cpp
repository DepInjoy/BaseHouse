#include <iostream>
#include <memory>

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

//工厂方法
class Factory
{
public:
	virtual Operation* createOperation() = 0;
};

//加法工厂
class AddFactory : public Factory
{
public:
	Operation* createOperation(){
		return new OperationAdd;
	}
};

//减法工厂
class SubFactory : public Factory
{
public:
	Operation* createOperation(){
		return new OperationSub;
	}
};

//乘法工厂
class MultiFactory : public Factory
{
public:
	Operation* createOperation(){
		return new OperationMulti;
	}
};

//除法工厂
class DiVFactory : public Factory
{
public:
	Operation* createOperation(){
		return new OperationDiv;
	}
};
int main(void)
{
	float a, b;
	std::cout << "Please input your first number : " << std::endl;
	std::cin >> a;
	std::cout << "Please input your second number : " << std::endl;
	std::cin >> b;

	//创建一个加法运算符
	Factory* _addFactory = new AddFactory();
	Operation* addOp = _addFactory->createOperation();
	addOp->setNumA(a);
	addOp->setNumB(b);
	std::cout << a << " + " << b << " = " << addOp->getResult() << std::endl;
	delete addOp;
	system("pause");
	return 0;
}