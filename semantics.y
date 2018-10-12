%{
// C requires that functions be declared before they are used and the following functions are used by the parser.
int yylex(void);
void yyerror(char const *);

// Function prototypes go here or must be included as external header.

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <list>
#include "cMinus.h"


using namespace std;

 extern FILE *yyin;

// the root of the abstract syntax tree
 stmt_node *root;

// for keeping track of line numbers in the program we are parsing
  int line_num = 1;

// function prototypes, we need the yylex return prototype so C++ won't complain
int yylex();
void yyerror(const char* s);
%}

%start program

%union {
  float number;
  char * var_name;
  exp_node *exp_node_ptr;
  stmt_node *stmt_node_ptr;
}

/* Bison Declarations */
%token IF WHILE
%token SEMI COMMA LPAR RPAR LCURL RCURL
%token INT STRING FLOAT CHAR BOOL VOID
%token RETURN
%token <number> NUMBER
%token <var_name> ID
%type <exp_node_ptr> expression
%type <exp_node_ptr> multiplicative_expr
%type <exp_node_ptr> factor
%type <stmt_node_ptr> statement_list
%type <stmt_node_ptr> statement
%type <stmt_node_ptr> program

%%

program:
    block { root = $$; }
    ;

function:
    function_declaration
    | function_declaration block
    ;

parameter_list:
    expression
    | parameter_list COMMA expression
    ;

function_declaration:
    type ID LPAR parameter_list RPAR
    ;

function_call:
    ID LPAR parameter_list RPAR
    ;

block:
    LCURL statement_list RCURL
    ;

statement_list:
    statement SEMI { $$ = $1; }
    | statement SEMI statement_list { $$ new sequence_node($3, $1);}
    ;

statement:
    expression { $$ = $1;}
    | var_declaration
    | function
    | if_statement
    | while_statement
    | return_statement
    | %empty
    ;

var_declaration:
    type declarator_list
    ;

type:
    primitive_type
    ;

primitive_type:
    numeric_type
    | boolean_type
    | string_type
    ;

numeric_type:
    INT NUM
    | FLOAT NUM
    ;

declarator_list:
    declarator
    | declarator COMMA declarator_list
    ;

declarator:
    ID
    | assign_expr
    ;    

if_statement:
    IF LPAR expression RPAR block  {$$ = ifElseStatement($3, $5)}
    ;

while_statement:
    WHILE LPAR expression RPAR block {$$ = whileStatement($3, $5)}
    ;

return_statement:
    RETURN expression {$$ = returnStatement($2);}
    | RETURN
    ;

expression:
    arithmetic_expr {$$ = $1;}
    | boolean_expr {$$ = $1;}
    | function_call {$$ = $1;}
    | assign_expr {$$ = $1;}
    ;

assign_expr:
    lhs '=' expression
    ;

lhs:
    ID
    ;

addop:
    '+' 
    | '-'
    ;

relop:
    "<"
    | "<="
    | "=="
    | ">="
    | ">"
    ;

multop:
    '*'
    | '/'
    ;

arithmetic_expr:
    arithmetic_expr '+' multiplicative_expr { $$ = new add_node($1, $3); }
    | arithmetic_expr '-' multiplicative_expr { $$ = new subtract_node($1, $3); }
    | multiplicative_expr { $$ = $1; }
    ;

multiplicative_expr:
    multiplicative_expr '*' factor { $$ = new multiply_node( $1, $3); }
    | multiplicative_expr '/' factor { $$ = new divide_node( $1, $3); }
    | factor   { $$ = $1}                    
    ;

factor:
    LPAR arithmetic_expr RPAR {$$ = $2; }
    | '-'factor  {$$ = new neg_node($2); }
    | NUM {$$ = new number_node($1); }
    | ID  {$$ = new variable_node($1); }
    ;

boolean_expr:
    boolean_expr "||" mul_bexpr
    | mul_bexpr
    ;

mul_bexpr:
    mul_bexpr "&&" root_bexpr
    | root_bexpr
    ;

root_bexpr:
    '!'root_bexpr
    | arithmetic_expr relop arithmetic_expr
    ;

%%
int main(int argc, char **argv)
{ 
  if (argc>1) yyin=fopen(argv[1],"r");

  //  yydebug = 1;
  yyparse();

  cout << "---------- list of input program------------" << endl << endl;

  root -> print();

  cout << "---------- exeuction of input program------------" << endl << endl;
  

  root->evaluate();
}


