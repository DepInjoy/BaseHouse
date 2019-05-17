#include <iostream>

class Subject{
public:
	virtual void request(){};
};

//代理代表的真实对象
class RealSubject : public Subject
{
public:
	void request(){
		std::cout << "RealSubject::request " << std::endl;
	}
};
//代理类，拥有和真实对象
class Proxy : public Subject
{
public:
	~Proxy(){
		if (_realSubject) delete _realSubject;
	}
	void request(){
		if (!_realSubject)
			_realSubject = new RealSubject();
		_realSubject->request();
	}
private:
	RealSubject* _realSubject = nullptr;
};

int main(void)
{
	Proxy* _proxy = new Proxy();
	_proxy->request();
	delete _proxy;
	system("pause");
	return 0;
}