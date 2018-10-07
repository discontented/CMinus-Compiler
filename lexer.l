%{

    #include <stdlib.h>
    #include <string.h>

    int num_val;
    char *id_val;
    char *str_val;
    typedef enum {IF=300, LPAR, RPAR, COMMA, SEMI, NUM, ID, VOID, RETURN, INT, FLOAT, CHAR, BOOL, STRING, LCURL, RCURL, WHILE,} tk_type;
    int yylval;
%}

ws     [ \t\n]+
digit  [0-9]
letter [a-zA-Z]
number {digit}+
identifier     {letter}({letter}|{digit})*
string_literal L?\"(\\.|[^\\"])*\"

%%

{ws}     ;
if      { return IF; }
"("     { return LPAR; }
")"     { return RPAR; }
"{"     { return LCURL; }
"}"     { return RCURL; }
"while" { return WHILE; }
";"     { return SEMI; }
","     { return COMMA; }
"int"   { return INT; }
"string" {return STRING; }
"float" { return FLOAT; }
"char"  { return CHAR; }
"boolean"  { return BOOL; }
"void"  { return VOID; }    
"return" { return RETURN; }
{number}    {num_val = atof(yytext); return NUM;} 
{identifier}    {id_val = strdup(yytext);  return ID;}
{string_literal}    { str_val = strdup(yytext); return STRING; }

%%

/* From Flex/scanner.l */
int main(int argc, char **argv){
    int token;


    if (argc>1) 
    { 
        yyin=fopen(argv[1],"r");
    }
    while ( (token=yylex()) > 1 ) {
        printf("%d", token);
        if (token == NUM) {
            printf("(%d)", num_val);
        } else if (token==ID) {
            printf("(%s)", id_val);
        }
        printf("\n"); 
        }
    return 0;

}

int yywrap()
{ return 1;
}