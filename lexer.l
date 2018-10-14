%{

#include <stdlib.h>
#include <string.h>
#include "cMinus.h"
#include "y.tab.h"

    int num_val;
    char *id_val;
    char *str_val;
    int yylval;

    extern int line_num;
%}

ws     [ \t\f\n]+
DIGIT  [0-9]
LETTER [a-zA-Z]
string_literal \"(\\.|[^\\"])*\"

%%

{ws}     ;

\n			{ line_num++ }
"if"		{ return IF; }
"else"      { return ELSE; }
"("			{ return LPAR; }
")"			{ return RPAR; }
"{"			{ return LCURL; }
"}"			{ return RCURL; }
"while"		{ return WHILE; }
";"			{ return SEMI; }
","			{ return COMMA; }
"int"		{ return INT; }
"string"    { return STRING; }
"float"		{ return FLOAT; }
"char"		{ return CHAR; }
"boolean"	{ return BOOL; }
"void"		{ return VOID; }    
"return"	{ return RETURN; }
"!"         { return NOT; }
"&&"        { return AND; }
"||"        { return OR; }
"=="                {yylval.oper = EQ; return RELOP;}
">"                 {yylval.oper = GE; return RELOP;}
{DIGIT}+            { yylval.num = atof(yytext); return NUMBER;	}
{LETTER}[0-9a-zA-Z]*    { yylval.id = strdup(yytext); return ID; }
{string_literal}	{ str_val = strdup(yytext); return STRING; }

. { BEGIN(ERROR); yymore(); }
<ERROR>[^{DIGIT}{LETTER}+\-/*(){}= \t\n\f\r] { yymore(); }
<ERROR>(.|\n) { yyless(yyleng-1); printf("error token: %s on line %d\n", yytext, line_num); 
           BEGIN(INITIAL); }

%%