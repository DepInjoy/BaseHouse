#pragma once
#include <iostream>
class StrategyDemo
{
public:
	static void strategyDemoTest(void);
};
class Strategy
{
public:
	void virtual AlgorithmInterface(void){
		std::cout << "Strategy  Algorithm Interface" << std::endl;
	};
};
class StrategyA : public Strategy
{
public:
	void AlgorithmInterface(void) final{
		std::cout << "Strategy A Algorithm Interface" << std::endl;
	}
};

class StrategyB : public Strategy{
public:
	void AlgorithmInterface(void) final{
		std::cout << "Strategy B Algorithm Interface" << std::endl;
	}
};

class StrategyC : public Strategy{
public:
	void AlgorithmInterface(void) final{
		std::cout << "Strategy C Algorithm Interface" << std::endl;
	}
};
class Context
{
public:
	Context(Strategy* s){
		strategy = s;
	}
	void ContextInterface(){
		strategy->AlgorithmInterface();
	}
private:
	Strategy* strategy;
};

