#include <iostream>
#include <string>
class Circle
{
public:
	Circle(){
		_r = 0;
		std::cout << "Construct Circle without Parameter" << std::endl;
	}
	Circle(double r){
		_r = r;
		std::cout << "Construct Circle with " << r << std::endl;
	}
	double area(void){
		std::cout << "Circle's area: " << 3.1415926 * _r * _r << std::endl;
		return 3.1415926 * _r * _r;
	}
	~Circle(){
		std::cout << "Deconstruct Circle r = " << _r << std::endl;
	}
private:
	double _r;
};

int main(void)
{
	Circle c1[2];
	std::cout << std::endl << std::endl;

	Circle c2[2] = { 1 };
	std::cout << std::endl << std::endl;

	Circle c3[2] = { 2, 3 };
	std::cout << std::endl << std::endl;

	Circle* a1 = new Circle[2];
	delete[]a1;
	std::cout << std::endl << std::endl;

	Circle a2[3] = { 1, Circle(2) };
	std::cout << std::endl << std::endl;

	Circle* a3[3] = { new Circle(), new Circle(1) }; //a3(2) NULL
	for (int i = 0; i < 2; i++){
		a3[i]->area();
		delete a3[i];
	}
	std::cout << std::endl << std::endl;
	system("pause");
	return 0;
}