#include <iostream>
#include <string>
class Country;
//抽象中介者，类比于联合国
class UnitedState{
public:
	virtual void declare(std::string word, Country* country) = 0;
	void setCoutry1(Country* country){ _country1 = country;}
	void setCoutry2(Country* country){ _country2 = country; }
protected:
	Country*					_country1 = nullptr;
	Country*					_country2 = nullptr;
};

//抽象同事类，类比于国家
class Country
{
public:
	Country(UnitedState* mediator)
	: _mediator(mediator){
	}
	virtual void declare(std::string word) = 0;
	virtual void getWord(std::string word) = 0;
protected:
	UnitedState*				_mediator;
	std::string					_name;
};

//具体的同事类，类比于美国
class USA : public Country
{
public:
public:
public:
	USA(UnitedState* mediator)
	: Country(mediator)
	{
	}
	void declare(std::string word){
		_mediator->declare(word, this);
	}
	void getWord(std::string word){
		std::cout << "USA  get word : " << word << std::endl;
	}
};

class Iraq : public Country
{
public:
	Iraq(UnitedState* mediator)
		: Country(mediator)
	{
	}
	void declare(std::string word){
		_mediator->declare(word, this);
	}
	void getWord(std::string word){
		std::cout << "Iraq get word : " << word << std::endl;
	}
};

class UNSC : public UnitedState{
public:
	void declare(std::string word, Country* country) override{
		if (country != _country1){
			_country1->getWord(word);
		}else{
			_country2->getWord(word);
		}
	}
};

int main(int argc, char* argv[])
{
	UnitedState* unsc = new UNSC();
	Country* usa = new USA(unsc);
	Country* iraq = new Iraq(unsc);
	unsc->setCoutry1(usa);
	unsc->setCoutry2(iraq);

	usa->declare("Hello World");
	iraq->declare("Nice to meet you!");
	delete unsc;
	delete usa;
	delete iraq;
	system("pause");
	return 0;
}