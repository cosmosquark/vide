/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "SDF-parse.y"

/*
    SDF Library for reading Self-Describing Files
    Copyright (C) 1991,1992  John K. Salmon

    Terms and conditions are specified in the file "copyright.h",
    and more precisely in the file COPYING.LIB which you should have
    received with this library.
*/

/* We don't rely on bison's -p argument any more.  
   Instead, just #define the name changes ourselves.  These are taken
   from the beginning of bison -p output.  These are far from a complete
   set of external 'yy' names, as a quick run throug 'nm' will show.  Maybe
   all the others come from lex.  I dunno.  In any event, the namespace is only
   partially cleaned up.  Perhaps we should apply for Superfund money
   to finish the cleanup?  bison -p does no better.
*/
#define yyparse SDFyyparse
#define yylex SDFyylex
#define yyerror SDFyyerror
#define yylval SDFyylval
#define yychar SDFyychar
#define yydebug SDFyydebug
#define yynerrs SDFyynerrs

#include <stdarg.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>
#include "protos.h"
#include "Msgs.h"
#include "SDF-private.h"
#include "obstack.h"
#include "Malloc.h"

#ifndef __DELTA__
#define YYDEBUG 1
#endif

#if YYDEBUG
/* yacc sends its debug output throught printf.  We change that... */
#define printf Msg_do		/* MUST be after protos.h!!! */
#endif

#ifdef cray
/* This wants to be a long on the cray?? */
extern long int yydebug;
#else
extern int yydebug;
#endif
extern void yyerror(char *fmt, ...);


static enum SDF_type_enum curtype;
static blk_descrip_t cur_blk;
static int cur_file_offset;
static int cur_data_offset;
static SDF  *cur_hdr;
static int no_more_data_blks;
static int zero_len_blknum;

char *SDFtype_names[] = {"notype", "char", "short", "int", "long", "int64_t",
			 "float", "double", "string"};

 int SDFtype_sizes[] = {0, sizeof(char), sizeof(short), sizeof(int), sizeof(long),
			sizeof(int64_t), sizeof(float), sizeof(double), sizeof(char *)};

static int do_value_param(enum value_param_enum type, const_t value);
static int data_dcl(declaration_t dcl);
static int const_dcl(declaration_t dcl, const_list_t consts);
static void finish_curblk(void);
static const_t convert_const(const_t *cp, enum SDF_type_enum type);
static int finish_parse(void);



/* Line 268 of yacc.c  */
#line 149 "y.tab.c"

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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     STRUCT = 258,
     NAME = 259,
     TYPE = 260,
     CONST = 261,
     VALUEPARAM = 262,
     PARAMETER = 263,
     EOHDR = 264,
     LEXERROR = 265
   };
#endif
/* Tokens.  */
#define STRUCT 258
#define NAME 259
#define TYPE 260
#define CONST 261
#define VALUEPARAM 262
#define PARAMETER 263
#define EOHDR 264
#define LEXERROR 265




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 90 "SDF-parse.y"

    enum SDF_type_enum type;
    enum value_param_enum valueparam;
    char *string;
    const_t constant;
    declaration_t declaration;
    dcl_list_t dcl_list;
    one_dcl_t one_dcl;
    const_list_t const_list;



/* Line 293 of yacc.c  */
#line 218 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 230 "y.tab.c"

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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
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
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   44

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  18
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  12
/* YYNRULES -- Number of rules.  */
#define YYNRULES  26
/* YYNRULES -- Number of states.  */
#define YYNSTATES  48

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   265

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    17,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    11,
       2,    12,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    13,     2,    14,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    15,     2,    16,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    15,    18,    23,
      29,    31,    37,    46,    54,    56,    60,    61,    65,    67,
      71,    73,    78,    82,    84,    88,    90
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      19,     0,    -1,    20,    -1,    20,     9,    -1,    10,    -1,
      21,    -1,    20,    21,    -1,    22,    11,    -1,    22,    12,
      28,    11,    -1,     8,     7,    12,     6,    11,    -1,    24,
      -1,     3,    15,    23,    11,    16,    -1,     3,    15,    23,
      11,    16,    13,     6,    14,    -1,     3,    15,    23,    11,
      16,    13,    14,    -1,    24,    -1,    23,    11,    24,    -1,
      -1,     5,    25,    26,    -1,    27,    -1,    26,    17,    27,
      -1,     4,    -1,     4,    13,     6,    14,    -1,     4,    13,
      14,    -1,     6,    -1,    15,    29,    16,    -1,     6,    -1,
      29,    17,     6,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   101,   101,   102,   103,   106,   107,   110,   111,   112,
     115,   116,   117,   126,   130,   131,   143,   143,   146,   152,
     160,   161,   170,   173,   179,   182,   188
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "STRUCT", "NAME", "TYPE", "CONST",
  "VALUEPARAM", "PARAMETER", "EOHDR", "LEXERROR", "';'", "'='", "'['",
  "']'", "'{'", "'}'", "','", "$accept", "hdr", "hdr1", "stmt",
  "declaration", "many_typed_dcl_list", "typed_dcl_list", "$@1",
  "comma_sep_dcls", "dcl1", "const_lst", "comma_sep_consts", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,    59,    61,    91,    93,   123,   125,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    18,    19,    19,    19,    20,    20,    21,    21,    21,
      22,    22,    22,    22,    23,    23,    25,    24,    26,    26,
      27,    27,    27,    28,    28,    29,    29
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     2,     2,     4,     5,
       1,     5,     8,     7,     1,     3,     0,     3,     1,     3,
       1,     4,     3,     1,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    16,     0,     4,     0,     2,     5,     0,    10,
       0,     0,     0,     1,     3,     6,     7,     0,     0,    14,
      20,    17,    18,     0,    23,     0,     0,     0,     0,     0,
       0,    25,     0,     8,    11,    15,     0,    22,    19,     9,
      24,     0,     0,    21,    26,     0,    13,    12
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,     7,     8,    18,     9,    11,    21,    22,
      26,    32
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -14
static const yytype_int8 yypact[] =
{
      13,   -13,   -14,     2,   -14,     5,    17,   -14,    16,   -14,
      10,     6,     7,   -14,   -14,   -14,   -14,    -2,    18,   -14,
      11,    14,   -14,    24,   -14,    26,    22,    -4,    -3,     6,
      23,   -14,    -9,   -14,    25,   -14,    21,   -14,   -14,   -14,
     -14,    30,     0,   -14,   -14,    27,   -14,   -14
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -14,   -14,   -14,    31,   -14,   -14,   -10,   -14,   -14,    15,
     -14,   -14
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      19,     2,    10,    36,    24,    13,    45,    40,    41,    12,
      20,    37,    34,    25,    46,     2,     1,    35,     2,    23,
       1,     3,     2,     4,    28,     3,    14,    16,    17,    27,
      30,    29,    31,    33,    39,    43,    44,    15,    42,     0,
       0,    47,     0,     0,    38
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-14))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      10,     5,    15,     6,     6,     0,     6,    16,    17,     7,
       4,    14,    16,    15,    14,     5,     3,    27,     5,    12,
       3,     8,     5,    10,    13,     8,     9,    11,    12,    11,
       6,    17,     6,    11,    11,    14,     6,     6,    13,    -1,
      -1,    14,    -1,    -1,    29
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     8,    10,    19,    20,    21,    22,    24,
      15,    25,     7,     0,     9,    21,    11,    12,    23,    24,
       4,    26,    27,    12,     6,    15,    28,    11,    13,    17,
       6,     6,    29,    11,    16,    24,     6,    14,    27,    11,
      16,    17,    13,    14,     6,     6,    14,    14
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
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


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

/* Line 1806 of yacc.c  */
#line 101 "SDF-parse.y"
    {if(finish_parse()) YYERROR;}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 102 "SDF-parse.y"
    {if(finish_parse()) YYERROR; else YYACCEPT;}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 103 "SDF-parse.y"
    {YYERROR;}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 110 "SDF-parse.y"
    {if(data_dcl((yyvsp[(1) - (2)].declaration))) YYERROR;}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 111 "SDF-parse.y"
    {if(const_dcl((yyvsp[(1) - (4)].declaration), (yyvsp[(3) - (4)].const_list))) YYERROR;}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 112 "SDF-parse.y"
    {if(do_value_param((yyvsp[(2) - (5)].valueparam), (yyvsp[(4) - (5)].constant))) YYERROR;}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 115 "SDF-parse.y"
    {(yyval.declaration).dcl_list = (yyvsp[(1) - (1)].dcl_list); (yyval.declaration).Nrec = 1;}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 116 "SDF-parse.y"
    {(yyval.declaration).dcl_list=(yyvsp[(3) - (5)].dcl_list); (yyval.declaration).Nrec=1;}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 118 "SDF-parse.y"
    {
	    if( (yyvsp[(7) - (8)].constant).type != SDF_INT64 ){
		yyerror("Expected integer constant");
		YYERROR;
	    }else{
		(yyval.declaration).dcl_list = (yyvsp[(3) - (8)].dcl_list); (yyval.declaration).Nrec = (yyvsp[(7) - (8)].constant).u.int64val;
	    }
	}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 127 "SDF-parse.y"
    { (yyval.declaration).dcl_list = (yyvsp[(3) - (7)].dcl_list); (yyval.declaration).Nrec = 0;}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 130 "SDF-parse.y"
    {(yyval.dcl_list) = (yyvsp[(1) - (1)].dcl_list);}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 132 "SDF-parse.y"
    {
	    int sz;

	    (yyval.dcl_list).ndcl = (yyvsp[(1) - (3)].dcl_list).ndcl + (yyvsp[(3) - (3)].dcl_list).ndcl;
	    (yyval.dcl_list).obs = (yyvsp[(1) - (3)].dcl_list).obs;
	    sz = obstack_object_size(&(yyvsp[(3) - (3)].dcl_list).obs);
	    (void)obstack_grow(&(yyval.dcl_list).obs, obstack_finish(&(yyvsp[(3) - (3)].dcl_list).obs), sz);
	    (void)obstack_free(&(yyvsp[(3) - (3)].dcl_list).obs, NULL);
	}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 143 "SDF-parse.y"
    {curtype = (yyvsp[(1) - (1)].type);}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 143 "SDF-parse.y"
    {(yyval.dcl_list) = (yyvsp[(3) - (3)].dcl_list);}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 147 "SDF-parse.y"
    {
	    obstack_begin(&(yyval.dcl_list).obs, 16*sizeof((yyvsp[(1) - (1)].one_dcl)));
	    (yyval.dcl_list).ndcl = 1;
	    (void)obstack_grow(&(yyval.dcl_list).obs, &(yyvsp[(1) - (1)].one_dcl), sizeof((yyvsp[(1) - (1)].one_dcl)));
	}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 153 "SDF-parse.y"
    {
	    (yyval.dcl_list) = (yyvsp[(1) - (3)].dcl_list);
	    (yyval.dcl_list).ndcl += 1;
	    (void)obstack_grow(&(yyval.dcl_list).obs, &(yyvsp[(3) - (3)].one_dcl), sizeof((yyvsp[(3) - (3)].one_dcl)));
	}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 160 "SDF-parse.y"
    {(yyval.one_dcl).name = (yyvsp[(1) - (1)].string); (yyval.one_dcl).type = curtype; (yyval.one_dcl).arrcnt = 1;}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 162 "SDF-parse.y"
    {
	    if( (yyvsp[(3) - (4)].constant).type != SDF_INT64 ){
		yyerror("Expected integer constant");
		YYERROR;
	    }else{
		(yyval.one_dcl).name = (yyvsp[(1) - (4)].string); (yyval.one_dcl).type = curtype; (yyval.one_dcl).arrcnt = (yyvsp[(3) - (4)].constant).u.int64val;
	    }
	}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 170 "SDF-parse.y"
    {(yyval.one_dcl).name=(yyvsp[(1) - (3)].string); (yyval.one_dcl).type=curtype; (yyval.one_dcl).arrcnt = 0;}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 174 "SDF-parse.y"
    { 
	    (yyval.const_list).nconst = 1; 
	    obstack_begin(&(yyval.const_list).obs, 16*sizeof((yyvsp[(1) - (1)].constant))); 
	    (void)obstack_grow(&(yyval.const_list).obs, &(yyvsp[(1) - (1)].constant), sizeof((yyvsp[(1) - (1)].constant)));
	}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 179 "SDF-parse.y"
    {(yyval.const_list) = (yyvsp[(2) - (3)].const_list);}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 183 "SDF-parse.y"
    { 
	    (yyval.const_list).nconst = 1; 
	    obstack_begin(&(yyval.const_list).obs, 16*sizeof((yyvsp[(1) - (1)].constant))); 
	    (void)obstack_grow(&(yyval.const_list).obs, &(yyvsp[(1) - (1)].constant), sizeof((yyvsp[(1) - (1)].constant)));
	}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 189 "SDF-parse.y"
    {
	    (yyval.const_list) = (yyvsp[(1) - (3)].const_list);
	    (yyval.const_list).nconst += 1;
	    (void)obstack_grow(&(yyval.const_list).obs, &(yyvsp[(3) - (3)].constant), sizeof((yyvsp[(3) - (3)].constant)));
	}
    break;



/* Line 1806 of yacc.c  */
#line 1686 "y.tab.c"
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
		      yytoken, &yylval);
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
                  yytoken, &yylval);
    }
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



/* Line 2067 of yacc.c  */
#line 196 "SDF-parse.y"

static int SDFlineno;

static const char *Dataname, *Hdrname;

#ifdef STANDALONE
char SDFerrstring[512];
unsigned int SDFcpubyteorder(void){return 0;}

main(int argc, char **argv)
{
    SDF hdr;

    if(argc > 1){
	yydebug = 1;
    }else{
	yydebug = 0;
    }
    SDFyyprepare(&hdr, "-", "-");
    if(yyparse()){
	printf("Terminated on error. \n");
	exit(1);
    }
    exit(0);
}
#endif

static int SDF_iomode = MPMY_RDONLY | MPMY_MULTI;

void SDFsetiomode(int mode)
{
    if (mode == SDF_SINGL) {
	SDF_iomode = MPMY_RDONLY | MPMY_SINGL;
    } else {
	SDF_iomode = MPMY_RDONLY | MPMY_MULTI;
    }
}
 


void SDFyyerror(char *fmt, ...)
{
    char *p;
    va_list ap;

    va_start(ap, fmt);
    vsprintf(SDFerrstring, fmt, ap);
    p = SDFerrstring + strlen(SDFerrstring);
    sprintf(p, " lineno = %d\n", SDFlineno);
    va_end(ap);
}

int SDFyyprepare(SDF *hdr, const char *hdrname, const char *dataname)
{
    no_more_data_blks = 0;

    cur_file_offset = 0;
    cur_data_offset = 0;

    cur_blk.Nrec = 1;
    cur_blk.inmem = 1;
    cur_blk.begin_offset = 0;
    cur_blk.reclen = 0;

    cur_hdr = hdr;
    cur_hdr->nblks = 0;
    cur_hdr->nvecs = 0;
    /* Assume that MPMY_Fopen does the 'right' thing with "-" */
    if( SDF_Hdropen(hdrname) < 0 ){
	sprintf(SDFerrstring, "SDFopen: could not open %s\n", hdrname);
	return -1;
    }
    Dataname = dataname;
    Hdrname = hdrname;
    SDFlineno = 0;		/* or 1?  It's always +-1 anyway */
    SDFlexprepare();

    obstack_begin(&cur_hdr->blks_obs, 16*sizeof(blk_descrip_t));
    obstack_begin(&cur_hdr->vecs_obs, 32*sizeof(vec_descrip_t));
    obstack_begin(&cur_hdr->data_obs, 2048);
    return 0;
}

static int finish_parse(void)
{
    int i;

    finish_curblk();
    cur_hdr->blks = (blk_descrip_t *)obstack_finish(&cur_hdr->blks_obs);
    cur_hdr->vecs = (vec_descrip_t *)obstack_finish(&cur_hdr->vecs_obs);
    cur_hdr->data = obstack_finish(&cur_hdr->data_obs);
    cur_hdr->vec_names = Malloc(cur_hdr->nvecs * sizeof(char *));
    for(i=0; i<cur_hdr->nvecs; i++){
	cur_hdr->vec_names[i] = cur_hdr->vecs[i].name;
    }

    if( (Dataname == NULL) || (Dataname[0] == '\0')
       || (strcmp(Hdrname, Dataname)==0)){
	cur_hdr->begin_file_offset = SDF_Hdroffset();
	if( cur_hdr->begin_file_offset < 0 ){
	    yyerror("Can't get offset of end of header\n");
	    return -1;
	}
    }else{
	cur_hdr->begin_file_offset = 0;
    }
    SDF_Hdrclose();

    /* cur_hdr->datafp = MPMY_Fopen(Dataname, MPMY_RDONLY); */
    /* If we come up with a better model for IO, call it here..  */
    cur_hdr->datafp = MPMY_Fopen(Dataname, SDF_iomode);

    Msgf(("cur_hdr->datafp = %p\n", cur_hdr->datafp));

    if( cur_hdr->datafp == NULL ){
	sprintf(SDFerrstring, "SDFopen: could not open data file: %s\n", 
		Dataname);
	return -1;
    }

    if(no_more_data_blks){
	blk_descrip_t *zerolenblk;
	off_t bytesleft, recsleft;
	off_t datalen;

	zerolenblk = &cur_hdr->blks[zero_len_blknum];
	if(zerolenblk->Nrec != 0){
	    yyerror("Zero length block has non-zero length!?\n");
	    return -1;
	}
	if( cur_hdr->begin_file_offset < 0 ){
	    yyerror("Can't have zero-len blk in an unseekable file\n");
	    return -1;
	}
	Msgf(("About to call MPMY_Flen\n"));
	if( (datalen = MPMY_Flen(cur_hdr->datafp)) < 0 ){
	    yyerror("Could not get length of data file.\n");
	    return -1;
	}
	bytesleft = datalen 
	    - (zerolenblk->begin_offset + cur_hdr->begin_file_offset); 
	Msgf(("datalen = %ld, butesleft = %ld\n", 
	      (long)datalen, (long)bytesleft));
	if( bytesleft < 0 ){
	    yyerror("File too short.\n");
	    return -1;
	}
	recsleft = bytesleft/zerolenblk->reclen;
	if( recsleft*zerolenblk->reclen != bytesleft ){
	  printf("datalen is %ld, bytesleft is %ld\n", (long)datalen, (long)bytesleft);
	    yyerror("File ends between record boundaries\n");
	    return -1;
	}
	zerolenblk->Nrec = recsleft;
    }
    return 0;
}

static int do_value_param(enum value_param_enum param, const_t value)
{
    switch(param){
    case BYTEORDER:
	if( value.type != SDF_INT64 )
	    return -1;
	cur_hdr->byteorder = value.u.int64val;
	cur_hdr->swapping = (cur_hdr->byteorder != SDFcpubyteorder());
	break;
    }
    return 0;
}
    

static int data_dcl(declaration_t dcl)
{
    dcl_list_t *dcl_list;
    one_dcl_t *base, *dclp;
    int i, offset;
    vec_descrip_t vec_descrip;

#if YYDEBUG
    if(yydebug)
	printf("Declaration of %ld records:\n", dcl.Nrec);
#endif
    if(no_more_data_blks){
	yyerror("You can't have data following an implicit-length dcl.\n");
	return -1;
    }

    /* Test to see if we can append this dcl to the current */
    /* block. */
    if(cur_blk.inmem || cur_blk.Nrec != 1 ||  dcl.Nrec != 1){
	finish_curblk();
	cur_blk.Nrec = dcl.Nrec;
	cur_blk.reclen = 0;
	cur_blk.inmem = 0;
	cur_blk.begin_offset = cur_file_offset;
#if YYDEBUG
	if(yydebug)
	    printf("New block (%d) at offset %d in file\n",
		   cur_hdr->nblks, cur_file_offset);
#endif
    }

    if(dcl.Nrec == 0){
	no_more_data_blks = 1;
	zero_len_blknum = cur_hdr->nblks;
    }
    
    offset = cur_blk.reclen;

    dcl_list = &dcl.dcl_list;
    base = (one_dcl_t *)obstack_base(&dcl_list->obs);
    for(i=0; i<dcl_list->ndcl; i++){
	dclp = &base[i];
	vec_descrip.name = dclp->name;
	vec_descrip.arrcnt = dclp->arrcnt;
	vec_descrip.type = dclp->type;
	vec_descrip.blk_off = offset;
	vec_descrip.blk_num = cur_hdr->nblks;
	vec_descrip.nread = 0;
	offset += SDFtype_sizes[dclp->type] * dclp->arrcnt;
	cur_hdr->nvecs++;
	(void)obstack_grow(&cur_hdr->vecs_obs, 
			   &vec_descrip, sizeof(vec_descrip));
#if YYDEBUG
	if(yydebug){
	    printf("\t %s %s[%d]", SDFtype_names[dclp->type], dclp->name,
		   dclp->arrcnt);
	    printf(" in block %ld at offset %ld\n",
		   vec_descrip.blk_num, vec_descrip.blk_off);
	}
#endif
    }
    (void)obstack_free(&dcl_list->obs, NULL);
    cur_blk.reclen = offset;
    return 0;
}

static void finish_curblk(void)
{
    cur_hdr->nblks++;
    (void)obstack_grow(&cur_hdr->blks_obs, &cur_blk, sizeof(cur_blk));
    if(cur_blk.inmem){
	cur_data_offset += cur_blk.reclen * cur_blk.Nrec;
    }else{
	cur_file_offset += cur_blk.reclen * cur_blk.Nrec;
    }
}

static int const_dcl(declaration_t dcl, const_list_t consts)
{
    dcl_list_t *dcl_list;
    one_dcl_t *dclbase, *dclp;
    const_t *cp, *cbase, converted;
    vec_descrip_t vec_descrip;
    int i, j, k;
    int offset;
    void *to;

    dcl_list = &dcl.dcl_list;
    if(dcl.Nrec == 0){
	dcl.Nrec = consts.nconst;
#if 0 /* Was it really this easy?? */
	yyerror("Cannot deal with implicit length constant dcls.");
	return -1;
#endif
    }

    /* Test to see if we can append this dcl to the current */
    /* block. */
    if(!cur_blk.inmem || cur_blk.Nrec != 1 ||  dcl.Nrec != 1){
	finish_curblk();
	cur_blk.Nrec = dcl.Nrec;
	cur_blk.reclen = 0;
	cur_blk.inmem = 1;
	cur_blk.begin_offset = cur_data_offset;
#if YYDEBUG
	if(yydebug)
	    printf("New block (%d) at offset %d in data\n",
		   cur_hdr->nblks, cur_data_offset);
#endif
    }

    offset = cur_blk.reclen;
    cbase = (const_t *)obstack_base(&consts.obs);
    dclbase = (one_dcl_t *)obstack_base(&dcl_list->obs);

    for(i=0; i<dcl_list->ndcl; i++){
	dclp = &dclbase[i];
	if(dclp->arrcnt == 0){
	    if(dclp->type == SDF_CHAR 
	       && cbase[i].type == SDF_STRING 
	       && dcl.Nrec == 1){
		dclp->arrcnt = strlen(cbase[i].u.stringval)+1;
		/* Round up for padding purposes. */
		dclp->arrcnt = (dclp->arrcnt + 7)& (~0x7);
	    }else if(i == dcl_list->ndcl-1 && dcl.Nrec == 1){
		dclp->arrcnt = consts.nconst - i;
	    }else{
		yyerror("Can't figure out implicit dcl from context.");
		return -1;
	    }
	}

	vec_descrip.name = dclp->name;
	vec_descrip.arrcnt = dclp->arrcnt;
	vec_descrip.type = dclp->type;
	vec_descrip.blk_off = offset;
	vec_descrip.blk_num = cur_hdr->nblks;
	vec_descrip.nread = 0;
	offset += SDFtype_sizes[dclp->type] * dclp->arrcnt;
	cur_hdr->nvecs++;
	(void)obstack_grow(&cur_hdr->vecs_obs, 
		     &vec_descrip, sizeof(vec_descrip));
#if YYDEBUG
	if(yydebug){
	    printf("\t %s %s[%d]", SDFtype_names[dclp->type], dclp->name,
		   dclp->arrcnt);
	    printf(" in block %ld at offset %ld\n",
		   vec_descrip.blk_num, vec_descrip.blk_off);
	}
#endif
    }
    cur_blk.reclen = offset;

    cp = cbase;
    for(i=0; i<dcl.Nrec; i++){
	for(j=0; j<dcl_list->ndcl; j++){
	    dclp = &dclbase[j];
#if YYDEBUG
	    if(yydebug)
		printf("\t %s %s[%d] (%d) = ", 
		       SDFtype_names[dclp->type], dclp->name,
		       dclp->arrcnt, i);
#endif
	    if( dclp->type == SDF_CHAR && cp->type == SDF_STRING){
#if YYDEBUG
		if(yydebug)
		    printf("\"%s\"\n", cp->u.stringval);
#endif
		to = obstack_next_free(&cur_hdr->data_obs);
		(void)obstack_blank(&cur_hdr->data_obs, dclp->arrcnt);
		/* Should we warn 
		   if strlen(cp->u.stringval) > dclp->arrcnt ????
		 It implies that the 'string' won't be null-terminated? */
		(void)strncpy(to, cp->u.stringval, dclp->arrcnt);
#ifdef YYDEBUG
		if(yydebug)
		    printf("Freeing const string 0x%lx\n", 
			   (unsigned long)cp->u.stringval);
#endif
		Free(cp->u.stringval);
		cp++;
		continue;
	    }

	    for(k=0; k<dclp->arrcnt; k++){
		converted = convert_const(cp, dclp->type);
		if(converted.type == SDF_NOTYPE){
		    yyerror("Failed constant conversion.");
		    return -1;
		}
		(void)obstack_grow(&cur_hdr->data_obs, &converted.u, 
			     SDFtype_sizes[converted.type]);

#ifdef YYDEBUG
		if(yydebug){
		    printf("(%s)", SDFtype_names[cp->type]);
		    switch(converted.type){
		    case SDF_CHAR:
			printf("%c", converted.u.charval);
			break;
		    case SDF_SHORT:
			printf("%d", converted.u.shortval);
			break;
		    case SDF_INT:
			printf("%d", converted.u.intval);
			break;
		    case SDF_LONG:
			printf("%ld", converted.u.longval);
			break;
		    case SDF_INT64:
#if __WORDSIZE==64
			printf("%ld", converted.u.int64val);
#else
			printf("%lld", converted.u.int64val);
#endif
			break;
		    case SDF_FLOAT:
			printf("%.7g", converted.u.floatval);
			break;
		    case SDF_DOUBLE:
			printf("%.17g", converted.u.doubleval);
			break;
		    default:
			printf("Unrecognized type: %d\n", converted.type);
			break;
		    }
		    if(k == dclp->arrcnt-1){
			printf("\n");
		    }else{
			printf(", ");
		    }
		}
#endif
		cp++;
	    }
	}
    }
    (void)obstack_free(&dcl_list->obs, NULL);
    (void)obstack_free(&consts.obs, NULL);
    return 0;
}

static const_t convert_const(const_t *cp, enum SDF_type_enum newtype)
/* Return a constant of type NEWTYPE, with the same value as */
/* *CP.  If the conversion does not preserve value, then */
/* return a constant of NOTYPE, with garbage value. */
{
    const_t value;
    double dval = 0.;
    int64_t ival = 0;

    if(cp->type == newtype){
      /* IRIX -32 bug fix */
      memcpy(&value, cp, sizeof(value));
      /* value = *cp; */
      return value;
    }

    if(cp->type == SDF_STRING || newtype == SDF_STRING){
	value.type = SDF_NOTYPE;
	yyerror("Cannot do const conversions with strings.\n");
	return value;
    }

    /* Now rely on the fact that a double can faithfully hold */
    /* any other arithmetic type (except long ints on 64-bit archs). */
    switch(cp->type){
    case SDF_CHAR:
	dval = (double)cp->u.charval;
	break;
    case SDF_SHORT:
	dval = (double)cp->u.shortval;
	break;
    case SDF_INT:
	dval = (double)cp->u.intval;
	ival = cp->u.intval;
	break;
    case SDF_LONG:
	dval = (double)cp->u.longval;
	ival = cp->u.longval;
	break;
    case SDF_INT64:
	dval = (double)cp->u.int64val;
	ival = cp->u.int64val;
	break;
    case SDF_FLOAT:
	dval = cp->u.floatval;
	break;
    case SDF_DOUBLE:
	dval = cp->u.doubleval;
	break;
    default:
	dval = 0.0;
	yyerror("Cannot do const conversions with strings.\n");
    }

    value.type = newtype;
    switch(newtype){
    case SDF_CHAR:
	value.u.charval = (char)dval;
	if( value.u.charval != dval ){
	    yyerror("Can't fit value into char.");
	    value.type = SDF_NOTYPE;
	}
	break;
    case SDF_SHORT:
	value.u.shortval = (short)dval;
	if( value.u.shortval != dval ){
	    yyerror("Can't fit value into short.");
	    value.type = SDF_NOTYPE;
	}
	break;
    case SDF_INT:
	value.u.intval = (int)dval;
	if( value.u.intval != dval ){
	    value.u.intval = ival;
	    if( value.u.intval != ival ){
		yyerror("Can't fit value into int.");
		value.type = SDF_NOTYPE;
	    }
	    break;
	}
	break;
    case SDF_LONG:
	value.u.longval = (long)dval;
	if( value.u.longval != dval ){
	    value.u.longval = ival;
	    if( value.u.longval != ival ){
		yyerror("Can't fit value into long.");
		value.type = SDF_NOTYPE;
	    }
	    break;
	}
	break;
    case SDF_INT64:
	value.u.int64val = (int64_t)dval;
	if( value.u.int64val != dval ){
	    value.u.int64val = ival;
	    if( value.u.int64val != ival ){
		yyerror("Can't fit value into int64_t.");
		value.type = SDF_NOTYPE;
	    }
	    break;
	}
	break;
    case SDF_FLOAT:
	if(dval > FLT_MAX || dval < -FLT_MAX){
	    yyerror("Can't fit value into float.");
	    value.type = SDF_NOTYPE;
	}
	value.u.floatval = dval;
	break;
    case SDF_DOUBLE:
	value.u.doubleval = dval;
	break;
    default:
	yyerror("Impossible case.\n");
	break;
    }
    return value;
}
    
void *SDFobstack_chunk_alloc(size_t n)
{ 
    void *p = Malloc(n);
#if YYDEBUG
    if(yydebug)
	printf("malloc(%ld) = 0x%lx\n", (long)n, (unsigned long)p);
#endif
    return p;
}

void SDFobstack_chunk_free(void *p)
{ 
#if YYDEBUG    
    if(yydebug)
	printf("free(0x%lx)\n", (unsigned long)p);
#endif
    Free(p); 
}

/* This symbol tells a Flex-based scanner not to bother trying to
   call isatty to figure out whether to do char-at-a-time input.  The
   actual behavior is under our explicit control anyway (see SDF-lex.l),
   but linking against fileno() and isatty() can be annoying. */
#define YY_ALWAYS_INTERACTIVE 1
#include "SDF-lex.c"

