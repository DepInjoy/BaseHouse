#include <iostream>
#include <string>
#include <List>
//对象接口，公共类统一接口默认行为
class Compnent{
public:
	Compnent(std::string name)
		: _name(name){
	}
	//添加子节点
	virtual void add(Compnent* c){};
	//删除子节点
	virtual void remove(Compnent c){};
	//子节点展示
	virtual void display(int dep){};
protected:
	std::string _name;
};
/*
叶子,叶子节点无子节点
无法添加和删除节点
*/
class Leaf : public Compnent
{
public:
	Leaf(std::string name)
		: Compnent(name){
	}
	void add(Compnent* c){
		std::cout << "Can not add a compnent from leaf !" << std::endl;
	}

	void remove(Compnent c){
		std::cout << "Can not remove a compnent from leaf !" << std::endl;
	}

	void display(int dep){
		std::string tmp(dep, '-');
		std::cout << tmp << _name << std::endl;
	}
};
//树枝
class Composite : public Compnent
{
public:
	Composite(std::string name)
		: Compnent(name){
	}
	void add(Compnent* c){
		_compnentList.push_back(c);
	};
	void remove(Compnent* c){
		_compnentList.remove(c);
	};
	void display(int dep){
		std::string tmp(dep, '-');
		std::cout << tmp << _name << std::endl;
		for (auto item = _compnentList.begin(); item != _compnentList.end(); item++){
			(*item)->display(dep + 1);
		}
	};
private:
	std::list<Compnent*> _compnentList;
};

int main(int argc, char* argv[])
{
	Composite* root = new Composite("Root");

	Leaf* leafA = new Leaf("LA");
	root->add(leafA);
	Composite* itemA = new Composite("A");
	root->add(itemA);


	Composite* itemB = new Composite("B");
	itemA->add(itemB);
	Leaf* leafBA = new Leaf("LBA");
	itemB->add(leafBA);
	Leaf* leafBB = new Leaf("LBB");
	itemB->add(leafBB);

	root->display(2);
	std::cout << std::endl;

	itemB->remove(leafBB);
	root->display(2);

	delete root;
	delete itemA;
	delete itemB;
	delete leafA;
	delete leafBA;
	delete leafBB;
	system("pause");
	return 0;
}