/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "./syntax.y" /* yacc.c:339  */

    #include <stdio.h>
    #include "syntaxTree.h"
    #include "lex.yy.c"
    extern int syntax_errs;
    extern int yylineno;
    extern char* yytext;
    int yyerr_line=0;
    void yyerror(const char *msg);
    int yylex();
    extern Node root;

#line 79 "./syntax.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "syntax.tab.h".  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    FLOAT = 259,
    ID = 260,
    SEMI = 261,
    COMMA = 262,
    ASSIGNOP = 263,
    RELOP = 264,
    PLUS = 265,
    MINUS = 266,
    STAR = 267,
    DIV = 268,
    AND = 269,
    OR = 270,
    NOT = 271,
    DOT = 272,
    TYPE = 273,
    LP = 274,
    RP = 275,
    LB = 276,
    RB = 277,
    LC = 278,
    RC = 279,
    STRUCT = 280,
    RETURN = 281,
    IF = 282,
    ELSE = 283,
    WHILE = 284,
    UMINUS = 285,
    LOWER_THAN_ELSE = 286
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 16 "./syntax.y" /* yacc.c:355  */

    struct treenode_* node;

#line 155 "./syntax.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 186 "./syntax.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   487

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  87
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  155

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    60,    60,    65,    68,    70,    73,    76,    79,    80,
      81,    82,    84,    87,    92,    95,    99,   102,   105,   107,
     110,   112,   117,   120,   124,   127,   131,   134,   138,   143,
     147,   150,   152,   155,   158,   161,   164,   167,   170,   171,
     172,   173,   174,   175,   178,   181,   183,   186,   187,   189,
     192,   196,   199,   204,   207,   210,   213,   216,   219,   222,
     225,   228,   231,   234,   237,   240,   243,   246,   249,   252,
     255,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   273,   276,   279
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "ID", "SEMI", "COMMA",
  "ASSIGNOP", "RELOP", "PLUS", "MINUS", "STAR", "DIV", "AND", "OR", "NOT",
  "DOT", "TYPE", "LP", "RP", "LB", "RB", "LC", "RC", "STRUCT", "RETURN",
  "IF", "ELSE", "WHILE", "UMINUS", "LOWER_THAN_ELSE", "$accept", "Program",
  "ExtDefList", "ExtDef", "ExtDecList", "Specifier", "StructSpecifier",
  "OptTag", "Tag", "VarDec", "FunDec", "VarList", "ParamDec", "CompSt",
  "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286
};
# endif

#define YYPACT_NINF -42

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-42)))

#define YYTABLE_NINF -32

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       8,    34,   -42,    18,    37,   -42,     8,    86,   -42,   -42,
      -3,   -42,    15,    36,   -42,   -42,   -42,    61,    49,   -42,
      74,    10,    58,    51,    50,    -3,    -3,   -42,   -42,    85,
     -42,    78,    93,   -42,   109,   -42,     3,   110,   102,    59,
     -42,   -42,    99,     9,   183,   192,   357,   101,   104,   -42,
     107,    50,   127,   -42,     5,   -42,    78,   105,   117,   -42,
     112,   -42,   357,   121,   -42,    78,   -42,   -42,   163,   -42,
     100,   -42,   100,   125,   142,   369,   209,   218,   -42,   -42,
     -42,   -42,   235,   244,   261,   270,   287,   296,   313,   322,
     141,   339,   123,   -42,   128,   -42,    -3,   -42,   441,   -42,
     -42,    12,   -42,   384,   138,   -42,   -42,   -42,   -42,   140,
     413,   145,   427,   -42,   441,   -42,   466,   -42,    77,   -42,
      77,   -42,   100,   -42,   100,   -42,   160,   -42,   454,   -42,
     139,   398,   -42,   -42,   357,   -42,   348,   -42,   103,   103,
     103,   103,   -42,   -42,   441,   168,   -42,   148,   150,   -42,
     -42,   103,   103,   -42,   -42
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    14,    20,     0,     2,     0,     0,    15,     9,
      45,     8,    21,     0,    17,     1,     3,     0,    22,     6,
       0,    12,     0,     0,     0,    45,    45,    10,    11,     0,
       5,     0,     0,     7,     0,    22,    51,     0,    49,     0,
      69,    70,    68,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,    44,     0,    25,     0,     0,    27,    13,
       0,    48,     0,     0,    46,     0,    38,    39,     0,    81,
      62,    82,    63,     0,     0,     0,     0,     0,    29,    30,
      40,    32,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    16,    28,    24,     0,    23,    52,    47,
      50,     0,    65,    86,     0,    79,    80,    61,    34,     0,
       0,     0,     0,    71,    53,    74,    56,    75,    57,    76,
      58,    77,    59,    78,    60,    72,    54,    73,    55,    67,
       0,     0,    18,    26,     0,    83,     0,    64,     0,     0,
       0,     0,    84,    66,    87,     0,    85,    41,    35,    43,
      37,     0,     0,    42,    36
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -42,   -42,   174,   -42,   154,     1,   -42,   -42,   -42,    -7,
     -42,    94,   -42,    17,   147,   -39,    46,   -42,   124,   -42,
     -41,    55
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    20,    23,     8,    13,    14,    21,
      22,    57,    58,    49,    50,    51,    24,    25,    37,    38,
      52,   104
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      67,     7,    70,    72,    74,    75,    92,     7,    -4,     1,
      69,    62,    40,    41,    42,     2,    36,    31,    11,   134,
      43,    98,     3,    12,    32,    44,     2,   103,    45,    93,
      56,    32,   135,     3,    28,   110,   112,    15,   -19,    33,
       9,   114,   116,   118,   120,   122,   124,   126,   128,    94,
     131,    39,    34,    40,    41,    42,    35,    10,    36,    26,
      39,    43,    40,    41,    42,    66,    44,    27,    29,    45,
      43,    53,    54,    10,   -31,    44,    46,    47,    45,    48,
      30,    10,    10,    35,    10,    46,    47,    17,    48,    86,
      87,    18,    19,   144,    90,   103,    60,    56,    91,   147,
     148,   149,   150,     2,    39,    55,    40,    41,    42,    65,
       3,    63,   153,   154,    43,    61,    64,    90,    68,    44,
      76,    91,    45,    77,    96,    95,    10,    99,    80,    46,
      47,    78,    48,    81,    97,    82,    83,    84,    85,    86,
      87,    88,    89,   106,    90,   105,   129,   132,    91,    32,
      82,    83,    84,    85,    86,    87,    88,    89,   137,    90,
     138,   142,   107,    91,   101,   140,    40,    41,    42,    83,
      84,    85,    86,    87,    43,   134,   151,    90,   152,    44,
      16,    91,    45,   102,    71,    59,    40,    41,    42,   100,
     133,   146,     0,    73,    43,    40,    41,    42,    79,    44,
       0,     0,    45,    43,     0,     0,     0,     0,    44,     0,
     109,    45,    40,    41,    42,     0,     0,     0,     0,   111,
      43,    40,    41,    42,     0,    44,     0,     0,    45,    43,
       0,     0,     0,     0,    44,     0,   113,    45,    40,    41,
      42,     0,     0,     0,     0,   115,    43,    40,    41,    42,
       0,    44,     0,     0,    45,    43,     0,     0,     0,     0,
      44,     0,   117,    45,    40,    41,    42,     0,     0,     0,
       0,   119,    43,    40,    41,    42,     0,    44,     0,     0,
      45,    43,     0,     0,     0,     0,    44,     0,   121,    45,
      40,    41,    42,     0,     0,     0,     0,   123,    43,    40,
      41,    42,     0,    44,     0,     0,    45,    43,     0,     0,
       0,     0,    44,     0,   125,    45,    40,    41,    42,     0,
       0,     0,     0,   127,    43,    40,    41,    42,     0,    44,
       0,     0,    45,    43,     0,     0,     0,     0,    44,     0,
     130,    45,    40,    41,    42,     0,     0,     0,     0,   145,
      43,    40,    41,    42,     0,    44,     0,     0,    45,    43,
      40,    41,    42,     0,    44,     0,     0,    45,    43,     0,
       0,     0,     0,    44,     0,   108,    45,    82,    83,    84,
      85,    86,    87,    88,    89,     0,    90,     0,     0,     0,
      91,   136,    82,    83,    84,    85,    86,    87,    88,    89,
       0,    90,     0,     0,     0,    91,    82,    83,    84,    85,
      86,    87,    88,    89,     0,    90,     0,     0,     0,    91,
     143,    82,    83,    84,    85,    86,    87,    88,    89,     0,
      90,     0,     0,   139,    91,    82,    83,    84,    85,    86,
      87,    88,    89,     0,    90,     0,     0,   141,    91,    82,
      83,    84,    85,    86,    87,    88,    89,     0,    90,     0,
       0,     0,    91,    83,    84,    85,    86,    87,    88,     0,
       0,    90,     0,     0,     0,    91,    84,    85,    86,    87,
       0,     0,     0,    90,     0,     0,     0,    91
};

static const yytype_int16 yycheck[] =
{
      39,     0,    43,    44,    45,    46,     1,     6,     0,     1,
       1,     8,     3,     4,     5,    18,    23,     7,     1,     7,
      11,    62,    25,     5,    21,    16,    18,    68,    19,    24,
      29,    21,    20,    25,    17,    76,    77,     0,    23,    22,
       6,    82,    83,    84,    85,    86,    87,    88,    89,    56,
      91,     1,     1,     3,     4,     5,     5,    23,    65,    23,
       1,    11,     3,     4,     5,     6,    16,     6,    19,    19,
      11,    25,    26,    23,    24,    16,    26,    27,    19,    29,
       6,    23,    23,     5,    23,    26,    27,     1,    29,    12,
      13,     5,     6,   134,    17,   136,     3,    96,    21,   138,
     139,   140,   141,    18,     1,    20,     3,     4,     5,     7,
      25,     1,   151,   152,    11,     6,     6,    17,    19,    16,
      19,    21,    19,    19,     7,    20,    23,     6,     1,    26,
      27,    24,    29,     6,    22,     8,     9,    10,    11,    12,
      13,    14,    15,     1,    17,    20,     5,    24,    21,    21,
       8,     9,    10,    11,    12,    13,    14,    15,    20,    17,
      20,    22,    20,    21,     1,    20,     3,     4,     5,     9,
      10,    11,    12,    13,    11,     7,    28,    17,    28,    16,
       6,    21,    19,    20,     1,    31,     3,     4,     5,    65,
      96,   136,    -1,     1,    11,     3,     4,     5,    51,    16,
      -1,    -1,    19,    11,    -1,    -1,    -1,    -1,    16,    -1,
       1,    19,     3,     4,     5,    -1,    -1,    -1,    -1,     1,
      11,     3,     4,     5,    -1,    16,    -1,    -1,    19,    11,
      -1,    -1,    -1,    -1,    16,    -1,     1,    19,     3,     4,
       5,    -1,    -1,    -1,    -1,     1,    11,     3,     4,     5,
      -1,    16,    -1,    -1,    19,    11,    -1,    -1,    -1,    -1,
      16,    -1,     1,    19,     3,     4,     5,    -1,    -1,    -1,
      -1,     1,    11,     3,     4,     5,    -1,    16,    -1,    -1,
      19,    11,    -1,    -1,    -1,    -1,    16,    -1,     1,    19,
       3,     4,     5,    -1,    -1,    -1,    -1,     1,    11,     3,
       4,     5,    -1,    16,    -1,    -1,    19,    11,    -1,    -1,
      -1,    -1,    16,    -1,     1,    19,     3,     4,     5,    -1,
      -1,    -1,    -1,     1,    11,     3,     4,     5,    -1,    16,
      -1,    -1,    19,    11,    -1,    -1,    -1,    -1,    16,    -1,
       1,    19,     3,     4,     5,    -1,    -1,    -1,    -1,     1,
      11,     3,     4,     5,    -1,    16,    -1,    -1,    19,    11,
       3,     4,     5,    -1,    16,    -1,    -1,    19,    11,    -1,
      -1,    -1,    -1,    16,    -1,     6,    19,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    17,    -1,    -1,    -1,
      21,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    17,    -1,    -1,    -1,    21,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    17,    -1,    -1,    -1,    21,
      22,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      17,    -1,    -1,    20,    21,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    17,    -1,    -1,    20,    21,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    17,    -1,
      -1,    -1,    21,     9,    10,    11,    12,    13,    14,    -1,
      -1,    17,    -1,    -1,    -1,    21,    10,    11,    12,    13,
      -1,    -1,    -1,    17,    -1,    -1,    -1,    21
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    18,    25,    33,    34,    35,    37,    38,     6,
      23,    45,     5,    39,    40,     0,    34,     1,     5,     6,
      36,    41,    42,    37,    48,    49,    23,     6,    45,    19,
       6,     7,    21,    45,     1,     5,    41,    50,    51,     1,
       3,     4,     5,    11,    16,    19,    26,    27,    29,    45,
      46,    47,    52,    48,    48,    20,    37,    43,    44,    36,
       3,     6,     8,     1,     6,     7,     6,    47,    19,     1,
      52,     1,    52,     1,    52,    52,    19,    19,    24,    46,
       1,     6,     8,     9,    10,    11,    12,    13,    14,    15,
      17,    21,     1,    24,    41,    20,     7,    22,    52,     6,
      50,     1,    20,    52,    53,    20,     1,    20,     6,     1,
      52,     1,    52,     1,    52,     1,    52,     1,    52,     1,
      52,     1,    52,     1,    52,     1,    52,     1,    52,     5,
       1,    52,    24,    43,     7,    20,     7,    20,    20,    20,
      20,    20,    22,    22,    52,     1,    53,    47,    47,    47,
      47,    28,    28,    47,    47
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    35,    35,    35,
      35,    35,    36,    36,    37,    37,    38,    38,    38,    39,
      39,    40,    41,    41,    42,    42,    43,    43,    44,    45,
      46,    46,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    48,    48,    49,    49,    49,    50,
      50,    51,    51,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    53,    53,    53
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     2,     2,
       3,     3,     1,     3,     1,     1,     5,     2,     6,     1,
       0,     1,     1,     4,     4,     3,     3,     1,     2,     4,
       2,     0,     2,     1,     3,     5,     7,     5,     2,     2,
       2,     5,     7,     5,     2,     0,     3,     4,     3,     1,
       3,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     4,     3,     4,     3,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     4,     4,     3,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 60 "./syntax.y" /* yacc.c:1646  */
    { 
    (yyval.node)=nonterminal_node("Program",(yyloc).first_line,1,(yyvsp[0].node));
    root=(yyval.node); 
}
#line 1529 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 65 "./syntax.y" /* yacc.c:1646  */
    { 
    (yyval.node)=nonterminal_node("ExtDefList",(yyloc).first_line,2,(yyvsp[-1].node),(yyvsp[0].node)); 
}
#line 1537 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 68 "./syntax.y" /* yacc.c:1646  */
    { (yyval.node)=NULL; }
#line 1543 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 70 "./syntax.y" /* yacc.c:1646  */
    { 
    (yyval.node)=nonterminal_node("ExtDef",(yyloc).first_line,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
}
#line 1551 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 73 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("ExtDef",(yyloc).first_line,2,(yyvsp[-1].node),(yyvsp[0].node)); 
    }
#line 1559 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 76 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("ExtDef",(yyloc).first_line,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
    }
#line 1567 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 79 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1573 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 80 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1579 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 81 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1585 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 82 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1591 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 84 "./syntax.y" /* yacc.c:1646  */
    { 
    (yyval.node)=nonterminal_node("ExtDecList",(yyloc).first_line,1,(yyvsp[0].node)); 
}
#line 1599 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 87 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("ExtDecList",(yyloc).first_line,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
    }
#line 1607 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 92 "./syntax.y" /* yacc.c:1646  */
    { 
    (yyval.node)=nonterminal_node("Specifier",(yyloc).first_line,1,(yyvsp[0].node)); 
    }
#line 1615 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 95 "./syntax.y" /* yacc.c:1646  */
    {
        (yyval.node)=nonterminal_node("Specifier",(yyloc).first_line,1,(yyvsp[0].node)); 
    }
#line 1623 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 99 "./syntax.y" /* yacc.c:1646  */
    { 
    (yyval.node)=nonterminal_node("StructSpecifier",(yyloc).first_line,5,(yyvsp[-4].node),(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
    }
#line 1631 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 102 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("StructSpecifier",(yyloc).first_line,2,(yyvsp[-1].node),(yyvsp[0].node)); 
    }
#line 1639 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 105 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1645 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 107 "./syntax.y" /* yacc.c:1646  */
    { 
    (yyval.node)=nonterminal_node("OptTag",(yyloc).first_line,1,(yyvsp[0].node)); 
    }
#line 1653 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 110 "./syntax.y" /* yacc.c:1646  */
    { (yyval.node)=NULL; }
#line 1659 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 112 "./syntax.y" /* yacc.c:1646  */
    { 
    (yyval.node)=nonterminal_node("Tag",(yyloc).first_line,1,(yyvsp[0].node)); 
}
#line 1667 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 117 "./syntax.y" /* yacc.c:1646  */
    { 
    (yyval.node)=nonterminal_node("VarDec",(yyloc).first_line,1,(yyvsp[0].node)); 
}
#line 1675 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 120 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("VarDec",(yyloc).first_line,4,(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
    }
#line 1683 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 124 "./syntax.y" /* yacc.c:1646  */
    { 
    (yyval.node)=nonterminal_node("FunDec",(yyloc).first_line,4,(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
}
#line 1691 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 127 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("FunDec",(yyloc).first_line,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
    }
#line 1699 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 131 "./syntax.y" /* yacc.c:1646  */
    { 
    (yyval.node)=nonterminal_node("VarList",(yyloc).first_line,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
}
#line 1707 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 134 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("VarList",(yyloc).first_line,1,(yyvsp[0].node)); 
    }
#line 1715 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 138 "./syntax.y" /* yacc.c:1646  */
    { 
    (yyval.node)=nonterminal_node("ParamDec",(yyloc).first_line,2,(yyvsp[-1].node),(yyvsp[0].node)); 
}
#line 1723 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 143 "./syntax.y" /* yacc.c:1646  */
    { 
    (yyval.node)=nonterminal_node("CompSt",(yyloc).first_line,4,(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
}
#line 1731 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 147 "./syntax.y" /* yacc.c:1646  */
    { 
    (yyval.node)=nonterminal_node("StmtList",(yyloc).first_line,2,(yyvsp[-1].node),(yyvsp[0].node)); 
}
#line 1739 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 150 "./syntax.y" /* yacc.c:1646  */
    { (yyval.node)=NULL; }
#line 1745 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 152 "./syntax.y" /* yacc.c:1646  */
    { 
    (yyval.node)=nonterminal_node("Stmt",(yyloc).first_line,2,(yyvsp[-1].node),(yyvsp[0].node)); 
}
#line 1753 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 155 "./syntax.y" /* yacc.c:1646  */
    {
        (yyval.node)=nonterminal_node("Stmt",(yyloc).first_line,1,(yyvsp[0].node)); 
    }
#line 1761 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 158 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("Stmt",(yyloc).first_line,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
    }
#line 1769 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 161 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("Stmt",(yyloc).first_line,5,(yyvsp[-4].node),(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
    }
#line 1777 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 164 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("Stmt",(yyloc).first_line,7,(yyvsp[-6].node),(yyvsp[-5].node),(yyvsp[-4].node),(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
    }
#line 1785 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 167 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("Stmt",(yyloc).first_line,5,(yyvsp[-4].node),(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
    }
#line 1793 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 170 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1799 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 171 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1805 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 172 "./syntax.y" /* yacc.c:1646  */
    {}
#line 1811 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 173 "./syntax.y" /* yacc.c:1646  */
    {}
#line 1817 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 174 "./syntax.y" /* yacc.c:1646  */
    {}
#line 1823 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 175 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1829 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 178 "./syntax.y" /* yacc.c:1646  */
    { 
    (yyval.node)=nonterminal_node("DefList",(yyloc).first_line,2,(yyvsp[-1].node),(yyvsp[0].node)); 
}
#line 1837 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 181 "./syntax.y" /* yacc.c:1646  */
    { (yyval.node)=NULL; }
#line 1843 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 183 "./syntax.y" /* yacc.c:1646  */
    { 
    (yyval.node)=nonterminal_node("Def",(yyloc).first_line,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
}
#line 1851 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 186 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1857 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 187 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1863 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 189 "./syntax.y" /* yacc.c:1646  */
    { 
    (yyval.node)=nonterminal_node("DecList",(yyloc).first_line,1,(yyvsp[0].node)); 
}
#line 1871 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 192 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("DecList",(yyloc).first_line,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
    }
#line 1879 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 196 "./syntax.y" /* yacc.c:1646  */
    { 
    (yyval.node)=nonterminal_node("Dec",(yyloc).first_line,1,(yyvsp[0].node)); 
}
#line 1887 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 199 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("Dec",(yyloc).first_line,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
    }
#line 1895 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 204 "./syntax.y" /* yacc.c:1646  */
    { 
    (yyval.node)=nonterminal_node("Exp",(yyloc).first_line,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
}
#line 1903 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 207 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("Exp",(yyloc).first_line,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
    }
#line 1911 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 210 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("Exp",(yyloc).first_line,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
    }
#line 1919 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 213 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("Exp",(yyloc).first_line,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
    }
#line 1927 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 216 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("Exp",(yyloc).first_line,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
    }
#line 1935 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 219 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("Exp",(yyloc).first_line,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
    }
#line 1943 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 222 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("Exp",(yyloc).first_line,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
    }
#line 1951 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 225 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("Exp",(yyloc).first_line,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
    }
#line 1959 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 228 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("Exp",(yyloc).first_line,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
    }
#line 1967 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 231 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("Exp",(yyloc).first_line,2,(yyvsp[-1].node),(yyvsp[0].node)); 
    }
#line 1975 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 234 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("Exp",(yyloc).first_line,2,(yyvsp[-1].node),(yyvsp[0].node)); 
    }
#line 1983 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 237 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("Exp",(yyloc).first_line,4,(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
    }
#line 1991 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 240 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("Exp",(yyloc).first_line,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
    }
#line 1999 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 243 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("Exp",(yyloc).first_line,4,(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
    }
#line 2007 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 246 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("Exp",(yyloc).first_line,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
    }
#line 2015 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 249 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("Exp",(yyloc).first_line,1,(yyvsp[0].node)); 
    }
#line 2023 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 252 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("Exp",(yyloc).first_line,1,(yyvsp[0].node)); 
    }
#line 2031 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 255 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("Exp",(yyloc).first_line,1,(yyvsp[0].node));
    }
#line 2039 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 258 "./syntax.y" /* yacc.c:1646  */
    {}
#line 2045 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 259 "./syntax.y" /* yacc.c:1646  */
    {}
#line 2051 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 260 "./syntax.y" /* yacc.c:1646  */
    {}
#line 2057 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 261 "./syntax.y" /* yacc.c:1646  */
    {}
#line 2063 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 262 "./syntax.y" /* yacc.c:1646  */
    {}
#line 2069 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 263 "./syntax.y" /* yacc.c:1646  */
    {}
#line 2075 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 264 "./syntax.y" /* yacc.c:1646  */
    {}
#line 2081 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 265 "./syntax.y" /* yacc.c:1646  */
    {}
#line 2087 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 266 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 2093 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 267 "./syntax.y" /* yacc.c:1646  */
    {}
#line 2099 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 268 "./syntax.y" /* yacc.c:1646  */
    {}
#line 2105 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 269 "./syntax.y" /* yacc.c:1646  */
    {}
#line 2111 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 270 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 2117 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 271 "./syntax.y" /* yacc.c:1646  */
    { yyerrok; }
#line 2123 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 273 "./syntax.y" /* yacc.c:1646  */
    { 
    (yyval.node)=nonterminal_node("Args",(yyloc).first_line,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node)); 
}
#line 2131 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 276 "./syntax.y" /* yacc.c:1646  */
    { 
        (yyval.node)=nonterminal_node("Args",(yyloc).first_line,1,(yyvsp[0].node));
    }
#line 2139 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 279 "./syntax.y" /* yacc.c:1646  */
    {}
#line 2145 "./syntax.tab.c" /* yacc.c:1646  */
    break;


#line 2149 "./syntax.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
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

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
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
  return yyresult;
}
#line 281 "./syntax.y" /* yacc.c:1906  */


void yyerror(const char *msg) {
    if(yyerr_line == yylineno)return;
    yyerr_line=yylineno;
    syntax_errs++;
    printf("Error type B at Line %d: %s\n", yylineno, msg);
}
