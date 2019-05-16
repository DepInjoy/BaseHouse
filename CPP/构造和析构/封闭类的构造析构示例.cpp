#include <iostream>
#include <string>
class Engine
{
public:
	Engine(std::string manu);
	~Engine();
	Engine(Engine& engine);
	std::string manu(void) { return _manu; }
private:
	std::string  _manu;
};

class Tyre {
public:
	Tyre(int radius);
	~Tyre();
private:
	int _radius;
};

class Car
{
public:
	Car(int radius, std::string manu);
	~Car();
private:
	Engine engine;
	Tyre tyre;
};

Engine::Engine(std::string manu) :
_manu(manu)
{
	std::cout << "Construct Engine with manufacture " << _manu << std::endl;
}

Engine::~Engine()
{
	std::cout << "Deconstruct Engine whose manufacture is " << _manu << std::endl;
}

Engine::Engine(Engine & engine)
{
	_manu = engine.manu();
	std::cout << "Engine's copy constructor " << _manu << std::endl;
}

Tyre::Tyre(int radius) :
_radius(radius)
{
	std::cout << "Construct Tyre with radius " << _radius << std::endl;
}
Tyre::~Tyre()
{
	std::cout << "Deconstruct Tyre whose radius is " << _radius << std::endl;
}

Car::Car(int radius, std::string manu) :
tyre(radius),
engine(manu)
{
	std::cout << "Construct Car with tyre's radius " << radius
		<< "and engine's manufacture " << manu << std::endl;
}

Car::~Car()
{
	std::cout << "Deconstruct Car " << std::endl;
}

int main(int argc, char* argv[])
{
	/*
		Construct Engine with manufacture Jili
		Construct Tyre with radius 20
		Construct Car with tyre's radius 20and engine's manufacture
		Engine's copy constructor Jili
		Deconstruct Car 
		Deconstruct Tyre whose radius is 20
		Deconstruct Engine whose manufacture is Jili
	*/
	Car car(20, std::string("Jili"));
	Car car2(car);
	system("pause");
	return 0;
}