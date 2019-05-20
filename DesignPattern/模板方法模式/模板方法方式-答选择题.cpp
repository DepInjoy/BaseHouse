#include <iostream>
#include <string>
/*
	试卷类：
		每个考生的题是相同的，提取为公共特征
		考生只需要重新答案接口即可
*/
class Paper
{
public:
	void testQuestion1(void){
		std::cout << "__you ___a meeting at four yesterday afternoon ?" << std::endl
			<< "A.Were ... having\tB.Was ... having\tC.Did ... have\tD.Do ... have" << std::endl
			<< "Your choose : " << answer1() << std::endl;		
	}
	void testQuestion2(void){
		std::cout << "What__ your grandfather__this time yesterday ?" << std::endl
			<< "A.is ... doing\t B.was ... doing\t C.did .. do\t D.had ... done" << std::endl
			<< "Your choose : " << answer2() << std::endl;
	}
	virtual std::string answer1(void){ return " "; }
	virtual std::string answer2(void){ return " "; }
};

class Stuent1 : public Paper
{
public:
	std::string answer1(void){ return "A"; }
	std::string answer2(void){ return "B "; }
};

class Stuent2 : public Paper
{
public:
	std::string answer1(void){ return "C"; }
	std::string answer2(void){ return "D"; }
};

int main(void)
{
	Paper* _paper0 = new Stuent1();
	_paper0->testQuestion1();
	_paper0->testQuestion2();
	std::cout << std::endl << std::endl;
	delete _paper0;

	Paper* _paper1 = new Stuent2();
	_paper1->testQuestion1();
	_paper1->testQuestion2();
	delete _paper1;
	system("pause");
	return 0;
}