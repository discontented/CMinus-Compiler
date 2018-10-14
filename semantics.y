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
 statement *root;

// for keeping track of line numbers in the program we are parsing
  int line_num = 1;

// function prototypes, we need the yylex return prototype so C++ won't complain
int yylex();
void yyerror(const char* s);
%}

%start program

%union {
  float num;
  char *id;
  operation oper;
  exp_node *exp_node_ptr;
  cond_node *cond_node_ptr;
  statement *st;
}

/* Bison Declarations */
%token IF WHILE ELSE
%token SEMI COMMA LPAR RPAR LCURL RCURL
%token INT STRING FLOAT CHAR BOOL VOID
%token RETURN
%token AND OR NOT
%token <num> NUMBER
%token <var_name> ID
%token <oper> RELOP
%type <exp_node_ptr> expression
%type <exp_node_ptr> multiplicative_expr
%type <exp_node_ptr> arithmetic_expr
%type <exp_node_ptr> assign_expr
// %type <exp_node_ptr> function_call
%type <exp_node_ptr> factor
%type <st> statement_list
%type <st> statement
%type <st> program
%type <st> declarator
// %type <st> declarator_list
%type <st> while_statement
%type <st> if_statement
// %type <st> return_statement
%type <cond_node_ptr> boolean_expr
%type <cond_node_ptr> mul_bexpr
%type <cond_node_ptr> root_bexpr

%%

program:
    statement_list { root = $$; }
    ;
/*
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
    ID LPAR parameter_list RPAR {;}
    ;
*/

statement_list:
    statement_list SEMI statement { $$ = new sequence_node($1, $3); }
    | statement_list SEMI error { $$ = $1; yyclearin; }
    | statement { $$ = $1; }
    ;

statement:
    expression { $$ = $1;}
    | declarator { $$ = $1;}
    | if_statement { $$ = $1;}
    | while_statement { $$ = $1;}
    // | return_statement { $$ = $1;}
    | LCURL statement RCURL { $$ = $2; }
    | { $$ = new skip_stmt(); }
    ;
/*
var_declaration:
    type declarator_list { $$ = $2 }
    ;

type:
    primitive_type { $$ = $1; }
    ;

primitive_type:
    numeric_type { $$ = $1; }
    ;

numeric_type:
    INT NUMBER { $$ = $2; }
    | FLOAT NUMBER { $$ = $2; }
    ;

declarator_list:
    declarator
    | declarator COMMA declarator_list
    ;
*/
declarator:
    ID { $$ = $1; }
    | assign_expr { $$ = $1; }
    ;    

if_statement:
    IF LPAR expression RPAR statement ELSE statement { $$ = new ife_stmt(new test($3), $5, $7); }
    ;

while_statement:
    WHILE LPAR expression RPAR statement { $$ = new while_stmt(new test($3), $5); }
    ;
/*
return_statement:
    //RETURN expression {$$ = returnStatement($2);}
    | RETURN
    ;
*/
expression:
    arithmetic_expr {$$ = $1;}
    | boolean_expr {$$ = $1;}
    | assign_expr {$$ = $1;}
    ;

assign_expr:
    ID '=' expression {$$ = new assignment_stmt($1, $3);}
    ;

arithmetic_expr:
    arithmetic_expr '+' multiplicative_expr { $$ = new plus_node($1, $3); }
    | arithmetic_expr '-' multiplicative_expr { $$ = new minus_node($1, $3); }
    | multiplicative_expr { $$ = $1; }
    ;

multiplicative_expr:
    multiplicative_expr '*' factor { $$ = new times_node( $1, $3); }
    | multiplicative_expr '/' factor { $$ = new divide_node( $1, $3); }
    | factor   { $$ = $1 }                    
    ;

factor:
    LPAR arithmetic_expr RPAR {$$ = $2; }
    | '-'factor  {$$ = new unary_minus_node($2); }
    | NUMBER {$$ = new number_node($1); }
    | ID  {$$ = new id_node($1); }
    ;

boolean_expr:
    boolean_expr OR mul_bexpr { $$ = new or_cond_node($1, $3); }
    | mul_bexpr { $$ = $1; }
    ;

mul_bexpr:
    mul_bexpr AND root_bexpr { $$ = new and_cond_node($1, $3); }
    | root_bexpr { $$ = $1; }
    ;

root_bexpr:
    '!'root_bexpr { $$ = new neg_cond_node($2); }
    | arithmetic_expr RELOP arithmetic_expr { $$ = new prim_cond_node($2, $1, $3); }
    ;

%%
int main(int argc, char **argv)
{ 
  if (argc>1) yyin=fopen(argv[1],"r");

  //  yydebug = 1;
  yyparse();

  cout << "---------- list of input program------------" << endl << endl;

  root -> labelling(1);

  root -> print(0); cout<< endl;

  cout << "---------- exeuction of input program------------" << endl << endl;
  

  root->evaluate();
}

void yyerror(char * s)
{
  fprintf(stderr, "line %d: %s\n", line_num, s);
}

