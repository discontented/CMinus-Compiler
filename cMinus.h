#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>

using namespace std;

class exp_node {
  public:

    // print function for pretty printing an expression
    virtual void print() = 0;

    // evaluation function for a leaf, replaced for interior nodes
    virtual float evaluate() = 0;
};

class binaryOp_node : public exp_node {
public:
    exp_node *left;
    exp_node *right;
    

  // the constructor for node links the node to its children,
  // and stores the character representation of the operator.
    binaryOp_node(exp_node *L, exp_node *R);
};

class number_node : public exp_node {
 private:
    float num;

 public:
  number_node(float value);
  void print();
  float evaluate();
};

class neg_node : public exp_node {
 protected:
  exp_node *exp;
 public:
  neg_node(exp_node *exp);
  void print();
  float evaluate();
};

typedef exp_node stmt_node;

class variable_node : public exp_node {
protected:
  string id;

public:
  variable_node(string value);
  void print();
  float evaluate();
};

// add_node inherits the characteristics of node and adds its own evaluate function
class add_node : public binaryOp_node {
  public:

  // add_node's constructor just uses node's constructor
  add_node(exp_node *L, exp_node *R);
  void print();
  float evaluate();
};


// subtract_node inherits the characteristics of node and adds its own evaluate function
class subtract_node : public binaryOp_node {
  public:

  subtract_node(exp_node *L, exp_node *R);
  void print();
  float evaluate();
};


// multiply_node inherits the characteristics of node and adds its own evaluate function
class multiply_node : public binaryOp_node {
  public:

  multiply_node(exp_node *L, exp_node *R);
  void print();
  float evaluate();
};


// divide_node inherits the characteristics of node and adds its own evaluate function
class divide_node : public binaryOp_node {
  public:

  divide_node(exp_node *L, exp_node *R);
  void print();
  float evaluate();
};

class assign_node : public stmt_node {
 protected:
  string id;
  exp_node *exp;
 public:
  assign_node(string name, exp_node *expression);
  void print();
  float evaluate();
};
class skip_node: public stmt_node {
 public:
  skip_node();
  void print();
  float evaluate();
};


class sequence_node: public stmt_node {
 protected:
  stmt_node *stmt1, *stmt2;
 public:
  sequence_node(stmt_node *mystmt1, stmt_node *mystmt2);
  void print();
  float evaluate();
};

// the object at the base of our tree
extern map<string, float> state;