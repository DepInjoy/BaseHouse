#include <iostream>
#include <string>
#include <sstream>

class  Complex
{
public:
	Complex(double r = 0.0, double i = 0.0){ real = r; image = i; }
	friend std::ostream& operator<<(std::ostream& o, Complex& c);
	friend std::istream& operator>>(std::istream& i, Complex& c);
private:
	double real;
	double image;
};
std::ostream& operator<<(std::ostream&o, Complex& c)
{
	if (c.image == 0.0)
		o << c.real;
	else if (c.image == 1)
		o << c.real << "+" << "i";
	else
		o << c.real << "+" << c.image << "i";
	return o;
}

std::istream& operator>>(std::istream& i, Complex& c)
{
	std::string s;
	i >> s;
	int rpos = s.find("+");
	if (rpos != std::string::npos){		//found
		std::string tmp = s.substr(0, rpos);
		c.real = atof(tmp.c_str());
	}else{
		std::stringstream sin(s);
		double t = 0.0;
		if (sin >> t){ //Transform sin to double number,succefully(not 0), failed(0)
			c.real = t;
		}			
	}
	std::size_t ipos = s.find("i");
	if (ipos != std::string::npos){
		if ((rpos + 1) == ipos)
			c.image = 1;		//Handle the issuse like 8+i
		else
			c.image = atof(s.substr(rpos, ipos).c_str());
	}
	return i;
}

int main(int argc, char* argv[])
{
	/*
		34.5				34.5
		8+i					8+i
		8+2i				8+2i
	*/
	Complex tmp;
	std::cin >> tmp;
	std::cout << "The comlex is " <<tmp << std::endl;
	system("pause");
	return 0;
}