#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>

using namespace std;

class statement
{
public:
  virtual void print() = 0;
  char *returnvariable_type(int t);
  //virtual void evaluate() = 0;
};

class exp_node : public statement
{
public:
  // print function for pretty printing an expression
  virtual void print() = 0;

  // evaluation function for a leaf, replaced for interior nodes
  //virtual float evaluate() = 0;
};

class operator_node : public exp_node
{
public:
  exp_node *left;
  exp_node *right;
  operator_node(exp_node *L, exp_node *R);
};

//**************************************
class arr1d_var : public exp_node
{
protected:
  int var_type;
  string id;
  float value;

public:
  arr1d_var(string id, float value);
  arr1d_var(int var_type, string id, float value);
  void print();
};

class arr2d_var : public exp_node
{
protected:
  int var_type;
  string id;
  float value1;
  float value2;

public:
  arr2d_var(string id, float value1, float value2);
  arr2d_var(int var_type, string id, float value1, float value2);
  void print();
};

class assignment_stmt : public statement
{
protected:
  int var_type;
  string id;
  exp_node *expr;

public:
  assignment_stmt(string id, exp_node *expr);
  assignment_stmt(int var_type, string id, exp_node *expr);
  void print();
};

class statement_list : public statement
{
protected:
  statement *st1;
  statement *st2;

public:
  statement_list(statement *st1, statement *st2);
  void print();
};
//********************************

class logical_oror : public exp_node
{
protected:
  exp_node *expr1;
  exp_node *expr2;

public:
  logical_oror(exp_node *expr1, exp_node *expr2);
  void print();
};

class logical_andand : public exp_node
{
protected:
  exp_node *expr1;
  exp_node *expr2;

public:
  logical_andand(exp_node *expr1, exp_node *expr2);
  void print();
};

class logical_equalequal : public exp_node
{
protected:
  exp_node *expr1;
  exp_node *expr2;

public:
  logical_equalequal(exp_node *expr1, exp_node *expr2);
  void print();
};

class logical_notequal : public exp_node
{
protected:
  exp_node *expr1;
  exp_node *expr2;

public:
  logical_notequal(exp_node *expr1, exp_node *expr2);
  void print();
};

class logical_less : public exp_node
{
protected:
  exp_node *expr1;
  exp_node *expr2;

public:
  logical_less(exp_node *expr1, exp_node *expr2);
  void print();
};

class logical_great : public exp_node
{
protected:
  exp_node *expr1;
  exp_node *expr2;

public:
  logical_great(exp_node *expr1, exp_node *expr2);
  void print();
};

class logical_lessequal : public exp_node
{
protected:
  exp_node *expr1;
  exp_node *expr2;

public:
  logical_lessequal(exp_node *expr1, exp_node *expr2);
  void print();
};

class logical_greatequal : public exp_node
{
protected:
  exp_node *expr1;
  exp_node *expr2;

public:
  logical_greatequal(exp_node *expr1, exp_node *expr2);
  void print();
};

class plus_expression : public exp_node
{
protected:
  exp_node *expr1;
  exp_node *expr2;

public:
  plus_expression(exp_node *expr1, exp_node *expr2);
  void print();
};

class minus_expression : public exp_node
{
protected:
  exp_node *expr1;
  exp_node *expr2;

public:
  minus_expression(exp_node *expr1, exp_node *expr2);
  void print();
};

class times_expression : public exp_node
{
protected:
  exp_node *expr1;
  exp_node *expr2;

public:
  times_expression(exp_node *expr1, exp_node *expr2);
  void print();
};

class divide_expression : public exp_node
{
protected:
  exp_node *expr1;
  exp_node *expr2;

public:
  divide_expression(exp_node *expr1, exp_node *expr2);
  void print();
};

class modulo_expression : public exp_node
{
protected:
  exp_node *expr1;
  exp_node *expr2;

public:
  modulo_expression(exp_node *expr1, exp_node *expr2);
  void print();
};

class if_then_stmt : public statement
{
protected:
  exp_node *expr;
  statement *st;

public:
  if_then_stmt(exp_node *expr, statement *st);
  void print();
};

class if_then_else_stmt : public statement
{
protected:
  exp_node *expr;
  statement *st1;
  statement *st2;

public:
  if_then_else_stmt(exp_node *expr, statement *st1, statement *st2);
  void print();
};

class while_stmt : public statement
{
protected:
  exp_node *expr;
  statement *st;

public:
  while_stmt(exp_node *expr, statement *st);
  void print();
};

class do_while_stmt : public statement
{
protected:
  exp_node *expr;
  statement *st;

public:
  do_while_stmt(statement *st, exp_node *expr);
  void print();
};

class for_stmt : public statement
{
protected:
  string id;
  exp_node *condition;
  exp_node *incrementation;
  statement *st;

public:
  for_stmt(string id, exp_node *condition, exp_node *incrementation, statement *st);
  void print();
};

class id_node : public exp_node
{
protected:
  string id;

public:
  id_node(string value);
  void print();
};

class param_node : public exp_node
{
protected:
  int var_type;
  string id;

public:
  param_node(int var_type, string value);
  void print();
};

class number_node : public exp_node
{
private:
  float num;

public:
  number_node(float value);
  void print();
};
//*********************************
class var_node : public exp_node
{
protected:
  int var_type;
  string id;
  exp_node *list;

public:
  var_node(int var_type, string id, exp_node *list);
  var_node(string id, exp_node *list);
  void print();
};
//********************************
class skip_stmt : public exp_node
{
public:
  skip_stmt();
  void print();
  //void evaluate();
};

class arg_node : public exp_node
{
protected:
  exp_node *stmt1, *stmt2;

public:
  arg_node(exp_node *stmt1, exp_node *stmt2);
  void print();
};

class function_parameter : public statement
{
protected:
  statement *stmt1;
  statement *stmt2;

public:
  function_parameter(statement *stmt1, statement *stmt2);
  void print();
};

class function_definition : public statement
{
public:
  int var_type;
  string id;
  exp_node *arg;
  statement *st;

public:
  function_definition(int var_type, string id, exp_node *arg, statement *st);
  void print();
};

class return_stmt : public statement
{
public:
  exp_node *expr;

public:
  return_stmt(exp_node *expr);
  void print();
};

class call_list : public exp_node
{
protected:
  exp_node *arg_list;
  exp_node *expr;

public:
  call_list(exp_node *arg_list, exp_node *expr);
  void print();
};

class call_stmt : public exp_node
{
protected:
  string id;
  exp_node *list;

public:
  call_stmt(string id, exp_node *list);
  void print();
};

extern map<string, float> idTable;