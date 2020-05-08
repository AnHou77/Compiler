%{
#define LIST     strcat(buf,yytext)
#define token(t) {LIST; printf("<%s>\n","t");}
#define tokenInteger(t,i) {LIST; printf("<%s:%d>\n","t",i);}
#define tokenString(t,s) {LIST; printf("<%s:%s>\n","t",s);}

#define MAX_LINE_LENG 256

int linenum = 1;
char buf[MAX_LINE_LENG];

#include <stdio.h>
%}

%%

delim	[,:.;()[]{}]

arithop	[+-/\*]
rmdrop	[%]
relatop	[<|<=|>=|>|==|!=]
logop	["&&"|"||"|"!"]

boolean [true|false]

break {
	token("break");
}

char {
	token("char");
}

case {
	token("case");
}

class {
	token("class");
}

"("	{token('(');}

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