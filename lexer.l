%{

    #include <string.h>

    int num_val;
    char *id_val;
    typedef enum {IF, LPAR, RPAR, COMMA, SEMI, NUM, ID, VOID, RETURN, INT, CHAR, BOOL, STRING, LCURL, RCURL, WHILE} tk_type;
%}

ws     [ \t\n]+
digit  [0-9]
letter [a-zA-Z]
number {digit}+
identifier     {letter}({letter}|{digit})*

%%

{ws}     ;
if    {return IF;}
"("     {return LPAR;}
")"     {return RPAR;}
"{"     {return LCURL;}
"}"     {return RCURL;}
"while" {return WHILE;}
";"     {return SEMI;}
","     {return COMMA;}
"int"   {return INT;}
"char"  {return CHAR;}
"bool"  {return BOOL;}
"void"  {return VOID;}    
"return" {return RETURN;}
{number}    {num_val = atoi(yytext); return NUM;} 
{identifier}    {id_val = strdup(yytext);  return ID;}

%%

/* From Flex/scanner.l */
int main(int argc, char **argv){
    int token;

    printf("Line 45\n");
    if (argc>1) 
    { 
        yyin=fopen(argv[1],"r");
        printf("File:\n");
    }
    while ( (token=yylex()) > 1 ) {
        printf("Line 52\n");
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