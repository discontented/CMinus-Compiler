#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>
#include "cMinus.h"

using namespace std;

map<string, float> state;

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
    case GE:
        cout << ">";
        break;
    case EQ:
        cout << "==";
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
    case GE:
        return (opdl > opdr);
        break;
    case EQ:
        return (opdl == opdr);
        break;
    }
}

/* End Condition Node */

/* Expression Nodes */

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
    return state[id];
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
    cout << "else { " << endl;
    elsebranch->print(n + 1);
    cout << "} ";
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

    state[id] = result;
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

    state[id] = result;
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

bool test::evaluate()
{
    return condition->evaluate();
}

void test::print()
{
    condition->print();
}

test::test(cond_node *condition)
{
    this->condition = condition;
}
