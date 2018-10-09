%{
// C requires that functions be declared before they are used and the following functions are used by the parser.
int yylex(void);
void yyerror(char const *);

// Function prototypes go here or must be included as external header.
%}

/* Bison Declarations */
%token IF WHILE
%token SEMI COMMA LPAR RPAR LCURL RCURL
%token INT STRING FLOAT CHAR BOOL VOID
%token RETURN
%token ID NUM
%left '-' '+'
%left '*' '/'

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
    statement SEMI
    | statement SEMI statement_list
    ;

statement:
    expression
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
    WHILE LPAR expression RPAR block
    ;

return_statement:
    RETURN expression
    | RETURN
    ;

expression:
    arithmetic_expr
    | boolean_expr
    | function_call
    | assign_expr
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
    | '%'
    ;

arithmetic_expr:
    arithmetic_expr addop multiplicative_expr
    | multiplicative_expr
    ;

multiplicative_expr:
    multiplicative_expr multop factor
    | factor                      
    ;

factor:
    LPAR arithmetic_expr RPAR
    | variable
    | '-'factor
    | NUM
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

variable:
    ID
    ;

%%



