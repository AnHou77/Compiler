%{
#define LIST     strcat(buf,yytext)
#define token(t) {LIST; printf("<%s>\n",t);}
#define tokenDel(t) {LIST; printf("<'%s'>\n",t);}
#define tokenInteger(t,i) {LIST; printf("<%s: %d>\n",t,i);}
#define tokenString(t,s) {LIST; printf("<%s: %s>\n",t,s);}
#define tokenDouble(t,d) {LIST; printf("<%s: %lf>\n",t,d);}

#define MAX_LINE_LENG 256
#define TABLE_SIZE 37

int linenum = 1;

char buf[MAX_LINE_LENG];

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <iostream>
#include <string>
#include "y.tab.hpp"

// /* Symbol Node */
// typedef struct{
// 	char *name;
// 	void *pre;
// 	void *next;
// } Node;

// /* Symbol table */
// typedef struct{
// 	Node **table;
// } SymbolTable;


// unsigned int hash(char* s);

// SymbolTable* create();
// int lookup(SymbolTable* st, char* s);
// int insert(SymbolTable* st, char* s);
// void dump(SymbolTable* st);

// /* Global symboltable */
// SymbolTable *ST;

%}

%x C_COMMENT

/* Delimiters */
delim	[,:\.;()\[\]\{\}]

/* Operators */
arithop	[\+\-\*/=]
rmdrop	%
relatop	<|<=|>=|>|==|!=
logop	"&&"|"||"|"!"
op {arithop}|{rmdrop}|{relatop}|{logop}

/* Single bit Operators */
SINGLEop {delim}|{arithop}|{rmdrop}

/* Boolean Constants */
boolean true|false

digits	[0-9]
letter	[a-zA-Z]

/* Integer Constants & Real Constants */
integer	{digits}+
plainreal	{integer}"."{integer}
expreal	{integer}"."{integer}[Ee][+-]?{integer}
realnum [+-]?({plainreal}|{expreal})

/* Identifiers */
id	{letter}({digits}|{letter})*

/* String Constants */
string	\"(\"\"|[^\"\n])*\"

/* Comments */
c_comments	"/*"
c_commente	"*/"
cpp_comment "//"[^\n]*

%%

	/* Keyword */
boolean {
	return BOOLEAN;
}

break {
	return BREAK;
}

char {
	return CHAR;
}

case {
	return CASE;
}

class {
	return CLASS;
}

continue {
	return CONTINUE;
}

def {
	return DEF;
}

do {
	return DO;
}

else {
	return ELSE;
}

exit {
	return EXIT;
}

false {
	tokenString("BOOL", yytext);
	yylval.bval = false;
	return BOOL_VAL;
}

float {
	return FLOAT;
}

for {
	return FOR;
}

if {
	return IF;
}

int {
	return INT;
}

null {
	return nULL;
}

object {
	return OBJECT;
}

print {
	return PRINT;
}

println {
	return PRINTLN;
}

repeat {
	return REPEAT;
}

return {
	return RETURN;
}

read {
	return READ;
}

string {
	return STRING;
}

to {
	return TO;
}

true {
	tokenString("BOOL", yytext);
	yylval.bval = true;
	return BOOL_VAL;
}

type {
	return TYPE;
}

val {
	return VAL;
}

var {
	return VAR;
}

while {
	return WHILE;
}

{SINGLEop} {
	token(yytext[0]);
	return yytext[0];
}

">" {
	token(yytext);
	return GT;
}

"<" {
	token(yytext);
	return LT;
}

">=" {
	token(yytext);
	return GE;
}

"<=" {
	token(yytext);
	return LE;
}

"==" {
	token(yytext);
	return EE;
}

"!=" {
	token(yytext);
	return NE;
}

"&&" {
	token(yytext);
	return AND;
}

"||" {
	token(yytext);
	return OR;
}

"!" {
	token(yytext);
	return NOT;
}

{integer} {
	int buff;
	sscanf(yytext,"%d",&buff);
	yylval.ival = buff;
	tokenInteger("INT",buff);
	return INT_VAL;
}

{realnum} {
	double buff;
	sscanf(yytext,"%lf",&buff);
	yylval.fval = buff;
	tokenDouble("FLOAT",buff);
	return FLOAT_VAL;
}

	/* Put Identifier into SymbolTable */
{id} {
	yylval.sval = new string(yytext);
	tokenString("ID",yytext);
	return ID;
}

	/* String deal with double quote */
{string} {
	int flag = 0;

	char c = getc(yyin);
	
	if(c == '"'){
		ungetc(c, yyin);
		yymore();
	}
	else{
		int cnt = 0;
		char *buff = (char *)malloc(yyleng - 1);
		for(int i = 0; i < yyleng; i++){
			if(yytext[i] == '"'){
				if(((i == 0) || (i == yyleng - 1))){
					continue;
				}
				else{
					if(flag){
						flag = 0;
						continue;
					}
					else{
						flag = 1;
					}
				}
			}
			buff[cnt] = yytext[i];
			cnt++;
		}
		tokenString("String",buff);
		ungetc(c, yyin);
		free(buff);
	}
}

{c_comments} {
	LIST;
	BEGIN(C_COMMENT);
}

<C_COMMENT>{c_commente} {
	LIST;
	BEGIN(INITIAL);
}

<C_COMMENT>. {
	LIST;
}

<C_COMMENT>\n {
	LIST;
	printf("%d: %s", linenum++, buf);
    buf[0] = '\0';
}

{cpp_comment} {
	LIST;
}

\n	{
    	LIST;
        printf("%d: %s", linenum++, buf);
    	buf[0] = '\0';
}

[ \t]*	{LIST;}

.	{
        LIST;
        printf("%d:%s\n", linenum+1, buf);
        printf("bad character:'%s'\n",yytext);
        exit(-1);
}

%%

// /* Hash function with division method */
// unsigned int hash(char* s){
// 	unsigned int idx = 0;
// 	while(1){
// 		if(*(s) == 0){
// 			break;
// 		}
// 		idx = idx + *(s++);
// 	}
// 	return idx % TABLE_SIZE;
// }

// /* Create a new symbol table */
// SymbolTable* create() {
// 	SymbolTable *st = NULL;
// 	st = malloc(sizeof(SymbolTable));
// 	st->table = malloc(sizeof(Node) * TABLE_SIZE);

// 	/* initial */
// 	for(int i = 0; i < TABLE_SIZE; i++){
// 		st->table[i] = NULL;
// 	}

// 	return st;
// }

// /* Check if s was already in symbol table */
// int lookup(SymbolTable* st, char* s){
// 	unsigned int idx = hash(s);
// 	Node *iter = st->table[idx];

// 	for(; iter != NULL; iter = iter->next){
// 		if(strcmp(s, iter->name) == 0){
// 			return 1;
// 		}
// 	}

// 	return 0;
// }

// /* Insert s into symbol table */
// int insert(SymbolTable* st, char* s){
// 	unsigned int idx = hash(s);
// 	Node *currentNode = st->table[idx];
// 	Node *newNode = malloc(sizeof(Node));

// 	/* There is still space in this row, set as first node */
// 	if(currentNode == NULL){
// 		newNode->name = malloc(sizeof(char)*strlen(s));
// 		strcpy(newNode->name, s);
// 		newNode->next = NULL;
// 		newNode->pre = NULL;
// 		st->table[idx] = newNode;
// 		return 1;
// 	}
// 	/* If it doesn't exist in the table, link to the end */
// 	else{
// 		Node *preNode = NULL;
// 		for(; currentNode != NULL; currentNode = currentNode->next){
// 			if(strcmp(s, currentNode->name) == 0){
// 				return 1;
// 			}
// 			else{
// 				preNode = currentNode;
// 			}
// 		}
		
// 		newNode->name = malloc(sizeof(char)*strlen(s));
// 		strcpy(newNode->name, s);
// 		newNode->next = NULL;
// 		newNode->pre = preNode;
// 		preNode->next = newNode;

// 		return 1;
// 	}
// }

// /* Output Symbol Table */
// void dump(SymbolTable* st){
// 	printf("=====SymbolTable=====\n");
// 	for(int i = 0; i < TABLE_SIZE; i++){
// 		Node *iter = st->table[i];
// 		for(; iter != NULL; iter = iter->next){
// 			printf("%s\n", iter->name);
// 		}
// 	}
// }