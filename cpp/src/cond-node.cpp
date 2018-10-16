#include "../include/cMinus.h"

/* Conditions Nodes */

or_cond_node::or_cond_node(cond_node *L, cond_node *R) : left(L), right(R)
{
}

void or_cond_node::print()
{
	cout << "(";
	left->print();
	cout << ") ||  (";
	right->print();
	cout << ")";
}

bool or_cond_node::evaluate()
{
	return (left->evaluate()) || (right->evaluate());
}

and_cond_node::and_cond_node(cond_node *L, cond_node *R) : left(L), right(R)
{
}

void and_cond_node::print()
{
	cout << "(";
	left->print();
	cout << ") &&  (";
	right->print();
	cout << ")";
}

bool and_cond_node::evaluate()
{
	return (left->evaluate()) && (right->evaluate());
}

neg_cond_node::neg_cond_node(cond_node *child)
{
	this->child = child;
}

void neg_cond_node::print()
{
	cout << "! (";
	child->print();
	cout << ")";
}

bool neg_cond_node::evaluate()
{
	return !(child->evaluate());
}

prim_cond_node::prim_cond_node(operation op, exp_node *left, exp_node *right)
{
	this->op = op;
	this->left = left;
	this->right = right;
}

void prim_cond_node::print()
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

bool prim_cond_node::evaluate()
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
