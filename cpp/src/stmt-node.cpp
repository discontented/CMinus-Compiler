#include "../include/cMinus.h"

/* Statement Nodes */

ife_stmt::ife_stmt(test *condition, statement *thenbranch, statement *elsebranch)
{
	this->condition = condition;
	this->thenbranch = thenbranch;
	this->elsebranch = elsebranch;
}

void ife_stmt::print(int n)
{
	output_tabs(n);
	cout << "if ";
	condition->print();
	cout << endl;
	output_tabs(n);
	cout << "then { " << endl;
	thenbranch->print(n + 1);
	cout << "} " << endl;
	output_tabs(n);
}

void ife_stmt::evaluate()
{

	if (condition->evaluate())
	{
		thenbranch->evaluate();
	}
	else
	{
		elsebranch->evaluate();
	}
}

while_stmt::while_stmt(test *condition, statement *bodystmt)
{
	this->condition = condition;
	this->bodystmt = bodystmt;
}

void while_stmt::print(int n)
{
	output_tabs(n);
	cout << "while ";
	condition->print();
	cout << " do {" << endl;
	bodystmt->print(n + 1);
	cout << "} ";
}

void while_stmt::evaluate()
{

	while (condition->evaluate())
	{
		bodystmt->evaluate();
	}
}

input_stmt::input_stmt(string name)
	: id(name) {}

void input_stmt::print(int n)
{
	output_tabs(n);
	cout << "read " << id;
}

void input_stmt::evaluate()
{
	float result;

	cout << "input " << id << ":" << endl;

	cin >> result;

	state_float[id] = result;
}

assignment_stmt::assignment_stmt(string name, exp_node *expression)
	: id(name), exp(expression) {}

void assignment_stmt::print(int n)
{
	//  cout << "in assignment" << "\n";
	output_tabs(n);
	cout << id << " = ";
	exp->print();
}

void assignment_stmt::evaluate()
{
	float result = exp->evaluate();

	state_float[id] = result;
}

print_stmt::print_stmt(exp_node *myexp) : exp(myexp) {}

void print_stmt::print(int n)
{
	output_tabs(n);
	cout << "print ";
	exp->print();
}

void print_stmt::evaluate()
{
	cout << "output: " << exp->evaluate() << endl
		 << endl;
}

skip_stmt::skip_stmt() {}

void skip_stmt::evaluate() {}
void skip_stmt::print(int n)
{
	output_tabs(n);
}

sequence_stmt::sequence_stmt(statement *mystmt1, statement *mystmt2) : stmt1(mystmt1), stmt2(mystmt2)
{
}

void sequence_stmt::print(int n)
{
	stmt1->print(n);
	cout << " ;" << endl;
	stmt2->print(n);
}

void sequence_stmt::evaluate()
{
	stmt1->evaluate();
	stmt2->evaluate();
}

expression_stmt::expression_stmt(exp_node *myexp) : exp(myexp) {}

void expression_stmt::print() {}

void expression_stmt::evaluate()
{
	exp->evaluate();
}
/* End statement nodes */