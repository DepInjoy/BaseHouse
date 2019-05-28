#include <iostream>
#include <string>
//客户端期待的接口类
class Target
{
public:
	virtual void request(void) {
		std::cout << "Target::request " << std::endl;
	}
};
//需要适配的类
class Adaptee{
public:
	void specifiedRequest(void) {
		std::cout << "Adaptee::specifiedRequest " << std::endl;
	}
};

//将源接口转化为目标接口
class Adapter : public Target {
	void request(void) {
		std::cout << "Adapter::request " << std::endl;
		Adaptee tmp = Adaptee();
		tmp.specifiedRequest();
	}
};

int main(int argc, char* argv[])
{
	//客户端调用
	Target* tmp = new Adapter();
	tmp->request();
	delete tmp;
	system("pause");
	return 0;
}