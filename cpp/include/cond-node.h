
enum operation
{
	EQ,
	GT,
    GE,
    LT,
    LE,
    NO
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
