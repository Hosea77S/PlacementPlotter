/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         lefyyparse
#define yylex           lefyylex
#define yyerror         lefyyerror
#define yydebug         lefyydebug
#define yynerrs         lefyynerrs

#define yylval          lefyylval
#define yychar          lefyychar

/* Copy the first part of user declarations.  */
#line 1 "lef.y" /* yacc.c:339  */

/*
 *     This  file  is  part  of  the  Cadence  LEF/DEF  Open   Source
 *  Distribution,  Product Version 5.3, and is subject to the Cadence
 *  LEF/DEF Open Source License Agreement.   Your  continued  use  of
 *  this file constitutes your acceptance of the terms of the LEF/DEF
 *  Open Source License and an agreement to abide by its  terms.   If
 *  you  don't  agree  with  this, you must remove this and any other
 *  files which are part of the distribution and  destroy any  copies
 *  made.
 *
 *     For updates, support, or to become part of the LEF/DEF Community,
 *  check www.openeda.org for details.
 */

#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <math.h>
/* # include <sys/types.h> */
/* # include <sys/stat.h> */
/* # include <fcntl.h> */
/* # include <unistd.h> */
/* # ifndef	WIN32 */
/* # include <sys/param.h> */
/* # endif */
#include "FEF_stringhash_lef.h"
#include "lex_lef.h"
#include "lefiDefs.hpp"
#include "lefiUser.hpp"
#include "lefrCallBacks.hpp"
#ifdef WIN32
#include <malloc.h>
#endif

#define LYPROP_ECAP "EDGE_CAPACITANCE"

int lefRetVal;

/* Macro to describe how we handle a callback.
 * If the function was set then call it.
 * If the function returns non zero then there was an error
 * so call the error routine and exit.
 */
#define CALLBACK(func, typ, data) \
    if (func) { \
      if ((lefRetVal = (*func)(typ, data, lefrUserData)) == 0) { \
      } else if (lefRetVal == STOP_PARSE) { \
	return lefRetVal; \
      } else { \
	yyerror("Error in callback"); \
	return lefRetVal; \
      } \
    }

extern int lefNlines, lefNtokens, lefErrors;
extern FILE* lefFile;

/**********************************************************************/
/**********************************************************************/

#define C_EQ 0
#define C_NE 1
#define C_LT 2
#define C_LE 3
#define C_GT 4
#define C_GE 5

extern int lefDumbMode;  // for communicating with parser
extern int lefNoNum;     // likewise, says no numbers for the next N tokens
extern int lefNlToken;   // likewise
extern int lefDefIf;     // likewise

int lefNamesCaseSensitive = FALSE;  // are names case sensitive?

/* XXXXXXXXXXXXX check out these variables */
double lef_save_x, lef_save_y;  // for interpreting (*) notation of LEF/DEF

/* #define STRING_LIST_SIZE 1024 */
/* char string_list[STRING_LIST_SIZE]; */

static char temp_name[256];

static int siteDef, symDef, sizeDef, pinDef, obsDef, origDef;
static int useLenThr, lenThr;

int comp_str(char *s1, int op, char *s2)
{
    int k = strcmp(s1, s2);
    switch (op) {
	case C_EQ: return k == 0;
	case C_NE: return k != 0;
	case C_GT: return k >  0;
	case C_GE: return k >= 0;
	case C_LT: return k <  0;
	case C_LE: return k <= 0;
	}
    return 0;
}
int comp_num(double s1, int op, double s2)
{
    double k = s1 - s2;
    switch (op) {
	case C_EQ: return k == 0;
	case C_NE: return k != 0;
	case C_GT: return k >  0;
	case C_GE: return k >= 0;
	case C_LT: return k <  0;
	case C_LE: return k <= 0;
	}
    return 0;
}

#line 188 "lef.tab.c" /* yacc.c:339  */

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
   by #include "lef.tab.h".  */
#ifndef YY_LEFYY_LEF_TAB_H_INCLUDED
# define YY_LEFYY_LEF_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int lefyydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    K_HISTORY = 258,
    K_ABUT = 259,
    K_ABUTMENT = 260,
    K_ACTIVE = 261,
    K_ANALOG = 262,
    K_ANTENNAAREAFACTOR = 263,
    K_ARRAY = 264,
    K_BLOCK = 265,
    K_BOTTOMLEFT = 266,
    K_BOTTOMRIGHT = 267,
    K_BY = 268,
    K_CAPACITANCE = 269,
    K_CAPMULTIPLIER = 270,
    K_CLASS = 271,
    K_CLOCK = 272,
    K_CLOCKTYPE = 273,
    K_COLUMNMAJOR = 274,
    K_COMPONENTS = 275,
    K_CORE = 276,
    K_CORNER = 277,
    K_COVER = 278,
    K_CPERSQDIST = 279,
    K_CURRENT = 280,
    K_CURRENTSOURCE = 281,
    K_CUT = 282,
    K_DEFAULT = 283,
    K_DATABASE = 284,
    K_DATA = 285,
    K_DIELECTRIC = 286,
    K_DIRECTION = 287,
    K_DO = 288,
    K_EDGECAPACITANCE = 289,
    K_EEQ = 290,
    K_END = 291,
    K_ENDCAP = 292,
    K_FALL = 293,
    K_FALLCS = 294,
    K_FALLT0 = 295,
    K_FALLSATT1 = 296,
    K_FALLRS = 297,
    K_FALLSATCUR = 298,
    K_FALLTHRESH = 299,
    K_FEEDTHRU = 300,
    K_FIXED = 301,
    K_FOREIGN = 302,
    K_FROMPIN = 303,
    K_GENERATE = 304,
    K_GENERATOR = 305,
    K_GROUND = 306,
    K_HEIGHT = 307,
    K_HORIZONTAL = 308,
    K_INOUT = 309,
    K_INPUT = 310,
    K_INPUTNOISEMARGIN = 311,
    K_COMPONENTPIN = 312,
    K_INTRINSIC = 313,
    K_INVERT = 314,
    K_IRDROP = 315,
    K_ITERATE = 316,
    K_IV_TABLES = 317,
    K_LAYER = 318,
    K_LEAKAGE = 319,
    K_LEQ = 320,
    K_LIBRARY = 321,
    K_MACRO = 322,
    K_MATCH = 323,
    K_MAXDELAY = 324,
    K_MAXLOAD = 325,
    K_METALOVERHANG = 326,
    K_MILLIAMPS = 327,
    K_MILLIWATTS = 328,
    K_MINFEATURE = 329,
    K_MUSTJOIN = 330,
    K_NAMESCASESENSITIVE = 331,
    K_NANOSECONDS = 332,
    K_NETS = 333,
    K_NEW = 334,
    K_NONDEFAULTRULE = 335,
    K_NONINVERT = 336,
    K_NONUNATE = 337,
    K_OBS = 338,
    K_OHMS = 339,
    K_OFFSET = 340,
    K_ORIENTATION = 341,
    K_ORIGIN = 342,
    K_OUTPUT = 343,
    K_OUTPUTNOISEMARGIN = 344,
    K_OUTPUTRESISTANCE = 345,
    K_OVERHANG = 346,
    K_OVERLAP = 347,
    K_OFF = 348,
    K_ON = 349,
    K_OVERLAPS = 350,
    K_PAD = 351,
    K_PATH = 352,
    K_PATTERN = 353,
    K_PICOFARADS = 354,
    K_PIN = 355,
    K_PITCH = 356,
    K_PLACED = 357,
    K_POLYGON = 358,
    K_PORT = 359,
    K_POST = 360,
    K_POWER = 361,
    K_PRE = 362,
    K_PULLDOWNRES = 363,
    K_RECT = 364,
    K_RESISTANCE = 365,
    K_RESISTIVE = 366,
    K_RING = 367,
    K_RISE = 368,
    K_RISECS = 369,
    K_RISERS = 370,
    K_RISESATCUR = 371,
    K_RISETHRESH = 372,
    K_RISESATT1 = 373,
    K_RISET0 = 374,
    K_RISEVOLTAGETHRESHOLD = 375,
    K_FALLVOLTAGETHRESHOLD = 376,
    K_ROUTING = 377,
    K_ROWMAJOR = 378,
    K_RPERSQ = 379,
    K_SAMENET = 380,
    K_SCANUSE = 381,
    K_SHAPE = 382,
    K_SHRINKAGE = 383,
    K_SIGNAL = 384,
    K_SITE = 385,
    K_SIZE = 386,
    K_SOURCE = 387,
    K_SPACER = 388,
    K_SPACING = 389,
    K_SPECIALNETS = 390,
    K_STACK = 391,
    K_START = 392,
    K_STEP = 393,
    K_STOP = 394,
    K_STRUCTURE = 395,
    K_SYMMETRY = 396,
    K_TABLE = 397,
    K_THICKNESS = 398,
    K_TIEHIGH = 399,
    K_TIELOW = 400,
    K_TIEOFFR = 401,
    K_TIME = 402,
    K_TIMING = 403,
    K_TO = 404,
    K_TOPIN = 405,
    K_TOPLEFT = 406,
    K_TOPRIGHT = 407,
    K_TOPOFSTACKONLY = 408,
    K_TRISTATE = 409,
    K_TYPE = 410,
    K_UNATENESS = 411,
    K_UNITS = 412,
    K_USE = 413,
    K_VARIABLE = 414,
    K_VERTICAL = 415,
    K_VHI = 416,
    K_VIA = 417,
    K_VIARULE = 418,
    K_VLO = 419,
    K_VOLTAGE = 420,
    K_VOLTS = 421,
    K_WIDTH = 422,
    K_X = 423,
    K_Y = 424,
    K_R90 = 425,
    T_STRING = 426,
    QSTRING = 427,
    NUMBER = 428,
    K_N = 429,
    K_S = 430,
    K_E = 431,
    K_W = 432,
    K_FN = 433,
    K_FS = 434,
    K_FE = 435,
    K_FW = 436,
    K_R0 = 437,
    K_R180 = 438,
    K_R270 = 439,
    K_MX = 440,
    K_MY = 441,
    K_MXR90 = 442,
    K_MYR90 = 443,
    K_USER = 444,
    K_MASTERSLICE = 445,
    K_ENDMACRO = 446,
    K_ENDMACROPIN = 447,
    K_ENDVIARULE = 448,
    K_ENDVIA = 449,
    K_ENDLAYER = 450,
    K_ENDSITE = 451,
    K_CANPLACE = 452,
    K_CANNOTOCCUPY = 453,
    K_TRACKS = 454,
    K_FLOORPLAN = 455,
    K_GCELLGRID = 456,
    K_DEFAULTCAP = 457,
    K_MINPINS = 458,
    K_WIRECAP = 459,
    K_STABLE = 460,
    K_SETUP = 461,
    K_HOLD = 462,
    K_DEFINE = 463,
    K_DEFINES = 464,
    K_DEFINEB = 465,
    K_IF = 466,
    K_THEN = 467,
    K_ELSE = 468,
    K_FALSE = 469,
    K_TRUE = 470,
    K_EQ = 471,
    K_NE = 472,
    K_LE = 473,
    K_LT = 474,
    K_GE = 475,
    K_GT = 476,
    K_OR = 477,
    K_AND = 478,
    K_NOT = 479,
    K_DELAY = 480,
    K_TABLEDIMENSION = 481,
    K_TABLEAXIS = 482,
    K_TABLEENTRIES = 483,
    K_TRANSITIONTIME = 484,
    K_EXTENSION = 485,
    K_PROPDEF = 486,
    K_STRING = 487,
    K_INTEGER = 488,
    K_REAL = 489,
    K_RANGE = 490,
    K_PROPERTY = 491,
    K_VIRTUAL = 492,
    K_BUSBITCHARS = 493,
    K_VERSION = 494,
    K_BEGINEXT = 495,
    K_ENDEXT = 496,
    K_UNIVERSALNOISEMARGIN = 497,
    K_EDGERATETHRESHOLD1 = 498,
    K_CORRECTIONTABLE = 499,
    K_EDGERATESCALEFACTOR = 500,
    K_EDGERATETHRESHOLD2 = 501,
    K_VICTIMNOISE = 502,
    K_NOISETABLE = 503,
    K_EDGERATE = 504,
    K_VICTIMLENGTH = 505,
    K_CORRECTIONFACTOR = 506,
    K_OUTPUTPINANTENNASIZE = 507,
    K_INPUTPINANTENNASIZE = 508,
    K_INOUTPINANTENNASIZE = 509,
    K_CURRENTDEN = 510,
    K_PWL = 511,
    K_ANTENNALENGTHFACTOR = 512,
    K_TAPERRULE = 513,
    K_DIVIDERCHAR = 514,
    K_ANTENNASIZE = 515,
    K_ANTENNAMETALLENGTH = 516,
    K_ANTENNAMETALAREA = 517,
    K_RISESLEWLIMIT = 518,
    K_FALLSLEWLIMIT = 519,
    K_FUNCTION = 520,
    K_BUFFER = 521,
    K_INVERTER = 522,
    K_NAMEMAPSTRING = 523,
    K_NOWIREEXTENSIONATPIN = 524,
    K_WIREEXTENSION = 525,
    K_MESSAGE = 526,
    K_CREATEFILE = 527,
    K_OPENFILE = 528,
    K_CLOSEFILE = 529,
    K_WARNING = 530,
    K_ERROR = 531,
    K_FATALERROR = 532,
    K_RECOVERY = 533,
    K_SKEW = 534,
    K_ANYEDGE = 535,
    K_POSEDGE = 536,
    K_NEGEDGE = 537,
    K_SDFCONDSTART = 538,
    K_SDFCONDEND = 539,
    K_SDFCOND = 540,
    K_MPWH = 541,
    K_MPWL = 542,
    K_PERIOD = 543,
    K_ACCURRENTDENSITY = 544,
    K_DCCURRENTDENSITY = 545,
    K_AVERAGE = 546,
    K_PEAK = 547,
    K_RMS = 548,
    K_FREQUENCY = 549,
    K_CUTAREA = 550,
    K_MEGAHERTZ = 551,
    K_USELENGTHTHRESHOLD = 552,
    K_LENGTHTHRESHOLD = 553,
    IF = 554,
    LNOT = 555,
    UMINUS = 556
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 115 "lef.y" /* yacc.c:355  */

	double dval ;
	int    integer ;
	char * string ;
	POINT  pt;

#line 537 "lef.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE lefyylval;

int lefyyparse (void);

#endif /* !YY_LEFYY_LEF_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 552 "lef.tab.c" /* yacc.c:358  */

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1604

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  313
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  302
/* YYNRULES -- Number of rules.  */
#define YYNRULES  706
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1404

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   556

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     310,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     307,   308,   303,   302,     2,   301,     2,   304,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   306,
     311,   309,   312,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   305
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   218,   218,   219,   222,   226,   230,   234,   235,   236,
     240,   244,   244,   244,   244,   245,   245,   245,   245,   245,
     246,   246,   247,   247,   247,   247,   247,   247,   247,   248,
     248,   248,   249,   249,   250,   250,   251,   251,   251,   252,
     252,   252,   253,   256,   262,   270,   272,   276,   280,   284,
     285,   288,   290,   292,   294,   296,   298,   300,   300,   302,
     306,   310,   310,   319,   319,   325,   326,   331,   333,   335,
     337,   339,   356,   358,   360,   362,   364,   366,   368,   370,
     372,   374,   376,   378,   380,   382,   384,   386,   388,   388,
     391,   390,   393,   400,   399,   402,   411,   412,   413,   416,
     417,   422,   421,   426,   425,   430,   429,   435,   436,   441,
     440,   445,   444,   449,   448,   454,   455,   460,   461,   465,
     467,   469,   478,   480,   484,   489,   490,   493,   498,   499,
     503,   508,   509,   510,   511,   512,   516,   517,   520,   525,
     529,   534,   541,   543,   547,   549,   551,   553,   553,   555,
     560,   561,   565,   567,   569,   574,   576,   578,   580,   584,
     584,   589,   590,   591,   592,   593,   594,   595,   596,   597,
     598,   599,   600,   601,   602,   603,   604,   607,   611,   611,
     615,   617,   620,   625,   625,   629,   629,   634,   639,   648,
     649,   652,   654,   658,   659,   662,   662,   667,   668,   672,
     674,   676,   684,   687,   689,   692,   696,   696,   700,   702,
     706,   708,   710,   712,   714,   716,   719,   721,   726,   726,
     730,   734,   739,   744,   746,   749,   756,   765,   769,   773,
     778,   783,   785,   788,   792,   794,   797,   801,   805,   813,
     818,   817,   826,   828,   832,   833,   834,   835,   838,   838,
     843,   844,   848,   851,   854,   864,   863,   868,   870,   874,
     876,   878,   883,   887,   887,   891,   891,   895,   897,   901,
     903,   905,   910,   911,   912,   915,   919,   921,   925,   927,
     929,   934,   936,   940,   944,   944,   958,   958,   962,   964,
     968,   969,   970,   971,   972,   973,   975,   977,   979,   980,
     981,   983,   985,   987,   989,   991,   993,   995,   997,   997,
    1002,  1003,  1006,  1010,  1012,  1016,  1018,  1020,  1025,  1027,
    1029,  1033,  1038,  1039,  1040,  1041,  1042,  1043,  1046,  1047,
    1054,  1057,  1063,  1064,  1065,  1066,  1067,  1071,  1072,  1073,
    1077,  1078,  1079,  1080,  1081,  1082,  1085,  1089,  1094,  1096,
    1098,  1102,  1106,  1128,  1131,  1134,  1137,  1142,  1142,  1146,
    1146,  1151,  1153,  1162,  1167,  1171,  1181,  1185,  1185,  1189,
    1189,  1195,  1196,  1201,  1203,  1205,  1207,  1209,  1211,  1213,
    1213,  1215,  1217,  1219,  1221,  1223,  1225,  1227,  1229,  1231,
    1233,  1235,  1237,  1239,  1241,  1241,  1243,  1243,  1245,  1245,
    1247,  1247,  1249,  1251,  1253,  1255,  1257,  1259,  1261,  1263,
    1265,  1267,  1269,  1271,  1271,  1273,  1282,  1284,  1286,  1288,
    1290,  1296,  1297,  1301,  1303,  1305,  1310,  1311,  1312,  1313,
    1314,  1317,  1328,  1329,  1330,  1331,  1332,  1333,  1337,  1338,
    1339,  1340,  1344,  1345,  1346,  1347,  1351,  1352,  1356,  1356,
    1359,  1362,  1364,  1367,  1370,  1373,  1376,  1379,  1381,  1386,
    1391,  1396,  1398,  1402,  1402,  1405,  1405,  1412,  1417,  1432,
    1440,  1431,  1443,  1451,  1442,  1453,  1462,  1473,  1475,  1478,
    1482,  1491,  1502,  1514,  1526,  1526,  1530,  1534,  1538,  1546,
    1548,  1553,  1552,  1561,  1561,  1564,  1563,  1567,  1576,  1578,
    1580,  1582,  1584,  1586,  1588,  1590,  1592,  1594,  1596,  1598,
    1600,  1602,  1604,  1606,  1608,  1610,  1615,  1617,  1619,  1624,
    1626,  1628,  1630,  1635,  1637,  1639,  1644,  1646,  1648,  1653,
    1655,  1660,  1662,  1666,  1671,  1673,  1679,  1680,  1682,  1688,
    1690,  1695,  1697,  1699,  1704,  1706,  1711,  1713,  1718,  1717,
    1727,  1727,  1736,  1736,  1745,  1746,  1751,  1751,  1758,  1758,
    1765,  1765,  1772,  1772,  1778,  1781,  1781,  1787,  1793,  1797,
    1803,  1804,  1809,  1809,  1816,  1816,  1827,  1828,  1832,  1837,
    1837,  1842,  1842,  1847,  1847,  1849,  1849,  1851,  1851,  1856,
    1857,  1858,  1862,  1863,  1867,  1868,  1872,  1873,  1874,  1875,
    1876,  1877,  1878,  1880,  1884,  1885,  1886,  1887,  1888,  1889,
    1890,  1891,  1892,  1893,  1894,  1895,  1896,  1898,  1899,  1903,
    1909,  1911,  1920,  1925,  1926,  1927,  1928,  1929,  1930,  1931,
    1932,  1933,  1938,  1937,  1945,  1946,  1951,  1951,  1957,  1957,
    1963,  1963,  1969,  1969,  1975,  1975,  1981,  1981,  1987,  1987,
    1993,  1993,  2002,  2004,  2006,  2008,  2010,  2016,  2017,  2019,
    2021,  2027,  2028,  2034,  2035,  2041,  2042,  2046,  2056,  2065,
    2074,  2084,  2083,  2090,  2091,  2095,  2102,  2107,  2106,  2112,
    2115,  2121,  2122,  2126,  2125,  2133,  2136,  2142,  2141,  2150,
    2151,  2155,  2162,  2167,  2166,  2174,  2177,  2183,  2184,  2189,
    2188,  2196,  2199,  2204,  2208,  2212,  2216
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "K_HISTORY", "K_ABUT", "K_ABUTMENT",
  "K_ACTIVE", "K_ANALOG", "K_ANTENNAAREAFACTOR", "K_ARRAY", "K_BLOCK",
  "K_BOTTOMLEFT", "K_BOTTOMRIGHT", "K_BY", "K_CAPACITANCE",
  "K_CAPMULTIPLIER", "K_CLASS", "K_CLOCK", "K_CLOCKTYPE", "K_COLUMNMAJOR",
  "K_COMPONENTS", "K_CORE", "K_CORNER", "K_COVER", "K_CPERSQDIST",
  "K_CURRENT", "K_CURRENTSOURCE", "K_CUT", "K_DEFAULT", "K_DATABASE",
  "K_DATA", "K_DIELECTRIC", "K_DIRECTION", "K_DO", "K_EDGECAPACITANCE",
  "K_EEQ", "K_END", "K_ENDCAP", "K_FALL", "K_FALLCS", "K_FALLT0",
  "K_FALLSATT1", "K_FALLRS", "K_FALLSATCUR", "K_FALLTHRESH", "K_FEEDTHRU",
  "K_FIXED", "K_FOREIGN", "K_FROMPIN", "K_GENERATE", "K_GENERATOR",
  "K_GROUND", "K_HEIGHT", "K_HORIZONTAL", "K_INOUT", "K_INPUT",
  "K_INPUTNOISEMARGIN", "K_COMPONENTPIN", "K_INTRINSIC", "K_INVERT",
  "K_IRDROP", "K_ITERATE", "K_IV_TABLES", "K_LAYER", "K_LEAKAGE", "K_LEQ",
  "K_LIBRARY", "K_MACRO", "K_MATCH", "K_MAXDELAY", "K_MAXLOAD",
  "K_METALOVERHANG", "K_MILLIAMPS", "K_MILLIWATTS", "K_MINFEATURE",
  "K_MUSTJOIN", "K_NAMESCASESENSITIVE", "K_NANOSECONDS", "K_NETS", "K_NEW",
  "K_NONDEFAULTRULE", "K_NONINVERT", "K_NONUNATE", "K_OBS", "K_OHMS",
  "K_OFFSET", "K_ORIENTATION", "K_ORIGIN", "K_OUTPUT",
  "K_OUTPUTNOISEMARGIN", "K_OUTPUTRESISTANCE", "K_OVERHANG", "K_OVERLAP",
  "K_OFF", "K_ON", "K_OVERLAPS", "K_PAD", "K_PATH", "K_PATTERN",
  "K_PICOFARADS", "K_PIN", "K_PITCH", "K_PLACED", "K_POLYGON", "K_PORT",
  "K_POST", "K_POWER", "K_PRE", "K_PULLDOWNRES", "K_RECT", "K_RESISTANCE",
  "K_RESISTIVE", "K_RING", "K_RISE", "K_RISECS", "K_RISERS",
  "K_RISESATCUR", "K_RISETHRESH", "K_RISESATT1", "K_RISET0",
  "K_RISEVOLTAGETHRESHOLD", "K_FALLVOLTAGETHRESHOLD", "K_ROUTING",
  "K_ROWMAJOR", "K_RPERSQ", "K_SAMENET", "K_SCANUSE", "K_SHAPE",
  "K_SHRINKAGE", "K_SIGNAL", "K_SITE", "K_SIZE", "K_SOURCE", "K_SPACER",
  "K_SPACING", "K_SPECIALNETS", "K_STACK", "K_START", "K_STEP", "K_STOP",
  "K_STRUCTURE", "K_SYMMETRY", "K_TABLE", "K_THICKNESS", "K_TIEHIGH",
  "K_TIELOW", "K_TIEOFFR", "K_TIME", "K_TIMING", "K_TO", "K_TOPIN",
  "K_TOPLEFT", "K_TOPRIGHT", "K_TOPOFSTACKONLY", "K_TRISTATE", "K_TYPE",
  "K_UNATENESS", "K_UNITS", "K_USE", "K_VARIABLE", "K_VERTICAL", "K_VHI",
  "K_VIA", "K_VIARULE", "K_VLO", "K_VOLTAGE", "K_VOLTS", "K_WIDTH", "K_X",
  "K_Y", "K_R90", "T_STRING", "QSTRING", "NUMBER", "K_N", "K_S", "K_E",
  "K_W", "K_FN", "K_FS", "K_FE", "K_FW", "K_R0", "K_R180", "K_R270",
  "K_MX", "K_MY", "K_MXR90", "K_MYR90", "K_USER", "K_MASTERSLICE",
  "K_ENDMACRO", "K_ENDMACROPIN", "K_ENDVIARULE", "K_ENDVIA", "K_ENDLAYER",
  "K_ENDSITE", "K_CANPLACE", "K_CANNOTOCCUPY", "K_TRACKS", "K_FLOORPLAN",
  "K_GCELLGRID", "K_DEFAULTCAP", "K_MINPINS", "K_WIRECAP", "K_STABLE",
  "K_SETUP", "K_HOLD", "K_DEFINE", "K_DEFINES", "K_DEFINEB", "K_IF",
  "K_THEN", "K_ELSE", "K_FALSE", "K_TRUE", "K_EQ", "K_NE", "K_LE", "K_LT",
  "K_GE", "K_GT", "K_OR", "K_AND", "K_NOT", "K_DELAY", "K_TABLEDIMENSION",
  "K_TABLEAXIS", "K_TABLEENTRIES", "K_TRANSITIONTIME", "K_EXTENSION",
  "K_PROPDEF", "K_STRING", "K_INTEGER", "K_REAL", "K_RANGE", "K_PROPERTY",
  "K_VIRTUAL", "K_BUSBITCHARS", "K_VERSION", "K_BEGINEXT", "K_ENDEXT",
  "K_UNIVERSALNOISEMARGIN", "K_EDGERATETHRESHOLD1", "K_CORRECTIONTABLE",
  "K_EDGERATESCALEFACTOR", "K_EDGERATETHRESHOLD2", "K_VICTIMNOISE",
  "K_NOISETABLE", "K_EDGERATE", "K_VICTIMLENGTH", "K_CORRECTIONFACTOR",
  "K_OUTPUTPINANTENNASIZE", "K_INPUTPINANTENNASIZE",
  "K_INOUTPINANTENNASIZE", "K_CURRENTDEN", "K_PWL",
  "K_ANTENNALENGTHFACTOR", "K_TAPERRULE", "K_DIVIDERCHAR", "K_ANTENNASIZE",
  "K_ANTENNAMETALLENGTH", "K_ANTENNAMETALAREA", "K_RISESLEWLIMIT",
  "K_FALLSLEWLIMIT", "K_FUNCTION", "K_BUFFER", "K_INVERTER",
  "K_NAMEMAPSTRING", "K_NOWIREEXTENSIONATPIN", "K_WIREEXTENSION",
  "K_MESSAGE", "K_CREATEFILE", "K_OPENFILE", "K_CLOSEFILE", "K_WARNING",
  "K_ERROR", "K_FATALERROR", "K_RECOVERY", "K_SKEW", "K_ANYEDGE",
  "K_POSEDGE", "K_NEGEDGE", "K_SDFCONDSTART", "K_SDFCONDEND", "K_SDFCOND",
  "K_MPWH", "K_MPWL", "K_PERIOD", "K_ACCURRENTDENSITY",
  "K_DCCURRENTDENSITY", "K_AVERAGE", "K_PEAK", "K_RMS", "K_FREQUENCY",
  "K_CUTAREA", "K_MEGAHERTZ", "K_USELENGTHTHRESHOLD", "K_LENGTHTHRESHOLD",
  "IF", "LNOT", "'-'", "'+'", "'*'", "'/'", "UMINUS", "';'", "'('", "')'",
  "'='", "'\\n'", "'<'", "'>'", "$accept", "lef_file", "version",
  "dividerchar", "busbitchars", "rules", "end_library", "rule",
  "case_sensitivity", "wireextension", "units_section", "start_units",
  "units_rules", "units_rule", "$@1", "layer_rule", "start_layer", "$@2",
  "end_layer", "$@3", "layer_options", "layer_option", "$@4", "$@5", "$@6",
  "layer_table_type", "ac_layer_table_opt_list", "ac_layer_table_opt",
  "$@7", "$@8", "$@9", "dc_layer_table_opt_list", "dc_layer_table_opt",
  "$@10", "$@11", "$@12", "number_list", "layer_prop_list", "layer_prop",
  "current_density_pwl_list", "current_density_pwl", "cap_points",
  "cap_point", "res_points", "res_point", "layer_type", "layer_direction",
  "via", "via_keyword", "start_via", "via_options", "via_option", "$@13",
  "via_prop_list", "via_name_value_pair", "via_foreign", "start_foreign",
  "$@14", "orientation", "via_layer_rule", "via_layer", "$@15",
  "via_rects", "via_rect", "end_via", "$@16", "viarule_keyword", "$@17",
  "viarule", "viarule_generate", "viarule_layer_list", "opt_viarule_props",
  "viarule_props", "viarule_prop", "$@18", "viarule_prop_list",
  "viarule_layer", "via_names", "via_name", "viarule_layer_name", "$@19",
  "viarule_layer_options", "viarule_layer_option", "end_viarule", "$@20",
  "spacing_rule", "start_spacing", "end_spacing", "spacings", "spacing",
  "samenet_keyword", "irdrop", "start_irdrop", "end_irdrop", "ir_tables",
  "ir_table", "ir_table_values", "ir_table_value", "ir_tablename",
  "minfeature", "dielectric", "nondefault_rule", "$@21", "nd_rules",
  "nd_rule", "nd_prop", "$@22", "nd_prop_list", "nd_layer", "$@23",
  "nd_layer_stmts", "nd_layer_stmt", "site", "start_site", "$@24",
  "end_site", "$@25", "site_options", "site_option", "site_class",
  "site_symmetry_statement", "site_symmetries", "site_symmetry", "pt",
  "macro", "start_macro", "$@26", "end_macro", "$@27", "macro_options",
  "macro_option", "$@28", "macro_prop_list", "macro_symmetry_statement",
  "macro_symmetries", "macro_symmetry", "macro_name_value_pair",
  "macro_class", "class_type", "pad_type", "core_type", "endcap_type",
  "macro_generator", "macro_generate", "macro_source", "macro_power",
  "macro_origin", "macro_foreign", "macro_eeq", "$@29", "macro_leq",
  "$@30", "macro_site", "macro_site_word", "site_word", "macro_size",
  "macro_pin", "start_macro_pin", "$@31", "end_macro_pin", "$@32",
  "macro_pin_options", "macro_pin_option", "$@33", "$@34", "$@35", "$@36",
  "$@37", "$@38", "pin_prop_list", "pin_name_value_pair",
  "electrical_direction", "start_macro_port", "macro_pin_use",
  "macro_scan_use", "pin_shape", "geometries", "geometry", "$@39",
  "firstPt", "nextPt", "otherPts", "via_placement", "$@40", "$@41",
  "stepPattern", "sitePattern", "trackPattern", "$@42", "$@43", "$@44",
  "$@45", "trackLayers", "layer_name", "gcellPattern", "macro_obs",
  "start_macro_obs", "macro_clocktype", "$@46", "timing", "start_timing",
  "end_timing", "timing_options", "timing_option", "$@47", "$@48", "$@49",
  "one_pin_trigger", "two_pin_trigger", "from_pin_trigger",
  "to_pin_trigger", "delay_or_transition", "list_of_table_entries",
  "table_entry", "list_of_table_axis_numbers", "slew_spec", "risefall",
  "unateness", "list_of_from_strings", "list_of_to_strings", "array",
  "$@50", "start_array", "$@51", "end_array", "$@52", "array_rules",
  "array_rule", "$@53", "$@54", "$@55", "$@56", "$@57", "floorplan_start",
  "floorplan_list", "floorplan_element", "$@58", "$@59", "cap_list",
  "one_cap", "msg_statement", "$@60", "create_file_statement", "$@61",
  "def_statement", "$@62", "$@63", "$@64", "dtrm", "then", "else",
  "expression", "b_expr", "s_expr", "relop", "prop_def_section", "$@65",
  "prop_stmts", "prop_stmt", "$@66", "$@67", "$@68", "$@69", "$@70",
  "$@71", "$@72", "$@73", "prop_define", "opt_range", "opt_def_range",
  "opt_def_value", "opt_layer_name", "universalnoisemargin",
  "edgeratethreshold1", "edgeratethreshold2", "edgeratescalefactor",
  "noisetable", "$@74", "noise_table_list", "noise_table_entry",
  "output_resistance_entry", "$@75", "num_list", "victim_list", "victim",
  "$@76", "vnoiselist", "correctiontable", "$@77", "correction_table_list",
  "correction_table_item", "output_list", "$@78", "numo_list",
  "corr_victim_list", "corr_victim", "$@79", "corr_list", "input_antenna",
  "output_antenna", "inout_antenna", "extension", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     555,    45,    43,    42,    47,   556,    59,    40,    41,    61,
      10,    60,    62
};
# endif

#define YYPACT_NINF -1140

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-1140)))

#define YYTABLE_NINF -477

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     160, -1140,    65,   432, -1140, -1140,   -91,    35, -1140, -1140,
   -1140,   -69,   255,   -49, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140, -1140, -1140,   -28,   -27, -1140,   -15,   122,   130,   133,
     138,   141,   172,   187,   191,   -16,   303, -1140, -1140, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140,   196, -1140,    71, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140, -1140, -1140,   201,    84, -1140,   211,   246,   262,   134,
     145, -1140,   283,   290,   301,   323,   325, -1140,   158,   199,
     338,   208,   222,   228,   239, -1140,   251,   263,   265,   279,
     298,   300,   336,   390,     8,    11,   580,    -5,   549, -1140,
     549, -1140, -1140,    88,   154,    48,   691,   584, -1140, -1140,
   -1140, -1140,   312, -1140, -1140, -1140, -1140, -1140,   319,   330,
     341,   358, -1140, -1140,   353, -1140, -1140, -1140, -1140,   356,
   -1140, -1140, -1140, -1140, -1140, -1140,   357,   364,   523,   593,
   -1140,   533,   606,   613,   623,   536,   409, -1140,   535,   682,
     537,    28,   539, -1140,   540,   542,   543,   594,   546,   548,
     552,    21,   569, -1140,  -103,   570,   587,   245,   471, -1140,
   -1140, -1140, -1140, -1140, -1140,   595, -1140, -1140, -1140, -1140,
     678, -1140, -1140, -1140,   -22,   598, -1140,   180,   267,   636,
   -1140, -1140, -1140,   600,   712,   602, -1140, -1140, -1140,     6,
   -1140,   603, -1140, -1140, -1140, -1140, -1140,    30, -1140, -1140,
   -1140,   604,   608, -1140, -1140,   -42, -1140,   607, -1140,   614,
      50, -1140, -1140, -1140,   235,   697, -1140, -1140, -1140, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,   617,
   -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140, -1140,   618, -1140,   622, -1140,   741, -1140, -1140, -1140,
   -1140,    23,    80,  -100,   132,   559, -1140, -1140, -1140, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140,   -24,   -17,  -100,  -100,
     625,   626,   629, -1140,   628,   630,   631,   632,   633,   490,
     115,   496, -1140, -1140,   502,   504,   638,   505,   506,   507,
     124,   508,  -112,   509, -1140, -1140, -1140, -1140, -1140,   511,
     512,   645,   513,   517,   647,   519,   520, -1140, -1140, -1140,
     654,   655,   658,   659,   660,   531,   667, -1140,   672, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140, -1140, -1140, -1140, -1140,   673,   534,   716,   738,   429,
   -1140,   813,   -77, -1140,   562,   698,   813, -1140,    42,   714,
     715,   -42,   732,   733,   734, -1140, -1140,   718, -1140, -1140,
    -111,   605,   619,   620,   737,   896,   -94, -1140,   248, -1140,
   -1140,    67,   425, -1140, -1140,   646,   739,   743,   780,   784,
     648,   801,   668,   805,   671,   899,   674,   675,   677,   -62,
     807,   695,   699, -1140,   701,   754,   -64,   702,   503,   221,
      49,   808,   808,   383, -1140,   386, -1140,   808, -1140, -1140,
      32,   835,   850,   454, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140,   132,    80,    80,   280, -1140,   132,  -100,  -173,   132,
   -1140, -1140,   132,   132,   797,   293,   435, -1140,   852,   853,
     854,   855,   856,   861,   862,   863, -1140,   883,     2, -1140,
   -1140, -1140,   884,     3, -1140, -1140,  -173,  -173,   752,   753,
     888,   756,   757,   758,   759,   760, -1140,   761,   762, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140,   764,   765, -1140,   895,
     898,   977, -1140, -1140, -1140,   510,   -73, -1140, -1140,   766,
     901, -1140, -1140,   769, -1140,   770, -1140, -1140, -1140,   771,
   -1140,   522,   -68, -1140, -1140,   905, -1140, -1140,   773,   -42,
   -1140, -1140, -1140, -1140,   -77, -1140, -1140, -1140, -1140,   774,
   -1140,   775,   776,   777,   778,   -42,   779,  1073,   938,   915,
     917, -1140, -1140, -1140, -1140, -1140, -1140,   918, -1140, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140,   786,   787, -1140,   788, -1140,   789, -1140, -1140, -1140,
     923, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,   557,
     -56, -1140, -1140, -1140, -1140, -1140,   791,   929, -1140, -1140,
     930,   274,   307, -1140,   931,   932, -1140,   936,   937, -1140,
     939,   940, -1140, -1140, -1140, -1140,   941,   942,   943,   944,
     946,   947,   948,   334,    72,   949,   324,   950,   951, -1140,
     954,   953,   955,   956,   957,   958,   -90, -1140, -1140, -1140,
   -1140,    30, -1140, -1140,   -38,   -37,   -33,   -32,   959, -1140,
   -1140,   963, -1140,   960,   961,   962,   964, -1140, -1140,   965,
     966,   967,   968, -1140,   441,   921, -1140, -1140,   969,   829,
     837, -1140, -1140,   972,   973,   974, -1140, -1140, -1140, -1140,
   -1140,   922,   316,    -3,   976,   841,   844,   978,   979,   847,
     981,   982,   851,    25,   857,   985,   987, -1140, -1140, -1140,
   -1140, -1140, -1140, -1140, -1140,    77,   281, -1140,   313,    80,
      80,    80,    80, -1140, -1140, -1140,   281,    55,  -100, -1140,
     281, -1140,   727,   302,   268, -1140, -1140, -1140, -1140, -1140,
   -1140,    80,    80, -1140, -1140, -1140,    80,   132,   132,   132,
     132, -1140,  -100,  -100,  -100,   194,   194,   194,   194,   194,
     194,   194,   194,   986,   858,   916, -1140,   988,   859,   914,
   -1140, -1140, -1140, -1140, -1140,   860, -1140, -1140, -1140, -1140,
   -1140, -1140,   864, -1140,   865,   994, -1140,   997,   868, -1140,
   -1140, -1140, -1140, -1140,   996,   340, -1140,   869, -1140,   -96,
   -1140,   -98, -1140, -1140, -1140, -1140, -1140, -1140,   870, -1140,
     -42, -1140,   -71,   999, -1140, -1140, -1140, -1140, -1140,   873,
   -1140,  1000,  1002,   -82, -1140,   874, -1140, -1140, -1140, -1140,
     875, -1140, -1140, -1140, -1140, -1140, -1140,   867,   876,   877,
     878,   879,   880,   881,   -97,  1005,   882,   885,  1016,  1019,
     886,  1022,   889,   890,  1023,  1024,  1025,   893,   894,   897,
     900,   902,   903,   904, -1140, -1140, -1140, -1140,   906, -1140,
   -1140, -1140,   907,   908, -1140, -1140, -1140, -1140, -1140, -1140,
     909,   910,   911,  1030,   912,   977,   977,   977,   913,   919,
      14, -1140,   783,   256,   920,  1031,   -42, -1140,   -42,   -42,
     -42,   -42,   -42,   -42, -1140,   924, -1140,  1032,  1034,  1038,
    1047,  1033,  1048,  1049,  1050,  1051,  1056, -1140, -1140, -1140,
     925,  1055, -1140,   -57,  1059,   257, -1140, -1140,   927,   928,
     933,  1062, -1140, -1140, -1140,   451,  1063, -1140, -1140,  1081,
   -1140, -1140,  1196,  1205, -1140,  1207,  1208, -1140,  1040,  1070,
   -1140, -1140, -1140, -1140,   808,   808, -1140, -1140,   -61, -1140,
    1035,    80, -1140,   271,   271, -1140, -1140,  -100, -1140, -1140,
     132, -1140,   342,   342,   342, -1140, -1140,   371,   220,   952,
     952,   952,  1072,  1010,  1010,  1075,   945,   970,   971,   975,
     980,   983,   984,   989, -1140,   -35, -1140,    19, -1140,   -21,
   -1140,    19, -1140,  1076,   361, -1140,  1077,   380, -1140,   990,
   -1140, -1140,  1079,   991, -1140,   992,  1080,  1082,  1083, -1140,
   -1140,  1084,  1085,  1086, -1140, -1140, -1140,   993, -1140, -1140,
   -1140, -1140,   995,   998,  1001, -1140, -1140, -1140,  1215, -1140,
   -1140, -1140, -1140, -1140, -1140,  1003, -1140, -1140, -1140, -1140,
    1087,  1004, -1140,  1006, -1140, -1140,  1007,  1088,  1089, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140, -1140,   563,   -44, -1140, -1140,  1008,  1009,  1011, -1140,
   -1140, -1140,   812, -1140,  1012, -1140, -1140,  1013,   -42, -1140,
     -42,  1014,   -42,   -42,   -42,  1015, -1140,  1092, -1140,  1017,
    1018,  1020,  1021, -1140,   -43,  1026,  1027,  1028,  1029, -1140,
     -20, -1140,  1057, -1140, -1140,  1093, -1140, -1140, -1140, -1140,
   -1140,  1094, -1140, -1140, -1140,  1039,  1095,   441,  1096,  1097,
    1098,  1099, -1140,  1069,  1036,  1037,    13, -1140, -1140, -1140,
     142,    76,   532,   243,   700, -1140,  1101,  1102,  1102, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,  1041,
   -1140, -1140,  1042, -1140,  1105,  1043, -1140,  1106,  1044, -1140,
   -1140,  1045, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140, -1140, -1140, -1140,  1107, -1140,  1046, -1140, -1140, -1140,
    1052,  1053, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140,  1054, -1140, -1140,  1249, -1140, -1140,   -42,   -42,  1249,
   -1140,  1112,  1058, -1140, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140, -1140, -1140, -1140, -1140,  1111,  1115,  1120,  1121, -1140,
    1074,  1147,  1158,  1164,  1165,  1132, -1140, -1140,  1135,  1138,
    1143,  1149, -1140, -1140,  1116,    80,  -100,   132,  1152, -1140,
   -1140, -1140,  1155,  1041, -1140,  1157,  1042, -1140,  1060, -1140,
    1061, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,  1295,
   -1140, -1140, -1140, -1140,  1163,  1064,   -42,   -42,  1065,  1249,
   -1140,   260,  1066,  1067,  1166,  1167,  1168,  1171,  1172,  1173,
    1174,  1071, -1140,  1078,  1090,  1091, -1140,   342,   952,   310,
   -1140,  1100, -1140,  1103, -1140, -1140, -1140,    20,  1175,    33,
      68,  1175,    73,  1178,  1318, -1140,   -42,  1104, -1140,  1108,
    1109, -1140, -1140,  1181,  1182,  1179,  1183,  1110,  1113, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140, -1140,  1199,  1184,  1249, -1140, -1140, -1140,  1114,  1188,
    1189,  1190,  1302,  1303,  1124,  1125,  1194,  1238,  1117, -1140,
    1206,  1209,  1118, -1140, -1140,  1210,  1212,  1213,  1214, -1140,
    1216,  1119, -1140, -1140, -1140, -1140,   105, -1140,   114, -1140,
    1217,  1218, -1140,  1221,  1221, -1140, -1140, -1140, -1140, -1140,
    1220, -1140, -1140, -1140
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     9,     0,     2,     1,   550,     0,     0,   229,    61,
     284,     0,     0,     0,   263,   221,    48,   139,   185,   583,
     585,   587,   632,     0,     0,   706,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   579,   581,    11,
      19,    12,     3,     8,    13,    20,    14,    49,    15,    65,
      16,     0,   142,     0,    17,    18,    22,   223,    25,   231,
      24,    23,    30,    26,   267,    27,   288,    28,   554,    21,
      42,    29,    31,    32,    33,    35,    34,    36,    37,    38,
      39,    40,    41,     0,     0,    10,     0,     0,     0,     0,
       0,   240,     0,     0,     0,     0,     0,   634,     0,     0,
       0,     0,     0,     0,     0,   671,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   140,     0,     0,   206,
     203,   189,   208,     0,     0,     0,     0,   548,   551,   239,
      62,   285,     0,    44,    43,   242,   264,   186,     0,     0,
       0,     0,     6,     4,     0,   668,   687,   670,   669,     0,
     704,   703,   705,     5,    46,    45,     0,     0,     0,     0,
      57,     0,     0,     0,     0,     0,     0,    50,     0,     0,
       0,     0,     0,    63,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    88,     0,     0,     0,     0,     0,    60,
      66,   141,   183,   159,   178,     0,   149,   147,   143,   144,
       0,   145,   180,   138,   191,     0,   190,   191,   202,     0,
     227,   220,   224,     0,     0,     0,   228,   232,   234,     0,
     265,     0,   276,   262,   268,   271,   270,     0,   484,   357,
     286,     0,     0,   359,   483,     0,   367,     0,   363,     0,
       0,   313,   487,   308,     0,     0,   283,   289,   294,   290,
     291,   292,   293,   296,   295,   297,   298,   299,   301,     0,
     300,   302,   371,   305,   446,   306,   307,   489,   364,   558,
     560,   562,     0,   565,     0,   556,     0,   555,   570,   568,
     238,     0,     0,     0,     0,     0,   638,   648,   636,   642,
     650,   640,   644,   646,   635,   667,     0,     0,     0,     0,
       0,     0,     0,    47,     0,     0,     0,     0,     0,     0,
       0,     0,   136,   137,     0,     0,     0,     0,     0,     0,
       0,     0,   657,     0,   132,   133,   131,   134,   135,     0,
       0,     0,     0,     0,     0,     0,     0,    97,    96,    98,
      90,    93,     0,     0,     0,     0,     0,   170,     0,   161,
     163,   162,   164,   165,   167,   166,   168,   169,   171,   172,
     173,   174,   175,   176,   155,     0,     0,     0,   177,     0,
     195,     0,   192,   193,     0,     0,     0,   204,     0,     0,
       0,     0,     0,     0,     0,   209,   222,     0,   230,   237,
       0,     0,     0,     0,     0,     0,     0,   324,   328,   329,
     322,     0,   325,   323,   326,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   353,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   569,     0,   576,     0,   552,   549,
       0,     0,     0,     0,   248,   245,   246,   243,   247,   244,
     603,     0,     0,     0,   589,   622,     0,     0,   589,     0,
     618,   617,     0,     0,     0,   589,     0,   633,     0,     0,
       0,     0,     0,     0,     0,     0,   693,     0,     0,   689,
     692,   677,     0,     0,   673,   676,   589,   589,     0,     0,
       0,     0,     0,     0,     0,     0,    83,     0,     0,    81,
      72,    82,    64,    77,    69,    68,     0,     0,    80,     0,
       0,   665,    79,    67,    70,     0,     0,   117,    85,     0,
       0,    84,    78,     0,    99,     0,   107,   184,   160,     0,
     146,     0,     0,   150,   281,     0,   158,   156,     0,     0,
     181,   199,   200,   201,     0,   218,   188,   194,   207,     0,
     187,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   233,   235,   273,   272,   274,   266,     0,   278,   279,
     280,   275,   277,   337,   338,   339,   330,   344,   345,   341,
     340,   342,   343,   331,   334,   332,   333,   335,   336,   327,
     321,     0,     0,   287,     0,   346,     0,   352,   368,   351,
       0,   350,   349,   348,   315,   316,   317,   312,   314,     0,
       0,   310,   303,   304,   356,   354,     0,     0,   361,   362,
       0,     0,     0,   369,     0,     0,   400,     0,     0,   379,
       0,     0,   394,   396,   398,   431,     0,     0,     0,     0,
       0,     0,     0,     0,   442,     0,     0,     0,     0,   413,
       0,     0,     0,     0,     0,     0,     0,   366,   372,   382,
     446,     0,   482,   448,     0,     0,     0,     0,     0,   447,
     457,     0,   540,     0,     0,     0,     0,   491,   539,     0,
       0,     0,     0,   493,     0,     0,   519,   520,     0,     0,
       0,   521,   522,     0,     0,     0,   516,   517,   518,   486,
     490,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   572,   574,   571,
     241,   255,   252,   253,   254,     0,     0,   600,     0,     0,
       0,     0,     0,   590,   591,   584,     0,     0,     0,   586,
       0,   614,     0,     0,     0,   627,   628,   623,   624,   625,
     626,     0,     0,   629,   630,   631,     0,     0,     0,     0,
       0,   588,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   690,     0,     0,     0,
     674,   580,   582,    52,    55,     0,    54,    53,    51,    56,
      59,    75,     0,    73,     0,     0,   660,     0,     0,   119,
     120,   121,    89,   118,     0,     0,   122,     0,    92,     0,
      95,     0,   179,   154,   153,   152,   148,   151,     0,   157,
       0,   197,     0,     0,   205,   210,   211,   214,   213,     0,
     217,     0,     0,     0,   236,     0,   485,   358,   347,   360,
       0,   320,   319,   318,   309,   311,   355,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   438,   439,   440,   441,     0,   443,
     445,   444,     0,     0,   433,   436,   437,   435,   434,   432,
       0,     0,     0,     0,     0,   665,   665,   665,     0,     0,
       0,   373,     0,     0,     0,     0,     0,   459,   461,     0,
       0,     0,     0,     0,   463,     0,   488,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   541,   542,   543,
       0,     0,   534,     0,     0,     0,   531,   515,     0,     0,
       0,     0,   523,   524,   525,     0,     0,   529,   530,     0,
     559,   561,     0,     0,   563,     0,     0,   566,     0,     0,
     577,   557,   553,   564,     0,     0,   257,   250,     0,   592,
       0,     0,   601,   597,   596,   598,   599,     0,   620,   619,
       0,   615,   606,   605,   604,   610,   611,   613,   612,   609,
     608,   607,   654,   661,   661,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   695,     0,   691,   589,   679,     0,
     675,   589,    58,     0,     0,   125,     0,     0,   128,   659,
     666,    71,     0,     0,   123,     0,     0,     0,     0,    91,
     100,     0,     0,     0,    94,   108,   282,     0,   196,   198,
     219,   215,     0,     0,     0,   225,   269,   365,     0,   402,
     407,   408,   430,   429,   426,     0,   427,   370,   389,   387,
       0,     0,   385,     0,   403,   404,     0,     0,     0,   381,
     406,   405,   388,   386,   409,   410,   384,   393,   392,   383,
     391,   390,     0,     0,   421,   412,     0,     0,     0,   419,
     420,   376,     0,   374,     0,   415,   458,     0,   461,   460,
     461,     0,     0,     0,     0,     0,   465,     0,   450,     0,
       0,     0,     0,   544,     0,     0,     0,     0,     0,   546,
       0,   508,     0,   535,   498,     0,   499,   532,   512,   513,
     514,     0,   526,   527,   528,     0,     0,     0,     0,     0,
       0,     0,   567,     0,     0,     0,     0,   249,   251,   593,
       0,     0,     0,     0,     0,   655,     0,   663,   663,   656,
     639,   649,   637,   643,   651,   641,   645,   647,   696,     0,
     688,   680,     0,   672,     0,     0,   126,     0,     0,   129,
     658,     0,    86,    87,   105,   103,   101,   113,   111,   109,
     182,   216,   212,   226,     0,   428,     0,   411,   380,   395,
       0,     0,   425,   424,   423,   414,   422,   416,   418,   417,
     377,     0,   375,   449,     0,   462,   451,     0,     0,     0,
     453,     0,     0,   503,   507,   505,   501,   545,   492,   502,
     500,   504,   506,   547,   494,     0,     0,     0,     0,   495,
       0,     0,     0,     0,     0,     0,   573,   575,     0,     0,
       0,     0,   258,   594,     0,     0,     0,     0,     0,   664,
     652,   653,     0,   694,   697,     0,   678,   681,     0,    76,
       0,    74,   124,   115,   115,   115,   115,   115,   115,     0,
     401,   397,   399,   378,     0,     0,     0,   461,     0,     0,
     464,     0,     0,     0,     0,   536,     0,     0,     0,     0,
       0,     0,   256,     0,     0,     0,   595,   602,   621,   616,
     662,     0,   698,     0,   682,   127,   130,     0,   104,     0,
       0,   112,     0,     0,     0,   452,   461,     0,   454,     0,
       0,   533,   511,     0,     0,     0,     0,   469,   472,   480,
     481,   578,   260,   259,   261,   699,   683,   116,   106,   102,
     114,   110,     0,     0,     0,   455,   466,   509,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   510,
       0,     0,     0,   470,   473,     0,     0,     0,     0,   456,
     537,     0,   497,   477,   477,   701,     0,   685,     0,   468,
       0,     0,   496,   471,   474,   702,   700,   686,   684,   467,
       0,   479,   478,   538
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140,  -734, -1140,   872, -1140,
     573, -1140,   366, -1140,   377, -1140, -1140,  1122,  1191, -1140,
   -1140, -1140, -1140, -1140,   849, -1140,  -116, -1140,  -242, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,
    1277,  1192, -1140,  -367, -1140, -1140,    -1, -1140, -1140, -1140,
   -1140, -1140, -1140,  1068, -1140,  1123, -1140, -1140, -1140, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140, -1140, -1140, -1140, -1140,  -695, -1140, -1140, -1140, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140, -1140, -1140,  -189, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140,   790, -1140,   740, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,
     322, -1140, -1140, -1140, -1140, -1140,   742, -1140, -1140,  -645,
    -902, -1066, -1140, -1140, -1140, -1139,  -416, -1140, -1140, -1140,
   -1140, -1140,    24, -1140, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140, -1140, -1140,   472, -1140, -1140,   120,   275, -1140, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140, -1140,
   -1140, -1140, -1140, -1140,  1286, -1140, -1140, -1140,  -451,  -396,
    -744,  -282,  -450,  -281,  -462, -1140, -1140, -1140, -1140, -1140,
   -1140, -1140, -1140, -1140, -1140, -1140, -1140,  -134, -1140,   423,
     264,  -138, -1140, -1140, -1140, -1140, -1140, -1140, -1140,   935,
   -1140, -1140, -1140, -1140,   155, -1140, -1140, -1140, -1140, -1140,
    1126, -1140, -1140, -1140, -1140,   163, -1140, -1140, -1140, -1140,
   -1140, -1140
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    39,    40,    41,     3,    42,    43,    44,    45,
      46,    47,   114,   167,   302,    48,    49,    86,   189,   316,
     115,   190,   331,   524,   526,   340,   809,  1030,  1275,  1274,
    1273,   811,  1035,  1278,  1277,  1276,  1317,   516,   517,   805,
     806,  1014,  1015,  1017,  1018,   329,   314,    50,    51,    52,
     117,   198,   346,   532,   533,   199,   200,   343,   366,   201,
     202,   344,   368,   540,   203,   342,    53,    93,    54,    55,
     120,   371,   372,   373,   544,   822,   121,   207,   377,   122,
     205,   208,   385,   546,   823,    56,    57,   211,   123,   212,
     213,    58,    59,   216,   124,   217,   390,   562,   218,    60,
      61,    62,   135,   281,   447,   448,   725,   968,   449,   966,
    1146,  1252,    63,    64,    92,   223,   394,   125,   224,   225,
     226,   396,   572,  1099,    65,    66,    87,   246,   408,   126,
     247,   420,   610,   248,   419,   608,   611,   249,   405,   589,
     576,   583,   250,   251,   252,   253,   254,   255,   256,   407,
     257,   411,   258,   259,   275,   260,   261,   262,   413,   657,
     855,   428,   658,   861,   864,   865,   866,   858,   893,  1083,
    1084,   659,   660,   890,   878,   882,   429,   669,   905,   908,
    1100,  1101,   670,  1107,  1221,  1285,   427,   709,  1362,  1383,
    1363,  1384,  1393,  1402,   712,   263,   264,   265,   406,   266,
     267,   699,   430,   700,   921,   926,  1295,   701,   702,   945,
    1135,   949,   935,   936,   933,  1335,   703,   930,  1114,  1120,
      67,   276,    68,    83,   439,   715,   127,   277,   437,   431,
     432,   433,   435,   278,   440,   719,   964,   965,   713,   960,
      69,   112,    70,   113,    71,    94,    95,    96,   735,   971,
    1255,   464,   465,   466,   756,    72,    97,   141,   294,   470,
     468,   473,   471,   474,   475,   469,   472,   996,   511,  1157,
    1260,   798,    73,    74,    75,    76,    77,   149,   483,   484,
     485,   777,  1009,  1266,  1267,  1365,  1388,    78,   296,   478,
     479,   480,   773,  1005,  1263,  1264,  1364,  1386,    79,    80,
      81,    82
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     454,   726,   458,   424,   764,   547,   736,   739,  1103,   740,
     245,   367,   741,   743,   761,   705,   706,   486,   487,   168,
     910,   714,   158,   906,   909,   169,   170,   391,   911,   913,
     967,   192,  1214,   159,  1215,   781,   782,   160,   775,   779,
     397,   119,   193,   171,   161,   172,   412,   173,   324,  1248,
     900,   398,   399,   400,  1044,   946,   425,  1055,   194,   441,
     416,   958,   560,   174,   219,     4,   476,   401,   716,  1031,
     332,  1026,   455,   481,   568,   569,   570,   879,   577,   578,
    1288,   312,    84,   348,   220,   671,   442,   672,   673,   674,
     675,   676,   476,   481,   369,   551,   175,   677,   515,   417,
     369,    85,   392,   531,    88,   195,   604,   605,   606,   617,
     443,   456,   176,   325,   162,   609,  1123,   880,   163,   206,
     118,   177,    91,   509,   209,   538,   402,  1082,  1227,   738,
    1032,   348,  1027,   733,   119,   348,   348,   734,  1168,   178,
     348,   348,   403,   326,    98,   179,    99,  1249,   196,   369,
    1329,  1233,  1171,   333,   180,   164,   109,    15,   100,   370,
      -7,     1,   678,   679,   680,   370,   181,   681,   682,    -7,
     727,   728,   579,   165,   580,   444,   737,   821,   182,   221,
    1250,   742,   744,   616,   881,    17,   510,   348,   313,   222,
     214,    -7,   555,  1347,   443,   561,    -7,  1033,  1028,   683,
    1217,  1218,   552,   206,   334,   684,  1347,   457,  1034,  1056,
    1029,   327,   571,   210,   370,  1368,   901,   365,   581,   582,
      -7,  1327,   947,    -7,  1045,   477,   948,    -7,   959,   717,
     718,   197,   482,   802,    -7,  1038,    -7,   661,   816,   418,
      -7,  1347,   618,   393,   607,  1147,  1347,   183,   443,  1124,
     844,   477,   482,   450,   685,   686,   687,   662,   328,   444,
    1354,  1098,  1205,  1228,  1102,   365,   184,   404,   185,   365,
     365,  1169,   661,  1148,   365,   365,   688,   689,  1395,   690,
     849,   186,   764,  1251,   663,  1172,  1234,  1397,   497,  1253,
      -7,   451,  1095,   573,    -7,   101,   215,   506,   672,   378,
     187,   188,   166,   102,   455,   450,   103,   985,   986,   987,
     988,   104,   656,   444,   105,  1286,  1287,    -7,   664,   663,
    1091,   365,    -7,    -7,   665,   733,  1348,   691,   692,   734,
     666,   884,   693,   694,   695,   696,   697,   698,   379,  1349,
     977,   885,    17,   459,   980,   106,   460,   461,    89,    90,
     820,   369,   851,   664,   886,  1253,   462,   738,   380,   665,
     107,   852,   853,   978,   108,   666,   829,   116,    -7,    -7,
      -7,   498,   128,   678,  1350,   887,   381,   382,   738,  1351,
     507,   452,   130,   667,  1326,   850,  1254,   453,   668,   874,
     129,    -7,   574,   575,   285,   854,   110,   111,    -7,    -7,
      -7,   383,    -7,    -7,    -7,    -7,    -7,  1256,    -7,  1257,
    1256,  1396,    -7,    -7,    -7,   286,   370,   131,   667,    -7,
    1398,   287,   875,   668,   288,   289,   992,   993,   994,    -7,
     888,    -7,    -7,   452,   384,   132,   757,   758,   290,   463,
     133,     5,   759,   729,   730,   731,   732,   973,   974,   975,
     976,   134,  1254,   889,   136,  1039,  1253,   979,   291,   757,
     758,   137,   995,     6,   142,   759,   760,   902,     7,   982,
     983,   876,   138,   877,   984,   907,   907,   912,   914,   584,
     585,   989,   990,   991,   745,   746,   747,   748,   749,   750,
     762,   763,     8,   969,   139,     9,   140,   757,   758,    10,
     927,   421,   422,   759,   760,   143,    11,   156,    12,   757,
     758,   144,    13,   586,   145,   759,   760,   620,   757,   758,
     292,   293,   928,   929,   759,   760,   757,   758,   146,   621,
    1153,   587,   759,   760,   147,   622,   337,   338,   339,   623,
    1318,  1319,  1320,  1321,  1322,   148,   624,   625,  1144,  1145,
     193,   707,   708,  1254,   710,   711,  1170,   150,   588,   626,
    1173,   157,    14,  1126,   934,   627,    15,   628,   629,   151,
     738,   152,   630,   631,   731,   732,   978,   753,   632,   754,
     755,   729,   730,   731,   732,   153,   733,   757,   758,    16,
     734,   970,   633,   634,    17,    18,   942,   943,   944,   733,
     541,   542,   543,   734,   154,  1048,   155,   635,   191,   636,
     981,   637,   119,   638,   729,   730,   731,   732,   280,   639,
     640,   972,   300,   641,   642,   722,   723,   724,   282,   643,
     644,  1037,   997,   998,   999,  1000,  1001,  1002,  1003,   283,
      19,    20,    21,   729,   730,   731,   732,   804,  1023,   645,
     284,   745,   746,   747,   748,   749,   750,   762,   763,   295,
    1094,   646,   297,    22,   647,   301,   298,   648,  1013,  1175,
      23,    24,    25,   299,    26,    27,    28,    29,    30,   304,
      31,   799,   800,   801,    32,    33,    34,  1016,  1178,  1150,
     303,    35,   764,   813,   814,   815,  1151,   305,  1152,  1154,
     306,    36,   307,    37,    38,   308,   310,   227,   309,   228,
     311,  1092,   315,   317,   268,   318,   319,   907,   320,   321,
     907,   322,  1104,  1105,  1106,   323,   229,   230,   841,   842,
     843,  1132,  1133,  1134,  1202,  1203,  1204,   738,   193,   649,
     231,   232,   330,   335,   753,  1253,   754,   755,   745,   746,
     747,   748,   749,   750,   751,   752,   233,  1086,  1087,  1088,
     336,   650,   341,   651,   652,   653,   654,   655,   345,   374,
     386,   387,   388,   389,   234,   409,   395,   438,   235,   410,
     414,   269,   270,   271,   272,   273,   274,   415,   426,   434,
     467,   236,    19,    20,    21,   436,   496,   237,   488,   489,
     490,   491,   499,   492,   493,   494,   495,  1309,   500,   502,
     501,   503,   504,   505,   508,   512,   515,   513,   514,   518,
     520,   238,   239,   240,   519,   521,   522,   523,   525,   527,
     528,   529,   241,   729,   730,   731,   732,   530,   531,   242,
     536,   753,  1254,   754,   755,   534,   535,   539,   347,   545,
    1211,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   362,   363,   347,   548,   549,
     348,   349,   350,   351,   352,   353,   354,   355,   356,   357,
     358,   359,   360,   361,   362,   363,   347,   553,   554,   559,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   362,   363,   556,   557,   558,   566,   567,
     591,   563,   600,  1253,   592,  1219,   745,   746,   747,   748,
     749,   750,   762,   763,   347,   564,   565,   243,   349,   350,
     351,   352,   353,   354,   355,   356,   357,   358,   359,   360,
     361,   362,   363,   745,   746,   747,   748,   749,   750,   751,
     752,   593,   590,   347,   595,   594,   244,   349,   350,   351,
     352,   353,   354,   355,   356,   357,   358,   359,   360,   361,
     362,   363,   596,  1307,   597,  1308,   598,   599,   609,   704,
     601,   602,   347,   603,   364,   365,   349,   350,   351,   352,
     353,   354,   355,   356,   357,   358,   359,   360,   361,   362,
     363,   612,   738,   423,   365,   613,   720,   614,   619,   753,
    1254,   754,   755,   745,   746,   747,   748,   749,   750,   751,
     752,   721,   537,   765,   766,   767,   768,   769,   729,   730,
     731,   732,   770,   771,   772,   972,   753,   347,   754,   755,
     797,   349,   350,   351,   352,   353,   354,   355,   356,   357,
     358,   359,   360,   361,   362,   363,   774,   778,   783,   784,
     615,   785,   786,   787,   788,   789,   790,   791,   795,   792,
     793,   796,   794,   804,   807,   808,   810,   812,   818,   819,
     824,   825,   826,   827,   828,   830,   831,   832,   833,  1093,
     834,   835,   836,   837,   838,   839,   840,   846,   729,   730,
     731,   732,   847,   848,   856,   857,   753,   859,   754,   755,
     860,   916,   862,   863,   867,   868,   869,   870,  1210,   871,
     872,   873,   883,   891,   892,   894,   895,   931,   896,   897,
     898,   899,   915,   917,   918,   919,   934,   920,   922,   923,
     924,   925,   932,   937,   938,   939,   940,   950,   941,   617,
     951,   952,   953,   954,   955,   956,   962,   957,   963,  1004,
    1007,  1008,  1011,   961,  1006,  1010,  1012,  1019,  1020,  1022,
    1040,  1013,  1016,  1042,  1021,  1043,  1057,  1025,  1036,  1041,
    1046,  1047,  1049,  1050,  1051,  1052,  1053,  1054,  1058,  1060,
    1061,  1059,  1062,  1063,  1066,  1064,  1065,  1067,  1068,  1069,
    1070,  1082,  1097,  1071,  1113,  1109,  1072,  1110,  1073,  1074,
    1075,  1111,  1076,  1077,  1078,  1079,  1080,  1081,  1085,  1089,
    1112,  1115,  1116,  1117,  1118,  1090,  1096,  1119,  1122,  1138,
    1108,  1121,  1125,  1128,  1129,  1131,  1136,  1137,  1139,  1130,
    1140,  1141,  1142,  1143,  1155,  1156,  1159,  1149,  1194,  1174,
    1177,  1160,  1181,  1184,   738,  1185,  1186,  1187,  1188,  1189,
    1196,  1200,  1201,  1222,  1235,  1238,  1236,  1237,  1239,  1241,
    1242,  1243,  1244,  1245,  1258,  1259,  1161,  1162,  1268,  1270,
    1279,  1163,  1284,  1289,  1291,  1297,  1164,  1180,  1292,  1165,
    1166,  1262,  1265,  1293,  1294,  1167,  1298,  1182,  1183,  1190,
    1296,  1191,  1299,  1300,  1192,  1301,  1302,  1193,  1323,  1195,
    1197,  1303,  1198,  1199,  1207,  1208,  1304,  1209,  1212,  1213,
    1216,  1220,  1305,  1223,  1224,  1310,  1225,  1226,  1311,  1306,
    1313,  1353,  1229,  1230,  1231,  1232,  1324,  1366,  1360,  1333,
    1334,  1336,  1246,  1247,  1337,  1338,  1339,  1340,  1347,  1269,
    1271,  1352,  1280,  1272,  1358,  1359,  1361,  1367,  1281,  1282,
    1283,  1370,  1371,  1372,  1290,  1373,  1374,  1377,  1315,  1316,
    1325,  1328,  1376,  1332,  1331,  1375,  1378,  1341,  1024,  1380,
    1176,   817,  1381,  1385,  1342,  1387,  1389,  1390,   803,  1391,
    1399,  1400,  1401,  1403,  1179,   204,  1343,  1344,   375,   376,
     845,   904,   903,   445,   446,  1206,  1345,  1127,  1394,  1346,
    1355,  1330,  1240,   279,  1356,  1357,  -475,  1158,   780,  -476,
    1369,  1314,  1261,  1379,  1382,  1392,  1312,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   550,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   776
};

static const yytype_int16 yycheck[] =
{
     282,   451,   283,   245,   466,   372,   456,   458,   910,   459,
     126,   200,   462,   463,   465,   431,   432,   298,   299,     8,
     665,   437,    14,    61,    61,    14,    15,    21,    61,    61,
     725,    36,  1098,    25,  1100,   486,   487,    29,    36,    36,
      10,    63,    47,    32,    36,    34,   235,    36,    27,    36,
     140,    21,    22,    23,   136,    58,   245,   154,    63,    36,
      10,    36,   173,    52,    16,     0,    90,    37,    36,   167,
     173,   167,   172,    90,   168,   169,   170,     5,    11,    12,
    1219,    53,   173,   173,    36,    36,    63,    38,    39,    40,
      41,    42,    90,    90,   171,    53,    85,    48,   171,    49,
     171,    66,    96,   171,   173,   110,   168,   169,   170,   173,
     171,   211,   101,    92,   106,   171,   173,    45,   110,   120,
      49,   110,   171,   235,    36,   367,    96,   171,   171,   302,
     228,   173,   228,   306,    63,   173,   173,   310,   173,   128,
     173,   173,   112,   122,   172,   134,   173,   134,   153,   171,
    1289,   171,   173,   256,   143,   147,   172,   134,   173,   236,
       0,     1,   113,   114,   115,   236,   155,   118,   119,     9,
     452,   453,   105,   165,   107,   236,   457,   544,   167,   131,
     167,   463,   463,   425,   112,   162,   298,   173,   160,   141,
      36,    31,   381,   173,   171,   306,    36,   295,   294,   150,
    1102,  1103,   160,   204,   307,   156,   173,   307,   306,   306,
     306,   190,   306,   125,   236,  1354,   306,   307,   151,   152,
      60,  1287,   225,    63,   306,   249,   229,    67,   203,   197,
     198,   236,   249,   306,    74,   306,    76,    16,   306,   189,
      80,   173,   306,   237,   306,   306,   173,   236,   171,   306,
     306,   249,   249,   173,   205,   206,   207,    36,   237,   236,
    1326,   906,   306,   306,   909,   307,   255,   237,   257,   307,
     307,   306,    16,   968,   307,   307,   227,   228,   173,   230,
       6,   270,   744,   270,    63,   306,   306,   173,   173,   213,
     130,   211,    36,    45,   134,   173,   142,   173,    38,    32,
     289,   290,   294,   173,   172,   173,   173,   757,   758,   759,
     760,   173,   428,   236,   173,  1217,  1218,   157,    97,    63,
     306,   307,   162,   163,   103,   306,   306,   278,   279,   310,
     109,     7,   283,   284,   285,   286,   287,   288,    71,   306,
     736,    17,   162,   211,   740,   173,   214,   215,    93,    94,
     539,   171,    45,    97,    30,   213,   224,   302,    91,   103,
     173,    54,    55,   308,   173,   109,   555,   171,   208,   209,
     210,   256,   171,   113,   306,    51,   109,   110,   302,   306,
     256,   301,   171,   162,  1286,   111,   310,   307,   167,    55,
     306,   231,   144,   145,    36,    88,    93,    94,   238,   239,
     240,   134,   242,   243,   244,   245,   246,  1151,   248,  1153,
    1154,   306,   252,   253,   254,    57,   236,   171,   162,   259,
     306,    63,    88,   167,    66,    67,   232,   233,   234,   269,
     106,   271,   272,   301,   167,   173,   216,   217,    80,   307,
     306,     9,   222,   301,   302,   303,   304,   729,   730,   731,
     732,   306,   310,   129,   171,   822,   213,   738,   100,   216,
     217,   171,   268,    31,   306,   222,   223,   656,    36,   751,
     752,   137,   171,   139,   756,   664,   665,   666,   667,    54,
      55,   762,   763,   764,   216,   217,   218,   219,   220,   221,
     222,   223,    60,   212,   171,    63,   171,   216,   217,    67,
      59,   266,   267,   222,   223,   306,    74,   171,    76,   216,
     217,   173,    80,    88,   306,   222,   223,    14,   216,   217,
     162,   163,    81,    82,   222,   223,   216,   217,   306,    26,
     980,   106,   222,   223,   306,    32,   291,   292,   293,    36,
    1274,  1275,  1276,  1277,  1278,   306,    43,    44,   964,   965,
      47,   168,   169,   310,   168,   169,  1007,   306,   133,    56,
    1011,   171,   130,   306,   307,    62,   134,    64,    65,   306,
     302,   306,    69,    70,   303,   304,   308,   309,    75,   311,
     312,   301,   302,   303,   304,   306,   306,   216,   217,   157,
     310,   310,    89,    90,   162,   163,   280,   281,   282,   306,
     171,   172,   173,   310,   306,   847,   306,   104,    28,   106,
     308,   108,    63,   110,   301,   302,   303,   304,   306,   116,
     117,   308,    99,   120,   121,   171,   172,   173,   309,   126,
     127,   820,   766,   767,   768,   769,   770,   771,   772,   309,
     208,   209,   210,   301,   302,   303,   304,   307,   308,   146,
     309,   216,   217,   218,   219,   220,   221,   222,   223,   306,
     902,   158,   306,   231,   161,    72,   309,   164,   307,   308,
     238,   239,   240,   309,   242,   243,   244,   245,   246,    73,
     248,   171,   172,   173,   252,   253,   254,   307,   308,   971,
     157,   259,  1154,   171,   172,   173,   977,    84,   980,   980,
      77,   269,   166,   271,   272,   296,    24,    16,   173,    18,
     173,   900,   173,   173,   130,   173,   173,   906,   124,   173,
     909,   173,   911,   912,   913,   173,    35,    36,   171,   172,
     173,   280,   281,   282,   171,   172,   173,   302,    47,   236,
      49,    50,   173,   173,   309,   213,   311,   312,   216,   217,
     218,   219,   220,   221,   222,   223,    65,   895,   896,   897,
     173,   258,   291,   260,   261,   262,   263,   264,   173,   171,
     134,   171,    60,   171,    83,   171,   173,    36,    87,   171,
     173,   197,   198,   199,   200,   201,   202,   173,   171,   171,
     231,   100,   208,   209,   210,   173,   306,   106,   173,   173,
     171,   173,   306,   173,   173,   173,   173,  1257,   306,   171,
     306,   306,   306,   306,   306,   306,   171,   306,   306,   306,
     173,   130,   131,   132,   307,   306,   306,   173,   173,   171,
     171,   171,   141,   301,   302,   303,   304,   306,   171,   148,
     306,   309,   310,   311,   312,   173,   173,   109,   170,    36,
    1092,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   170,   306,   171,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   170,   173,   173,   171,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   173,   173,   173,   171,    13,
     171,   306,    13,   213,   171,  1104,   216,   217,   218,   219,
     220,   221,   222,   223,   170,   306,   306,   236,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   216,   217,   218,   219,   220,   221,   222,
     223,   171,   306,   170,   306,   171,   265,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   171,  1255,   306,  1256,   171,   306,   171,   171,
     306,   306,   170,   306,   306,   307,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   306,   302,   306,   307,   306,   171,   306,   306,   309,
     310,   311,   312,   216,   217,   218,   219,   220,   221,   222,
     223,   171,   306,   171,   171,   171,   171,   171,   301,   302,
     303,   304,   171,   171,   171,   308,   309,   170,   311,   312,
      63,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   173,   173,   306,   306,
     306,   173,   306,   306,   306,   306,   306,   306,   173,   307,
     306,   173,   307,   307,   173,   306,   306,   306,   173,   306,
     306,   306,   306,   306,   306,   306,    13,   149,   173,   306,
     173,   173,   306,   306,   306,   306,   173,   306,   301,   302,
     303,   304,   173,   173,   173,   173,   309,   171,   311,   312,
     173,   148,   173,   173,   173,   173,   173,   173,   306,   173,
     173,   173,   173,   173,   173,   171,   173,   206,   173,   173,
     173,   173,   173,   173,   173,   173,   307,   173,   173,   173,
     173,   173,   173,   306,   172,   172,   172,   306,   226,   173,
     306,   173,   173,   306,   173,   173,   171,   306,   171,   173,
     244,   173,   248,   306,   306,   306,   306,   173,   171,   173,
     171,   307,   307,   173,   306,   173,   171,   308,   308,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   173,
     171,   306,   306,   171,   171,   306,   306,   173,   173,   306,
     306,   171,   171,   306,   171,   173,   306,   173,   306,   306,
     306,   173,   306,   306,   306,   306,   306,   306,   306,   306,
     173,   173,   173,   173,   173,   306,   306,   171,   173,    33,
     306,   306,   173,   306,   306,   173,   173,   156,    33,   306,
      33,    33,   202,   173,   172,   235,   171,   212,    33,   173,
     173,   306,   173,   173,   302,   173,   173,   173,   173,   173,
     173,   173,   173,   171,   207,   226,   173,   173,   173,   173,
     173,   173,   173,   204,   173,   173,   306,   306,   173,   173,
     173,   306,    33,   171,   173,   138,   306,   297,   173,   306,
     306,   250,   250,   173,   173,   306,   138,   306,   306,   306,
     226,   306,   138,   138,   306,   173,   171,   306,    13,   306,
     306,   173,   306,   306,   306,   306,   173,   306,   306,   306,
     306,   306,   173,   306,   306,   173,   306,   306,   173,   213,
     173,    13,   306,   306,   306,   306,   173,   138,   159,   173,
     173,   173,   306,   306,   173,   173,   173,   173,   173,   306,
     306,   173,   306,   308,   173,   173,   173,   173,   306,   306,
     306,   173,   173,   173,   306,    63,    63,   173,   308,   308,
     306,   306,   247,   306,   308,   251,   138,   306,   805,   173,
    1014,   532,   173,   173,   306,   173,   173,   173,   516,   173,
     173,   173,   171,   173,  1017,   118,   306,   306,   207,   207,
     610,   661,   660,   281,   281,  1083,   306,   935,  1384,   306,
     306,  1291,  1137,   127,   306,   306,   306,   994,   483,   306,
     306,  1266,  1158,   306,   306,   306,  1263,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   376,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   478
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     1,   314,   318,     0,     9,    31,    36,    60,    63,
      67,    74,    76,    80,   130,   134,   157,   162,   163,   208,
     209,   210,   231,   238,   239,   240,   242,   243,   244,   245,
     246,   248,   252,   253,   254,   259,   269,   271,   272,   315,
     316,   317,   319,   320,   321,   322,   323,   324,   328,   329,
     360,   361,   362,   379,   381,   382,   398,   399,   404,   405,
     412,   413,   414,   425,   426,   437,   438,   533,   535,   553,
     555,   557,   568,   585,   586,   587,   588,   589,   600,   611,
     612,   613,   614,   536,   173,    66,   330,   439,   173,    93,
      94,   171,   427,   380,   558,   559,   560,   569,   172,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   172,
      93,    94,   554,   556,   325,   333,   171,   363,    49,    63,
     383,   389,   392,   401,   407,   430,   442,   539,   171,   306,
     171,   171,   173,   306,   306,   415,   171,   171,   171,   171,
     171,   570,   306,   306,   173,   306,   306,   306,   306,   590,
     306,   306,   306,   306,   306,   306,   171,   171,    14,    25,
      29,    36,   106,   110,   147,   165,   294,   326,     8,    14,
      15,    32,    34,    36,    52,    85,   101,   110,   128,   134,
     143,   155,   167,   236,   255,   257,   270,   289,   290,   331,
     334,    28,    36,    47,    63,   110,   153,   236,   364,   368,
     369,   372,   373,   377,   383,   393,   389,   390,   394,    36,
     125,   400,   402,   403,    36,   142,   406,   408,   411,    16,
      36,   131,   141,   428,   431,   432,   433,    16,    18,    35,
      36,    49,    50,    65,    83,    87,   100,   106,   130,   131,
     132,   141,   148,   236,   265,   369,   440,   443,   446,   450,
     455,   456,   457,   458,   459,   460,   461,   463,   465,   466,
     468,   469,   470,   508,   509,   510,   512,   513,   130,   197,
     198,   199,   200,   201,   202,   467,   534,   540,   546,   557,
     306,   416,   309,   309,   309,    36,    57,    63,    66,    67,
      80,   100,   162,   163,   571,   306,   601,   306,   309,   309,
      99,    72,   327,   157,    73,    84,    77,   166,   296,   173,
      24,   173,    53,   160,   359,   173,   332,   173,   173,   173,
     124,   173,   173,   173,    27,    92,   122,   190,   237,   358,
     173,   335,   173,   256,   307,   173,   173,   291,   292,   293,
     338,   291,   378,   370,   374,   173,   365,   170,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   306,   307,   371,   436,   375,   171,
     236,   384,   385,   386,   171,   361,   384,   391,    32,    71,
      91,   109,   110,   134,   167,   395,   134,   171,    60,   171,
     409,    21,    96,   237,   429,   173,   434,    10,    21,    22,
      23,    37,    96,   112,   237,   451,   511,   462,   441,   171,
     171,   464,   436,   471,   173,   173,    10,    49,   189,   447,
     444,   266,   267,   306,   371,   436,   171,   499,   474,   489,
     515,   542,   543,   544,   171,   545,   173,   541,    36,   537,
     547,    36,    63,   171,   236,   360,   398,   417,   418,   421,
     173,   211,   301,   307,   564,   172,   211,   307,   566,   211,
     214,   215,   224,   307,   564,   565,   566,   231,   573,   578,
     572,   575,   579,   574,   576,   577,    90,   249,   602,   603,
     604,    90,   249,   591,   592,   593,   566,   566,   173,   173,
     171,   173,   173,   173,   173,   173,   306,   173,   256,   306,
     306,   306,   171,   306,   306,   306,   173,   256,   306,   235,
     298,   581,   306,   306,   306,   171,   350,   351,   306,   307,
     173,   306,   306,   173,   336,   173,   337,   171,   171,   171,
     306,   171,   366,   367,   173,   173,   306,   306,   371,   109,
     376,   171,   172,   173,   387,    36,   396,   386,   306,   171,
     396,    53,   160,   173,   173,   436,   173,   173,   173,   171,
     173,   306,   410,   306,   306,   306,   171,    13,   168,   169,
     170,   306,   435,    45,   144,   145,   453,    11,    12,   105,
     107,   151,   152,   454,    54,    55,    88,   106,   133,   452,
     306,   171,   171,   171,   171,   306,   171,   306,   171,   306,
      13,   306,   306,   306,   168,   169,   170,   306,   448,   171,
     445,   449,   306,   306,   306,   306,   371,   173,   306,   306,
      14,    26,    32,    36,    43,    44,    56,    62,    64,    65,
      69,    70,    75,    89,    90,   104,   106,   108,   110,   116,
     117,   120,   121,   126,   127,   146,   158,   161,   164,   236,
     258,   260,   261,   262,   263,   264,   369,   472,   475,   484,
     485,    16,    36,    63,    97,   103,   109,   162,   167,   490,
     495,    36,    38,    39,    40,    41,    42,    48,   113,   114,
     115,   118,   119,   150,   156,   205,   206,   207,   227,   228,
     230,   278,   279,   283,   284,   285,   286,   287,   288,   514,
     516,   520,   521,   529,   171,   499,   499,   168,   169,   500,
     168,   169,   507,   551,   499,   538,    36,   197,   198,   548,
     171,   171,   171,   172,   173,   419,   565,   564,   564,   301,
     302,   303,   304,   306,   310,   561,   565,   566,   302,   561,
     565,   565,   564,   565,   566,   216,   217,   218,   219,   220,
     221,   222,   223,   309,   311,   312,   567,   216,   217,   222,
     223,   561,   222,   223,   567,   171,   171,   171,   171,   171,
     171,   171,   171,   605,   173,    36,   603,   594,   173,    36,
     592,   561,   561,   306,   306,   173,   306,   306,   306,   306,
     306,   306,   307,   306,   307,   173,   173,    63,   584,   171,
     172,   173,   306,   351,   307,   352,   353,   173,   306,   339,
     306,   344,   306,   171,   172,   173,   306,   367,   173,   306,
     436,   386,   388,   397,   306,   306,   306,   306,   306,   436,
     306,    13,   149,   173,   173,   173,   306,   306,   306,   306,
     173,   171,   172,   173,   306,   449,   306,   173,   173,     6,
     111,    45,    54,    55,    88,   473,   173,   173,   480,   171,
     173,   476,   173,   173,   477,   478,   479,   173,   173,   173,
     173,   173,   173,   173,    55,    88,   137,   139,   487,     5,
      45,   112,   488,   173,     7,    17,    30,    51,   106,   129,
     486,   173,   173,   481,   171,   173,   173,   173,   173,   173,
     140,   306,   436,   489,   451,   491,    61,   436,   492,    61,
     492,    61,   436,    61,   436,   173,   148,   173,   173,   173,
     173,   517,   173,   173,   173,   173,   518,    59,    81,    82,
     530,   206,   173,   527,   307,   525,   526,   306,   172,   172,
     172,   226,   280,   281,   282,   522,    58,   225,   229,   524,
     306,   306,   173,   173,   306,   173,   173,   306,    36,   203,
     552,   306,   171,   171,   549,   550,   422,   418,   420,   212,
     310,   562,   308,   564,   564,   564,   564,   562,   308,   566,
     562,   308,   564,   564,   564,   565,   565,   565,   565,   566,
     566,   566,   232,   233,   234,   268,   580,   580,   580,   580,
     580,   580,   580,   580,   173,   606,   306,   244,   173,   595,
     306,   248,   306,   307,   354,   355,   307,   356,   357,   173,
     171,   306,   173,   308,   353,   308,   167,   228,   294,   306,
     340,   167,   228,   295,   306,   345,   308,   436,   306,   386,
     171,   306,   173,   173,   136,   306,   306,   306,   371,   306,
     306,   306,   306,   306,   306,   154,   306,   171,   306,   306,
     173,   171,   306,   171,   306,   306,   171,   173,   173,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   171,   482,   483,   306,   584,   584,   584,   306,
     306,   306,   436,   306,   371,    36,   306,   171,   492,   436,
     493,   494,   492,   493,   436,   436,   436,   496,   306,   173,
     173,   173,   173,   171,   531,   173,   173,   173,   173,   171,
     532,   306,   173,   173,   306,   173,   306,   526,   306,   306,
     306,   173,   280,   281,   282,   523,   173,   156,    33,    33,
      33,    33,   202,   173,   499,   499,   423,   306,   418,   212,
     564,   566,   564,   565,   566,   172,   235,   582,   582,   171,
     306,   306,   306,   306,   306,   306,   306,   306,   173,   306,
     561,   173,   306,   561,   173,   308,   355,   173,   308,   357,
     297,   173,   306,   306,   173,   173,   173,   173,   173,   173,
     306,   306,   306,   306,    33,   306,   173,   306,   306,   306,
     173,   173,   171,   172,   173,   306,   483,   306,   306,   306,
     306,   371,   306,   306,   494,   494,   306,   493,   493,   436,
     306,   497,   171,   306,   306,   306,   306,   171,   306,   306,
     306,   306,   306,   171,   306,   207,   173,   173,   226,   173,
     530,   173,   173,   173,   173,   204,   306,   306,    36,   134,
     167,   270,   424,   213,   310,   563,   563,   563,   173,   173,
     583,   583,   250,   607,   608,   250,   596,   597,   173,   306,
     173,   306,   308,   343,   342,   341,   348,   347,   346,   173,
     306,   306,   306,   306,    33,   498,   493,   493,   498,   171,
     306,   173,   173,   173,   173,   519,   226,   138,   138,   138,
     138,   173,   171,   173,   173,   173,   213,   564,   566,   565,
     173,   173,   608,   173,   597,   308,   308,   349,   349,   349,
     349,   349,   349,    13,   173,   306,   493,   494,   306,   498,
     529,   308,   306,   173,   173,   528,   173,   173,   173,   173,
     173,   306,   306,   306,   306,   306,   306,   173,   306,   306,
     306,   306,   173,    13,   494,   306,   306,   306,   173,   173,
     159,   173,   501,   503,   609,   598,   138,   173,   498,   306,
     173,   173,   173,    63,    63,   251,   247,   173,   138,   306,
     173,   173,   306,   502,   504,   173,   610,   173,   599,   173,
     173,   173,   306,   505,   505,   173,   306,   173,   306,   173,
     173,   171,   506,   173
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   313,   314,   314,   315,   316,   317,   318,   318,   318,
     319,   320,   320,   320,   320,   320,   320,   320,   320,   320,
     320,   320,   320,   320,   320,   320,   320,   320,   320,   320,
     320,   320,   320,   320,   320,   320,   320,   320,   320,   320,
     320,   320,   320,   321,   321,   322,   322,   323,   324,   325,
     325,   326,   326,   326,   326,   326,   326,   327,   326,   326,
     328,   330,   329,   332,   331,   333,   333,   334,   334,   334,
     334,   334,   334,   334,   334,   334,   334,   334,   334,   334,
     334,   334,   334,   334,   334,   334,   334,   334,   335,   334,
     336,   334,   334,   337,   334,   334,   338,   338,   338,   339,
     339,   341,   340,   342,   340,   343,   340,   344,   344,   346,
     345,   347,   345,   348,   345,   349,   349,   350,   350,   351,
     351,   351,   352,   352,   353,   354,   354,   355,   356,   356,
     357,   358,   358,   358,   358,   358,   359,   359,   360,   361,
     362,   362,   363,   363,   364,   364,   364,   365,   364,   364,
     366,   366,   367,   367,   367,   368,   368,   368,   368,   370,
     369,   371,   371,   371,   371,   371,   371,   371,   371,   371,
     371,   371,   371,   371,   371,   371,   371,   372,   374,   373,
     375,   375,   376,   378,   377,   380,   379,   381,   382,   383,
     383,   384,   384,   385,   385,   387,   386,   388,   388,   386,
     386,   386,   389,   390,   390,   391,   393,   392,   394,   394,
     395,   395,   395,   395,   395,   395,   395,   395,   397,   396,
     398,   399,   400,   401,   401,   402,   402,   403,   404,   405,
     406,   407,   407,   408,   409,   409,   410,   411,   412,   413,
     415,   414,   416,   416,   417,   417,   417,   417,   419,   418,
     420,   420,   418,   418,   418,   422,   421,   423,   423,   424,
     424,   424,   425,   427,   426,   429,   428,   430,   430,   431,
     431,   431,   432,   432,   432,   433,   434,   434,   435,   435,
     435,   436,   436,   437,   439,   438,   441,   440,   442,   442,
     443,   443,   443,   443,   443,   443,   443,   443,   443,   443,
     443,   443,   443,   443,   443,   443,   443,   443,   444,   443,
     445,   445,   446,   447,   447,   448,   448,   448,   449,   449,
     449,   450,   451,   451,   451,   451,   451,   451,   451,   451,
     451,   451,   452,   452,   452,   452,   452,   453,   453,   453,
     454,   454,   454,   454,   454,   454,   455,   456,   457,   457,
     457,   458,   459,   460,   460,   460,   460,   462,   461,   464,
     463,   465,   465,   466,   467,   468,   469,   471,   470,   473,
     472,   474,   474,   475,   475,   475,   475,   475,   475,   476,
     475,   475,   475,   475,   475,   475,   475,   475,   475,   475,
     475,   475,   475,   475,   477,   475,   478,   475,   479,   475,
     480,   475,   475,   475,   475,   475,   475,   475,   475,   475,
     475,   475,   475,   481,   475,   475,   475,   475,   475,   475,
     475,   482,   482,   483,   483,   483,   484,   484,   484,   484,
     484,   485,   486,   486,   486,   486,   486,   486,   487,   487,
     487,   487,   488,   488,   488,   488,   489,   489,   491,   490,
     490,   490,   490,   490,   490,   490,   490,   490,   490,   492,
     493,   494,   494,   496,   495,   497,   495,   498,   499,   501,
     502,   500,   503,   504,   500,   500,   500,   505,   505,   506,
     507,   507,   508,   509,   511,   510,   512,   513,   514,   515,
     515,   517,   516,   518,   516,   519,   516,   516,   516,   516,
     516,   516,   516,   516,   516,   516,   516,   516,   516,   516,
     516,   516,   516,   516,   516,   516,   520,   520,   520,   521,
     521,   521,   521,   522,   522,   522,   523,   523,   523,   524,
     524,   525,   525,   526,   527,   527,   528,   528,   528,   529,
     529,   530,   530,   530,   531,   531,   532,   532,   534,   533,
     536,   535,   538,   537,   539,   539,   541,   540,   542,   540,
     543,   540,   544,   540,   540,   545,   540,   540,   540,   546,
     547,   547,   549,   548,   550,   548,   551,   551,   552,   554,
     553,   556,   555,   558,   557,   559,   557,   560,   557,   561,
     561,   561,   562,   562,   563,   563,   564,   564,   564,   564,
     564,   564,   564,   564,   565,   565,   565,   565,   565,   565,
     565,   565,   565,   565,   565,   565,   565,   565,   565,   566,
     566,   566,   566,   567,   567,   567,   567,   567,   567,   567,
     567,   567,   569,   568,   570,   570,   572,   571,   573,   571,
     574,   571,   575,   571,   576,   571,   577,   571,   578,   571,
     579,   571,   580,   580,   580,   580,   580,   581,   581,   581,
     581,   582,   582,   583,   583,   584,   584,   585,   586,   587,
     588,   590,   589,   591,   591,   592,   592,   594,   593,   595,
     595,   596,   596,   598,   597,   599,   599,   601,   600,   602,
     602,   603,   603,   605,   604,   606,   606,   607,   607,   609,
     608,   610,   610,   611,   612,   613,   614
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     3,     3,     3,     0,     2,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     4,     1,     0,
       2,     4,     4,     4,     4,     4,     4,     0,     5,     4,
       3,     0,     3,     0,     3,     0,     2,     3,     3,     3,
       3,     5,     3,     4,     7,     4,     7,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     6,     6,     0,     4,
       0,     5,     4,     0,     5,     4,     1,     1,     1,     0,
       2,     0,     5,     0,     4,     0,     5,     0,     2,     0,
       5,     0,     4,     0,     5,     0,     2,     1,     2,     2,
       2,     2,     1,     2,     4,     1,     2,     4,     1,     2,
       4,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       2,     3,     0,     2,     1,     1,     3,     0,     4,     1,
       1,     2,     2,     2,     2,     2,     3,     4,     3,     0,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     0,     4,
       0,     2,     4,     0,     3,     0,     3,     5,     5,     1,
       2,     0,     1,     1,     2,     0,     4,     1,     2,     2,
       2,     2,     2,     0,     2,     3,     0,     4,     0,     2,
       3,     3,     5,     3,     3,     4,     5,     3,     0,     3,
       3,     1,     2,     0,     2,     5,     6,     1,     3,     1,
       2,     0,     2,     3,     0,     2,     2,     2,     4,     3,
       0,     6,     0,     2,     1,     1,     1,     1,     0,     4,
       1,     2,     2,     2,     2,     0,     6,     0,     2,     3,
       3,     3,     3,     0,     3,     0,     3,     0,     2,     5,
       1,     1,     3,     3,     3,     3,     0,     2,     1,     1,
       1,     2,     4,     3,     0,     3,     0,     3,     0,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     1,     1,     1,     0,     4,
       1,     2,     3,     0,     2,     1,     1,     1,     2,     2,
       2,     3,     1,     1,     1,     1,     1,     2,     1,     1,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     4,     3,     3,
       3,     3,     3,     2,     3,     4,     3,     0,     4,     0,
       4,     3,     3,     1,     1,     5,     3,     0,     3,     0,
       3,     0,     2,     2,     3,     4,     3,     4,     5,     0,
       4,     3,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     0,     5,     0,     5,
       0,     5,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     4,     3,     0,     4,     3,     4,     4,     4,     3,
       3,     1,     2,     2,     2,     2,     3,     3,     4,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     1,     1,     1,     0,     2,     0,     4,
       3,     4,     6,     4,     6,     7,     9,     1,     3,     1,
       1,     0,     2,     0,     5,     0,     7,     7,    11,     0,
       0,    10,     0,     0,    10,     6,     6,     0,     2,     1,
       6,     6,     3,     1,     0,     4,     3,     1,     2,     0,
       2,     0,     4,     0,     4,     0,    10,     9,     3,     3,
       4,     4,     4,     4,     4,     4,     4,     4,     3,     7,
       8,     6,     3,     3,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     5,     1,     2,     0,     4,     7,     1,
       1,     1,     1,     1,     1,     2,     1,     2,     0,     4,
       0,     3,     0,     3,     0,     2,     0,     4,     0,     4,
       0,     4,     0,     4,     4,     0,     4,     5,     1,     2,
       0,     2,     0,     4,     0,     4,     0,     2,     5,     0,
       6,     0,     6,     0,     6,     0,     6,     0,     6,     0,
       1,     1,     1,     2,     1,     2,     3,     3,     3,     3,
       2,     3,     6,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     3,     6,     1,     1,     3,
       3,     6,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     5,     0,     2,     0,     5,     0,     5,
       0,     5,     0,     5,     0,     5,     0,     5,     0,     5,
       0,     5,     3,     3,     1,     2,     2,     0,     4,     3,
       2,     0,     3,     0,     1,     0,     2,     4,     3,     3,
       3,     0,     8,     1,     2,     3,     1,     0,     5,     1,
       2,     1,     2,     0,     7,     1,     2,     0,     8,     1,
       2,     3,     1,     0,     5,     1,     2,     1,     2,     0,
       7,     1,     2,     3,     3,     3,     1
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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                                              );
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:
#line 223 "lef.y" /* yacc.c:1646  */
    { CALLBACK(lefrVersionCbk, lefrVersionCbkType, (yyvsp[-1].dval)); }
#line 2810 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 227 "lef.y" /* yacc.c:1646  */
    { CALLBACK(lefrDividerCharCbk, lefrDividerCharCbkType, (yyvsp[-1].string)); }
#line 2816 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 231 "lef.y" /* yacc.c:1646  */
    { CALLBACK(lefrBusBitCharsCbk, lefrBusBitCharsCbkType, (yyvsp[-1].string)); }
#line 2822 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 237 "lef.y" /* yacc.c:1646  */
    { }
#line 2828 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 241 "lef.y" /* yacc.c:1646  */
    { CALLBACK(lefrLibraryEndCbk, lefrLibraryEndCbkType, 0); }
#line 2834 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 257 "lef.y" /* yacc.c:1646  */
    {
	    lefNamesCaseSensitive = TRUE;
	    CALLBACK(lefrCaseSensitiveCbk, lefrCaseSensitiveCbkType,
			     lefNamesCaseSensitive);
	  }
#line 2844 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 263 "lef.y" /* yacc.c:1646  */
    {
	    lefNamesCaseSensitive = FALSE;
	    CALLBACK(lefrCaseSensitiveCbk, lefrCaseSensitiveCbkType,
			     lefNamesCaseSensitive);
	  }
#line 2854 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 271 "lef.y" /* yacc.c:1646  */
    { CALLBACK(lefrNoWireExtensionCbk, lefrNoWireExtensionCbkType, "ON"); }
#line 2860 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 273 "lef.y" /* yacc.c:1646  */
    { CALLBACK(lefrNoWireExtensionCbk, lefrNoWireExtensionCbkType, "OFF"); }
#line 2866 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 277 "lef.y" /* yacc.c:1646  */
    { CALLBACK(lefrUnitsCbk, lefrUnitsCbkType, &lefrUnits); }
#line 2872 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 281 "lef.y" /* yacc.c:1646  */
    { lefrUnits.lefiUnits::clear(); }
#line 2878 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 289 "lef.y" /* yacc.c:1646  */
    { if (lefrUnitsCbk) lefrUnits.lefiUnits::setTime((yyvsp[-1].dval)); }
#line 2884 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 291 "lef.y" /* yacc.c:1646  */
    { if (lefrUnitsCbk) lefrUnits.lefiUnits::setCapacitance((yyvsp[-1].dval)); }
#line 2890 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 293 "lef.y" /* yacc.c:1646  */
    { if (lefrUnitsCbk) lefrUnits.lefiUnits::setResistance((yyvsp[-1].dval)); }
#line 2896 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 295 "lef.y" /* yacc.c:1646  */
    { if (lefrUnitsCbk) lefrUnits.lefiUnits::setPower((yyvsp[-1].dval)); }
#line 2902 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 297 "lef.y" /* yacc.c:1646  */
    { if (lefrUnitsCbk) lefrUnits.lefiUnits::setCurrent((yyvsp[-1].dval)); }
#line 2908 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 299 "lef.y" /* yacc.c:1646  */
    { if (lefrUnitsCbk) lefrUnits.lefiUnits::setVoltage((yyvsp[-1].dval)); }
#line 2914 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 300 "lef.y" /* yacc.c:1646  */
    { lefDumbMode = 1; }
#line 2920 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 301 "lef.y" /* yacc.c:1646  */
    { if (lefrUnitsCbk) lefrUnits.lefiUnits::setDatabase((yyvsp[-2].string), (yyvsp[-1].dval)); }
#line 2926 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 303 "lef.y" /* yacc.c:1646  */
    { if (lefrUnitsCbk) lefrUnits.lefiUnits::setFrequency((yyvsp[-1].dval)); }
#line 2932 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 307 "lef.y" /* yacc.c:1646  */
    { CALLBACK(lefrLayerCbk, lefrLayerCbkType, &lefrLayer); }
#line 2938 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 310 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefNoNum = 1; }
#line 2944 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 311 "lef.y" /* yacc.c:1646  */
    { 
      if (lefrLayerCbk)
        lefrLayer.lefiLayer::setName((yyvsp[0].string));
      useLenThr = 0;
      lenThr = 0;
    }
#line 2955 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 319 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefNoNum = 1; }
#line 2961 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 320 "lef.y" /* yacc.c:1646  */
    { }
#line 2967 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 325 "lef.y" /* yacc.c:1646  */
    { }
#line 2973 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 327 "lef.y" /* yacc.c:1646  */
    { }
#line 2979 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 332 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::setType((yyvsp[-1].string)); }
#line 2985 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 334 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::setPitch((yyvsp[-1].dval)); }
#line 2991 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 336 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::setOffset((yyvsp[-1].dval)); }
#line 2997 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 338 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::setWidth((yyvsp[-1].dval)); }
#line 3003 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 340 "lef.y" /* yacc.c:1646  */
    {
      if (lefrLayerCbk) {
        if (lenThr) {
	  lefrLayer.lefiLayer::setSpacing((yyvsp[-3].dval), (yyvsp[-2].pt).x, (yyvsp[-2].pt).y);
          lefrLayer.lefiLayer::setSpacingLength((yyvsp[-2].pt).x);
          lenThr = 0;
        } else {
	  lefrLayer.lefiLayer::setSpacing((yyvsp[-3].dval), (yyvsp[-2].pt).x, (yyvsp[-2].pt).y);
          if (useLenThr) {
            lefrLayer.lefiLayer::setSpacingUseLength();
            useLenThr = 0;
          }
        }
	if ((yyvsp[-1].string)) lefrLayer.lefiLayer::setSpacingName((yyvsp[-1].string));
      } 
    }
#line 3024 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 357 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::setDirection((yyvsp[-1].string)); }
#line 3030 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 359 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::setResistance((yyvsp[-1].dval)); }
#line 3036 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 361 "lef.y" /* yacc.c:1646  */
    { }
#line 3042 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 363 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::setCapacitance((yyvsp[-1].dval)); }
#line 3048 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 365 "lef.y" /* yacc.c:1646  */
    { }
#line 3054 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 367 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::setHeight((yyvsp[-1].dval)); }
#line 3060 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 369 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::setWireExtension((yyvsp[-1].dval)); }
#line 3066 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 371 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::setThickness((yyvsp[-1].dval)); }
#line 3072 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 373 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::setShrinkage((yyvsp[-1].dval)); }
#line 3078 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 375 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::setCapMultiplier((yyvsp[-1].dval)); }
#line 3084 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 377 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::setEdgeCap((yyvsp[-1].dval)); }
#line 3090 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 379 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::setAntennaArea((yyvsp[-1].dval)); }
#line 3096 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 381 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::setAntennaLength((yyvsp[-1].dval)); }
#line 3102 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 383 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::setCurrentDensity((yyvsp[-1].dval)); }
#line 3108 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 385 "lef.y" /* yacc.c:1646  */
    { }
#line 3114 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 387 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::setCurrentPoint((yyvsp[-3].dval), (yyvsp[-2].dval)); }
#line 3120 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 388 "lef.y" /* yacc.c:1646  */
    { lefDumbMode = 10000000; }
#line 3126 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 389 "lef.y" /* yacc.c:1646  */
    { lefDumbMode = 0; }
#line 3132 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 391 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::addAccurrentDensity((yyvsp[0].string)); }
#line 3138 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 394 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) {
         lefrLayer.lefiLayer::addAccurrentDensity((yyvsp[-2].string));
         lefrLayer.lefiLayer::setAcOneEntry((yyvsp[-1].dval));
       }
    }
#line 3148 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 400 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::addDccurrentDensity("AVERAGE"); }
#line 3154 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 403 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) {
         lefrLayer.lefiLayer::addDccurrentDensity("AVERAGE");
         lefrLayer.lefiLayer::setDcOneEntry((yyvsp[-1].dval));
       }
    }
#line 3164 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 411 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"PEAK";}
#line 3170 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 412 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"AVERAGE";}
#line 3176 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 413 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"RMS";}
#line 3182 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 422 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::addNumber((yyvsp[0].dval)); }
#line 3188 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 424 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::addAcFrequency(); }
#line 3194 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 426 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::addNumber((yyvsp[0].dval)); }
#line 3200 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 428 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::addAcTableEntry(); }
#line 3206 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 430 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::addNumber((yyvsp[0].dval)); }
#line 3212 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 432 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::addAcWidth(); }
#line 3218 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 441 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::addNumber((yyvsp[0].dval)); }
#line 3224 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 443 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::addDcCutarea(); }
#line 3230 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 445 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::addNumber((yyvsp[0].dval)); }
#line 3236 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 447 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::addDcTableEntry(); }
#line 3242 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 449 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::addNumber((yyvsp[0].dval)); }
#line 3248 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 451 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::addDcWidth(); }
#line 3254 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 456 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::addNumber((yyvsp[0].dval)); }
#line 3260 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 466 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::addProp((yyvsp[-1].string), (yyvsp[0].string)); }
#line 3266 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 468 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::addProp((yyvsp[-1].string), (yyvsp[0].string)); }
#line 3272 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 470 "lef.y" /* yacc.c:1646  */
    {
      char temp[32];
      sprintf(temp, "%g", (yyvsp[0].dval));
      if (lefrLayerCbk) lefrLayer.lefiLayer::addProp((yyvsp[-1].string), temp);
    }
#line 3282 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 479 "lef.y" /* yacc.c:1646  */
    { }
#line 3288 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 481 "lef.y" /* yacc.c:1646  */
    { }
#line 3294 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 485 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::setCurrentPoint((yyvsp[-2].dval), (yyvsp[-1].dval)); }
#line 3300 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 494 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::setCapacitancePoint((yyvsp[-2].dval), (yyvsp[-1].dval)); }
#line 3306 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 500 "lef.y" /* yacc.c:1646  */
    { }
#line 3312 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 504 "lef.y" /* yacc.c:1646  */
    { if (lefrLayerCbk) lefrLayer.lefiLayer::setResistancePoint((yyvsp[-2].dval), (yyvsp[-1].dval)); }
#line 3318 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 508 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"ROUTING";}
#line 3324 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 509 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"CUT";}
#line 3330 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 510 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"OVERLAP";}
#line 3336 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 511 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"MASTERSLICE";}
#line 3342 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 512 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"VIRTUAL";}
#line 3348 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 516 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"HORIZONTAL";}
#line 3354 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 517 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"VERTICAL";}
#line 3360 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 521 "lef.y" /* yacc.c:1646  */
    { CALLBACK(lefrViaCbk, lefrViaCbkType, &lefrVia); }
#line 3366 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 526 "lef.y" /* yacc.c:1646  */
    { lefDumbMode = 1; lefNoNum = 1;}
#line 3372 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 530 "lef.y" /* yacc.c:1646  */
    {
      /* 0 is nodefault */
      if (lefrViaCbk) lefrVia.lefiVia::setName((yyvsp[0].string), 0);
    }
#line 3381 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 535 "lef.y" /* yacc.c:1646  */
    {
      /* 1 is default */
      if (lefrViaCbk) lefrVia.lefiVia::setName((yyvsp[-1].string), 1);
    }
#line 3390 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 548 "lef.y" /* yacc.c:1646  */
    { }
#line 3396 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 550 "lef.y" /* yacc.c:1646  */
    { }
#line 3402 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 552 "lef.y" /* yacc.c:1646  */
    { if (lefrViaCbk) lefrVia.lefiVia::setResistance((yyvsp[-1].dval)); }
#line 3408 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 553 "lef.y" /* yacc.c:1646  */
    { lefDumbMode = 1000000; }
#line 3414 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 554 "lef.y" /* yacc.c:1646  */
    { lefDumbMode = 0; }
#line 3420 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 556 "lef.y" /* yacc.c:1646  */
    { if (lefrViaCbk) lefrVia.lefiVia::setTopOfStack(); }
#line 3426 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 566 "lef.y" /* yacc.c:1646  */
    { if (lefrViaCbk) lefrVia.lefiVia::addNumProp((yyvsp[-1].string), (yyvsp[0].dval)); }
#line 3432 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 568 "lef.y" /* yacc.c:1646  */
    { if (lefrViaCbk) lefrVia.lefiVia::addProp((yyvsp[-1].string), (yyvsp[0].string)); }
#line 3438 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 570 "lef.y" /* yacc.c:1646  */
    { if (lefrViaCbk) lefrVia.lefiVia::addProp((yyvsp[-1].string), (yyvsp[0].string)); }
#line 3444 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 575 "lef.y" /* yacc.c:1646  */
    { if (lefrViaCbk) lefrVia.lefiVia::setForeign((yyvsp[-1].string), 0, 0.0, 0.0, -1); }
#line 3450 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 577 "lef.y" /* yacc.c:1646  */
    { if (lefrViaCbk) lefrVia.lefiVia::setForeign((yyvsp[-2].string), 1, (yyvsp[-1].pt).x, (yyvsp[-1].pt).y, -1); }
#line 3456 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 579 "lef.y" /* yacc.c:1646  */
    { if (lefrViaCbk) lefrVia.lefiVia::setForeign((yyvsp[-3].string), 1, (yyvsp[-2].pt).x, (yyvsp[-2].pt).y, (yyvsp[-1].integer)); }
#line 3462 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 581 "lef.y" /* yacc.c:1646  */
    { if (lefrViaCbk) lefrVia.lefiVia::setForeign((yyvsp[-2].string), 0, 0.0, 0.0, (yyvsp[-1].integer)); }
#line 3468 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 584 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefNoNum= 1;}
#line 3474 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 585 "lef.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 3480 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 589 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = 0;}
#line 3486 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 590 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = 3;}
#line 3492 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 591 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = 2;}
#line 3498 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 592 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = 1;}
#line 3504 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 593 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = 4;}
#line 3510 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 594 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = 5;}
#line 3516 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 595 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = 6;}
#line 3522 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 596 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = 7;}
#line 3528 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 597 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = 0;}
#line 3534 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 598 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = 1;}
#line 3540 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 599 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = 2;}
#line 3546 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 600 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = 3;}
#line 3552 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 601 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = 4;}
#line 3558 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 602 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = 5;}
#line 3564 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 603 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = 6;}
#line 3570 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 604 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = 7;}
#line 3576 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 608 "lef.y" /* yacc.c:1646  */
    { }
#line 3582 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 611 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefNoNum = 1; }
#line 3588 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 612 "lef.y" /* yacc.c:1646  */
    { if (lefrViaCbk) lefrVia.lefiVia::addLayer((yyvsp[-1].string)); }
#line 3594 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 621 "lef.y" /* yacc.c:1646  */
    { if (lefrViaCbk)
      lefrVia.lefiVia::addRectToLayer((yyvsp[-2].pt).x, (yyvsp[-2].pt).y, (yyvsp[-1].pt).x, (yyvsp[-1].pt).y); }
#line 3601 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 625 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefNoNum = 1;}
#line 3607 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 626 "lef.y" /* yacc.c:1646  */
    { }
#line 3613 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 629 "lef.y" /* yacc.c:1646  */
    { lefDumbMode = 1; lefNoNum = 1;}
#line 3619 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 630 "lef.y" /* yacc.c:1646  */
    { if (lefrViaRuleCbk) lefrViaRule.lefiViaRule::setName((yyvsp[0].string)); }
#line 3625 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 635 "lef.y" /* yacc.c:1646  */
    { CALLBACK(lefrViaRuleCbk, lefrViaRuleCbkType, &lefrViaRule); }
#line 3631 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 641 "lef.y" /* yacc.c:1646  */
    {
      if (lefrViaRuleCbk) lefrViaRule.lefiViaRule::setGenerate();
      CALLBACK(lefrViaRuleCbk, lefrViaRuleCbkType, &lefrViaRule);
    }
#line 3640 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 662 "lef.y" /* yacc.c:1646  */
    { lefDumbMode = 10000000; }
#line 3646 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 663 "lef.y" /* yacc.c:1646  */
    { lefDumbMode = 0; }
#line 3652 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 673 "lef.y" /* yacc.c:1646  */
    { if (lefrViaRuleCbk) lefrViaRule.lefiViaRule::addProp((yyvsp[-1].string), (yyvsp[0].string)); }
#line 3658 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 675 "lef.y" /* yacc.c:1646  */
    { if (lefrViaRuleCbk) lefrViaRule.lefiViaRule::addProp((yyvsp[-1].string), (yyvsp[0].string)); }
#line 3664 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 677 "lef.y" /* yacc.c:1646  */
    {
      char temp[32];
      sprintf(temp, "%g", (yyvsp[0].dval));
      if (lefrViaRuleCbk) lefrViaRule.lefiViaRule::addProp((yyvsp[-1].string), temp);
    }
#line 3674 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 693 "lef.y" /* yacc.c:1646  */
    { if (lefrViaRuleCbk) lefrViaRule.lefiViaRule::addViaName((yyvsp[-1].string)); }
#line 3680 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 696 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefNoNum = 1; }
#line 3686 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 697 "lef.y" /* yacc.c:1646  */
    { if (lefrViaRuleCbk) lefrViaRule.lefiViaRule::setLayer((yyvsp[-1].string)); }
#line 3692 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 707 "lef.y" /* yacc.c:1646  */
    { if (lefrViaRuleCbk) lefrViaRule.lefiViaRule::setHorizontal(); }
#line 3698 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 709 "lef.y" /* yacc.c:1646  */
    { if (lefrViaRuleCbk) lefrViaRule.lefiViaRule::setVertical(); }
#line 3704 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 711 "lef.y" /* yacc.c:1646  */
    { if (lefrViaRuleCbk) lefrViaRule.lefiViaRule::setWidth((yyvsp[-3].dval),(yyvsp[-1].dval)); }
#line 3710 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 713 "lef.y" /* yacc.c:1646  */
    { if (lefrViaRuleCbk) lefrViaRule.lefiViaRule::setOverhang((yyvsp[-1].dval)); }
#line 3716 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 715 "lef.y" /* yacc.c:1646  */
    { if (lefrViaRuleCbk) lefrViaRule.lefiViaRule::setMetalOverhang((yyvsp[-1].dval)); }
#line 3722 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 717 "lef.y" /* yacc.c:1646  */
    { if (lefrViaRuleCbk)
	lefrViaRule.lefiViaRule::setRect((yyvsp[-2].pt).x, (yyvsp[-2].pt).y, (yyvsp[-1].pt).x, (yyvsp[-1].pt).y); }
#line 3729 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 720 "lef.y" /* yacc.c:1646  */
    { if (lefrViaRuleCbk) lefrViaRule.lefiViaRule::setSpacing((yyvsp[-3].dval),(yyvsp[-1].dval)); }
#line 3735 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 722 "lef.y" /* yacc.c:1646  */
    { if (lefrViaRuleCbk) lefrViaRule.lefiViaRule::setResistance((yyvsp[-1].dval)); }
#line 3741 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 726 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefNoNum = 1;}
#line 3747 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 727 "lef.y" /* yacc.c:1646  */
    { }
#line 3753 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 731 "lef.y" /* yacc.c:1646  */
    { }
#line 3759 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 735 "lef.y" /* yacc.c:1646  */
    { if (lefrSpacingBeginCbk)
	CALLBACK(lefrSpacingBeginCbk, lefrSpacingBeginCbkType, 0); }
#line 3766 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 740 "lef.y" /* yacc.c:1646  */
    { if (lefrSpacingEndCbk)
            CALLBACK(lefrSpacingEndCbk, lefrSpacingEndCbkType, 0); }
#line 3773 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 750 "lef.y" /* yacc.c:1646  */
    {
      if (lefrSpacingCbk) {
	lefrSpacing.lefiSpacing::set((yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-1].dval), 0);
	CALLBACK(lefrSpacingCbk, lefrSpacingCbkType, &lefrSpacing);
      }
    }
#line 3784 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 757 "lef.y" /* yacc.c:1646  */
    {
      if (lefrSpacingCbk) {
	lefrSpacing.lefiSpacing::set((yyvsp[-4].string), (yyvsp[-3].string), (yyvsp[-2].dval), 1);
	CALLBACK(lefrSpacingCbk, lefrSpacingCbkType, &lefrSpacing);
      }
    }
#line 3795 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 766 "lef.y" /* yacc.c:1646  */
    { lefDumbMode = 2; lefNoNum = 2; }
#line 3801 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 770 "lef.y" /* yacc.c:1646  */
    { }
#line 3807 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 774 "lef.y" /* yacc.c:1646  */
    { if (lefrIRDropBeginCbk)
	CALLBACK(lefrIRDropBeginCbk, lefrIRDropBeginCbkType, 0); }
#line 3814 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 779 "lef.y" /* yacc.c:1646  */
    { if (lefrIRDropEndCbk)
	  CALLBACK(lefrIRDropEndCbk, lefrIRDropEndCbkType, 0); }
#line 3821 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 789 "lef.y" /* yacc.c:1646  */
    { CALLBACK(lefrIRDropCbk, lefrIRDropCbkType, &lefrIRDrop); }
#line 3827 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 798 "lef.y" /* yacc.c:1646  */
    { if (lefrIRDropCbk) lefrIRDrop.lefiIRDrop::setValues((yyvsp[-1].dval), (yyvsp[0].dval)); }
#line 3833 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 802 "lef.y" /* yacc.c:1646  */
    { if (lefrIRDropCbk) lefrIRDrop.lefiIRDrop::setTableName((yyvsp[0].string)); }
#line 3839 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 806 "lef.y" /* yacc.c:1646  */
    {
    if (lefrMinFeatureCbk)
      lefrMinFeature.lefiMinFeature::set((yyvsp[-2].dval), (yyvsp[-1].dval));
    CALLBACK(lefrMinFeatureCbk, lefrMinFeatureCbkType, &lefrMinFeature);
  }
#line 3849 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 814 "lef.y" /* yacc.c:1646  */
    { CALLBACK(lefrDielectricCbk, lefrDielectricCbkType, (yyvsp[-1].dval)); }
#line 3855 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 818 "lef.y" /* yacc.c:1646  */
    { if (lefrNonDefaultCbk) lefrNonDefault.lefiNonDefault::setName((yyvsp[0].string)); }
#line 3861 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 820 "lef.y" /* yacc.c:1646  */
    {
    if (lefrNonDefaultCbk) lefrNonDefault.lefiNonDefault::end();
    CALLBACK(lefrNonDefaultCbk, lefrNonDefaultCbkType, &lefrNonDefault);
  }
#line 3870 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 838 "lef.y" /* yacc.c:1646  */
    { lefDumbMode = 10000000; }
#line 3876 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 839 "lef.y" /* yacc.c:1646  */
    { lefDumbMode = 0; }
#line 3882 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 252:
#line 849 "lef.y" /* yacc.c:1646  */
    { if (lefrNonDefaultCbk) lefrNonDefault.lefiNonDefault::addProp((yyvsp[-1].string), (yyvsp[0].string));
    }
#line 3889 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 253:
#line 852 "lef.y" /* yacc.c:1646  */
    { if (lefrNonDefaultCbk) lefrNonDefault.lefiNonDefault::addProp((yyvsp[-1].string), (yyvsp[0].string));
    }
#line 3896 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 855 "lef.y" /* yacc.c:1646  */
    {
      char temp[32];
      sprintf(temp, "%g", (yyvsp[0].dval));
      if (lefrNonDefaultCbk)
	lefrNonDefault.lefiNonDefault::addProp((yyvsp[-1].string), temp);
    }
#line 3907 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 864 "lef.y" /* yacc.c:1646  */
    { if (lefrNonDefaultCbk) lefrNonDefault.lefiNonDefault::addLayer((yyvsp[0].string)); }
#line 3913 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 875 "lef.y" /* yacc.c:1646  */
    { if (lefrNonDefaultCbk) lefrNonDefault.lefiNonDefault::addWidth((yyvsp[-1].dval)); }
#line 3919 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 260:
#line 877 "lef.y" /* yacc.c:1646  */
    { if (lefrNonDefaultCbk) lefrNonDefault.lefiNonDefault::addSpacing((yyvsp[-1].dval)); }
#line 3925 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 261:
#line 879 "lef.y" /* yacc.c:1646  */
    { if (lefrNonDefaultCbk)
    lefrNonDefault.lefiNonDefault::addWireExtension((yyvsp[-1].dval)); }
#line 3932 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 884 "lef.y" /* yacc.c:1646  */
    { CALLBACK(lefrSiteCbk, lefrSiteCbkType, &lefrSite); }
#line 3938 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 263:
#line 887 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefNoNum = 1;}
#line 3944 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 888 "lef.y" /* yacc.c:1646  */
    { if (lefrSiteCbk) lefrSite.lefiSite::setName((yyvsp[0].string)); }
#line 3950 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 891 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefNoNum = 1;}
#line 3956 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 892 "lef.y" /* yacc.c:1646  */
    { }
#line 3962 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 902 "lef.y" /* yacc.c:1646  */
    { if (lefrSiteCbk) lefrSite.lefiSite::setSize((yyvsp[-3].dval),(yyvsp[-1].dval)); }
#line 3968 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 270:
#line 904 "lef.y" /* yacc.c:1646  */
    { }
#line 3974 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 906 "lef.y" /* yacc.c:1646  */
    { if (lefrSiteCbk) lefrSite.lefiSite::setClass((yyvsp[0].string)); }
#line 3980 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 272:
#line 910 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"PAD"; }
#line 3986 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 911 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"CORE"; }
#line 3992 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 912 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"VIRTUAL"; }
#line 3998 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 275:
#line 916 "lef.y" /* yacc.c:1646  */
    { }
#line 4004 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 278:
#line 926 "lef.y" /* yacc.c:1646  */
    { if (lefrSiteCbk) lefrSite.lefiSite::setXSymmetry(); }
#line 4010 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 279:
#line 928 "lef.y" /* yacc.c:1646  */
    { if (lefrSiteCbk) lefrSite.lefiSite::setYSymmetry(); }
#line 4016 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 280:
#line 930 "lef.y" /* yacc.c:1646  */
    { if (lefrSiteCbk) lefrSite.lefiSite::set90Symmetry(); }
#line 4022 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 281:
#line 935 "lef.y" /* yacc.c:1646  */
    { (yyval.pt).x = (yyvsp[-1].dval); (yyval.pt).y = (yyvsp[0].dval); }
#line 4028 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 937 "lef.y" /* yacc.c:1646  */
    { (yyval.pt).x = (yyvsp[-2].dval); (yyval.pt).y = (yyvsp[-1].dval); }
#line 4034 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 941 "lef.y" /* yacc.c:1646  */
    { CALLBACK(lefrMacroCbk, lefrMacroCbkType, &lefrMacro); lefrDoSite = 0; }
#line 4040 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 284:
#line 944 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefNoNum = 1;}
#line 4046 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 285:
#line 945 "lef.y" /* yacc.c:1646  */
    {
      siteDef = 0;
      symDef = 0;
      sizeDef = 0; 
      pinDef = 0; 
      obsDef = 0; 
      origDef = 0;
      lefrMacro.lefiMacro::clear();      
      if (lefrMacroCbk) lefrMacro.lefiMacro::setName((yyvsp[0].string));
      CALLBACK(lefrMacroBeginCbk, lefrMacroBeginCbkType, (yyvsp[0].string));
    }
#line 4062 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 286:
#line 958 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefNoNum = 1;}
#line 4068 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 959 "lef.y" /* yacc.c:1646  */
    { }
#line 4074 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 295:
#line 974 "lef.y" /* yacc.c:1646  */
    { }
#line 4080 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 296:
#line 976 "lef.y" /* yacc.c:1646  */
    { }
#line 4086 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 297:
#line 978 "lef.y" /* yacc.c:1646  */
    { }
#line 4092 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 300:
#line 982 "lef.y" /* yacc.c:1646  */
    { }
#line 4098 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 984 "lef.y" /* yacc.c:1646  */
    { }
#line 4104 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 302:
#line 986 "lef.y" /* yacc.c:1646  */
    { }
#line 4110 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 303:
#line 988 "lef.y" /* yacc.c:1646  */
    { if (lefrMacroCbk) lefrMacro.lefiMacro::setBuffer(); }
#line 4116 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 304:
#line 990 "lef.y" /* yacc.c:1646  */
    { if (lefrMacroCbk) lefrMacro.lefiMacro::setInverter(); }
#line 4122 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 992 "lef.y" /* yacc.c:1646  */
    { }
#line 4128 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 306:
#line 994 "lef.y" /* yacc.c:1646  */
    { }
#line 4134 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 307:
#line 996 "lef.y" /* yacc.c:1646  */
    { }
#line 4140 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 308:
#line 997 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1000000;}
#line 4146 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 309:
#line 998 "lef.y" /* yacc.c:1646  */
    { lefDumbMode = 0; }
#line 4152 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 312:
#line 1007 "lef.y" /* yacc.c:1646  */
    { symDef = 1; }
#line 4158 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 315:
#line 1017 "lef.y" /* yacc.c:1646  */
    { if (lefrMacroCbk) lefrMacro.lefiMacro::setXSymmetry(); }
#line 4164 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 316:
#line 1019 "lef.y" /* yacc.c:1646  */
    { if (lefrMacroCbk) lefrMacro.lefiMacro::setYSymmetry(); }
#line 4170 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 317:
#line 1021 "lef.y" /* yacc.c:1646  */
    { if (lefrMacroCbk) lefrMacro.lefiMacro::set90Symmetry(); }
#line 4176 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 318:
#line 1026 "lef.y" /* yacc.c:1646  */
    { if (lefrMacroCbk) lefrMacro.lefiMacro::setNumProperty((yyvsp[-1].string), (yyvsp[0].dval)); }
#line 4182 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 319:
#line 1028 "lef.y" /* yacc.c:1646  */
    { if (lefrMacroCbk) lefrMacro.lefiMacro::setProperty((yyvsp[-1].string), (yyvsp[0].string)); }
#line 4188 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 320:
#line 1030 "lef.y" /* yacc.c:1646  */
    { if (lefrMacroCbk) lefrMacro.lefiMacro::setProperty((yyvsp[-1].string), (yyvsp[0].string)); }
#line 4194 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 321:
#line 1034 "lef.y" /* yacc.c:1646  */
    { if (lefrMacroCbk) lefrMacro.lefiMacro::setClass((yyvsp[-1].string)); }
#line 4200 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 322:
#line 1038 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"COVER"; }
#line 4206 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 323:
#line 1039 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"RING"; }
#line 4212 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 324:
#line 1040 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"BLOCK"; }
#line 4218 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 325:
#line 1041 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"PAD"; }
#line 4224 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 326:
#line 1042 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"VIRTUAL"; }
#line 4230 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 327:
#line 1044 "lef.y" /* yacc.c:1646  */
    {sprintf(temp_name, "PAD %s", (yyvsp[0].string));
      (yyval.string) = temp_name;}
#line 4237 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 328:
#line 1046 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"CORE"; }
#line 4243 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 329:
#line 1048 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"CORNER";
      /* This token is NOT in the spec but has shown up in 
       * some lef files.  This exception came from LEFOUT
       * in 'frameworks'
       */
      }
#line 4254 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 330:
#line 1055 "lef.y" /* yacc.c:1646  */
    {sprintf(temp_name, "CORE %s", (yyvsp[0].string));
      (yyval.string) = temp_name;}
#line 4261 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 331:
#line 1058 "lef.y" /* yacc.c:1646  */
    {sprintf(temp_name, "ENDCAP %s", (yyvsp[0].string));
      (yyval.string) = temp_name;}
#line 4268 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 332:
#line 1063 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"INPUT";}
#line 4274 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 333:
#line 1064 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"OUTPUT";}
#line 4280 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 334:
#line 1065 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"INOUT";}
#line 4286 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 335:
#line 1066 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"POWER";}
#line 4292 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 336:
#line 1067 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"SPACER";}
#line 4298 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 337:
#line 1071 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"FEEDTHRU";}
#line 4304 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 338:
#line 1072 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"TIEHIGH";}
#line 4310 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 339:
#line 1073 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"TIELOW";}
#line 4316 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 340:
#line 1077 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"PRE";}
#line 4322 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 341:
#line 1078 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"POST";}
#line 4328 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 342:
#line 1079 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"TOPLEFT";}
#line 4334 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 343:
#line 1080 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"TOPRIGHT";}
#line 4340 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 344:
#line 1081 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"BOTTOMLEFT";}
#line 4346 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 345:
#line 1082 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"BOTTOMRIGHT";}
#line 4352 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 346:
#line 1086 "lef.y" /* yacc.c:1646  */
    { if (lefrMacroCbk) lefrMacro.lefiMacro::setGenerator((yyvsp[-1].string)); }
#line 4358 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 347:
#line 1090 "lef.y" /* yacc.c:1646  */
    { if (lefrMacroCbk) lefrMacro.lefiMacro::setGenerate((yyvsp[-2].string), (yyvsp[-1].string)); }
#line 4364 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 348:
#line 1095 "lef.y" /* yacc.c:1646  */
    { if (lefrMacroCbk) lefrMacro.lefiMacro::setSource("USER"); }
#line 4370 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 349:
#line 1097 "lef.y" /* yacc.c:1646  */
    { if (lefrMacroCbk) lefrMacro.lefiMacro::setSource("GENERATE"); }
#line 4376 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 350:
#line 1099 "lef.y" /* yacc.c:1646  */
    { if (lefrMacroCbk) lefrMacro.lefiMacro::setSource("BLOCK"); }
#line 4382 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 351:
#line 1103 "lef.y" /* yacc.c:1646  */
    { if (lefrMacroCbk) lefrMacro.lefiMacro::setPower((yyvsp[-1].dval)); }
#line 4388 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 352:
#line 1107 "lef.y" /* yacc.c:1646  */
    { 
       if (origDef) { /* Has multiple ORIGIN defined in a macro, stop parsing*/
          yyerror("ORIGIN statement is defined more than once.  Parser stops executions.");
          return 1;
       }
       origDef = 1;
       if (siteDef) { /* SITE is defined before ORIGIN, error, stop parsing */
          yyerror("SITE is defined before ORIGIN.  Parser stops execution.");
          return 1;
       } else if (pinDef) { /* PIN is defined before ORIGIN */
          yyerror("PIN is defined before ORIGIN.  Parser stops execution");
          return 1;
       } else if (obsDef) { /* OBS is defined before ORIGIN */
          yyerror("OBS is defined before ORIGIN.  Parser stops execution");
          return 1;
       }
       if (lefrMacroCbk) lefrMacro.lefiMacro::setOrigin((yyvsp[-1].pt).x, (yyvsp[-1].pt).y);
    }
#line 4411 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 353:
#line 1129 "lef.y" /* yacc.c:1646  */
    { if (lefrMacroCbk)
      lefrMacro.lefiMacro::setForeign((yyvsp[-1].string), 0, 0.0, 0.0, -1); }
#line 4418 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 354:
#line 1132 "lef.y" /* yacc.c:1646  */
    { if (lefrMacroCbk)
      lefrMacro.lefiMacro::setForeign((yyvsp[-2].string), 1, (yyvsp[-1].pt).x, (yyvsp[-1].pt).y, -1); }
#line 4425 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 355:
#line 1135 "lef.y" /* yacc.c:1646  */
    { if (lefrMacroCbk)
      lefrMacro.lefiMacro::setForeign((yyvsp[-3].string), 1, (yyvsp[-2].pt).x, (yyvsp[-2].pt).y, (yyvsp[-1].integer)); }
#line 4432 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 356:
#line 1138 "lef.y" /* yacc.c:1646  */
    { if (lefrMacroCbk)
      lefrMacro.lefiMacro::setForeign((yyvsp[-2].string), 0, 0.0, 0.0, (yyvsp[-1].integer)); }
#line 4439 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 357:
#line 1142 "lef.y" /* yacc.c:1646  */
    { lefDumbMode = 1; lefNoNum = 1; }
#line 4445 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 358:
#line 1143 "lef.y" /* yacc.c:1646  */
    { if (lefrMacroCbk) lefrMacro.lefiMacro::setEEQ((yyvsp[-1].string)); }
#line 4451 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 359:
#line 1146 "lef.y" /* yacc.c:1646  */
    { lefDumbMode = 1; lefNoNum = 1; }
#line 4457 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 360:
#line 1147 "lef.y" /* yacc.c:1646  */
    { if (lefrMacroCbk) lefrMacro.lefiMacro::setLEQ((yyvsp[-1].string)); }
#line 4463 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 361:
#line 1152 "lef.y" /* yacc.c:1646  */
    { if (lefrMacroCbk) lefrMacro.lefiMacro::setSiteName((yyvsp[-1].string)); }
#line 4469 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 362:
#line 1154 "lef.y" /* yacc.c:1646  */
    {
      if (lefrMacroCbk) {
	lefrMacro.lefiMacro::setSitePattern(lefrSitePatternPtr);
	lefrSitePatternPtr = 0;
      }
    }
#line 4480 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 363:
#line 1163 "lef.y" /* yacc.c:1646  */
    { lefDumbMode = 1; lefNoNum = 1; siteDef = 1;
        if (lefrMacroCbk) lefrDoSite = 1; }
#line 4487 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 364:
#line 1168 "lef.y" /* yacc.c:1646  */
    { lefDumbMode = 1; lefNoNum = 1; }
#line 4493 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 365:
#line 1172 "lef.y" /* yacc.c:1646  */
    { 
      sizeDef = 1;
      if (lefrMacroCbk) lefrMacro.lefiMacro::setSize((yyvsp[-3].dval), (yyvsp[-1].dval));
    }
#line 4502 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 366:
#line 1182 "lef.y" /* yacc.c:1646  */
    { CALLBACK(lefrPinCbk, lefrPinCbkType, &lefrPin); }
#line 4508 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 367:
#line 1185 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefNoNum = 1; pinDef = 1;}
#line 4514 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 368:
#line 1186 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setName((yyvsp[0].string)); }
#line 4520 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 369:
#line 1189 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefNoNum = 1;}
#line 4526 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 370:
#line 1190 "lef.y" /* yacc.c:1646  */
    { }
#line 4532 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 371:
#line 1195 "lef.y" /* yacc.c:1646  */
    { }
#line 4538 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 372:
#line 1197 "lef.y" /* yacc.c:1646  */
    { }
#line 4544 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 373:
#line 1202 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setForeign((yyvsp[-1].string), 0, 0.0, 0.0, -1); }
#line 4550 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 374:
#line 1204 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setForeign((yyvsp[-2].string), 1, (yyvsp[-1].pt).x, (yyvsp[-1].pt).y, -1); }
#line 4556 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 375:
#line 1206 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setForeign((yyvsp[-3].string), 1, (yyvsp[-2].pt).x, (yyvsp[-2].pt).y, (yyvsp[-1].integer)); }
#line 4562 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 376:
#line 1208 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setForeign((yyvsp[-2].string), 0, 0.0, 0.0, -1); }
#line 4568 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 377:
#line 1210 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setForeign((yyvsp[-3].string), 1, (yyvsp[-1].pt).x, (yyvsp[-1].pt).y, -1); }
#line 4574 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 378:
#line 1212 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setForeign((yyvsp[-4].string), 1, (yyvsp[-2].pt).x, (yyvsp[-2].pt).y, (yyvsp[-1].integer)); }
#line 4580 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 379:
#line 1213 "lef.y" /* yacc.c:1646  */
    { lefDumbMode = 1; lefNoNum = 1; }
#line 4586 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 380:
#line 1214 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setLEQ((yyvsp[-1].string)); }
#line 4592 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 381:
#line 1216 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setPower((yyvsp[-1].dval)); }
#line 4598 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 382:
#line 1218 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setDirection((yyvsp[0].string)); }
#line 4604 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 383:
#line 1220 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setUse((yyvsp[-1].string)); }
#line 4610 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 384:
#line 1222 "lef.y" /* yacc.c:1646  */
    { }
#line 4616 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 385:
#line 1224 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setLeakage((yyvsp[-1].dval)); }
#line 4622 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 386:
#line 1226 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setRiseThresh((yyvsp[-1].dval)); }
#line 4628 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 387:
#line 1228 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setFallThresh((yyvsp[-1].dval)); }
#line 4634 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 388:
#line 1230 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setRiseSatcur((yyvsp[-1].dval)); }
#line 4640 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 389:
#line 1232 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setFallSatcur((yyvsp[-1].dval)); }
#line 4646 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 390:
#line 1234 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setVLO((yyvsp[-1].dval)); }
#line 4652 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 391:
#line 1236 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setVHI((yyvsp[-1].dval)); }
#line 4658 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 392:
#line 1238 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setTieoffr((yyvsp[-1].dval)); }
#line 4664 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 393:
#line 1240 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setShape((yyvsp[-1].string)); }
#line 4670 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 394:
#line 1241 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefNoNum = 1;}
#line 4676 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 395:
#line 1242 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setMustjoin((yyvsp[-1].string)); }
#line 4682 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 396:
#line 1243 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1;}
#line 4688 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 397:
#line 1244 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setOutMargin((yyvsp[-2].dval), (yyvsp[-1].dval)); }
#line 4694 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 398:
#line 1245 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1;}
#line 4700 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 399:
#line 1246 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setOutResistance((yyvsp[-2].dval), (yyvsp[-1].dval)); }
#line 4706 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 400:
#line 1247 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1;}
#line 4712 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 401:
#line 1248 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setInMargin((yyvsp[-2].dval), (yyvsp[-1].dval)); }
#line 4718 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 402:
#line 1250 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setCapacitance((yyvsp[-1].dval)); }
#line 4724 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 403:
#line 1252 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setMaxdelay((yyvsp[-1].dval)); }
#line 4730 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 404:
#line 1254 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setMaxload((yyvsp[-1].dval)); }
#line 4736 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 405:
#line 1256 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setResistance((yyvsp[-1].dval)); }
#line 4742 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 406:
#line 1258 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setPulldownres((yyvsp[-1].dval)); }
#line 4748 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 407:
#line 1260 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setCurrentSource("ACTIVE"); }
#line 4754 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 408:
#line 1262 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setCurrentSource("RESISTIVE"); }
#line 4760 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 409:
#line 1264 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setRiseVoltage((yyvsp[-1].dval)); }
#line 4766 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 410:
#line 1266 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setFallVoltage((yyvsp[-1].dval)); }
#line 4772 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 411:
#line 1268 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setTables((yyvsp[-2].string), (yyvsp[-1].string)); }
#line 4778 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 412:
#line 1270 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setTaperRule((yyvsp[-1].string)); }
#line 4784 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 413:
#line 1271 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1000000;}
#line 4790 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 414:
#line 1272 "lef.y" /* yacc.c:1646  */
    { lefDumbMode = 0; }
#line 4796 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 415:
#line 1274 "lef.y" /* yacc.c:1646  */
    {
      lefDumbMode = 0;
      if (lefrPinCbk) {
	lefrPin.lefiPin::addPort(lefrGeometriesPtr);
	lefrGeometriesPtr = 0;
	lefrDoGeometries = 0;
      }
    }
#line 4809 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 416:
#line 1283 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::addAntennaSize((yyvsp[-2].dval), (yyvsp[-1].string)); }
#line 4815 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 417:
#line 1285 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::addAntennaMetalArea((yyvsp[-2].dval), (yyvsp[-1].string)); }
#line 4821 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 418:
#line 1287 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::addAntennaMetalLength((yyvsp[-2].dval), (yyvsp[-1].string)); }
#line 4827 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 419:
#line 1289 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setRiseSlewLimit((yyvsp[-1].dval)); }
#line 4833 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 420:
#line 1291 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setFallSlewLimit((yyvsp[-1].dval)); }
#line 4839 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 423:
#line 1302 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setNumProperty((yyvsp[-1].string), (yyvsp[0].dval)); }
#line 4845 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 424:
#line 1304 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setProperty((yyvsp[-1].string), (yyvsp[0].string)); }
#line 4851 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 425:
#line 1306 "lef.y" /* yacc.c:1646  */
    { if (lefrPinCbk) lefrPin.lefiPin::setProperty((yyvsp[-1].string), (yyvsp[0].string)); }
#line 4857 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 426:
#line 1310 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"INPUT";}
#line 4863 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 427:
#line 1311 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"OUTPUT";}
#line 4869 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 428:
#line 1312 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"OUTPUT TRISTATE";}
#line 4875 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 429:
#line 1313 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"INOUT";}
#line 4881 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 430:
#line 1314 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"FEEDTHRU";}
#line 4887 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 431:
#line 1318 "lef.y" /* yacc.c:1646  */
    {
      if (lefrPinCbk) {
	lefrDoGeometries = 1;
	lefrGeometriesPtr = (lefiGeometries*)malloc( sizeof(lefiGeometries));
	lefrGeometriesPtr->lefiGeometries::Init();
      }
    }
#line 4899 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 432:
#line 1328 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"SIGNAL";}
#line 4905 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 433:
#line 1329 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"ANALOG";}
#line 4911 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 434:
#line 1330 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"POWER";}
#line 4917 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 435:
#line 1331 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"GROUND";}
#line 4923 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 436:
#line 1332 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"CLOCK";}
#line 4929 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 437:
#line 1333 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"DATA";}
#line 4935 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 438:
#line 1337 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"INPUT";}
#line 4941 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 439:
#line 1338 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"OUTPUT";}
#line 4947 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 440:
#line 1339 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"START";}
#line 4953 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 441:
#line 1340 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"STOP";}
#line 4959 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 442:
#line 1344 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)""; }
#line 4965 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 443:
#line 1345 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"ABUTMENT";}
#line 4971 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 444:
#line 1346 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"RING";}
#line 4977 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 445:
#line 1347 "lef.y" /* yacc.c:1646  */
    {(yyval.string) = (char*)"FEEDTHRU";}
#line 4983 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 446:
#line 1351 "lef.y" /* yacc.c:1646  */
    { }
#line 4989 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 447:
#line 1352 "lef.y" /* yacc.c:1646  */
    { }
#line 4995 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 448:
#line 1356 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefNoNum = 1; }
#line 5001 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 449:
#line 1357 "lef.y" /* yacc.c:1646  */
    { if (lefrDoGeometries)
    lefrGeometriesPtr->lefiGeometries::addLayer((yyvsp[-1].string)); }
#line 5008 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 450:
#line 1360 "lef.y" /* yacc.c:1646  */
    { if (lefrDoGeometries)
    lefrGeometriesPtr->lefiGeometries::addWidth((yyvsp[-1].dval)); }
#line 5015 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 451:
#line 1363 "lef.y" /* yacc.c:1646  */
    { if (lefrDoGeometries) lefrGeometriesPtr->lefiGeometries::addPath(); }
#line 5021 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 452:
#line 1365 "lef.y" /* yacc.c:1646  */
    { if (lefrDoGeometries)
    lefrGeometriesPtr->lefiGeometries::addPathIter(); }
#line 5028 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 453:
#line 1368 "lef.y" /* yacc.c:1646  */
    { if (lefrDoGeometries) lefrGeometriesPtr->lefiGeometries::addRect((yyvsp[-2].pt).x,
    (yyvsp[-2].pt).y, (yyvsp[-1].pt).x, (yyvsp[-1].pt).y); }
#line 5035 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 454:
#line 1371 "lef.y" /* yacc.c:1646  */
    { if (lefrDoGeometries) lefrGeometriesPtr->lefiGeometries::addRectIter(
    (yyvsp[-3].pt).x, (yyvsp[-3].pt).y, (yyvsp[-2].pt).x, (yyvsp[-2].pt).y); }
#line 5042 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 455:
#line 1374 "lef.y" /* yacc.c:1646  */
    { if (lefrDoGeometries)
    lefrGeometriesPtr->lefiGeometries::addPolygon(); }
#line 5049 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 456:
#line 1377 "lef.y" /* yacc.c:1646  */
    { if (lefrDoGeometries)
    lefrGeometriesPtr->lefiGeometries::addPolygonIter(); }
#line 5056 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 457:
#line 1380 "lef.y" /* yacc.c:1646  */
    { }
#line 5062 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 458:
#line 1382 "lef.y" /* yacc.c:1646  */
    { if (lefrDoGeometries)
    lefrGeometriesPtr->lefiGeometries::addClass((yyvsp[-1].string)); }
#line 5069 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 459:
#line 1387 "lef.y" /* yacc.c:1646  */
    { if (lefrDoGeometries)
    lefrGeometriesPtr->lefiGeometries::startList((yyvsp[0].pt).x, (yyvsp[0].pt).y); }
#line 5076 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 460:
#line 1392 "lef.y" /* yacc.c:1646  */
    { if (lefrDoGeometries)
    lefrGeometriesPtr->lefiGeometries::addToList((yyvsp[0].pt).x, (yyvsp[0].pt).y); }
#line 5083 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 463:
#line 1402 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1;}
#line 5089 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 464:
#line 1403 "lef.y" /* yacc.c:1646  */
    { if (lefrDoGeometries)
    lefrGeometriesPtr->lefiGeometries::addVia((yyvsp[-3].pt).x, (yyvsp[-3].pt).y, (yyvsp[-1].string)); }
#line 5096 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 465:
#line 1405 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefNoNum = 1;}
#line 5102 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 466:
#line 1407 "lef.y" /* yacc.c:1646  */
    { if (lefrDoGeometries)
    lefrGeometriesPtr->lefiGeometries::addViaIter((yyvsp[-4].pt).x, (yyvsp[-4].pt).y, (yyvsp[-2].string)); }
#line 5109 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 467:
#line 1413 "lef.y" /* yacc.c:1646  */
    { if (lefrDoGeometries)
     lefrGeometriesPtr->lefiGeometries::addStepPattern((yyvsp[-5].dval), (yyvsp[-3].dval), (yyvsp[-1].dval), (yyvsp[0].dval)); }
#line 5116 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 468:
#line 1419 "lef.y" /* yacc.c:1646  */
    {
      if (lefrDoSite) {
	lefrSitePatternPtr = (lefiSitePattern*)malloc(
				   sizeof(lefiSitePattern));
	lefrSitePatternPtr->lefiSitePattern::Init();
	lefrSitePatternPtr->lefiSitePattern::set((yyvsp[-10].string), (yyvsp[-9].dval), (yyvsp[-8].dval), (yyvsp[-7].integer), (yyvsp[-5].dval), (yyvsp[-3].dval),
	  (yyvsp[-1].dval), (yyvsp[0].dval));
	}
    }
#line 5130 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 469:
#line 1432 "lef.y" /* yacc.c:1646  */
    { 
      if (lefrDoTrack) {
	lefrTrackPatternPtr = (lefiTrackPattern*)malloc(
				sizeof(lefiTrackPattern));
	lefrTrackPatternPtr->lefiTrackPattern::Init();
	lefrTrackPatternPtr->lefiTrackPattern::set("X", (yyvsp[-4].dval), (yyvsp[-2].dval), (yyvsp[0].dval));
      }    
    }
#line 5143 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 470:
#line 1440 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1000000000;}
#line 5149 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 471:
#line 1441 "lef.y" /* yacc.c:1646  */
    { lefDumbMode = 0;}
#line 5155 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 472:
#line 1443 "lef.y" /* yacc.c:1646  */
    { 
      if (lefrDoTrack) {
	lefrTrackPatternPtr = (lefiTrackPattern*)malloc(
                                    sizeof(lefiTrackPattern));
	lefrTrackPatternPtr->lefiTrackPattern::Init();
	lefrTrackPatternPtr->lefiTrackPattern::set("Y", (yyvsp[-4].dval), (yyvsp[-2].dval), (yyvsp[0].dval));
      }    
    }
#line 5168 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 473:
#line 1451 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1000000000;}
#line 5174 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 474:
#line 1452 "lef.y" /* yacc.c:1646  */
    { lefDumbMode = 0;}
#line 5180 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 475:
#line 1454 "lef.y" /* yacc.c:1646  */
    { 
      if (lefrDoTrack) {
	lefrTrackPatternPtr = (lefiTrackPattern*)malloc(
                                    sizeof(lefiTrackPattern));
	lefrTrackPatternPtr->lefiTrackPattern::Init();
	lefrTrackPatternPtr->lefiTrackPattern::set("X", (yyvsp[-4].dval), (yyvsp[-2].dval), (yyvsp[0].dval));
      }    
    }
#line 5193 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 476:
#line 1463 "lef.y" /* yacc.c:1646  */
    { 
      if (lefrDoTrack) {
	lefrTrackPatternPtr = (lefiTrackPattern*)malloc(
                                    sizeof(lefiTrackPattern));
	lefrTrackPatternPtr->lefiTrackPattern::Init();
	lefrTrackPatternPtr->lefiTrackPattern::set("Y", (yyvsp[-4].dval), (yyvsp[-2].dval), (yyvsp[0].dval));
      }    
    }
#line 5206 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 479:
#line 1479 "lef.y" /* yacc.c:1646  */
    { if (lefrDoTrack) lefrTrackPatternPtr->lefiTrackPattern::addLayer((yyvsp[0].string)); }
#line 5212 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 480:
#line 1483 "lef.y" /* yacc.c:1646  */
    {
      if (lefrDoGcell) {
	lefrGcellPatternPtr = (lefiGcellPattern*)malloc(
                                    sizeof(lefiGcellPattern));
	lefrGcellPatternPtr->lefiGcellPattern::Init();
	lefrGcellPatternPtr->lefiGcellPattern::set("X", (yyvsp[-4].dval), (yyvsp[-2].dval), (yyvsp[0].dval));
      }    
    }
#line 5225 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 481:
#line 1492 "lef.y" /* yacc.c:1646  */
    {
      if (lefrDoGcell) {
	lefrGcellPatternPtr = (lefiGcellPattern*)malloc(
                                    sizeof(lefiGcellPattern));
	lefrGcellPatternPtr->lefiGcellPattern::Init();
	lefrGcellPatternPtr->lefiGcellPattern::set("Y", (yyvsp[-4].dval), (yyvsp[-2].dval), (yyvsp[0].dval));
      }    
    }
#line 5238 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 482:
#line 1503 "lef.y" /* yacc.c:1646  */
    { 
      if (lefrObstructionCbk) {
	lefrObstruction.lefiObstruction::setGeometries(lefrGeometriesPtr);
	lefrGeometriesPtr = 0;
	lefrDoGeometries = 0;
      }
      CALLBACK(lefrObstructionCbk, lefrObstructionCbkType, &lefrObstruction);
      lefDumbMode = 0;
    }
#line 5252 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 483:
#line 1515 "lef.y" /* yacc.c:1646  */
    {
      obsDef = 1;
      if (lefrObstructionCbk) {
	lefrDoGeometries = 1;
	lefrGeometriesPtr = (lefiGeometries*)malloc(
	    sizeof(lefiGeometries));
	lefrGeometriesPtr->lefiGeometries::Init();
	}
    }
#line 5266 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 484:
#line 1526 "lef.y" /* yacc.c:1646  */
    { lefDumbMode = 1; lefNoNum = 1; }
#line 5272 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 485:
#line 1527 "lef.y" /* yacc.c:1646  */
    { if (lefrMacroCbk) lefrMacro.lefiMacro::setClockType((yyvsp[-1].string)); }
#line 5278 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 486:
#line 1531 "lef.y" /* yacc.c:1646  */
    { }
#line 5284 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 487:
#line 1535 "lef.y" /* yacc.c:1646  */
    { /* XXXXX for macros */ }
#line 5290 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 488:
#line 1539 "lef.y" /* yacc.c:1646  */
    {
    if (lefrTimingCbk && lefrTiming.lefiTiming::hasData())
      CALLBACK(lefrTimingCbk, lefrTimingCbkType, &lefrTiming);
    lefrTiming.lefiTiming::clear();
  }
#line 5300 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 491:
#line 1553 "lef.y" /* yacc.c:1646  */
    {
    if (lefrTimingCbk && lefrTiming.lefiTiming::hasData())
      CALLBACK(lefrTimingCbk, lefrTimingCbkType, &lefrTiming);
    lefDumbMode = 1000000000;
    lefrTiming.lefiTiming::clear();
    }
#line 5311 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 492:
#line 1560 "lef.y" /* yacc.c:1646  */
    { lefDumbMode = 0;}
#line 5317 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 493:
#line 1561 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1000000000;}
#line 5323 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 494:
#line 1562 "lef.y" /* yacc.c:1646  */
    { lefDumbMode = 0;}
#line 5329 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 495:
#line 1564 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::addRiseFall((yyvsp[-3].string),(yyvsp[-1].dval),(yyvsp[0].dval)); }
#line 5335 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 496:
#line 1566 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::addRiseFallVariable((yyvsp[-2].dval),(yyvsp[-1].dval)); }
#line 5341 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 497:
#line 1569 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) {
	if ((yyvsp[-7].string)[0] == 'D' || (yyvsp[-7].string)[0] == 'd') /* delay */
	  lefrTiming.lefiTiming::addDelay((yyvsp[-8].string), (yyvsp[-5].string), (yyvsp[-3].dval), (yyvsp[-2].dval), (yyvsp[-1].dval));
	else
	  lefrTiming.lefiTiming::addTransition((yyvsp[-8].string), (yyvsp[-5].string), (yyvsp[-3].dval), (yyvsp[-2].dval), (yyvsp[-1].dval));
	}
    }
#line 5353 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 498:
#line 1577 "lef.y" /* yacc.c:1646  */
    { }
#line 5359 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 499:
#line 1579 "lef.y" /* yacc.c:1646  */
    { }
#line 5365 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 500:
#line 1581 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::setRiseRS((yyvsp[-2].dval),(yyvsp[-1].dval)); }
#line 5371 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 501:
#line 1583 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::setFallRS((yyvsp[-2].dval),(yyvsp[-1].dval)); }
#line 5377 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 502:
#line 1585 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::setRiseCS((yyvsp[-2].dval),(yyvsp[-1].dval)); }
#line 5383 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 503:
#line 1587 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::setFallCS((yyvsp[-2].dval),(yyvsp[-1].dval)); }
#line 5389 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 504:
#line 1589 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::setRiseAtt1((yyvsp[-2].dval),(yyvsp[-1].dval)); }
#line 5395 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 505:
#line 1591 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::setFallAtt1((yyvsp[-2].dval),(yyvsp[-1].dval)); }
#line 5401 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 506:
#line 1593 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::setRiseTo((yyvsp[-2].dval),(yyvsp[-1].dval)); }
#line 5407 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 507:
#line 1595 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::setFallTo((yyvsp[-2].dval),(yyvsp[-1].dval)); }
#line 5413 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 508:
#line 1597 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::addUnateness((yyvsp[-1].string)); }
#line 5419 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 509:
#line 1599 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::setStable((yyvsp[-4].dval),(yyvsp[-2].dval),(yyvsp[-1].string)); }
#line 5425 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 510:
#line 1601 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::addSDF2Pins((yyvsp[-7].string),(yyvsp[-6].string),(yyvsp[-5].string),(yyvsp[-3].dval),(yyvsp[-2].dval),(yyvsp[-1].dval)); }
#line 5431 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 511:
#line 1603 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::addSDF1Pin((yyvsp[-5].string),(yyvsp[-3].dval),(yyvsp[-2].dval),(yyvsp[-2].dval)); }
#line 5437 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 512:
#line 1605 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::setSDFcondStart((yyvsp[-1].string)); }
#line 5443 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 513:
#line 1607 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::setSDFcondEnd((yyvsp[-1].string)); }
#line 5449 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 514:
#line 1609 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::setSDFcond((yyvsp[-1].string)); }
#line 5455 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 515:
#line 1611 "lef.y" /* yacc.c:1646  */
    { /* XXXXX */ }
#line 5461 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 516:
#line 1616 "lef.y" /* yacc.c:1646  */
    { (yyval.string) = (char*)"MPWH";}
#line 5467 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 517:
#line 1618 "lef.y" /* yacc.c:1646  */
    { (yyval.string) = (char*)"MPWL";}
#line 5473 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 518:
#line 1620 "lef.y" /* yacc.c:1646  */
    { (yyval.string) = (char*)"PERIOD";}
#line 5479 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 519:
#line 1625 "lef.y" /* yacc.c:1646  */
    { (yyval.string) = (char*)"SETUP";}
#line 5485 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 520:
#line 1627 "lef.y" /* yacc.c:1646  */
    { (yyval.string) = (char*)"HOLD";}
#line 5491 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 521:
#line 1629 "lef.y" /* yacc.c:1646  */
    { (yyval.string) = (char*)"RECOVERY";}
#line 5497 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 522:
#line 1631 "lef.y" /* yacc.c:1646  */
    { (yyval.string) = (char*)"SKEW";}
#line 5503 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 523:
#line 1636 "lef.y" /* yacc.c:1646  */
    { (yyval.string) = (char*)"ANYEDGE";}
#line 5509 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 524:
#line 1638 "lef.y" /* yacc.c:1646  */
    { (yyval.string) = (char*)"POSEDGE";}
#line 5515 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 525:
#line 1640 "lef.y" /* yacc.c:1646  */
    { (yyval.string) = (char*)"NEGEDGE";}
#line 5521 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 526:
#line 1645 "lef.y" /* yacc.c:1646  */
    { (yyval.string) = (char*)"ANYEDGE";}
#line 5527 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 527:
#line 1647 "lef.y" /* yacc.c:1646  */
    { (yyval.string) = (char*)"POSEDGE";}
#line 5533 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 528:
#line 1649 "lef.y" /* yacc.c:1646  */
    { (yyval.string) = (char*)"NEGEDGE";}
#line 5539 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 529:
#line 1654 "lef.y" /* yacc.c:1646  */
    { (yyval.string) = (char*)"DELAY"; }
#line 5545 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 530:
#line 1656 "lef.y" /* yacc.c:1646  */
    { (yyval.string) = (char*)"TRANSITION"; }
#line 5551 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 531:
#line 1661 "lef.y" /* yacc.c:1646  */
    { }
#line 5557 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 532:
#line 1663 "lef.y" /* yacc.c:1646  */
    { }
#line 5563 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 533:
#line 1667 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::addTableEntry((yyvsp[-3].dval),(yyvsp[-2].dval),(yyvsp[-1].dval)); }
#line 5569 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 534:
#line 1672 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::addTableAxisNumber((yyvsp[0].dval)); }
#line 5575 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 535:
#line 1674 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::addTableAxisNumber((yyvsp[0].dval)); }
#line 5581 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 536:
#line 1679 "lef.y" /* yacc.c:1646  */
    { }
#line 5587 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 537:
#line 1681 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::addRiseFallSlew((yyvsp[-3].dval),(yyvsp[-2].dval),(yyvsp[-1].dval),(yyvsp[0].dval)); }
#line 5593 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 538:
#line 1683 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::addRiseFallSlew((yyvsp[-6].dval),(yyvsp[-5].dval),(yyvsp[-4].dval),(yyvsp[-3].dval));
      if (lefrTimingCbk) lefrTiming.lefiTiming::addRiseFallSlew2((yyvsp[-2].dval),(yyvsp[-1].dval),(yyvsp[0].dval)); }
#line 5600 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 539:
#line 1689 "lef.y" /* yacc.c:1646  */
    { (yyval.string) = (char*)"RISE"; }
#line 5606 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 540:
#line 1691 "lef.y" /* yacc.c:1646  */
    { (yyval.string) = (char*)"FALL"; }
#line 5612 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 541:
#line 1696 "lef.y" /* yacc.c:1646  */
    { (yyval.string) = (char*)"INVERT"; }
#line 5618 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 542:
#line 1698 "lef.y" /* yacc.c:1646  */
    { (yyval.string) = (char*)"NONINVERT"; }
#line 5624 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 543:
#line 1700 "lef.y" /* yacc.c:1646  */
    { (yyval.string) = (char*)"NONUNATE"; }
#line 5630 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 544:
#line 1705 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::addFromPin((yyvsp[0].string)); }
#line 5636 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 545:
#line 1707 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::addFromPin((yyvsp[0].string)); }
#line 5642 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 546:
#line 1712 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::addToPin((yyvsp[0].string)); }
#line 5648 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 547:
#line 1714 "lef.y" /* yacc.c:1646  */
    { if (lefrTimingCbk) lefrTiming.lefiTiming::addToPin((yyvsp[0].string)); }
#line 5654 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 548:
#line 1718 "lef.y" /* yacc.c:1646  */
    {
	CALLBACK(lefrArrayCbk, lefrArrayCbkType, &lefrArray);
	lefrArray.lefiArray::clear();
	lefrSitePatternPtr = 0;
	lefrDoSite = 0;
    }
#line 5665 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 550:
#line 1727 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefNoNum = 1;}
#line 5671 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 551:
#line 1728 "lef.y" /* yacc.c:1646  */
    {
      if (lefrArrayCbk) {
	lefrArray.lefiArray::setName((yyvsp[0].string));
	CALLBACK(lefrArrayBeginCbk, lefrArrayBeginCbkType, (yyvsp[0].string));
      }
    }
#line 5682 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 552:
#line 1736 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefNoNum = 1;}
#line 5688 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 553:
#line 1737 "lef.y" /* yacc.c:1646  */
    {
      if (lefrArrayCbk)
	CALLBACK(lefrArrayEndCbk, lefrArrayEndCbkType, (yyvsp[0].string));
    }
#line 5697 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 554:
#line 1745 "lef.y" /* yacc.c:1646  */
    { }
#line 5703 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 555:
#line 1747 "lef.y" /* yacc.c:1646  */
    { }
#line 5709 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 556:
#line 1751 "lef.y" /* yacc.c:1646  */
    { if (lefrArrayCbk) lefrDoSite = 1; lefDumbMode = 1; }
#line 5715 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 557:
#line 1753 "lef.y" /* yacc.c:1646  */
    {
      if (lefrArrayCbk) {
	lefrArray.lefiArray::addSitePattern(lefrSitePatternPtr);
      }
    }
#line 5725 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 558:
#line 1758 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; if (lefrArrayCbk) lefrDoSite = 1; }
#line 5731 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 559:
#line 1760 "lef.y" /* yacc.c:1646  */
    {
      if (lefrArrayCbk) {
	lefrArray.lefiArray::addCanPlace(lefrSitePatternPtr);
      }
    }
#line 5741 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 560:
#line 1765 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; if (lefrArrayCbk) lefrDoSite = 1; }
#line 5747 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 561:
#line 1767 "lef.y" /* yacc.c:1646  */
    {
      if (lefrArrayCbk) {
	lefrArray.lefiArray::addCannotOccupy(lefrSitePatternPtr);
      }
    }
#line 5757 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 562:
#line 1772 "lef.y" /* yacc.c:1646  */
    { if (lefrArrayCbk) lefrDoTrack = 1; }
#line 5763 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 563:
#line 1773 "lef.y" /* yacc.c:1646  */
    {
      if (lefrArrayCbk) {
	lefrArray.lefiArray::addTrack(lefrTrackPatternPtr);
      }
    }
#line 5773 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 564:
#line 1779 "lef.y" /* yacc.c:1646  */
    {
    }
#line 5780 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 565:
#line 1781 "lef.y" /* yacc.c:1646  */
    { if (lefrArrayCbk) lefrDoGcell = 1; }
#line 5786 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 566:
#line 1782 "lef.y" /* yacc.c:1646  */
    {
      if (lefrArrayCbk) {
	lefrArray.lefiArray::addGcell(lefrGcellPatternPtr);
      }
    }
#line 5796 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 567:
#line 1788 "lef.y" /* yacc.c:1646  */
    {
      if (lefrArrayCbk) {
	lefrArray.lefiArray::setTableSize((yyvsp[-3].dval));
      }
    }
#line 5806 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 568:
#line 1794 "lef.y" /* yacc.c:1646  */
    { }
#line 5812 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 569:
#line 1798 "lef.y" /* yacc.c:1646  */
    { if (lefrArrayCbk) lefrArray.lefiArray::addFloorPlan((yyvsp[0].string)); }
#line 5818 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 570:
#line 1803 "lef.y" /* yacc.c:1646  */
    { }
#line 5824 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 571:
#line 1805 "lef.y" /* yacc.c:1646  */
    { }
#line 5830 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 572:
#line 1809 "lef.y" /* yacc.c:1646  */
    { lefDumbMode = 1; if (lefrArrayCbk) lefrDoSite = 1; }
#line 5836 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 573:
#line 1811 "lef.y" /* yacc.c:1646  */
    {
      if (lefrArrayCbk)
	lefrArray.lefiArray::addSiteToFloorPlan("CANPLACE",
	lefrSitePatternPtr);
    }
#line 5846 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 574:
#line 1816 "lef.y" /* yacc.c:1646  */
    { if (lefrArrayCbk) lefrDoSite = 1; lefDumbMode = 1; }
#line 5852 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 575:
#line 1818 "lef.y" /* yacc.c:1646  */
    {
      if (lefrArrayCbk)
	lefrArray.lefiArray::addSiteToFloorPlan("CANNOTOCCUPY",
	lefrSitePatternPtr);
     }
#line 5862 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 576:
#line 1827 "lef.y" /* yacc.c:1646  */
    { }
#line 5868 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 577:
#line 1829 "lef.y" /* yacc.c:1646  */
    { }
#line 5874 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 578:
#line 1833 "lef.y" /* yacc.c:1646  */
    { if (lefrArrayCbk) lefrArray.lefiArray::addDefaultCap((yyvsp[-3].dval), (yyvsp[-1].dval)); }
#line 5880 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 579:
#line 1837 "lef.y" /* yacc.c:1646  */
    {lefDumbMode=1;lefNlToken=TRUE;}
#line 5886 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 580:
#line 1838 "lef.y" /* yacc.c:1646  */
    { lefAddStringMessage((yyvsp[-3].string), (yyvsp[-1].string)); }
#line 5892 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 581:
#line 1842 "lef.y" /* yacc.c:1646  */
    {lefDumbMode=1;lefNlToken=TRUE;}
#line 5898 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 582:
#line 1843 "lef.y" /* yacc.c:1646  */
    { }
#line 5904 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 583:
#line 1847 "lef.y" /* yacc.c:1646  */
    {lefDumbMode=1;lefNlToken=TRUE;}
#line 5910 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 584:
#line 1848 "lef.y" /* yacc.c:1646  */
    { lefAddNumDefine((yyvsp[-3].string), (yyvsp[-1].dval)); }
#line 5916 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 585:
#line 1849 "lef.y" /* yacc.c:1646  */
    {lefDumbMode=1;lefNlToken=TRUE;}
#line 5922 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 586:
#line 1850 "lef.y" /* yacc.c:1646  */
    { lefAddStringDefine((yyvsp[-3].string), (yyvsp[-1].string)); }
#line 5928 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 587:
#line 1851 "lef.y" /* yacc.c:1646  */
    {lefDumbMode=1;lefNlToken=TRUE;}
#line 5934 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 588:
#line 1852 "lef.y" /* yacc.c:1646  */
    { lefAddBooleanDefine((yyvsp[-3].string), (yyvsp[-1].integer)); }
#line 5940 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 590:
#line 1857 "lef.y" /* yacc.c:1646  */
    {lefNlToken = FALSE;}
#line 5946 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 591:
#line 1858 "lef.y" /* yacc.c:1646  */
    {lefNlToken = FALSE;}
#line 5952 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 596:
#line 1872 "lef.y" /* yacc.c:1646  */
    {(yyval.dval) = (yyvsp[-2].dval) + (yyvsp[0].dval); }
#line 5958 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 597:
#line 1873 "lef.y" /* yacc.c:1646  */
    {(yyval.dval) = (yyvsp[-2].dval) - (yyvsp[0].dval); }
#line 5964 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 598:
#line 1874 "lef.y" /* yacc.c:1646  */
    {(yyval.dval) = (yyvsp[-2].dval) * (yyvsp[0].dval); }
#line 5970 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 599:
#line 1875 "lef.y" /* yacc.c:1646  */
    {(yyval.dval) = (yyvsp[-2].dval) / (yyvsp[0].dval); }
#line 5976 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 600:
#line 1876 "lef.y" /* yacc.c:1646  */
    {(yyval.dval) = -(yyvsp[0].dval);}
#line 5982 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 601:
#line 1877 "lef.y" /* yacc.c:1646  */
    {(yyval.dval) = (yyvsp[-1].dval);}
#line 5988 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 602:
#line 1879 "lef.y" /* yacc.c:1646  */
    {(yyval.dval) = ((yyvsp[-4].integer) != 0) ? (yyvsp[-2].dval) : (yyvsp[0].dval);}
#line 5994 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 603:
#line 1880 "lef.y" /* yacc.c:1646  */
    {(yyval.dval) = (yyvsp[0].dval);}
#line 6000 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 604:
#line 1884 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = comp_num((yyvsp[-2].dval),(yyvsp[-1].integer),(yyvsp[0].dval));}
#line 6006 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 605:
#line 1885 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = (yyvsp[-2].dval) != 0 && (yyvsp[0].dval) != 0;}
#line 6012 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 606:
#line 1886 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = (yyvsp[-2].dval) != 0 || (yyvsp[0].dval) != 0;}
#line 6018 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 607:
#line 1887 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = comp_str((yyvsp[-2].string),(yyvsp[-1].integer),(yyvsp[0].string));}
#line 6024 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 608:
#line 1888 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = (yyvsp[-2].string)[0] != 0 && (yyvsp[0].string)[0] != 0;}
#line 6030 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 609:
#line 1889 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = (yyvsp[-2].string)[0] != 0 || (yyvsp[0].string)[0] != 0;}
#line 6036 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 610:
#line 1890 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = (yyvsp[-2].integer) == (yyvsp[0].integer);}
#line 6042 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 611:
#line 1891 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = (yyvsp[-2].integer) != (yyvsp[0].integer);}
#line 6048 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 612:
#line 1892 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = (yyvsp[-2].integer) && (yyvsp[0].integer);}
#line 6054 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 613:
#line 1893 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = (yyvsp[-2].integer) || (yyvsp[0].integer);}
#line 6060 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 614:
#line 1894 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = !(yyval.integer);}
#line 6066 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 615:
#line 1895 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = (yyvsp[-1].integer);}
#line 6072 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 616:
#line 1897 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = ((yyvsp[-4].integer) != 0) ? (yyvsp[-2].integer) : (yyvsp[0].integer);}
#line 6078 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 617:
#line 1898 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = 1;}
#line 6084 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 618:
#line 1899 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = 0;}
#line 6090 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 619:
#line 1904 "lef.y" /* yacc.c:1646  */
    {
      (yyval.string) = (char*)malloc(strlen((yyvsp[-2].string))+strlen((yyvsp[0].string))+1);
      strcpy((yyval.string),(yyvsp[-2].string));
      strcat((yyval.string),(yyvsp[0].string));
    }
#line 6100 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 620:
#line 1910 "lef.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[-1].string); }
#line 6106 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 621:
#line 1912 "lef.y" /* yacc.c:1646  */
    {
      lefDefIf = TRUE;
      if ((yyvsp[-4].integer) != 0) {
	(yyval.string) = (yyvsp[-2].string);	
      } else {
	(yyval.string) = (yyvsp[0].string);
      }
    }
#line 6119 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 622:
#line 1921 "lef.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 6125 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 623:
#line 1925 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = C_LE;}
#line 6131 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 624:
#line 1926 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = C_LT;}
#line 6137 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 625:
#line 1927 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = C_GE;}
#line 6143 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 626:
#line 1928 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = C_GT;}
#line 6149 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 627:
#line 1929 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = C_EQ;}
#line 6155 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 628:
#line 1930 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = C_NE;}
#line 6161 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 629:
#line 1931 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = C_EQ;}
#line 6167 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 630:
#line 1932 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = C_LT;}
#line 6173 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 631:
#line 1933 "lef.y" /* yacc.c:1646  */
    {(yyval.integer) = C_GT;}
#line 6179 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 632:
#line 1938 "lef.y" /* yacc.c:1646  */
    { CALLBACK(lefrPropBeginCbk, lefrPropBeginCbkType, 0); }
#line 6185 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 633:
#line 1940 "lef.y" /* yacc.c:1646  */
    { CALLBACK(lefrPropEndCbk, lefrPropEndCbkType, 0); }
#line 6191 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 634:
#line 1945 "lef.y" /* yacc.c:1646  */
    { }
#line 6197 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 635:
#line 1947 "lef.y" /* yacc.c:1646  */
    { }
#line 6203 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 636:
#line 1951 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefrProp.lefiProp::clear(); }
#line 6209 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 637:
#line 1953 "lef.y" /* yacc.c:1646  */
    { 
      if (lefrPropCbk) lefrProp.lefiProp::setPropType("library", (yyvsp[-2].string));
      CALLBACK(lefrPropCbk, lefrPropCbkType, &lefrProp);
    }
#line 6218 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 638:
#line 1957 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefrProp.lefiProp::clear(); }
#line 6224 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 639:
#line 1959 "lef.y" /* yacc.c:1646  */
    { 
      if (lefrPropCbk) lefrProp.lefiProp::setPropType("componentpin", (yyvsp[-2].string));
      CALLBACK(lefrPropCbk, lefrPropCbkType, &lefrProp);
    }
#line 6233 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 640:
#line 1963 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefrProp.lefiProp::clear(); }
#line 6239 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 641:
#line 1965 "lef.y" /* yacc.c:1646  */
    { 
      if (lefrPropCbk) lefrProp.lefiProp::setPropType("pin", (yyvsp[-2].string));
      CALLBACK(lefrPropCbk, lefrPropCbkType, &lefrProp);
    }
#line 6248 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 642:
#line 1969 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefrProp.lefiProp::clear(); }
#line 6254 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 643:
#line 1971 "lef.y" /* yacc.c:1646  */
    { 
      if (lefrPropCbk) lefrProp.lefiProp::setPropType("macro", (yyvsp[-2].string));
      CALLBACK(lefrPropCbk, lefrPropCbkType, &lefrProp);
    }
#line 6263 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 644:
#line 1975 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefrProp.lefiProp::clear(); }
#line 6269 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 645:
#line 1977 "lef.y" /* yacc.c:1646  */
    { 
      if (lefrPropCbk) lefrProp.lefiProp::setPropType("via", (yyvsp[-2].string));
      CALLBACK(lefrPropCbk, lefrPropCbkType, &lefrProp);
    }
#line 6278 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 646:
#line 1981 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefrProp.lefiProp::clear(); }
#line 6284 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 647:
#line 1983 "lef.y" /* yacc.c:1646  */
    { 
      if (lefrPropCbk) lefrProp.lefiProp::setPropType("viarule", (yyvsp[-2].string));
      CALLBACK(lefrPropCbk, lefrPropCbkType, &lefrProp);
    }
#line 6293 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 648:
#line 1987 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefrProp.lefiProp::clear(); }
#line 6299 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 649:
#line 1989 "lef.y" /* yacc.c:1646  */
    { 
      if (lefrPropCbk) lefrProp.lefiProp::setPropType("layer", (yyvsp[-2].string));
      CALLBACK(lefrPropCbk, lefrPropCbkType, &lefrProp);
    }
#line 6308 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 650:
#line 1993 "lef.y" /* yacc.c:1646  */
    {lefDumbMode = 1; lefrProp.lefiProp::clear(); }
#line 6314 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 651:
#line 1995 "lef.y" /* yacc.c:1646  */
    { 
      if (lefrPropCbk) lefrProp.lefiProp::setPropType("nondefaultrule", (yyvsp[-2].string));
      CALLBACK(lefrPropCbk, lefrPropCbkType, &lefrProp);
    }
#line 6323 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 652:
#line 2003 "lef.y" /* yacc.c:1646  */
    { if (lefrPropCbk) lefrProp.lefiProp::setPropInteger(); }
#line 6329 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 653:
#line 2005 "lef.y" /* yacc.c:1646  */
    { if (lefrPropCbk) lefrProp.lefiProp::setPropReal(); }
#line 6335 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 654:
#line 2007 "lef.y" /* yacc.c:1646  */
    { if (lefrPropCbk) lefrProp.lefiProp::setPropString(); }
#line 6341 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 655:
#line 2009 "lef.y" /* yacc.c:1646  */
    { if (lefrPropCbk) lefrProp.lefiProp::setPropQString((yyvsp[0].string)); }
#line 6347 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 656:
#line 2011 "lef.y" /* yacc.c:1646  */
    { if (lefrPropCbk) lefrProp.lefiProp::setPropNameMapString((yyvsp[0].string)); }
#line 6353 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 657:
#line 2016 "lef.y" /* yacc.c:1646  */
    { (yyval.pt).x = -1; (yyval.pt).y = -1; }
#line 6359 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 658:
#line 2018 "lef.y" /* yacc.c:1646  */
    { (yyval.pt).x = (yyvsp[-2].dval); (yyval.pt).y = (yyvsp[-1].dval); useLenThr = 1; }
#line 6365 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 659:
#line 2020 "lef.y" /* yacc.c:1646  */
    { (yyval.pt).x = (yyvsp[-1].dval); (yyval.pt).y = (yyvsp[0].dval); }
#line 6371 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 660:
#line 2022 "lef.y" /* yacc.c:1646  */
    { (yyval.pt).x = (yyvsp[0].dval); (yyval.pt).y = -1; lenThr = 1; }
#line 6377 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 661:
#line 2027 "lef.y" /* yacc.c:1646  */
    { }
#line 6383 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 662:
#line 2029 "lef.y" /* yacc.c:1646  */
    { lefrProp.lefiProp::setRange((yyvsp[-1].dval), (yyvsp[0].dval)); }
#line 6389 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 663:
#line 2034 "lef.y" /* yacc.c:1646  */
    { }
#line 6395 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 664:
#line 2036 "lef.y" /* yacc.c:1646  */
    { if (lefrPropCbk) lefrProp.lefiProp::setNumber((yyvsp[0].dval)); }
#line 6401 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 665:
#line 2041 "lef.y" /* yacc.c:1646  */
    { (yyval.string) = 0; }
#line 6407 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 666:
#line 2043 "lef.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 6413 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 667:
#line 2047 "lef.y" /* yacc.c:1646  */
    {
      if (lefrNoiseMarginCbk) {
        lefrNoiseMargin.low = (yyvsp[-2].dval);
        lefrNoiseMargin.high = (yyvsp[-1].dval);
      }
      CALLBACK(lefrNoiseMarginCbk, lefrNoiseMarginCbkType, &lefrNoiseMargin);
    }
#line 6425 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 668:
#line 2057 "lef.y" /* yacc.c:1646  */
    {
      if (lefrEdgeRateThreshold1Cbk) {
	CALLBACK(lefrEdgeRateThreshold1Cbk,
	lefrEdgeRateThreshold1CbkType, (yyvsp[-1].dval));
      }
    }
#line 6436 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 669:
#line 2066 "lef.y" /* yacc.c:1646  */
    {
      if (lefrEdgeRateThreshold2Cbk) {
	CALLBACK(lefrEdgeRateThreshold2Cbk,
	lefrEdgeRateThreshold2CbkType, (yyvsp[-1].dval));
      }
    }
#line 6447 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 670:
#line 2075 "lef.y" /* yacc.c:1646  */
    {
      if (lefrEdgeRateScaleFactorCbk) {
	CALLBACK(lefrEdgeRateScaleFactorCbk,
	lefrEdgeRateScaleFactorCbkType, (yyvsp[-1].dval));
      }
    }
#line 6458 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 671:
#line 2084 "lef.y" /* yacc.c:1646  */
    { if (lefrNoiseTableCbk) lefrNoiseTable.lefiNoiseTable::setup((yyvsp[0].dval)); }
#line 6464 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 672:
#line 2086 "lef.y" /* yacc.c:1646  */
    { CALLBACK(lefrNoiseTableCbk, lefrNoiseTableCbkType, &lefrNoiseTable); }
#line 6470 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 675:
#line 2096 "lef.y" /* yacc.c:1646  */
    { if (lefrNoiseTableCbk)
         {
            lefrNoiseTable.lefiNoiseTable::newEdge();
            lefrNoiseTable.lefiNoiseTable::addEdge((yyvsp[-1].dval));
         }
    }
#line 6481 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 676:
#line 2103 "lef.y" /* yacc.c:1646  */
    { }
#line 6487 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 677:
#line 2107 "lef.y" /* yacc.c:1646  */
    { if (lefrNoiseTableCbk) lefrNoiseTable.lefiNoiseTable::addResistance(); }
#line 6493 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 679:
#line 2113 "lef.y" /* yacc.c:1646  */
    { if (lefrNoiseTableCbk)
    lefrNoiseTable.lefiNoiseTable::addResistanceNumber((yyvsp[0].dval)); }
#line 6500 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 680:
#line 2116 "lef.y" /* yacc.c:1646  */
    { if (lefrNoiseTableCbk)
    lefrNoiseTable.lefiNoiseTable::addResistanceNumber((yyvsp[0].dval)); }
#line 6507 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 683:
#line 2126 "lef.y" /* yacc.c:1646  */
    { if (lefrNoiseTableCbk)
	lefrNoiseTable.lefiNoiseTable::addVictimLength((yyvsp[-1].dval)); }
#line 6514 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 684:
#line 2129 "lef.y" /* yacc.c:1646  */
    { }
#line 6520 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 685:
#line 2134 "lef.y" /* yacc.c:1646  */
    { if (lefrNoiseTableCbk)
    lefrNoiseTable.lefiNoiseTable::addVictimNoise((yyvsp[0].dval)); }
#line 6527 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 686:
#line 2137 "lef.y" /* yacc.c:1646  */
    { if (lefrNoiseTableCbk)
    lefrNoiseTable.lefiNoiseTable::addVictimNoise((yyvsp[0].dval)); }
#line 6534 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 687:
#line 2142 "lef.y" /* yacc.c:1646  */
    { if (lefrCorrectionTableCbk)
    lefrCorrectionTable.lefiCorrectionTable::setup((yyvsp[-1].dval)); }
#line 6541 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 688:
#line 2145 "lef.y" /* yacc.c:1646  */
    { CALLBACK(lefrCorrectionTableCbk,
    lefrCorrectionTableCbkType, &lefrCorrectionTable); }
#line 6548 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 691:
#line 2156 "lef.y" /* yacc.c:1646  */
    { if (lefrCorrectionTableCbk)
         {
            lefrCorrectionTable.lefiCorrectionTable::newEdge();
            lefrCorrectionTable.lefiCorrectionTable::addEdge((yyvsp[-1].dval));
         }
    }
#line 6559 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 692:
#line 2163 "lef.y" /* yacc.c:1646  */
    { }
#line 6565 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 693:
#line 2167 "lef.y" /* yacc.c:1646  */
    { if (lefrCorrectionTableCbk)
  lefrCorrectionTable.lefiCorrectionTable::addResistance(); }
#line 6572 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 694:
#line 2170 "lef.y" /* yacc.c:1646  */
    { }
#line 6578 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 695:
#line 2175 "lef.y" /* yacc.c:1646  */
    { if (lefrCorrectionTableCbk)
    lefrCorrectionTable.lefiCorrectionTable::addResistanceNumber((yyvsp[0].dval)); }
#line 6585 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 696:
#line 2178 "lef.y" /* yacc.c:1646  */
    { if (lefrCorrectionTableCbk)
    lefrCorrectionTable.lefiCorrectionTable::addResistanceNumber((yyvsp[0].dval)); }
#line 6592 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 699:
#line 2189 "lef.y" /* yacc.c:1646  */
    { if (lefrCorrectionTableCbk)
     lefrCorrectionTable.lefiCorrectionTable::addVictimLength((yyvsp[-1].dval)); }
#line 6599 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 700:
#line 2192 "lef.y" /* yacc.c:1646  */
    { }
#line 6605 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 701:
#line 2197 "lef.y" /* yacc.c:1646  */
    { if (lefrCorrectionTableCbk)
	lefrCorrectionTable.lefiCorrectionTable::addVictimCorrection((yyvsp[0].dval)); }
#line 6612 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 702:
#line 2200 "lef.y" /* yacc.c:1646  */
    { if (lefrCorrectionTableCbk)
	lefrCorrectionTable.lefiCorrectionTable::addVictimCorrection((yyvsp[0].dval)); }
#line 6619 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 703:
#line 2205 "lef.y" /* yacc.c:1646  */
    { CALLBACK(lefrInputAntennaCbk, lefrInputAntennaCbkType, (yyvsp[-1].dval)); }
#line 6625 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 704:
#line 2209 "lef.y" /* yacc.c:1646  */
    { CALLBACK(lefrOutputAntennaCbk, lefrOutputAntennaCbkType, (yyvsp[-1].dval)); }
#line 6631 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 705:
#line 2213 "lef.y" /* yacc.c:1646  */
    { CALLBACK(lefrInoutAntennaCbk, lefrInoutAntennaCbkType, (yyvsp[-1].dval)); }
#line 6637 "lef.tab.c" /* yacc.c:1646  */
    break;

  case 706:
#line 2217 "lef.y" /* yacc.c:1646  */
    { }
#line 6643 "lef.tab.c" /* yacc.c:1646  */
    break;


#line 6647 "lef.tab.c" /* yacc.c:1646  */
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 2220 "lef.y" /* yacc.c:1906  */

