%{

#include <stdlib.h>
#include <string.h>
#include "cMinus.h"
#include "y.tab.h"

    int num_val;
    char *id_val;
    char *str_val;

    extern int line_num;
%}

%option noyywrap
ws     [ \t\f]+
DIGIT  [0-9]
LETTER [a-zA-Z]
string_literal \"(\\.|[^\\"])*\"

%x ERROR

%%

{ws}     ;
\n			{ line_num++; }
"if"		{ return IF; }
"else"      { return ELSE; }
"while"		{ return WHILE; }
"int"		{ return INT; }
"string"    { return STRING; }
"float"		{ return FLOAT; }
"char"		{ return CHAR; }
"boolean"	{ return BOOL; }
"void"		{ return VOID; }    
"return"	{ return RETURN; }
"print"     { return PRINT; }
"("			{ return LPAR; }
")"			{ return RPAR; }
"{"			{ return LCURL; }
"}"			{ return RCURL; }
";"			{ return SEMI; }
","			{ return COMMA; }
"-"         { return MINUS; }
"+"         { return PLUS; }
"*"         { return TIMES; }
"/"         { return DIVIDE; }
"="         { return EQUALS; }
"!"         { return NOT; }
"&&"        { return AND; }
"||"        { return OR; }
"=="                {yylval.oper = EQ; return RELOP;}
">"                 {yylval.oper = GT; return RELOP;}
">="                {yylval.oper = GE; return RELOP;}
"<"                 {yylval.oper = LT; return RELOP;}
"<="                {yylval.oper = LE; return RELOP;}
"!="                {yylval.oper = NO; return RELOP;}
{DIGIT}+            { yylval.num = atof(yytext); return NUMBER;	}
{LETTER}[0-9a-zA-Z]*    { yylval.id = strdup(yytext); return ID; }
{string_literal}	{ str_val = strdup(yytext); return STRING; }


. { BEGIN(ERROR); yymore(); }
<ERROR>[^{DIGIT}{LETTER}+\-/*(){}= \t\n\f\r] { yymore(); }
<ERROR>(.|\n) { yyless(yyleng-1); printf("error token: %s on line %d\n", yytext, line_num); 
           BEGIN(INITIAL); }

%%