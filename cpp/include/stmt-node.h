
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