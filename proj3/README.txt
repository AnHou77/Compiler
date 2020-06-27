My Scanner change:

1. Use C++ instead C.
2. Add return in token(t), return yytext to parser.
3. Operator token divided into single bit and muti bit
    , return to parser can parse easier.
4. All tokens that need to be passed to the parser are passed with yylval.
5. Define char type token.
6. For checking parser easily, define "DEBUG" to control cout.