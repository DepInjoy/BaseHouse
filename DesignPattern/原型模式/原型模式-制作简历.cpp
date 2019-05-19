#include <iostream>
#include <string>

class Prototype{
public:
	virtual Prototype* clone(){ return NULL; }
private:
	int size;
};

class WrokExperience : public Prototype
{
public:
	WrokExperience() = default;
	
	WrokExperience(const WrokExperience& e){
		_workedTime = e._workedTime;
		_workedCompany = e._workedCompany;
	}

	Prototype* clone(void){
		return new WrokExperience(*this);
	}

	int getWorkedTime(void){ return _workedTime; }
	void setWorkedTime(int time){
		if (_workedTime != time) _workedTime = time;
	}

	std::string getWorkedCompany(void){ return _workedCompany; }
	void setWorkedCompany(std::string company){
		if (_workedCompany != company) _workedCompany = company;
	}
private:
	int _workedTime = 0;
	std::string _workedCompany = std::string("NONE");
};

class Resum : public Prototype
{
public:
	Resum(std::string name) : 
		 _name(name)
		, _sex(false)
		, _age(22)
		, _workExperience(new WrokExperience)
	{}
	~Resum(){
		delete _workExperience;
		_workExperience = NULL;
	}
	Resum(WrokExperience& workExperience){
		this->_workExperience = reinterpret_cast<WrokExperience*>(workExperience.clone());
	}

	Prototype* clone(void){
		Resum* obj = new Resum(*_workExperience);
		obj->_name = _name;
		obj->_sex = _sex;
		obj->_age = _age;
		return obj;
	}

	void setName(std::string name){
		if (_name != name) _name = name;
	}

	void setSex(bool sex){
		if (_sex != sex) _sex = sex;
	}

	void setAge(int age){
		if (_age != age) _age = age;
	}

	void setExperience(int time, std::string company){
		_workExperience->setWorkedTime(time);
		_workExperience->setWorkedCompany(company);
	}

	void displayInfo(void){
		std::cout << _name << "\t" << _sex << "\t" << _age
			<< "\t" << _workExperience->getWorkedTime()
			<< "\t" << _workExperience->getWorkedCompany() << std::endl;
	}
private:
	std::string _name;
	int _age;
	bool _sex;
	WrokExperience* _workExperience;
};

int main()
{
	Resum* a = new Resum(std::string("Lucy"));
	a->setAge(28);
	a->setSex(true);
	a->displayInfo();

	Resum* b = reinterpret_cast<Resum*>(a->clone());
	b->setExperience(1, "HaiTian");
	b->setName("Lily");
	b->displayInfo();
	
	Resum* c = reinterpret_cast<Resum*>(b->clone());
	b->displayInfo();

	delete a;
	delete b;
	delete c;

	system("pause");
	return 0;
}