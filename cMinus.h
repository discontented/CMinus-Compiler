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

class statement {
 public:
  virtual void print()=0 ;
  char* return_type (int t );
  //virtual void evaluate() = 0;
};

class exp_node: public statement {
public:
	// print function for pretty printing an expression
	virtual void print() = 0;

	// evaluation function for a leaf, replaced for interior nodes
	virtual float evaluate() = 0;
};

class operator_node : public exp_node
{
public:
	exp_node *left;
	exp_node *right;

	// the constructor for node links the node to its children,
	// and stores the character representation of the operator.
	operator_node(exp_node *L, exp_node *R);
};

class arr_var : public exp_node {
protected:
int var_type;
string id;
float value;
public:
arr_var( string id, float value);
arr_var(int var_type, string id, float value);
void print();
};

class assignment_stmt: public statement{
protected:
int var_type;
string id;
exp_node *expr;
public:
assignment_stmt (string id, exp_node *expr);
assignment_stmt (int var_type,string id, exp_node *expr);
void print();
};

class statement_list: public statement{
 protected:
 statement *st1;
 statement *st2;
public:
statement_list ( statement *st1,statement *st2 );
void print();
};

class number_node : public exp_node
{
private:
	float num;

public:
	number_node(float value);
	void print();
	float evaluate();
};

class unary_minus_node : public exp_node
{
protected:
	exp_node *exp;

public:
	unary_minus_node(exp_node *exp);
	void print();
	float evaluate();
};

class id_node : public exp_node
{
protected:
	string id;

public:
	id_node(string value);
	void print();
	float evaluate();
};

// plus_node inherits the characteristics of node and adds its own evaluate function
class plus_node : public operator_node
{
public:
	// plus_node's constructor just uses node's constructor
	plus_node(exp_node *L, exp_node *R);
	void print();
	float evaluate();
};

// minus_node inherits the characteristics of node and adds its own evaluate function
class minus_node : public operator_node
{
public:
	minus_node(exp_node *L, exp_node *R);
	void print();
	float evaluate();
};

// times_node inherits the characteristics of node and adds its own evaluate function
class times_node : public operator_node
{
public:
	times_node(exp_node *L, exp_node *R);
	void print();
	float evaluate();
};

// divide_node inherits the characteristics of node and adds its own evaluate function
class divide_node : public operator_node
{
public:
	divide_node(exp_node *L, exp_node *R);
	void print();
	float evaluate();
};

class cond_node
{
public:
	// print function for pretty printing an expression
	virtual void print() = 0;

	// evaluation function for a leaf, replaced for interior nodes
	virtual bool evaluate() = 0;
};

class or_cond_node : public cond_node
{
private:
	cond_node *left, *right;

public:
	or_cond_node(cond_node *L, cond_node *R);
	void print();
	bool evaluate();
};

class and_cond_node : public cond_node
{
private:
	cond_node *left, *right;

public:
	and_cond_node(cond_node *L, cond_node *R);
	void print();
	bool evaluate();
};

class neg_cond_node : public cond_node
{
private:
	cond_node *child;

public:
	neg_cond_node(cond_node *child);
	void print();
	bool evaluate();
};

class prim_cond_node : public cond_node
{
private:
	operation op;
	exp_node *left, *right;

public:
	prim_cond_node(operation op, exp_node *L, exp_node *R);
	void print();
	bool evaluate();
};

class test
{
private:
	cond_node *condition;

public:
	test(cond_node *condition);
	void print();
	bool evaluate();
};

class statement
{
public:
	virtual void print(int) {}
	virtual void evaluate() = 0;
};

class ife_stmt : public statement
{
protected:
	test *condition;
	statement *thenbranch, *elsebranch;

public:
	ife_stmt(test *condition, statement *thenbranch, statement *elsebranch);
	void print(int);
	void evaluate();
};

class while_stmt : public statement
{
protected:
	test *condition;
	statement *bodystmt;

public:
	while_stmt(test *condition, statement *bodystmt);
	void print(int);
	void evaluate();
};

class input_stmt : public statement
{
protected:
	string id;

public:
	input_stmt(string name);
	void print(int);
	void evaluate();
};

class assignment_stmt : public statement
{
protected:
	string id;
	exp_node *exp;

public:
	assignment_stmt(string name, exp_node *expression);
	void print(int);
	void evaluate();
};

class print_stmt : public statement
{
protected:
	exp_node *exp;

public:
	print_stmt(exp_node *myexp);
	void print(int);
	void evaluate();
};

class skip_stmt : public statement
{
public:
	skip_stmt();
	void print(int);
	void evaluate();
};

class sequence_stmt : public statement
{
protected:
	statement *stmt1, *stmt2;

public:
	sequence_stmt(statement *mystmt1, statement *mystmt2);
	void print(int);
	void evaluate();
};

class expression_stmt : public statement
{
protected:
	exp_node *exp;

public:
	expression_stmt(exp_node *myexp);
	void print();
	void evaluate();
};

class func_stmt : public statement
{
protected:
	id_node *id;
	id_node *param;
	sequence_stmt *block;

public:
	func_stmt(id_node *myID, id_node *myParam, sequence_stmt *myBlock);
	void print();
	void evaluate();
};

extern map<string, float> state_float;
extern map<string, int> state_int;
extern map<string, string> state_string;