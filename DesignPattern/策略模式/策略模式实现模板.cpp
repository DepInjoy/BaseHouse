#include <iostream>
#include <string>
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
	StrategyA(std::string name = "A"){ uname = name; };
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
/* ------------------------------------------------------ */

/* ---------------------- 策略模式 ----------------------*/
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

/* ---------------------- 策略模式和工厂模式相结合 ----------------------*/
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

//策略模式测试用例
void strategyDemoTest(void)
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

//策略模式和工厂模式结合的测试用例
void strategyFactoryDemoTest(void)
{
	StrategyFactoryDemo strategyFactoryDemo;
	strategyFactoryDemo.selectedStrategy('A');
	strategyFactoryDemo.ContextInterface();

	strategyFactoryDemo.selectedStrategy('C');
	strategyFactoryDemo.ContextInterface();
}

int main(void)
{
	strategyDemoTest();
	std::cout << "---------------- next unit test ---------------------- " << std::endl;
	strategyFactoryDemoTest();
	return 0;
}