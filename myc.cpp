#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>
#include "myc.h"
#include "y.tab.h"

using namespace std;

string statement::returnvariable_type(int t)
{
  switch (t)
  {
  case INT:
    return "int";
  case CHAR:
    return "char";
  case VOID:
    return "void";
  case STRING:
    return "string";
  }
}


string exp_node::returnvariable_type(int t)
{
  switch (t)
  {
  case INT:
    return "int";
  case CHAR:
    return "char";
  case VOID:
    return "void";
  case STRING:
    return "string";
  }
}

expression_stmt::expression_stmt(exp_node *myexp) : exp(myexp) {}

void expression_stmt::print() {}

void expression_stmt::evaluate()
{
    exp->evaluate();
}

//function_definition
function_definition::function_definition(int var_type, string id, exp_node *arg, statement *st)
    : var_type(var_type), id(id), arg(arg), st(st) {}
void function_definition::print()
{
  cout << returnvariable_type(var_type);
  cout << "  " << id;
  cout << "(";
  arg->print();
  cout << ")";
  cout << "\n";
  cout << "{";
  cout << "\n";
  st->print();
  cout << "}";
  cout << "\n";
}

//arg_node for functions
arg_node::arg_node(exp_node *stmt1, exp_node *stmt2)
    : stmt1(stmt1), stmt2(stmt2) {}
void arg_node::print()
{
  stmt1->print();
  cout << ",";
  stmt2->print();
}

//function_parameter
function_parameter::function_parameter(statement *stmt1, statement *stmt2)
    : stmt1(stmt1), stmt2(stmt2) {}
void function_parameter::print()
{
  stmt1->print();
  stmt2->print();
}

operator_node::operator_node(exp_node *L, exp_node *R)
{
  left = L;
  right = R;
}
//**************************************
//for global variable
var_node::var_node(int var_type, string id)
    : var_type(var_type), id(id) {}

void var_node::print()
{
  if (var_type != -1)
    cout << returnvariable_type(var_type);
  cout << "  " << id;
  cout << ";";
  cout << "\n";
}

//for 1D array
arr_var::arr_var(int var_type, string id, float value)
    : var_type(var_type), id(id), value(value) {}
arr_var::arr_var(string id, float value)
    : var_type(-1), id(id), value(value) {}
void arr_var::print()
{
  if (var_type != -1)
    cout << returnvariable_type(var_type);
  //cout << "1D Array :";
  //cout << "\n";
  cout << "  " << id << "[" << value << "]"
       << ";"
       << "\n";
}

//assignment statement
assignment_stmt::assignment_stmt(int var_type, string id, exp_node *expr)
    : var_type(var_type), id(id), expr(expr) {}
assignment_stmt::assignment_stmt(string id, exp_node *expr)
    : var_type(-1), id(id), expr(expr) {}
void assignment_stmt::print()
{
  //cout << "Assignment Statement: ";
  if (var_type != -1)
    cout << returnvariable_type(var_type);
  cout << "  " << id << "=";
  expr->print();
  cout << ";";
  cout << "\n";
}

statement_list::statement_list(statement *st1, statement *st2)
    : st1(st1), st2(st2) {}
void statement_list::print()
{
  st1->print();
  //cout << "\n";
  st2->print();
}
//*************************************
//logical_oror
logical_oror::logical_oror(exp_node *expr1, exp_node *expr2)
    : expr1(expr1), expr2(expr2) {}
void logical_oror::print()
{
  //cout << "Logical OR: ";

  expr1->print();
  cout << "||";
  expr2->print();
}

//logical_andand
logical_andand::logical_andand(exp_node *expr1, exp_node *expr2)
    : expr1(expr1), expr2(expr2) {}
void logical_andand::print()
{
  //cout << "Logical AND: ";

  expr1->print();
  cout << "&&";
  expr2->print();
}

//logical_equalequal
logical_equalequal::logical_equalequal(exp_node *expr1, exp_node *expr2)
    : expr1(expr1), expr2(expr2) {}
void logical_equalequal::print()
{
  //cout << "Logical EQUALITY: ";

  expr1->print();
  cout << "==";
  expr2->print();
}

//logical_notequal
logical_notequal::logical_notequal(exp_node *expr1, exp_node *expr2)
    : expr1(expr1), expr2(expr2) {}
void logical_notequal::print()
{
  //cout << "Logical NON-EQUALITY: ";

  expr1->print();
  cout << "!=";
  expr2->print();
}

//logical_less
logical_less::logical_less(exp_node *expr1, exp_node *expr2)
    : expr1(expr1), expr2(expr2) {}
void logical_less::print()
{
  //cout << "Logical LESS THAN: ";

  expr1->print();
  cout << "<";
  expr2->print();
  //cout << "\n";
}

//logical_great
logical_great::logical_great(exp_node *expr1, exp_node *expr2)
    : expr1(expr1), expr2(expr2) {}
void logical_great::print()
{
  //cout << "Logical GREATER THAN: ";

  expr1->print();
  cout << ">";
  expr2->print();
  //cout << "\n";
}

//logical_lessequal
logical_lessequal::logical_lessequal(exp_node *expr1, exp_node *expr2)
    : expr1(expr1), expr2(expr2) {}
void logical_lessequal::print()
{
  //cout << "Logical LESS THAN OR EQUAL TO: ";

  expr1->print();
  cout << "<=";
  expr2->print();
  //cout << "\n";
}

//logical_greatequal
logical_greatequal::logical_greatequal(exp_node *expr1, exp_node *expr2)
    : expr1(expr1), expr2(expr2) {}
void logical_greatequal::print()
{
  //cout << "Logical GREATER THAN OR EQUAL TO: ";

  expr1->print();
  cout << ">=";
  expr2->print();
  //cout << "\n";
}

//plus_expression
plus_expression::plus_expression(exp_node *expr1, exp_node *expr2)
    : expr1(expr1), expr2(expr2) {}
void plus_expression::print()
{
  //cout << "ADDITION Expression: ";

  //cout << "(";
  expr1->print();
  cout << "+";
  expr2->print();
  cout << ";";
}

//minus_expression
minus_expression::minus_expression(exp_node *expr1, exp_node *expr2)
    : expr1(expr1), expr2(expr2) {}
void minus_expression::print()
{
  //cout << "MINUS Expression: ";

  expr1->print();
  cout << "-";
  expr2->print();
  cout << ";";
}

//times_expression
times_expression::times_expression(exp_node *expr1, exp_node *expr2)
    : expr1(expr1), expr2(expr2) {}
void times_expression::print()
{
  //cout << "MULTIPLICATION Expression: ";

  expr1->print();
  cout << "*";
  expr2->print();
  cout << ";";
}

//divide_expression
divide_expression::divide_expression(exp_node *expr1, exp_node *expr2)
    : expr1(expr1), expr2(expr2) {}
void divide_expression::print()
{
  //cout << "DIVIDE Expression: ";

  expr1->print();
  cout << "/";
  expr2->print();
  cout << ";";
}

//modulo_expression
modulo_expression::modulo_expression(exp_node *expr1, exp_node *expr2)
    : expr1(expr1), expr2(expr2) {}
void modulo_expression::print()
{
  //cout << "MODULO Expression: ";

  expr1->print();
  cout << "%";
  expr2->print();
  cout << ";";
}

//if_then_stmt
if_then_stmt::if_then_stmt(exp_node *expr, statement *st)
    : expr(expr), st(st) {}
void if_then_stmt::print()
{
  //cout << "IF_THEN Statement:";
  //cout << "\n";
  cout << "if";
  cout << "(";
  expr->print();
  cout << ")";
  //cout <<"then";
  cout << "{";
  cout << "\n";
  st->print();
  cout << "\n";
  cout << "}";
  cout << "\n";
}

//if_then_else_stmt
if_then_else_stmt::if_then_else_stmt(exp_node *expr, statement *st1, statement *st2)
    : expr(expr), st1(st1), st2(st2) {}
void if_then_else_stmt::print()
{
  //cout << "IF_THEN_ELSE Statement:";
  //cout << "\n";
  cout << "if";
  cout << "(";
  expr->print();
  cout << ")";
  //cout << "then \n";
  cout << "{";
  cout << "\n";
  st1->print();
  cout << "\n";
  cout << "}";
  cout << "else \n";
  cout << "{";
  cout << "\n";
  st2->print();
  cout << "\n";
  cout << "}";
  cout << "\n";
}

//while_stmt
while_stmt::while_stmt(exp_node *expr, statement *st)
    : expr(expr), st(st) {}
void while_stmt::print()
{
  //cout << "WHILE Statement:";
  //cout << "\n";
  cout << "while";
  cout << "(";
  expr->print();
  cout << ")";
  //cout << "then";
  cout << "{";
  cout << "\n";
  st->print();
  cout << "\n";
  cout << "}";
  cout << "\n";
}

//do_while_stmt
do_while_stmt::do_while_stmt(statement *st, exp_node *expr)
    : expr(expr), st(st) {}
void do_while_stmt::print()
{
  //cout << "DO_WHILE Statement:";
  cout << "\n";
  cout << "do";
  cout << "{";
  cout << "\n";
  st->print();
  cout << "}";
  cout << "  ";
  cout << "while";
  cout << "(";
  expr->print();
  cout << ")";
  cout << "\n";
  cout << "\n";
}

//for_statement
for_stmt::for_stmt(string id, exp_node *condition, exp_node *incrementation, statement *st)
    : id(id), condition(condition), incrementation(incrementation), st(st) {}
void for_stmt::print()
{
  cout << "for (" << id;
  cout << ";";
  condition->print();
  cout << ";";
  incrementation->print();
  cout << ")"
       << "\n";
  cout << "{\n";
  st->print();
  cout << "\n} \n";
}

// id_node code
id_node::id_node(string value)
    : id(value) {}
void id_node::print()
{
  //cout << "\n";
  //cout << "\"" <<"id node:";
  cout << id; //<<"\"" << "\n";
}

// id_node code
param_node::param_node(int var_type, string value)
    : var_type(var_type), id(value) {}
void param_node::print()
{
  cout << returnvariable_type(var_type) << "  ";
  cout << id;
}

//call_list
call_list::call_list(exp_node *arg_list, exp_node *expr)
    : arg_list(arg_list), expr(expr) {}
void call_list::print()
{
  cout << "(";
  arg_list->print();
  cout << ",";
  expr->print();
  cout << ")";
}

//call_stmt
call_stmt::call_stmt(string id, exp_node *list)
    : id(id), list(list) {}
void call_stmt::print()
{
  cout << id;
  list->print();
  cout << ";";
  cout << "\n";
}

// number node
number_node::number_node(float value) { num = value; }
void number_node::print()
{
  //cout << "\n";
  cout << num;
}

float number_node::evaluate()
{
    return num;
}

//skip statement
skip_stmt::skip_stmt() {}
void skip_stmt::print() {}

//skip expression
skip_exp::skip_exp() {}
void skip_exp::print() {}

//return statement
return_stmt::return_stmt(exp_node *expr)
    : expr(expr) {}
void return_stmt::print()
{
  cout << "return";
  cout << "(";
  expr->print();
  cout << ")";
  cout << ";";
  cout << "\n";
}
map<string, float> idTable;