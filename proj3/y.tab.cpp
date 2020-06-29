/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "parser.y"


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

vector<vector<int>> forLabelStack;


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 193 of yacc.c.  */
#line 236 "y.tab.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 249 "y.tab.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   439

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  104
/* YYNRULES -- Number of states.  */
#define YYNSTATES  184

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   302

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      58,    59,    49,    47,    60,    48,     2,    50,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    55,     2,
       2,    54,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    56,     2,    57,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    52,     2,    53,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    51
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,    11,    14,    17,    18,    20,    22,
      24,    29,    36,    41,    46,    53,    56,    64,    65,    66,
      78,    80,    84,    85,    89,    92,    93,    95,    97,    99,
     101,   103,   106,   109,   111,   113,   116,   118,   120,   122,
     124,   126,   130,   137,   138,   142,   143,   147,   150,   152,
     155,   157,   159,   162,   166,   170,   174,   178,   182,   186,
     190,   194,   198,   202,   205,   209,   213,   217,   219,   221,
     223,   228,   230,   232,   234,   236,   238,   243,   245,   249,
     250,   251,   256,   259,   262,   263,   265,   266,   270,   271,
     278,   279,   283,   286,   288,   290,   292,   294,   295,   296,
     304,   305,   317,   319,   322
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      62,     0,    -1,    -1,    19,    46,    63,    52,    64,    53,
      -1,    65,    64,    -1,    69,    64,    -1,    -1,    66,    -1,
      67,    -1,    68,    -1,    29,    46,    54,    82,    -1,    29,
      46,    55,    75,    54,    82,    -1,    30,    46,    55,    75,
      -1,    30,    46,    54,    82,    -1,    30,    46,    55,    75,
      54,    82,    -1,    30,    46,    -1,    30,    46,    55,    75,
      56,    41,    57,    -1,    -1,    -1,     9,    46,    70,    58,
      72,    59,    74,    71,    52,    76,    53,    -1,    73,    -1,
      73,    60,    72,    -1,    -1,    46,    55,    75,    -1,    55,
      75,    -1,    -1,    17,    -1,    14,    -1,     5,    -1,    25,
      -1,     3,    -1,    65,    76,    -1,    77,    76,    -1,   102,
      -1,    78,    -1,    78,    77,    -1,    79,    -1,    86,    -1,
      89,    -1,    96,    -1,    84,    -1,    46,    54,    82,    -1,
      46,    56,    82,    57,    54,    82,    -1,    -1,    20,    80,
      82,    -1,    -1,    21,    81,    82,    -1,    24,    46,    -1,
      23,    -1,    23,    82,    -1,    82,    -1,    84,    -1,    48,
      82,    -1,    82,    49,    82,    -1,    82,    50,    82,    -1,
      82,    47,    82,    -1,    82,    48,    82,    -1,    82,    33,
      82,    -1,    82,    35,    82,    -1,    82,    36,    82,    -1,
      82,    34,    82,    -1,    82,    32,    82,    -1,    82,    37,
      82,    -1,    40,    82,    -1,    82,    38,    82,    -1,    82,
      39,    82,    -1,    58,    82,    59,    -1,    83,    -1,    46,
      -1,    84,    -1,    46,    56,    82,    57,    -1,    41,    -1,
      42,    -1,    43,    -1,    44,    -1,    45,    -1,    46,    58,
      85,    59,    -1,    82,    -1,    82,    60,    85,    -1,    -1,
      -1,    52,    87,    88,    53,    -1,    65,    88,    -1,    77,
      88,    -1,    -1,    91,    -1,    -1,    91,    90,    93,    -1,
      -1,    16,    58,    82,    59,    92,    95,    -1,    -1,    11,
      94,    91,    -1,    11,    95,    -1,    79,    -1,    86,    -1,
      97,    -1,   100,    -1,    -1,    -1,    31,    98,    58,    82,
      59,    99,    95,    -1,    -1,    15,    58,    46,    33,    48,
      41,    26,    41,    59,   101,    95,    -1,    23,    -1,    23,
      82,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    85,    85,    84,   107,   108,   109,   114,   115,   116,
     120,   131,   148,   167,   186,   208,   232,   245,   255,   244,
     312,   320,   328,   336,   358,   365,   372,   376,   380,   384,
     388,   395,   396,   397,   400,   401,   405,   406,   407,   408,
     409,   415,   452,   480,   479,   488,   487,   495,   505,   511,
     517,   519,   524,   542,   558,   574,   590,   606,   622,   638,
     653,   669,   685,   700,   718,   735,   753,   759,   765,   826,
     835,   863,   869,   874,   885,   890,   900,   942,   949,   956,
     964,   963,   975,   976,   977,   981,   986,   985,   994,   993,
    1015,  1014,  1018,  1031,  1032,  1038,  1039,  1045,  1048,  1044,
    1065,  1064,  1078,  1080,  1082
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BOOLEAN", "BREAK", "CHAR", "CASE",
  "CLASS", "CONTINUE", "DEF", "DO", "ELSE", "EXIT", "FALSE", "FLOAT",
  "FOR", "IF", "INT", "nULL", "OBJECT", "PRINT", "PRINTLN", "REPEAT",
  "RETURN", "READ", "STRING", "TO", "TRUE", "TYPE", "VAL", "VAR", "WHILE",
  "GT", "LT", "GE", "LE", "EE", "NE", "AND", "OR", "NOT", "INT_VAL",
  "FLOAT_VAL", "BOOL_VAL", "CHAR_VAL", "STRING_VAL", "ID", "'+'", "'-'",
  "'*'", "'/'", "UMINUS", "'{'", "'}'", "'='", "':'", "'['", "']'", "'('",
  "')'", "','", "$accept", "program", "@1", "PRO_BLOCK_CONTENT",
  "VAR_VAL_DEC", "CONSTANT_DEC", "VARIABLE_DEC", "ARRAY_DEC", "METHOD",
  "@2", "@3", "FORMAL_ARGS", "FORMAL_ARG", "TYPE_OPT", "VAL_TYPE",
  "METH_BLOCK_CONTENT", "STMTS", "STMT", "STMT_SIMPLE", "@4", "@5", "EXPR",
  "CONST_VAL", "FUNC_INVOCATION", "COMMA_SEPARATED_EXPR", "STMT_BLOCK",
  "@6", "STMT_BLOCK_CONTENTS", "STMT_CONDITIONAL", "@7", "IF_COND", "@8",
  "ELSE_COND", "@9", "CONDITION_LOOP_SCOPE", "STMT_LOOP", "WHILE_LOOP",
  "@10", "@11", "FOR_LOOP", "@12", "METH_RETURN", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,    43,    45,    42,
      47,   302,   123,   125,    61,    58,    91,    93,    40,    41,
      44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    61,    63,    62,    64,    64,    64,    65,    65,    65,
      66,    66,    67,    67,    67,    67,    68,    70,    71,    69,
      72,    72,    72,    73,    74,    74,    75,    75,    75,    75,
      75,    76,    76,    76,    77,    77,    78,    78,    78,    78,
      78,    79,    79,    80,    79,    81,    79,    79,    79,    79,
      79,    79,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    83,    83,    83,    83,    83,    84,    85,    85,    85,
      87,    86,    88,    88,    88,    89,    90,    89,    92,    91,
      94,    93,    93,    95,    95,    96,    96,    98,    99,    97,
     101,   100,   102,   102,   102
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     6,     2,     2,     0,     1,     1,     1,
       4,     6,     4,     4,     6,     2,     7,     0,     0,    11,
       1,     3,     0,     3,     2,     0,     1,     1,     1,     1,
       1,     2,     2,     1,     1,     2,     1,     1,     1,     1,
       1,     3,     6,     0,     3,     0,     3,     2,     1,     2,
       1,     1,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     3,     3,     1,     1,     1,
       4,     1,     1,     1,     1,     1,     4,     1,     3,     0,
       0,     4,     2,     2,     0,     1,     0,     3,     0,     6,
       0,     3,     2,     1,     1,     1,     1,     0,     0,     7,
       0,    11,     1,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     1,     0,     6,     0,     0,     0,
       0,     6,     7,     8,     9,     6,    17,     0,    15,     3,
       4,     5,     0,     0,     0,     0,     0,    22,     0,    71,
      72,    73,    74,    75,    68,     0,     0,    10,    67,    69,
      30,    28,    27,    26,    29,     0,    13,    12,     0,     0,
      20,    63,     0,    79,    52,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    25,    22,     0,    77,     0,    66,    61,    57,
      60,    58,    59,    62,    64,    65,    55,    56,    53,    54,
      11,    14,     0,    23,     0,    18,    21,    70,    79,    76,
      16,    24,     0,    78,   104,     0,     0,    43,    45,    48,
       0,    97,    68,    80,   104,     0,   104,    34,    36,    50,
      40,    37,    38,    85,    39,    95,    96,    33,     0,     0,
       0,     0,    49,    47,     0,     0,     0,    84,    31,    19,
      32,    48,    35,     0,     0,     0,    44,    46,     0,    41,
       0,    84,    84,     0,    49,    90,    87,     0,    88,     0,
      70,    82,    83,    81,    93,    51,    94,     0,    92,     0,
       0,    98,     0,    91,     0,    89,     0,    42,     0,    99,
       0,   100,     0,   101
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,    10,    11,    12,    13,    14,    15,    22,
     102,    49,    50,    95,    45,   115,   116,   117,   118,   130,
     131,   119,    38,    39,    76,   121,   137,   153,   122,   143,
     123,   170,   156,   167,   168,   124,   125,   134,   176,   126,
     182,   127
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -104
static const yytype_int16 yypact[] =
{
     -16,   -14,     7,  -104,  -104,   -36,    -8,    12,    28,    32,
      43,    -8,  -104,  -104,  -104,    -8,  -104,     0,    10,  -104,
    -104,  -104,    39,   196,     6,   196,     6,    52,   196,  -104,
    -104,  -104,  -104,  -104,   -39,   196,   196,   362,  -104,  -104,
    -104,  -104,  -104,  -104,  -104,    45,   362,   -30,    46,    41,
      44,   329,   196,   196,  -104,   253,   196,   196,   196,   196,
     196,   196,   196,   196,   196,   196,   196,   196,   196,   196,
      61,     6,    48,    52,   310,   234,    50,  -104,    42,    42,
      42,    42,    42,    42,   329,   370,    11,    11,  -104,  -104,
     362,   362,    53,  -104,     6,  -104,  -104,  -104,   196,  -104,
    -104,  -104,    59,  -104,    99,    47,    58,  -104,  -104,   196,
      71,  -104,   -48,  -104,    99,    68,    99,   177,  -104,   362,
     389,  -104,  -104,   113,  -104,  -104,  -104,  -104,    80,   196,
     196,   196,   362,  -104,    69,   196,   196,   138,  -104,  -104,
    -104,   196,  -104,   120,   100,   272,   362,   362,   196,   362,
     336,   138,   138,    79,   362,   207,  -104,    86,  -104,   291,
      81,  -104,  -104,  -104,  -104,   389,  -104,   121,  -104,    95,
     207,  -104,   196,  -104,   112,  -104,   207,   362,   105,  -104,
      89,  -104,   207,  -104
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -104,  -104,  -104,     3,   -57,  -104,  -104,  -104,  -104,  -104,
    -104,    77,  -104,  -104,   -22,   -63,   -67,  -104,  -103,  -104,
    -104,   -23,  -104,   -89,    54,   -99,  -104,   -83,  -104,  -104,
     -12,  -104,  -104,  -104,   -94,  -104,  -104,  -104,  -104,  -104,
    -104,  -104
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -87
static const yytype_int16 yytable[] =
{
      37,     7,    46,     1,    47,    51,   135,     4,   136,    40,
      53,    41,    54,    55,    20,   120,     6,    52,    21,    53,
      42,     8,     9,    43,    69,   120,    70,   120,   120,    74,
      75,    44,     3,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,   114,   120,    93,
     142,   138,   164,   140,    23,    24,   166,   114,    16,   114,
      66,    67,   120,   120,    25,    26,   165,   164,   161,   162,
     152,   166,   101,   164,    17,    75,   175,   166,    18,   164,
     151,   165,   179,   166,   152,   152,   132,   165,   183,    64,
      65,    66,    67,   165,   151,   151,    19,    27,    48,    68,
      72,    71,    92,    94,    73,   128,   145,   146,   147,    99,
     100,   104,   149,   150,   105,   106,   129,   133,   154,   107,
     108,   139,   109,   110,   -86,   159,   144,   148,     8,     9,
     111,   155,   163,   157,   169,   172,   174,   106,   178,    28,
      29,    30,    31,    32,    33,   112,   180,    35,   181,   177,
      96,   113,   103,   105,   106,   173,     0,    36,   107,   108,
       0,   141,   110,     0,     0,     0,     0,     8,     9,   111,
       0,     0,     0,     0,     0,     0,     0,     0,    28,    29,
      30,    31,    32,    33,   112,     0,    35,     0,     0,     0,
     113,     0,   105,   106,     0,     0,    36,   107,   108,     0,
     141,   110,     0,     0,     0,     0,     0,     0,   111,     0,
       0,     0,     0,     0,     0,     0,     0,    28,    29,    30,
      31,    32,    33,   112,     0,    35,     0,   107,   108,   113,
     141,   110,     0,     0,     0,    36,    28,    29,    30,    31,
      32,    33,    34,     0,    35,     0,     0,    28,    29,    30,
      31,    32,    33,   112,    36,    35,     0,     0,     0,   113,
       0,     0,     0,     0,     0,    36,    56,    57,    58,    59,
      60,    61,    62,    63,     0,     0,     0,     0,     0,     0,
       0,    64,    65,    66,    67,    56,    57,    58,    59,    60,
      61,    62,    63,     0,    98,     0,     0,     0,     0,     0,
      64,    65,    66,    67,    56,    57,    58,    59,    60,    61,
      62,    63,    77,     0,     0,     0,     0,     0,     0,    64,
      65,    66,    67,    56,    57,    58,    59,    60,    61,    62,
      63,   158,     0,     0,     0,     0,     0,     0,    64,    65,
      66,    67,    56,    57,    58,    59,    60,    61,    62,    63,
     171,     0,     0,     0,     0,     0,     0,    64,    65,    66,
      67,    56,    57,    58,    59,    60,    61,    97,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
       0,     0,     0,    64,    65,    66,    67,     0,     0,     0,
       0,     0,     0,   160,    56,    57,    58,    59,    60,    61,
      62,    63,    56,    57,    58,    59,    60,    61,    62,    64,
      65,    66,    67,     0,     0,     0,     0,    64,    65,    66,
      67,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,     0,
       0,     0,     0,     0,     0,     0,   -69,     0,   -69,   -69
};

static const yytype_int16 yycheck[] =
{
      23,     9,    25,    19,    26,    28,    54,     0,    56,     3,
      58,     5,    35,    36,    11,   104,    52,    56,    15,    58,
      14,    29,    30,    17,    54,   114,    56,   116,   117,    52,
      53,    25,    46,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,   104,   137,    71,
     117,   114,   155,   116,    54,    55,   155,   114,    46,   116,
      49,    50,   151,   152,    54,    55,   155,   170,   151,   152,
     137,   170,    94,   176,    46,    98,   170,   176,    46,   182,
     137,   170,   176,   182,   151,   152,   109,   176,   182,    47,
      48,    49,    50,   182,   151,   152,    53,    58,    46,    54,
      59,    55,    41,    55,    60,    58,   129,   130,   131,    59,
      57,    52,   135,   136,    15,    16,    58,    46,   141,    20,
      21,    53,    23,    24,    11,   148,    46,    58,    29,    30,
      31,    11,    53,    33,    48,    54,    41,    16,    26,    40,
      41,    42,    43,    44,    45,    46,    41,    48,    59,   172,
      73,    52,    98,    15,    16,   167,    -1,    58,    20,    21,
      -1,    23,    24,    -1,    -1,    -1,    -1,    29,    30,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,
      42,    43,    44,    45,    46,    -1,    48,    -1,    -1,    -1,
      52,    -1,    15,    16,    -1,    -1,    58,    20,    21,    -1,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    44,    45,    46,    -1,    48,    -1,    20,    21,    52,
      23,    24,    -1,    -1,    -1,    58,    40,    41,    42,    43,
      44,    45,    46,    -1,    48,    -1,    -1,    40,    41,    42,
      43,    44,    45,    46,    58,    48,    -1,    -1,    -1,    52,
      -1,    -1,    -1,    -1,    -1,    58,    32,    33,    34,    35,
      36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    48,    49,    50,    32,    33,    34,    35,    36,
      37,    38,    39,    -1,    60,    -1,    -1,    -1,    -1,    -1,
      47,    48,    49,    50,    32,    33,    34,    35,    36,    37,
      38,    39,    59,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      48,    49,    50,    32,    33,    34,    35,    36,    37,    38,
      39,    59,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,
      49,    50,    32,    33,    34,    35,    36,    37,    38,    39,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,
      50,    32,    33,    34,    35,    36,    37,    57,    32,    33,
      34,    35,    36,    37,    38,    39,    47,    48,    49,    50,
      -1,    -1,    -1,    47,    48,    49,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    57,    32,    33,    34,    35,    36,    37,
      38,    39,    32,    33,    34,    35,    36,    37,    38,    47,
      48,    49,    50,    -1,    -1,    -1,    -1,    47,    48,    49,
      50,    32,    33,    34,    35,    36,    37,    38,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,    49,    50
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    19,    62,    46,     0,    63,    52,     9,    29,    30,
      64,    65,    66,    67,    68,    69,    46,    46,    46,    53,
      64,    64,    70,    54,    55,    54,    55,    58,    40,    41,
      42,    43,    44,    45,    46,    48,    58,    82,    83,    84,
       3,     5,    14,    17,    25,    75,    82,    75,    46,    72,
      73,    82,    56,    58,    82,    82,    32,    33,    34,    35,
      36,    37,    38,    39,    47,    48,    49,    50,    54,    54,
      56,    55,    59,    60,    82,    82,    85,    59,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    41,    75,    55,    74,    72,    57,    60,    59,
      57,    75,    71,    85,    52,    15,    16,    20,    21,    23,
      24,    31,    46,    52,    65,    76,    77,    78,    79,    82,
      84,    86,    89,    91,    96,    97,   100,   102,    58,    58,
      80,    81,    82,    46,    98,    54,    56,    87,    76,    53,
      76,    23,    77,    90,    46,    82,    82,    82,    58,    82,
      82,    65,    77,    88,    82,    11,    93,    33,    59,    82,
      57,    88,    88,    53,    79,    84,    86,    94,    95,    48,
      92,    59,    54,    91,    41,    95,    99,    82,    26,    95,
      41,    59,   101,    95
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 85 "parser.y"
    {
                classID = *(yyvsp[(2) - (2)].sval);
                javafile << "class " << classID << "{" << endl;
                my_tables.push();
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*(yyvsp[(2) - (2)].sval), OBJECT_type);
                if (ID_idx == isExist){
                    yyerror(*(yyvsp[(2) - (2)].sval) + ": already exists !");
                }
                Trace("OBJECT ID\n");
            }
    break;

  case 3:
#line 95 "parser.y"
    {
                my_tables.dump();
                my_tables.pop();
                Trace("{ Reducing to program }\n");
                javafile << "}" << endl;
            }
    break;

  case 10:
#line 121 "parser.y"
    {
                Trace("VAL ID = EXPR\n");
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*(yyvsp[(2) - (4)].sval), CONST_type, (yyvsp[(4) - (4)].arg));
                if (ID_idx == isExist){
                    yyerror(*(yyvsp[(2) - (4)].sval) + ": already exists !");
                }

                IDDetail* tmp = my_tables.lookup(*(yyvsp[(2) - (4)].sval));
                tmp->val = (yyvsp[(4) - (4)].arg);
            }
    break;

  case 11:
#line 132 "parser.y"
    {
                if ((yyvsp[(4) - (6)].type) != (yyvsp[(6) - (6)].arg)->type){
                    yyerror("Error assignment: Type different !");
                } 
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*(yyvsp[(2) - (6)].sval), CONST_type, (yyvsp[(6) - (6)].arg));
                if (ID_idx == isExist){
                    yyerror(*(yyvsp[(2) - (6)].sval) + ": already exists !");
                }
                Trace("VAL ID : VAL_TYPE = EXPR\n");

                IDDetail* tmp = my_tables.lookup(*(yyvsp[(2) - (6)].sval));
                tmp->val = (yyvsp[(6) - (6)].arg);
            }
    break;

  case 12:
#line 149 "parser.y"
    {
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*(yyvsp[(2) - (4)].sval), VAR_type, (yyvsp[(4) - (4)].type));
                if (ID_idx == isExist){
                    yyerror(*(yyvsp[(2) - (4)].sval) + ": already exists !");
                }
                Trace("VAR ID : VAL_TYPE\n");

                IDDetail *tmp = my_tables.lookup(*(yyvsp[(2) - (4)].sval));

                if (my_tables.first == isGLOBAL){
                    javafile << "\t\tfield static int " << *(yyvsp[(2) - (4)].sval) << endl;
                }
                else{
                    javafile << "\t\tsipush " << 0 << endl;
                    tmp->stackidx = varStackidx;
                    javafile << "\t\tistore " << varStackidx++ << endl;
                }
            }
    break;

  case 13:
#line 168 "parser.y"
    {
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*(yyvsp[(2) - (4)].sval), VAR_type, (yyvsp[(4) - (4)].arg));
                if (ID_idx == isExist){
                    yyerror(*(yyvsp[(2) - (4)].sval) + ": already exists !");
                }
                Trace("VAR ID = EXPR\n");

                IDDetail *tmp = my_tables.lookup(*(yyvsp[(2) - (4)].sval));

                if (my_tables.first == isGLOBAL){
                    javafile << "\t\tfield static int " << *(yyvsp[(2) - (4)].sval) << endl;
                    javafile << "\t\tputstatic int " << classID << "." << *(yyvsp[(2) - (4)].sval) << endl;
                }
                else{
                    tmp->stackidx = varStackidx;
                    javafile << "\t\tistore " << varStackidx++ << endl;
                }
            }
    break;

  case 14:
#line 187 "parser.y"
    {
                if ((yyvsp[(4) - (6)].type) != (yyvsp[(6) - (6)].arg)->type){
                    yyerror("Error assignment: Type different !");
                }
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*(yyvsp[(2) - (6)].sval), VAR_type, (yyvsp[(6) - (6)].arg));
                if (ID_idx == isExist){
                    yyerror(*(yyvsp[(2) - (6)].sval) + ": already exists !");
                }
                Trace("VAR ID : VAL_TYPE = EXPR\n");

                IDDetail *tmp = my_tables.lookup(*(yyvsp[(2) - (6)].sval));

                if (my_tables.first == isGLOBAL){
                    javafile << "\t\tfield static int " << *(yyvsp[(2) - (6)].sval) << endl;
                    javafile << "\t\tputstatic int " << classID << "." << *(yyvsp[(2) - (6)].sval) << endl;
                }
                else{
                    tmp->stackidx = varStackidx;
                    javafile << "\t\tistore " << varStackidx++ << endl;
                }
            }
    break;

  case 15:
#line 209 "parser.y"
    {
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*(yyvsp[(2) - (2)].sval), VAR_type, VAL_UNDEF_type);
                if (ID_idx == isExist){
                    yyerror(*(yyvsp[(2) - (2)].sval) + ": already exists !");
                }
                Trace("VAR ID\n");

                IDDetail *tmp = my_tables.lookup(*(yyvsp[(2) - (2)].sval));

                if (my_tables.first == isGLOBAL){
                    javafile << "\t\tfield static int " << *(yyvsp[(2) - (2)].sval) << endl;
                }
                else{
                    javafile << "\t\tsipush " << 0 << endl;
                    tmp->stackidx = varStackidx;
                    javafile << "\t\tistore " << varStackidx++ << endl;
                }

                tmp->val->type = INT_type;
            }
    break;

  case 16:
#line 233 "parser.y"
    {
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*(yyvsp[(2) - (7)].sval), ARRAY_type, (yyvsp[(4) - (7)].type), (yyvsp[(6) - (7)].ival));
                if (ID_idx == isExist){
                    yyerror(*(yyvsp[(2) - (7)].sval) + ": already exists !");
                }
                Trace("VAL ID : VAL_TYPE [ INT_VAL ]\n");
            }
    break;

  case 17:
#line 245 "parser.y"
    {
                Trace("DEF ID ( ARGS ) <:TYPE> {METHOD}");
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*(yyvsp[(2) - (2)].sval), FUNC_type);
                if (ID_idx == isExist){
                    yyerror(*(yyvsp[(2) - (2)].sval) + ": already exists !");
                }
                my_tables.push();
                varStackidx = 0;
                needRETURN = false;
            }
    break;

  case 18:
#line 255 "parser.y"
    {

                IDDetail *tmp = my_tables.lookup(*(yyvsp[(2) - (7)].sval));

                tmp->arg_val = *(yyvsp[(5) - (7)].args);

                if ((yyvsp[(7) - (7)].type) != VAL_UNDEF_type){
                    tmp->returnType = (yyvsp[(7) - (7)].type);
                }
                if (*(yyvsp[(2) - (7)].sval) == "main"){
                    javafile << "\tmethod public static void main(java.lang.String[])" << endl;
                }
                else{

                    javafile << "\tmethod public static ";

                    if (tmp->returnType == VAL_UNDEF_type){
                        javafile << "void " << *(yyvsp[(2) - (7)].sval);
                    }
                    else{
                        javafile << getVALTypeStr(tmp->returnType) << " " << *(yyvsp[(2) - (7)].sval);
                    }

                    if ((yyvsp[(5) - (7)].args)->size() == 0){
                        javafile << "()" << endl;
                    }
                    else{
                        javafile << "(";
                        for(int i = (yyvsp[(5) - (7)].args)->size() - 1; i >= 0; i--){
                            if(i == (yyvsp[(5) - (7)].args)->size() - 1){
                                javafile << getVALTypeStr((*(yyvsp[(5) - (7)].args))[i]->type);
                            }
                            else{
                                javafile << "," << getVALTypeStr((*(yyvsp[(5) - (7)].args))[i]->type);
                            }
                        }
                        javafile << ")" << endl;
                    }
                }

                javafile << "\tmax_stack 15\n\tmax_locals 15" << endl;
                javafile << "\t{" << endl;

            }
    break;

  case 19:
#line 299 "parser.y"
    {
                Trace("In Function Block\n");

                my_tables.dump();
                my_tables.pop();

                javafile << "\t\treturn" << endl;
                javafile << "\t}" << endl;
            }
    break;

  case 20:
#line 313 "parser.y"
    {
                Trace("FORMAL_ARG\n");
                vector<ValueDetail*>* tmp = new vector<ValueDetail*>();
                tmp->push_back((yyvsp[(1) - (1)].arg));
                (yyval.args) = tmp;
            }
    break;

  case 21:
#line 321 "parser.y"
    {  
                Trace("FORMAL_ARG, FORMAL_ARGS\n");
                (yyvsp[(3) - (3)].args)->push_back((yyvsp[(1) - (3)].arg));
                (yyval.args) = (yyvsp[(3) - (3)].args);
            }
    break;

  case 22:
#line 328 "parser.y"
    {
                (yyval.args) = new vector<ValueDetail*>();
            }
    break;

  case 23:
#line 337 "parser.y"
    {
                Trace("ID : VAL_TYPE\n");
                int ID_idx = my_tables.table_vec[my_tables.first].insert(*(yyvsp[(1) - (3)].sval), VAR_type, (yyvsp[(3) - (3)].type));
                if (ID_idx == isExist){
                    yyerror(*(yyvsp[(1) - (3)].sval) + ": already exists !");
                }
                
                IDDetail* IDtmp = my_tables.lookup(*(yyvsp[(1) - (3)].sval));
                IDtmp->stackidx = varStackidx++;
                
                ValueDetail* tmp = new ValueDetail();
                tmp->arg_name = *(yyvsp[(1) - (3)].sval);
                cout<< tmp->arg_name<<endl;
                tmp->type = (yyvsp[(3) - (3)].type);

                (yyval.arg) = tmp;
            }
    break;

  case 24:
#line 359 "parser.y"
    {
                Trace("<: VAL_TYPE>\n");
                (yyval.type) = (yyvsp[(2) - (2)].type);
            }
    break;

  case 25:
#line 365 "parser.y"
    {
                (yyval.type) = VAL_UNDEF_type;
            }
    break;

  case 26:
#line 373 "parser.y"
    {
                (yyval.type) = INT_type;
            }
    break;

  case 27:
#line 377 "parser.y"
    {
                (yyval.type) = FLOAT_type;
            }
    break;

  case 28:
#line 381 "parser.y"
    {
                (yyval.type) = CHAR_type;
            }
    break;

  case 29:
#line 385 "parser.y"
    {
                (yyval.type) = STRING_type;
            }
    break;

  case 30:
#line 389 "parser.y"
    {
                (yyval.type) = BOOL_type;
            }
    break;

  case 41:
#line 416 "parser.y"
    {
                Trace("STMT(ID = EXPR)\n");
                IDDetail* tmp = new IDDetail();
                tmp = my_tables.lookup(*(yyvsp[(1) - (3)].sval));
                
                if (tmp == NULL){
                    yyerror("This ID does not exist !\n");
                }
                
                else{
                    if (tmp->type != VAR_type){
                        yyerror("Sorry, it can't be assgined !\n");
                    }

                    if (!tmp->needInit){
                        if (tmp->val->type != (yyvsp[(3) - (3)].arg)->type){
                            yyerror("Sorry, differnt type can't be assigned !\n");
                        }
                        *(tmp->val) = *(yyvsp[(3) - (3)].arg);
                    }
                    else{
                        tmp->val = new ValueDetail();
                        *(tmp->val) = *(yyvsp[(3) - (3)].arg);
                        tmp->needInit = false;
                    }

                    if (tmp->stackidx == -1){
                        javafile << "\t\tputstatic int " << classID << "." << *(yyvsp[(1) - (3)].sval) << endl;
                    }
                    else{
                        javafile << "\t\tistore " << tmp->stackidx << endl;
                    }
                }
            }
    break;

  case 42:
#line 453 "parser.y"
    {
                Trace("STMT(ID [EXPR] = EXPR)\n");
                IDDetail* tmp = new IDDetail();
                tmp = my_tables.lookup(*(yyvsp[(1) - (6)].sval));

                if (tmp == NULL){
                    yyerror("This ID does not exist !\n");
                }

                else{
                    if (tmp->type != ARRAY_type){
                        yyerror("Sorry, it can't be assgined !\n");
                    }

                    if ((yyvsp[(3) - (6)].arg)->type != INT_type){
                        yyerror("Sorry, array size must be Integer !\n");
                    }

                    if (tmp->arrType != (yyvsp[(6) - (6)].arg)->type){
                        yyerror("Sorry, different type can't be assigned !\n");
                    }

                    *(tmp->arr_val[(yyvsp[(3) - (6)].arg)->intValue]) = *(yyvsp[(6) - (6)].arg);
                }
            }
    break;

  case 43:
#line 480 "parser.y"
    {
                javafile << "\t\tgetstatic java.io.PrintStream java.lang.System.out" << endl;
            }
    break;

  case 44:
#line 482 "parser.y"
    {
                string buf = getVALTypeStr((yyvsp[(3) - (3)].arg)->type);
                javafile << "\t\tinvokevirtual void java.io.PrintStream.print(" << buf << ")" <<endl;
            }
    break;

  case 45:
#line 488 "parser.y"
    {
                javafile << "\t\tgetstatic java.io.PrintStream java.lang.System.out" << endl;
            }
    break;

  case 46:
#line 490 "parser.y"
    {
                string buf = getVALTypeStr((yyvsp[(3) - (3)].arg)->type);
                javafile << "\t\tinvokevirtual void java.io.PrintStream.println(" << buf << ")" <<endl;
            }
    break;

  case 47:
#line 496 "parser.y"
    {
                IDDetail* tmp = new IDDetail();
                tmp = my_tables.lookup(*(yyvsp[(2) - (2)].sval));
                
                if (tmp == NULL){
                    yyerror("This ID does not exist !\n");
                }
            }
    break;

  case 48:
#line 506 "parser.y"
    {
                needRETURN = true;
                javafile << "\t\treturn" << endl;
            }
    break;

  case 49:
#line 512 "parser.y"
    {
                needRETURN = true;
                javafile << "\t\tireturn" << endl;
            }
    break;

  case 52:
#line 525 "parser.y"
    {
                Trace("-EXPR\n");
                if((yyvsp[(2) - (2)].arg)->type == INT_type){
                    (yyvsp[(2) - (2)].arg)->intValue *= -1;
                    (yyval.arg) = (yyvsp[(2) - (2)].arg);
                }
                else if((yyvsp[(2) - (2)].arg)->type == FLOAT_type){
                    (yyvsp[(2) - (2)].arg)->floatValue *= -1;
                    (yyval.arg)= (yyvsp[(2) - (2)].arg);
                }
                else{
                    yyerror("Value type must be Integer & Float !\n");
                }
                
                genJBOperation('n');
            }
    break;

  case 53:
#line 543 "parser.y"
    {
                Trace("EXPR * EXPR\n");
                if((yyvsp[(1) - (3)].arg)->type != (yyvsp[(3) - (3)].arg)->type){
                    yyerror("Sorry, different type can't be caculated !\n");
                }
                if((yyvsp[(1) - (3)].arg)->type == INT_type || (yyvsp[(1) - (3)].arg)->type == FLOAT_type){
                    (yyval.arg) = *(yyvsp[(1) - (3)].arg) * *(yyvsp[(3) - (3)].arg);
                }
                else{
                    yyerror("Value type must be Integer & Float !\n");
                }

                genJBOperation('*');
            }
    break;

  case 54:
#line 559 "parser.y"
    {
                Trace("EXPR / EXPR\n");
                if((yyvsp[(1) - (3)].arg)->type != (yyvsp[(3) - (3)].arg)->type){
                    yyerror("Sorry, different type can't be caculated !\n");
                }
                if((yyvsp[(1) - (3)].arg)->type == INT_type || (yyvsp[(1) - (3)].arg)->type == FLOAT_type){
                    (yyval.arg) = *(yyvsp[(1) - (3)].arg) / *(yyvsp[(3) - (3)].arg);
                }
                else{
                    yyerror("Value type must be Integer & Float !\n");
                }

                genJBOperation('/');
            }
    break;

  case 55:
#line 575 "parser.y"
    {
                Trace("EXPR + EXPR\n");
                if((yyvsp[(1) - (3)].arg)->type != (yyvsp[(3) - (3)].arg)->type){
                    yyerror("Sorry, different type can't be caculated !\n");
                }
                if((yyvsp[(1) - (3)].arg)->type == INT_type || (yyvsp[(1) - (3)].arg)->type == FLOAT_type){
                    (yyval.arg) = *(yyvsp[(1) - (3)].arg) + *(yyvsp[(3) - (3)].arg);
                }
                else{
                    yyerror("Value type must be Integer & Float !\n");
                }

                genJBOperation('+');
            }
    break;

  case 56:
#line 591 "parser.y"
    {
                Trace("EXPR - EXPR\n");
                if((yyvsp[(1) - (3)].arg)->type != (yyvsp[(3) - (3)].arg)->type){
                    yyerror("Sorry, different type can't be caculated !\n");
                }
                if((yyvsp[(1) - (3)].arg)->type == INT_type || (yyvsp[(1) - (3)].arg)->type == FLOAT_type){
                    (yyval.arg) = *(yyvsp[(1) - (3)].arg) - *(yyvsp[(3) - (3)].arg);
                }
                else{
                    yyerror("Value type must be Integer & Float !\n");
                }

                genJBOperation('-');
            }
    break;

  case 57:
#line 607 "parser.y"
    {
                Trace("EXPR < EXPR\n");
                if((yyvsp[(1) - (3)].arg)->type != (yyvsp[(3) - (3)].arg)->type){
                    yyerror("Sorry, different type can't be compared !\n");
                }
                if((yyvsp[(1) - (3)].arg)->type == INT_type || (yyvsp[(1) - (3)].arg)->type == FLOAT_type){
                    (yyval.arg) = (*(yyvsp[(1) - (3)].arg) < *(yyvsp[(3) - (3)].arg));
                }
                else{
                    yyerror("Value type must be Integer & Float !\n");
                }

                genJBLogicOp(opLT);
            }
    break;

  case 58:
#line 623 "parser.y"
    {
                Trace("EXPR <= EXPR\n");
                if((yyvsp[(1) - (3)].arg)->type != (yyvsp[(3) - (3)].arg)->type){
                    yyerror("Sorry, different type can't be compared !\n");
                }
                if((yyvsp[(1) - (3)].arg)->type == INT_type || (yyvsp[(1) - (3)].arg)->type == FLOAT_type){
                    (yyval.arg) = (*(yyvsp[(1) - (3)].arg) <= *(yyvsp[(3) - (3)].arg));
                }
                else{
                    yyerror("Value type must be Integer & Float !\n");
                }

                genJBLogicOp(opLE);
            }
    break;

  case 59:
#line 639 "parser.y"
    {
                Trace("EXPR == EXPR\n");
                if((yyvsp[(1) - (3)].arg)->type != (yyvsp[(3) - (3)].arg)->type){
                    yyerror("Sorry, different type can't be compared !\n");
                }
                if((yyvsp[(1) - (3)].arg)->type == VAL_UNDEF_type){
                    yyerror("There is an undefined type expression !\n");
                }
                /* == can compared with any type */
                (yyval.arg) = (*(yyvsp[(1) - (3)].arg) == *(yyvsp[(3) - (3)].arg));

                genJBLogicOp(opEE);
            }
    break;

  case 60:
#line 654 "parser.y"
    {
                Trace("EXPR >= EXPR\n");
                if((yyvsp[(1) - (3)].arg)->type != (yyvsp[(3) - (3)].arg)->type){
                    yyerror("Sorry, different type can't be compared !\n");
                }
                if((yyvsp[(1) - (3)].arg)->type == INT_type || (yyvsp[(1) - (3)].arg)->type == FLOAT_type){
                    (yyval.arg) = (*(yyvsp[(1) - (3)].arg) >= *(yyvsp[(3) - (3)].arg));
                }
                else{
                    yyerror("Value type must be Integer & Float !\n");
                }

                genJBLogicOp(opGE);
            }
    break;

  case 61:
#line 670 "parser.y"
    {
                Trace("EXPR > EXPR\n");
                if((yyvsp[(1) - (3)].arg)->type != (yyvsp[(3) - (3)].arg)->type){
                    yyerror("Sorry, different type can't be compared !\n");
                }
                if((yyvsp[(1) - (3)].arg)->type == INT_type || (yyvsp[(1) - (3)].arg)->type == FLOAT_type){
                    (yyval.arg) = (*(yyvsp[(1) - (3)].arg) > *(yyvsp[(3) - (3)].arg));
                }
                else{
                    yyerror("Value type must be Integer & Float !\n");
                }

                genJBLogicOp(opGT);
            }
    break;

  case 62:
#line 686 "parser.y"
    {
                Trace("EXPR != EXPR\n");
                if((yyvsp[(1) - (3)].arg)->type != (yyvsp[(3) - (3)].arg)->type){
                    yyerror("Sorry, different type can't be compared !\n");
                }
                if((yyvsp[(1) - (3)].arg)->type == VAL_UNDEF_type){
                    yyerror("There is an undefined type expression !\n");
                }
                /* != can compared with any type */
                (yyval.arg) = (*(yyvsp[(1) - (3)].arg) != *(yyvsp[(3) - (3)].arg));

                genJBLogicOp(opNE);
            }
    break;

  case 63:
#line 701 "parser.y"
    {
                Trace("! EXPR\n");
                ValueDetail* tmp = new ValueDetail();
                tmp->type = BOOL_type;
                if ((yyvsp[(2) - (2)].arg)->type != BOOL_type){
                    if ((yyvsp[(2) - (2)].arg)->type == VAL_UNDEF_type){
                        yyerror("There is an undefined type expression !\n");
                    }
                    else{
                        tmp->boolValue = !((yyvsp[(2) - (2)].arg)->boolValue);
                    }
                }
                (yyval.arg) = tmp;

                genJBOperation('!');
            }
    break;

  case 64:
#line 719 "parser.y"
    {
                Trace("EXPR && EXPR\n");
                ValueDetail* tmp = new ValueDetail();
                tmp->type = BOOL_type;
                if((yyvsp[(1) - (3)].arg)->type != (yyvsp[(3) - (3)].arg)->type){
                    yyerror("Sorry, different type can't be compared !\n");
                }
                if((yyvsp[(1) - (3)].arg)->type != BOOL_type){
                    yyerror("Value type must be Boolean !\n");
                }
                tmp->boolValue = ((yyvsp[(1) - (3)].arg)->boolValue && (yyvsp[(3) - (3)].arg)->boolValue);
                (yyval.arg) = tmp;

                genJBOperation('&');
            }
    break;

  case 65:
#line 736 "parser.y"
    {
                Trace("EXPR || EXPR\n");
                ValueDetail* tmp = new ValueDetail();
                tmp->type = BOOL_type;
                if((yyvsp[(1) - (3)].arg)->type != (yyvsp[(3) - (3)].arg)->type){
                    yyerror("Sorry, different type can't be compared !\n");
                }
                if((yyvsp[(1) - (3)].arg)->type != BOOL_type){
                    yyerror("Value type must be Boolean !\n");
                }
                tmp->boolValue = ((yyvsp[(1) - (3)].arg)->boolValue || (yyvsp[(3) - (3)].arg)->boolValue);
                (yyval.arg) = tmp;

                genJBOperation('|');
            }
    break;

  case 66:
#line 754 "parser.y"
    {
                Trace("( EXPR )\n");
                (yyval.arg) = (yyvsp[(2) - (3)].arg);
            }
    break;

  case 67:
#line 760 "parser.y"
    {
                Trace("EXPR(Const_value)\n");
                (yyval.arg) = (yyvsp[(1) - (1)].arg);
            }
    break;

  case 68:
#line 766 "parser.y"
    {
                Trace("EXPR(ID)\n");
                IDDetail* tmp = my_tables.lookup(*(yyvsp[(1) - (1)].sval));
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
                        (yyval.arg) = buf;
                    }

                    if (tmp->val == NULL){
                        (yyval.arg) = new ValueDetail();
                    }
                    else{
                        (yyval.arg) = tmp->val;
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
                                javafile << "\t\tldc" << *(tmp->val->stringValue) << endl;
                            }
                        }
                        else{
                            if(tmp->stackidx == -1){
                                javafile << "\t\tgetstatic int " << classID << "." << *(yyvsp[(1) - (1)].sval) << endl;
                            }
                            else{
                                javafile << "\t\tiload " << tmp->stackidx << endl;
                            }
                        }
                    }
                }
            }
    break;

  case 69:
#line 827 "parser.y"
    {
                Trace("FUNCTION_CALL\n");
                ValueDetail* tmp = new ValueDetail();
                tmp->type = (yyvsp[(1) - (1)].type);
                (yyval.arg) = tmp;
            }
    break;

  case 70:
#line 836 "parser.y"
    {
                Trace("ID [EXPR]\n");
                IDDetail* tmp = my_tables.lookup(*(yyvsp[(1) - (4)].sval));
                if (tmp == NULL){
                    yyerror("This ID does not exist !\n");
                }
                else{
                    if (tmp->type != ARRAY_type){
                        yyerror("ID type must be array !\n");
                    }

                    if ((yyvsp[(3) - (4)].arg)->type != INT_type){
                        yyerror("Sorry, array size must be Integer !\n");
                    }

                    if ((yyvsp[(3) - (4)].arg)->intValue >= tmp->arrLength || (yyvsp[(3) - (4)].arg)->intValue < 0){
                        yyerror("Array size out of range !\n");
                    }

                    ValueDetail* arr_tmp = new ValueDetail();
                    arr_tmp = tmp->arr_val[(yyvsp[(3) - (4)].arg)->intValue];
                    (yyval.arg) = arr_tmp;
                }
            }
    break;

  case 71:
#line 864 "parser.y"
    {
                Trace("Get Integer\n");
                (yyval.arg) = INTconst((yyvsp[(1) - (1)].ival));
                javafile << "\t\tsipush " << (yyvsp[(1) - (1)].ival) << endl;
            }
    break;

  case 72:
#line 870 "parser.y"
    {
                Trace("Get Float\n");
                (yyval.arg) = FLOATconst((yyvsp[(1) - (1)].fval));
            }
    break;

  case 73:
#line 875 "parser.y"
    {
                Trace("Get Boolean\n");
                (yyval.arg) = BOOLconst((yyvsp[(1) - (1)].bval));
                if ((yyvsp[(1) - (1)].bval)){
                    javafile << "\t\tsipush " << 1 << endl;
                }
                else{
                    javafile << "\t\tsipush " << 0 << endl;
                }
            }
    break;

  case 74:
#line 886 "parser.y"
    {
                Trace("Get Char\n");
                (yyval.arg) = CHARconst((yyvsp[(1) - (1)].cval));
            }
    break;

  case 75:
#line 891 "parser.y"
    {
                Trace("Get String\n");
                (yyval.arg) = STRINGconst((yyvsp[(1) - (1)].sval));
                javafile << "\t\tldc " << *(yyvsp[(1) - (1)].sval) << endl;
            }
    break;

  case 76:
#line 901 "parser.y"
    {
                IDDetail* tmp = my_tables.lookup(*(yyvsp[(1) - (4)].sval));
                
                if (tmp == NULL){
                    yyerror("This ID does not exist !\n");
                }
                else{
                    if (tmp->type != FUNC_type){
                        yyerror("This ID is not a function !\n");
                    }

                    if ((yyvsp[(3) - (4)].args)->size() != tmp->arg_val.size()){
                        yyerror("Wrong argument size !\n");
                    }

                    for (int i = 0; i < (yyvsp[(3) - (4)].args)->size(); i++){
                        if((*(yyvsp[(3) - (4)].args))[i]->type != tmp->arg_val[i]->type){
                            yyerror("exist argument's type error");
                        }
                    }

                    (yyval.type) = tmp->returnType;

                    javafile << "\t\tinvokestatic int " << classID << "." << *(yyvsp[(1) - (4)].sval) << "(";

                    for (int i = (yyvsp[(3) - (4)].args)->size() - 1; i >= 0; i--){
                        if(i == (yyvsp[(3) - (4)].args)->size() - 1){
                            javafile << getVALTypeStr((*(yyvsp[(3) - (4)].args))[i]->type);
                        }
                        else{
                            javafile << "," << getVALTypeStr((*(yyvsp[(3) - (4)].args))[i]->type);
                        }
                    }

                    javafile << ")" << endl;
                }
            }
    break;

  case 77:
#line 943 "parser.y"
    {
                vector<ValueDetail*>* tmp = new vector<ValueDetail*>();
                tmp->push_back((yyvsp[(1) - (1)].arg));
                (yyval.args) = tmp;
            }
    break;

  case 78:
#line 950 "parser.y"
    {
                (yyvsp[(3) - (3)].args)->push_back((yyvsp[(1) - (3)].arg));
                (yyval.args) = (yyvsp[(3) - (3)].args);
            }
    break;

  case 79:
#line 956 "parser.y"
    {
                (yyval.args) = new vector<ValueDetail*>();
            }
    break;

  case 80:
#line 964 "parser.y"
    {
                my_tables.push();
            }
    break;

  case 81:
#line 967 "parser.y"
    {   
                Trace("Reducing Block\n");
                my_tables.dump();
                my_tables.pop();
            }
    break;

  case 85:
#line 982 "parser.y"
    {
                IFEnd();
            }
    break;

  case 86:
#line 986 "parser.y"
    {
                ELSEStart();
            }
    break;

  case 88:
#line 994 "parser.y"
    {
                Trace("IF ( EXPR )\n");
                if ((yyvsp[(3) - (4)].arg)->type != BOOL_type){
                    yyerror("Conditional expression must be Boolean !\n");
                }

                if (!elifFLAG){
                    IFStart();
                }
                else{
                    ELIFStart();
                }

                elifFLAG = false;
            }
    break;

  case 89:
#line 1009 "parser.y"
    {
                IFScope();
            }
    break;

  case 90:
#line 1015 "parser.y"
    {
                elifFLAG = true;
            }
    break;

  case 92:
#line 1019 "parser.y"
    {
                ELSEEnd();
            }
    break;

  case 97:
#line 1045 "parser.y"
    {
                WHILEStart();
            }
    break;

  case 98:
#line 1048 "parser.y"
    {
                Trace("WHILE ( EXPR )\n");
                if ((yyvsp[(4) - (5)].arg)->type != BOOL_type){
                    yyerror("Conditional expression must be Boolean !\n");
                }

                WHILEBeforeScope();
            }
    break;

  case 99:
#line 1056 "parser.y"
    {
                WHILEScope();
                WHILEEnd();
            }
    break;

  case 100:
#line 1065 "parser.y"
    {
                Trace("FOR ( ID < - INT TO INT )\n");
                IDDetail* tmp = new IDDetail();
                tmp = my_tables.lookup(*(yyvsp[(3) - (9)].sval));
                if(tmp->type != VAR_type){
                    yyerror("This ID must be variable type !\n");
                }
            }
    break;


/* Line 1267 of yacc.c.  */
#line 2723 "y.tab.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 1087 "parser.y"


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

