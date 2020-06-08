%{

#define Trace(t)        cout << t;
#define isExist         -1

#include "st.h"
#include "lex.yy.cpp"

void yyerror(string msg);

/* Create a symboltable list */
SymbolTableS my_tables;

%}

/* defined yylval */
%union{
    int ival;
    float fval;
    bool bval;
    char cval;
    string* sval;

    ValueType type;
    ValueDetail* arg;
    vector<ValueDetail*> *args;
}

/* start from */
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
%token <sval> STRING_VAL ID

/* define type token  */
%type <type> VAL_TYPE TYPE_OPT FUNC_INVOCATION
%type <arg> FORMAL_ARG EXPR CONST_VAL
%type <args> FORMAL_ARGS COMMA_SEPARATED_EXPR

/* operater's priority */
%left OR
%left AND
%left NOT
%left GT LT GE LE EE NE
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%%

/* Program */
program:        
            /* Start with <object id_name> */
            /* Push a symboltable when entering a scope, and pop it after exiting the scope */
            OBJECT ID
            {
                my_tables.push();
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*$2, OBJECT_type);
                if (ID_idx == isExist){
                    yyerror(*$2 + ": already exists !");
                }
                Trace("OBJECT ID\n");
            } '{' PRO_BLOCK_CONTENT_BASE '}'
            {
                my_tables.dump();
                my_tables.pop();
                Trace("{ Reducing to program }\n");
            };
/* At least one method */
PRO_BLOCK_CONTENT_BASE:
            METHOD PRO_BLOCK_CONTENT;

/* Program's block contents */
PRO_BLOCK_CONTENT:
            VAR_VAL_DEC PRO_BLOCK_CONTENT
        |   METHOD PRO_BLOCK_CONTENT
        |
        ;

/* Constant or variable or array declaration */
VAR_VAL_DEC:
            CONSTANT_DEC
        |   VARIABLE_DEC
        |   ARRAY_DEC;

/* Constant declaration */
CONSTANT_DEC:  
            VAL ID '=' EXPR
            {
                Trace("VAL ID = EXPR\n");
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*$2, CONST_type, $4);
                if (ID_idx == isExist){
                    yyerror(*$2 + ": already exists !");
                }
            }
        |   VAL ID ':' VAL_TYPE '=' EXPR
            {
                if ($4 != $6->type){
                    yyerror("Error assignment: Type different !");
                } 
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*$2, CONST_type, $6);
                if (ID_idx == isExist){
                    yyerror(*$2 + ": already exists !");
                }
                Trace("VAL ID : VAL_TYPE = EXPR\n");
            };

/* Variable declaration */
VARIABLE_DEC:
            VAR ID ':' VAL_TYPE
            {
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*$2, VAR_type, $4);
                if (ID_idx == isExist){
                    yyerror(*$2 + ": already exists !");
                }
                Trace("VAR ID : VAL_TYPE\n");
            }
        |   VAR ID '=' EXPR
            {
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*$2, VAR_type, $4);
                if (ID_idx == isExist){
                    yyerror(*$2 + ": already exists !");
                }
                Trace("VAR ID = EXPR\n");
            }
        |   VAR ID ':' VAL_TYPE '=' EXPR
            {
                if ($4 != $6->type){
                    yyerror("Error assignment: Type different !");
                }
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*$2, VAR_type, $6);
                if (ID_idx == isExist){
                    yyerror(*$2 + ": already exists !");
                }
                Trace("VAR ID : VAL_TYPE = EXPR\n");
            }
        |   VAR ID
            {
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*$2, VAR_type, VAL_UNDEF_type);
                if (ID_idx == isExist){
                    yyerror(*$2 + ": already exists !");
                }
                Trace("VAR ID\n");
            };

/* Array declaration */
ARRAY_DEC:
            VAR ID ':' VAL_TYPE '[' INT_VAL ']'
            {
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*$2, ARRAY_type, $4, $6);
                if (ID_idx == isExist){
                    yyerror(*$2 + ": already exists !");
                }
                Trace("VAL ID : VAL_TYPE [ INT_VAL ]\n");
            };

/* Method declaration */
METHOD:
            DEF ID 
            {
                Trace("DEF ID ( ARGS ) <:TYPE> {METHOD}");
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*$2, FUNC_type);
                if (ID_idx == isExist){
                    yyerror(*$2 + ": already exists !");
                }
            } '(' FORMAL_ARGS ')' TYPE_OPT 
            {
                IDDetail *tmp = my_tables.lookup(*$2);

                tmp->arg_val = $5;

                if($7 != VAL_UNDEF_type){
                    tmp->returnType = $7;
                }
                my_tables.push();
            } '{' METH_BLOCK_CONTENT '}'
            {
                Trace("In Function Block\n")
                my_tables.dump();
                my_tables.pop();
            };

/* Arguments declaration */
FORMAL_ARGS:
            FORMAL_ARG
            {
                Trace("FORMAL_ARG\n");
                vector<ValueDetail*>* tmp = new vector<ValueDetail*>();
                tmp->push_back($1);
                $$ = tmp;
            }
        |   FORMAL_ARG ',' FORMAL_ARGS
            {  
                Trace("FORMAL_ARG, FORMAL_ARGS\n");
                $3->push_back($1);
                $$ = $3;
            }
        |
            {
                $$ = new vector<ValueDetail*>();
            }
        ;

/* Argument declaration */
FORMAL_ARG:
            ID ':' VAL_TYPE
            {
                Trace("ID : VAL_TYPE\n");
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*$1, VAR_type, $3);
                if (ID_idx == isExist){
                    yyerror(*$1 + ": already exists !");
                }
                ValueDetail* tmp = new ValueDetail();
                tmp->arg_name = *$1;
                cout<< tmp->arg_name<<endl;
                tmp->type = $3;

                $$ = tmp;
            };

/* Function has returntype is optional */
TYPE_OPT:
            ':' VAL_TYPE
            {
                Trace("<: VAL_TYPE>\n");
                $$ = $2;
            }
        |
            {
                $$ = VAL_UNDEF_type;
            }
        ;

/* Value type declaration */
VAL_TYPE:
            INT
            {
                $$ = INT_type;
            }
        |   FLOAT
            {
                $$ = FLOAT_type;
            }
        |   CHAR
            {
                $$ = CHAR_type;
            }
        |   STRING
            {
                $$ = STRING_type;
            }
        |   BOOLEAN
            {
                $$ = BOOL_type;
            };

/* Method's block contents */
METH_BLOCK_CONTENT: 
            VAR_VAL_DEC METH_BLOCK_CONTENT
        |   STMTS METH_BLOCK_CONTENT
        |   METH_RETURN;

/* Statements declaration */
STMTS:      STMT
        |   STMT STMTS;

/* Statement declaration */
STMT:
            STMT_SIMPLE
        |   STMT_BLOCK
        |   STMT_CONDITIONAL
        |   STMT_LOOP
        |   FUNC_INVOCATION
        ;

/* simple statement declaration */
STMT_SIMPLE:
            ID '=' EXPR
            {
                Trace("STMT(ID = EXPR)\n");
                IDDetail* tmp = new IDDetail();
                tmp = my_tables.lookup(*$1);
                
                if (tmp == NULL){
                    yyerror("This ID does not exist !\n");
                }

                if (tmp->type != VAR_type){
                    yyerror("Sorry, it can't be assgined !\n");
                }

                if (!tmp->needInit){
                    if (tmp->val->type != $3->type){
                        yyerror("Sorry, differnt type can't be assigned !\n");
                    }
                    *(tmp->val) = *$3;
                }
                else{
                    tmp->val = new ValueDetail();
                    *(tmp->val) = *$3;
                    tmp->needInit = false;
                }

            }
        |   ID '[' EXPR ']' '=' EXPR
            {
                Trace("STMT(ID [EXPR] = EXPR)\n");
                IDDetail* tmp = new IDDetail();
                tmp = my_tables.lookup(*$1);

                if (tmp == NULL){
                    yyerror("This ID does not exist !\n");
                }

                if (tmp->type != ARRAY_type){
                    yyerror("Sorry, it can't be assgined !\n");
                }

                if ($3->type != INT_type){
                    yyerror("Sorry, array size must be Integer !\n");
                }

                if (tmp->arrType != $6->type){
                    yyerror("Sorry, different type can't be assigned !\n");
                }
                *(tmp->arr_val[$3->intValue]) = *$6;
            }
        |   PRINT EXPR 
        |   PRINTLN EXPR
        |   READ ID
            {
                IDDetail* tmp = new IDDetail();
                tmp = my_tables.lookup(*$2);
                
                if (tmp == NULL){
                    yyerror("This ID does not exist !\n");
                }
            }
        |   RETURN
        |   RETURN EXPR
        |   EXPR
        |   FUNC_INVOCATION;

/* Expression declaration */
EXPR:
            '-' EXPR %prec UMINUS
            {
                Trace("-EXPR\n");
                if($2->type == INT_type){
                    $2->intValue *= -1;
                    $$ = $2;
                }
                else if($2->type == FLOAT_type){
                    $2->floatValue *= -1;
                    $$= $2;
                }
                else{
                    yyerror("Value type must be Integer & Float !\n");
                }
            }
        |   EXPR '*' EXPR
            {
                Trace("EXPR * EXPR\n");
                if($1->type != $3->type){
                    yyerror("Sorry, different type can't be caculated !\n");
                }
                if($1->type == INT_type || $1->type == FLOAT_type){
                    $$ = *$1 * *$3;
                }
                else{
                    yyerror("Value type must be Integer & Float !\n");
                }
            }
        |   EXPR '/' EXPR
            {
                Trace("EXPR / EXPR\n");
                if($1->type != $3->type){
                    yyerror("Sorry, different type can't be caculated !\n");
                }
                if($1->type == INT_type || $1->type == FLOAT_type){
                    $$ = *$1 / *$3;
                }
                else{
                    yyerror("Value type must be Integer & Float !\n");
                }
            }
        |   EXPR '+' EXPR
            {
                Trace("EXPR + EXPR\n");
                if($1->type != $3->type){
                    yyerror("Sorry, different type can't be caculated !\n");
                }
                if($1->type == INT_type || $1->type == FLOAT_type){
                    $$ = *$1 + *$3;
                }
                else{
                    yyerror("Value type must be Integer & Float !\n");
                }
            }
        |   EXPR '-' EXPR
            {
                Trace("EXPR - EXPR\n");
                if($1->type != $3->type){
                    yyerror("Sorry, different type can't be caculated !\n");
                }
                if($1->type == INT_type || $1->type == FLOAT_type){
                    $$ = *$1 - *$3;
                }
                else{
                    yyerror("Value type must be Integer & Float !\n");
                }
            }
        |   EXPR LT EXPR
            {
                Trace("EXPR < EXPR\n");
                if($1->type != $3->type){
                    yyerror("Sorry, different type can't be compared !\n");
                }
                if($1->type == INT_type || $1->type == FLOAT_type){
                    $$ = (*$1 < *$3);
                }
                else{
                    yyerror("Value type must be Integer & Float !\n");
                }
            }
        |   EXPR LE EXPR
            {
                Trace("EXPR <= EXPR\n");
                if($1->type != $3->type){
                    yyerror("Sorry, different type can't be compared !\n");
                }
                if($1->type == INT_type || $1->type == FLOAT_type){
                    $$ = (*$1 <= *$3);
                }
                else{
                    yyerror("Value type must be Integer & Float !\n");
                }
            }
        |   EXPR EE EXPR
            {
                Trace("EXPR == EXPR\n");
                if($1->type != $3->type){
                    yyerror("Sorry, different type can't be compared !\n");
                }
                if($1->type == VAL_UNDEF_type){
                    yyerror("There is an undefined type expression !\n");
                }
                $$ = (*$1 == *$3);
            }
        |   EXPR GE EXPR
            {
                Trace("EXPR >= EXPR\n");
                if($1->type != $3->type){
                    yyerror("Sorry, different type can't be compared !\n");
                }
                if($1->type == INT_type || $1->type == FLOAT_type){
                    $$ = (*$1 >= *$3);
                }
                else{
                    yyerror("Value type must be Integer & Float !\n");
                }
            }
        |   EXPR GT EXPR
            {
                Trace("EXPR > EXPR\n");
                if($1->type != $3->type){
                    yyerror("Sorry, different type can't be compared !\n");
                }
                if($1->type == INT_type || $1->type == FLOAT_type){
                    $$ = (*$1 > *$3);
                }
                else{
                    yyerror("Value type must be Integer & Float !\n");
                }
            }
        |   EXPR NE EXPR
            {
                Trace("EXPR != EXPR\n");
                if($1->type != $3->type){
                    yyerror("Sorry, different type can't be compared !\n");
                }
                if($1->type == VAL_UNDEF_type){
                    yyerror("There is an undefined type expression !\n");
                }
                $$ = (*$1 != *$3);
            }
        |   NOT EXPR
            {
                Trace("! EXPR\n");
                ValueDetail* tmp = new ValueDetail();
                tmp->type = BOOL_type;
                if ($2->type != BOOL_type){
                    if ($2->type == VAL_UNDEF_type){
                        yyerror("There is an undefined type expression !\n");
                    }
                    else{
                        tmp->boolValue = !($2->boolValue);
                    }
                }
                $$ = tmp;
            }
        |   EXPR AND EXPR
            {
                Trace("EXPR && EXPR\n");
                ValueDetail* tmp = new ValueDetail();
                tmp->type = BOOL_type;
                if($1->type != $3->type){
                    yyerror("Sorry, different type can't be compared !\n");
                }
                if($1->type != BOOL_type){
                    yyerror("Value type must be Boolean !\n");
                }
                tmp->boolValue = ($1->boolValue && $3->boolValue);
                $$ = tmp;
            }
        |   EXPR OR EXPR
            {
                Trace("EXPR || EXPR\n");
                ValueDetail* tmp = new ValueDetail();
                tmp->type = BOOL_type;
                if($1->type != $3->type){
                    yyerror("Sorry, different type can't be compared !\n");
                }
                if($1->type != BOOL_type){
                    yyerror("Value type must be Boolean !\n");
                }
                tmp->boolValue = ($1->boolValue || $3->boolValue);
                $$ = tmp;
            }
        |   '(' EXPR ')'
            {
                Trace("( EXPR )\n");
                $$ = $2;
            }
        |   CONST_VAL
            {
                Trace("EXPR(Const_value)\n");
                cout<< "---INT---"<<endl;
                $$ = $1;
            }
        |   ID
            {
                Trace("EXPR(ID)\n");
                IDDetail* tmp = my_tables.lookup(*$1);
                if (tmp == NULL){
                    yyerror("This ID does not exist !\n");
                }

                if (tmp->type != CONST_type && tmp->type != VAR_type){
                    yyerror("Can get this ID value !\n");
                }

                $$ = tmp->val;
            }
        |   FUNC_INVOCATION
            {
                Trace("FUNCTION_CALL")
                ValueDetail* tmp = new ValueDetail();
                tmp->type = $1;
                $$ = tmp;
            }
        |   ID '[' EXPR ']'
            {
                Trace("ID [EXPR]\n");
                IDDetail* tmp = my_tables.lookup(*$1);
                if (tmp == NULL){
                    yyerror("This ID does not exist !\n");
                }

                if (tmp->type != ARRAY_type){
                    yyerror("ID type must be array !\n");
                }

                if ($3->type != INT_type){
                    yyerror("Sorry, array size must be Integer !\n");
                }

                if ($3->intValue >= tmp->arrLength || $3->intValue < 0){
                    yyerror("Array size out of range !\n");
                }

                ValueDetail* arr_tmp = new ValueDetail();
                arr_tmp = tmp->arr_val[$3->intValue];
                $$ = arr_tmp;
            };

/* Constant value type declaration */
CONST_VAL:
            INT_VAL
            {
                Trace("Get Integer\n");
                $$ = INTconst($1);
            }
        |   FLOAT_VAL
            {
                Trace("Get Float\n");
                $$ = FLOATconst($1);
            }
        |   BOOL_VAL
            {
                Trace("Get Boolean\n");
                $$ = BOOLconst($1);
            }
        |   CHAR_VAL
            {
                Trace("Get Char\n");
                $$ = CHARconst($1);
            }
        |   STRING_VAL
            {
                Trace("Get String\n");
                $$ = STRINGconst($1);
            };

/* Call function */
FUNC_INVOCATION:
            ID '(' COMMA_SEPARATED_EXPR ')'
            {
                IDDetail* tmp = new IDDetail();
                tmp = my_tables.lookup(*$1);
                
                if (tmp == NULL){
                    yyerror("This ID does not exist !\n");
                }

                if (tmp->type != FUNC_type){
                    yyerror("This ID is not a function !\n");
                }

                if ($3->size() != tmp->arg_val->size()){
                    yyerror("Wrong argument size !\n");
                }

                $$ = tmp->returnType;
            };

/* Muti expression separated by comma */
COMMA_SEPARATED_EXPR:
            EXPR
            {
                vector<ValueDetail*>* tmp = new vector<ValueDetail*>();
                tmp->push_back($1);
                $$ = tmp;
            }
        |   EXPR ',' COMMA_SEPARATED_EXPR
            {
                $3->push_back($1);
                $$ = $3;
            }
        |
            {
                $$ = new vector<ValueDetail*>();
            };

/* Block_statement declaration */
STMT_BLOCK:
            '{' 
            {
                my_tables.push();
            } STMT_BLOCK_CONTENTS '}'
            {   
                Trace("Reducing Block\n");
                my_tables.dump();
                my_tables.pop();
            };

/* block_statement's contents */
STMT_BLOCK_CONTENTS:
            VAR_VAL_DEC STMT_BLOCK_CONTENTS
        |   STMTS STMT_BLOCK_CONTENTS
        |;

/* Conditional statements declaration */
STMT_CONDITIONAL:
            IF_COND
        |   IF_COND ELSE_COND;

/* Condition_if declaration */
IF_COND:
            IF '(' EXPR ')'
            {
                Trace("IF ( EXPR )\n");
                if ($3->type != BOOL_type){
                    yyerror("Conditional expression must be Boolean !\n");
                }
            } STMT_SCOPE;
/* Condition_else declaration */
ELSE_COND:
            ELSE STMT_SCOPE;

/* Statement's scope contents */
STMT_SCOPE:
            STMT_SIMPLE
        |   STMT_BLOCK;

/* Loop_statements declaration */
STMT_LOOP:
            WHILE_LOOP
        |   FOR_LOOP;

/* Loop_while delcaration */
WHILE_LOOP:
            WHILE '(' EXPR ')' 
            {
                Trace("WHILE ( EXPR )\n");
                if ($3->type != BOOL_type){
                    yyerror("Conditional expression must be Boolean !\n");
                }
            } STMT_SCOPE;

/* Loop_for declaration */
FOR_LOOP:
            FOR '(' ID LT '-' INT_VAL TO INT_VAL ')' 
            {
                Trace("FOR ( ID < - INT TO INT )\n");
                IDDetail* tmp = new IDDetail();
                tmp = my_tables.lookup(*$3);
                if(tmp->type != VAR_type){
                    yyerror("This ID must be variable type !\n");
                }
            }
            STMT_SCOPE;

/* Method's return rule declaration */
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
    
    if (argc == 1){
        /* user input */
        yyin = stdin;
    }
    else if (argc == 2) {
        /* open the source program file */
        yyin = fopen(argv[1],"r");
    }
    else {
        cout << "Command error" << endl;
    }

    /* perform parsing */
    if (yyparse() == 1)                 /* parsing */
        yyerror("Parsing error !");     /* syntax error */

    /* Dump symboltable list */
    my_tables.dump();
}
