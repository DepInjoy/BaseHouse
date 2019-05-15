#include <iostream>
#include <string>
class Quote{
public:
	Quote();
	Quote(std::string name);
	//纯虚函数，派生类必须重写，否则将报错
	virtual std::string name0() = 0;
	virtual std::string name1(){
		return "Quote - virtual";
	};
	virtual std::string name2(){
		return "Not Override";
	};
	std::string unoverridedFun(void){
		return name0();
	};
protected:
	//在基类和派生类之间共享
	int _protectedValue;
};

Quote::Quote(){
	std::cout << "Quote - structure Quote without parameter" << std::endl;
	_protectedValue = 666;
}

Quote::Quote(std::string name)
{
	std::cout << "Quote - Structure Quote with Parameter of string " << name << std::endl;
}

class BulkQuote : public Quote
{
public:
	BulkQuote();
	BulkQuote(std::string name);
	virtual std::string name0() override{
		return "BulkQuote - Pure Virtual";
	};
	virtual std::string name1(){
		return "BulkQuote - Override name1";
	};
	virtual std::string name3() const{
		//_protectedValue = 444;
		return "BulkQuote - Const function";
	}
	float total(float price, int num){
		return price * num;
	};
	float total(float price, int num, float discout){
		return price * num * discout;
	};
	//基类和派生类都可以访问protected变量
	void potectedTest(){
		std::cout << "Protected value in Quote : " << _protectedValue << std::endl;
	};
};

BulkQuote::BulkQuote()
	:Quote()
{
	std::cout << "BulkQuote - struct BulkQuote witout name " << std::endl;
}

BulkQuote::BulkQuote(std::string name)
	: Quote(name){
	std::cout << "BulkQuote - struct BulkQuote with name " << name << std::endl;
}

int main(int argc, char*argv[])
{
	std::cout << "================== test 0 ================== " << std::endl;
	BulkQuote* _bulkQuote = new BulkQuote("Hello Inherit");
	std::string name = _bulkQuote->name0();
	std::cout << name << std::endl;

	name = _bulkQuote->name1();
	std::cout << name << std::endl;

	name = _bulkQuote->name2();
	std::cout << name << std::endl;

	float total1 = _bulkQuote->total(12.8, 10);
	float total2 = _bulkQuote->total(12.8, 10, 0.1);
	std::cout << "Dynamic binding test " << total1 << "  " << total2 << std::endl;

	name = _bulkQuote->unoverridedFun();
	std::cout << "insteresting Dynamic binding to BulkQuote's name0 " << name << std::endl;
	std::cout << std::endl << "================== test 1 ================== " << std::endl;
	_bulkQuote->potectedTest();

	std::cout << std::endl << "================== test 2 ================== " << std::endl;
	/*not allowed as pure virtual fuction is contained */
	//Quote* _quote = new Quote();
	Quote* _quote = _bulkQuote;
	name = _quote->name1();
	std::cout << name << std::endl;

	std::cout << std::endl << "================== test 3 ================== " << std::endl;
	const BulkQuote constBulkQuote;
	std::string name3 = constBulkQuote.name3();
	std::cout << name3 << std::endl;
	// name3 = constBulkQuote.name1(); //not allowed
	std::cout << std::endl;

	BulkQuote bulkQuote0;
	std::cout << bulkQuote0.name3() << std::endl;

	system("pause");
	return 0;
}