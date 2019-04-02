#include "StrategyDemo.h"

void StrategyDemo::strategyDemoTest(void)
{
	StrategyA* _althA = new StrategyA();
	Context context0(_althA);
	context0.ContextInterface();
	delete _althA;

	StrategyB* _althB = new StrategyB();
	Context context1(_althB);
	context1.ContextInterface();
	delete _althB;
}
