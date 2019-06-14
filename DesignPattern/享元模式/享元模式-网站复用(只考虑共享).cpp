#include <iostream>
#include <string>
#include <unordered_map>

//网站
class WebSite{
public:
	virtual void use(void) = 0;
};

//具体网站
class ConcreteWebSite : public WebSite
{
public:
	ConcreteWebSite(std::string name){
		userName = name;
	};

	void use(void){
		std::cout << "category: " << userName << std::endl;
	}
private:
	std::string userName;
};

//网站工厂
class WebsiteFactory
{
public:
	~WebsiteFactory(){
		for (auto item : _websitesMap){
			delete  dynamic_cast<ConcreteWebSite*>(item.second);
		}
		_websitesMap.clear();
	}
	
	//根据网站的分类，获取网站对应的指针
	WebSite* getWebSite(std::string category){
		if (_websitesMap.find(category) == _websitesMap.end()){
			WebSite* tmp = new  ConcreteWebSite(category);
			_websitesMap.insert(std::pair<std::string, WebSite*>(category, tmp));
			return tmp;
		}
		return _websitesMap[category];
	}
	//获取创建的网站个数
	int getWebSiteCount(void){
		return _websitesMap.size();
	}
private:
	std::unordered_map<std::string, WebSite*>	_websitesMap;
};

int main(int argc, char* argv[])
{
	WebsiteFactory* factory = new WebsiteFactory();
	WebSite* web0 =  factory->getWebSite("Blog");
	web0->use();
	
	WebSite* web1 = factory->getWebSite("Blog");
	web1->use();
	
	std::cout << "size = " << factory->getWebSiteCount() << std::endl;

	WebSite* web2 = factory->getWebSite("Display");
	web2->use();

	std::cout << "size = " << factory->getWebSiteCount() << std::endl;
	
	delete factory;
	system("pause");
	return 0;
}