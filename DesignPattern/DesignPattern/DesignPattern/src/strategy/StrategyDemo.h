#pragma once
#include <iostream>
#include <string>
class StrategyDemo
{
public:
	static void strategyDemoTest(void);
	static void strategyFactoryDemoTest(void);
};

/* ------------------------------------------------------ */
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
	std::string uname;
	StrategyA(std::string name ="A"){ uname = name; };
	void AlgorithmInterface(void) final{
		std::cout << "Strategy A Algorithm Interface " << uname << std::endl;
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
////策略模式
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
//策略模式和工厂模式相结合
class StrategyFactoryDemo
{
public:
	void selectedStrategy(char type){
		switch (type)
		{
		case 'A':
			strategy = new StrategyA();
			break;
		case 'B':
			strategy = new StrategyB();
			break;
		case 'C':
			strategy = new StrategyC();
			break;
		default:
			break;
		}
	}
	void ContextInterface(){
		strategy->AlgorithmInterface();
	}
private:
	Strategy* strategy;
};
