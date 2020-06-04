%{

#define Trace(t)        printf(t)

#include "st.hpp"
#include "lex.yy.cpp"

void yyerror(string msg);
%}

%union{
    int ival;
    float fval;
    bool bval;
    char cval;
    string* sval;
    ValueDetail* val;
    ValueType
}

%start program

/* tokens */
%token SEMICOLON
%token BOOLEAN BREAK CHAR CASE CLASS CONTINUE DEF DO ELSE EXIT FALSE FLOAT FOR IF INT
%token nULL OBJECT PRINT PRINTLN REPEAT RETURN READ STRING TO TRUE TYPE VAL VAR WHILE 

%token GT LT GE LE EE NE
%token AND OR NOT

%token <ival> INT_VAL
%token <fval> FLOAT_VAL
%token <bval> BOOL_VAL
%token <cval> CHAR_VAL
%token <sval> STRING_VAL
%token <sval> ID

%token <val> EXPR
%token <ValueType> VAL_TYPE

%left OR
%left AND
%left NOT
%left GT LT GE LE EE NE
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%%
program:        
            OBJECT ID
            {
                Trace("Reducing to program\n");
            };

CONSTANT_DEC:  
            VAL ID '=' EXPR
            {

            }
        |   VAL ID ':' VAL_TYPE '=' EXPR
            {

            };

VARIABLE_DEC:
            VAR ID ':' VAL_TYPE
            {

            }
        |   VAR ID '=' EXPR
            {

            }
        |   VAR ID ':' VAL_TYPE '=' EXPR
            {

            }
        |   VAR ID
            {

            };

ARRAY_DEC:
            VAR ID ':' VAL_TYPE '[' INT_VAL ']'



%%

void yyerror(string msg)
{
   cout << msg << endl;
}

int main(int argc, char **argv)
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
