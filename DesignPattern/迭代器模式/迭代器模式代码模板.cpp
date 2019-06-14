#include <iostream>
#include <string>
#include <vector>

//迭代器基类，定义统一接口
template<class Item>
class Iterator{
public:
	//获取第一个对象
	virtual Item* first(void) = 0;
	//获取下一个对象
	virtual Item* next(void) = 0;
	//获取当前对象
	virtual Item* currentItem(void) = 0;
	//判断是否到结尾
	virtual bool isEnd(void) = 0;
};

//集合，定义创建迭代器的接口
template<class Item>
class Aggregate
{
public:
	//创建迭代器
	virtual Iterator<Item>* createIterator(void) = 0;
	//获取索引为index的元素
	virtual Item& operator[](int index) = 0;
	//追加元素
	virtual void push_back(const Item item) = 0;
	//返回集合的元素数
	virtual size_t size() = 0;
};

//具体的集合类，实现创建具体迭代器的接口
template<class Item>
class ConcreateAggregate : public Aggregate<Item>
{
public:
	ConcreateAggregate(){}
	~ConcreateAggregate(){
		if (_iterator){
			delete _iterator;
		}
	}

	Iterator<Item>* createIterator(void){
		_iterator = new ConcreateIterator<Item>(this);
		return _iterator;
	}

	size_t size(void){
		return _containter.size();
	}

	Item& operator[](int index){
		return _containter[index];
	}

	void push_back(const Item item){
		_containter.push_back(item);
	}
private:
	std::vector<Item>			_containter;
	Iterator<Item>*				_iterator = nullptr;
};

//具体的迭代器类，实现迭代器接口
template<class Item>
class ConcreateIterator : public Iterator<Item>
{
public:
	ConcreateIterator(ConcreateAggregate<Item>* agg)
		: _aggregate(agg)
		, _curIndex(0){
	}

	~ConcreateIterator(){
		if (_aggregate) delete _aggregate;
	}
	
	Item* first(void) override{
		if (!_aggregate->size()) return nullptr;
		return &((*_aggregate)[0]);
	}

	Item* next(void) override{
		Item* res = nullptr;
		_curIndex++;
		if (_curIndex < _aggregate->size()){
			res = &((*_aggregate)[_curIndex]);
		}
		return res;
	}

	Item* currentItem(void) override{
		Item* res = nullptr;
		if (_curIndex < _aggregate->size()){
			res = &((*_aggregate)[_curIndex]);
		}
		return res;
	}

	bool isEnd(void) override{
		return (_curIndex >= _aggregate->size());
	}
private:
	ConcreateAggregate<Item>*			_aggregate;
	size_t								_curIndex;
};


int main(int argc, char* argv[])
{
	Aggregate<int>* aggregate = new ConcreateAggregate<int>();
	//创建迭代器，类似于STL中的begin接口
	Iterator<int>* it = aggregate->createIterator();
	aggregate->push_back(6);
	aggregate->push_back(8);
	aggregate->push_back(10);
	aggregate->push_back(12);
	aggregate->push_back(68);
	
	//遍历集合中元素并打印
	for (; !it->isEnd(); it->next()){
		std::cout << *(it->currentItem()) << std::endl;
	}
	delete aggregate;

	system("pause");
	return 0;
}