#include <iostream>

class IProduct{
public:
	virtual void process(void) = 0;
	virtual void display(void) = 0;
};
class A1Product : public IProduct{
public:
	void process(void){
		std::cout << "A1 Product is processing." << std::endl;
	}

	void display(void){
		std::cout << "Now, A1 Product's show time." << std::endl;
	}
};

class B1Product : public IProduct{
public:
	void process(void){
		std::cout << "B1 Product is processing." << std::endl;
	}

	void display(void){
		std::cout << "Now, B1 Product's show time." << std::endl;
	}
};

class A2Product : public IProduct{
public:
	void process(void){
		std::cout << "A2 Product is processing." << std::endl;
	}

	void display(void){
		std::cout << "Now, A2 Product's show time." << std::endl;
	}
};

class B2Product : public IProduct{
public:
	void process(void){
		std::cout << "B2 Product is processing." << std::endl;
	}

	void display(void){
		std::cout << "Now, B2 Product's show time." << std::endl;
	}
};

class IFactory{
public:
	typedef enum{
		A_PRODUCT_TYPE,
		B_PRODUCT_TYPE
	}productType;
	virtual IProduct* createProduct(productType type) = 0;
};

class Factory1 : public IFactory{
	IProduct* createProduct(productType type){
		switch (type){
		case A_PRODUCT_TYPE:
				return new A1Product();
				break;
			case B_PRODUCT_TYPE:
				return new B1Product();
				break;
			default:
				return nullptr;
		}
	}
};

class Factory2 : public IFactory{
	IProduct* createProduct(productType type){
		switch (type){
		case A_PRODUCT_TYPE:
			return new A2Product();
			break;
		case B_PRODUCT_TYPE:
			return new B2Product();
			break;
		default:
			return nullptr;
		}
	}
};

int main(int argc, char* argv[])
{
	IFactory* f1 = new Factory1();
	IProduct* ap1 = f1->createProduct(IFactory::A_PRODUCT_TYPE);
	IProduct* bp1 = f1->createProduct(IFactory::B_PRODUCT_TYPE);
	ap1->process();
	ap1->display();
	bp1->process();
	bp1->display();
	delete ap1;
	delete bp1;
	delete f1;

	std::cout << std::endl << std::endl;

	IFactory* f2 = new Factory2();
	IProduct* ap2 = f2->createProduct(IFactory::A_PRODUCT_TYPE);
	IProduct* bp2 = f2->createProduct(IFactory::B_PRODUCT_TYPE);
	ap2->process();
	ap2->display();
	bp2->process();
	bp2->display();
	delete ap2;
	delete bp2;
	delete f2;
	system("pause");
	return 0;
}


