%{

#define DEBUG	0

#define LIST     strcat(buf,yytext)
#define token(t) {LIST; if(DEBUG){cout<< t << endl;} return t;}
#define tokenDel(t) {LIST; if(DEBUG){cout<< t << endl;}}
#define tokenInteger(t,i) {LIST; if(DEBUG){cout<< t << ": " << i << endl;}}
#define tokenString(t,s) {LIST; if(DEBUG){cout<< t << ": " << s << endl;}}
#define tokenDouble(t,d) {LIST; if(DEBUG){cout<< t << ": " << d << endl;}}

#define MAX_LINE_LENG 256

int linenum = 1;

char buf[MAX_LINE_LENG];

#include <iostream>
#include <string>
#include "y.tab.hpp"

using namespace std;


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

/* Char Constant */
char \'([^"\\\n]|\\.)\'

/* Comments */
c_comments	"/*"
c_commente	"*/"
cpp_comment "//"[^\n]*

%%

	/* Keyword */
boolean {
	token(BOOLEAN);
}

break {
	token(BREAK);
}

char {
	token(CHAR);
}

case {
	token(CASE);
}

class {
	token(CLASS);
}

continue {
	token(CONTINUE);
}

def {
	token(DEF);
}

do {
	token(DO);
}

else {
	token(ELSE);
}

exit {
	token(EXIT);
}

false {
	tokenString("BOOL", yytext);
	yylval.bval = false;
	return BOOL_VAL;
}

float {
	token(FLOAT);
}

for {
	token(FOR);
}

if {
	token(IF);
}

int {
	token(INT);
}

null {
	token(nULL);
}

object {
	token(OBJECT);
}

print {
	token(PRINT);
}

println {
	token(PRINTLN);
}

repeat {
	token(REPEAT);
}

return {
	token(RETURN);
}

read {
	token(READ);
}

string {
	token(STRING);
}

to {
	token(TO);
}

true {
	tokenString("BOOL", yytext);
	yylval.bval = true;
	return BOOL_VAL;
}

type {
	token(TYPE);
}

val {
	token(VAL);
}

var {
	token(VAR);
}

while {
	token(WHILE);
}

{SINGLEop} {
	token(yytext[0]);
}

">" {
	tokenString("OP",yytext);
	return GT;
}

"<" {
	tokenString("OP",yytext);
	return LT;
}

">=" {
	tokenString("OP",yytext);
	return GE;
}

"<=" {
	tokenString("OP",yytext);
	return LE;
}

"==" {
	tokenString("OP",yytext);
	return EE;
}

"!=" {
	tokenString("OP",yytext);
	return NE;
}

"&&" {
	tokenString("OP",yytext);
	return AND;
}

"||" {
	tokenString("OP",yytext);
	return OR;
}

"!" {
	tokenString("OP",yytext);
	return NOT;
}

{integer} {
	int buff = atoi(yytext);
	yylval.ival = buff;
	tokenInteger("INT",buff);
	return INT_VAL;
}

{realnum} {
	double buff = atof(yytext);
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

		yylval.sval = new string(buff);
		free(buff);
		return STRING_VAL;
	}
}

{char} {
	tokenString("Char",yytext);
	yylval.cval = yytext[1];
	return CHAR_VAL;
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
        cout << linenum+1 << ":" << buf << endl;
		cout << "bad character: " << yytext << endl;
        exit(-1);
}

%%