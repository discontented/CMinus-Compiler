#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>
#include "cMinus.h"

using namespace std;

map<string, void*> state;


// preconditon: n>=0
void output_tabs(int n)
{
	while (n > 0)
	{
		cout << "\t";
		n--;
	}
}

/* Conditions Nodes */

template<typename T>
or_cond_node<T>::or_cond_node(cond_node<T> *L, cond_node<T> *R) : left(L), right(R)
{
}

template<typename T>
void or_cond_node<T>::print()
{
	cout << "(";
	left->print();
	cout << ") ||  (";
	right->print();
	cout << ")";
}

template<typename T>
bool or_cond_node<T>::evaluate()
{
	return (left->evaluate()) || (right->evaluate());
}

template<typename T>
and_cond_node<T>::and_cond_node(cond_node<T> *L, cond_node<T> *R) : left(L), right(R)
{
}

template<typename T>
void and_cond_node<T>::print()
{
	cout << "(";
	left->print();
	cout << ") &&  (";
	right->print();
	cout << ")";
}

template<typename T>
bool and_cond_node<T>::evaluate()
{
	return (left->evaluate()) && (right->evaluate());
}

template<typename T>
neg_cond_node<T>::neg_cond_node(cond_node<T> *child)
{
	this->child = child;
}

template<typename T>
void neg_cond_node<T>::print()
{
	cout << "! (";
	child->print();
	cout << ")";
}

template<typename T>
bool neg_cond_node<T>::evaluate()
{
	return !(child->evaluate());
}

template<typename T>
prim_cond_node<T>::prim_cond_node(operation<T> op, exp_node<T> *left, exp_node<T> *right)
{
	this->op = op;
	this->left = left;
	this->right = right;
}

template<typename T>
void prim_cond_node<T>::print()
{
	left->print();
	switch (op)
	{
	case GT:
		cout << ">";
		break;
	case GE:
		cout << ">=";
		break;
	case LT:
		cout << "<";
		break;
	case LE:
		cout << "<=";
		break;
	case EQ:
		cout << "==";
		break;
	case NO:
		cout << "!=";
		break;
	}
	right->print();
}

template<typename T>
bool prim_cond_node<T>::evaluate()
{
	float opdl, opdr;

	opdl = left->evaluate();
	opdr = right->evaluate();

	switch (op)
	{
	case GT:
		return (opdl > opdr);
		break;
	case GE:
		return (opdl >= opdr);
		break;
	case LT:
		return (opdl < opdr);
		break;
	case LE:
		return (opdl <= opdr);
		break;
	case EQ:
		return (opdl == opdr);
		break;
	case NO:
		return (opdl != opdr);
		break;
	}
}

/* End Condition Node */

/* Expression Nodes */

// the constructor for node links the node to its children,
// and stores the character representation of the operator.
template<typename T>
operator_node<T>::operator_node(exp_node<T> *L, exp_node<T> *R)
{
	left = L;
	right = R;
}

template<typename T>
number_node<T>::number_node(T value)
{
	num = value;
}

template<typename T>
void number_node<T>::print()
{
	cout << num;
}

template<typename T>
float number_node<T>::evaluate()
{
	return num;
}

template<typename T>
id_node<T>::id_node(string value) : id(value) {}

template<typename T>
void id_node<T>::print()
{
	cout << id;
}

template<typename T>
float id_node<T>::evaluate()
{
	return state[id];
}

// plus_node inherits the characteristics of node and adds its own evaluate function
// plus_node's constructor just uses node's constructor
template<typename T>
plus_node<T>::plus_node(exp_node<T> *L, exp_node<T> *R) : operator_node(L, R)
{
}

template<typename T>
void plus_node<T>::print()
{
	cout << "(";
	left->print();
	cout << " + ";
	right->print();
	cout << ")";
}

template<typename T>
float plus_node<T>::evaluate()
{
	float left_num, right_num;

	left_num = left->evaluate();
	right_num = right->evaluate();

	return left_num + right_num;
}

// minus_node inherits the characteristics of node and adds its own evaluate function
template<typename T>
minus_node<T>::minus_node(exp_node<T> *L, exp_node<T> *R) : operator_node(L, R)
{
}

template<typename T>
void minus_node<T>::print()
{
	cout << "(";
	left->print();
	cout << " - ";
	right->print();
	cout << ")";
}

template<typename T>
float minus_node<T>::evaluate()
{
	float left_num, right_num;

	left_num = left->evaluate();
	right_num = right->evaluate();

	return left_num - right_num;
}

// times_node inherits the characteristics of node and adds its own evaluate function
times_node<T>::times_node(exp_node<T> *L, exp_node<T> *R) : operator_node(L, R)
{
}
template<typename T>
void times_node<T>::print()
{
	cout << "(";
	left->print();
	cout << " * ";
	right->print();
	cout << ")";
}
template<typename T>
float times_node<T>::evaluate()
{
	float left_num, right_num;

	left_num = left->evaluate();
	right_num = right->evaluate();

	return left_num * right_num;
}

// divide_node inherits the characteristics of node and adds its own evaluate functiontemplate<typename T>
template<typename T>
divide_node<T>::divide_node(exp_node<T> *L, exp_node<T> *R) : operator_node(L, R)
{
}

void divide_node::print()
{
	cout << "(";
	left->print();
	cout << " / ";
	right->print();
	cout << ")";
}

float divide_node::evaluate()
{
	float left_num, right_num;

	left_num = left->evaluate();
	right_num = right->evaluate();

	if (right_num)
	{
		return left_num / right_num;
	}
	else
	{
		cout << "division by zero -> " << left_num << " / " << 0 << endl;
		//  include stdlib.h for exit
		exit(1);
	}
}
template<typename T>
unary_minus_node<T>::unary_minus_node(exp_node<T> *L) : exp(L) {}

void unary_minus_node<T>::print()
{
	cout << "- ( ";
	exp->print();
	cout << " )";
}

float unary_minus_node<T>::evaluate()
{
	float expValue = exp->evaluate();
	return -expValue;
}

/* End Expression Nodes */

/* Statement Nodes */template<typename T>::ife_stmt(test *condition, statement *thenbranch, statement *elsebranch)
{
	this->condition = condition;
	this->thenbranch = thenbranch;
	this->elsebranch = elsebranch;
}

void ife_stmt<T>::print(int n)
{
	output_tabs(n);
	cout << "if (";
	condition->print();
	cout << ")";
	cout << endl;
	output_tabs(n);
	cout << " { " << endl;
	thenbranch->print(n + 1);
	cout << "} " << endl;
	output_tabs(n);
	cout << "else { " << endl;
	elsebranch->print(n + 1);
	cout << "} ";
}

void ife_stmt<T>::evaluate()
{

	if (condition->evaluate())
	{
		thenbranch->evaluate();
	}
	else
	{
		elsebranch->evaluate();
	}
}template<typename T>::while_stmt(test *condition, statement *bodystmt)
{
	this->condition = condition;
	this->bodystmt = bodystmt;
}

void while_stmt<T>::print(int n)
{
	output_tabs(n);
	cout << "while (";
	condition->print();
	cout << ") {" << endl;
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

template<typename T>
input_stmt<T>::input_stmt(string name)
	: id(name) {}

void input_stmt<T>::print(int n)
{
	output_tabs(n);
	cout << "read " << id;
}

void input_stmt<T>::evaluate()
{
	float result;

	cout << "input " << id << ":" << endl;

	cin >> result;

	state[id] = result;
}

template<typename T>
assignment_stmt<T>::assignment_stmt(string name, exp_node<T> *expression)
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

	state[id] = result;
}

template<typename T>
print_stmt<T>::print_stmt(exp_node<T> *myexp) : exp(myexp) {}

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

template<typename T>
skip_stmt<T>::skip_stmt() {}

void skip_stmt::evaluate() {}
void skip_stmt::print(int n)
{
	output_tabs(n);
}

template<typename T>
sequence_stmt<T>::sequence_stmt(statement *mystmt1, statement *mystmt2) : stmt1(mystmt1), stmt2(mystmt2)
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

template<typename T>
expression_stmt<T>::expression_stmt(exp_node<T> *myexp) : exp(myexp) {}

void expression_stmt::print() {}

void expression_stmt::evaluate()
{
	exp->evaluate();
}
/* End statement nodes */

bool test::evaluate()
{
	return condition->evaluate();
}

void test::print()
{
	condition->print();
}

template<typename T>
test<T>::test(cond_node<T> *condition)
{
	this->condition = condition;
}
