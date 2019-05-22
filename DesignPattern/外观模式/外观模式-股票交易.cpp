#include <iostream>
#include <string>
//股票
class StockA
{
public:
	void buy(void) { std::cout << "Buy StockA " << std::endl; }
	void sell(void) { std::cout << "Sell StockA " << std::endl; }
};
//股票
class StockB
{
public:
	void buy(void) { std::cout << "Buy StockB " << std::endl; }
	void sell(void) { std::cout << "Sell StockB " << std::endl; }
};
//股票
class StockC
{
public:
	void buy(void) { std::cout << "Buy StockC " << std::endl; }
	void sell(void) { std::cout << "Sell StockC " << std::endl; }
};
//股票
class StockD
{
public:
	void buy(void) { std::cout << "Buy StockD " << std::endl; }
	void sell(void) { std::cout << "Sell StockD " << std::endl; }
};
//基金
class Fund
{
public:
	void buy(void){
		StockA a; StockB b; StockD d;
		a.buy();
		b.buy();
		d.buy();
	}
	void sell(void){
		StockA a; StockB b; StockD d;
		a.sell();
		b.sell();
		d.sell();
	}
};

int main()
{
	Fund f;
	f.buy();
	std::cout << std::endl << std::endl;
	f.sell();
	system("pause");
	return 0;
}