ifeq ($(shell uname -s), Darwin)
		javaa := ./javaa_mac
else
		javaa := ./javaa
endif

all: parser

parser: y.tab.cpp lex.yy.cpp st.cpp st.h
	g++ y.tab.cpp st.cpp -o compiler -ll -ly -std=c++11 -Wno-deprecated-register

lex.yy.cpp: scanner.l
	lex -o lex.yy.cpp scanner.l

y.tab.cpp: parser.y
	yacc -d parser.y -o y.tab.cpp


clean:
	-rm parser 
	-rm lex.yy.* y.tab.* *.class *.jasm

run:
	./compiler $(file).scala
	$(javaa) $(file).scala.jasm
	java $(file)