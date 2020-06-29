/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     BOOLEAN = 258,
     BREAK = 259,
     CHAR = 260,
     CASE = 261,
     CLASS = 262,
     CONTINUE = 263,
     DEF = 264,
     DO = 265,
     ELSE = 266,
     EXIT = 267,
     FALSE = 268,
     FLOAT = 269,
     FOR = 270,
     IF = 271,
     INT = 272,
     nULL = 273,
     OBJECT = 274,
     PRINT = 275,
     PRINTLN = 276,
     REPEAT = 277,
     RETURN = 278,
     READ = 279,
     STRING = 280,
     TO = 281,
     TRUE = 282,
     TYPE = 283,
     VAL = 284,
     VAR = 285,
     WHILE = 286,
     GT = 287,
     LT = 288,
     GE = 289,
     LE = 290,
     EE = 291,
     NE = 292,
     AND = 293,
     OR = 294,
     NOT = 295,
     INT_VAL = 296,
     FLOAT_VAL = 297,
     BOOL_VAL = 298,
     CHAR_VAL = 299,
     STRING_VAL = 300,
     ID = 301,
     UMINUS = 302
   };
#endif
/* Tokens.  */
#define BOOLEAN 258
#define BREAK 259
#define CHAR 260
#define CASE 261
#define CLASS 262
#define CONTINUE 263
#define DEF 264
#define DO 265
#define ELSE 266
#define EXIT 267
#define FALSE 268
#define FLOAT 269
#define FOR 270
#define IF 271
#define INT 272
#define nULL 273
#define OBJECT 274
#define PRINT 275
#define PRINTLN 276
#define REPEAT 277
#define RETURN 278
#define READ 279
#define STRING 280
#define TO 281
#define TRUE 282
#define TYPE 283
#define VAL 284
#define VAR 285
#define WHILE 286
#define GT 287
#define LT 288
#define GE 289
#define LE 290
#define EE 291
#define NE 292
#define AND 293
#define OR 294
#define NOT 295
#define INT_VAL 296
#define FLOAT_VAL 297
#define BOOL_VAL 298
#define CHAR_VAL 299
#define STRING_VAL 300
#define ID 301
#define UMINUS 302




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 36 "parser.y"
{
    int ival;
    float fval;
    bool bval;
    char cval;
    string* sval;

    ValueType type;
    ValueDetail* arg;
    vector<ValueDetail*> *args;
}
/* Line 1529 of yacc.c.  */
#line 155 "y.tab.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

