#include <iostream>
#include <list>

class Element;
class ConcreteElementA;
class ConcreteElementB;

//抽象访问者
class Visitor {
public:
	virtual void VisitConcreteElementA(ConcreteElementA* ca) = 0;
	virtual void VisitConcreteElementB(ConcreteElementB* cb) = 0;
};

class Element {
public:
	virtual void Accept(Visitor* visitor) = 0;
};

class ConcreteElementA : public Element {
public:
	void Accept(Visitor* visitor) {
		std::cout << "ConcreteElementA: ";
		visitor->VisitConcreteElementA(this);
	}
};

class ConcreteElementB : public Element {
public:
	void Accept(Visitor* visitor) {
		std::cout << "ConcreteElementB: ";
		visitor->VisitConcreteElementB(this);
	}
};

//具体的访问者
class ConcreteVisitorA : public Visitor{
public:
	void VisitConcreteElementA(ConcreteElementA* ca) {
		std::cout << "ConcreteVisitorA::VisitConcreteElementA" << std::endl;
	}
	void VisitConcreteElementB(ConcreteElementB* cb) {
		std::cout << "ConcreteVisitorA::VisitConcreteElementB" << std::endl;
	}
};

class ConcreteVisitorB : public Visitor{
public:
	void VisitConcreteElementA(ConcreteElementA* ca) {
		std::cout << "ConcreteVisitorB::VisitConcreteElementA" << std::endl;
	}
	void VisitConcreteElementB(ConcreteElementB* cb) {
		std::cout << "ConcreteVisitorB::VisitConcreteElementB" << std::endl;
	}
};

//对象结构
class ObjectStructure {
public:
	void Attach(Element* element) {
		_elements.push_back(element);
	}
	void Detach(Element* element) {
		_elements.remove(element);
	}
	void Accept(Visitor* visitor) {
		for (auto e = _elements.begin(); e != _elements.end(); e++) {
			(*e)->Accept(visitor);
		}
	}
private:
	std::list<Element* >_elements;
};

int main() {
	ObjectStructure* o = new ObjectStructure();

	ConcreteElementA* ca = new ConcreteElementA();
	ConcreteElementB* cb = new ConcreteElementB();

	o->Attach(ca);
	o->Attach(cb);

	ConcreteVisitorA* cv1 = new ConcreteVisitorA();
	ConcreteVisitorB* cv2 = new ConcreteVisitorB();

	o->Accept(cv1);
	o->Accept(cv2);
	delete ca;
	delete cb;
	delete cv1;
	delete cv2;
	delete o;
	system("pause");
	return 0;
}