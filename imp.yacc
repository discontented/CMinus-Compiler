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
#include "imp.h"

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
%type <exp_node_ptr> arithmetic_expr
%type <exp_node_ptr> factor
%type <stmt_node_ptr> statement_list
%type <stmt_node_ptr> statement
%type <stmt_node_ptr> program

%%

program:
    statement_list { root = $$; }
    ;
/*
block:
    LCURL statement_list RCURL
    ;
*/
statement_list:
    statement SEMI { $$ = $1; }
    | statement SEMI statement_list { $$ = new sequence_node($3, $1);}
    ;

statement:
    expression { $$ = (stmt_node*)$1;}
    | { $$ = new skip_node(); }
    ;

expression:
    arithmetic_expr {$$ = $1;}
    ;

arithmetic_expr:
    arithmetic_expr '+' multiplicative_expr { $$ = new add_node($1, $3); }
    | arithmetic_expr '-' multiplicative_expr { $$ = new subtract_node($1, $3); }
    | multiplicative_expr { $$ = $1; }
    ;

multiplicative_expr:
    multiplicative_expr '*' factor { $$ = new multiply_node( $1, $3); }
    | multiplicative_expr '/' factor { $$ = new divide_node( $1, $3); }
    | factor   { $$ = $1; }                    
    ;

factor:
    LPAR arithmetic_expr RPAR {$$ = $2; }
    | '-'factor  {$$ = new neg_node($2); }
    | NUMBER {$$ = new number_node($1); }
    | ID  {$$ = new variable_node($1); }
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


