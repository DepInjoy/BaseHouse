#include <iostream>
#include <string>

//用户接口，客户端访问，用于解除客户端和具体数据库访问的解耦合
class User
{
public:
	virtual void insertUser(User* user) = 0;
	virtual void getUser(int id) = 0;
};
//SQL用户接口
class SQLUser : public User
{
public:
	void insertUser(User* user){
		std::cout << "Inser a user to SQL " << std::endl;
	}
	void getUser(int id){
		std::cout << "Get info with id( " << id << ") From SQL " << std::endl;
	}
};
//Access用户接口
class AccessUser : public User
{
public:
	void insertUser(User* user){
		std::cout << "Inser a user to Access " << std::endl;
	}
	void getUser(int id){
		std::cout << "Get info with id(" << id << ") From Access " << std::endl;
	}
};
//访问User表的对象的抽象接口
class IFactory
{
public:
	virtual User* createUser() = 0;
};

class SQLFactory : public IFactory{
	User* createUser(){
		return new SQLUser();
	}
};

class AccessFactory : public IFactory{
	User* createUser(){
		return new AccessUser();
	}
};

int main(int argc, char* argv[])
{
	//访问SQL数据库
	IFactory* sqlFactory = new SQLFactory();
	User* sqlUser = sqlFactory->createUser();
	sqlUser->getUser(1);
	User* tmp = new SQLUser();
	sqlUser->insertUser(tmp);
	delete sqlFactory;
	delete sqlUser;
	delete tmp;

	std::cout << std::endl << std::endl;
	
	//访问Access数据库
	IFactory* accessFactory = new AccessFactory();
	User* accessUser = accessFactory->createUser();
	accessUser->getUser(6);
	User* tmp1 = new AccessUser();
	accessUser->insertUser(tmp1);
	delete accessFactory;
	delete accessUser;
	delete tmp1;
	system("pause");
	return 0;
}