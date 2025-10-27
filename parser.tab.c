/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"

extern int yylex();
extern int line_num;
extern FILE *yyin;
extern char *yytext;

ASTNode *root = NULL;
SymbolTable *current_scope = NULL;
SymbolTable *global_scope = NULL;
int error_count = 0;

void yyerror(const char *s) {
    fprintf(stderr, "%s:%d: error: %s\n", current_filename, line_num, s);
    error_count++;
}

#line 93 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_STRING = 4,                     /* STRING  */
  YYSYMBOL_INT_CONST = 5,                  /* INT_CONST  */
  YYSYMBOL_FLOAT_CONST = 6,                /* FLOAT_CONST  */
  YYSYMBOL_INT = 7,                        /* INT  */
  YYSYMBOL_FLOAT = 8,                      /* FLOAT  */
  YYSYMBOL_VOID = 9,                       /* VOID  */
  YYSYMBOL_IF = 10,                        /* IF  */
  YYSYMBOL_ELSE = 11,                      /* ELSE  */
  YYSYMBOL_WHILE = 12,                     /* WHILE  */
  YYSYMBOL_FOR = 13,                       /* FOR  */
  YYSYMBOL_RETURN = 14,                    /* RETURN  */
  YYSYMBOL_PRINTF = 15,                    /* PRINTF  */
  YYSYMBOL_SCANF = 16,                     /* SCANF  */
  YYSYMBOL_PLUS = 17,                      /* PLUS  */
  YYSYMBOL_MINUS = 18,                     /* MINUS  */
  YYSYMBOL_MULT = 19,                      /* MULT  */
  YYSYMBOL_DIV = 20,                       /* DIV  */
  YYSYMBOL_MOD = 21,                       /* MOD  */
  YYSYMBOL_EQ = 22,                        /* EQ  */
  YYSYMBOL_NE = 23,                        /* NE  */
  YYSYMBOL_LT = 24,                        /* LT  */
  YYSYMBOL_GT = 25,                        /* GT  */
  YYSYMBOL_LE = 26,                        /* LE  */
  YYSYMBOL_GE = 27,                        /* GE  */
  YYSYMBOL_AND = 28,                       /* AND  */
  YYSYMBOL_OR = 29,                        /* OR  */
  YYSYMBOL_NOT = 30,                       /* NOT  */
  YYSYMBOL_ASSIGN = 31,                    /* ASSIGN  */
  YYSYMBOL_SEMICOLON = 32,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 33,                     /* COMMA  */
  YYSYMBOL_LPAREN = 34,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 35,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 36,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 37,                    /* RBRACE  */
  YYSYMBOL_AMPERSAND = 38,                 /* AMPERSAND  */
  YYSYMBOL_UMINUS = 39,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_program = 41,                   /* program  */
  YYSYMBOL_declaration_list = 42,          /* declaration_list  */
  YYSYMBOL_declaration = 43,               /* declaration  */
  YYSYMBOL_var_declaration = 44,           /* var_declaration  */
  YYSYMBOL_type_specifier = 45,            /* type_specifier  */
  YYSYMBOL_function_declaration = 46,      /* function_declaration  */
  YYSYMBOL_params = 47,                    /* params  */
  YYSYMBOL_param_list = 48,                /* param_list  */
  YYSYMBOL_param = 49,                     /* param  */
  YYSYMBOL_compound_stmt = 50,             /* compound_stmt  */
  YYSYMBOL_stmt_list = 51,                 /* stmt_list  */
  YYSYMBOL_stmt = 52,                      /* stmt  */
  YYSYMBOL_expr_stmt = 53,                 /* expr_stmt  */
  YYSYMBOL_selection_stmt = 54,            /* selection_stmt  */
  YYSYMBOL_iteration_stmt = 55,            /* iteration_stmt  */
  YYSYMBOL_return_stmt = 56,               /* return_stmt  */
  YYSYMBOL_print_stmt = 57,                /* print_stmt  */
  YYSYMBOL_scan_stmt = 58,                 /* scan_stmt  */
  YYSYMBOL_expr = 59,                      /* expr  */
  YYSYMBOL_simple_expr = 60,               /* simple_expr  */
  YYSYMBOL_additive_expr = 61,             /* additive_expr  */
  YYSYMBOL_term = 62,                      /* term  */
  YYSYMBOL_factor = 63,                    /* factor  */
  YYSYMBOL_call = 64,                      /* call  */
  YYSYMBOL_args = 65,                      /* args  */
  YYSYMBOL_arg_list = 66                   /* arg_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   226

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  79
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  148

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    62,    62,    70,    74,    81,    82,    86,    91,    97,
     106,   119,   120,   121,   125,   135,   136,   140,   146,   150,
     157,   165,   166,   172,   176,   183,   184,   185,   186,   187,
     188,   189,   190,   194,   198,   206,   212,   217,   226,   231,
     241,   244,   248,   259,   266,   272,   283,   296,   306,   313,
     317,   322,   327,   332,   337,   342,   347,   352,   357,   361,
     366,   371,   375,   380,   385,   390,   394,   395,   399,   400,
     405,   410,   414,   421,   426,   435,   439,   443,   447,   455
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "STRING",
  "INT_CONST", "FLOAT_CONST", "INT", "FLOAT", "VOID", "IF", "ELSE",
  "WHILE", "FOR", "RETURN", "PRINTF", "SCANF", "PLUS", "MINUS", "MULT",
  "DIV", "MOD", "EQ", "NE", "LT", "GT", "LE", "GE", "AND", "OR", "NOT",
  "ASSIGN", "SEMICOLON", "COMMA", "LPAREN", "RPAREN", "LBRACE", "RBRACE",
  "AMPERSAND", "UMINUS", "$accept", "program", "declaration_list",
  "declaration", "var_declaration", "type_specifier",
  "function_declaration", "params", "param_list", "param", "compound_stmt",
  "stmt_list", "stmt", "expr_stmt", "selection_stmt", "iteration_stmt",
  "return_stmt", "print_stmt", "scan_stmt", "expr", "simple_expr",
  "additive_expr", "term", "factor", "call", "args", "arg_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-106)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-17)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      18,  -106,  -106,  -106,    19,    18,  -106,  -106,    29,  -106,
    -106,  -106,    17,  -106,   170,  -106,   125,   -27,  -106,  -106,
     184,   184,   170,    13,   183,    50,   172,  -106,  -106,     4,
      39,    26,    38,  -106,   170,     6,    46,  -106,  -106,    51,
    -106,  -106,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,  -106,    55,    18,  -106,  -106,
      94,  -106,    59,    71,  -106,    50,    50,    50,    50,    50,
      50,    50,    50,   172,   172,  -106,  -106,  -106,    69,  -106,
    -106,  -106,  -106,    25,    68,    73,    79,   106,    96,   101,
    -106,  -106,  -106,   141,  -106,   113,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,    22,   143,  -106,   170,   170,   165,  -106,
      28,   144,   155,    21,  -106,  -106,  -106,  -106,  -106,   117,
     130,   165,  -106,  -106,   -20,   134,   148,   148,   170,    32,
      63,    32,   158,  -106,   137,    65,  -106,  -106,    75,   148,
     148,    64,   142,  -106,  -106,  -106,  -106,  -106
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    11,    12,    13,     0,     2,     4,     5,     0,     6,
       1,     3,     0,     9,     0,     7,    17,    67,    69,    70,
       0,     0,     0,     0,    49,    58,    61,    65,    68,    13,
       0,     0,    15,    19,     0,     0,    67,    71,    72,     0,
      10,     8,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    20,     0,     0,    48,    74,
       0,    77,     0,    75,    66,    52,    53,    54,    56,    55,
      57,    51,    50,    59,    60,    62,    63,    64,     0,    14,
      18,    78,    73,     0,     0,     0,     0,     0,     0,     0,
      35,    22,    32,     0,    26,     0,    24,    25,    27,    28,
      29,    30,    31,     0,     0,    76,     0,     0,     0,    40,
       0,     0,     0,     0,    21,    23,    34,    33,    79,     0,
       0,     0,    42,    41,     0,     0,     0,     0,     0,     0,
       0,     0,    36,    38,     0,     0,    46,    44,     0,     0,
       0,     0,     0,    37,    39,    45,    43,    47
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -106,  -106,  -106,   174,     5,     1,  -106,  -106,  -106,   120,
     129,  -106,   -93,  -105,  -106,  -106,  -106,  -106,  -106,   -14,
    -106,   177,    91,    36,  -106,  -106,     8
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,    92,    93,     9,    31,    32,    33,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
      24,    25,    26,    27,    28,    62,    63
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      23,     8,   115,   121,    34,     7,     8,    35,    39,    17,
       7,    18,    19,   129,    40,   130,   128,    30,    13,    10,
      58,    61,    13,   116,    20,     1,     2,     3,    17,   122,
      18,    19,    12,   132,   133,    17,    21,    18,    19,   -16,
      22,    59,    55,    20,    60,    41,   143,   144,    14,    15,
      20,    16,    14,    15,   117,    21,    37,    38,    30,    22,
     123,    56,    21,   104,   136,   145,    22,    50,    51,   105,
      60,    57,    17,   110,    18,    19,     1,     2,     3,    84,
      35,    85,    86,    87,    88,    89,    64,    20,    75,    76,
      77,    78,   119,   120,    82,   137,   146,    81,    83,    21,
     141,    90,   106,    22,    83,    78,    91,   107,    83,    17,
     142,    18,    19,   108,   134,    61,    17,    61,    18,    19,
       1,     2,     3,    84,    20,    85,    86,    87,    88,    89,
     111,    20,     1,     2,    29,   112,    21,   135,   109,   138,
      22,    73,    74,    21,   113,    90,   118,    22,   124,    78,
     114,    17,   126,    18,    19,     1,     2,     3,    84,   125,
      85,    86,    87,    88,    89,   127,    20,   131,    17,   139,
      18,    19,   140,    17,   147,    18,    19,    80,    21,    11,
      90,     0,    22,    20,    78,    79,     0,    36,    20,    18,
      19,    52,    53,    54,     0,    21,     0,    90,     0,    22,
      21,     0,    20,     0,    22,    42,    43,    44,    45,    46,
      47,    48,    49,     0,    21,     0,     0,     0,    22,    65,
      66,    67,    68,    69,    70,    71,    72
};

static const yytype_int16 yycheck[] =
{
      14,     0,    95,   108,    31,     0,     5,    34,    22,     3,
       5,     5,     6,    33,     1,    35,   121,    16,     1,     0,
      34,    35,     1,     1,    18,     7,     8,     9,     3,     1,
       5,     6,     3,   126,   127,     3,    30,     5,     6,    35,
      34,    35,     3,    18,    38,    32,   139,   140,    31,    32,
      18,    34,    31,    32,    32,    30,    20,    21,    57,    34,
      32,    35,    30,    38,     1,     1,    34,    17,    18,    83,
      38,    33,     3,    87,     5,     6,     7,     8,     9,    10,
      34,    12,    13,    14,    15,    16,    35,    18,    52,    53,
      54,    36,   106,   107,    35,    32,    32,     3,    33,    30,
      35,    32,    34,    34,    33,    36,    37,    34,    33,     3,
      35,     5,     6,    34,   128,   129,     3,   131,     5,     6,
       7,     8,     9,    10,    18,    12,    13,    14,    15,    16,
      34,    18,     7,     8,     9,    34,    30,   129,    32,   131,
      34,    50,    51,    30,     3,    32,     3,    34,     4,    36,
      37,     3,    35,     5,     6,     7,     8,     9,    10,     4,
      12,    13,    14,    15,    16,    35,    18,    33,     3,    11,
       5,     6,    35,     3,    32,     5,     6,    57,    30,     5,
      32,    -1,    34,    18,    36,    56,    -1,     3,    18,     5,
       6,    19,    20,    21,    -1,    30,    -1,    32,    -1,    34,
      30,    -1,    18,    -1,    34,    22,    23,    24,    25,    26,
      27,    28,    29,    -1,    30,    -1,    -1,    -1,    34,    42,
      43,    44,    45,    46,    47,    48,    49
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,     8,     9,    41,    42,    43,    44,    45,    46,
       0,    43,     3,     1,    31,    32,    34,     3,     5,     6,
      18,    30,    34,    59,    60,    61,    62,    63,    64,     9,
      45,    47,    48,    49,    31,    34,     3,    63,    63,    59,
       1,    32,    22,    23,    24,    25,    26,    27,    28,    29,
      17,    18,    19,    20,    21,     3,    35,    33,    59,    35,
      38,    59,    65,    66,    35,    61,    61,    61,    61,    61,
      61,    61,    61,    62,    62,    63,    63,    63,    36,    50,
      49,     3,    35,    33,    10,    12,    13,    14,    15,    16,
      32,    37,    44,    45,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    38,    59,    34,    34,    34,    32,
      59,    34,    34,     3,    37,    52,     1,    32,     3,    59,
      59,    53,     1,    32,     4,     4,    35,    35,    53,    33,
      35,    33,    52,    52,    59,    66,     1,    32,    66,    11,
      35,    35,    35,    52,    52,     1,    32,    32
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    44,    44,    44,
      44,    45,    45,    45,    46,    47,    47,    47,    48,    48,
      49,    50,    50,    51,    51,    52,    52,    52,    52,    52,
      52,    52,    52,    53,    53,    53,    54,    54,    55,    55,
      56,    56,    56,    57,    57,    57,    57,    58,    59,    59,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    61,
      61,    61,    62,    62,    62,    62,    63,    63,    63,    63,
      63,    63,    63,    64,    64,    65,    66,    66,    66,    66
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     5,     3,
       5,     1,     1,     1,     6,     1,     1,     0,     3,     1,
       2,     3,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     1,     5,     7,     5,     7,
       2,     3,     3,     7,     5,     7,     5,     7,     3,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     1,     3,     1,     1,     1,
       1,     2,     2,     4,     3,     1,     3,     1,     2,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: declaration_list  */
#line 62 "parser.y"
                     {
        root = createNode(NODE_PROGRAM, "Program");
        addChild(root, (yyvsp[0].node));
        (yyval.node) = root;
    }
#line 1530 "parser.tab.c"
    break;

  case 3: /* declaration_list: declaration_list declaration  */
#line 70 "parser.y"
                                 {
        (yyval.node) = (yyvsp[-1].node);
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 1539 "parser.tab.c"
    break;

  case 4: /* declaration_list: declaration  */
#line 74 "parser.y"
                  {
        (yyval.node) = createNode(NODE_COMPOUND_STMT, "DeclarationList");
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 1548 "parser.tab.c"
    break;

  case 5: /* declaration: var_declaration  */
#line 81 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1554 "parser.tab.c"
    break;

  case 6: /* declaration: function_declaration  */
#line 82 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1560 "parser.tab.c"
    break;

  case 7: /* var_declaration: type_specifier ID SEMICOLON  */
#line 86 "parser.y"
                                {
        (yyval.node) = createNode(NODE_VAR_DECL, (yyvsp[-1].str));
        (yyval.node)->data_type = (yyvsp[-2].type);
        free((yyvsp[-1].str));
    }
#line 1570 "parser.tab.c"
    break;

  case 8: /* var_declaration: type_specifier ID ASSIGN expr SEMICOLON  */
#line 91 "parser.y"
                                              {
        (yyval.node) = createNode(NODE_VAR_DECL, (yyvsp[-3].str));
        (yyval.node)->data_type = (yyvsp[-4].type);
        addChild((yyval.node), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1581 "parser.tab.c"
    break;

  case 9: /* var_declaration: type_specifier ID error  */
#line 97 "parser.y"
                              {
        fprintf(stderr, "%s:%d: error: expected ';' after variable declaration\n", 
                current_filename, line_num);
        error_count++;
        yyerrok;
        (yyval.node) = createNode(NODE_VAR_DECL, (yyvsp[-1].str));
        (yyval.node)->data_type = (yyvsp[-2].type);
        free((yyvsp[-1].str));
    }
#line 1595 "parser.tab.c"
    break;

  case 10: /* var_declaration: type_specifier ID ASSIGN expr error  */
#line 106 "parser.y"
                                          {
        fprintf(stderr, "%s:%d: error: expected ';' after initialization\n", 
                current_filename, line_num);
        error_count++;
        yyerrok;
        (yyval.node) = createNode(NODE_VAR_DECL, (yyvsp[-3].str));
        (yyval.node)->data_type = (yyvsp[-4].type);
        addChild((yyval.node), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1610 "parser.tab.c"
    break;

  case 11: /* type_specifier: INT  */
#line 119 "parser.y"
        { (yyval.type) = TYPE_INT; }
#line 1616 "parser.tab.c"
    break;

  case 12: /* type_specifier: FLOAT  */
#line 120 "parser.y"
            { (yyval.type) = TYPE_FLOAT; }
#line 1622 "parser.tab.c"
    break;

  case 13: /* type_specifier: VOID  */
#line 121 "parser.y"
           { (yyval.type) = TYPE_VOID; }
#line 1628 "parser.tab.c"
    break;

  case 14: /* function_declaration: type_specifier ID LPAREN params RPAREN compound_stmt  */
#line 125 "parser.y"
                                                         {
        (yyval.node) = createNode(NODE_FUNCTION_DECL, (yyvsp[-4].str));
        (yyval.node)->data_type = (yyvsp[-5].type);
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
        free((yyvsp[-4].str));
    }
#line 1640 "parser.tab.c"
    break;

  case 15: /* params: param_list  */
#line 135 "parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 1646 "parser.tab.c"
    break;

  case 16: /* params: VOID  */
#line 136 "parser.y"
           {
        (yyval.node) = createNode(NODE_PARAM, "void");
        (yyval.node)->data_type = TYPE_VOID;
    }
#line 1655 "parser.tab.c"
    break;

  case 17: /* params: %empty  */
#line 140 "parser.y"
                  {
        (yyval.node) = createNode(NODE_PARAM, "empty");
    }
#line 1663 "parser.tab.c"
    break;

  case 18: /* param_list: param_list COMMA param  */
#line 146 "parser.y"
                           {
        (yyval.node) = (yyvsp[-2].node);
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 1672 "parser.tab.c"
    break;

  case 19: /* param_list: param  */
#line 150 "parser.y"
            {
        (yyval.node) = createNode(NODE_COMPOUND_STMT, "ParamList");
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 1681 "parser.tab.c"
    break;

  case 20: /* param: type_specifier ID  */
#line 157 "parser.y"
                      {
        (yyval.node) = createNode(NODE_PARAM, (yyvsp[0].str));
        (yyval.node)->data_type = (yyvsp[-1].type);
        free((yyvsp[0].str));
    }
#line 1691 "parser.tab.c"
    break;

  case 21: /* compound_stmt: LBRACE stmt_list RBRACE  */
#line 165 "parser.y"
                            { (yyval.node) = (yyvsp[-1].node); }
#line 1697 "parser.tab.c"
    break;

  case 22: /* compound_stmt: LBRACE RBRACE  */
#line 166 "parser.y"
                    {
        (yyval.node) = createNode(NODE_COMPOUND_STMT, "EmptyBlock");
    }
#line 1705 "parser.tab.c"
    break;

  case 23: /* stmt_list: stmt_list stmt  */
#line 172 "parser.y"
                   {
        (yyval.node) = (yyvsp[-1].node);
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 1714 "parser.tab.c"
    break;

  case 24: /* stmt_list: stmt  */
#line 176 "parser.y"
           {
        (yyval.node) = createNode(NODE_COMPOUND_STMT, "StmtList");
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 1723 "parser.tab.c"
    break;

  case 25: /* stmt: expr_stmt  */
#line 183 "parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 1729 "parser.tab.c"
    break;

  case 26: /* stmt: compound_stmt  */
#line 184 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1735 "parser.tab.c"
    break;

  case 27: /* stmt: selection_stmt  */
#line 185 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 1741 "parser.tab.c"
    break;

  case 28: /* stmt: iteration_stmt  */
#line 186 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 1747 "parser.tab.c"
    break;

  case 29: /* stmt: return_stmt  */
#line 187 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1753 "parser.tab.c"
    break;

  case 30: /* stmt: print_stmt  */
#line 188 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1759 "parser.tab.c"
    break;

  case 31: /* stmt: scan_stmt  */
#line 189 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1765 "parser.tab.c"
    break;

  case 32: /* stmt: var_declaration  */
#line 190 "parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1771 "parser.tab.c"
    break;

  case 33: /* expr_stmt: expr SEMICOLON  */
#line 194 "parser.y"
                   {
        (yyval.node) = createNode(NODE_EXPR_STMT, "ExprStmt");
        addChild((yyval.node), (yyvsp[-1].node));
    }
#line 1780 "parser.tab.c"
    break;

  case 34: /* expr_stmt: expr error  */
#line 198 "parser.y"
                 {
        fprintf(stderr, "%s:%d: error: expected ';' after expression\n", 
                current_filename, line_num);
        error_count++;
        yyerrok;
        (yyval.node) = createNode(NODE_EXPR_STMT, "ExprStmt");
        addChild((yyval.node), (yyvsp[-1].node));
    }
#line 1793 "parser.tab.c"
    break;

  case 35: /* expr_stmt: SEMICOLON  */
#line 206 "parser.y"
                {
        (yyval.node) = createNode(NODE_EXPR_STMT, "EmptyStmt");
    }
#line 1801 "parser.tab.c"
    break;

  case 36: /* selection_stmt: IF LPAREN expr RPAREN stmt  */
#line 212 "parser.y"
                               {
        (yyval.node) = createNode(NODE_IF_STMT, "If");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 1811 "parser.tab.c"
    break;

  case 37: /* selection_stmt: IF LPAREN expr RPAREN stmt ELSE stmt  */
#line 217 "parser.y"
                                           {
        (yyval.node) = createNode(NODE_IF_STMT, "IfElse");
        addChild((yyval.node), (yyvsp[-4].node));
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 1822 "parser.tab.c"
    break;

  case 38: /* iteration_stmt: WHILE LPAREN expr RPAREN stmt  */
#line 226 "parser.y"
                                  {
        (yyval.node) = createNode(NODE_WHILE_STMT, "While");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 1832 "parser.tab.c"
    break;

  case 39: /* iteration_stmt: FOR LPAREN expr_stmt expr_stmt expr RPAREN stmt  */
#line 231 "parser.y"
                                                      {
        (yyval.node) = createNode(NODE_FOR_STMT, "For");
        addChild((yyval.node), (yyvsp[-4].node));
        addChild((yyval.node), (yyvsp[-3].node));
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 1844 "parser.tab.c"
    break;

  case 40: /* return_stmt: RETURN SEMICOLON  */
#line 241 "parser.y"
                     {
        (yyval.node) = createNode(NODE_RETURN_STMT, "Return");
    }
#line 1852 "parser.tab.c"
    break;

  case 41: /* return_stmt: RETURN expr SEMICOLON  */
#line 244 "parser.y"
                            {
        (yyval.node) = createNode(NODE_RETURN_STMT, "Return");
        addChild((yyval.node), (yyvsp[-1].node));
    }
#line 1861 "parser.tab.c"
    break;

  case 42: /* return_stmt: RETURN expr error  */
#line 248 "parser.y"
                        {
        fprintf(stderr, "%s:%d: error: expected ';' after return statement\n", 
                current_filename, line_num);
        error_count++;
        yyerrok;
        (yyval.node) = createNode(NODE_RETURN_STMT, "Return");
        addChild((yyval.node), (yyvsp[-1].node));
    }
#line 1874 "parser.tab.c"
    break;

  case 43: /* print_stmt: PRINTF LPAREN STRING COMMA arg_list RPAREN SEMICOLON  */
#line 259 "parser.y"
                                                         {
        (yyval.node) = createNode(NODE_PRINT_STMT, "Printf");
        ASTNode *fmt = createNode(NODE_IDENTIFIER, (yyvsp[-4].str));
        addChild((yyval.node), fmt);
        addChild((yyval.node), (yyvsp[-2].node));
        free((yyvsp[-4].str));
    }
#line 1886 "parser.tab.c"
    break;

  case 44: /* print_stmt: PRINTF LPAREN STRING RPAREN SEMICOLON  */
#line 266 "parser.y"
                                            {
        (yyval.node) = createNode(NODE_PRINT_STMT, "Printf");
        ASTNode *fmt = createNode(NODE_IDENTIFIER, (yyvsp[-2].str));
        addChild((yyval.node), fmt);
        free((yyvsp[-2].str));
    }
#line 1897 "parser.tab.c"
    break;

  case 45: /* print_stmt: PRINTF LPAREN STRING COMMA arg_list RPAREN error  */
#line 272 "parser.y"
                                                       {
        fprintf(stderr, "%s:%d: error: expected ';' after printf statement\n", 
                current_filename, line_num);
        error_count++;
        yyerrok;
        (yyval.node) = createNode(NODE_PRINT_STMT, "Printf");
        ASTNode *fmt = createNode(NODE_IDENTIFIER, (yyvsp[-4].str));
        addChild((yyval.node), fmt);
        addChild((yyval.node), (yyvsp[-2].node));
        free((yyvsp[-4].str));
    }
#line 1913 "parser.tab.c"
    break;

  case 46: /* print_stmt: PRINTF LPAREN STRING RPAREN error  */
#line 283 "parser.y"
                                        {
        fprintf(stderr, "%s:%d: error: expected ';' after printf statement\n", 
                current_filename, line_num);
        error_count++;
        yyerrok;
        (yyval.node) = createNode(NODE_PRINT_STMT, "Printf");
        ASTNode *fmt = createNode(NODE_IDENTIFIER, (yyvsp[-2].str));
        addChild((yyval.node), fmt);
        free((yyvsp[-2].str));
    }
#line 1928 "parser.tab.c"
    break;

  case 47: /* scan_stmt: SCANF LPAREN STRING COMMA arg_list RPAREN SEMICOLON  */
#line 296 "parser.y"
                                                        {
        (yyval.node) = createNode(NODE_SCAN_STMT, "Scanf");
        ASTNode *fmt = createNode(NODE_IDENTIFIER, (yyvsp[-4].str));
        addChild((yyval.node), fmt);
        addChild((yyval.node), (yyvsp[-2].node));
        free((yyvsp[-4].str));
    }
#line 1940 "parser.tab.c"
    break;

  case 48: /* expr: ID ASSIGN expr  */
#line 306 "parser.y"
                   {
        (yyval.node) = createNode(NODE_ASSIGN, "=");
        ASTNode *id = createNode(NODE_IDENTIFIER, (yyvsp[-2].str));
        addChild((yyval.node), id);
        addChild((yyval.node), (yyvsp[0].node));
        free((yyvsp[-2].str));
    }
#line 1952 "parser.tab.c"
    break;

  case 49: /* expr: simple_expr  */
#line 313 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1958 "parser.tab.c"
    break;

  case 50: /* simple_expr: simple_expr OR additive_expr  */
#line 317 "parser.y"
                                 {
        (yyval.node) = createNode(NODE_BINARY_OP, "||");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 1968 "parser.tab.c"
    break;

  case 51: /* simple_expr: simple_expr AND additive_expr  */
#line 322 "parser.y"
                                    {
        (yyval.node) = createNode(NODE_BINARY_OP, "&&");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 1978 "parser.tab.c"
    break;

  case 52: /* simple_expr: simple_expr EQ additive_expr  */
#line 327 "parser.y"
                                   {
        (yyval.node) = createNode(NODE_BINARY_OP, "==");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 1988 "parser.tab.c"
    break;

  case 53: /* simple_expr: simple_expr NE additive_expr  */
#line 332 "parser.y"
                                   {
        (yyval.node) = createNode(NODE_BINARY_OP, "!=");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 1998 "parser.tab.c"
    break;

  case 54: /* simple_expr: simple_expr LT additive_expr  */
#line 337 "parser.y"
                                   {
        (yyval.node) = createNode(NODE_BINARY_OP, "<");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2008 "parser.tab.c"
    break;

  case 55: /* simple_expr: simple_expr LE additive_expr  */
#line 342 "parser.y"
                                   {
        (yyval.node) = createNode(NODE_BINARY_OP, "<=");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2018 "parser.tab.c"
    break;

  case 56: /* simple_expr: simple_expr GT additive_expr  */
#line 347 "parser.y"
                                   {
        (yyval.node) = createNode(NODE_BINARY_OP, ">");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2028 "parser.tab.c"
    break;

  case 57: /* simple_expr: simple_expr GE additive_expr  */
#line 352 "parser.y"
                                   {
        (yyval.node) = createNode(NODE_BINARY_OP, ">=");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2038 "parser.tab.c"
    break;

  case 58: /* simple_expr: additive_expr  */
#line 357 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2044 "parser.tab.c"
    break;

  case 59: /* additive_expr: additive_expr PLUS term  */
#line 361 "parser.y"
                            {
        (yyval.node) = createNode(NODE_BINARY_OP, "+");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2054 "parser.tab.c"
    break;

  case 60: /* additive_expr: additive_expr MINUS term  */
#line 366 "parser.y"
                               {
        (yyval.node) = createNode(NODE_BINARY_OP, "-");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2064 "parser.tab.c"
    break;

  case 61: /* additive_expr: term  */
#line 371 "parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2070 "parser.tab.c"
    break;

  case 62: /* term: term MULT factor  */
#line 375 "parser.y"
                     {
        (yyval.node) = createNode(NODE_BINARY_OP, "*");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2080 "parser.tab.c"
    break;

  case 63: /* term: term DIV factor  */
#line 380 "parser.y"
                      {
        (yyval.node) = createNode(NODE_BINARY_OP, "/");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2090 "parser.tab.c"
    break;

  case 64: /* term: term MOD factor  */
#line 385 "parser.y"
                      {
        (yyval.node) = createNode(NODE_BINARY_OP, "%");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2100 "parser.tab.c"
    break;

  case 65: /* term: factor  */
#line 390 "parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2106 "parser.tab.c"
    break;

  case 66: /* factor: LPAREN expr RPAREN  */
#line 394 "parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 2112 "parser.tab.c"
    break;

  case 67: /* factor: ID  */
#line 395 "parser.y"
         {
        (yyval.node) = createNode(NODE_IDENTIFIER, (yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 2121 "parser.tab.c"
    break;

  case 68: /* factor: call  */
#line 399 "parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2127 "parser.tab.c"
    break;

  case 69: /* factor: INT_CONST  */
#line 400 "parser.y"
                {
        (yyval.node) = createNode(NODE_INT_LITERAL, "int");
        (yyval.node)->value.int_val = (yyvsp[0].int_val);
        (yyval.node)->data_type = TYPE_INT;
    }
#line 2137 "parser.tab.c"
    break;

  case 70: /* factor: FLOAT_CONST  */
#line 405 "parser.y"
                  {
        (yyval.node) = createNode(NODE_FLOAT_LITERAL, "float");
        (yyval.node)->value.float_val = (yyvsp[0].float_val);
        (yyval.node)->data_type = TYPE_FLOAT;
    }
#line 2147 "parser.tab.c"
    break;

  case 71: /* factor: MINUS factor  */
#line 410 "parser.y"
                                {
        (yyval.node) = createNode(NODE_UNARY_OP, "-");
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2156 "parser.tab.c"
    break;

  case 72: /* factor: NOT factor  */
#line 414 "parser.y"
                 {
        (yyval.node) = createNode(NODE_UNARY_OP, "!");
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2165 "parser.tab.c"
    break;

  case 73: /* call: ID LPAREN args RPAREN  */
#line 421 "parser.y"
                          {
        (yyval.node) = createNode(NODE_FUNC_CALL, (yyvsp[-3].str));
        addChild((yyval.node), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 2175 "parser.tab.c"
    break;

  case 74: /* call: ID LPAREN RPAREN  */
#line 426 "parser.y"
                       {
        (yyval.node) = createNode(NODE_FUNC_CALL, (yyvsp[-2].str));
        ASTNode *empty_args = createNode(NODE_COMPOUND_STMT, "EmptyArgs");
        addChild((yyval.node), empty_args);
        free((yyvsp[-2].str));
    }
#line 2186 "parser.tab.c"
    break;

  case 75: /* args: arg_list  */
#line 435 "parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2192 "parser.tab.c"
    break;

  case 76: /* arg_list: arg_list COMMA expr  */
#line 439 "parser.y"
                        {
        (yyval.node) = (yyvsp[-2].node);
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2201 "parser.tab.c"
    break;

  case 77: /* arg_list: expr  */
#line 443 "parser.y"
           {
        (yyval.node) = createNode(NODE_COMPOUND_STMT, "ArgList");
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2210 "parser.tab.c"
    break;

  case 78: /* arg_list: AMPERSAND ID  */
#line 447 "parser.y"
                   {
        (yyval.node) = createNode(NODE_COMPOUND_STMT, "ArgList");
        ASTNode *ref = createNode(NODE_UNARY_OP, "&");
        ASTNode *id = createNode(NODE_IDENTIFIER, (yyvsp[0].str));
        addChild(ref, id);
        addChild((yyval.node), ref);
        free((yyvsp[0].str));
    }
#line 2223 "parser.tab.c"
    break;

  case 79: /* arg_list: arg_list COMMA AMPERSAND ID  */
#line 455 "parser.y"
                                  {
        (yyval.node) = (yyvsp[-3].node);
        ASTNode *ref = createNode(NODE_UNARY_OP, "&");
        ASTNode *id = createNode(NODE_IDENTIFIER, (yyvsp[0].str));
        addChild(ref, id);
        addChild((yyval.node), ref);
        free((yyvsp[0].str));
    }
#line 2236 "parser.tab.c"
    break;


#line 2240 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 465 "parser.y"

