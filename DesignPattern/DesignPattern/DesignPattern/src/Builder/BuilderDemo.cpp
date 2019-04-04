#include "BuilderDemo.h"
void BuilderDemo::builderTest(void)
{
	Builder* a = new BuilderA();
	Builder* b = new BuilderB();

	Director* director = new Director(a);
	director->constuct();
	Product* product = a->getProduct();

	std::cout << "********************  set other build  **************************  " << std::endl;
	director->setBuilder(b);
	director->constuct();

	delete a;
	delete b;
	delete director;
}