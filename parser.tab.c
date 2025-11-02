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
    fprintf(stderr, "\n%s:%d:1: \033[1;31merror:\033[0m %s\n", current_filename, line_num, s);
    fprintf(stderr, "    %s\n", s);
    error_count++;
}

void detailed_error(const char *error_msg, const char *note, const char *fix) {
    fprintf(stderr, "\n%s:%d:1: \033[1;31merror:\033[0m %s\n", current_filename, line_num, error_msg);
    if (note) {
        fprintf(stderr, "\033[1;36mnote:\033[0m %s\n", note);
    }
    if (fix) {
        fprintf(stderr, "\033[1;32msuggested fix:\033[0m\n%s\n", fix);
    }
    error_count++;
}

#line 105 "parser.tab.c"

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
#define YYLAST   236

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  89
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  160

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
       0,    74,    74,    82,    86,    93,    94,    98,   103,   109,
     121,   137,   138,   139,   143,   150,   168,   169,   173,   179,
     183,   190,   198,   199,   202,   212,   216,   223,   224,   225,
     226,   227,   228,   229,   230,   234,   238,   246,   252,   257,
     263,   272,   282,   287,   296,   303,   314,   324,   327,   331,
     342,   349,   355,   366,   376,   386,   393,   407,   414,   418,
     423,   428,   433,   438,   443,   448,   453,   458,   462,   467,
     472,   476,   481,   486,   491,   495,   496,   500,   501,   506,
     511,   515,   522,   527,   533,   547,   551,   555,   559,   567
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

#define YYPACT_NINF (-111)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-18)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      23,  -111,  -111,  -111,    26,    23,  -111,  -111,    38,  -111,
    -111,  -111,    70,  -111,   180,  -111,   104,    36,  -111,  -111,
     194,   194,   180,     2,   193,   178,    97,  -111,  -111,    20,
      62,    55,    40,  -111,   180,     9,    80,  -111,  -111,    85,
    -111,  -111,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,  -111,     6,    23,  -111,   109,
    -111,   105,  -111,   121,   118,  -111,   178,   178,   178,   178,
     178,   178,   178,   178,    97,    97,  -111,  -111,  -111,  -111,
      73,  -111,  -111,  -111,  -111,  -111,    19,   125,    12,   124,
      17,   116,    22,   135,  -111,  -111,  -111,   172,  -111,   123,
    -111,  -111,  -111,  -111,  -111,  -111,  -111,    27,   174,  -111,
    -111,  -111,   180,   180,  -111,   175,  -111,    68,  -111,   183,
     185,    65,  -111,  -111,  -111,  -111,  -111,    10,    15,   175,
    -111,  -111,   107,   146,  -111,   158,  -111,   158,   180,    30,
      74,    30,   171,  -111,    28,   110,  -111,  -111,   114,   158,
    -111,   158,    83,    91,  -111,  -111,  -111,  -111,  -111,  -111
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    11,    12,    13,     0,     2,     4,     5,     0,     6,
       1,     3,     0,     9,     0,     7,    18,    76,    78,    79,
       0,     0,     0,     0,    58,    67,    70,    74,    77,    13,
       0,     0,    16,    20,     0,     0,    76,    80,    81,     0,
      10,     8,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    21,     0,     0,    57,     0,
      83,     0,    87,     0,    85,    75,    61,    62,    63,    65,
      64,    66,    60,    59,    68,    69,    71,    72,    73,    15,
       0,    14,    19,    84,    88,    82,     0,     0,     0,     0,
       0,     0,     0,     0,    37,    23,    34,     0,    28,     0,
      26,    27,    29,    30,    31,    32,    33,     0,     0,    86,
      24,    41,     0,     0,    46,     0,    47,     0,    54,     0,
       0,     0,    22,    25,    36,    35,    89,     0,     0,     0,
      49,    48,     0,     0,    40,     0,    43,     0,     0,     0,
       0,     0,    38,    42,     0,     0,    53,    51,     0,     0,
      45,     0,     0,     0,    39,    44,    52,    50,    56,    55
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -111,  -111,  -111,   179,     4,     1,  -111,  -111,  -111,   134,
     147,  -111,   -97,  -110,  -111,  -111,  -111,  -111,  -111,   -14,
    -111,   187,   151,    41,  -111,  -111,    13
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,    96,    97,     9,    31,    32,    33,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
      24,    25,    26,    27,    28,    63,    64
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      23,     8,   123,    40,     7,   129,     8,    79,    39,     7,
      59,   134,    17,   111,    18,    19,   136,    30,   114,   138,
      58,    62,    17,   118,    18,    19,    10,    20,   124,   150,
       1,     2,     3,    17,    41,    18,    19,    20,   142,    21,
     143,    12,    80,    22,    60,   135,   112,    61,    20,    21,
     137,   115,   154,    22,   155,   -17,   119,   108,    30,   125,
      21,    37,    38,   151,    22,    55,    13,    34,    61,   130,
      35,    13,   109,    57,    87,   146,    17,   117,    18,    19,
       1,     2,     3,    88,   156,    89,    90,    91,    92,    93,
      56,    20,   158,    76,    77,    78,    14,    15,   127,   128,
     131,    14,    15,    21,    16,    94,   147,    22,    84,    80,
      95,     1,     2,    29,    35,   157,    52,    53,    54,    17,
      65,    18,    19,   159,   144,    62,    17,    62,    18,    19,
       1,     2,     3,    88,    20,    89,    90,    91,    92,    93,
     139,    20,   140,    86,    83,   152,    21,    86,   116,   153,
      22,    86,   145,    21,   148,    94,    85,    22,   113,    80,
     122,    17,   110,    18,    19,     1,     2,     3,    88,   120,
      89,    90,    91,    92,    93,   121,    20,   126,    17,   141,
      18,    19,   149,    17,    11,    18,    19,   132,    21,   133,
      94,    82,    22,    20,    80,    50,    51,    36,    20,    18,
      19,    74,    75,    81,     0,    21,     0,    94,     0,    22,
      21,     0,    20,     0,    22,    42,    43,    44,    45,    46,
      47,    48,    49,     0,    21,     0,     0,     0,    22,    66,
      67,    68,    69,    70,    71,    72,    73
};

static const yytype_int16 yycheck[] =
{
      14,     0,    99,     1,     0,   115,     5,     1,    22,     5,
       1,     1,     3,     1,     5,     6,     1,    16,     1,   129,
      34,    35,     3,     1,     5,     6,     0,    18,     1,     1,
       7,     8,     9,     3,    32,     5,     6,    18,   135,    30,
     137,     3,    36,    34,    35,    35,    34,    38,    18,    30,
      35,    34,   149,    34,   151,    35,    34,    38,    57,    32,
      30,    20,    21,    35,    34,     3,     1,    31,    38,     1,
      34,     1,    86,    33,     1,     1,     3,    91,     5,     6,
       7,     8,     9,    10,     1,    12,    13,    14,    15,    16,
      35,    18,     1,    52,    53,    54,    31,    32,   112,   113,
      32,    31,    32,    30,    34,    32,    32,    34,     3,    36,
      37,     7,     8,     9,    34,    32,    19,    20,    21,     3,
      35,     5,     6,    32,   138,   139,     3,   141,     5,     6,
       7,     8,     9,    10,    18,    12,    13,    14,    15,    16,
      33,    18,    35,    33,    35,    35,    30,    33,    32,    35,
      34,    33,   139,    30,   141,    32,    35,    34,    34,    36,
      37,     3,    37,     5,     6,     7,     8,     9,    10,    34,
      12,    13,    14,    15,    16,     3,    18,     3,     3,    33,
       5,     6,    11,     3,     5,     5,     6,     4,    30,     4,
      32,    57,    34,    18,    36,    17,    18,     3,    18,     5,
       6,    50,    51,    56,    -1,    30,    -1,    32,    -1,    34,
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
      17,    18,    19,    20,    21,     3,    35,    33,    59,     1,
      35,    38,    59,    65,    66,    35,    61,    61,    61,    61,
      61,    61,    61,    61,    62,    62,    63,    63,    63,     1,
      36,    50,    49,    35,     3,    35,    33,     1,    10,    12,
      13,    14,    15,    16,    32,    37,    44,    45,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    38,    59,
      37,     1,    34,    34,     1,    34,    32,    59,     1,    34,
      34,     3,    37,    52,     1,    32,     3,    59,    59,    53,
       1,    32,     4,     4,     1,    35,     1,    35,    53,    33,
      35,    33,    52,    52,    59,    66,     1,    32,    66,    11,
       1,    35,    35,    35,    52,    52,     1,    32,     1,    32
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    44,    44,    44,
      44,    45,    45,    45,    46,    46,    47,    47,    47,    48,
      48,    49,    50,    50,    50,    51,    51,    52,    52,    52,
      52,    52,    52,    52,    52,    53,    53,    53,    54,    54,
      54,    54,    55,    55,    55,    55,    55,    56,    56,    56,
      57,    57,    57,    57,    57,    58,    58,    59,    59,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    61,    61,
      61,    62,    62,    62,    62,    63,    63,    63,    63,    63,
      63,    63,    64,    64,    64,    65,    66,    66,    66,    66
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     5,     3,
       5,     1,     1,     1,     6,     6,     1,     1,     0,     3,
       1,     2,     3,     2,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     1,     5,     7,
       4,     2,     5,     4,     7,     6,     2,     2,     3,     3,
       7,     5,     7,     5,     2,     7,     7,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     1,     3,     1,     1,     1,     1,
       2,     2,     4,     3,     4,     1,     3,     1,     2,     4
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
#line 74 "parser.y"
                     {
        root = createNode(NODE_PROGRAM, "Program");
        addChild(root, (yyvsp[0].node));
        (yyval.node) = root;
    }
#line 1550 "parser.tab.c"
    break;

  case 3: /* declaration_list: declaration_list declaration  */
#line 82 "parser.y"
                                 {
        (yyval.node) = (yyvsp[-1].node);
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 1559 "parser.tab.c"
    break;

  case 4: /* declaration_list: declaration  */
#line 86 "parser.y"
                  {
        (yyval.node) = createNode(NODE_COMPOUND_STMT, "DeclarationList");
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 1568 "parser.tab.c"
    break;

  case 5: /* declaration: var_declaration  */
#line 93 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1574 "parser.tab.c"
    break;

  case 6: /* declaration: function_declaration  */
#line 94 "parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1580 "parser.tab.c"
    break;

  case 7: /* var_declaration: type_specifier ID SEMICOLON  */
#line 98 "parser.y"
                                {
        (yyval.node) = createNode(NODE_VAR_DECL, (yyvsp[-1].str));
        (yyval.node)->data_type = (yyvsp[-2].type);
        free((yyvsp[-1].str));
    }
#line 1590 "parser.tab.c"
    break;

  case 8: /* var_declaration: type_specifier ID ASSIGN expr SEMICOLON  */
#line 103 "parser.y"
                                              {
        (yyval.node) = createNode(NODE_VAR_DECL, (yyvsp[-3].str));
        (yyval.node)->data_type = (yyvsp[-4].type);
        addChild((yyval.node), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1601 "parser.tab.c"
    break;

  case 9: /* var_declaration: type_specifier ID error  */
#line 109 "parser.y"
                              {
        char msg[512], note[512], fix[512];
        snprintf(msg, sizeof(msg), "expected ';' after variable declaration");
        snprintf(note, sizeof(note), "variable '%s' is missing semicolon terminator", (yyvsp[-1].str));
        snprintf(fix, sizeof(fix), "    %s %s;  // add semicolon here", 
                 (yyvsp[-2].type) == TYPE_INT ? "int" : ((yyvsp[-2].type) == TYPE_FLOAT ? "float" : "void"), (yyvsp[-1].str));
        detailed_error(msg, note, fix);
        yyerrok;
        (yyval.node) = createNode(NODE_VAR_DECL, (yyvsp[-1].str));
        (yyval.node)->data_type = (yyvsp[-2].type);
        free((yyvsp[-1].str));
    }
#line 1618 "parser.tab.c"
    break;

  case 10: /* var_declaration: type_specifier ID ASSIGN expr error  */
#line 121 "parser.y"
                                          {
        char msg[512], note[512], fix[512];
        snprintf(msg, sizeof(msg), "expected ';' after initialization");
        snprintf(note, sizeof(note), "initialized variable '%s' is missing semicolon", (yyvsp[-3].str));
        snprintf(fix, sizeof(fix), "    %s %s = <value>;  // add semicolon at the end", 
                 (yyvsp[-4].type) == TYPE_INT ? "int" : ((yyvsp[-4].type) == TYPE_FLOAT ? "float" : "void"), (yyvsp[-3].str));
        detailed_error(msg, note, fix);
        yyerrok;
        (yyval.node) = createNode(NODE_VAR_DECL, (yyvsp[-3].str));
        (yyval.node)->data_type = (yyvsp[-4].type);
        addChild((yyval.node), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 1636 "parser.tab.c"
    break;

  case 11: /* type_specifier: INT  */
#line 137 "parser.y"
        { (yyval.type) = TYPE_INT; }
#line 1642 "parser.tab.c"
    break;

  case 12: /* type_specifier: FLOAT  */
#line 138 "parser.y"
            { (yyval.type) = TYPE_FLOAT; }
#line 1648 "parser.tab.c"
    break;

  case 13: /* type_specifier: VOID  */
#line 139 "parser.y"
           { (yyval.type) = TYPE_VOID; }
#line 1654 "parser.tab.c"
    break;

  case 14: /* function_declaration: type_specifier ID LPAREN params RPAREN compound_stmt  */
#line 143 "parser.y"
                                                         {
        (yyval.node) = createNode(NODE_FUNCTION_DECL, (yyvsp[-4].str));
        (yyval.node)->data_type = (yyvsp[-5].type);
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
        free((yyvsp[-4].str));
    }
#line 1666 "parser.tab.c"
    break;

  case 15: /* function_declaration: type_specifier ID LPAREN params RPAREN error  */
#line 150 "parser.y"
                                                   {
        char msg[512], note[512], fix[512];
        snprintf(msg, sizeof(msg), "expected function body after declaration");
        snprintf(note, sizeof(note), "function '%s' is missing opening brace '{'", (yyvsp[-4].str));
        snprintf(fix, sizeof(fix), 
                 "    %s %s(...) {\n        // function body\n        return 0;\n    }", 
                 (yyvsp[-5].type) == TYPE_INT ? "int" : ((yyvsp[-5].type) == TYPE_FLOAT ? "float" : "void"), (yyvsp[-4].str));
        detailed_error(msg, note, fix);
        yyerrok;
        (yyval.node) = createNode(NODE_FUNCTION_DECL, (yyvsp[-4].str));
        (yyval.node)->data_type = (yyvsp[-5].type);
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), createNode(NODE_COMPOUND_STMT, "EmptyBlock"));
        free((yyvsp[-4].str));
    }
#line 1686 "parser.tab.c"
    break;

  case 16: /* params: param_list  */
#line 168 "parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 1692 "parser.tab.c"
    break;

  case 17: /* params: VOID  */
#line 169 "parser.y"
           {
        (yyval.node) = createNode(NODE_PARAM, "void");
        (yyval.node)->data_type = TYPE_VOID;
    }
#line 1701 "parser.tab.c"
    break;

  case 18: /* params: %empty  */
#line 173 "parser.y"
                  {
        (yyval.node) = createNode(NODE_PARAM, "empty");
    }
#line 1709 "parser.tab.c"
    break;

  case 19: /* param_list: param_list COMMA param  */
#line 179 "parser.y"
                           {
        (yyval.node) = (yyvsp[-2].node);
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 1718 "parser.tab.c"
    break;

  case 20: /* param_list: param  */
#line 183 "parser.y"
            {
        (yyval.node) = createNode(NODE_COMPOUND_STMT, "ParamList");
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 1727 "parser.tab.c"
    break;

  case 21: /* param: type_specifier ID  */
#line 190 "parser.y"
                      {
        (yyval.node) = createNode(NODE_PARAM, (yyvsp[0].str));
        (yyval.node)->data_type = (yyvsp[-1].type);
        free((yyvsp[0].str));
    }
#line 1737 "parser.tab.c"
    break;

  case 22: /* compound_stmt: LBRACE stmt_list RBRACE  */
#line 198 "parser.y"
                            { (yyval.node) = (yyvsp[-1].node); }
#line 1743 "parser.tab.c"
    break;

  case 23: /* compound_stmt: LBRACE RBRACE  */
#line 199 "parser.y"
                    {
        (yyval.node) = createNode(NODE_COMPOUND_STMT, "EmptyBlock");
    }
#line 1751 "parser.tab.c"
    break;

  case 24: /* compound_stmt: LBRACE error RBRACE  */
#line 202 "parser.y"
                          {
        detailed_error("invalid statement in block", 
                      "syntax error inside braces",
                      "    {\n        // check for missing semicolons\n        statement;\n    }");
        yyerrok;
        (yyval.node) = createNode(NODE_COMPOUND_STMT, "ErrorBlock");
    }
#line 1763 "parser.tab.c"
    break;

  case 25: /* stmt_list: stmt_list stmt  */
#line 212 "parser.y"
                   {
        (yyval.node) = (yyvsp[-1].node);
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 1772 "parser.tab.c"
    break;

  case 26: /* stmt_list: stmt  */
#line 216 "parser.y"
           {
        (yyval.node) = createNode(NODE_COMPOUND_STMT, "StmtList");
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 1781 "parser.tab.c"
    break;

  case 27: /* stmt: expr_stmt  */
#line 223 "parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 1787 "parser.tab.c"
    break;

  case 28: /* stmt: compound_stmt  */
#line 224 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1793 "parser.tab.c"
    break;

  case 29: /* stmt: selection_stmt  */
#line 225 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 1799 "parser.tab.c"
    break;

  case 30: /* stmt: iteration_stmt  */
#line 226 "parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 1805 "parser.tab.c"
    break;

  case 31: /* stmt: return_stmt  */
#line 227 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1811 "parser.tab.c"
    break;

  case 32: /* stmt: print_stmt  */
#line 228 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1817 "parser.tab.c"
    break;

  case 33: /* stmt: scan_stmt  */
#line 229 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1823 "parser.tab.c"
    break;

  case 34: /* stmt: var_declaration  */
#line 230 "parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1829 "parser.tab.c"
    break;

  case 35: /* expr_stmt: expr SEMICOLON  */
#line 234 "parser.y"
                   {
        (yyval.node) = createNode(NODE_EXPR_STMT, "ExprStmt");
        addChild((yyval.node), (yyvsp[-1].node));
    }
#line 1838 "parser.tab.c"
    break;

  case 36: /* expr_stmt: expr error  */
#line 238 "parser.y"
                 {
        detailed_error("expected ';' after expression",
                      "expressions must be terminated with semicolon",
                      "    expression;  // add semicolon here");
        yyerrok;
        (yyval.node) = createNode(NODE_EXPR_STMT, "ExprStmt");
        addChild((yyval.node), (yyvsp[-1].node));
    }
#line 1851 "parser.tab.c"
    break;

  case 37: /* expr_stmt: SEMICOLON  */
#line 246 "parser.y"
                {
        (yyval.node) = createNode(NODE_EXPR_STMT, "EmptyStmt");
    }
#line 1859 "parser.tab.c"
    break;

  case 38: /* selection_stmt: IF LPAREN expr RPAREN stmt  */
#line 252 "parser.y"
                               {
        (yyval.node) = createNode(NODE_IF_STMT, "If");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 1869 "parser.tab.c"
    break;

  case 39: /* selection_stmt: IF LPAREN expr RPAREN stmt ELSE stmt  */
#line 257 "parser.y"
                                           {
        (yyval.node) = createNode(NODE_IF_STMT, "IfElse");
        addChild((yyval.node), (yyvsp[-4].node));
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 1880 "parser.tab.c"
    break;

  case 40: /* selection_stmt: IF LPAREN expr error  */
#line 263 "parser.y"
                           {
        detailed_error("expected ')' after if condition",
                      "if statement condition is not properly closed",
                      "    if (condition) {  // add closing parenthesis\n        statement;\n    }");
        yyerrok;
        (yyval.node) = createNode(NODE_IF_STMT, "If");
        addChild((yyval.node), (yyvsp[-1].node));
        addChild((yyval.node), createNode(NODE_EXPR_STMT, "EmptyStmt"));
    }
#line 1894 "parser.tab.c"
    break;

  case 41: /* selection_stmt: IF error  */
#line 272 "parser.y"
               {
        detailed_error("expected '(' after 'if'",
                      "if keyword must be followed by opening parenthesis",
                      "    if (condition) {\n        statement;\n    }");
        yyerrok;
        (yyval.node) = createNode(NODE_IF_STMT, "If");
    }
#line 1906 "parser.tab.c"
    break;

  case 42: /* iteration_stmt: WHILE LPAREN expr RPAREN stmt  */
#line 282 "parser.y"
                                  {
        (yyval.node) = createNode(NODE_WHILE_STMT, "While");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 1916 "parser.tab.c"
    break;

  case 43: /* iteration_stmt: WHILE LPAREN expr error  */
#line 287 "parser.y"
                              {
        detailed_error("expected ')' after while condition",
                      "while loop condition is not properly closed",
                      "    while (condition) {  // add closing parenthesis\n        statement;\n    }");
        yyerrok;
        (yyval.node) = createNode(NODE_WHILE_STMT, "While");
        addChild((yyval.node), (yyvsp[-1].node));
        addChild((yyval.node), createNode(NODE_EXPR_STMT, "EmptyStmt"));
    }
#line 1930 "parser.tab.c"
    break;

  case 44: /* iteration_stmt: FOR LPAREN expr_stmt expr_stmt expr RPAREN stmt  */
#line 296 "parser.y"
                                                      {
        (yyval.node) = createNode(NODE_FOR_STMT, "For");
        addChild((yyval.node), (yyvsp[-4].node));
        addChild((yyval.node), (yyvsp[-3].node));
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 1942 "parser.tab.c"
    break;

  case 45: /* iteration_stmt: FOR LPAREN expr_stmt expr_stmt expr error  */
#line 303 "parser.y"
                                                {
        detailed_error("expected ')' after for loop header",
                      "for loop is missing closing parenthesis",
                      "    for (init; condition; increment) {  // add ')' here\n        statement;\n    }");
        yyerrok;
        (yyval.node) = createNode(NODE_FOR_STMT, "For");
        addChild((yyval.node), (yyvsp[-3].node));
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[-1].node));
        addChild((yyval.node), createNode(NODE_EXPR_STMT, "EmptyStmt"));
    }
#line 1958 "parser.tab.c"
    break;

  case 46: /* iteration_stmt: FOR error  */
#line 314 "parser.y"
                {
        detailed_error("expected '(' after 'for'",
                      "for keyword must be followed by opening parenthesis",
                      "    for (init; condition; increment) {\n        statement;\n    }");
        yyerrok;
        (yyval.node) = createNode(NODE_FOR_STMT, "For");
    }
#line 1970 "parser.tab.c"
    break;

  case 47: /* return_stmt: RETURN SEMICOLON  */
#line 324 "parser.y"
                     {
        (yyval.node) = createNode(NODE_RETURN_STMT, "Return");
    }
#line 1978 "parser.tab.c"
    break;

  case 48: /* return_stmt: RETURN expr SEMICOLON  */
#line 327 "parser.y"
                            {
        (yyval.node) = createNode(NODE_RETURN_STMT, "Return");
        addChild((yyval.node), (yyvsp[-1].node));
    }
#line 1987 "parser.tab.c"
    break;

  case 49: /* return_stmt: RETURN expr error  */
#line 331 "parser.y"
                        {
        detailed_error("expected ';' after return statement",
                      "return statement must be terminated with semicolon",
                      "    return value;  // add semicolon here");
        yyerrok;
        (yyval.node) = createNode(NODE_RETURN_STMT, "Return");
        addChild((yyval.node), (yyvsp[-1].node));
    }
#line 2000 "parser.tab.c"
    break;

  case 50: /* print_stmt: PRINTF LPAREN STRING COMMA arg_list RPAREN SEMICOLON  */
#line 342 "parser.y"
                                                         {
        (yyval.node) = createNode(NODE_PRINT_STMT, "Printf");
        ASTNode *fmt = createNode(NODE_IDENTIFIER, (yyvsp[-4].str));
        addChild((yyval.node), fmt);
        addChild((yyval.node), (yyvsp[-2].node));
        free((yyvsp[-4].str));
    }
#line 2012 "parser.tab.c"
    break;

  case 51: /* print_stmt: PRINTF LPAREN STRING RPAREN SEMICOLON  */
#line 349 "parser.y"
                                            {
        (yyval.node) = createNode(NODE_PRINT_STMT, "Printf");
        ASTNode *fmt = createNode(NODE_IDENTIFIER, (yyvsp[-2].str));
        addChild((yyval.node), fmt);
        free((yyvsp[-2].str));
    }
#line 2023 "parser.tab.c"
    break;

  case 52: /* print_stmt: PRINTF LPAREN STRING COMMA arg_list RPAREN error  */
#line 355 "parser.y"
                                                       {
        detailed_error("expected ';' after printf statement",
                      "printf must be terminated with semicolon",
                      "    printf(\"format\", args);  // add semicolon");
        yyerrok;
        (yyval.node) = createNode(NODE_PRINT_STMT, "Printf");
        ASTNode *fmt = createNode(NODE_IDENTIFIER, (yyvsp[-4].str));
        addChild((yyval.node), fmt);
        addChild((yyval.node), (yyvsp[-2].node));
        free((yyvsp[-4].str));
    }
#line 2039 "parser.tab.c"
    break;

  case 53: /* print_stmt: PRINTF LPAREN STRING RPAREN error  */
#line 366 "parser.y"
                                        {
        detailed_error("expected ';' after printf statement",
                      "printf must be terminated with semicolon",
                      "    printf(\"format\");  // add semicolon");
        yyerrok;
        (yyval.node) = createNode(NODE_PRINT_STMT, "Printf");
        ASTNode *fmt = createNode(NODE_IDENTIFIER, (yyvsp[-2].str));
        addChild((yyval.node), fmt);
        free((yyvsp[-2].str));
    }
#line 2054 "parser.tab.c"
    break;

  case 54: /* print_stmt: PRINTF error  */
#line 376 "parser.y"
                   {
        detailed_error("expected '(' after printf",
                      "printf requires format string in parentheses",
                      "    printf(\"format string\", args);");
        yyerrok;
        (yyval.node) = createNode(NODE_PRINT_STMT, "Printf");
    }
#line 2066 "parser.tab.c"
    break;

  case 55: /* scan_stmt: SCANF LPAREN STRING COMMA arg_list RPAREN SEMICOLON  */
#line 386 "parser.y"
                                                        {
        (yyval.node) = createNode(NODE_SCAN_STMT, "Scanf");
        ASTNode *fmt = createNode(NODE_IDENTIFIER, (yyvsp[-4].str));
        addChild((yyval.node), fmt);
        addChild((yyval.node), (yyvsp[-2].node));
        free((yyvsp[-4].str));
    }
#line 2078 "parser.tab.c"
    break;

  case 56: /* scan_stmt: SCANF LPAREN STRING COMMA arg_list RPAREN error  */
#line 393 "parser.y"
                                                      {
        detailed_error("expected ';' after scanf statement",
                      "scanf must be terminated with semicolon",
                      "    scanf(\"format\", &var);  // add semicolon");
        yyerrok;
        (yyval.node) = createNode(NODE_SCAN_STMT, "Scanf");
        ASTNode *fmt = createNode(NODE_IDENTIFIER, (yyvsp[-4].str));
        addChild((yyval.node), fmt);
        addChild((yyval.node), (yyvsp[-2].node));
        free((yyvsp[-4].str));
    }
#line 2094 "parser.tab.c"
    break;

  case 57: /* expr: ID ASSIGN expr  */
#line 407 "parser.y"
                   {
        (yyval.node) = createNode(NODE_ASSIGN, "=");
        ASTNode *id = createNode(NODE_IDENTIFIER, (yyvsp[-2].str));
        addChild((yyval.node), id);
        addChild((yyval.node), (yyvsp[0].node));
        free((yyvsp[-2].str));
    }
#line 2106 "parser.tab.c"
    break;

  case 58: /* expr: simple_expr  */
#line 414 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 2112 "parser.tab.c"
    break;

  case 59: /* simple_expr: simple_expr OR additive_expr  */
#line 418 "parser.y"
                                 {
        (yyval.node) = createNode(NODE_BINARY_OP, "||");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2122 "parser.tab.c"
    break;

  case 60: /* simple_expr: simple_expr AND additive_expr  */
#line 423 "parser.y"
                                    {
        (yyval.node) = createNode(NODE_BINARY_OP, "&&");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2132 "parser.tab.c"
    break;

  case 61: /* simple_expr: simple_expr EQ additive_expr  */
#line 428 "parser.y"
                                   {
        (yyval.node) = createNode(NODE_BINARY_OP, "==");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2142 "parser.tab.c"
    break;

  case 62: /* simple_expr: simple_expr NE additive_expr  */
#line 433 "parser.y"
                                   {
        (yyval.node) = createNode(NODE_BINARY_OP, "!=");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2152 "parser.tab.c"
    break;

  case 63: /* simple_expr: simple_expr LT additive_expr  */
#line 438 "parser.y"
                                   {
        (yyval.node) = createNode(NODE_BINARY_OP, "<");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2162 "parser.tab.c"
    break;

  case 64: /* simple_expr: simple_expr LE additive_expr  */
#line 443 "parser.y"
                                   {
        (yyval.node) = createNode(NODE_BINARY_OP, "<=");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2172 "parser.tab.c"
    break;

  case 65: /* simple_expr: simple_expr GT additive_expr  */
#line 448 "parser.y"
                                   {
        (yyval.node) = createNode(NODE_BINARY_OP, ">");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2182 "parser.tab.c"
    break;

  case 66: /* simple_expr: simple_expr GE additive_expr  */
#line 453 "parser.y"
                                   {
        (yyval.node) = createNode(NODE_BINARY_OP, ">=");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2192 "parser.tab.c"
    break;

  case 67: /* simple_expr: additive_expr  */
#line 458 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2198 "parser.tab.c"
    break;

  case 68: /* additive_expr: additive_expr PLUS term  */
#line 462 "parser.y"
                            {
        (yyval.node) = createNode(NODE_BINARY_OP, "+");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2208 "parser.tab.c"
    break;

  case 69: /* additive_expr: additive_expr MINUS term  */
#line 467 "parser.y"
                               {
        (yyval.node) = createNode(NODE_BINARY_OP, "-");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2218 "parser.tab.c"
    break;

  case 70: /* additive_expr: term  */
#line 472 "parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2224 "parser.tab.c"
    break;

  case 71: /* term: term MULT factor  */
#line 476 "parser.y"
                     {
        (yyval.node) = createNode(NODE_BINARY_OP, "*");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2234 "parser.tab.c"
    break;

  case 72: /* term: term DIV factor  */
#line 481 "parser.y"
                      {
        (yyval.node) = createNode(NODE_BINARY_OP, "/");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2244 "parser.tab.c"
    break;

  case 73: /* term: term MOD factor  */
#line 486 "parser.y"
                      {
        (yyval.node) = createNode(NODE_BINARY_OP, "%");
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2254 "parser.tab.c"
    break;

  case 74: /* term: factor  */
#line 491 "parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2260 "parser.tab.c"
    break;

  case 75: /* factor: LPAREN expr RPAREN  */
#line 495 "parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 2266 "parser.tab.c"
    break;

  case 76: /* factor: ID  */
#line 496 "parser.y"
         {
        (yyval.node) = createNode(NODE_IDENTIFIER, (yyvsp[0].str));
        free((yyvsp[0].str));
    }
#line 2275 "parser.tab.c"
    break;

  case 77: /* factor: call  */
#line 500 "parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2281 "parser.tab.c"
    break;

  case 78: /* factor: INT_CONST  */
#line 501 "parser.y"
                {
        (yyval.node) = createNode(NODE_INT_LITERAL, "int");
        (yyval.node)->value.int_val = (yyvsp[0].int_val);
        (yyval.node)->data_type = TYPE_INT;
    }
#line 2291 "parser.tab.c"
    break;

  case 79: /* factor: FLOAT_CONST  */
#line 506 "parser.y"
                  {
        (yyval.node) = createNode(NODE_FLOAT_LITERAL, "float");
        (yyval.node)->value.float_val = (yyvsp[0].float_val);
        (yyval.node)->data_type = TYPE_FLOAT;
    }
#line 2301 "parser.tab.c"
    break;

  case 80: /* factor: MINUS factor  */
#line 511 "parser.y"
                                {
        (yyval.node) = createNode(NODE_UNARY_OP, "-");
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2310 "parser.tab.c"
    break;

  case 81: /* factor: NOT factor  */
#line 515 "parser.y"
                 {
        (yyval.node) = createNode(NODE_UNARY_OP, "!");
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2319 "parser.tab.c"
    break;

  case 82: /* call: ID LPAREN args RPAREN  */
#line 522 "parser.y"
                          {
        (yyval.node) = createNode(NODE_FUNC_CALL, (yyvsp[-3].str));
        addChild((yyval.node), (yyvsp[-1].node));
        free((yyvsp[-3].str));
    }
#line 2329 "parser.tab.c"
    break;

  case 83: /* call: ID LPAREN RPAREN  */
#line 527 "parser.y"
                       {
        (yyval.node) = createNode(NODE_FUNC_CALL, (yyvsp[-2].str));
        ASTNode *empty_args = createNode(NODE_COMPOUND_STMT, "EmptyArgs");
        addChild((yyval.node), empty_args);
        free((yyvsp[-2].str));
    }
#line 2340 "parser.tab.c"
    break;

  case 84: /* call: ID LPAREN error RPAREN  */
#line 533 "parser.y"
                             {
        char msg[512];
        snprintf(msg, sizeof(msg), "invalid argument list for function '%s'", (yyvsp[-3].str));
        detailed_error(msg, 
                      "check for syntax errors in function arguments",
                      "    function(arg1, arg2);  // comma-separated arguments");
        yyerrok;
        (yyval.node) = createNode(NODE_FUNC_CALL, (yyvsp[-3].str));
        addChild((yyval.node), createNode(NODE_COMPOUND_STMT, "EmptyArgs"));
        free((yyvsp[-3].str));
    }
#line 2356 "parser.tab.c"
    break;

  case 85: /* args: arg_list  */
#line 547 "parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2362 "parser.tab.c"
    break;

  case 86: /* arg_list: arg_list COMMA expr  */
#line 551 "parser.y"
                        {
        (yyval.node) = (yyvsp[-2].node);
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2371 "parser.tab.c"
    break;

  case 87: /* arg_list: expr  */
#line 555 "parser.y"
           {
        (yyval.node) = createNode(NODE_COMPOUND_STMT, "ArgList");
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 2380 "parser.tab.c"
    break;

  case 88: /* arg_list: AMPERSAND ID  */
#line 559 "parser.y"
                   {
        (yyval.node) = createNode(NODE_COMPOUND_STMT, "ArgList");
        ASTNode *ref = createNode(NODE_UNARY_OP, "&");
        ASTNode *id = createNode(NODE_IDENTIFIER, (yyvsp[0].str));
        addChild(ref, id);
        addChild((yyval.node), ref);
        free((yyvsp[0].str));
    }
#line 2393 "parser.tab.c"
    break;

  case 89: /* arg_list: arg_list COMMA AMPERSAND ID  */
#line 567 "parser.y"
                                  {
        (yyval.node) = (yyvsp[-3].node);
        ASTNode *ref = createNode(NODE_UNARY_OP, "&");
        ASTNode *id = createNode(NODE_IDENTIFIER, (yyvsp[0].str));
        addChild(ref, id);
        addChild((yyval.node), ref);
        free((yyvsp[0].str));
    }
#line 2406 "parser.tab.c"
    break;


#line 2410 "parser.tab.c"

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

#line 577 "parser.y"
