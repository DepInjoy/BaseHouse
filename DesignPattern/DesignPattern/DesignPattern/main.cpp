#define BUILDER
#include <iostream>

#ifdef SIMPLE_FACTORY
#include <SimpleFactoryDemo.h>
#endif // SIMPLE_FACTORY

#ifdef STRATEGY
#include "StrategyDemo.h"
#endif

#ifdef BUILDER
#include "BuilderDemo.h"
#endif // BUILDER

int main(int argc, char* argv[])
{
#ifdef SIMPLE_FACTORY
	//SimpleFactoryDemo::simplestCalculator();
	float a, b;
	std::cout << "Please input your first number : " << std::endl;
	std::cin >> a ;
	std::cout << "Please input your second number : " << std::endl;
	std::cin >> b;
	Operation* opAdd =  SimpleFactoryDemo::createFactory('+');
	opAdd->setNumA(a);
	opAdd->setNumB(b);
	std::cout << opAdd->getResult() << std::endl;
#endif // SIMPLE_FACTORY

#ifdef STRATEGY
	StrategyDemo::strategyDemoTest();
	StrategyDemo::strategyFactoryDemoTest();
#endif

#ifdef BUILDER
	BuilderDemo::builderTest();
#endif // BUILDER
	system("pause");
	return 0;
}