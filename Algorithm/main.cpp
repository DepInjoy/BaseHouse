#include <iostream>
#include <mutex>
#include <thread>

static std::mutex g_mutex;


class Singleton{
public:
	static Singleton* _instance;
};
Singleton* getInstance();

Singleton* Singleton::_instance = NULL;

Singleton* getInstance(){
	if (!Singleton::_instance){
		g_mutex.lock();
		if (!Singleton::_instance){
			Singleton::_instance = new Singleton();
		}
		std::cout << "============== Singleton::getInstance =======================";
		g_mutex.unlock();
	}
	return Singleton::_instance;
}

int main(int argc, char*argv[]){
	Singleton* instance = getInstance();
	system("pause");
	return 0;
}