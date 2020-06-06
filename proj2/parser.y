%{

#define Trace(t)        printf(t)

#include "st.hpp"
#include "lex.yy.cpp"

void yyerror(string msg);

SymbolTableS my_tables;
%}

%union{
    int ival;
    float fval;
    bool bval;
    char cval;
    string* sval;
    ValueDetail* val;
    ValueType type;
}

%start program

/* tokens */
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

%type <val> EXPR CONST_VAL
%type <type> VAL_TYPE

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
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*$2, OBJECT_type);
                if (ID_idx == -1){
                    yyerror(*$2 + ": already exists !");
                }
            } '{' PRO_BLOCK_CONTENT '}'
            {
                Trace("Reducing to program\n");
                my_tables.dump();
                my_tables.pop();
            };
PRO_BLOCK_CONTENT:
            VAR_VAL_DEC PRO_BLOCK_CONTENT
        |   METHOD PRO_BLOCK_CONTENT
        |
        ;

VAR_VAL_DEC:
            CONSTANT_DEC
        |   VARIABLE_DEC
        |   ARRAY_DEC;

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
            {

            };

METHOD:
            DEF ID '(' FORMAL_ARGS ')' TYPE_OPT
            {

            } '{' METH_BLOCK_CONTENT '}'
            {

            };

FORMAL_ARGS:
            FORMAL_ARG
            {

            }
        |   FORMAL_ARG ',' FORMAL_ARGS
            {

            }
        |
        ;

FORMAL_ARG:
            ID ':' VAL_TYPE
            {

            };

TYPE_OPT:
            ':' VAL_TYPE
            {

            }
        |
        ;

VAL_TYPE:
            INT
        |   FLOAT
        |   CHAR
        |   STRING
        |   BOOLEAN;

METH_BLOCK_CONTENT: 
            VAR_VAL_DEC METH_BLOCK_CONTENT
        |   STMTS METH_BLOCK_CONTENT
        |   METH_RETURN;

STMTS:
            STMT_SIMPLE
        |   STMT_BLOCK
        |   STMT_CONDITIONAL
        |   STMT_LOOP
        |   FUNC_INVOCATION
        ;

STMT_SIMPLE:
            ID '=' EXPR
        |   ID '[' EXPR ']' '=' EXPR
        |   PRINT '(' EXPR ')'
        |   PRINTLN '(' EXPR ')'
        |   READ ID
        |   RETURN
        |   RETURN EXPR;
        |   EXPR
        |   FUNC_INVOCATION

EXPR:
            '-' EXPR %prec UMINUS
        |   EXPR '*' EXPR
        |   EXPR '/' EXPR
        |   EXPR '+' EXPR
        |   EXPR '-' EXPR
        |   EXPR LT EXPR
        |   EXPR LE EXPR
        |   EXPR EE EXPR
        |   EXPR GE EXPR
        |   EXPR GT EXPR
        |   EXPR NE EXPR
        |   NOT EXPR
        |   EXPR AND EXPR
        |   EXPR OR EXPR
        |   CONST_VAL
        |   ID
        |   FUNC_INVOCATION
        |   ID '[' EXPR ']';

CONST_VAL:
            INT_VAL
        |   FLOAT_VAL
        |   BOOL_VAL
        |   CHAR_VAL
        |   STRING_VAL;

FUNC_INVOCATION:
            ID '(' COMMA_SEPARATED_EXPR ')';

COMMA_SEPARATED_EXPR:
            EXPR
        |   EXPR ',' COMMA_SEPARATED_EXPR
        |
        ;

STMT_BLOCK:
            '{' VAR_VAL_DEC STMTS '}';

STMT_CONDITIONAL:
            IF_COND
        |   IF_COND ELSE_COND;

IF_COND:
            IF '(' EXPR ')' STMT_SIMPLE
        |
            IF '(' EXPR ')' STMT_BLOCK;

ELSE_COND:
            ELSE STMT_SIMPLE
        |   ELSE STMT_BLOCK;

STMT_LOOP:
            WHILE_LOOP
        |   FOR_LOOP;

WHILE_LOOP:
            WHILE '(' EXPR ')' STMT_SIMPLE
        |   WHILE '(' EXPR ')' STMT_BLOCK;

FOR_LOOP:
            FOR '(' ID LT '-' INT_VAL TO INT_VAL ')' STMT_SIMPLE
        |   FOR '(' ID LT '-' INT_VAL TO INT_VAL ')' STMT_BLOCK;

METH_RETURN:
            RETURN
        |   RETURN EXPR
        |
        ;




%%

void yyerror(string msg)
{
   cout << msg << endl;
}

int main(int argc, char **argv)
{
    /* open the source program file */
    if (argc == 1){
        yyin = stdin;
    }
    else if (argc == 2) {
        yyin = fopen(argv[1],"r");
    }
    else {
        cout << "Command error" << endl;
    }

    /* perform parsing */
    if (yyparse() == 1)                 /* parsing */
        yyerror("Parsing error !");     /* syntax error */


}
