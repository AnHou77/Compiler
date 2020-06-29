%{

#define Trace(t)        if (DEBUG)  cout << t;
#define isExist         -1

#include "st.h"
#include "lex.yy.cpp"

void yyerror(string msg);

#define DEBUG 0
#define isGLOBAL 0

/* Create a symboltable list */
SymbolTableS my_tables;

string fname;
ofstream javafile;

string classID;
int varStackidx = 0;

int labelCnt = 0;

bool needRETURN = false;

bool elifFLAG = false;
vector<vector<int>> ifLabelStack;

vector<vector<int>> whileLabelStack;
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
                classID = *$2;
                javafile << "class " << classID << "{" << endl;
                my_tables.push();
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*$2, OBJECT_type);
                if (ID_idx == isExist){
                    yyerror(*$2 + ": already exists !");
                }
                Trace("OBJECT ID\n");
            } '{' PRO_BLOCK_CONTENT '}'
            {
                my_tables.dump();
                my_tables.pop();
                Trace("{ Reducing to program }\n");
                javafile << "}" << endl;
            };
/* Program's block should have at least one method
PRO_BLOCK_CONTENT_BASE:
            METHOD PRO_BLOCK_CONTENT; */

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

                IDDetail* tmp = my_tables.lookup(*$2);
                tmp->val = $4;
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

                IDDetail* tmp = my_tables.lookup(*$2);
                tmp->val = $6;
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

                IDDetail *tmp = my_tables.lookup(*$2);

                if (my_tables.first == isGLOBAL){
                    javafile << "\tfield static int " << *$2 << endl;
                }
                else{
                    javafile << "\t\tsipush " << 0 << endl;
                    tmp->stackidx = varStackidx;
                    javafile << "\t\tistore " << varStackidx++ << endl;
                }
            }
        |   VAR ID '=' EXPR
            {
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*$2, VAR_type, $4);
                if (ID_idx == isExist){
                    yyerror(*$2 + ": already exists !");
                }
                Trace("VAR ID = EXPR\n");

                IDDetail *tmp = my_tables.lookup(*$2);

                if (my_tables.first == isGLOBAL){
                    javafile << "\tfield static int " << *$2 << endl;
                    //javafile << "\tputstatic int " << classID << "." << *$2 << endl;
                }
                else{
                    tmp->stackidx = varStackidx;
                    javafile << "\t\tistore " << varStackidx++ << endl;
                }
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

                IDDetail *tmp = my_tables.lookup(*$2);

                if (my_tables.first == isGLOBAL){
                    javafile << "\tfield static int " << *$2 << endl;
                    //javafile << "\tputstatic int " << classID << "." << *$2 << endl;
                }
                else{
                    tmp->stackidx = varStackidx;
                    javafile << "\t\tistore " << varStackidx++ << endl;
                }
            }
        |   VAR ID
            {
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*$2, VAR_type, VAL_UNDEF_type);
                if (ID_idx == isExist){
                    yyerror(*$2 + ": already exists !");
                }
                Trace("VAR ID\n");

                IDDetail *tmp = my_tables.lookup(*$2);

                if (my_tables.first == isGLOBAL){
                    javafile << "\tfield static int " << *$2 << endl;
                }
                else{
                    javafile << "\t\tsipush " << 0 << endl;
                    tmp->stackidx = varStackidx;
                    javafile << "\t\tistore " << varStackidx++ << endl;
                }

                tmp->val->type = INT_type;
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
            /* def ID (arguments) <type> { block contents } */
            DEF ID 
            {
                Trace("DEF ID ( ARGS ) <:TYPE> {METHOD}");
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*$2, FUNC_type);
                if (ID_idx == isExist){
                    yyerror(*$2 + ": already exists !");
                }
                my_tables.push();
                varStackidx = 0;
                needRETURN = false;
            } '(' FORMAL_ARGS ')' TYPE_OPT 
            {

                IDDetail *tmp = my_tables.lookup(*$2);

                tmp->arg_val = *$5;

                if ($7 != VAL_UNDEF_type){
                    tmp->returnType = $7;
                }
                if (*$2 == "main"){
                    javafile << "\tmethod public static void main(java.lang.String[])" << endl;
                }
                else{

                    javafile << "\tmethod public static ";

                    if (tmp->returnType == VAL_UNDEF_type){
                        javafile << "void " << *$2;
                    }
                    else{
                        javafile << getVALTypeStr(tmp->returnType) << " " << *$2;
                    }

                    if ($5->size() == 0){
                        javafile << "()" << endl;
                    }
                    else{
                        javafile << "(";
                        for(int i = $5->size() - 1; i >= 0; i--){
                            if(i == $5->size() - 1){
                                javafile << getVALTypeStr((*$5)[i]->type);
                            }
                            else{
                                javafile << "," << getVALTypeStr((*$5)[i]->type);
                            }
                        }
                        javafile << ")" << endl;
                    }
                }

                javafile << "\tmax_stack 15\n\tmax_locals 15" << endl;
                javafile << "\t{" << endl;

            } '{' METH_BLOCK_CONTENT '}'
            {
                Trace("In Function Block\n");

                my_tables.dump();
                my_tables.pop();

                javafile << "\t\treturn" << endl;
                javafile << "\t}" << endl;
            };

/* Arguments declaration */
FORMAL_ARGS:
            /* single argument */
            FORMAL_ARG
            {
                Trace("FORMAL_ARG\n");
                vector<ValueDetail*>* tmp = new vector<ValueDetail*>();
                tmp->push_back($1);
                $$ = tmp;
            }
            /* Muti arguments */
        |   FORMAL_ARG ',' FORMAL_ARGS
            {  
                Trace("FORMAL_ARG, FORMAL_ARGS\n");
                $3->push_back($1);
                $$ = $3;
            }
        |
            /* empty entry */
            {
                $$ = new vector<ValueDetail*>();
            }
        ;

/* Argument declaration */
FORMAL_ARG:
            /* ID : type */
            ID ':' VAL_TYPE
            {
                Trace("ID : VAL_TYPE\n");
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*$1, VAR_type, $3);
                if (ID_idx == isExist){
                    yyerror(*$1 + ": already exists !");
                }
                
                IDDetail* IDtmp = my_tables.lookup(*$1);
                IDtmp->stackidx = varStackidx++;
                
                ValueDetail* tmp = new ValueDetail();
                tmp->arg_name = *$1;
                cout<< tmp->arg_name<<endl;
                tmp->type = $3;

                $$ = tmp;
            };

/* Function has returntype is optional */
TYPE_OPT:
            /* return VAL_TYPE */
            ':' VAL_TYPE
            {
                Trace("<: VAL_TYPE>\n");
                $$ = $2;
            }
        |
            /* empty entry */
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
            /* ID = EXPR */
            ID '=' EXPR
            {
                Trace("STMT(ID = EXPR)\n");
                IDDetail* tmp = new IDDetail();
                tmp = my_tables.lookup(*$1);
                
                if (tmp == NULL){
                    yyerror("This ID does not exist !\n");
                }
                
                else{
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

                    if (tmp->stackidx == -1){
                        javafile << "\t\tputstatic int " << classID << "." << *$1 << endl;
                    }
                    else{
                        javafile << "\t\tistore " << tmp->stackidx << endl;
                    }
                }
            }
            /* ID [EXPR] = EXPR */
            /* ID should be array type */
        |   ID '[' EXPR ']' '=' EXPR
            {
                Trace("STMT(ID [EXPR] = EXPR)\n");
                IDDetail* tmp = new IDDetail();
                tmp = my_tables.lookup(*$1);

                if (tmp == NULL){
                    yyerror("This ID does not exist !\n");
                }

                else{
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
            }
            /* Print EXPR */
        |   PRINT
            {
                javafile << "\t\tgetstatic java.io.PrintStream java.lang.System.out" << endl;
            } EXPR {
                string buf = getVALTypeStr($3->type);
                javafile << "\t\tinvokevirtual void java.io.PrintStream.print(" << buf << ")" <<endl;
            }
            /* Println EXPR */
        |   PRINTLN
            {
                javafile << "\t\tgetstatic java.io.PrintStream java.lang.System.out" << endl;
            } EXPR {
                string buf = getVALTypeStr($3->type);
                javafile << "\t\tinvokevirtual void java.io.PrintStream.println(" << buf << ")" <<endl;
            }
            /* To get ID */
        |   READ ID
            {
                IDDetail* tmp = new IDDetail();
                tmp = my_tables.lookup(*$2);
                
                if (tmp == NULL){
                    yyerror("This ID does not exist !\n");
                }
            }
            /* Return without expression */
        |   RETURN
            {
                needRETURN = true;
                javafile << "\t\treturn" << endl;
            }
            /* Return EXPR */
        |   RETURN EXPR
            {
                needRETURN = true;
                javafile << "\t\tireturn" << endl;
            }
            /* EXPR */
        |   EXPR
            /* Call function */
        |   FUNC_INVOCATION;

/* Expression declaration */
EXPR:
            /* - EXPR */
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
                
                genJBOperation('n');
            }
            /* EXPR * EXPR with the same type */
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

                genJBOperation('*');
            }
            /* EXPR / EXPR with the same type */
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

                genJBOperation('/');
            }
            /* EXPR + EXPR with the same type */
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

                genJBOperation('+');
            }
            /* EXPR - EXPR with the same type */
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

                genJBOperation('-');
            }
            /* return (EXPR < EXPR) with boolean */
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

                genJBLogicOp(opLT);
            }
            /* return (EXPR <= EXPR) with boolean */
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

                genJBLogicOp(opLE);
            }
            /* return (EXPR == EXPR) with boolean */
        |   EXPR EE EXPR
            {
                Trace("EXPR == EXPR\n");
                if($1->type != $3->type){
                    yyerror("Sorry, different type can't be compared !\n");
                }
                if($1->type == VAL_UNDEF_type){
                    yyerror("There is an undefined type expression !\n");
                }
                /* == can compared with any type */
                $$ = (*$1 == *$3);

                genJBLogicOp(opEE);
            }
            /* return (EXPR >= EXPR) with boolean */
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

                genJBLogicOp(opGE);
            }
            /* return (EXPR > EXPR) with boolean */
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

                genJBLogicOp(opGT);
            }
            /* return (EXPR != EXPR) with boolean */
        |   EXPR NE EXPR
            {
                Trace("EXPR != EXPR\n");
                if($1->type != $3->type){
                    yyerror("Sorry, different type can't be compared !\n");
                }
                if($1->type == VAL_UNDEF_type){
                    yyerror("There is an undefined type expression !\n");
                }
                /* != can compared with any type */
                $$ = (*$1 != *$3);

                genJBLogicOp(opNE);
            }
            /* return (!EXPR) with boolean */
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

                genJBOperation('!');
            }
            /* return (EXPR && EXPR) with boolean */
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

                genJBOperation('&');
            }
            /* return (EXPR && EXPR) with boolean */
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

                genJBOperation('|');
            }
            /* ( EXPR ) */
            /* For print & println */
        |   '(' EXPR ')'
            {
                Trace("( EXPR )\n");
                $$ = $2;
            }
            /* Value */
        |   CONST_VAL
            {
                Trace("EXPR(Const_value)\n");
                $$ = $1;
            }
            /* ID */
        |   ID
            {
                Trace("EXPR(ID)\n");
                IDDetail* tmp = my_tables.lookup(*$1);
                if (tmp == NULL){
                    yyerror("This ID does not exist !\n");
                }
                else{
                    // if (tmp->type != CONST_type && tmp->type != VAR_type){
                    //     yyerror("Can get this ID value !\n");
                    // }

                    // $$ = tmp->val;
                    if (tmp->type == FUNC_type){
                        Trace("Is function type");
                        
                        if(tmp->arg_val.size() != 0){
                            yyerror("argument size error");
                        }

                        ValueDetail* buf = new ValueDetail();
                        $$ = buf;
                    }

                    if (tmp->val == NULL){
                        $$ = new ValueDetail();
                    }
                    else{
                        $$ = tmp->val;
                        int buf;
                    
                        if (tmp->type == CONST_type){
                            if (tmp->val->type == INT_type){
                                buf = tmp->val->intValue;
                                javafile << "\t\tsipush " << buf << endl;
                            }
                            else if (tmp->val->type == BOOL_type){
                                if (tmp->val->boolValue){
                                    buf = 1;
                                }
                                else{
                                    buf = 0;
                                }
                                javafile << "\t\tsipush " << buf << endl;
                            }
                            else if (tmp->val->type == STRING_type){
                                javafile << "\t\tldc \"" << *(tmp->val->stringValue) << "\"" << endl;
                            }
                        }
                        else{
                            if(tmp->stackidx == -1){
                                javafile << "\t\tgetstatic int " << classID << "." << *$1 << endl;
                            }
                            else{
                                javafile << "\t\tiload " << tmp->stackidx << endl;
                            }
                        }
                    }
                }
            }
            /* Call function */
        |   FUNC_INVOCATION
            {
                Trace("FUNCTION_CALL\n");
                ValueDetail* tmp = new ValueDetail();
                tmp->type = $1;
                $$ = tmp;
            }
            /* ID [EXPR] */
            /* ID should be Array */
        |   ID '[' EXPR ']'
            {
                Trace("ID [EXPR]\n");
                IDDetail* tmp = my_tables.lookup(*$1);
                if (tmp == NULL){
                    yyerror("This ID does not exist !\n");
                }
                else{
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
                }
            };

/* Constant value type declaration */
CONST_VAL:
            INT_VAL
            {
                Trace("Get Integer\n");
                $$ = INTconst($1);
                if (my_tables.first != isGLOBAL){
                    javafile << "\t\tsipush " << $1 << endl;
                }
                //javafile << "\t\tsipush " << $1 << endl;
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
                if (my_tables.first != isGLOBAL){
                    if ($1){
                        javafile << "\t\tsipush " << 1 << endl;
                    }
                    else{
                        javafile << "\t\tsipush " << 0 << endl;
                    }   
                }
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
                if (my_tables.first != isGLOBAL){
                    javafile << "\t\tldc \"" << *$1 << "\"" << endl;
                }
                //javafile << "\t\tldc \"" << *$1 << "\"" << endl;
            };

/* Call function */
FUNC_INVOCATION:
            /* Call function can be : ID  or  ID(expr,expr,...,expr) */
            ID '(' COMMA_SEPARATED_EXPR ')'
            {
                IDDetail* tmp = my_tables.lookup(*$1);
                
                if (tmp == NULL){
                    yyerror("This ID does not exist !\n");
                }
                else{
                    if (tmp->type != FUNC_type){
                        yyerror("This ID is not a function !\n");
                    }

                    if ($3->size() != tmp->arg_val.size()){
                        yyerror("Wrong argument size !\n");
                    }

                    for (int i = 0; i < $3->size(); i++){
                        if((*$3)[i]->type != tmp->arg_val[i]->type){
                            yyerror("exist argument's type error");
                        }
                    }

                    $$ = tmp->returnType;

                    javafile << "\t\tinvokestatic int " << classID << "." << *$1 << "(";

                    for (int i = $3->size() - 1; i >= 0; i--){
                        if(i == $3->size() - 1){
                            javafile << getVALTypeStr((*$3)[i]->type);
                        }
                        else{
                            javafile << "," << getVALTypeStr((*$3)[i]->type);
                        }
                    }

                    javafile << ")" << endl;
                }
            };

/* Muti expression separated by comma */
COMMA_SEPARATED_EXPR:
            /* Single EXPR */
            EXPR
            {
                vector<ValueDetail*>* tmp = new vector<ValueDetail*>();
                tmp->push_back($1);
                $$ = tmp;
            }
            /* Multi EXPR */
        |   EXPR ',' COMMA_SEPARATED_EXPR
            {
                $3->push_back($1);
                $$ = $3;
            }
        |
            /* empty entry */
            {
                $$ = new vector<ValueDetail*>();
            };

/* Block_statement declaration */
STMT_BLOCK:
            /* { block entry } */
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
            {
                IFEnd();
            }
        |   IF_COND
            {
                ELSEStart();
            } ELSE_COND;

/* Condition_if declaration */
IF_COND:
            /* if_condition can be :  IF (EXPR)  or  IF(EXPR) ELSE */
            IF '(' EXPR ')'
            {
                Trace("IF ( EXPR )\n");
                if ($3->type != BOOL_type){
                    yyerror("Conditional expression must be Boolean !\n");
                }

                if (!elifFLAG){
                    IFStart();
                }
                else{
                    ELIFStart();
                }

                elifFLAG = false;
            } CONDITION_LOOP_SCOPE
            {
                IFScope();
            };
/* Condition_else declaration */
ELSE_COND:
            ELSE
            {
                elifFLAG = true;
            } IF_COND
        |   ELSE CONDITION_LOOP_SCOPE
            {
                ELSEEnd();
            };

/* Statement's scope contents */
//STMT_SCOPE:
            /* Just a simple_statement */
//            STMT_SIMPLE
            /* a block with multi statements */
//        |   STMT_BLOCK;

CONDITION_LOOP_SCOPE:   
            STMT_SIMPLE
        |   STMT_BLOCK;



/* Loop_statements declaration */
STMT_LOOP:
            WHILE_LOOP
        |   FOR_LOOP;

/* Loop_while delcaration */
WHILE_LOOP:
            /* while (EXPR) */
            WHILE
            {
                WHILEStart();
            } '(' EXPR ')' 
            {
                Trace("WHILE ( EXPR )\n");
                if ($4->type != BOOL_type){
                    yyerror("Conditional expression must be Boolean !\n");
                }

                WHILEBeforeScope();
            } CONDITION_LOOP_SCOPE
            {
                WHILEScope();
                WHILEEnd();
            };

/* Loop_for declaration */
FOR_LOOP:
            /* for (ID <- int to int) */
            FOR '(' ID LT '-' INT_VAL TO INT_VAL ')' 
            {
                Trace("FOR ( ID < - INT TO INT )\n");
                IDDetail* tmp = new IDDetail();
                tmp = my_tables.lookup(*$3);
                if(tmp->type != VAR_type){
                    yyerror("This ID must be variable type !\n");
                }
            }
            CONDITION_LOOP_SCOPE;

/* Method's return rule declaration */
METH_RETURN:
            /* Only return */
            RETURN
            /* return with an expression */
        |   RETURN EXPR
            /* empty */
        |;




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

    if (argc > 1){
        fname = string(argv[1]);
        //fname = "example";
        javafile.open(fname + ".jasm");
        cout << "file build!!" << endl;

    }

    if (!javafile){
        cout << "javafile open failed" << endl;
        exit(1);
    }

    /* perform parsing */
    if (yyparse() == 1)                 /* parsing */
    {
        yyerror("Parsing error !");     /* syntax error */
    }
    else
    {
        cout << endl << endl << "===========PARSING COMPLETE===========" << endl << endl << endl;
    }
}
