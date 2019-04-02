#include "StrategyDemo.h"

void StrategyDemo::strategyDemoTest(void)
{
	StrategyA* _althA = new StrategyA("Hello");
	Context context0(_althA);
	context0.ContextInterface();
	delete _althA;

	StrategyB* _althB = new StrategyB();
	Context context1(_althB);
	context1.ContextInterface();
	delete _althB;
}

void StrategyDemo::strategyFactoryDemoTest(void)
{
	StrategyFactoryDemo strategyFactoryDemo;
	strategyFactoryDemo.selectedStrategy('A');
	strategyFactoryDemo.ContextInterface();

	strategyFactoryDemo.selectedStrategy('C');
	strategyFactoryDemo.ContextInterface();
}
