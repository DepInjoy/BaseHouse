#include <iostream>
#include <string>
using namespace std;

// 包含解释器之外的全局信息
class Context {
public:
	void SetInput(string i) { input = i; }
	string GetInput() { return input; }
	void SetOutput(string o) { output = o; }
	string GetOutput() { return output; }
private:
	string input;
	string output;
};

//抽象表达式
class AbstractExpression {
public:
	virtual void Interpret(Context* context) = 0;
	//虚析构函数
	virtual ~AbstractExpression() {}
};

// 终结符表达式
class TerminalExpression : public AbstractExpression {
public:
	void Interpret(Context* context) {
		cout << "TerminalExpression: " << context->GetInput() << ", " << context->GetOutput() << endl;
	}
};
// 非终结符表达式
class NonterminalExpression : public AbstractExpression {
public:
	NonterminalExpression(AbstractExpression* e) { expression = e; }
	void Interpret(Context* context) {
		cout << "NonterminalExpression: " << context->GetInput() << ", " << context->GetOutput() << endl;
		expression->Interpret(context);
	}
private:
	AbstractExpression* expression;
};

int main() {
	Context* c = new Context();
	c->SetInput("Hello");
	c->SetOutput("World");

	AbstractExpression* exp1 = new TerminalExpression();
	AbstractExpression* exp2 = new NonterminalExpression(exp1);
	//TerminalExpression: Hello, World
	exp1->Interpret(c);
	/*
		NonterminalExpression: Hello, World
		TerminalExpression: Hello, World
	*/
	exp2->Interpret(c); 
	delete exp1;
	delete exp2;
	delete c;
	system("pause");
	return 0;
}