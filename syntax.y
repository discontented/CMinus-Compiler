%{
// C requires that functions be declared before they are used and the following functions are used by the parser.
int yylex();
void yyerror(const char * s);

// Function prototypes go here or must be included as external header.

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <list>
#include "myc.h"
#include "y.tab.h"
#define YYDEBUG 1

using namespace std;

extern FILE *yyin;

// the root of the abstract syntax tree
statement *root;

// for keeping track of line numbers in the program we are parsing
int line_num = 1;

%}

%start current_state

%union {
  float num;
  char *id;
  exp_node *exp_node_ptr;
  statement *st;
  int t;
}

// %error-verbose

/* Bison Declarations */
// Structurs
%token IF WHILE ELSE
// Symbols
%token SEMI COMMA LPAR RPAR LCURL RCURL
%token LBRACK RBRACK NULLTOKEN
// Types
%token<t> INT STRING FLOAT CHAR BOOL VOID
// Operators
%token GREATERTHAN GREATEQUAL LESSTHAN LESSEQUAL
%token EQUAL DOUBLEQUAL NOTEQUAL
%token AND OR NOT
%token EQUALS PLUS MINUS TIMES DIVIDE
// Special functions
%token RETURN
%token PRINT

%token <num> NUMBER
%token <id> ID
%type <exp_node_ptr> expression
%type <exp_node_ptr> multiplicative_expr
%type <exp_node_ptr> arithmetic_expr
%type <exp_node_ptr> logical_or_expr
%type <exp_node_ptr> logical_and_expr
%type <exp_node_ptr> equality_expr
%type <exp_node_ptr> relational_expr
%type <exp_node_ptr> array
%type <exp_node_ptr> function_call
%type <exp_node_ptr> function_call_arg_list
%type <exp_node_ptr> function_call_args
%type <exp_node_ptr> factor
// %type <exp_node_ptr> global_variable_list
%type <exp_node_ptr> parameters
%type <exp_node_ptr> parameter_list
%type <exp_node_ptr> arg
%type <st> current_state
%type <st> statement_list
%type <st> statement
%type <st> block
%type <st> program
%type <st> global_variable
%type <st> expression_stmt
%type <st> assign_stmt
%type <st> return_statement
%type <st> function_list
%type <st> function
// %type <st> declarator
// %type <st> declarator_list
%type <st> while_statement
%type <st> if_statement
%type <st> conditional_statement

%type <t> var_type
// %type <st> return_statement
// %type <cond_node_ptr> boolean_expr
// %type <cond_node_ptr> mul_bexpr
// %type <cond_node_ptr> root_bexpr

%%

current_state:
    program {root = $$; }
    ;

program:
    function_list { root = $1; }
    ;

function_list:
    function_list function { $$ = new function_parameter ($1,$2); }
    | function_list global_variable { $$ = new function_parameter ($1,$2); }
    | { $$ = new skip_stmt(); }
    ;

function: 
    var_type ID LPAR parameters RPAR block { $$ = new function_definition ($1, $2, $4, $6); } 
    ;

block:
    LCURL statement_list RCURL { $$ = $2; }
    ;

parameters:
    parameter_list {$$ = $1;}
    | { $$ = new skip_exp(); }
    ;

parameter_list:
    arg { $$ = $1; }
    | parameter_list COMMA arg { $$ = new arg_node($1, $3); }
    ;

arg:
    var_type ID { $$ = new param_node($1, $2); }
    ;

function_call:
    ID LPAR function_call_args RPAR { $$ = new call_stmt($1, $3); }
    ;

/* Used to allow for empty function arg on functions without arguments*/
function_call_args:
    function_call_arg_list { $$ = $1; }
    | { $$ = new skip_exp(); }
    ;

function_call_arg_list:
    expression { $$ = $1; }
    | function_call_arg_list COMMA expression { $$ = new call_list($1, $3); }
    ;

global_variable:
    var_type ID SEMI { $$ = new var_node($1, $2); }
    ;

array: 
    var_type ID LBRACK NUMBER RBRACK SEMI { $$ = new arr_var($1,$2,$4); }
    ;

var_type:
    CHAR 
    | STRING
    | INT
    | FLOAT
    | VOID 
    ;

statement:
    assign_stmt { $$ = $1; }
    // | PRINT expression { $$ = new print_stmt($2); }
    | expression_stmt { $$ = $1; }
    | conditional_statement { $$ = $1; }
    | return_statement { $$ = $1; };
    ;

statement_list:
    statement_list SEMI statement { $$ = new statement_list($1, $3); }
    | statement_list SEMI error { $$ = $1; yyclearin; }
    | statement { $$ = $1; }
    ;

conditional_statement:
    if_statement { $$ = $1; }
    | while_statement { $$ = $1; }
    ;

if_statement:
	IF LPAR expression RPAR block { $$ = new if_then_stmt($3, $5); }
    | IF LPAR expression RPAR block ELSE block { $$ = new if_then_else_stmt($3, $5, $7); }
    ;

while_statement:
    WHILE LPAR expression RPAR block { $$ = new while_stmt($3, $5); }
    ;

return_statement:
    RETURN factor SEMI {$$ = new return_stmt($2);}
    ;
    
expression_stmt:
    expression { $$ = new expression_stmt($1); }
    ;

expression:
    logical_or_expr {$$ = $1;}
    | function_call SEMI { $$ = $1; }
    | array { $$ = $1; }
    ;

logical_or_expr:
    logical_and_expr { $$ = $1; }
    | logical_or_expr OR logical_and_expr { $$ = new logical_oror($1,$3); }
    ;

logical_and_expr:
    equality_expr { $$ = $1; }
    | logical_and_expr AND equality_expr { $$ = new logical_andand($1,$3); }
    ;

equality_expr:
    relational_expr { $$ = $1; }
    | equality_expr DOUBLEQUAL relational_expr { $$ = new logical_equalequal($1,$3); }
    | equality_expr NOTEQUAL relational_expr { $$ = new logical_notequal($1,$3); }
    ;

relational_expr:
    arithmetic_expr { $$ = $1; }
    | relational_expr LESSTHAN arithmetic_expr { $$ = new logical_less($1,$3); }
    | relational_expr GREATERTHAN arithmetic_expr { $$ = new logical_great($1,$3); }
    | relational_expr LESSEQUAL arithmetic_expr { $$ = new logical_lessequal($1,$3); }
    | relational_expr GREATEQUAL arithmetic_expr { $$ = new logical_greatequal($1,$3); }
    ;

assign_stmt:
    var_type ID EQUALS factor SEMI { $$ = new assignment_stmt ($1,$2,$4); }
    | ID EQUALS expression SEMI  { $$ = new assignment_stmt ($1,$3); }       
    ;

arithmetic_expr:
    arithmetic_expr PLUS multiplicative_expr { $$ = new plus_expression($1, $3); }
    | arithmetic_expr MINUS multiplicative_expr { $$ = new minus_expression($1, $3); }
    | multiplicative_expr { $$ = $1; }
    ;

multiplicative_expr:
    multiplicative_expr TIMES factor { $$ = new times_expression( $1, $3); }
    | multiplicative_expr DIVIDE factor { $$ = new divide_expression( $1, $3); }
    | factor { $$ = $1; }                    
    ;

factor:
    LPAR expression RPAR {$$ = $2; }
    // | MINUS factor  {$$ = new unary_minus_node($2); }
    | NUMBER {$$ = new number_node($1); }
    | ID  {$$ = new id_node($1); }
    | ID LBRACK NUMBER RBRACK { $$ = new arr_var($1,$3); }
    ;
/*
boolean_expr:
    boolean_expr OR mul_bexpr { $$ = new or_cond_node($1, $3); }
    | mul_bexpr { $$ = $1; }
    ;

mul_bexpr:
    mul_bexpr AND root_bexpr { $$ = new and_cond_node($1, $3); }
    | root_bexpr { $$ = $1; }
    ;

root_bexpr:
    NOT root_bexpr { $$ = new neg_cond_node($2); }
    | LPAR boolean_expr RPAR { $$ = $2; }
    | arithmetic_expr RELOP arithmetic_expr { $$ = new prim_cond_node($2, $1, $3); }
    ;
*/
%%
int main(int argc, char **argv)
{ 
  if (argc>1) yyin=fopen(argv[1],"r");

   yydebug = 1;
  yyparse();

  cout << "---------- list of input program------------" << endl << endl;

  root -> print(); cout<< endl;

  cout << "---------- exeuction of input program------------" << endl << endl;

  root->evaluate();
}

void yyerror(const char * s)
{
  fprintf(stderr, "line %d: %s\n", line_num, s);
}

