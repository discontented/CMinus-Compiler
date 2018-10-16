#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>

using namespace std;

enum operation
{
	EQ,
	GT,
	GE,
	LT,
	LE,
	NO
};

template <typename T>

class exp_node
{
public:
	// print function for pretty printing an expression
	virtual void print() = 0;

	// evaluation function for a leaf, replaced for interior nodes
	virtual T evaluate() = 0;
};

template <typename T>
class operator_node : public exp_node<T>
{
public:
	exp_node<T> *left, *right;

	// the constructor for node links the node to its children,
	// and stores the character representation of the operator.
	operator_node(exp_node<T> *L, exp_node<T> *R);
};
template <typename T>
class number_node : public exp_node<T>
{
private:
	T num;

public:
	number_node(T value);
	void print();
	T evaluate();
};
template <typename T>
class unary_minus_node : public exp_node<T>
{
protected:
	exp_node<T> *exp;

public:
	unary_minus_node(exp_node<T> *exp);
	void print();
	float evaluate();
};

template <typename T>
class id_node : public exp_node<T>
{
protected:
	string id;

public:
	id_node(string value);
	void print();
	float evaluate();
};

// plus_node inherits the characteristics of node and adds its own evaluatefunction
template <typename T>
class plus_node : public operator_node<T>
{
public:
	// plus_node's constructor just uses node's constructor
	plus_node(exp_node<T> *L, exp_node<T> *R);
	void print();
	float evaluate();
};

// minus_node inherits the characteristics of node and adds its own evaluate function
template <typename T>
class minus_node : public operator_node<T>
{
public:
	minus_node(exp_node<T> *L, exp_node<T> *R);
	void print();
	float evaluate();
};

// times_node inherits the characteristics of node and adds its own evaluate function
template <typename T>
class times_node : public operator_node<T>
{
public:
	times_node(exp_node<T> *L, exp_node<T> *R);
	void print();
	float evaluate();
};

// divide_node inherits the characteristics of node and adds its own evaluate function
template <typename T>
class divide_node : public operator_node<T>
{
public:
	divide_node(exp_node<T> *L, exp_node<T> *R);
	void print();
	float evaluate();
};

template <typename T>
class cond_node
{
public:
	// print function for pretty printing an expression
	virtual void print() = 0;

	// evaluation function for a leaf, replaced for interior nodes
	virtual T evaluate() = 0;
};

template <typename T>
class or_cond_node : public cond_node<T>
{
private:
	cond_node<T> *left, *right;

public:
	or_cond_node(cond_node<T> *L, cond_node<T> *R);
	void print();
	bool evaluate();
};

template <typename T>
class and_cond_node : public cond_node<T>
{
private:
	cond_node<T> *left, *right;

public:
	and_cond_node(cond_node<T> *L, cond_node<T> *R);
	void print();
	bool evaluate();
};

template <typename T>
class neg_cond_node : public cond_node<T>
{
private:
	cond_node<T> *child;

public:
	neg_cond_node(cond_node<T> *child);
	void print();
	bool evaluate();
};

template <typename T>
class prim_cond_node : public cond_node<T>
{
private:
	operation op;
	exp_node<T> *left, *right;

public:
	prim_cond_node(operation op, exp_node<T> *L, exp_node<T> *R);
	void print();
	bool evaluate();
};

template <typename T>
class test
{
private:
	cond_node<T> *condition;

public:
	test(cond_node<T> *condition);
	void print();
	bool evaluate();
};

template <typename T>
class statement
{
public:
	virtual void print(int) {}
	virtual void evaluate() = 0;
};

template <typename T>
class ife_stmt : public statement<T>
{
protected:
	test<T> *condition;
	statement<T> *thenbranch, *elsebranch;

public:
	ife_stmt(test<T> *condition, statement<T> *thenbranch, statement<T> *elsebranch);
	void print(int);
	void evaluate();
};

template <typename T>
class while_stmt : public statement<T>
{
protected:
	test<T> *condition;
	statement<T> *bodystmt;

public:
	while_stmt(test<T> *condition, statement<T> *bodystmt);
	void print(int);
	void evaluate();
};
template <typename T>
class input_stmt : public statement<T>
{
protected:
	string id;

public:
	input_stmt(string name);
	void print(int);
	void evaluate();
};
template <typename T>
class assignment_stmt : public statement<T>
{
protected:
	string id;
	exp_node<T> *exp;

public:
	assignment_stmt(string name, exp_node<T> *expression);
	void print(int);
	void evaluate();
};
template <typename T>
class print_stmt : public statement<T>
{
protected:
	exp_node<T> *exp;

public:
	print_stmt(exp_node<T> *myexp);
	void print(int);
	void evaluate();
};
template <typename T>
class skip_stmt : public statement<T>
{
public:
	skip_stmt();
	void print(int);
	void evaluate();
};
template <typename T>
class sequence_stmt : public statement<T>
{
protected:
	statement<T> *stmt1, *stmt2;

public:
	sequence_stmt(statement<T> *mystmt1, statement<T> *mystmt2);
	void print(int);
	void evaluate();
};

template <typename T>
class expression_stmt : public statement<T>
{
protected:
	exp_node<T> *exp;

public:
	expression_stmt(exp_node<T> *myexp);
	void print();
	void evaluate();
};

template <typename T>
class func_stmt : public statement<T>
{
protected:
	id_node<T> *id;
	id_node<T> *param;
	sequence_stmt<T> *block;

public:
	func_stmt(id_node<T> *myID, id_node<T> *myParam, sequence_stmt<T> *myBlock);
	void print();
	void evaluate();
};

extern map<string, void*> state;