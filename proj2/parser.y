%{

#define Trace(t)        cout<<t;

#include "st.h"
#include "lex.yy.cpp"

void yyerror(string msg);

SymbolTableS my_tables;

#define isExist         -1
%}

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

%type <type> VAL_TYPE TYPE_OPT FUNC_INVOCATION
%type <arg> FORMAL_ARG EXPR CONST_VAL
%type <args> FORMAL_ARGS COMMA_SEPARATED_EXPR

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
                my_tables.push();
                cout<<my_tables.table_vec.size()<<endl<<my_tables.first<<endl;
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*$2, OBJECT_type);
                if (ID_idx == isExist){
                    yyerror(*$2 + ": already exists !");
                }
                Trace("OBJECT ID\n");
                my_tables.push();
            } '{' PRO_BLOCK_CONTENT '}'
            {
                my_tables.dump();
                my_tables.pop();
                Trace("{ Reducing to program }\n");
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
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*$2, CONST_type, $4);
                if (ID_idx == isExist){
                    yyerror(*$2 + ": already exists !");
                }
                Trace("VAL ID = EXPR\n");
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

VARIABLE_DEC:
            VAR ID ':' VAL_TYPE
            {
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*$2, CONST_type, $4);
                if (ID_idx == isExist){
                    yyerror(*$2 + ": already exists !");
                }
                Trace("VAR ID : VAL_TYPE\n");
            }
        |   VAR ID '=' EXPR
            {
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*$2, CONST_type, $4);
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
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*$2, CONST_type, $6);
                if (ID_idx == isExist){
                    yyerror(*$2 + ": already exists !");
                }
                Trace("VAR ID : VAL_TYPE = EXPR\n");
            }
        |   VAR ID
            {
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*$2, CONST_type, VAL_UNDEF_type);
                if (ID_idx == isExist){
                    yyerror(*$2 + ": already exists !");
                }
                Trace("VAR ID\n");
            };

ARRAY_DEC:
            VAR ID ':' VAL_TYPE '[' INT_VAL ']'
            {
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*$2, ARRAY_type, $4, $6);
                if (ID_idx == isExist){
                    yyerror(*$2 + ": already exists !");
                }
                Trace("VAL ID : VAL_TYPE [ INT_VAL ]\n");
            };

METHOD:
            DEF ID '(' FORMAL_ARGS ')' TYPE_OPT 
            {
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*$2, FUNC_type);
                if (ID_idx == isExist){
                    yyerror(*$2 + ": already exists !");
                }

                IDDetail *tmp = my_tables.lookup(*$2);

                tmp->arg_val = $4;

                if($6 != VAL_UNDEF_type){
                    tmp->returnType = $6;
                }
                my_tables.push();
            } '{' METH_BLOCK_CONTENT '}'
            {
                my_tables.dump();
                my_tables.pop();
            };

FORMAL_ARGS:
            FORMAL_ARG
            {
                vector<ValueDetail*>* tmp = new vector<ValueDetail*>();
                tmp->push_back($1);
                $$ = tmp;
            }
        |   FORMAL_ARG ',' FORMAL_ARGS
            {  
                $3->push_back($1);
                $$ = $3;
            }
        |
            {
                $$ = new vector<ValueDetail*>();
            }
        ;

FORMAL_ARG:
            ID ':' VAL_TYPE
            {
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*$1, VAR_type, $3);
                if (ID_idx == isExist){
                    yyerror(*$1 + ": already exists !");
                }
                ValueDetail* tmp;
                tmp->arg_name = *$1;
                tmp->type = $3;

                $$ = tmp;
            };

TYPE_OPT:
            ':' VAL_TYPE
            {
                $$ = $2;
            }
        |
            {
                $$ = VAL_UNDEF_type;
            }
        ;

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

METH_BLOCK_CONTENT: 
            VAR_VAL_DEC METH_BLOCK_CONTENT
        |   STMTS METH_BLOCK_CONTENT
        |   METH_RETURN;

STMTS:      STMT
        |   STMT STMTS;

STMT:
            STMT_SIMPLE
        |   STMT_BLOCK
        |   STMT_CONDITIONAL
        |   STMT_LOOP
        |   FUNC_INVOCATION
        ;

STMT_SIMPLE:
            ID '=' EXPR
            {
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
        |   PRINT '(' EXPR ')'
        |   PRINTLN '(' EXPR ')'
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

EXPR:
            '-' EXPR %prec UMINUS
            {
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
        |   CONST_VAL
            {
                $$ = $1;
            }
        |   ID
            {
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
                ValueDetail* tmp = new ValueDetail();
                tmp->type = $1;
                $$ = tmp;
            }
        |   ID '[' EXPR ']'
            {
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

CONST_VAL:
            INT_VAL
            {
                $$ = INTconst($1);
            }
        |   FLOAT_VAL
            {
                $$ = FLOATconst($1);
            }
        |   BOOL_VAL
            {
                $$ = BOOLconst($1);
            }
        |   CHAR_VAL
            {
                $$ = CHARconst($1);
            }
        |   STRING_VAL
            {
                $$ = STRINGconst($1);
            };

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

STMT_BLOCK:
            '{' 
            {
                my_tables.push();
            } VAR_VAL_DEC STMTS '}'
            {   
                my_tables.dump();
                my_tables.pop();
            };

STMT_CONDITIONAL:
            IF_COND
        |   IF_COND ELSE_COND;

IF_COND:
            IF '(' EXPR ')'
            {
                if ($3->type != BOOL_type){
                    yyerror("Conditional expression must be Boolean !\n");
                }
            } STMT_SCOPE;

ELSE_COND:
            ELSE STMT_SCOPE;

STMT_SCOPE:
            STMT_SIMPLE
        |   STMT_BLOCK;

STMT_LOOP:
            WHILE_LOOP
        |   FOR_LOOP;

WHILE_LOOP:
            WHILE '(' EXPR ')' 
            {
                if ($3->type != BOOL_type){
                    yyerror("Conditional expression must be Boolean !\n");
                }
            } STMT_SCOPE;

FOR_LOOP:
            FOR '(' ID LT '-' INT_VAL TO INT_VAL ')' 
            {
                IDDetail* tmp = new IDDetail();
                tmp = my_tables.lookup(*$3);
                if(tmp->type != VAR_type){
                    yyerror("This ID must be variable type !\n");
                }
            }
            STMT_SCOPE;

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

    my_tables.dump();
}
