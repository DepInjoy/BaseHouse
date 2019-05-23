#include <iostream>
#include <string>
#include <list>
//订阅者基类
class Observer
{
public:
    Observer(std::string name) :
        _name(name){}
    virtual void update(void) = 0;
    void setMessage(std::string message){
        if (_message != message) _message = message;
    }
    std::string getMessage(void) { return _message; }
protected:
    std::string _name;
    std::string _message;
};
//订阅者派生类
class ObserverA : public Observer
{
public:
    ObserverA(std::string name) :
        Observer(name){
    }
    void update(void){
        std::cout << _name << " , " << getMessage() << std::endl;
    }
};
//订阅者派生类
class ObserverB : public Observer
{
public:
    ObserverB(std::string name) :
        Observer(name){
    }
    void update(void){
        std::cout << _name << ", " << getMessage() << std::endl;
    }
};
//发布者基类
class Publisher
{
public:
    //添加订阅对象
    void attach(Observer* observer){
        _observers.push_back(observer);
    }
    //取消订阅
    void dettach(Observer* observer){
        for (std::list<Observer*>::iterator item = _observers.begin();
             item != _observers.end();){
            if (*item == observer){
                item = _observers.erase(item);
                return;
            }
            else{
                item++;
            }
        }
    }
    //发布通知
    virtual void notify(const std::string message){
        for (std::list<Observer*>::iterator item = _observers.begin();
             item != _observers.end(); item++){
            (*item)->setMessage(message);
            (*item)->update();
        }
    }
private:
    std::list<Observer*> _observers;
};
//发布者派生类
class PublicA : public Publisher{
};

int main(void)
{
    Observer* oa = new ObserverA("A");
    Observer* ob = new ObserverB("B");
    PublicA* _pa = new PublicA();
    _pa->attach(ob);		//添加订阅对象
    _pa->attach(oa);
    _pa->notify("Boss come back, please be quite!");
    std::cout << std::endl << std::endl;
    
    _pa->dettach(oa);	   //取消订阅
    _pa->notify("Let's to celebrate! ");
    
    delete oa;
    delete ob;
    delete _pa;
    
    system("pause");
    return 0;
}