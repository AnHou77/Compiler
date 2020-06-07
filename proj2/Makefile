all: parser

parser: y.tab.cpp lex.yy.cpp st.cpp st.h
	g++ y.tab.cpp st.cpp -o parser -ll -ly -std=c++11

lex.yy.cpp: scanner.l
	lex -o lex.yy.cpp scanner.l

y.tab.cpp: parser.y
	yacc -d parser.y -o y.tab.cpp

clean:
	rm parser lex.yy.* y.tab.*