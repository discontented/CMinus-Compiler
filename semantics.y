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
%token ID NUM STRING
%left '-' '+'
%left '*' '/'

%%

program:
    function
    | program function
    ;

function:
    function_declaration
    | function_declaration block
    ;

function_declaration:
    type ID LPAR paramater_list RPAR
    ;

function_call:
    ID LPAR paramater_list RPAR
    ;

paramater_list:
    parameter
    | parameter paramater_list
    ;

block:
    LCURL statement_list RCURL
    ;

statement_list:
    statement
    | statement statement_list
    ;

statement:
    expression SEMI
    | if_statement
    | while_statement
    | var_declaration SEMI
    | assign_statement SEMI
    | %empty
    ;

var_declaration:
    type declarator_list
    ;

declarator_list:
    declarator
    | declarator declarator_list
    ;

if_statement:
    IF LPAR expression RPAR block
    ;

while_statement:
    WHILE LPAR expression RPAR block
    ;

expression:
    arithmetic_expr
    | boolean_expr
    | string_expr
    | function_call
    ;

arithmetic_expr:
    expression '+' multiplicative_expr
    | expression '-' multiplicative_expr
    | multiplicative_expr
    ;

multiplicative_expr:
    multiplicative_expr '*' root_expr   {$$ = $1 * $2}
    | multiplicative_expr '/' root_expr {$$ = $1 / $2}
    | root_expr                         {$$ = $1}
    ;

root_expr:
    LPAR expression RPAR    {$$ = $1}
    | NUM                   {$$ = $1}
    ;

boolean_expr:
    boolean_expr '||' mul_bexpr
    | mul_bexpr
    ;

mul_bexpr:
    mul_bexpr '&&' root_bexpr
    | expression '>=' expression
    | expression '<=' expression
    | expression '==' expression

%%



