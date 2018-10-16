#include "../include/cMinus.h"

using namespace std;

map<string, float> state_float;
map<string, int> state_int;
map<string, string> state_string;

// preconditon: n>=0
void output_tabs(int n)
{
	while (n > 0)
	{
		cout << "\t";
		n--;
	}
}

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

