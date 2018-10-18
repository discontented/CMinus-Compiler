#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>
#include "myc.h"
#include "y.tab.h"

using namespace std;

funcStruct::funcStruct(int my_var_type, string my_id, exp_node *my_arg, statement *my_st) : var_type(my_var_type), id(my_id), arg(my_arg), st(my_st) {}

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

void function_definition::evaluate() {
  funcTable[id] = new funcStruct(var_type, id, arg, st);
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
float arg_node::evaluate() {
  stmt1->evaluate();
  return stmt2->evaluate();
}

//function_parameter
function_parameter::function_parameter(statement *stmt1, statement *stmt2)
    : stmt1(stmt1), stmt2(stmt2) {}
void function_parameter::print()
{
  stmt1->print();
  stmt2->print();
}
void function_parameter::evaluate() {
  stmt1->evaluate();
  stmt2->evaluate();
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
void var_node::evaluate() {
  idTable[id];
}
/*
//for 1D array
arr_var::arr_var(int var_type, string id, int value)
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
float arr_var::evaluate() {
  return arrayTable[id][value];
}
*/
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
void assignment_stmt::evaluate()
{
  float result = expr->evaluate();
  idTable[id] = result;
}

statement_list::statement_list(statement *st1, statement *st2)
    : st1(st1), st2(st2) {}
void statement_list::print()
{
  st1->print();
  //cout << "\n";
  st2->print();
}
void statement_list::evaluate() {
  st1->evaluate();
  st2->evaluate();
}

print_stmt::print_stmt(exp_node *myexp) : exp(myexp) {}

void print_stmt::print()
{
    cout << "print ";
    exp->print();
}

void print_stmt::evaluate()
{
    cout << "output: " << exp->evaluate() << endl
         << endl;
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
float logical_oror::evaluate() {
  return (expr1->evaluate()) || (expr2->evaluate());
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
float logical_andand::evaluate() {
  return (expr1->evaluate()) && (expr2->evaluate());
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

float logical_equalequal::evaluate() {
  return (expr1->evaluate()) == (expr2->evaluate());
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
float logical_notequal::evaluate() {
  return (expr1->evaluate()) != (expr2->evaluate());
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
float logical_less::evaluate() {
  return (expr1->evaluate()) > (expr2->evaluate());
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
float logical_great::evaluate() {
  return (expr1->evaluate()) > (expr2->evaluate());
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
float logical_lessequal::evaluate() {
  return (expr1->evaluate()) <= (expr2->evaluate());
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
float logical_greatequal::evaluate() {
  return (expr1->evaluate()) >= (expr2->evaluate());
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
float plus_expression::evaluate()
{
    float left_num, right_num;

    left_num = expr1->evaluate();
    right_num = expr2->evaluate();

    return left_num + right_num;
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

float minus_expression::evaluate()
{
    float left_num, right_num;

    left_num = expr1->evaluate();
    right_num = expr2->evaluate();

    return left_num - right_num;
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

float times_expression::evaluate()
{
    float left_num, right_num;

    left_num = expr1->evaluate();
    right_num = expr2->evaluate();

    return left_num * right_num;
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
float divide_expression::evaluate()
{
    float left_num, right_num;

    left_num = expr1->evaluate();
    right_num = expr2->evaluate();

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

float modulo_expression::evaluate()
{
    int left_num, right_num;

    left_num = expr1->evaluate();
    right_num = expr2->evaluate();

    return left_num % right_num;
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

void if_then_stmt::evaluate() {
  if(expr->evaluate()) {
    st->evaluate();
  }
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

void if_then_else_stmt::evaluate() {
  if(expr->evaluate()) {
    st1->evaluate();
  } else {
    st2->evaluate();
  }
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

void while_stmt::evaluate()
{
  while (expr->evaluate())
  {
    st->evaluate();
  }
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
float id_node::evaluate() {
  return idTable[id];
}


// id_node code
param_node::param_node(int var_type, string value)
    : var_type(var_type), id(value) {}
void param_node::print()
{
  cout << returnvariable_type(var_type) << "  ";
  cout << id;
}

float param_node::evaluate() {

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

float call_list::evaluate()
{
  arg_list->evaluate();
  expr->evaluate();
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
float call_stmt::evaluate() {
  funcTable[id]->st->evaluate();
  return funcTable[id]->arg->evaluate();
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
void skip_stmt::evaluate() {}

//skip expression
skip_exp::skip_exp() {}
void skip_exp::print() {}
float skip_exp::evaluate() {}

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

float return_stmt::evaluate() {
  return expr->evaluate();
}

map<string, float> idTable;
map<string, float*> arrayTable;
map<string, funcStruct*> funcTable;