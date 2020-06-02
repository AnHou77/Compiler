%{

#define Trace(t)        printf(t)

#include "st.hpp"

%}

%union{
    int ival;
    float fval;
    bool bval;
    char cval;
    char* sval;
}


%start program

/* tokens */
%token SEMICOLON
%token identifier
%token BOOLEAN BREAK CHAR CASE CLASS CONTINUE DEF DO ELSE EXIT FALSE FLOAT FOR IF INT
%token NULL OBJECT PRINT PRINTLN REPEAT RETURN READ STRING TO TRUE TYPE VAL VAR WHILE 

%token <ival> INT_VAL
%token <fval> FLOAT_VAL
%token <bval> BOOL_VAL
%token <cval> CHAR_VAL
%token <sval> STRING_VAL
%token <sval> ID

%left "||"

%%
program:        identifier semi
                {
                Trace("Reducing to program\n");
                }
                ;

semi:           SEMICOLON
                {
                Trace("Reducing to semi\n");
                }
                ;
%%
#include "lex.yy.rc"

yyerror(msg)
char *msg;
{
    fprintf(stderr, "%s\n", msg);
}

main()
{
    /* open the source program file */
    if (argc != 2) {
        printf ("Usage: sc filename\n");
        exit(1);
    }
    yyin = fopen(argv[1], "r");         /* open input file */

    /* perform parsing */
    if (yyparse() == 1)                 /* parsing */
        yyerror("Parsing error !");     /* syntax error */
}
