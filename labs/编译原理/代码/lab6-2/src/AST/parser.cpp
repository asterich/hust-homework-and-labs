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
#line 3 "parser.y"

    #include "ast.h"
    #include "define.h"
    #include <memory>
    #include <cstring>
    #include <stdarg.h>
    using namespace std;
    unique_ptr<CompUnitAST> root; /* the top level root node of our final AST */

    extern int yylineno;
    extern int yylex();
    extern void yyerror(const char *s);
    extern void initFileName(char *name);
    char filename[100];

#line 87 "parser.cpp"

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

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_FLOAT = 4,                      /* FLOAT  */
  YYSYMBOL_ID = 5,                         /* ID  */
  YYSYMBOL_GTE = 6,                        /* GTE  */
  YYSYMBOL_LTE = 7,                        /* LTE  */
  YYSYMBOL_GT = 8,                         /* GT  */
  YYSYMBOL_LT = 9,                         /* LT  */
  YYSYMBOL_EQ = 10,                        /* EQ  */
  YYSYMBOL_NEQ = 11,                       /* NEQ  */
  YYSYMBOL_INTTYPE = 12,                   /* INTTYPE  */
  YYSYMBOL_FLOATTYPE = 13,                 /* FLOATTYPE  */
  YYSYMBOL_VOID = 14,                      /* VOID  */
  YYSYMBOL_CONST = 15,                     /* CONST  */
  YYSYMBOL_RETURN = 16,                    /* RETURN  */
  YYSYMBOL_IF = 17,                        /* IF  */
  YYSYMBOL_ELSE = 18,                      /* ELSE  */
  YYSYMBOL_WHILE = 19,                     /* WHILE  */
  YYSYMBOL_BREAK = 20,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 21,                  /* CONTINUE  */
  YYSYMBOL_LP = 22,                        /* LP  */
  YYSYMBOL_RP = 23,                        /* RP  */
  YYSYMBOL_LB = 24,                        /* LB  */
  YYSYMBOL_RB = 25,                        /* RB  */
  YYSYMBOL_LC = 26,                        /* LC  */
  YYSYMBOL_RC = 27,                        /* RC  */
  YYSYMBOL_COMMA = 28,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 29,                 /* SEMICOLON  */
  YYSYMBOL_NOT = 30,                       /* NOT  */
  YYSYMBOL_POS = 31,                       /* POS  */
  YYSYMBOL_NEG = 32,                       /* NEG  */
  YYSYMBOL_ASSIGN = 33,                    /* ASSIGN  */
  YYSYMBOL_MINUS = 34,                     /* MINUS  */
  YYSYMBOL_ADD = 35,                       /* ADD  */
  YYSYMBOL_MUL = 36,                       /* MUL  */
  YYSYMBOL_DIV = 37,                       /* DIV  */
  YYSYMBOL_MOD = 38,                       /* MOD  */
  YYSYMBOL_AND = 39,                       /* AND  */
  YYSYMBOL_OR = 40,                        /* OR  */
  YYSYMBOL_LOWER_THEN_ELSE = 41,           /* LOWER_THEN_ELSE  */
  YYSYMBOL_YYACCEPT = 42,                  /* $accept  */
  YYSYMBOL_Program = 43,                   /* Program  */
  YYSYMBOL_CompUnit = 44,                  /* CompUnit  */
  YYSYMBOL_DeclDef = 45,                   /* DeclDef  */
  YYSYMBOL_Decl = 46,                      /* Decl  */
  YYSYMBOL_BType = 47,                     /* BType  */
  YYSYMBOL_DefList = 48,                   /* DefList  */
  YYSYMBOL_Def = 49,                       /* Def  */
  YYSYMBOL_Arrays = 50,                    /* Arrays  */
  YYSYMBOL_InitVal = 51,                   /* InitVal  */
  YYSYMBOL_InitValList = 52,               /* InitValList  */
  YYSYMBOL_FuncDef = 53,                   /* FuncDef  */
  YYSYMBOL_VoidType = 54,                  /* VoidType  */
  YYSYMBOL_FuncFParamList = 55,            /* FuncFParamList  */
  YYSYMBOL_FuncFParam = 56,                /* FuncFParam  */
  YYSYMBOL_Block = 57,                     /* Block  */
  YYSYMBOL_BlockItemList = 58,             /* BlockItemList  */
  YYSYMBOL_BlockItem = 59,                 /* BlockItem  */
  YYSYMBOL_Stmt = 60,                      /* Stmt  */
  YYSYMBOL_SelectStmt = 61,                /* SelectStmt  */
  YYSYMBOL_IterationStmt = 62,             /* IterationStmt  */
  YYSYMBOL_ReturnStmt = 63,                /* ReturnStmt  */
  YYSYMBOL_Exp = 64,                       /* Exp  */
  YYSYMBOL_Cond = 65,                      /* Cond  */
  YYSYMBOL_LVal = 66,                      /* LVal  */
  YYSYMBOL_PrimaryExp = 67,                /* PrimaryExp  */
  YYSYMBOL_Number = 68,                    /* Number  */
  YYSYMBOL_UnaryExp = 69,                  /* UnaryExp  */
  YYSYMBOL_Call = 70,                      /* Call  */
  YYSYMBOL_UnaryOp = 71,                   /* UnaryOp  */
  YYSYMBOL_FuncCParamList = 72,            /* FuncCParamList  */
  YYSYMBOL_MulExp = 73,                    /* MulExp  */
  YYSYMBOL_AddExp = 74,                    /* AddExp  */
  YYSYMBOL_RelExp = 75,                    /* RelExp  */
  YYSYMBOL_EqExp = 76,                     /* EqExp  */
  YYSYMBOL_LAndExp = 77,                   /* LAndExp  */
  YYSYMBOL_LOrExp = 78                     /* LOrExp  */
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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
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
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   222

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  91
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  161

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   296


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
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   118,   118,   124,   128,   135,   139,   146,   152,   161,
     164,   170,   174,   181,   187,   192,   197,   204,   208,   216,
     220,   223,   230,   234,   241,   248,   254,   261,   269,   275,
     279,   286,   292,   298,   308,   311,   318,   322,   329,   333,
     340,   344,   350,   355,   359,   363,   369,   375,   380,   388,
     393,   402,   409,   413,   418,   424,   430,   434,   442,   447,
     452,   460,   466,   475,   480,   485,   493,   498,   507,   510,
     513,   519,   523,   530,   535,   542,   549,   559,   564,   571,
     581,   586,   593,   600,   607,   617,   622,   629,   639,   644,
     652,   657
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
  "\"end of file\"", "error", "\"invalid token\"", "INT", "FLOAT", "ID",
  "GTE", "LTE", "GT", "LT", "EQ", "NEQ", "INTTYPE", "FLOATTYPE", "VOID",
  "CONST", "RETURN", "IF", "ELSE", "WHILE", "BREAK", "CONTINUE", "LP",
  "RP", "LB", "RB", "LC", "RC", "COMMA", "SEMICOLON", "NOT", "POS", "NEG",
  "ASSIGN", "MINUS", "ADD", "MUL", "DIV", "MOD", "AND", "OR",
  "LOWER_THEN_ELSE", "$accept", "Program", "CompUnit", "DeclDef", "Decl",
  "BType", "DefList", "Def", "Arrays", "InitVal", "InitValList", "FuncDef",
  "VoidType", "FuncFParamList", "FuncFParam", "Block", "BlockItemList",
  "BlockItem", "Stmt", "SelectStmt", "IterationStmt", "ReturnStmt", "Exp",
  "Cond", "LVal", "PrimaryExp", "Number", "UnaryExp", "Call", "UnaryOp",
  "FuncCParamList", "MulExp", "AddExp", "RelExp", "EqExp", "LAndExp",
  "LOrExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-113)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     191,  -113,  -113,  -113,    66,    15,   191,  -113,  -113,    24,
    -113,    28,    31,  -113,  -113,    40,    58,  -113,    22,    -8,
      96,     5,   156,    19,    32,    31,  -113,   141,  -113,    26,
      43,    71,  -113,  -113,  -113,   122,   156,  -113,  -113,  -113,
      38,  -113,  -113,  -113,  -113,  -113,   156,   -25,   106,    16,
    -113,  -113,   156,    19,  -113,    26,    79,    55,  -113,    45,
      26,    66,   133,    77,    57,  -113,  -113,   156,   156,   156,
     156,   156,  -113,  -113,   130,    70,  -113,  -113,    26,   147,
      89,   109,   120,   146,  -113,  -113,  -113,    31,  -113,    93,
    -113,  -113,  -113,  -113,  -113,   158,   112,   145,  -113,  -113,
    -113,  -113,    98,  -113,  -113,  -113,  -113,   -25,   -25,  -113,
      19,  -113,  -113,  -113,   159,   156,   156,  -113,  -113,  -113,
    -113,  -113,   156,   165,  -113,   156,  -113,  -113,   169,   106,
     201,   155,   154,   171,   189,   184,    77,  -113,   113,   156,
     156,   156,   156,   156,   156,   156,   156,   113,  -113,   176,
     106,   106,   106,   106,   201,   201,   155,   154,  -113,   113,
    -113
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     9,    10,    28,     0,     0,     2,     4,     5,     0,
       6,     0,     0,     1,     3,    16,     0,    11,     0,    16,
       0,     0,     0,     0,    15,     0,     8,     0,     7,     0,
       0,     0,    29,    61,    62,    56,     0,    70,    69,    68,
       0,    59,    63,    60,    73,    64,     0,    77,    54,     0,
      14,    19,     0,     0,    12,     0,     0,     0,    25,    31,
       0,     0,     0,    57,     0,    17,    65,     0,     0,     0,
       0,     0,    20,    23,     0,     0,    13,    27,     0,     0,
       0,     0,     0,     0,    34,    40,    38,     0,    45,     0,
      36,    39,    47,    48,    46,     0,    59,     0,    24,    30,
      66,    71,     0,    58,    74,    75,    76,    79,    78,    21,
       0,    18,    26,    53,     0,     0,     0,    44,    43,    35,
      37,    42,     0,    32,    67,     0,    22,    52,     0,    80,
      85,    88,    90,    55,     0,     0,    33,    72,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    41,    49,
      81,    82,    83,    84,    86,    87,    89,    91,    51,     0,
      50
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -113,  -113,  -113,   208,   -50,     4,   203,   192,   -32,   -44,
    -113,  -113,  -113,   193,   157,   -23,  -113,   127,  -112,  -113,
    -113,  -113,   -22,   105,   -55,  -113,  -113,   116,  -113,  -113,
    -113,   103,    56,    36,    74,    76,  -113
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,     7,     8,    30,    16,    17,    24,    50,
      74,    10,    11,    31,    32,    88,    89,    90,    91,    92,
      93,    94,    95,   128,    41,    42,    43,    44,    45,    46,
     102,    47,    48,   130,   131,   132,   133
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      40,    51,    96,    63,     9,    73,    58,    86,    12,    76,
       9,    67,    68,    69,    64,    13,    22,     1,     2,    33,
      34,    35,    33,    34,    35,    23,   149,    51,    29,    15,
      75,    51,    77,    18,    96,   158,    19,    98,    36,    86,
     101,    36,    49,    72,    27,    49,    37,   160,    59,    37,
      38,    39,    57,    38,    39,   112,    52,   114,    33,    34,
      35,    87,    21,    65,    22,    53,   126,     1,     2,    97,
       4,    79,    80,    23,    81,    82,    83,    36,     1,     2,
     103,    57,    84,    96,    85,    37,    25,    26,    51,    38,
      39,   136,    96,    87,    60,   111,    33,    34,    35,    61,
     135,    52,    78,   137,    96,     1,     2,    61,     4,    79,
      80,   115,    81,    82,    83,    36,    33,    34,    35,    57,
     119,   124,    85,    37,    25,    28,   125,    38,    39,    79,
      80,   116,    81,    82,    83,    36,    33,    34,    35,    57,
      70,    71,    85,    37,    62,   122,    22,    38,    39,   117,
      33,    34,    35,     1,     2,    36,   100,   109,   110,    33,
      34,    35,    66,    37,    55,   143,   144,    38,    39,    36,
     123,   129,   129,   107,   108,   118,   113,    37,    36,   154,
     155,    38,    39,   104,   105,   106,    37,   121,   127,    22,
      38,    39,   138,   145,   159,   150,   151,   152,   153,   129,
     129,   129,   129,     1,     2,     3,     4,   139,   140,   141,
     142,   146,   147,   148,    14,    20,   120,    54,    99,   156,
      56,   134,   157
};

static const yytype_uint8 yycheck[] =
{
      22,    23,    57,    35,     0,    49,    29,    57,     4,    53,
       6,    36,    37,    38,    36,     0,    24,    12,    13,     3,
       4,     5,     3,     4,     5,    33,   138,    49,    23,     5,
      52,    53,    55,     5,    89,   147,     5,    60,    22,    89,
      62,    22,    26,    27,    22,    26,    30,   159,     5,    30,
      34,    35,    26,    34,    35,    78,    24,    79,     3,     4,
       5,    57,    22,    25,    24,    33,   110,    12,    13,    24,
      15,    16,    17,    33,    19,    20,    21,    22,    12,    13,
      23,    26,    27,   138,    29,    30,    28,    29,   110,    34,
      35,   123,   147,    89,    23,    25,     3,     4,     5,    28,
     122,    24,    23,   125,   159,    12,    13,    28,    15,    16,
      17,    22,    19,    20,    21,    22,     3,     4,     5,    26,
      27,    23,    29,    30,    28,    29,    28,    34,    35,    16,
      17,    22,    19,    20,    21,    22,     3,     4,     5,    26,
      34,    35,    29,    30,    22,    33,    24,    34,    35,    29,
       3,     4,     5,    12,    13,    22,    23,    27,    28,     3,
       4,     5,    46,    30,    23,    10,    11,    34,    35,    22,
      25,   115,   116,    70,    71,    29,    29,    30,    22,   143,
     144,    34,    35,    67,    68,    69,    30,    29,    29,    24,
      34,    35,    23,    39,    18,   139,   140,   141,   142,   143,
     144,   145,   146,    12,    13,    14,    15,     6,     7,     8,
       9,    40,    23,    29,     6,    12,    89,    25,    61,   145,
      27,   116,   146
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    12,    13,    14,    15,    43,    44,    45,    46,    47,
      53,    54,    47,     0,    45,     5,    48,    49,     5,     5,
      48,    22,    24,    33,    50,    28,    29,    22,    29,    23,
      47,    55,    56,     3,     4,     5,    22,    30,    34,    35,
      64,    66,    67,    68,    69,    70,    71,    73,    74,    26,
      51,    64,    24,    33,    49,    23,    55,    26,    57,     5,
      23,    28,    22,    50,    64,    25,    69,    36,    37,    38,
      34,    35,    27,    51,    52,    64,    51,    57,    23,    16,
      17,    19,    20,    21,    27,    29,    46,    47,    57,    58,
      59,    60,    61,    62,    63,    64,    66,    24,    57,    56,
      23,    64,    72,    23,    69,    69,    69,    73,    73,    27,
      28,    25,    57,    29,    64,    22,    22,    29,    29,    27,
      59,    29,    33,    25,    23,    28,    51,    29,    65,    74,
      75,    76,    77,    78,    65,    64,    50,    64,    23,     6,
       7,     8,     9,    10,    11,    39,    40,    23,    29,    60,
      74,    74,    74,    74,    75,    75,    76,    77,    60,    18,
      60
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    46,    46,    47,
      47,    48,    48,    49,    49,    49,    49,    50,    50,    51,
      51,    51,    52,    52,    53,    53,    53,    53,    54,    55,
      55,    56,    56,    56,    57,    57,    58,    58,    59,    59,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    61,
      61,    62,    63,    63,    64,    65,    66,    66,    67,    67,
      67,    68,    68,    69,    69,    69,    70,    70,    71,    71,
      71,    72,    72,    73,    73,    73,    73,    74,    74,    74,
      75,    75,    75,    75,    75,    76,    76,    76,    77,    77,
      78,    78
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     4,     3,     1,
       1,     1,     3,     4,     3,     2,     1,     3,     4,     1,
       2,     3,     3,     1,     6,     5,     6,     5,     1,     1,
       3,     2,     4,     5,     2,     3,     1,     2,     1,     1,
       1,     4,     2,     2,     2,     1,     1,     1,     1,     5,
       7,     5,     3,     2,     1,     1,     1,     2,     3,     1,
       1,     1,     1,     1,     1,     2,     3,     4,     1,     1,
       1,     1,     3,     1,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       1,     3
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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
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

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
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
  YYLTYPE *yylloc;
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: CompUnit  */
#line 118 "parser.y"
                 {
          root = unique_ptr<CompUnitAST>((yyvsp[0].compUnit));
		}
#line 1666 "parser.cpp"
    break;

  case 3: /* CompUnit: CompUnit DeclDef  */
#line 124 "parser.y"
                          {
            (yyval.compUnit) = (yyvsp[-1].compUnit);
            (yyval.compUnit)->declDefList.push_back(unique_ptr<DeclDefAST>((yyvsp[0].declDef)));
		}
#line 1675 "parser.cpp"
    break;

  case 4: /* CompUnit: DeclDef  */
#line 128 "parser.y"
                         {
            (yyval.compUnit) = new CompUnitAST();
		    (yyval.compUnit)->declDefList.push_back(unique_ptr<DeclDefAST>((yyvsp[0].declDef)));
		}
#line 1684 "parser.cpp"
    break;

  case 5: /* DeclDef: Decl  */
#line 135 "parser.y"
              {
			(yyval.declDef) = new DeclDefAST();
			(yyval.declDef)->Decl = unique_ptr<DeclAST>((yyvsp[0].decl));
		}
#line 1693 "parser.cpp"
    break;

  case 6: /* DeclDef: FuncDef  */
#line 139 "parser.y"
                         {
            (yyval.declDef) =  new DeclDefAST();
			(yyval.declDef)->funcDef = unique_ptr<FuncDefAST>((yyvsp[0].funcDef));
		}
#line 1702 "parser.cpp"
    break;

  case 7: /* Decl: CONST BType DefList SEMICOLON  */
#line 146 "parser.y"
                                      {
            (yyval.decl) = new DeclAST();
            (yyval.decl)->isConst = true;
			(yyval.decl)->bType = (yyvsp[-2].ty);
			(yyval.decl)->defList.swap((yyvsp[-1].defList)->list);
		}
#line 1713 "parser.cpp"
    break;

  case 8: /* Decl: BType DefList SEMICOLON  */
#line 152 "parser.y"
                                 {
            (yyval.decl) = new DeclAST();
            (yyval.decl)->isConst = false;
			(yyval.decl)->bType = (yyvsp[-2].ty);
			(yyval.decl)->defList.swap((yyvsp[-1].defList)->list);
        }
#line 1724 "parser.cpp"
    break;

  case 9: /* BType: INTTYPE  */
#line 161 "parser.y"
                {
			(yyval.ty) = TYPE_INT;
		}
#line 1732 "parser.cpp"
    break;

  case 10: /* BType: FLOATTYPE  */
#line 164 "parser.y"
                           {
            (yyval.ty) = TYPE_FLOAT;
        }
#line 1740 "parser.cpp"
    break;

  case 11: /* DefList: Def  */
#line 170 "parser.y"
            {
			(yyval.defList) = new DefListAST();
            (yyval.defList)->list.push_back(unique_ptr<DefAST>((yyvsp[0].def)));
		}
#line 1749 "parser.cpp"
    break;

  case 12: /* DefList: DefList COMMA Def  */
#line 174 "parser.y"
                                   {
			(yyval.defList) = (yyvsp[-2].defList);
            (yyval.defList)->list.push_back(unique_ptr<DefAST>((yyvsp[0].def)));
		}
#line 1758 "parser.cpp"
    break;

  case 13: /* Def: ID Arrays ASSIGN InitVal  */
#line 181 "parser.y"
                                 {
			(yyval.def) = new DefAST();
			(yyval.def)->id = unique_ptr<string>((yyvsp[-3].token));
			(yyval.def)->arrays.swap((yyvsp[-2].arrays)->list);
			(yyval.def)->initVal = unique_ptr<InitValAST>((yyvsp[0].initVal));
		}
#line 1769 "parser.cpp"
    break;

  case 14: /* Def: ID ASSIGN InitVal  */
#line 187 "parser.y"
                           {
			(yyval.def) = new DefAST();
			(yyval.def)->id = unique_ptr<string>((yyvsp[-2].token));
			(yyval.def)->initVal = unique_ptr<InitValAST>((yyvsp[0].initVal));
        }
#line 1779 "parser.cpp"
    break;

  case 15: /* Def: ID Arrays  */
#line 192 "parser.y"
                   {
            (yyval.def) = new DefAST();
            (yyval.def)->id = unique_ptr<string>((yyvsp[-1].token));
            (yyval.def)->arrays.swap((yyvsp[0].arrays)->list);
        }
#line 1789 "parser.cpp"
    break;

  case 16: /* Def: ID  */
#line 197 "parser.y"
            {
            (yyval.def) = new DefAST();
            (yyval.def)->id = unique_ptr<string>((yyvsp[0].token));
        }
#line 1798 "parser.cpp"
    break;

  case 17: /* Arrays: LB Exp RB  */
#line 204 "parser.y"
                  {
			(yyval.arrays) = new ArraysAST();
			(yyval.arrays)->list.push_back(unique_ptr<AddExpAST>((yyvsp[-1].addExp)));
		}
#line 1807 "parser.cpp"
    break;

  case 18: /* Arrays: Arrays LB Exp RB  */
#line 208 "parser.y"
                          {
			(yyval.arrays) = (yyvsp[-3].arrays);
			(yyval.arrays)->list.push_back(unique_ptr<AddExpAST>((yyvsp[-1].addExp)));
		}
#line 1816 "parser.cpp"
    break;

  case 19: /* InitVal: Exp  */
#line 216 "parser.y"
             {
			(yyval.initVal) = new InitValAST();
			(yyval.initVal)->exp = unique_ptr<AddExpAST>((yyvsp[0].addExp));
		}
#line 1825 "parser.cpp"
    break;

  case 20: /* InitVal: LC RC  */
#line 220 "parser.y"
                        {
			(yyval.initVal) = new InitValAST();
		}
#line 1833 "parser.cpp"
    break;

  case 21: /* InitVal: LC InitValList RC  */
#line 223 "parser.y"
                                   {
			(yyval.initVal) = new InitValAST();
			(yyval.initVal)->initValList.swap((yyvsp[-1].initValList)->list);
		}
#line 1842 "parser.cpp"
    break;

  case 22: /* InitValList: InitValList COMMA InitVal  */
#line 230 "parser.y"
                                      {
			(yyval.initValList) = (yyvsp[-2].initValList);
			(yyval.initValList)->list.push_back(unique_ptr<InitValAST>((yyvsp[0].initVal)));
		}
#line 1851 "parser.cpp"
    break;

  case 23: /* InitValList: InitVal  */
#line 234 "parser.y"
                         {
			(yyval.initValList)  = new InitValListAST();
			(yyval.initValList)->list.push_back(unique_ptr<InitValAST>((yyvsp[0].initVal)));
		}
#line 1860 "parser.cpp"
    break;

  case 24: /* FuncDef: BType ID LP FuncFParamList RP Block  */
#line 241 "parser.y"
                                             {
			(yyval.funcDef) = new FuncDefAST();
			(yyval.funcDef)->funcType = (yyvsp[-5].ty);
			(yyval.funcDef)->id = unique_ptr<string>((yyvsp[-4].token));
			(yyval.funcDef)->funcFParamList.swap((yyvsp[-2].FuncFParamList)->list);
			(yyval.funcDef)->block = unique_ptr<BlockAST>((yyvsp[0].block));
		}
#line 1872 "parser.cpp"
    break;

  case 25: /* FuncDef: BType ID LP RP Block  */
#line 248 "parser.y"
                              {
			(yyval.funcDef) = new FuncDefAST();
			(yyval.funcDef)->funcType = (yyvsp[-4].ty);
			(yyval.funcDef)->id = unique_ptr<string>((yyvsp[-3].token));
			(yyval.funcDef)->block = unique_ptr<BlockAST>((yyvsp[0].block));
		}
#line 1883 "parser.cpp"
    break;

  case 26: /* FuncDef: VoidType ID LP FuncFParamList RP Block  */
#line 254 "parser.y"
                                                {
			(yyval.funcDef) = new FuncDefAST();
			(yyval.funcDef)->funcType = (yyvsp[-5].ty);
			(yyval.funcDef)->id = unique_ptr<string>((yyvsp[-4].token));
			(yyval.funcDef)->funcFParamList.swap((yyvsp[-2].FuncFParamList)->list);
			(yyval.funcDef)->block = unique_ptr<BlockAST>((yyvsp[0].block));
		}
#line 1895 "parser.cpp"
    break;

  case 27: /* FuncDef: VoidType ID LP RP Block  */
#line 261 "parser.y"
                                 {
			(yyval.funcDef) = new FuncDefAST();
			(yyval.funcDef)->funcType = (yyvsp[-4].ty);
			(yyval.funcDef)->id = unique_ptr<string>((yyvsp[-3].token));
			(yyval.funcDef)->block = unique_ptr<BlockAST>((yyvsp[0].block));
		}
#line 1906 "parser.cpp"
    break;

  case 28: /* VoidType: VOID  */
#line 269 "parser.y"
               {
			(yyval.ty) = TYPE_VOID;
		}
#line 1914 "parser.cpp"
    break;

  case 29: /* FuncFParamList: FuncFParam  */
#line 275 "parser.y"
                           {
				(yyval.FuncFParamList) = new FuncFParamListAST();
				(yyval.FuncFParamList)->list.push_back(unique_ptr<FuncFParamAST>((yyvsp[0].funcFParam)));
			}
#line 1923 "parser.cpp"
    break;

  case 30: /* FuncFParamList: FuncFParamList COMMA FuncFParam  */
#line 279 "parser.y"
                                                         {
				(yyval.FuncFParamList) = (yyvsp[-2].FuncFParamList);
				(yyval.FuncFParamList)->list.push_back(unique_ptr<FuncFParamAST>((yyvsp[0].funcFParam)));
			}
#line 1932 "parser.cpp"
    break;

  case 31: /* FuncFParam: BType ID  */
#line 286 "parser.y"
                          {
				(yyval.funcFParam) = new FuncFParamAST();
				(yyval.funcFParam)->bType = (yyvsp[-1].ty);
				(yyval.funcFParam)->id = unique_ptr<string>((yyvsp[0].token));
				(yyval.funcFParam)->isArray = false;
			}
#line 1943 "parser.cpp"
    break;

  case 32: /* FuncFParam: BType ID LB RB  */
#line 292 "parser.y"
                                        {
				(yyval.funcFParam) = new FuncFParamAST();
				(yyval.funcFParam)->bType = (yyvsp[-3].ty);
				(yyval.funcFParam)->id = unique_ptr<string>((yyvsp[-2].token));
				(yyval.funcFParam)->isArray = true;
			}
#line 1954 "parser.cpp"
    break;

  case 33: /* FuncFParam: BType ID LB RB Arrays  */
#line 298 "parser.y"
                                               {
				(yyval.funcFParam) = new FuncFParamAST();
				(yyval.funcFParam)->bType = (yyvsp[-4].ty);
				(yyval.funcFParam)->id = unique_ptr<string>((yyvsp[-3].token));
				(yyval.funcFParam)->isArray = true;
				(yyval.funcFParam)->arrays.swap((yyvsp[0].arrays)->list);
			}
#line 1966 "parser.cpp"
    break;

  case 34: /* Block: LC RC  */
#line 308 "parser.y"
               {
			(yyval.block) = new BlockAST();
		}
#line 1974 "parser.cpp"
    break;

  case 35: /* Block: LC BlockItemList RC  */
#line 311 "parser.y"
                                     {
			(yyval.block) = new BlockAST();
			(yyval.block)->blockItemList.swap((yyvsp[-1].blockItemList)->list);
		}
#line 1983 "parser.cpp"
    break;

  case 36: /* BlockItemList: BlockItem  */
#line 318 "parser.y"
                        {
				(yyval.blockItemList) = new BlockItemListAST();
				(yyval.blockItemList)->list.push_back(unique_ptr<BlockItemAST>((yyvsp[0].blockItem)));
			}
#line 1992 "parser.cpp"
    break;

  case 37: /* BlockItemList: BlockItemList BlockItem  */
#line 322 "parser.y"
                                                 {
				(yyval.blockItemList) = (yyvsp[-1].blockItemList);
				(yyval.blockItemList)->list.push_back(unique_ptr<BlockItemAST>((yyvsp[0].blockItem)));
			}
#line 2001 "parser.cpp"
    break;

  case 38: /* BlockItem: Decl  */
#line 329 "parser.y"
                      {
				(yyval.blockItem) = new BlockItemAST();
				(yyval.blockItem)->decl = unique_ptr<DeclAST>((yyvsp[0].decl));
			}
#line 2010 "parser.cpp"
    break;

  case 39: /* BlockItem: Stmt  */
#line 333 "parser.y"
                              {
				(yyval.blockItem) = new BlockItemAST();
				(yyval.blockItem)->stmt = unique_ptr<StmtAST>((yyvsp[0].stmt));
			}
#line 2019 "parser.cpp"
    break;

  case 40: /* Stmt: SEMICOLON  */
#line 340 "parser.y"
                        {
			(yyval.stmt) = new StmtAST();
			(yyval.stmt)->sType = SEMI;
		}
#line 2028 "parser.cpp"
    break;

  case 41: /* Stmt: LVal ASSIGN Exp SEMICOLON  */
#line 344 "parser.y"
                                           {
			(yyval.stmt) = new StmtAST();
			(yyval.stmt)->sType = ASS;
			(yyval.stmt)->lVal = unique_ptr<LValAST>((yyvsp[-3].lVal));
			(yyval.stmt)->exp = unique_ptr<AddExpAST>((yyvsp[-1].addExp));
		}
#line 2039 "parser.cpp"
    break;

  case 42: /* Stmt: Exp SEMICOLON  */
#line 350 "parser.y"
                               {
			(yyval.stmt) = new StmtAST();
			(yyval.stmt)->sType = EXP;
			(yyval.stmt)->exp = unique_ptr<AddExpAST>((yyvsp[-1].addExp));
		}
#line 2049 "parser.cpp"
    break;

  case 43: /* Stmt: CONTINUE SEMICOLON  */
#line 355 "parser.y"
                                {
			(yyval.stmt) = new StmtAST();
			(yyval.stmt)->sType = CONT;
		}
#line 2058 "parser.cpp"
    break;

  case 44: /* Stmt: BREAK SEMICOLON  */
#line 359 "parser.y"
                         {
			(yyval.stmt) = new StmtAST();
			(yyval.stmt)->sType = BRE;
		}
#line 2067 "parser.cpp"
    break;

  case 45: /* Stmt: Block  */
#line 363 "parser.y"
               {
			(yyval.stmt) = new StmtAST();
			(yyval.stmt)->sType = BLK;
			(yyval.stmt)->block = unique_ptr<BlockAST>((yyvsp[0].block));

		}
#line 2078 "parser.cpp"
    break;

  case 46: /* Stmt: ReturnStmt  */
#line 369 "parser.y"
                    {
			(yyval.stmt) = new StmtAST();
			(yyval.stmt)->sType = RET;
			(yyval.stmt)->returnStmt = unique_ptr<ReturnStmtAST>((yyvsp[0].returnStmt));

		}
#line 2089 "parser.cpp"
    break;

  case 47: /* Stmt: SelectStmt  */
#line 375 "parser.y"
                    {
			(yyval.stmt) = new StmtAST();
			(yyval.stmt)->sType = SEL;
			(yyval.stmt)->selectStmt = unique_ptr<SelectStmtAST>((yyvsp[0].selectStmt));
		}
#line 2099 "parser.cpp"
    break;

  case 48: /* Stmt: IterationStmt  */
#line 380 "parser.y"
                       {
			(yyval.stmt) = new StmtAST();
			(yyval.stmt)->sType = ITER;
			(yyval.stmt)->iterationStmt = unique_ptr<IterationStmtAST>((yyvsp[0].iterationStmt));
		}
#line 2109 "parser.cpp"
    break;

  case 49: /* SelectStmt: IF LP Cond RP Stmt  */
#line 388 "parser.y"
                                                         {
				(yyval.selectStmt) = new SelectStmtAST();
				(yyval.selectStmt)->cond = unique_ptr<LOrExpAST>((yyvsp[-2].lOrExp));
				(yyval.selectStmt)->ifStmt = unique_ptr<StmtAST>((yyvsp[0].stmt));
			}
#line 2119 "parser.cpp"
    break;

  case 50: /* SelectStmt: IF LP Cond RP Stmt ELSE Stmt  */
#line 393 "parser.y"
                                                      {
				(yyval.selectStmt) = new SelectStmtAST();
				(yyval.selectStmt)->cond = unique_ptr<LOrExpAST>((yyvsp[-4].lOrExp));
				(yyval.selectStmt)->ifStmt = unique_ptr<StmtAST>((yyvsp[-2].stmt));
				(yyval.selectStmt)->elseStmt = unique_ptr<StmtAST>((yyvsp[0].stmt));
			}
#line 2130 "parser.cpp"
    break;

  case 51: /* IterationStmt: WHILE LP Cond RP Stmt  */
#line 402 "parser.y"
                                      {
					(yyval.iterationStmt) = new IterationStmtAST();
					(yyval.iterationStmt)->cond = unique_ptr<LOrExpAST>((yyvsp[-2].lOrExp));
					(yyval.iterationStmt)->stmt = unique_ptr<StmtAST>((yyvsp[0].stmt));
				}
#line 2140 "parser.cpp"
    break;

  case 52: /* ReturnStmt: RETURN Exp SEMICOLON  */
#line 409 "parser.y"
                                     {
				(yyval.returnStmt) = new ReturnStmtAST();
				(yyval.returnStmt)->exp = unique_ptr<AddExpAST>((yyvsp[-1].addExp));
			}
#line 2149 "parser.cpp"
    break;

  case 53: /* ReturnStmt: RETURN SEMICOLON  */
#line 413 "parser.y"
                              {
				(yyval.returnStmt) = new ReturnStmtAST();
			}
#line 2157 "parser.cpp"
    break;

  case 54: /* Exp: AddExp  */
#line 418 "parser.y"
               {
			(yyval.addExp) = (yyvsp[0].addExp);
		}
#line 2165 "parser.cpp"
    break;

  case 55: /* Cond: LOrExp  */
#line 424 "parser.y"
               {
			(yyval.lOrExp) = (yyvsp[0].lOrExp);
		}
#line 2173 "parser.cpp"
    break;

  case 56: /* LVal: ID  */
#line 430 "parser.y"
           {
			(yyval.lVal) = new LValAST();
			(yyval.lVal)->id = unique_ptr<string>((yyvsp[0].token));
		}
#line 2182 "parser.cpp"
    break;

  case 57: /* LVal: ID Arrays  */
#line 434 "parser.y"
                           {
			(yyval.lVal) = new LValAST();
			(yyval.lVal)->id = unique_ptr<string>((yyvsp[-1].token));
			(yyval.lVal)->arrays.swap((yyvsp[0].arrays)->list);
		}
#line 2192 "parser.cpp"
    break;

  case 58: /* PrimaryExp: LP Exp RP  */
#line 442 "parser.y"
                           {
				(yyval.primaryExp) = new PrimaryExpAST();
				(yyval.primaryExp)->exp = unique_ptr<AddExpAST>((yyvsp[-1].addExp));
				
			}
#line 2202 "parser.cpp"
    break;

  case 59: /* PrimaryExp: LVal  */
#line 447 "parser.y"
                              {
				(yyval.primaryExp) = new PrimaryExpAST();
				(yyval.primaryExp)->lval = unique_ptr<LValAST>((yyvsp[0].lVal));
				
			}
#line 2212 "parser.cpp"
    break;

  case 60: /* PrimaryExp: Number  */
#line 452 "parser.y"
                                {
				(yyval.primaryExp) = new PrimaryExpAST();
				(yyval.primaryExp)->number = unique_ptr<NumberAST>((yyvsp[0].number));
				
			}
#line 2222 "parser.cpp"
    break;

  case 61: /* Number: INT  */
#line 460 "parser.y"
             {
			(yyval.number) = new NumberAST();
			(yyval.number)->isInt = true;
			(yyval.number)->intval = (yyvsp[0].int_val);
			
		}
#line 2233 "parser.cpp"
    break;

  case 62: /* Number: FLOAT  */
#line 466 "parser.y"
                       {
			(yyval.number) = new NumberAST();
			(yyval.number)->isInt = false;
			(yyval.number)->floatval = (yyvsp[0].float_val);
			
		}
#line 2244 "parser.cpp"
    break;

  case 63: /* UnaryExp: PrimaryExp  */
#line 475 "parser.y"
                                {
				(yyval.unaryExp) = new UnaryExpAST();
				(yyval.unaryExp)->primaryExp = unique_ptr<PrimaryExpAST>((yyvsp[0].primaryExp));
				
			}
#line 2254 "parser.cpp"
    break;

  case 64: /* UnaryExp: Call  */
#line 480 "parser.y"
                              {
				(yyval.unaryExp) = new UnaryExpAST();
				(yyval.unaryExp)->call = unique_ptr<CallAST>((yyvsp[0].call));
				
			}
#line 2264 "parser.cpp"
    break;

  case 65: /* UnaryExp: UnaryOp UnaryExp  */
#line 485 "parser.y"
                                          {
				(yyval.unaryExp) = new UnaryExpAST();
				(yyval.unaryExp)->op = (yyvsp[-1].op);
				(yyval.unaryExp)->unaryExp = unique_ptr<UnaryExpAST>((yyvsp[0].unaryExp));
			}
#line 2274 "parser.cpp"
    break;

  case 66: /* Call: ID LP RP  */
#line 493 "parser.y"
              {
		(yyval.call) = new CallAST();
		(yyval.call)->id = unique_ptr<string>((yyvsp[-2].token));
		
	}
#line 2284 "parser.cpp"
    break;

  case 67: /* Call: ID LP FuncCParamList RP  */
#line 498 "parser.y"
                                  {
		(yyval.call) = new CallAST();
		(yyval.call)->id = unique_ptr<string>((yyvsp[-3].token));
		(yyval.call)->funcCParamList.swap((yyvsp[-1].funcCParamList)->list);
		
	 }
#line 2295 "parser.cpp"
    break;

  case 68: /* UnaryOp: ADD  */
#line 507 "parser.y"
             {
            (yyval.op) = UOP_ADD;
		}
#line 2303 "parser.cpp"
    break;

  case 69: /* UnaryOp: MINUS  */
#line 510 "parser.y"
               {
            (yyval.op) = UOP_MINUS;
		}
#line 2311 "parser.cpp"
    break;

  case 70: /* UnaryOp: NOT  */
#line 513 "parser.y"
             {
            (yyval.op) = UOP_NOT;
		}
#line 2319 "parser.cpp"
    break;

  case 71: /* FuncCParamList: Exp  */
#line 519 "parser.y"
                    {
				(yyval.funcCParamList) = new FuncCParamListAST();
				(yyval.funcCParamList)->list.push_back(unique_ptr<AddExpAST>((yyvsp[0].addExp)));
			}
#line 2328 "parser.cpp"
    break;

  case 72: /* FuncCParamList: FuncCParamList COMMA Exp  */
#line 523 "parser.y"
                                                  {
				(yyval.funcCParamList) = (FuncCParamListAST*) (yyvsp[-2].funcCParamList);
				(yyval.funcCParamList)->list.push_back(unique_ptr<AddExpAST>((yyvsp[0].addExp)));
			}
#line 2337 "parser.cpp"
    break;

  case 73: /* MulExp: UnaryExp  */
#line 530 "parser.y"
                  {
			(yyval.mulExp) = new MulExpAST();
			(yyval.mulExp)->unaryExp = unique_ptr<UnaryExpAST>((yyvsp[0].unaryExp));
			
		}
#line 2347 "parser.cpp"
    break;

  case 74: /* MulExp: MulExp MUL UnaryExp  */
#line 535 "parser.y"
                                     {
			(yyval.mulExp) = new MulExpAST();
			(yyval.mulExp)->mulExp = unique_ptr<MulExpAST>((yyvsp[-2].mulExp));
			(yyval.mulExp)->op = MOP_MUL;
			(yyval.mulExp)->unaryExp = unique_ptr<UnaryExpAST>((yyvsp[0].unaryExp));
			
		}
#line 2359 "parser.cpp"
    break;

  case 75: /* MulExp: MulExp DIV UnaryExp  */
#line 542 "parser.y"
                                     {
			(yyval.mulExp) = new MulExpAST();
			(yyval.mulExp)->mulExp = unique_ptr<MulExpAST>((yyvsp[-2].mulExp));
			(yyval.mulExp)->op = MOP_DIV;
			(yyval.mulExp)->unaryExp = unique_ptr<UnaryExpAST>((yyvsp[0].unaryExp));
			
		}
#line 2371 "parser.cpp"
    break;

  case 76: /* MulExp: MulExp MOD UnaryExp  */
#line 549 "parser.y"
                                     {
			(yyval.mulExp) = new MulExpAST();
			(yyval.mulExp)->mulExp = unique_ptr<MulExpAST>((yyvsp[-2].mulExp));
			(yyval.mulExp)->op = MOP_MOD;
			(yyval.mulExp)->unaryExp = unique_ptr<UnaryExpAST>((yyvsp[0].unaryExp));
			
		}
#line 2383 "parser.cpp"
    break;

  case 77: /* AddExp: MulExp  */
#line 559 "parser.y"
                {
			(yyval.addExp) = new AddExpAST();
			(yyval.addExp)->mulExp = unique_ptr<MulExpAST>((yyvsp[0].mulExp));
			
		}
#line 2393 "parser.cpp"
    break;

  case 78: /* AddExp: AddExp ADD MulExp  */
#line 564 "parser.y"
                                   {
			(yyval.addExp) = new AddExpAST();
			(yyval.addExp)->addExp = unique_ptr<AddExpAST>((yyvsp[-2].addExp));
			(yyval.addExp)->op = AOP_ADD;
			(yyval.addExp)->mulExp = unique_ptr<MulExpAST>((yyvsp[0].mulExp));
			
		}
#line 2405 "parser.cpp"
    break;

  case 79: /* AddExp: AddExp MINUS MulExp  */
#line 571 "parser.y"
                                     {
			(yyval.addExp) = new AddExpAST();
			(yyval.addExp)->addExp = unique_ptr<AddExpAST>((yyvsp[-2].addExp));
			(yyval.addExp)->op = AOP_MINUS;
			(yyval.addExp)->mulExp = unique_ptr<MulExpAST>((yyvsp[0].mulExp));
			
		}
#line 2417 "parser.cpp"
    break;

  case 80: /* RelExp: AddExp  */
#line 581 "parser.y"
                {
			(yyval.relExp) = new RelExpAST();
			(yyval.relExp)->addExp = unique_ptr<AddExpAST>((yyvsp[0].addExp));
			
		}
#line 2427 "parser.cpp"
    break;

  case 81: /* RelExp: RelExp GTE AddExp  */
#line 586 "parser.y"
                                  {
			(yyval.relExp) = new RelExpAST();
			(yyval.relExp)->relExp = unique_ptr<RelExpAST>((yyvsp[-2].relExp));
			(yyval.relExp)->op = ROP_GTE;
			(yyval.relExp)->addExp = unique_ptr<AddExpAST>((yyvsp[0].addExp));
			
		}
#line 2439 "parser.cpp"
    break;

  case 82: /* RelExp: RelExp LTE AddExp  */
#line 593 "parser.y"
                                  {
			(yyval.relExp) = new RelExpAST();
			(yyval.relExp)->relExp = unique_ptr<RelExpAST>((yyvsp[-2].relExp));
			(yyval.relExp)->op = ROP_LTE;
			(yyval.relExp)->addExp = unique_ptr<AddExpAST>((yyvsp[0].addExp));
			
		}
#line 2451 "parser.cpp"
    break;

  case 83: /* RelExp: RelExp GT AddExp  */
#line 600 "parser.y"
                                  {
			(yyval.relExp) = new RelExpAST();
			(yyval.relExp)->relExp = unique_ptr<RelExpAST>((yyvsp[-2].relExp));
			(yyval.relExp)->op = ROP_GT;
			(yyval.relExp)->addExp = unique_ptr<AddExpAST>((yyvsp[0].addExp));
			
		}
#line 2463 "parser.cpp"
    break;

  case 84: /* RelExp: RelExp LT AddExp  */
#line 607 "parser.y"
                                  {
			(yyval.relExp) = new RelExpAST();
			(yyval.relExp)->relExp = unique_ptr<RelExpAST>((yyvsp[-2].relExp));
			(yyval.relExp)->op = ROP_LT;
			(yyval.relExp)->addExp = unique_ptr<AddExpAST>((yyvsp[0].addExp));
			
		}
#line 2475 "parser.cpp"
    break;

  case 85: /* EqExp: RelExp  */
#line 617 "parser.y"
                {
			(yyval.eqExp) = new EqExpAST();
			(yyval.eqExp)->relExp = unique_ptr<RelExpAST>((yyvsp[0].relExp));
			
		}
#line 2485 "parser.cpp"
    break;

  case 86: /* EqExp: EqExp EQ RelExp  */
#line 622 "parser.y"
                                {
			(yyval.eqExp) = new EqExpAST();
			(yyval.eqExp)->eqExp = unique_ptr<EqExpAST>((yyvsp[-2].eqExp));
			(yyval.eqExp)->op = EOP_EQ;
			(yyval.eqExp)->relExp = unique_ptr<RelExpAST>((yyvsp[0].relExp));
			
		}
#line 2497 "parser.cpp"
    break;

  case 87: /* EqExp: EqExp NEQ RelExp  */
#line 629 "parser.y"
                                 {
			(yyval.eqExp) = new EqExpAST();
			(yyval.eqExp)->eqExp = unique_ptr<EqExpAST>((yyvsp[-2].eqExp));
			(yyval.eqExp)->op = EOP_NEQ;
			(yyval.eqExp)->relExp = unique_ptr<RelExpAST>((yyvsp[0].relExp));
			
		}
#line 2509 "parser.cpp"
    break;

  case 88: /* LAndExp: EqExp  */
#line 639 "parser.y"
               {
			(yyval.lAndExp) = new LAndExpAST();
			(yyval.lAndExp)->eqExp = unique_ptr<EqExpAST>((yyvsp[0].eqExp));
			
		}
#line 2519 "parser.cpp"
    break;

  case 89: /* LAndExp: LAndExp AND EqExp  */
#line 644 "parser.y"
                                   {
			(yyval.lAndExp) = new LAndExpAST();
			(yyval.lAndExp)->lAndExp = unique_ptr<LAndExpAST>((yyvsp[-2].lAndExp));
			(yyval.lAndExp)->eqExp = unique_ptr<EqExpAST>((yyvsp[0].eqExp));
		}
#line 2529 "parser.cpp"
    break;

  case 90: /* LOrExp: LAndExp  */
#line 652 "parser.y"
                 {
			(yyval.lOrExp) = new LOrExpAST();
			(yyval.lOrExp)->lAndExp = unique_ptr<LAndExpAST>((yyvsp[0].lAndExp));
			
		}
#line 2539 "parser.cpp"
    break;

  case 91: /* LOrExp: LOrExp OR LAndExp  */
#line 657 "parser.y"
                                   {
			(yyval.lOrExp) = new LOrExpAST();
			(yyval.lOrExp)->lOrExp = unique_ptr<LOrExpAST>((yyvsp[-2].lOrExp));
			(yyval.lOrExp)->lAndExp = unique_ptr<LAndExpAST>((yyvsp[0].lAndExp));
			
		}
#line 2550 "parser.cpp"
    break;


#line 2554 "parser.cpp"

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
  *++yylsp = yyloc;

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
          = {yyssp, yytoken, &yylloc};
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
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

#line 664 "parser.y"


void initFileName(char *name){
    strcpy(filename, name);
}

void yyerror(const char* fmt) {
    printf("%s:%d ", filename, yylloc.first_line);
    printf("%s\n", fmt);
}

