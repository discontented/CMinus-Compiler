#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>
#include "cond-node.h"
#include "stmt-node.h"
#include "exp-node.h"

using namespace std;

class test
{
  private:
	cond_node *condition;

  public:
	test(cond_node *condition);
	void print();
	bool evaluate();
};

void output_tabs(int n);

extern map<string, float> state_float;
extern map<string, int> state_int;
extern map<string, string> state_string;