#include "../include/cMinus.h"

// the constructor for node links the node to its children,
// and stores the character representation of the operator.
operator_node::operator_node(exp_node *L, exp_node *R)
{
	left = L;
	right = R;
}

number_node::number_node(float value)
{
	num = value;
}

void number_node::print()
{
	cout << num;
}

float number_node::evaluate()
{
	return num;
}

id_node::id_node(string value) : id(value) {}

void id_node::print()
{
	cout << id;
}

float id_node::evaluate()
{
	return state_float[id];
}

// plus_node inherits the characteristics of node and adds its own evaluate function
// plus_node's constructor just uses node's constructor
plus_node::plus_node(exp_node *L, exp_node *R) : operator_node(L, R)
{
}

void plus_node::print()
{
	cout << "(";
	left->print();
	cout << " + ";
	right->print();
	cout << ")";
}

float plus_node::evaluate()
{
	float left_num, right_num;

	left_num = left->evaluate();
	right_num = right->evaluate();

	return left_num + right_num;
}

// minus_node inherits the characteristics of node and adds its own evaluate function
minus_node::minus_node(exp_node *L, exp_node *R) : operator_node(L, R)
{
}

void minus_node::print()
{
	cout << "(";
	left->print();
	cout << " - ";
	right->print();
	cout << ")";
}

float minus_node::evaluate()
{
	float left_num, right_num;

	left_num = left->evaluate();
	right_num = right->evaluate();

	return left_num - right_num;
}

// times_node inherits the characteristics of node and adds its own evaluate function
times_node::times_node(exp_node *L, exp_node *R) : operator_node(L, R)
{
}

void times_node::print()
{
	cout << "(";
	left->print();
	cout << " * ";
	right->print();
	cout << ")";
}

float times_node::evaluate()
{
	float left_num, right_num;

	left_num = left->evaluate();
	right_num = right->evaluate();

	return left_num * right_num;
}

// divide_node inherits the characteristics of node and adds its own evaluate function

divide_node::divide_node(exp_node *L, exp_node *R) : operator_node(L, R)
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

unary_minus_node::unary_minus_node(exp_node *L) : exp(L) {}

void unary_minus_node::print()
{
	cout << "- ( ";
	exp->print();
	cout << " )";
}

float unary_minus_node::evaluate()
{
	float expValue = exp->evaluate();
	return -expValue;
}

/* End Expression Nodes */