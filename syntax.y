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
#include "cMinus.h"
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
  operation oper;
  exp_node *exp_node_ptr;
  statement *st;
}

// %error-verbose

/* Bison Declarations */
%token IF WHILE ELSE
%token SEMI COMMA LPAR RPAR LCURL RCURL
%token INT STRING FLOAT CHAR CHARSTAR BOOL VOID DOUBLEQUAL NOTEQUAL LBRACK RBRACK NULLTOKEN
%token RETURN
%token AND OR NOT
%token EQUALS PLUS MINUS TIMES DIVIDE
%token PRINT
%token <num> NUMBER
%token <id> ID
%token <oper> RELOP
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
%type <exp_node_ptr> global_variable_list
%type <exp_node_ptr> parameters
%type <exp_node_ptr> arg
%type <exp_node_ptr> parameter_list
%type <st> current_state
%type <st> statement_list
%type <st> stmt
%type <st> block
%type <st> program
%type <st> global_variable
%type <st> expression_stmt
%type <st> assign_stmt
%type <st> function_list
%type <st> function
// %type <st> declarator
// %type <st> declarator_list
%type <st> while_statement
%type <st> if_statement
%type <t> variable_type
// %type <st> return_statement
%type <cond_node_ptr> boolean_expr
%type <cond_node_ptr> mul_bexpr
%type <cond_node_ptr> root_bexpr

%%

current_state: program{root = $$}

program:
    function_list { root = $1; }
    ;

function_list:
    function_list function
            { 
             $$ = new function_parameter ($1,$2);
            }
            | function_list global_variable
            {
             $$ = $$ = new function_parameter ($1,$2);
            }
            | 
            {
             $$ = new skip_stmt();
            }
    ;

function: 
       var_type ID LPARENT arguments RPARENT block 
       {
        $$ = new function_definition ($1, $2, $4, $6);
       } 
  ;

block:
             LCURLY statement_list RCURLY
             {
             $$ = $2;
             }
             ;

parameters:
        parameter_list{$$ = 1;}
        |
        {
            $$ = new skip_stmt();
        }

parameter_list:
    arg
    { $$ = $1; }
    parameter_list COMMA arg
    {
        $$ = new arg_node($1, $3)
    }
    ;

arg:
    var_type ID{
        $$ = new par_node($1, $2, $3)
    }

global_variable_list: 
         global_variable_list COMMA ID  
         {
          $$ = new var_node ($3,$1);
         }
         |
         {
          $$ = new skip_stmt();
         }         
  ;

var_type:
       CHAR
       | CHARSTAR
       | INT
       | FLOAT
       | VOID
  ;

array: 
     var_type ID LBRACK NUMBER RBRACK SEMI
     {
      $$ = new arr_var($1,$2,$4);
      }


function_declaration:
    type ID LPAR parameter_list RPAR
    ;

function_call:
    ID LPAR function_call_args RPAR
    {
        $$ = new function_call_stmt($1, $3);
    }
    ;

function_call_args:
    function_call_arg_list
    {
        $$ = $1;
    }
    |
    {
        $$ = new skip_stmt();
    }
    ;

statement_list:
            statement statement_list
            {
             $$ = new statement_list($1,$2);
            }
            | return_stmt
         {
          $$ = $1;
         }
            | 
            {
             $$ = new skip_stmt();
            } 
  ;


statement:
         assignment
         {
          $$ = $1;
         }
         |call SEMICOLON
         {
          $$=$1;
         } 
         | conditional_statement
         {
          $$ = $1;
         }
         ;

/*statement_list:
    statement_list SEMI stmt { $$ = new sequence_stmt($1, $3); }
    | statement_list SEMI error { $$ = $1; yyclearin; }
    | stmt { $$ = $1; }
    ;

stmt:
    expression_stmt { $$ = $1; }
    | PRINT expression { $$ = new print_stmt($2); }
    | if_statement { $$ = $1; }
    | while_statement { $$ = $1; }
    | assign_stmt { $$ = $1; } 
    // | return_statement { $$ = $1;}
    | LCURL statement_list RCURL { $$ = $2; }
    | { $$ = new skip_stmt(); }
    ;
/*
var_declaration:
    type declarator_list { $$ = $2; }
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

declarator:
    ID { $$ = $1; }
    | assign_expr { $$ = $1; }
    ;    
*/

if_statement:
	IF LPAR boolean_expr RPAR stmt ELSE stmt { $$ = new ife_stmt(new test($3), $5, $7); }
    ;

while_statement:
    WHILE LPAR boolean_expr RPAR stmt { $$ = new while_stmt(new test($3), $5); }
    ;


return_statement:
    RETURN factor SEMI {$$ = new return_stmt($2);}
    
    ;


/*expression_stmt: 
    expression {$$ = new expression_stmt($1); }
    ;*/
    
expression:
    logical_or_expr {$$ = $1;}
    ;

logical_or_expr:
              logical_and_expr
              {
               $$ = $1;
              }
                | logical_or_expr OR logical_and_expr 
              {
                   $$ = new logical_or ($1,$3);
              }
     ;

logical_and_expr:
               equality_expr
               {
                $$ = $1;
               }
                 | logical_and_expr AND equality_expr 
               {
                  $$ = new logical_and ($1,$3);
               }
     ;

equality_expr:
            relational_expr
            {
             $$ = $1;
            }
              | equality_expr DOUBLEEQUAL relational_expr 
            {
             $$ = new logical_equal($1,$3);
                }
              | equality_expr NOTEQUAL relational_expr 
            {
             $$ = new logical_notequal($1,$3);
            }
    ;

relational_expr:
              arithmetic_expr
              {
               $$ = $1;
              }
                | relational_expr LESSTHAN arithmetic_expr 
              {
               $$ = new logical_less_than($1,$3);
                }
                | relational_expr GREATERTHAN arithmetic_expr 
              {
                   $$ = new logical_greater_than($1,$3);
                }
              | relational_expr LESSEQUAL arithmetic_expr 
              {
                   $$ = new logical_lessequal($1,$3);
              }
                | relational_expr GREATEQUAL arithmetic_expr 
              {
                   $$ = new logical_greatequal($1,$3);
                }
  ;

assign_stmt:
    global_variable
           {
           $$ = $1;
           }
           |
           array
           {
           $$ = $1;
            }
           |
           var_type ID EQUAL factor SEMI
           {
               $$ = new assignment_stmt ($1,$2,$4);          
               }
           | 
           expression SEM
           {
            $$ = $1;
           }
           | 
           ID EQUAL expression SEM
           {
           $$ = new assignment_stmt ($1,$3);
           }       
    ;

arithmetic_expr:
    arithmetic_expr PLUS multiplicative_expr { $$ = new plus_expression($1, $3); }
    | arithmetic_expr MINUS multiplicative_expr { $$ = new minus_expression($1, $3); }
    | multiplicative_expr { $$ = $1; }
    ;

multiplicative_expr:
    multiplicative_expr TIMES factor { $$ = new times_node( $1, $3); }
    | multiplicative_expr DIVIDE factor { $$ = new divide_node( $1, $3); }
    | factor { $$ = $1; }                    
    ;

factor:
    LPAR arithmetic_expr RPAR {$$ = $2; }
    | MINUS factor  {$$ = new unary_minus_node($2); }
    | NUMBER {$$ = new number_node($1); }
    | ID  {$$ = new id_node($1); }
    | ID LSQUBRACKT NUMBER RSQUBRACKT
            {
             $$ = new arr_var($1,$3);
            }
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
    NOT root_bexpr { $$ = new neg_cond_node($2); }
    | LPAR boolean_expr RPAR { $$ = $2; }
    | arithmetic_expr RELOP arithmetic_expr { $$ = new prim_cond_node($2, $1, $3); }
    ;

%%
int main(int argc, char **argv)
{ 
  if (argc>1) yyin=fopen(argv[1],"r");

   yydebug = 1;
  yyparse();

  cout << "---------- list of input program------------" << endl << endl;

  root -> print(0); cout<< endl;

  cout << "---------- exeuction of input program------------" << endl << endl;

  root->evaluate();
}

void yyerror(const char * s)
{
  fprintf(stderr, "line %d: %s\n", line_num, s);
}

