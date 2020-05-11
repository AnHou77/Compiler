%{
#define LIST     strcat(buf,yytext)
#define token(t) {LIST; printf("<%s>\n",t);}
#define tokenDel(t) {LIST; printf("<'%s'>\n",t);}
#define tokenInteger(t,i) {LIST; printf("<%s: %d>\n",t,i);}
#define tokenString(t,s) {LIST; printf("<%s: %s>\n",t,s);}
#define tokenDouble(t,d) {LIST; printf("<%s: %lf>\n",t,d);}

#define MAX_LINE_LENG 256

int linenum = 1;
char buf[MAX_LINE_LENG];

#include <stdio.h>
%}

%x C_COMMENT

/* Delimiters */
delim	[,:\.;()\[\]\{\}]

/* Operators */
arithop	[\+\-\*/]
rmdrop	%
relatop	<|<=|>=|>|==|!=
logop	"&&"|"||"|"!"
op {arithop}|{rmdrop}|{relatop}|{logop}

/* Boolean Constants */
boolean [true|false]

digits	[0-9]
letter	[a-zA-Z]

/* Integer Constants & Real Constants */
integer	{digits}+
plainreal	[+-]?{digits}"."{digits}
expreal	[+-]?{digits}"."{digits}[Ee][+-]?{digits}
realnum {plainreal}|{expreal}

/* Identifiers */
id	{letter}({digits}|{letter})*

/* String Constants */
string	\"(\"\"|[^\"\n])*\"

/* Comments */
c_comments	"/*"
c_commente	"*/"
cpp_comment "//"[^\n]*

%%

boolean {
	token("BOOLEAN");
}

break {
	token("BREAK");
}

char {
	token("CHAR");
}

case {
	token("CASE");
}

class {
	token("CLASS");
}

continue {
	token("CONTINUE");
}

def {
	token("DEF");
}

do {
	token("DO");
}

else {
	token("ELSE");
}

exit {
	token("EXIT");
}

false {
	token("FALSE");
}

float {
	token("FLOAT");
}

for {
	token("FOR");
}

if {
	token("IF");
}

int {
	token("INT");
}

null {
	token("NULL");
}

object {
	token("OBJECT");
}

print {
	token("PRINT");
}

println {
	token("PRINTLN");
}

repeat {
	token("REPEAT");
}

return {
	token("RETURN");
}

string {
	token("STRING");
}

to {
	token("TO");
}

true {
	token("TRUE");
}

type {
	token("TYPE");
}

val {
	token("VAL");
}

var {
	token("VAR");
}

while {
	token("WHILE");
}

{delim} {
	tokenDel(yytext);
}

{op} {
	tokenString("Operators",yytext);
}

{boolean} {
	tokenString("Boolean",yytext);
}

{integer} {
	int buff;
	sscanf(yytext,"%d",&buff);
	tokenInteger("Integer",buff);
}

{realnum} {
	double buff;
	sscanf(yytext,"%lf",&buff);
	tokenDouble("Real Constants",buff);
}

{id} {
	tokenString("id",yytext);
}

{string} {
	int flag = 0;

	char c = input();
	
	if(c == '"'){
		unput(c);
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
		unput(c);
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

int main(){
	yylex();
}