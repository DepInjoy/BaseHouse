#include <iostream>
#include <string>

class SuperCash
{
public:
	virtual float acceptCash(float money) = 0;
};

class CashNormal : public SuperCash{
	float acceptCash(float money){
		return money;
	}
};

class CashRebate : public SuperCash{
public:
	CashRebate(float rebate) 
		: _rebate(rebate){
	}

	float acceptCash(float money){
		return money * _rebate;
	}
private:
	float _rebate;
};

class CashReturn : public SuperCash{
public:
	CashReturn(float full, float back):
	_full(full)
	, _back(back){}

	float acceptCash(float money){
		if (money > _full){
			return money - _back;
		}
		return money;
	}
private:
	float _full;
	float _back;
};

class CashContext
{
public:
	CashContext(int type){
		switch (type){
		case 0:		//正常
			_cash = new CashNormal();
			break;
		case 1:		//8折
			_cash = new CashRebate(0.8);
			break;
		case 2:		//满199减100
			_cash = new CashReturn(199, 100);
			break;
		default:
			_cash = NULL;
			break;
		}
	}

	~CashContext(){
		if (_cash) delete _cash;
	}
	float realPrice(float money){
		return _cash->acceptCash(money);
	}
private:
	SuperCash* _cash;
};

int main(void)
{
	float total = 200;
	CashContext * _context0 = new CashContext(0);
	std::cout << "Real Price : " << _context0->realPrice(total) << std::endl;
	delete _context0;
	CashContext * _context1 = new CashContext(1);
	std::cout << "Real Price : " << _context1->realPrice(total) << std::endl;
	delete _context1;
	CashContext * _context2 = new CashContext(2);
	std::cout << "Real Price : " << _context2->realPrice(total) << std::endl;
	delete _context2;
	return 0;
}
