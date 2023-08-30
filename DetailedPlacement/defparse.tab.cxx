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
#define yyparse         defparse
#define yylex           deflex
#define yyerror         deferror
#define yydebug         defdebug
#define yynerrs         defnerrs

#define yylval          deflval
#define yychar          defchar

/* Copy the first part of user declarations.  */
#line 1 "defparse.y" /* yacc.c:339  */

#ifdef _MSC_VER
#pragma warning (disable:4786)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
//#include <malloc.h>
#include "plGeom.h"
#include "LEFDEFpoint.h"
typedef struct lexsstr
    {
    char *str;
    int  DoDelete;
    } lexemeStruct;

#include "DB.h"
#include "parserLEFDEF.h"
//#include "hash.h"
#include "localhash.h"
#include "sgi_hash_map.h"

using std::pair;
using std::vector;

void deferror (const char *s) ;
int lefparse(void);
int deflex(void);
//CellHashTable *pCellTable;
//NetHashTable  *pNetTable, *pSNetTable;
//MasterCellHashTable *pMasterTable;
//dbPinRec            *firstPinGlobalList=NULL;
//dbPinRec            *lastPinGlobalList=NULL;
int nNets;
int nNetsSoFar=0;
int nSNets;
int nSNetsSoFar=0;
int bInSNets;  //are we in the "special" nets section?
static char *tempstr;
//dbTimeNetRec *netPtr;
//dbTimeCellRec *tempCellPtr;
//dbTimeNetlistRec *pNetlist;
//dbWrapper *pWrapperPtr;
//dbUnits   *pUnitsPtr;
//dbPinRec  *oldPinPtr;
int runningPinIdx;
int nPinsThisNet;
int nCellsThisNet;
double lastX,lastY;
//enum {CHANGE_IN_X,CHANGE_IN_Y,DEFAULT_CHANGE} lastChange=DEFAULT_CHANGE;
dbLayer::Dir pathDirection,oldPathDirection;
int tempArea;
extern int defLinenum;
static char errtxt[1023];
int mikesMain(int argc,char **argv);
//section for variables from parseArgs
extern int lefdebug;
extern FILE *lefin, *defin;
int nIOsThisNet;
int nOUTThisNet;
bool bSpecial;

extern DB           *pdb;
extern ParserLEFDEF *pp;

//globals for dbCell ctor and other comps section info
static char               tempCellName[1023];
static dbMasterCell      *pTempMaster;
static ctainerPinsLocal   tempPins;
//static ctainerPinsLocal   emptyPins;
static dbCell            *pTempCell;
static LEFDEFpoint        tempLoc;
static bool               tempLocValid;
static bool               tempFixed;
static Orient             tempOrient;
//end dbCell globals

//globals for regions
static parserRegion* pTempRegion;
static unsigned runParRegIdx=0;
//end globals for regions

//globals for dbPin ctor
static dbPin             *pTempPin;
//end dbPin globals

//globals for dbNet ctor
static char              tempNetName[1023];
static dbNetType::NetUse tempNetUse;
static int               runningNetIdx=0;
static int               runningSNetIdx=0;
static dbNet            *pTempNet;
static char              tempPinName[1023];
static ctainerLayerGeoms tempWiring; //for special nets only
static bool              logicalPinReferenced;
//end dbNet globals

//globals for external pins
static dbMasterPin *pTempMasterPin;
static char tempMasterPinUse[127];
static char tempMasterPinDir[127];
static BBox tempMpinBBox;
static dbLayerGeom *pTempPort;
static dbLayer     *pTempLayer;
static dbMasterCell *pTempMasterCell;
static dbMasterCellType::PadSubClass tempPadClass;
//end extpin globals

//globals for groups
static vector<dbCell*> tempCompCache;
//static vector<dbCell*> emptyCompCache;
static bool            bSoft;
static int             nNumGroupRegions; // to check my understanding only
static int             tempMaxX,tempMaxY,tempMaxHp;
//end groups globals

//globals for dbRow ctor
static char       tempRowName[1023];
static dbSite    *pTempSite;
static Point      tempRowOrig;
static dbRow::Dir tempRowDir;
//static Orient     tempRowOrient; //already have tempOrient
static unsigned   tempNumSites;
static unsigned   tempRowSpacing;
//end dbRow globals

//globals for tracks
static bool tempHoriz;
static vector<dbLayer*> trackLayers;
//end tracks globals

//globals for vias
static dbVia            *pTempVia;
static char              tempViaName[1023];
static ctainerLayerGeoms tempViaLGs;
//end vias globals

//globals for special wiring
static double        tempWidth;
static Point         lastPoint;
        //following two vectors are parallel 
static vector<BBoxExtended>    wireGeoms;
static vector<bool> wrongWay;

double        wireMinX,wireMinY,wireMaxX,wireMaxY;
//end special wiring globals

int bCaseSensDEF=0;

static char cellname[2048];
static char pinname[2048];
static char tempGroupName[2048];

#line 229 "defparse.tab.c" /* yacc.c:339  */

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
   by #include "defparse.tab.h".  */
#ifndef YY_DEF_DEFPARSE_TAB_H_INCLUDED
# define YY_DEF_DEFPARSE_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int defdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    QSTRING = 258,
    STRING_not_keyword = 259,
    NUMBER = 260,
    K_HISTORY = 261,
    K_DESIGN = 262,
    K_VIAS = 263,
    K_TECH = 264,
    K_UNITS = 265,
    K_ARRAY = 266,
    K_FLOORPLAN = 267,
    K_LRECT = 268,
    K_SITE = 269,
    K_DIEAREA = 270,
    K_PINS = 271,
    K_DCAP = 272,
    K_MINPINS = 273,
    K_WIRECAP = 274,
    K_TRACKS = 275,
    K_GCELLGRID = 276,
    K_SYNTH = 277,
    K_DO = 278,
    K_BY = 279,
    K_STEP = 280,
    K_LAYER = 281,
    K_XTALK = 282,
    K_COMPS = 283,
    K_COMP_GEN = 284,
    K_SOURCE = 285,
    K_WEIGHT = 286,
    K_FIXED = 287,
    K_COVER = 288,
    K_PLACED = 289,
    K_UNPLACED = 290,
    K_FOREIGN = 291,
    K_REGION = 292,
    K_NETS = 293,
    K_MUSTJOIN = 294,
    K_ORIGINAL = 295,
    K_USE = 296,
    K_ORDER = 297,
    K_FLOAT = 298,
    K_SCAN = 299,
    K_COMM_SCAN = 300,
    K_START = 301,
    K_STOP = 302,
    K_IN = 303,
    K_OUT = 304,
    K_PATTERN = 305,
    K_SCANFIX = 306,
    K_ESTCAP = 307,
    K_ROUTED = 308,
    K_NEW = 309,
    K_SNETS = 310,
    K_WIDTH = 311,
    K_VOLTAGE = 312,
    K_SPACING = 313,
    K_N = 314,
    K_S = 315,
    K_E = 316,
    K_W = 317,
    K_FN = 318,
    K_FE = 319,
    K_FS = 320,
    K_FW = 321,
    K_GROUPS = 322,
    K_START_GROUP = 323,
    K_SOFT = 324,
    K_MAXX = 325,
    K_MAXY = 326,
    K_MAXHALFPERIMETER = 327,
    K_CONSTRAINTS = 328,
    K_NET = 329,
    K_PATH = 330,
    K_RISEMIN = 331,
    K_RISEMAX = 332,
    K_FALLMIN = 333,
    K_FALLMAX = 334,
    K_WIREDLOGIC = 335,
    K_MAXDIST = 336,
    K_ASSERTIONS = 337,
    K_SUM = 338,
    K_DISTANCE = 339,
    K_MICRONS = 340,
    K_LE = 341,
    K_GE = 342,
    K_NE = 343,
    K_END = 344,
    K_DCAPS = 345,
    K_PATTERNNAME = 346,
    K_ROW = 347,
    K_SIGNAL = 348,
    K_POWER = 349,
    K_GROUND = 350,
    K_CLOCK = 351,
    K_TIEOFF = 352,
    K_ANALOG = 353,
    K_INPUT = 354,
    K_OUTPUT = 355,
    K_INOUT = 356,
    K_TRISTATE = 357,
    K_DIRECTION = 358,
    K_SPECIAL = 359,
    K_SHAPE = 360,
    K_ABUTMENT = 361,
    K_RING = 362,
    K_FEEDTHRU = 363,
    K_TAPER = 364,
    K_REGIONS = 365,
    K_PROPERTY = 366,
    K_VERSION = 367,
    K_BUSBITCHARS = 368,
    K_DIVIDERCHAR = 369,
    QUOTED_STR = 370,
    K_X = 371,
    K_Y = 372,
    K_ON = 373,
    K_OFF = 374,
    K_CASE = 375,
    K_PROPERTYDEFINITIONS = 376,
    K_SPECIALNET = 377,
    K_GROUP = 378,
    K_COMPONENTPIN = 379,
    K_INTEGER = 380,
    K_REAL = 381,
    K_STRING = 382,
    K_RANGE = 383,
    K_COMPONENT = 384,
    K_RISE = 385,
    K_FALL = 386,
    K_VARIABLE = 387,
    K_SLEWRATE = 388,
    K_CAPACITANCE = 389,
    K_DRIVECELL = 390,
    K_FROMPIN = 391,
    K_TOPIN = 392,
    K_PARALLEL = 393,
    K_PIN = 394,
    K_IOTIMINGS = 395,
    K_PINPROPERTIES = 396,
    K_STRIPE = 397,
    K_PLUS = 398,
    K_MINUS = 399,
    K_STAR = 400,
    K_ASGN = 401,
    SITE_PATTERN = 402,
    K_COMMA = 403,
    K_SEMCOL = 404,
    K_DOT_DOT = 405,
    K_DOT = 406,
    K_COLON = 407,
    K_ORDBR1 = 408,
    K_ORDBR2 = 409,
    K_CHAR_CONST = 410,
    K_INT_CONST = 411,
    K_REAL_CONST = 412,
    K_IDENTIFIER = 413
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 156 "defparse.y" /* yacc.c:355  */

    double       dval ;
    int          integer ;
    lexemeStruct string ;
    int          keyword ;  /* really just a nop */
    struct       LEFDEFpoint pt;
    BBoxSimple   bbox;
    /* TOKEN *tk; */

#line 438 "defparse.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE deflval;

int defparse (void);

#endif /* !YY_DEF_DEFPARSE_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 453 "defparse.tab.c" /* yacc.c:358  */

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
#define YYLAST   1710

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  159
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  194
/* YYNRULES -- Number of rules.  */
#define YYNRULES  484
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  743

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   413

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
     155,   156,   157,   158
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   229,   229,   230,   233,   234,   235,   238,   238,   238,
     238,   239,   240,   240,   240,   241,   242,   242,   242,   243,
     243,   243,   244,   248,   252,   256,   260,   261,   265,   269,
     272,   274,   278,   285,   286,   287,   288,   289,   290,   291,
     292,   296,   297,   298,   302,   303,   307,   308,   312,   313,
     317,   317,   317,   317,   317,   317,   318,   318,   318,   318,
     318,   319,   322,   330,   335,   342,   346,   350,   354,   360,
     366,   372,   384,   385,   388,   405,   417,   482,   483,   484,
     485,   486,   487,   488,   489,   492,   498,   502,   506,   507,
     510,   514,   518,   522,   528,   529,   532,   552,   783,   787,
     788,   791,   792,   793,   794,   795,   798,   801,   804,   824,
     835,   837,   839,   841,   846,   862,   870,   871,   874,   875,
     878,   882,   883,   887,   893,   896,   900,   901,   904,   912,
     990,   993,   996,   997,  1000,  1003,  1026,  1027,  1030,  1033,
    1033,  1045,  1055,  1056,  1059,  1060,  1063,  1071,  1078,  1083,
    1089,  1095,  1103,  1109,  1113,  1116,  1129,  1130,  1134,  1186,
    1191,  1228,  1229,  1233,  1240,  1241,  1245,  1246,  1247,  1249,
    1250,  1251,  1254,  1261,  1267,  1273,  1294,  1301,  1315,  1322,
    1329,  1334,  1340,  1344,  1351,  1356,  1370,  1371,  1375,  1382,
    1476,  1502,  1503,  1506,  1582,  1586,  1593,  1594,  1598,  1599,
    1602,  1604,  1606,  1608,  1612,  1616,  1620,  1624,  1626,  1629,
    1633,  1636,  1637,  1638,  1639,  1640,  1641,  1644,  1646,  1648,
    1653,  1658,  1659,  1663,  1669,  1705,  1711,  1724,  1725,  1729,
    1730,  1733,  1736,  1737,  1738,  1739,  1744,  1750,  1751,  1754,
    1778,  1796,  1800,  1816,  1829,  1832,  1833,  1836,  1844,  1845,
    1848,  1848,  1849,  1849,  1852,  1858,  1862,  1868,  1879,  1884,
    1887,  1891,  1892,  1895,  1898,  1904,  1905,  1908,  1909,  1914,
    1916,  1918,  1925,  1926,  1930,  1936,  1937,  1938,  1939,  1942,
    1949,  1956,  1959,  1964,  1968,  1969,  1972,  2012,  2025,  2026,
    2029,  2049,  2050,  2053,  2057,  2058,  2065,  2070,  2090,  2091,
    2095,  2096,  2097,  2100,  2103,  2106,  2109,  2110,  2113,  2114,
    2117,  2118,  2121,  2122,  2125,  2129,  2138,  2144,  2145,  2148,
    2150,  2152,  2154,  2158,  2163,  2166,  2168,  2173,  2177,  2184,
    2186,  2190,  2194,  2196,  2200,  2206,  2208,  2212,  2212,  2217,
    2219,  2223,  2230,  2231,  2232,  2233,  2238,  2239,  2242,  2244,
    2247,  2249,  2252,  2254,  2259,  2260,  2261,  2262,  2263,  2264,
    2265,  2266,  2267,  2268,  2269,  2270,  2271,  2272,  2273,  2274,
    2275,  2276,  2277,  2278,  2279,  2280,  2281,  2282,  2283,  2284,
    2285,  2286,  2287,  2288,  2289,  2290,  2291,  2292,  2293,  2294,
    2295,  2296,  2297,  2298,  2299,  2300,  2301,  2302,  2303,  2304,
    2305,  2306,  2307,  2308,  2309,  2310,  2311,  2312,  2313,  2314,
    2315,  2316,  2317,  2318,  2319,  2320,  2321,  2322,  2323,  2324,
    2325,  2326,  2327,  2328,  2329,  2330,  2331,  2332,  2333,  2334,
    2335,  2336,  2337,  2338,  2339,  2340,  2341,  2342,  2343,  2344,
    2345,  2346,  2347,  2348,  2349,  2350,  2351,  2352,  2353,  2354,
    2355,  2356,  2357,  2358,  2359,  2360,  2361,  2362,  2363,  2364,
    2365,  2366,  2367,  2368,  2369,  2370,  2371,  2372,  2373,  2374,
    2375,  2376,  2377,  2378,  2379,  2380,  2381,  2382,  2383,  2384,
    2385,  2388,  2390,  2393,  2394
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "QSTRING", "STRING_not_keyword",
  "NUMBER", "K_HISTORY", "K_DESIGN", "K_VIAS", "K_TECH", "K_UNITS",
  "K_ARRAY", "K_FLOORPLAN", "K_LRECT", "K_SITE", "K_DIEAREA", "K_PINS",
  "K_DCAP", "K_MINPINS", "K_WIRECAP", "K_TRACKS", "K_GCELLGRID", "K_SYNTH",
  "K_DO", "K_BY", "K_STEP", "K_LAYER", "K_XTALK", "K_COMPS", "K_COMP_GEN",
  "K_SOURCE", "K_WEIGHT", "K_FIXED", "K_COVER", "K_PLACED", "K_UNPLACED",
  "K_FOREIGN", "K_REGION", "K_NETS", "K_MUSTJOIN", "K_ORIGINAL", "K_USE",
  "K_ORDER", "K_FLOAT", "K_SCAN", "K_COMM_SCAN", "K_START", "K_STOP",
  "K_IN", "K_OUT", "K_PATTERN", "K_SCANFIX", "K_ESTCAP", "K_ROUTED",
  "K_NEW", "K_SNETS", "K_WIDTH", "K_VOLTAGE", "K_SPACING", "K_N", "K_S",
  "K_E", "K_W", "K_FN", "K_FE", "K_FS", "K_FW", "K_GROUPS",
  "K_START_GROUP", "K_SOFT", "K_MAXX", "K_MAXY", "K_MAXHALFPERIMETER",
  "K_CONSTRAINTS", "K_NET", "K_PATH", "K_RISEMIN", "K_RISEMAX",
  "K_FALLMIN", "K_FALLMAX", "K_WIREDLOGIC", "K_MAXDIST", "K_ASSERTIONS",
  "K_SUM", "K_DISTANCE", "K_MICRONS", "K_LE", "K_GE", "K_NE", "K_END",
  "K_DCAPS", "K_PATTERNNAME", "K_ROW", "K_SIGNAL", "K_POWER", "K_GROUND",
  "K_CLOCK", "K_TIEOFF", "K_ANALOG", "K_INPUT", "K_OUTPUT", "K_INOUT",
  "K_TRISTATE", "K_DIRECTION", "K_SPECIAL", "K_SHAPE", "K_ABUTMENT",
  "K_RING", "K_FEEDTHRU", "K_TAPER", "K_REGIONS", "K_PROPERTY",
  "K_VERSION", "K_BUSBITCHARS", "K_DIVIDERCHAR", "QUOTED_STR", "K_X",
  "K_Y", "K_ON", "K_OFF", "K_CASE", "K_PROPERTYDEFINITIONS",
  "K_SPECIALNET", "K_GROUP", "K_COMPONENTPIN", "K_INTEGER", "K_REAL",
  "K_STRING", "K_RANGE", "K_COMPONENT", "K_RISE", "K_FALL", "K_VARIABLE",
  "K_SLEWRATE", "K_CAPACITANCE", "K_DRIVECELL", "K_FROMPIN", "K_TOPIN",
  "K_PARALLEL", "K_PIN", "K_IOTIMINGS", "K_PINPROPERTIES", "K_STRIPE",
  "K_PLUS", "K_MINUS", "K_STAR", "K_ASGN", "SITE_PATTERN", "K_COMMA",
  "K_SEMCOL", "K_DOT_DOT", "K_DOT", "K_COLON", "K_ORDBR1", "K_ORDBR2",
  "K_CHAR_CONST", "K_INT_CONST", "K_REAL_CONST", "K_IDENTIFIER", "$accept",
  "def_file", "rules", "rule", "version_section", "busbitchar_section",
  "dividerchar_section", "case_section", "begin_case", "propdefs_section",
  "propdefs_list", "propdef_item", "object_type", "prop_type",
  "poss_range", "poss_prop_val", "prop_val", "design_section",
  "design_name", "end_design", "tech_name", "array_name", "floorplan_name",
  "history", "units", "row_start", "site_start", "row_init",
  "row_start_or_site_start", "site_type_and_step_pattern", "row",
  "site_step_pattern", "orient", "die_area", "pin_cap_rule",
  "start_def_cap", "pin_caps", "pin_cap", "end_def_cap", "pin_rule",
  "start_pins", "pins", "pin_start", "pin", "end_pins", "ext_pin_net_opts",
  "ext_pin_net_opt", "direction_spec", "special_opt", "layer_name",
  "ext_pin_layer_opt", "pin_direction", "tracks_rule", "track_start",
  "track_direction", "poss_mult_layers_spec", "mult_layers_spec",
  "mult_layer_names", "gcellgrid", "via_section", "via",
  "via_declarations", "via_start", "via_declaration", "regions_section",
  "regions_start", "region_declarations", "region_declaration",
  "region_boxes_start", "region_boxes", "region_box", "region_prop",
  "regions_end", "layer_rects_or_patterns", "layer_rect_or_pattern",
  "layer_rect", "layer_pattern", "pt", "bbox", "via_end", "comps_section",
  "start_comps", "comps_rule", "comp", "comp_start", "comp_id_and_name",
  "comp_netlist", "comp_options", "comp_option", "comp_generate",
  "comp_source", "comp_region", "comp_foreign", "comp_type", "comp_types",
  "weight", "end_comps", "nets_section", "start_nets", "net_rules",
  "one_net", "net_and_connections", "net_start", "net_connections",
  "net_connection", "plus_synth", "net_options", "net_option",
  "use_option", "use_spec", "net_type", "paths", "new_paths",
  "new_keyword", "layer_path", "layer_path_start", "poss_taper",
  "poss_shape_opt", "shape_opt", "shape_spec", "path_start_pt",
  "pt_or_via_opts", "pt_or_via", "end_nets", "via_name",
  "via_name_tolerant", "snets_section", "snet_rules", "snet_rule",
  "snet_options", "snet_option", "snet_width", "snet_voltage",
  "snet_spacing", "start_snets", "end_snets", "scan_section", "scan_start",
  "scan_rules", "one_scan", "scan_name", "scan_opts", "scan_opt",
  "scan_elements", "scan_element", "scan_pin_opt", "scan_in_pin",
  "scan_out_pin", "scan_end", "groups_section", "groups_start",
  "group_rules", "group_rule", "start_group", "group_members",
  "group_member", "group_options", "group_option", "grp_region",
  "group_soft_options", "group_soft_opt", "groups_end",
  "constraint_section", "constraints_start", "constraint_rules",
  "constraint_rule", "operand_rule", "operands", "operand",
  "wiredlogic_rule", "delay_specs", "delay_spec", "constraints_end",
  "iotimings_section", "iotimings_list", "iotiming_spec", "iotiming_pin",
  "iotiming_trait_list", "pinproperties_section", "pinproperties_list",
  "pinproperty_stmt", "pinprop_list", "prop_spec", "$@1",
  "prop_spec0_list", "prop_spec0", "iotiming_trait", "r_or_f",
  "poss_drivecell_pins", "poss_drivecell_from", "poss_drivecell_parallel",
  "STRING_not_NEW", "STRING_list", "STRING", YY_NULLPTR
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
     405,   406,   407,   408,   409,   410,   411,   412,   413
};
# endif

#define YYPACT_NINF -582

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-582)))

#define YYTABLE_NINF -351

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     226,  -582,    47,  1569,  -582,  -582,  1297,    25,  1297,   -35,
    1297,  1297,  -582,  -102,    56,    59,  -582,  1297,    61,   218,
     220,   223,   240,   250,   261,  1297,   278,   280,   116,   188,
    -582,  -582,   299,   302,  -582,  -582,  -582,  -582,  -582,   -60,
    -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  1297,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
     -83,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
     873,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
     159,   160,   162,   227,   164,   168,    15,  -102,   170,   171,
    -582,   317,   174,   176,   180,   181,   183,   185,  -582,  -582,
     192,   193,   194,   196,   232,   199,   201,   202,   203,  -582,
     339,   195,   -81,  -582,  -582,   348,   -79,   -77,   -76,   -74,
     127,   128,   129,   -73,  -582,  -582,  -582,  -582,  -582,   352,
    -582,  -582,    34,    35,  -582,  -582,  -582,   314,  -582,  -582,
    -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,   237,  -582,  -582,  -582,  -582,  -582,  -582,  1297,  -582,
    -582,  -582,  -582,   354,  -582,   355,   346,  -582,  -582,   349,
    1297,   221,  -582,  -582,   350,   366,  -582,  1434,  -582,  -582,
     252,  1297,  -582,  -102,  -582,   351,  1297,  -582,  -582,  -582,
    -582,   342,  1297,  -582,  -582,  -582,  -582,   326,  -582,  -582,
    -582,   338,  1297,  -582,   244,  -582,   316,  1297,  -582,  1297,
    -582,  1297,   315,   -57,  -582,  -582,  -582,  -582,   242,   238,
     239,   245,   246,   389,  -582,   165,   130,   131,   387,   385,
    -582,  -582,  -582,   331,   401,  -582,  -582,  -582,  -582,  -582,
    -129,  -582,  -582,  -582,  1297,  -118,  1017,  -582,  -582,  -111,
      30,  -582,  -108,  -582,  -582,   206,  -106,  -582,  -582,  -582,
    1297,  -582,  -582,   328,  -582,  1297,  1297,   257,  -582,  -582,
    -582,  -582,  -582,  -582,   390,  -582,  -582,  -582,   288,   277,
     265,  -582,   279,  1297,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -582,  -582,   400,   439,  1297,   429,  -101,   344,  -582,
     310,  -582,   406,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -102,  -582,  -582,  -582,   381,  -582,  -582,  -582,  1297,  -582,
     307,  1157,  -582,   345,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -582,   308,  1297,  1297,  -582,  -582,  -582,   -99,   457,
    -582,  1297,   186,   -97,   458,   459,    99,  -582,  1297,  -582,
    -582,  1297,   461,   318,  -582,   463,   198,  -582,  -582,  -582,
    -582,  1297,  -582,  1297,  1297,   464,  -582,  -582,  -582,  -582,
    1297,    69,   387,   465,  1297,   466,  -582,  -582,  1297,   332,
    1297,  -582,   468,  -582,  -582,   205,  -582,  -582,  -582,  -582,
    1297,  1297,  1297,  1297,   469,  1297,  1297,  1297,   428,   324,
    1297,  1297,   175,  -582,  -582,   329,  1297,   333,   219,  -582,
    -582,   330,   475,  -582,  -582,   334,  -582,  1297,   -89,  -582,
     460,  -582,   -87,   456,  1297,  1297,   481,  1297,  -582,  -582,
    -102,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -582,  -582,  -582,  -582,  -582,  -582,  1297,   347,  -582,
    -102,   437,   725,  1297,   343,   353,   488,  -582,   494,  -582,
     356,  1297,   451,  -582,  -582,  -582,    69,  -582,  1297,  -582,
    1297,   186,   357,   496,   498,   500,   501,  -582,  -582,  -582,
     358,   132,  -582,    72,   502,   224,  -582,  -582,  -582,  -582,
    -582,  -582,  -582,  -582,   359,  -582,  -102,  -582,  -582,  -582,
    1297,  -582,  -582,    99,   405,  -102,  -582,  -582,  -582,  -582,
    1297,  -582,  -582,  -582,  -582,   364,  -582,   491,   368,  -582,
    -582,   228,  -582,   324,  -582,   369,  1297,  -582,  -582,  -582,
     230,   521,  -582,   333,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -582,   522,  1297,  -582,   147,   417,  -582,  -582,   504,
    1297,   -72,  -582,  1297,  -582,  -582,  -582,  -582,   -85,  -582,
    -582,  -582,  -582,  -582,  -582,  -582,   377,   527,   528,   529,
    -582,  -582,  -582,    81,  -582,   151,   530,   531,   532,  -102,
    -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -582,  -582,  -582,  -582,  -582,  1297,   402,   407,   533,
     534,   537,  -582,  -582,   538,  -582,  1297,  -582,  -582,   396,
    -582,  -582,  -582
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     6,     0,     2,     1,   481,     0,     0,     0,     0,
       0,     0,    70,     0,     0,     0,   115,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      28,    30,     0,     0,     5,     7,     8,    10,     9,     0,
      11,    12,    50,     3,    51,    60,    61,    52,    53,    72,
      73,     0,    71,    54,    55,    56,    88,    57,    94,    58,
       0,    59,    13,   126,    14,   132,    15,   156,    16,   186,
      17,   245,    19,   261,    18,   284,    20,   306,    21,    22,
       0,   354,   355,   356,   357,   358,   359,   360,   361,   362,
     363,   364,   365,   366,   367,   368,   369,   370,   371,   372,
     373,   374,   375,   376,   377,   378,   379,   380,   381,   382,
     383,   384,   385,   386,   387,   388,   389,   390,   391,   392,
     393,   394,   395,   396,   397,   398,   399,   400,   401,   484,
     402,   403,   404,   405,   406,   407,   408,   409,   410,   411,
     412,   413,   414,   415,   416,   417,   418,   419,   420,   421,
     422,   423,   424,   425,   426,   427,   428,   429,   430,   431,
     432,   433,   434,   435,   436,   437,   438,   439,   440,   441,
     442,   443,   444,   445,   446,   447,   448,   449,   450,   451,
     452,   453,   454,   455,   456,   457,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   473,   474,   475,   476,   477,   478,   479,   480,   483,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      87,     0,     0,     0,     0,     0,     0,     0,    63,    69,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    75,
       0,     0,     0,   116,   117,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    67,   482,    62,   125,    64,     0,
      65,    66,     0,     0,   152,    85,    93,     0,   155,   185,
     260,   257,   283,   305,   131,    23,    24,    25,    33,    40,
      35,     0,    38,    36,    37,    39,    34,    31,     0,   325,
     332,    26,    27,     0,    74,     0,     0,    89,    86,     0,
       0,     0,    95,    92,     0,     0,   128,     0,   127,   124,
       0,     0,   133,     0,   130,     0,     0,   157,   164,   161,
     154,     0,     0,   187,   198,   191,   184,     0,   248,   246,
     244,     0,     0,   262,     0,   259,     0,     0,   285,     0,
     282,     0,     0,     0,   307,   308,   309,   304,     0,     0,
       0,     0,     0,     0,    29,     0,     0,     0,     0,     0,
      91,    98,    96,     0,     0,   153,   142,   243,   141,   135,
     139,   136,   138,   183,     0,     0,   159,   241,   190,     0,
     189,   258,     0,   281,   264,     0,     0,   265,   303,   287,
     291,   288,   290,     0,   323,     0,     0,     0,   317,    68,
     148,   150,   149,   151,     0,    41,    42,    43,    44,     0,
       0,   326,     0,     0,   333,    77,    79,    78,    80,    81,
      82,    83,    84,     0,     0,     0,     0,     0,     0,   137,
       0,   160,     0,   158,   165,   166,   167,   171,   170,   168,
       0,   169,   162,   163,     0,   188,   199,   208,     0,   209,
       0,     0,   192,     0,   247,   253,   249,   250,   251,   252,
     272,   272,     0,     0,     0,   263,   266,   289,     0,     0,
     314,     0,     0,     0,     0,     0,    46,   324,     0,   329,
     331,     0,     0,     0,    99,     0,     0,   129,   143,   144,
     145,     0,   134,     0,     0,     0,   178,   179,   180,   181,
       0,     0,     0,     0,     0,     0,   217,   218,     0,     0,
       0,   201,     0,   219,   339,   227,   200,   221,   237,   108,
       0,     0,     0,     0,     0,     0,   270,   269,     0,     0,
       0,     0,     0,   286,   292,     0,     0,   312,     0,   310,
     318,     0,     0,    48,    49,     0,    47,     0,     0,   335,
       0,    90,     0,   118,     0,     0,     0,     0,   173,   182,
       0,   174,   175,   177,   202,   203,   206,   204,   211,   212,
     213,   214,   215,   216,   210,   205,   207,   337,   229,   228,
       0,   220,   224,     0,     0,   196,     0,   255,     0,   273,
     275,     0,     0,   267,   268,   271,     0,   298,     0,   316,
       0,     0,     0,     0,     0,     0,     0,   123,    45,    32,
       0,     0,   327,     0,     0,     0,    97,   100,   101,   103,
     104,   105,   102,   121,     0,   119,     0,   147,   140,   172,
       0,   338,   340,     0,     0,     0,   230,   236,   226,   223,
       0,   239,   238,   240,   242,     0,   194,     0,     0,   254,
     256,     0,   274,   277,   278,     0,     0,   296,   294,   297,
     293,     0,   315,   312,   317,   319,   320,   321,   322,   328,
     346,   347,     0,     0,   330,     0,     0,   334,   336,     0,
       0,     0,   107,   120,   114,   146,   176,   341,     0,   225,
     222,   195,   197,   193,   276,   279,     0,     0,     0,     0,
     299,   295,   313,     0,   344,   348,     0,     0,     0,     0,
     110,   112,   111,   113,   106,   122,   232,   233,   234,   235,
     231,   280,   300,   301,   302,   311,     0,   352,     0,     0,
       0,     0,   109,   351,     0,   345,     0,   342,   343,     0,
     353,   349,    76
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -582,  -582,  -582,  -582,  -582,   -86,  -582,  -582,  -582,
    -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -582,    44,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -499,
    -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
     178,  -582,  -582,  -582,  -582,  -582,  -582,  -211,   -12,  -582,
    -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -582,  -582,    -2,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,   303,  -582,  -582,  -582,  -582,  -582,   172,     0,  -582,
    -582,  -582,  -582,  -582,   -84,  -582,  -582,  -582,  -582,  -582,
     -80,  -582,  -582,  -582,  -582,   -25,  -582,  -582,  -582,  -582,
    -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -582,   173,    97,  -582,  -582,   -30,  -581,  -582,  -582,
    -582,  -582,  -582,  -582,  -582,   177,  -582,  -582,  -582,  -582,
    -582,  -582,  -582,  -582,  -582,  -582,  -582,  -100,  -419,  -582,
    -103,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -582,   -51,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,  -304,  -582,    -6
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    34,    35,    36,    37,    38,    39,    40,
     234,   287,   288,   408,   476,   545,   546,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,   239,
      53,   294,   423,    54,    55,    56,   241,   297,   298,    57,
      58,   242,   301,   302,   303,   552,   617,   618,   619,   515,
     620,   714,    59,    60,   245,   624,   625,   683,    61,    62,
      63,   246,   307,   308,    64,    65,   247,   312,   313,   370,
     371,   430,   314,   427,   488,   489,   490,   217,   372,   309,
      66,    67,   248,   317,   318,   319,   376,   375,   434,   435,
     436,   437,   438,   439,   440,   441,   320,    68,    69,   249,
     323,   324,   325,   380,   452,   648,   379,   446,   447,   574,
     448,   516,   581,   640,   517,   518,   580,   635,   636,   720,
     638,   582,   642,   326,   643,   366,    70,   250,   329,   382,
     456,   457,   458,   459,    71,   330,    72,    73,   251,   333,
     334,   386,   387,   526,   589,   652,   529,   593,   335,    74,
      75,   252,   338,   339,   390,   391,   468,   534,   658,   660,
     700,   340,    76,    77,   253,   344,   345,   602,   398,   346,
     473,   540,   347,    78,   356,   411,   479,   548,    79,   357,
     414,   613,   449,   631,   577,   632,   674,   675,   727,   728,
     735,   209,    80,   519
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     210,   218,   212,   367,   214,   215,   264,   341,   299,   654,
     305,   221,   310,   315,   428,   321,   342,   395,   396,   229,
     262,   716,   717,   718,   216,   432,   397,   710,   711,   712,
     211,   433,   444,   243,   244,   453,   713,   385,   445,   349,
     351,   454,   486,   465,   532,   240,   538,     4,   487,   213,
     533,   216,   539,   537,   611,   626,   615,   719,   237,   238,
     612,   219,   616,   300,   220,   306,   222,   311,   316,   450,
     322,   343,   694,    81,   255,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   543,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     263,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   350,
     352,   709,   663,   451,   715,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     578,   554,   596,   295,   544,   676,   327,   331,   336,   409,
     412,   677,   216,   223,   538,   224,    -4,     1,   225,   502,
     725,   232,    -4,    -4,    -4,    -4,    -4,    -4,    -4,   278,
      -4,    -4,    -4,    -4,   597,   226,    -4,    -4,   460,   461,
     680,   462,   463,   464,    -4,   227,   496,   497,   498,   499,
     395,   396,   670,   671,    -4,   509,   672,   673,   228,   279,
      -4,   322,   332,   337,   410,   413,   591,   656,   367,   706,
     707,    -4,   355,   230,   296,   231,   598,   726,  -350,   555,
     405,   406,   407,    -4,   362,   603,   604,   605,   606,    -4,
     697,   698,   699,   233,   235,   369,   280,   236,   256,   257,
     374,   258,   259,   260,   579,    -4,   378,   261,    -4,   265,
     266,   281,   267,   268,   282,   269,   384,   681,   682,   270,
     271,   389,   272,   392,   273,   393,    -4,   353,    -4,    -4,
      -4,   274,   275,   276,   293,   277,    -4,    -4,   289,   630,
     290,   291,   292,   304,   283,   284,   285,   348,   354,   358,
     359,   286,   368,   360,   363,   361,    -4,    -4,   431,   637,
     443,   641,   503,   364,   365,   504,   505,   506,   507,   373,
     377,   381,   383,   388,   392,   508,   509,   385,   394,   470,
     471,   399,   400,   401,   404,   510,   511,   512,   513,   402,
     403,   523,   524,   525,   424,   425,   426,   481,   503,   469,
     472,   504,   505,   506,   507,   474,   475,   477,   478,   484,
     480,   508,   509,   482,   637,   568,   569,   570,   571,   572,
     573,   510,   511,   512,   513,   493,   494,   495,   496,   497,
     498,   499,   500,   501,   483,   522,   415,   416,   417,   418,
     419,   420,   421,   422,   485,   491,   514,   530,   531,   492,
     520,   528,   535,   541,   542,   536,   550,   551,   553,   559,
     564,   566,   547,   576,   587,   549,   591,   592,   599,   607,
     608,   601,   623,   609,   614,   556,   628,   557,   558,   561,
     634,   639,   514,   649,   560,   562,   647,   646,   565,   650,
     656,   665,   567,   666,   575,   667,   668,   679,   684,   651,
     688,   664,   669,   692,   583,   584,   585,   586,   691,   588,
     590,   590,   693,   695,   594,   595,   701,   704,   514,   708,
     600,   721,   722,   723,   724,   729,   730,   731,   737,   738,
     734,   610,   739,   740,   736,   742,   563,   687,   429,   627,
     621,   629,   622,   328,   455,   689,   690,   644,   527,   466,
     653,   703,   678,   702,     0,     0,     0,   467,     0,     0,
       0,   633,     0,     0,     0,     0,     0,   645,     0,     0,
       0,     0,     0,     0,   657,   655,     0,     0,     0,     0,
     659,     0,   661,     0,   662,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   685,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   686,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     696,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   705,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   732,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     733,     0,     0,     0,     0,     0,     0,     0,     0,    81,
     741,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
       0,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,     0,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,     0,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,     0,     0,     0,     0,     0,
       0,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    81,   216,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,     0,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,     0,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,     0,     0,     0,     0,     0,     0,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,     0,     0,     0,     0,     0,     0,
       0,    81,   254,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,     0,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,     0,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,     0,     0,     0,
       0,     0,     0,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,     0,     0,
       0,    81,   442,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,     0,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,     0,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,     0,     0,     0,
       0,     0,     0,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,     0,     0,
       0,    81,   521,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,     0,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,     0,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,     0,     0,     0,
       0,     0,     0,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,    81,     0,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,     0,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,     0,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,     0,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,     0,     0,     0,     0,     0,     0,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,     5,     6,     7,     8,     9,
      10,    11,     0,    12,    13,    14,    15,     0,     0,    16,
      17,     0,     0,     0,     0,     0,     0,    18,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    19,     0,     0,
       0,     0,     0,    20,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    21,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    22,     0,     0,     0,
       0,     0,    23,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    24,     0,
       0,    25,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    26,
       0,    27,    28,    29,     0,     0,     0,     0,     0,    30,
      31,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    32,
      33
};

static const yytype_int16 yycheck[] =
{
       6,    13,     8,   307,    10,    11,   217,    80,    89,   590,
      89,    17,    89,    89,   143,    89,    89,    74,    75,    25,
       5,   106,   107,   108,   153,   143,    83,    99,   100,   101,
       5,   149,   143,   116,   117,   143,   108,   143,   149,     5,
       5,   149,   143,   149,   143,    51,   143,     0,   149,    84,
     149,   153,   149,   472,   143,   554,   143,   142,   118,   119,
     149,     5,   149,   144,     5,   144,     5,   144,   144,    39,
     144,   144,   653,     4,    80,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,     5,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
     145,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   145,
     145,   680,   601,   153,   683,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
       5,    13,    37,    18,   115,   143,    89,    89,    89,    89,
      89,   149,   153,     5,   143,     5,     0,     1,     5,   440,
     149,   115,     6,     7,     8,     9,    10,    11,    12,     7,
      14,    15,    16,    17,    69,     5,    20,    21,    42,    43,
      26,    45,    46,    47,    28,     5,    32,    33,    34,    35,
      74,    75,   130,   131,    38,    41,   134,   135,     7,    37,
      44,   144,   144,   144,   144,   144,    48,    49,   582,   132,
     133,    55,   288,     5,    89,     5,   111,   136,   137,    91,
     125,   126,   127,    67,   300,    76,    77,    78,    79,    73,
      70,    71,    72,   115,     5,   311,    74,     5,   149,   149,
     316,   149,    85,   149,   109,    89,   322,   149,    92,   149,
     149,    89,     5,   149,    92,   149,   332,   103,   104,   149,
     149,   337,   149,   339,   149,   341,   110,    23,   112,   113,
     114,   149,   149,   149,     5,   149,   120,   121,   149,   560,
     149,   149,   149,     5,   122,   123,   124,     5,   121,     5,
       5,   129,   110,    17,   143,    16,   140,   141,   374,   580,
     376,   582,    27,    23,     8,    30,    31,    32,    33,    28,
      38,    55,    44,    67,   390,    40,    41,   143,    73,   395,
     396,   149,   154,   154,     5,    50,    51,    52,    53,   154,
     154,    56,    57,    58,    19,    74,     5,   413,    27,    81,
     153,    30,    31,    32,    33,    25,   128,   140,   153,   425,
     141,    40,    41,    23,   635,    93,    94,    95,    96,    97,
      98,    50,    51,    52,    53,    29,    30,    31,    32,    33,
      34,    35,    36,    37,     5,   451,    59,    60,    61,    62,
      63,    64,    65,    66,    25,   111,   111,   463,   464,   149,
     153,   153,     5,     5,     5,   471,     5,   149,     5,     5,
       5,     5,   478,     5,     5,   481,    48,   153,   149,   149,
       5,   148,    26,   149,    24,   491,     5,   493,   494,   501,
     143,    54,   111,     5,   500,   501,   143,   154,   504,     5,
      49,     5,   508,     5,   510,     5,     5,     5,   149,   153,
     105,   154,   154,    22,   520,   521,   522,   523,   154,   525,
     526,   527,   154,   154,   530,   531,     5,     5,   111,    25,
     536,   154,     5,     5,     5,     5,     5,     5,     5,     5,
     138,   547,     5,     5,   137,   149,   502,   633,   370,   555,
     552,   557,   552,   250,   382,   635,   640,   582,   461,   386,
     590,   664,   613,   663,    -1,    -1,    -1,   390,    -1,    -1,
      -1,   577,    -1,    -1,    -1,    -1,    -1,   583,    -1,    -1,
      -1,    -1,    -1,    -1,   596,   591,    -1,    -1,    -1,    -1,
     596,    -1,   598,    -1,   600,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   626,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   630,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     656,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   673,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   709,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     726,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     4,
     736,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      -1,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    -1,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    -1,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,    -1,    -1,    -1,    -1,    -1,
      -1,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     4,   153,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    -1,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    -1,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,    -1,    -1,    -1,    -1,    -1,    -1,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     4,   149,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    -1,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    -1,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,    -1,    -1,    -1,
      -1,    -1,    -1,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,    -1,    -1,
      -1,     4,   145,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    -1,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    -1,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,    -1,    -1,    -1,
      -1,    -1,    -1,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,    -1,    -1,
      -1,     4,   145,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    -1,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    -1,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,    -1,    -1,    -1,
      -1,    -1,    -1,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,     4,    -1,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    -1,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    -1,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,    -1,    -1,    -1,    -1,    -1,    -1,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,     6,     7,     8,     9,    10,
      11,    12,    -1,    14,    15,    16,    17,    -1,    -1,    20,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,
      -1,    -1,    -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,
      -1,    -1,    73,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,
      -1,    92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   110,
      -1,   112,   113,   114,    -1,    -1,    -1,    -1,    -1,   120,
     121,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   140,
     141
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     1,   160,   161,     0,     6,     7,     8,     9,    10,
      11,    12,    14,    15,    16,    17,    20,    21,    28,    38,
      44,    55,    67,    73,    89,    92,   110,   112,   113,   114,
     120,   121,   140,   141,   162,   163,   164,   165,   166,   167,
     168,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   189,   192,   193,   194,   198,   199,   211,
     212,   217,   218,   219,   223,   224,   239,   240,   256,   257,
     285,   293,   295,   296,   308,   309,   321,   322,   332,   337,
     351,     4,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   350,
     352,     5,   352,    84,   352,   352,   153,   236,   237,     5,
       5,   352,     5,     5,     5,     5,     5,     5,     7,   352,
       5,     5,   115,   115,   169,     5,     5,   118,   119,   188,
     352,   195,   200,   116,   117,   213,   220,   225,   241,   258,
     286,   297,   310,   323,   149,   352,   149,   149,   149,    85,
     149,   149,     5,   145,   236,   149,   149,     5,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,     7,    37,
      74,    89,    92,   122,   123,   124,   129,   170,   171,   149,
     149,   149,   149,     5,   190,    18,    89,   196,   197,    89,
     144,   201,   202,   203,     5,    89,   144,   221,   222,   238,
      89,   144,   226,   227,   231,    89,   144,   242,   243,   244,
     255,    89,   144,   259,   260,   261,   282,    89,   260,   287,
     294,    89,   144,   298,   299,   307,    89,   144,   311,   312,
     320,    80,    89,   144,   324,   325,   328,   331,     5,     5,
     145,     5,   145,    23,   121,   352,   333,   338,     5,     5,
      17,    16,   352,   143,    23,     8,   284,   350,   110,   352,
     228,   229,   237,    28,   352,   246,   245,    38,   352,   265,
     262,    55,   288,    44,   352,   143,   300,   301,    67,   352,
     313,   314,   352,   352,    73,    74,    75,    83,   327,   149,
     154,   154,   154,   154,     5,   125,   126,   127,   172,    89,
     144,   334,    89,   144,   339,    59,    60,    61,    62,    63,
      64,    65,    66,   191,    19,    74,     5,   232,   143,   229,
     230,   352,   143,   149,   247,   248,   249,   250,   251,   252,
     253,   254,   145,   352,   143,   149,   266,   267,   269,   341,
      39,   153,   263,   143,   149,   266,   289,   290,   291,   292,
      42,    43,    45,    46,    47,   149,   301,   314,   315,    81,
     352,   352,   153,   329,    25,   128,   173,   140,   153,   335,
     141,   352,    23,     5,   352,    25,   143,   149,   233,   234,
     235,   111,   149,    29,    30,    31,    32,    33,    34,    35,
      36,    37,   236,    27,    30,    31,    32,    33,    40,    41,
      50,    51,    52,    53,   111,   208,   270,   273,   274,   352,
     153,   145,   352,    56,    57,    58,   302,   302,   153,   305,
     352,   352,   143,   149,   316,     5,   352,   327,   143,   149,
     330,     5,     5,     5,   115,   174,   175,   352,   336,   352,
       5,   149,   204,     5,    13,    91,   352,   352,   352,     5,
     352,   237,   352,   191,     5,   352,     5,   352,    93,    94,
      95,    96,    97,    98,   268,   352,     5,   343,     5,   109,
     275,   271,   280,   352,   352,   352,   352,     5,   352,   303,
     352,    48,   153,   306,   352,   352,    37,    69,   111,   149,
     352,   148,   326,    76,    77,    78,    79,   149,     5,   149,
     352,   143,   149,   340,    24,   143,   149,   205,   206,   207,
     209,   252,   267,    26,   214,   215,   208,   352,     5,   352,
     236,   342,   344,   352,   143,   276,   277,   236,   279,    54,
     272,   236,   281,   283,   284,   352,   154,   143,   264,     5,
       5,   153,   304,   305,   306,   352,    49,   237,   317,   352,
     318,   352,   352,   327,   154,     5,     5,     5,     5,   154,
     130,   131,   134,   135,   345,   346,   143,   149,   341,     5,
      26,   103,   104,   216,   149,   237,   352,   175,   105,   279,
     273,   154,    22,   154,   306,   154,   352,    70,    71,    72,
     319,     5,   326,   329,     5,   352,   132,   133,    25,   208,
      99,   100,   101,   108,   210,   208,   106,   107,   108,   142,
     278,   154,     5,     5,     5,   149,   136,   347,   348,     5,
       5,     5,   237,   352,   138,   349,   137,     5,     5,     5,
       5,   352,   149
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   159,   160,   160,   161,   161,   161,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   163,   164,   165,   166,   166,   167,   168,
     169,   169,   170,   171,   171,   171,   171,   171,   171,   171,
     171,   172,   172,   172,   173,   173,   174,   174,   175,   175,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   187,   188,   189,   190,   191,   191,   191,
     191,   191,   191,   191,   191,   192,   193,   194,   195,   195,
     196,   197,   198,   199,   200,   200,   201,   202,   203,   204,
     204,   205,   205,   205,   205,   205,   206,   207,   208,   209,
     210,   210,   210,   210,   211,   212,   213,   213,   214,   214,
     215,   216,   216,   217,   218,   219,   220,   220,   221,   222,
     223,   224,   225,   225,   226,   227,   228,   228,   229,   230,
     230,   231,   232,   232,   233,   233,   234,   235,   236,   236,
     236,   236,   237,   238,   239,   240,   241,   241,   242,   243,
     244,   245,   245,   245,   246,   246,   247,   247,   247,   247,
     247,   247,   248,   249,   250,   250,   251,   252,   253,   253,
     253,   253,   254,   255,   256,   257,   258,   258,   259,   260,
     261,   262,   262,   263,   263,   263,   264,   264,   265,   265,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     267,   268,   268,   268,   268,   268,   268,   269,   269,   269,
     270,   271,   271,   272,   273,   274,   274,   275,   275,   276,
     276,   277,   278,   278,   278,   278,   279,   280,   280,   281,
     281,   282,   283,   284,   285,   286,   286,   287,   288,   288,
     289,   289,   289,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   297,   298,   299,   300,   300,   301,   301,   301,
     301,   301,   302,   302,   303,   304,   304,   304,   304,   305,
     306,   307,   308,   309,   310,   310,   311,   312,   313,   313,
     314,   315,   315,   316,   316,   316,   317,   317,   318,   318,
     319,   319,   319,   320,   321,   322,   323,   323,   324,   324,
     325,   325,   326,   326,   327,   327,   328,   329,   329,   330,
     330,   330,   330,   331,   332,   333,   333,   334,   335,   336,
     336,   337,   338,   338,   339,   340,   340,   342,   341,   343,
     343,   344,   345,   345,   345,   345,   346,   346,   347,   347,
     348,   348,   349,   349,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   350,   350,   350,   350,   350,   350,   350,   350,   350,
     350,   351,   351,   352,   352
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     1,     4,
       0,     2,     6,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     3,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     2,     3,     3,     3,     3,     5,     2,
       1,     1,     1,     1,     2,     2,    11,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     2,     0,     2,
       5,     2,     3,     3,     0,     2,     2,     6,     2,     0,
       2,     1,     1,     1,     1,     1,     3,     2,     1,     4,
       1,     1,     1,     1,     9,     1,     1,     1,     0,     1,
       2,     0,     2,     8,     3,     3,     0,     2,     1,     4,
       3,     3,     0,     2,     4,     2,     1,     2,     1,     0,
       4,     2,     0,     2,     1,     1,     4,     3,     4,     4,
       4,     4,     2,     2,     3,     3,     0,     2,     3,     2,
       3,     0,     2,     2,     0,     2,     1,     1,     1,     1,
       1,     1,     4,     3,     3,     3,     5,     3,     2,     2,
       2,     2,     3,     2,     3,     3,     0,     2,     3,     2,
       2,     0,     2,     5,     4,     5,     0,     2,     0,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     2,     2,     2,
       2,     0,     3,     1,     2,     4,     3,     0,     1,     0,
       1,     3,     1,     1,     1,     1,     1,     0,     2,     1,
       1,     2,     1,     1,     3,     0,     2,     3,     0,     2,
       1,     1,     1,     1,     4,     3,     4,     3,     2,     3,
       3,     0,     2,     3,     2,     1,     2,     4,     4,     3,
       3,     4,     0,     2,     2,     0,     2,     1,     1,     4,
       4,     2,     3,     3,     0,     2,     4,     2,     1,     2,
       1,     0,     2,     3,     3,     4,     1,     1,     0,     2,
       2,     2,     2,     2,     3,     3,     0,     2,     1,     1,
       4,     8,     0,     3,     2,     5,     5,     0,     2,     3,
       3,     3,     3,     2,     6,     0,     2,     4,     4,     0,
       3,     6,     0,     2,     5,     0,     2,     0,     4,     0,
       2,     2,     4,     4,     2,     4,     1,     1,     0,     3,
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     2,     1,     1
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
        case 23:
#line 248 "defparse.y" /* yacc.c:1646  */
    {}
#line 2368 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 252 "defparse.y" /* yacc.c:1646  */
    {}
#line 2374 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 256 "defparse.y" /* yacc.c:1646  */
    {}
#line 2380 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 260 "defparse.y" /* yacc.c:1646  */
    {bCaseSensDEF = 1;}
#line 2386 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 261 "defparse.y" /* yacc.c:1646  */
    {bCaseSensDEF = 0;}
#line 2392 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 265 "defparse.y" /* yacc.c:1646  */
    {}
#line 2398 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 269 "defparse.y" /* yacc.c:1646  */
    {}
#line 2404 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 274 "defparse.y" /* yacc.c:1646  */
    {}
#line 2410 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 279 "defparse.y" /* yacc.c:1646  */
    {
     if ((yyvsp[-4].string).DoDelete) free ((yyvsp[-4].string).str);
     }
#line 2418 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 285 "defparse.y" /* yacc.c:1646  */
    {}
#line 2424 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 286 "defparse.y" /* yacc.c:1646  */
    {}
#line 2430 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 287 "defparse.y" /* yacc.c:1646  */
    {}
#line 2436 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 288 "defparse.y" /* yacc.c:1646  */
    {}
#line 2442 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 289 "defparse.y" /* yacc.c:1646  */
    {}
#line 2448 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 290 "defparse.y" /* yacc.c:1646  */
    {}
#line 2454 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 291 "defparse.y" /* yacc.c:1646  */
    {}
#line 2460 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 292 "defparse.y" /* yacc.c:1646  */
    {}
#line 2466 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 296 "defparse.y" /* yacc.c:1646  */
    {}
#line 2472 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 297 "defparse.y" /* yacc.c:1646  */
    {}
#line 2478 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 298 "defparse.y" /* yacc.c:1646  */
    {}
#line 2484 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 302 "defparse.y" /* yacc.c:1646  */
    {}
#line 2490 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 303 "defparse.y" /* yacc.c:1646  */
    {}
#line 2496 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 307 "defparse.y" /* yacc.c:1646  */
    {}
#line 2502 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 308 "defparse.y" /* yacc.c:1646  */
    {}
#line 2508 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 312 "defparse.y" /* yacc.c:1646  */
    {}
#line 2514 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 313 "defparse.y" /* yacc.c:1646  */
    {}
#line 2520 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 318 "defparse.y" /* yacc.c:1646  */
    {}
#line 2526 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 319 "defparse.y" /* yacc.c:1646  */
    {}
#line 2532 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 323 "defparse.y" /* yacc.c:1646  */
    {
    strcpy(pdb->designName,(yyvsp[-1].string).str);
    if ((yyvsp[-1].string).DoDelete) free((yyvsp[-1].string).str);
    }
#line 2541 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 331 "defparse.y" /* yacc.c:1646  */
    { 
    }
#line 2548 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 336 "defparse.y" /* yacc.c:1646  */
    {
    strcpy(pdb->technoName,(yyvsp[-1].string).str);
    if ((yyvsp[-1].string).DoDelete)free((yyvsp[-1].string).str)  ;
    }
#line 2557 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 343 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[-1].string);if ((yyvsp[-1].string).DoDelete) free ((yyvsp[-1].string).str);}
#line 2563 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 347 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[-1].string);if ((yyvsp[-1].string).DoDelete) free ((yyvsp[-1].string).str);}
#line 2569 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 351 "defparse.y" /* yacc.c:1646  */
    { }
#line 2575 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 355 "defparse.y" /* yacc.c:1646  */
    {
    //pUnitsPtr->DEFDistConv = (int)($4+1e-5);
    }
#line 2583 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 360 "defparse.y" /* yacc.c:1646  */
    {
                        strcpy(tempRowName,(yyvsp[0].string).str);
                        if ((yyvsp[0].string).DoDelete) free ((yyvsp[0].string).str);
                        }
#line 2592 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 366 "defparse.y" /* yacc.c:1646  */
    {
                   sprintf(tempRowName,"Anonymous Row %d",
                                       pp->tempAllRows.size());
                   }
#line 2601 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 372 "defparse.y" /* yacc.c:1646  */
    {
                                 pTempSite=NULL;
                                 tempNumSites = unsigned(-1);
                                 tempRowSpacing = unsigned(-1);
                                 tempRowOrig.x=tempRowOrig.y=DBL_MAX;
                                 tempRowDir = 
                                    static_cast<dbRow::Dir>(INT_MAX);
                                 // don't know how to give impossible value
                                 // to tempOrient
                                 }
#line 2616 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 384 "defparse.y" /* yacc.c:1646  */
    {}
#line 2622 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 385 "defparse.y" /* yacc.c:1646  */
    {}
#line 2628 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 389 "defparse.y" /* yacc.c:1646  */
    {
                            ParserLEFDEF::siteHashMapType::iterator iS 
                                         = pp->siteHash.find((yyvsp[-1].string).str);
                            if (iS == pp->siteHash.end())
                                {
                                sprintf(errtxt,"Site %s not found in line %d "
                                               "of DEF file",(yyvsp[-1].string).str,
                                               defLinenum);
                                abkfatal(0,errtxt);
                                }
                             else
                                pTempSite = (*iS).second;
                            if ((yyvsp[-1].string).DoDelete) free ((yyvsp[-1].string).str);
                            }
#line 2647 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 406 "defparse.y" /* yacc.c:1646  */
    {
        pp->tempAllRows.push_back(new dbRow(*pTempSite,
                                            tempRowOrig,
                                            tempRowDir,
                                            tempRowSpacing,
                                            tempNumSites,
                                            tempRowName,
                                            tempOrient));
        }
#line 2661 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 419 "defparse.y" /* yacc.c:1646  */
    {
             tempRowOrig.x = (yyvsp[-10].dval);
             tempRowOrig.y = (yyvsp[-9].dval);
             if ((yyvsp[-6].dval) > 1)
                 {
                 tempNumSites=unsigned((yyvsp[-6].dval));
                 tempRowDir = dbRow::HORIZ;
                 tempRowSpacing = unsigned((yyvsp[-2].dval));
                 if ((yyvsp[-4].dval)>1)
                     {
                     sprintf(errtxt,"ambiguous row direction in "
                                    "line %d of DEF",defLinenum);
                     abkfatal(0,errtxt);
                     }
                 }
             else if ((yyvsp[-4].dval) > 1)
                 {
                 tempNumSites=unsigned((yyvsp[-4].dval));
                 tempRowDir = dbRow::VERT;
                 tempRowSpacing = unsigned((yyvsp[-1].dval));
                 }
             else
                 { // 1x1 case
                 if ((yyvsp[-6].dval) !=1 || (yyvsp[-4].dval) != 1)
                     {
                     sprintf(errtxt,"illegal num sites in "
                                    "line %d of DEF",defLinenum);
                     abkfatal(0,errtxt);
                     }
                 tempNumSites=1;
                 tempRowDir = dbRow::HORIZ;  //rather strange, but
                                             //shouldn't matter
                 tempRowSpacing = 0;

/*                 if ($9>0)
                     {
                     if ($10!=0)
                         {
                         sprintf(errtxt,"ambiguous row direction in "
                                        "line %d of DEF",defLinenum);
                         abkfatal(0,errtxt);
                         }
                     tempRowDir = dbRow::HORIZ;
                     tempRowSpacing = $9;
                     }

                else if ($10>0)
                     {
                     tempRowDir = dbRow::VERT;
                     tempRowSpacing = $10;
                     }

                else
                     {
                     sprintf(errtxt,"ambiguous row direction (1x1) in "
                                    "line %d of DEF",defLinenum);
                     abkfatal(0,errtxt);
                     }
*/
                 } //end 1x1 case
             }
#line 2727 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 482 "defparse.y" /* yacc.c:1646  */
    {tempOrient = Orient(0,true);if((yyvsp[0].string).DoDelete)free((yyvsp[0].string).str);}
#line 2733 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 483 "defparse.y" /* yacc.c:1646  */
    {tempOrient = Orient(90,true);if((yyvsp[0].string).DoDelete)free((yyvsp[0].string).str);}
#line 2739 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 484 "defparse.y" /* yacc.c:1646  */
    {tempOrient = Orient(180,true);if((yyvsp[0].string).DoDelete)free((yyvsp[0].string).str);}
#line 2745 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 485 "defparse.y" /* yacc.c:1646  */
    {tempOrient = Orient(270,true);if((yyvsp[0].string).DoDelete)free((yyvsp[0].string).str);}
#line 2751 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 486 "defparse.y" /* yacc.c:1646  */
    {tempOrient = Orient(0,false);}
#line 2757 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 487 "defparse.y" /* yacc.c:1646  */
    {tempOrient = Orient(90,false);}
#line 2763 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 488 "defparse.y" /* yacc.c:1646  */
    {tempOrient = Orient(180,false);}
#line 2769 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 489 "defparse.y" /* yacc.c:1646  */
    {tempOrient = Orient(270,false);}
#line 2775 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 493 "defparse.y" /* yacc.c:1646  */
    {
    pdb->context._bbox = (yyvsp[-1].bbox);
    }
#line 2783 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 499 "defparse.y" /* yacc.c:1646  */
    { }
#line 2789 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 503 "defparse.y" /* yacc.c:1646  */
    {  }
#line 2795 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 511 "defparse.y" /* yacc.c:1646  */
    { }
#line 2801 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 515 "defparse.y" /* yacc.c:1646  */
    { }
#line 2807 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 519 "defparse.y" /* yacc.c:1646  */
    { }
#line 2813 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 523 "defparse.y" /* yacc.c:1646  */
    {
//    pNetlist->netList.reserve($2); 
    }
#line 2821 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 533 "defparse.y" /* yacc.c:1646  */
    {
    bSpecial = false;
    tempPins.clear();
    strcpy(tempPinName,(yyvsp[0].string).str);
    if ((yyvsp[0].string).DoDelete) free((yyvsp[0].string).str);
    tempMasterPinUse[0] = '\0';
    tempMasterPinDir[0] = '\0';
    tempMpinBBox.clear();
    pTempPort = NULL;
    pTempLayer = NULL;
    tempLoc.x = tempLoc.y = DBL_MAX;
    tempLocValid = false;
    tempFixed    = false;
    tempOrient = Orient();
    tempNetUse = dbNetType::SIGNAL; //default added 9-11-97 mro
    tempPadClass = dbMasterCellType::PadUNKNOWN;
    }
#line 2843 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 553 "defparse.y" /* yacc.c:1646  */
    {

    bool isLogicalPin=true; // will be changed if pin has geometry

    if (pTempPort)
        {
        isLogicalPin=false;
        char mpinname[1023];
        strcpy(mpinname,"FakedMasterPinFor");
        strcat(mpinname,tempPinName);

        switch(tempNetUse)
            {
            case dbNetType::SIGNAL:
                strcpy(tempMasterPinUse,"SIGNAL");
                break;
            case dbNetType::ANALOG:
                strcpy(tempMasterPinUse,"ANALOG");
                break;
            case dbNetType::POWER:
                strcpy(tempMasterPinUse,"POWER");
                break;
            case dbNetType::GROUND:
                strcpy(tempMasterPinUse,"GROUND");
                break;
            case dbNetType::CLOCK:
                strcpy(tempMasterPinUse,"CLOCK");
                break;
            case dbNetType::UNKNOWN:
                strcpy(tempMasterPinUse,"");
                break;
            case dbNetType::TIEOFF:
            default:
                abkfatal(0,"Illegal use spec for external pin");
            }

        if (tempMpinBBox.isEmpty())
            {
            sprintf(errtxt,"In line %d of DEF file, I/O pin %s has"
                    " empty bounding box; adding (0,0) "
                    "to avoid crash",defLinenum,mpinname);
            abkwarn(0,errtxt);
            tempMpinBBox += Point(0,0);
            }

        pdb->design._pinLib.push_back(
                  pTempMasterPin = new dbMasterPin(mpinname,
                                                   tempMasterPinDir,
                                                   tempMasterPinUse,
                                                   "",
                                                   tempMpinBBox,
                                                   tempMpinBBox.getGeomCenter()
                                                   )
                                                   );

        if (pTempPort) pTempMasterPin->_ports.push_back(pTempPort);

        ctainerMasterPinsLocal tempMasterPins;
        tempMasterPins.push_back(pTempMasterPin);
        ctainerLayerGeoms      emptyLGs;

        char mcellname[1023];
        strcpy(mcellname,"FakedMasterCellFor");
        strcat(mcellname,tempPinName);

        pdb->design._cellLib.push_back(
                  pTempMasterCell = new dbMasterCell(mcellname,
                                                     dbMasterCellType::EXTPIN,
                                                     tempPadClass,
                                                     0.0,
                                                     0.0,
                                                     Point(0.0,0.0),
                                                     tempMasterPins,
                                                     emptyLGs,
                                                     Symmetry(false,false,false),
                                                     *(pp->pExtPinSite))
                                                     );

        pTempMasterPin->_cell = pTempMasterCell;
        pair<char const* const,dbMasterCell*> const &pref =
            pair<char const* const,dbMasterCell*>(
                                     tempstr=strdup(mcellname),
                                     pTempMasterCell) ;
                                 
        pp->stringsToClean.push_back(tempstr);
                                         

        pair<ParserLEFDEF::masterCellHashMapType::iterator,bool> p =
            pp->masterCellHash.insert(pref);

        if (!p.second)
            {
            sprintf(errtxt,"duplicate declaration of IO pin master cell %s "
                      "in line %d of DEF; ignored",tempCellName,defLinenum);
            abkfatal(0,errtxt);
            pdb->design._cellLib.pop_back();
            delete pTempMasterCell;
            }

        int numPins = pp->tempAllPins.size();

        pp->tempAllPins.push_back(pTempPin = new dbPin(*pTempMasterPin,
                                                         numPins));

        tempPins.clear();
        tempPins.push_back(pTempPin);

        strcpy(cellname,"FakedInstantiatedCellFor");
        strcat(cellname,tempPinName);

        int numCells = pp->tempAllCells.size();

        pp->tempAllCells.push_back(pTempCell = new dbCell(cellname,
                                                            numCells,
                                                            *pTempMasterCell,
                                                            tempPins) );

        pTempPin->_cell = pTempCell;
        pair<char const* const,dbCell*> const &pref0 =
              pair<char const* const,dbCell*>(
                                          tempstr=strdup(cellname),
                                          pTempCell) ;
        pp->stringsToClean.push_back(tempstr);
        pair<ParserLEFDEF::cellHashMapType::iterator,bool> p0 =
             pp->cellHash.insert(pref0);

        if (!p0.second)
            {
            sprintf(errtxt,"duplicate io pin name %s "
                           "in line %d of DEF",cellname,defLinenum);
            abkfatal(0,errtxt);
            pp->tempAllCells.pop_back();
            delete pTempCell;
            }

        pp->tempAllLocsValid.push_back(tempLocValid);
        pp->tempAllOrients.push_back(tempOrient);
        pp->tempAllLocs.push_back(tempLoc);

        if (tempFixed)
           pp->fixedCompIndices.push_back(pTempCell->getIndex());

        } // end creation of faked stuff for non-logical pin
    else
        {
        tempPins.clear();
        }



    strcpy(tempNetName,(yyvsp[-2].string).str);

    ParserLEFDEF::netHashMapType &condHash = (bSpecial)? pp->SnetHash
                                                       : pp->netHash;

    ParserLEFDEF::netHashMapType::iterator iN = condHash
                                                .find((char const*)tempNetName);

    if (iN == condHash.end())
        pTempNet=NULL;
     else
        pTempNet = (*iN).second;

    //LOOK! this code is almost identical to that in net_and_connections.
    //      how can duplication be avoided?

    if (!pTempNet)
        {
        pTempNet = new dbNet(tempNetName,
                             (bSpecial)?(runningSNetIdx++):(runningNetIdx++),
                             dbNetType(tempNetUse),
                             tempPins);

        if (bSpecial)
            pp->tempAllSNets.push_back(pTempNet);
        else
            pp->tempAllNets.push_back(pTempNet);

        pair<char const* const,dbNet*> const &pref1 =
              pair<char const* const,dbNet*>(
                                          tempstr=strdup(tempNetName),
                                          pTempNet) ;

        pp->stringsToClean.push_back(tempstr);
                                      
        pair<ParserLEFDEF::netHashMapType::iterator,bool> p1 =
             condHash.insert(pref1);

        if (!p1.second)
            {
            sprintf(errtxt,"internal error at net %s "
                           "in line %d of DEF",tempNetName,defLinenum);
            abkfatal(0,errtxt);
            }
        }
    else
        {
        // we have to add connections to an existing net
        ctainerPinsLocal::iterator iP;
        for (iP = tempPins.begin() ; iP != tempPins.end() ; iP++ )
            {
            pTempNet->_pins.push_back((*iP));
            }
        }

    if (isLogicalPin)
        pTempNet->_hasLogicalPin=true;

    ctainerPinsLocal::iterator iP;
    for (iP = tempPins.begin() ; iP != tempPins.end() ; iP++ )
        {
        dbPin &pin = *(*iP);
        if (pin._net)
            {
            sprintf(errtxt,"Pin %s of cell %s found on two nets, %s and %s",
                           pin.getMasterPinName(),
                           pin.getCell().getName(),
                           pin._net->getName(),
                           tempNetName);
            abkfatal(0,errtxt);
            }
        pin._net = pTempNet;
        }



    if ((yyvsp[-2].string).DoDelete)free((yyvsp[-2].string).str);
    }
#line 3076 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 784 "defparse.y" /* yacc.c:1646  */
    { }
#line 3082 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 788 "defparse.y" /* yacc.c:1646  */
    {}
#line 3088 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 791 "defparse.y" /* yacc.c:1646  */
    {}
#line 3094 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 792 "defparse.y" /* yacc.c:1646  */
    {}
#line 3100 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 793 "defparse.y" /* yacc.c:1646  */
    {}
#line 3106 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 794 "defparse.y" /* yacc.c:1646  */
    {}
#line 3112 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 795 "defparse.y" /* yacc.c:1646  */
    {}
#line 3118 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 798 "defparse.y" /* yacc.c:1646  */
    {}
#line 3124 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 801 "defparse.y" /* yacc.c:1646  */
    {bSpecial=true;}
#line 3130 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 805 "defparse.y" /* yacc.c:1646  */
    {              //note: this rule is used not only by ext_pin_layer_opt,
                     //but also by mult_layer_names (ultimately used for
                     //tracks)

      ParserLEFDEF::layerHashMapType::iterator iL =
                   pp->layerHash.find((yyvsp[0].string).str);

      if (iL == pp->layerHash.end())
         {
         sprintf(errtxt,"Layer %s not found in line %d "
                        "of DEF file",(yyvsp[0].string).str,defLinenum);
         abkfatal(0,errtxt);
         }
      else
         pTempLayer = (*iL).second;
      if ((yyvsp[0].string).DoDelete) free ((yyvsp[0].string).str);
      }
#line 3152 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 825 "defparse.y" /* yacc.c:1646  */
    {
                  tempMpinBBox = (yyvsp[0].bbox);

                  pTempPort = new dbLayerGeom(tempMpinBBox,
                                             *pTempLayer);

                  }
#line 3164 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 835 "defparse.y" /* yacc.c:1646  */
    {tempPadClass=dbMasterCellType::INPUT;
               strcpy(tempMasterPinDir,"OUTPUT");}
#line 3171 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 837 "defparse.y" /* yacc.c:1646  */
    {tempPadClass=dbMasterCellType::INOUT;
               strcpy(tempMasterPinDir,"INOUT");}
#line 3178 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 839 "defparse.y" /* yacc.c:1646  */
    {tempPadClass=dbMasterCellType::OUTPUT;
                strcpy(tempMasterPinDir,"INPUT");}
#line 3185 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 841 "defparse.y" /* yacc.c:1646  */
    {tempPadClass=dbMasterCellType::PadUNKNOWN;//LOOK! is this right?
                  strcpy(tempMasterPinDir,"INOUT");}
#line 3192 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 848 "defparse.y" /* yacc.c:1646  */
    {
    itLayer iL;
    for (iL=trackLayers.begin();iL!=trackLayers.end();iL++)
        {
        pp->tempAllTracks.push_back(new dbTrack(*(*iL),
                                                tempHoriz,
                                                (yyvsp[-6].dval),
                                                (yyvsp[-4].dval),
                                                (yyvsp[-2].dval)));
        }

    }
#line 3209 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 863 "defparse.y" /* yacc.c:1646  */
    {
    pTempLayer=NULL;
    trackLayers.clear();
    }
#line 3218 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 870 "defparse.y" /* yacc.c:1646  */
    {tempHoriz = true; if ((yyvsp[0].string).DoDelete) free((yyvsp[0].string).str);}
#line 3224 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 871 "defparse.y" /* yacc.c:1646  */
    {tempHoriz = false; if ((yyvsp[0].string).DoDelete) free((yyvsp[0].string).str);}
#line 3230 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 875 "defparse.y" /* yacc.c:1646  */
    {}
#line 3236 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 878 "defparse.y" /* yacc.c:1646  */
    {}
#line 3242 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 884 "defparse.y" /* yacc.c:1646  */
    {trackLayers.push_back(pTempLayer);}
#line 3248 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 888 "defparse.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-6].string).DoDelete) free((yyvsp[-6].string).str);
        }
#line 3256 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 897 "defparse.y" /* yacc.c:1646  */
    {pp->tempAllVias.reserve(pp->tempAllVias.size() + (int)((yyvsp[-1].dval)+.01));}
#line 3262 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 905 "defparse.y" /* yacc.c:1646  */
    {
    tempViaLGs.clear();
    pTempLayer=NULL;
    pTempVia=NULL;
    }
#line 3272 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 913 "defparse.y" /* yacc.c:1646  */
    {
        std::sort(tempViaLGs.begin(),tempViaLGs.end(),CompareLayerGeoms());

        if (pTempVia)
            { //via was declared in LEF, or perhaps earlier in DEF
            if (pTempVia->getGeometries().size() != tempViaLGs.size())
                {
                sprintf(errtxt,"Size of previously-declared via "
                               "geometries does not equal size of current "
                               "declaration, via name %s, line %d "
                               "of DEF",pTempVia->getName(),defLinenum);

                abkwarn(0,errtxt);
                }
            ctainerLayerGeoms::const_iterator iPrevLGs;

            ctainerLayerGeoms::const_iterator iViaLGs;

            for (iPrevLGs=pTempVia->getGeometries().begin(),
                 iViaLGs = tempViaLGs.begin();

                 iPrevLGs != pTempVia->getGeometries().end();

                 iPrevLGs++,iViaLGs++)
                     {
                     Rectangle r1 = *(*iViaLGs);
                     Rectangle r2 = *(*iPrevLGs);
                     if (fabs(r1.xMin - r2.xMin) > 1e-4
                         || fabs(r1.xMax - r2.xMax) > 1e-4
                         || fabs(r1.yMin - r2.yMin) > 1e-4
                         || fabs(r1.yMax - r2.yMax) > 1e-4)
                         {
                         sprintf(errtxt,"Possible mismatch in redundant "
                                        "via declarations, via name %s, "
                                        "line %d of DEF",pTempVia->getName(),
                                        defLinenum);
                         abkwarn(0,errtxt);
                         break;
                         } 
                     }

            //Now we have to clean up as the LGs won't be getting
            //into tempAllVias

            itLayerGeom iLG;

            for (iLG=tempViaLGs.begin();iLG!=tempViaLGs.end();iLG++)
                delete (*iLG);


            }
        else
            { // new via
            pp->tempAllVias.push_back(pTempVia = new dbVia(tempViaName,
                                                          -1.0, //resistance
                                                                //not given
                                                                //in DEF
                                                          tempViaLGs));
            pair<char const* const,dbVia*> const &pref =
                pair<char const* const,dbVia*>(
                                         tempstr=strdup(tempViaName),
                                         pTempVia) ;
                                 
            pp->stringsToClean.push_back(tempstr);
                                         

            pair<ParserLEFDEF::viaHashMapType::iterator,bool> p =
                pp->viaHash.insert(pref);

            if (!p.second)
                {
                abkfatal(0,"Internal error");
                }
            }
        }
#line 3352 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 990 "defparse.y" /* yacc.c:1646  */
    {}
#line 3358 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 993 "defparse.y" /* yacc.c:1646  */
    {pp->regions.reserve((yyvsp[-1].dval));}
#line 3364 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 996 "defparse.y" /* yacc.c:1646  */
    {}
#line 3370 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 997 "defparse.y" /* yacc.c:1646  */
    {}
#line 3376 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1000 "defparse.y" /* yacc.c:1646  */
    {}
#line 3382 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1004 "defparse.y" /* yacc.c:1646  */
    {pTempRegion = new parserRegion(runParRegIdx++);
                        pp->regions.push_back(pTempRegion); //for cleanup
                        pair<char const* const,parserRegion*> const &pref =
                              pair<char const* const,parserRegion*>(
                                                          tempstr=strdup((yyvsp[0].string).str),
                                                          pTempRegion) ;

                        pp->stringsToClean.push_back(tempstr);
                                          
                        pair<ParserLEFDEF::regionHashMapType::iterator,bool> p =
                             pp->regionHash.insert(pref);

                        if (!p.second)
                            {
                            sprintf(errtxt,"internal error at region %s "
                                           "in line %d of DEF",(yyvsp[0].string).str,defLinenum);
                            abkfatal(0,errtxt);
                            }
                        if ((yyvsp[0].string).DoDelete) free((yyvsp[0].string).str);
                        }
#line 3407 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1026 "defparse.y" /* yacc.c:1646  */
    {}
#line 3413 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1027 "defparse.y" /* yacc.c:1646  */
    {}
#line 3419 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1030 "defparse.y" /* yacc.c:1646  */
    {pTempRegion->boxes.push_back((yyvsp[0].bbox));}
#line 3425 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1034 "defparse.y" /* yacc.c:1646  */
    {
			   abkwarn(0,"Properties not supported in regions");
			   if(!strcmp((yyvsp[-1].string).str,"UTILIZATION"))
			     {
			       pTempRegion->utilConstraint = true;
			       pTempRegion->utilization = (double)(yyvsp[0].dval);
			     }
			   if ((yyvsp[-1].string).DoDelete) free ((yyvsp[-1].string).str);
			 }
#line 3439 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1045 "defparse.y" /* yacc.c:1646  */
    {}
#line 3445 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1056 "defparse.y" /* yacc.c:1646  */
    {}
#line 3451 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1059 "defparse.y" /* yacc.c:1646  */
    {}
#line 3457 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1060 "defparse.y" /* yacc.c:1646  */
    {}
#line 3463 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1064 "defparse.y" /* yacc.c:1646  */
    {
        tempViaLGs.push_back(new dbLayerGeom((yyvsp[0].bbox),
                                            *pTempLayer,
                                            true));
        }
#line 3473 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1072 "defparse.y" /* yacc.c:1646  */
    {
        if ((yyvsp[0].string).DoDelete) free ((yyvsp[0].string).str);
        }
#line 3481 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1079 "defparse.y" /* yacc.c:1646  */
    {
    lastX = (yyval.pt).x = (int)((yyvsp[-2].dval)); //*(pUnitsPtr->DEFDistConv)+1e-5);
    lastY = (yyval.pt).y = (int)((yyvsp[-1].dval)); //*(pUnitsPtr->DEFDistConv)+1e-5);
    }
#line 3490 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1084 "defparse.y" /* yacc.c:1646  */
    {
    (yyval.pt).x = lastX;
    lastY = (yyval.pt).y = (int)((yyvsp[-1].dval)); //*(pUnitsPtr->DEFDistConv)+1e-5);
    pathDirection = dbLayer::VERT;
    }
#line 3500 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1090 "defparse.y" /* yacc.c:1646  */
    {
    lastX = (yyval.pt).x = (int)((yyvsp[-2].dval)); //*(pUnitsPtr->DEFDistConv)+1e-5);
    (yyval.pt).y = lastY;
    pathDirection = dbLayer::HORIZ;
   }
#line 3510 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1096 "defparse.y" /* yacc.c:1646  */
    {
    (yyval.pt).x = lastX;
    (yyval.pt).y = lastY;
    pathDirection = dbLayer::VERT;
   }
#line 3520 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1103 "defparse.y" /* yacc.c:1646  */
    {(yyval.bbox).xMin=min((yyvsp[-1].pt).x,(yyvsp[0].pt).x);
              (yyval.bbox).yMin=min((yyvsp[-1].pt).y,(yyvsp[0].pt).y);
              (yyval.bbox).xMax=max((yyvsp[-1].pt).x,(yyvsp[0].pt).x);
              (yyval.bbox).yMax=max((yyvsp[-1].pt).y,(yyvsp[0].pt).y);}
#line 3529 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1110 "defparse.y" /* yacc.c:1646  */
    { }
#line 3535 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1117 "defparse.y" /* yacc.c:1646  */
    { //printf("parsed successfully \n");
    double dNumCells = (yyvsp[-1].dval);
    int    nNumCells = (int) dNumCells;

    if (dNumCells != (double) nNumCells)
        deferror("Nonintegral number of cells!\n");

    runningPinIdx = 0; 
    pp->tempAllCells.reserve((int)((yyvsp[-1].dval) * 1.2)); //20% leeway for extpins
    }
#line 3550 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1130 "defparse.y" /* yacc.c:1646  */
    {//printf("comps_rule parsed \n");
                          }
#line 3557 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1135 "defparse.y" /* yacc.c:1646  */
    {//printf("comp parsed \n");
    unsigned cellIdx=pp->tempAllCells.size();
    pp->tempAllCells.push_back(pTempCell = new dbCell(tempCellName,
                                                      cellIdx,
                                                      *pTempMaster,
                                                      tempPins) );

    ctainerPinsLocal::iterator iP;

    for (iP=tempPins.begin();iP!=tempPins.end();iP++)
        {
        (*iP)->_cell = pTempCell;
        }

    pair<char const* const,dbCell*> const &pref =
          pair<char const* const,dbCell*>(
                                      tempstr=strdup(tempCellName),
                                      pTempCell) ;
                                      
    pp->stringsToClean.push_back(tempstr);
         
    
    pair<ParserLEFDEF::cellHashMapType::iterator,bool> p =
         pp->cellHash.insert(pref);

    if (!p.second)
        {
        sprintf(errtxt,"duplicate declaration of cell %s "
                       "in line %d of DEF; ignoring"
                       " (could be an IO pin of the same name)"
                       ,tempCellName,defLinenum);
        abkfatal(0,errtxt);
        delete pTempCell;
        pp->tempAllCells.pop_back();
        }

    pp->tempAllLocsValid.push_back(tempLocValid);
    pp->tempAllOrients.push_back(tempOrient);
    pp->tempAllLocs.push_back(tempLoc);
    if (pTempRegion)
        {
        compRegionPair thisPair(pTempCell,pTempRegion);
        pp->compRegions.push_back(thisPair);
        }

    if (tempFixed)
       pp->fixedCompIndices.push_back(pTempCell->getIndex());

    }
#line 3611 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1187 "defparse.y" /* yacc.c:1646  */
    { //printf("comp_start parsed\n");
    }
#line 3618 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1192 "defparse.y" /* yacc.c:1646  */
    {
    tempPins.clear();
    strcpy(tempCellName,(yyvsp[-1].string).str);
    ParserLEFDEF::masterCellHashMapType::iterator iC 
                 = pp->masterCellHash.find((yyvsp[0].string).str);
    if (iC == pp->masterCellHash.end())
        {
        sprintf(errtxt,"Master Cell %s not found in line %d "
                       "of DEF file",(yyvsp[0].string).str,defLinenum);
        abkfatal(0,errtxt);
        }
     else
        pTempMaster = (*iC).second;


    ctainerMasterPinsLocal::const_iterator iP;

    for (iP = pTempMaster->pinsBegin();iP != pTempMaster->pinsEnd();iP++)
        {
        pp->tempAllPins.push_back(pTempPin = 
                                       new dbPin(*(*iP),runningPinIdx++));
        tempPins.push_back(pTempPin);

        }

    tempLoc.x = tempLoc.y = DBL_MAX;
    tempLocValid          = false;
    tempFixed             = false;
    tempOrient            = Orient();
    pTempRegion           = NULL;
    if ((yyvsp[-1].string).DoDelete) free ((yyvsp[-1].string).str);
    if ((yyvsp[0].string).DoDelete) free ((yyvsp[0].string).str);
    }
#line 3656 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1228 "defparse.y" /* yacc.c:1646  */
    { }
#line 3662 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1230 "defparse.y" /* yacc.c:1646  */
    {
    abkwarn(0,"Net connection specified in component\n");
    }
#line 3670 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1234 "defparse.y" /* yacc.c:1646  */
    {
    abkwarn(0,"Net connection specified in component\n");
    if ((yyvsp[0].string).DoDelete) free((yyvsp[0].string).str);
    }
#line 3679 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1241 "defparse.y" /* yacc.c:1646  */
    { //printf("comp_options parsed\n");
                                   }
#line 3686 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1245 "defparse.y" /* yacc.c:1646  */
    {abkwarn(0,"component GENERATE option ignored")}
#line 3692 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1247 "defparse.y" /* yacc.c:1646  */
    { //printf("comp_option parsed\n");
                      }
#line 3699 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 1255 "defparse.y" /* yacc.c:1646  */
    {
    if ((yyvsp[-1].string).DoDelete) free((yyvsp[-1].string).str);
    if ((yyvsp[0].string).DoDelete) free((yyvsp[0].string).str);
    }
#line 3708 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1262 "defparse.y" /* yacc.c:1646  */
    {
    if ((yyvsp[0].string).DoDelete) free((yyvsp[0].string).str);
    }
#line 3716 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 1268 "defparse.y" /* yacc.c:1646  */
    {
                    pTempRegion = new parserRegion(runParRegIdx++);
                    pTempRegion->boxes.push_back((yyvsp[0].bbox));
                    pp->regions.push_back(pTempRegion); //for cleanup
                    }
#line 3726 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1274 "defparse.y" /* yacc.c:1646  */
    {
                    ParserLEFDEF::regionHashMapType::iterator iR = 
                                pp->regionHash.find((char const*)((yyvsp[0].string).str));

                    if (iR == pp->regionHash.end())
                        {
                        pTempRegion=NULL;
                        sprintf(errtxt,"Region %s not found for component %s "
                                       "in line %d of DEF file",(yyvsp[0].string).str,
                                       tempCellName,defLinenum);
                        abkfatal(0,errtxt);
                        }
                     else
                        pTempRegion = (*iR).second;

                    if ((yyvsp[0].string).DoDelete) free ((yyvsp[0].string).str);
                    }
#line 3748 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 1295 "defparse.y" /* yacc.c:1646  */
    {
    if ((yyvsp[-2].string).DoDelete) free((yyvsp[-2].string).str);
    if ((yyvsp[0].string).DoDelete) free ((yyvsp[0].string).str);
    }
#line 3757 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 1302 "defparse.y" /* yacc.c:1646  */
    {
    //tempCellPtr->setCoord($2.x,$2.y);
    //if (tempCellPtr->getPlacementStatus()==StatusFIXED)
    //    {
    //    dbRectangle &Region = tempCellPtr->Region;
    //    Region.llx = Region.urx = $2.x;
    //    Region.lly = Region.ury = $2.y;
    //    }

    tempLoc = (yyvsp[-1].pt);
    }
#line 3773 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 1316 "defparse.y" /* yacc.c:1646  */
    {
        //tempCellPtr->setPlacementStatus(StatusFIXED);
        //pNetlist->incrementNumFixed();
        tempLocValid = true;
        tempFixed    = true;
        }
#line 3784 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1323 "defparse.y" /* yacc.c:1646  */
    {
        //tempCellPtr->setPlacementStatus(StatusCOVER);
        //pNetlist->incrementNumFixed();
        tempLocValid = true;
        tempFixed    = true;
        }
#line 3795 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1330 "defparse.y" /* yacc.c:1646  */
    {
        //tempCellPtr->setPlacementStatus(StatusPLACED);
        tempLocValid = true;
        }
#line 3804 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 1335 "defparse.y" /* yacc.c:1646  */
    {
        tempLocValid = false;
        }
#line 3812 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 1341 "defparse.y" /* yacc.c:1646  */
    { }
#line 3818 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 1345 "defparse.y" /* yacc.c:1646  */
    {
        //pNetlist->setNumCells(runningCellIdx);
        //pNetlist->sortCells();
        }
#line 3827 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 1352 "defparse.y" /* yacc.c:1646  */
    { //printf("nets_section parsed\n"); 
           }
#line 3834 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 1357 "defparse.y" /* yacc.c:1646  */
    { //printf("start_nets parsed\n");
    bInSNets=0;
    double numNets = (yyvsp[-1].dval);
    nNets = (int)numNets;
    if (numNets !=(double)(nNets))
        deferror("nonintegral number of nets!\n");

    pp->tempAllNets.reserve(pp->tempAllNets.size()+nNets);

    //pNetlist->createNets(nNets,nNetsSoFar);
    }
#line 3850 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1371 "defparse.y" /* yacc.c:1646  */
    { //printf("net_rules parsed\n"); 
                        }
#line 3857 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 1376 "defparse.y" /* yacc.c:1646  */
    { //printf("one_net parsed\n");
    *(const_cast<dbNetType*>(&(pTempNet->_type))) = dbNetType(tempNetUse);

    }
#line 3866 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1383 "defparse.y" /* yacc.c:1646  */
    { //printf("net_and_connection parsed\n");
    if (!pTempNet)
        {
        pTempNet = new dbNet(tempNetName,
                             (bInSNets)?(runningSNetIdx++):(runningNetIdx++),
                             dbNetType(dbNetType::UNKNOWN), //use is not set
                                                            //until net_options
                                                            //rule (or
                                                            // snet_options) 
                                                            // rule is parsed.
                             tempPins);

        if (bInSNets)
            {
            pp->tempAllSNets.push_back(pTempNet);
            }
        else
            pp->tempAllNets.push_back(pTempNet);

        pair<char const* const,dbNet*> const &pref =
              pair<char const* const,dbNet*>(
                                          tempstr=strdup(tempNetName),
                                          pTempNet) ;

        pp->stringsToClean.push_back(tempstr);

                                          
        ParserLEFDEF::netHashMapType &condHash = (bInSNets)? pp->SnetHash
                                                           : pp->netHash;
         
    
        pair<ParserLEFDEF::netHashMapType::iterator,bool> p =
             condHash.insert(pref);

        if (!p.second)
            {
            sprintf(errtxt,"internal error at net %s "
                           "in line %d of DEF",tempNetName,defLinenum);
            abkfatal(0,errtxt);
            }
        }
    else
        {
        // we have to add connections to an existing net from
        // an external pin
        ctainerPinsLocal::iterator iP;
        for (iP = tempPins.begin() ; iP != tempPins.end() ; iP++ )
            {
            dbPin &pin = *(*iP);
            if (pin._net)
                {
                if (pin._net!=pTempNet)
                   {
                   sprintf(errtxt,
                     "Pin %s of cell %s found on two nets, %s and %s"
                     " when adding connections to external pin",
                       pin.getMasterPinName(),
                       pin.getCell().getName(),
                       pin._net->getName(),
                       tempNetName);
                   abkfatal(0,errtxt);
                   }

                }
            else
                pTempNet->_pins.push_back((*iP));
            }
        }
    if (logicalPinReferenced)
        pTempNet->_hasLogicalPin=true;

    ctainerPinsLocal::iterator iP;
    for (iP = tempPins.begin() ; iP != tempPins.end() ; iP++ )
        {
        dbPin &pin = *(*iP);
        if (pin._net)
            {
            //const char * oldName=pin._net->getName();
            if (pin._net != pTempNet)
                {
                sprintf(errtxt,"Pin %s of cell %s found on two nets, %s and %s",
                               pin.getMasterPinName(),
                               pin.getCell().getName(),
                               pin._net->getName(),
                               tempNetName);
                abkfatal(0,errtxt);
                }
            }
        pin._net = pTempNet;
        }
    }
#line 3962 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1477 "defparse.y" /* yacc.c:1646  */
    {

    logicalPinReferenced=false;

    strcpy(tempNetName,(yyvsp[0].string).str);
    tempNetUse = dbNetType::SIGNAL; //changed from UNKNOWN mro 9-11-97
    tempPins.clear();
    tempWiring.clear();
    pTempCell = NULL;
    if ((yyvsp[0].string).DoDelete) free((yyvsp[0].string).str);

    ParserLEFDEF::netHashMapType &condHash = (bInSNets)? pp->SnetHash
                                                       : pp->netHash;

    ParserLEFDEF::netHashMapType::iterator iN = condHash
                                           .find((char const*)tempNetName);

    if (iN == condHash.end())
        pTempNet=NULL;
     else
        pTempNet = (*iN).second;

    }
#line 3990 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 1503 "defparse.y" /* yacc.c:1646  */
    {}
#line 3996 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1507 "defparse.y" /* yacc.c:1646  */
    { //printf("net_connection parsed\n");

    bool isIOpin=false;

    if (strcmp((yyvsp[-3].string).str,"PIN")==0)
        {
        /*
        if (!pp->bIncludeLogicalPins ||
               (bInSNets && !pp->bIncludeSpecialPins) )
            {
            if ($2.DoDelete) free($2.str);
            if ($3.DoDelete) free($3.str);
            break;
            }
            */
        strcpy(cellname,"FakedInstantiatedCellFor");
        strcat(cellname,(yyvsp[-2].string).str);
        strcpy(pinname,"FakedMasterPinFor");
        strcat(pinname,(yyvsp[-2].string).str);
        isIOpin=true;
        }
    else
        {
        strcpy(cellname,(yyvsp[-3].string).str);
        strcpy(pinname,(yyvsp[-2].string).str);
        }


    ParserLEFDEF::cellHashMapType::iterator iC 
                 = pp->cellHash.find((const char*)cellname);

    if (iC == pp->cellHash.end())
        {
        if (!isIOpin)
            {
            sprintf(errtxt,"Cell %s not found in net %s in line %d "
                           "of DEF file",cellname,tempNetName,defLinenum);
            abkfatal(0,errtxt);
            }

        //assume this is a logical pin.  NOTE!!! if the name is
        //just spelled wrong, this code WILL NOT NOTICE!!! mro 001012

        logicalPinReferenced=true;

        }
     else
        {
        pTempCell = (*iC).second;

        ctainerPinsLocal::iterator iP;

        pTempPin = NULL;
        for (iP=pTempCell->_pins.begin();iP!=pTempCell->_pins.end();iP++)
            {
            if (strcmp((*iP)->_master._name,pinname)==0)
                {
                pTempPin = *iP;
                break;
                }
            }

        if (!pTempPin)
            {
            sprintf(errtxt,"Pin %s not found in cell %s in net %s in line %d "
                           "of DEF file",(yyvsp[-2].string).str,(yyvsp[-3].string).str,tempNetName,defLinenum);
            abkfatal(0,errtxt);
            }

        tempPins.push_back(pTempPin);
        }
    
    if ((yyvsp[-3].string).DoDelete) free((yyvsp[-3].string).str);
    if ((yyvsp[-2].string).DoDelete) free((yyvsp[-2].string).str);
    }
#line 4076 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1583 "defparse.y" /* yacc.c:1646  */
    {
    if ((yyvsp[-1].string).DoDelete) free ((yyvsp[-1].string).str);
    }
#line 4084 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1587 "defparse.y" /* yacc.c:1646  */
    {   
        if ((yyvsp[-2].string).DoDelete) free ((yyvsp[-2].string).str);
        if ((yyvsp[-1].string).DoDelete) free ((yyvsp[-1].string).str);
        }
#line 4093 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1603 "defparse.y" /* yacc.c:1646  */
    {  }
#line 4099 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1605 "defparse.y" /* yacc.c:1646  */
    { }
#line 4105 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1607 "defparse.y" /* yacc.c:1646  */
    { }
#line 4111 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1609 "defparse.y" /* yacc.c:1646  */
    {
        if ((yyvsp[0].string).DoDelete) free ((yyvsp[0].string).str);
        }
#line 4119 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1613 "defparse.y" /* yacc.c:1646  */
    {
        if ((yyvsp[0].string).DoDelete) free ((yyvsp[0].string).str);
        }
#line 4127 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1617 "defparse.y" /* yacc.c:1646  */
    {
        if ((yyvsp[0].string).DoDelete) free ((yyvsp[0].string).str);
        }
#line 4135 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1621 "defparse.y" /* yacc.c:1646  */
    {
	  pTempNet->_weight = double((yyvsp[0].dval));
	}
#line 4143 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1625 "defparse.y" /* yacc.c:1646  */
    { }
#line 4149 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 1627 "defparse.y" /* yacc.c:1646  */
    {
        }
#line 4156 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1630 "defparse.y" /* yacc.c:1646  */
    {}
#line 4162 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1633 "defparse.y" /* yacc.c:1646  */
    {}
#line 4168 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1636 "defparse.y" /* yacc.c:1646  */
    {tempNetUse = dbNetType::SIGNAL;}
#line 4174 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1637 "defparse.y" /* yacc.c:1646  */
    {tempNetUse = dbNetType::POWER;}
#line 4180 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1638 "defparse.y" /* yacc.c:1646  */
    {tempNetUse = dbNetType::GROUND;}
#line 4186 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1639 "defparse.y" /* yacc.c:1646  */
    {tempNetUse = dbNetType::CLOCK;}
#line 4192 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1640 "defparse.y" /* yacc.c:1646  */
    {tempNetUse = dbNetType::TIEOFF;}
#line 4198 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1641 "defparse.y" /* yacc.c:1646  */
    {tempNetUse = dbNetType::ANALOG;}
#line 4204 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1645 "defparse.y" /* yacc.c:1646  */
    { }
#line 4210 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1647 "defparse.y" /* yacc.c:1646  */
    { }
#line 4216 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1649 "defparse.y" /* yacc.c:1646  */
    { }
#line 4222 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1654 "defparse.y" /* yacc.c:1646  */
    { 
    }
#line 4229 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1660 "defparse.y" /* yacc.c:1646  */
    {  }
#line 4235 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1664 "defparse.y" /* yacc.c:1646  */
    {
    }
#line 4242 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1670 "defparse.y" /* yacc.c:1646  */
    {
    if (!bInSNets)
        break;     // We don't process regular wiring
    unsigned i;

    //Take care of final rectangle

    if (fabs(wireMinX-wireMaxX) > 1e-4 || fabs(wireMinY-wireMaxY) > 1e-4)
        {
        BBoxExtended b(wireMinX-tempWidth/2,wireMinY-tempWidth/2,
                        wireMaxX+tempWidth/2,wireMaxY+tempWidth/2);

        wireGeoms.push_back(b);
                                  
        wrongWay.push_back(pathDirection != pTempLayer->getDirection());
       }

    for (i=0;i<wireGeoms.size();i++)
        {
        //Next block says:  If we have overlapping rectangles, pare
        //redundant pieces off the wrong-way-routed wires.

        if (wrongWay[i])
           {
           if (i>0)
               wireGeoms[i].snip(wireGeoms[i-1]);
           if (i<wireGeoms.size()-1)
               wireGeoms[i].snip(wireGeoms[i+1]);
           }

        tempWiring.push_back(new dbLayerGeom(wireGeoms[i],*pTempLayer));
        }
    }
#line 4280 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1706 "defparse.y" /* yacc.c:1646  */
    {
                        tempWidth=(yyvsp[-2].dval);
                        wireGeoms.clear();
                        wrongWay.clear();
                        }
#line 4290 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1712 "defparse.y" /* yacc.c:1646  */
    {
                    if (bInSNets)
                        {
                        sprintf(errtxt,"In line %d of DEF, special wiring "
                                       "given in regular wiring format",
                                        defLinenum);
                        abkfatal(0,errtxt);
                        }

                    }
#line 4305 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1725 "defparse.y" /* yacc.c:1646  */
    {}
#line 4311 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1730 "defparse.y" /* yacc.c:1646  */
    {}
#line 4317 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1733 "defparse.y" /* yacc.c:1646  */
    {}
#line 4323 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1736 "defparse.y" /* yacc.c:1646  */
    {}
#line 4329 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1737 "defparse.y" /* yacc.c:1646  */
    {}
#line 4335 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1738 "defparse.y" /* yacc.c:1646  */
    {}
#line 4341 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1739 "defparse.y" /* yacc.c:1646  */
    {}
#line 4347 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1744 "defparse.y" /* yacc.c:1646  */
    {lastPoint=(yyvsp[0].pt);
                    pathDirection = oldPathDirection = dbLayer::NOPREFERRED;
                    wireMinX=wireMaxX=(yyvsp[0].pt).x;
                    wireMinY=wireMaxY=(yyvsp[0].pt).y;}
#line 4356 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1755 "defparse.y" /* yacc.c:1646  */
    {

    if (pathDirection != oldPathDirection 
         && oldPathDirection != dbLayer::NOPREFERRED)
         {
         BBoxExtended b(wireMinX-tempWidth/2,wireMinY-tempWidth/2,
                        wireMaxX+tempWidth/2,wireMaxY+tempWidth/2);

         wireGeoms.push_back(b);
                                  
         wrongWay.push_back(oldPathDirection != pTempLayer->getDirection());

         wireMinX = wireMaxX = lastPoint.x;
         wireMinY = wireMaxY = lastPoint.y;
         }

    lastPoint = (yyvsp[0].pt);
    if ((yyvsp[0].pt).x<wireMinX) wireMinX = (yyvsp[0].pt).x;
    if ((yyvsp[0].pt).x>wireMaxX) wireMaxX = (yyvsp[0].pt).x;
    if ((yyvsp[0].pt).y<wireMinY) wireMinY = (yyvsp[0].pt).y;
    if ((yyvsp[0].pt).y>wireMaxY) wireMaxY = (yyvsp[0].pt).y;
    oldPathDirection = pathDirection;
    }
#line 4384 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1780 "defparse.y" /* yacc.c:1646  */
    {
    typedef ctainerLayerGeoms const &rlg;
    rlg LGref(pTempVia->getGeometries());

    ctainerLayerGeoms::const_iterator iLG;

    for (iLG=LGref.begin();iLG!=LGref.end();iLG++)
        {
        BBox b=*(*iLG);
        b.TranslateBy(lastPoint);
        tempWiring.push_back(new dbLayerGeom(b,(*iLG)->getLayer()));
        }

    }
#line 4403 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 1797 "defparse.y" /* yacc.c:1646  */
    { }
#line 4409 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 1801 "defparse.y" /* yacc.c:1646  */
    {
    if (!pTempVia)
        {
        sprintf(errtxt,"via %s not found in line %d of DEF",
                 tempViaName,defLinenum);
        abkfatal(pTempVia,errtxt);
        }
    }
#line 4422 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 1817 "defparse.y" /* yacc.c:1646  */
    {
    strcpy(tempViaName,(yyvsp[0].string).str);
    if ((yyvsp[0].string).DoDelete) free((yyvsp[0].string).str);
    ParserLEFDEF::viaHashMapType::iterator iV
                   = pp->viaHash.find((char const*)tempViaName);
    if (iV == pp->viaHash.end())
         pTempVia = NULL;
    else
         pTempVia = (*iV).second;
    }
#line 4437 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1837 "defparse.y" /* yacc.c:1646  */
    {
    *(const_cast<dbNetType*>(&(pTempNet->_type))) = dbNetType(tempNetUse);
    pTempNet->_wiring = tempWiring;
    }
#line 4446 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 1853 "defparse.y" /* yacc.c:1646  */
    {
    if ((yyvsp[-1].string).DoDelete) free((yyvsp[-1].string).str);
    }
#line 4454 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1859 "defparse.y" /* yacc.c:1646  */
    { }
#line 4460 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 256:
#line 1863 "defparse.y" /* yacc.c:1646  */
    {
    if ((yyvsp[-1].string).DoDelete) free((yyvsp[-1].string).str);
    }
#line 4468 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 257:
#line 1869 "defparse.y" /* yacc.c:1646  */
    {
    double numSNets = (yyvsp[-1].dval);
    nSNets = (int)numSNets;
    if (nSNets !=(double)(nSNets))
        deferror("nonintegral number of special nets!\n");
//    pNetlist->createSNets(nSNets,nSNetsSoFar);
    bInSNets=1; 
    }
#line 4481 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1880 "defparse.y" /* yacc.c:1646  */
    {
    }
#line 4488 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 260:
#line 1888 "defparse.y" /* yacc.c:1646  */
    { }
#line 4494 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1899 "defparse.y" /* yacc.c:1646  */
    {
    if ((yyvsp[0].string).DoDelete) free ((yyvsp[0].string).str);
    }
#line 4502 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1905 "defparse.y" /* yacc.c:1646  */
    {}
#line 4508 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1910 "defparse.y" /* yacc.c:1646  */
    {
    if ((yyvsp[-1].string).DoDelete) free((yyvsp[-1].string).str);
    if ((yyvsp[0].string).DoDelete) free((yyvsp[0].string).str);
    }
#line 4517 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1915 "defparse.y" /* yacc.c:1646  */
    { }
#line 4523 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1917 "defparse.y" /* yacc.c:1646  */
    { }
#line 4529 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1919 "defparse.y" /* yacc.c:1646  */
    {
    if ((yyvsp[-1].string).DoDelete) free((yyvsp[-1].string).str);
    if ((yyvsp[0].string).DoDelete) free((yyvsp[0].string).str);
    }
#line 4538 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 1927 "defparse.y" /* yacc.c:1646  */
    { }
#line 4544 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 1931 "defparse.y" /* yacc.c:1646  */
    {
    if ((yyvsp[-1].string).DoDelete) free ((yyvsp[-1].string).str);
    }
#line 4552 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 279:
#line 1943 "defparse.y" /* yacc.c:1646  */
    {
    if ((yyvsp[-2].string).DoDelete) free ((yyvsp[-2].string).str); //KLUDGE
    if ((yyvsp[-1].string).DoDelete) free ((yyvsp[-1].string).str);
    }
#line 4561 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 280:
#line 1950 "defparse.y" /* yacc.c:1646  */
    {
    if ((yyvsp[-2].string).DoDelete) free ((yyvsp[-2].string).str); //KLUDGE
    if ((yyvsp[-1].string).DoDelete) free ((yyvsp[-1].string).str);
    }
#line 4570 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 281:
#line 1956 "defparse.y" /* yacc.c:1646  */
    {}
#line 4576 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 1959 "defparse.y" /* yacc.c:1646  */
    {}
#line 4582 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 1965 "defparse.y" /* yacc.c:1646  */
    { }
#line 4588 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 286:
#line 1973 "defparse.y" /* yacc.c:1646  */
    {
    if (nNumGroupRegions>1)
        {
        sprintf(errtxt,"More than one \"+ REGION\" keyword for a single"
                       " group before line %d in DEF.  This is contrary"
                       "\nto my reading of the DEF manual (but obviously"
                       " I wasn't really sure :-)  Please contact Mike. ",
                       defLinenum);
        abkfatal(0,errtxt);
        }

    if (bSoft)
        {
        //LOOK! this is somewhat wasteful in the case that the region
        //has been specified here by points (instead of by name); we're
        //creating essentially the same object twice.

        if (pTempRegion) //region specified)
            pTempRegion = new parserRegion(runParRegIdx++,
                                           *pTempRegion,
                                           tempMaxX,tempMaxY,tempMaxHp);
        else
            pTempRegion = new parserRegion(runParRegIdx++,false,DBL_MAX,true,
                                           tempMaxX,tempMaxY,tempMaxHp);

        pp->regions.push_back(pTempRegion);
        }

    std::vector<dbCell*>::iterator iC;
    for (iC=tempCompCache.begin();iC!=tempCompCache.end();iC++)
        {
        compRegionPair thisPair((*iC),pTempRegion);
//      compRegionPair thisPair(pTempCell,pTempRegion);
        pp->compRegions.push_back(thisPair);
        }

    }
#line 4630 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 2013 "defparse.y" /* yacc.c:1646  */
    {
    tempCompCache.clear();
    bSoft        = false;
    pTempRegion  = NULL;
    pTempCell    = NULL;
    nNumGroupRegions  = 0;
    tempMaxX = tempMaxY = tempMaxHp = int(pdb->context._bbox.getHalfPerim());
    strcpy(tempGroupName,(yyvsp[0].string).str);
    if ((yyvsp[0].string).DoDelete) free ((yyvsp[0].string).str);
    }
#line 4645 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 288:
#line 2025 "defparse.y" /* yacc.c:1646  */
    {}
#line 4651 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 289:
#line 2026 "defparse.y" /* yacc.c:1646  */
    {}
#line 4657 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 290:
#line 2030 "defparse.y" /* yacc.c:1646  */
    {
    ParserLEFDEF::cellHashMapType::iterator iC 
                 = pp->cellHash.find((yyvsp[0].string).str);

    if (iC == pp->cellHash.end())
        {
        sprintf(errtxt,"Cell %s of group %s not found in line %d "
                       "of DEF file",(yyvsp[0].string).str,tempGroupName,defLinenum);
        strcat(errtxt,"\nPossible regular expression?  If so please"
                      " edit file; regexps not supported");
        abkfatal(0,errtxt);
        }
     else
        pTempCell = (*iC).second;
    tempCompCache.push_back(pTempCell);
    if ((yyvsp[0].string).DoDelete) free ((yyvsp[0].string).str);
    }
#line 4679 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 292:
#line 2050 "defparse.y" /* yacc.c:1646  */
    {}
#line 4685 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 293:
#line 2054 "defparse.y" /* yacc.c:1646  */
    {
                   bSoft = true;
                   }
#line 4693 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 294:
#line 2057 "defparse.y" /* yacc.c:1646  */
    {nNumGroupRegions++;}
#line 4699 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 295:
#line 2059 "defparse.y" /* yacc.c:1646  */
    {
                  abkwarn(0,"Properties not supported in groups");
                  if ((yyvsp[-1].string).DoDelete) free ((yyvsp[-1].string).str);
                  }
#line 4708 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 296:
#line 2065 "defparse.y" /* yacc.c:1646  */
    {
                  pTempRegion = new parserRegion(runParRegIdx++);
                  pTempRegion->boxes.push_back((yyvsp[0].bbox));
                  pp->regions.push_back(pTempRegion); //for cleanup
                  }
#line 4718 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 297:
#line 2071 "defparse.y" /* yacc.c:1646  */
    {
                    ParserLEFDEF::regionHashMapType::iterator iR = 
                                pp->regionHash.find((char const*)((yyvsp[0].string).str));

                    if (iR == pp->regionHash.end())
                        {
                        pTempRegion=NULL;
                        sprintf(errtxt,"Region %s not found "
                                       "in line %d of DEF file",(yyvsp[0].string).str,
                                       defLinenum);
                        abkfatal(pTempRegion!=NULL,errtxt);
                        }
                     else
                        pTempRegion = (*iR).second;

                    if ((yyvsp[0].string).DoDelete) free ((yyvsp[0].string).str);
                  }
#line 4740 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 299:
#line 2091 "defparse.y" /* yacc.c:1646  */
    {}
#line 4746 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 300:
#line 2095 "defparse.y" /* yacc.c:1646  */
    {tempMaxX=int((yyvsp[0].dval));}
#line 4752 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 2096 "defparse.y" /* yacc.c:1646  */
    {tempMaxY=int((yyvsp[0].dval));}
#line 4758 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 302:
#line 2097 "defparse.y" /* yacc.c:1646  */
    {tempMaxHp=int((yyvsp[0].dval));}
#line 4764 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 303:
#line 2100 "defparse.y" /* yacc.c:1646  */
    {}
#line 4770 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 304:
#line 2103 "defparse.y" /* yacc.c:1646  */
    {}
#line 4776 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 2106 "defparse.y" /* yacc.c:1646  */
    {}
#line 4782 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 307:
#line 2110 "defparse.y" /* yacc.c:1646  */
    {}
#line 4788 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 308:
#line 2113 "defparse.y" /* yacc.c:1646  */
    {}
#line 4794 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 309:
#line 2114 "defparse.y" /* yacc.c:1646  */
    {}
#line 4800 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 314:
#line 2126 "defparse.y" /* yacc.c:1646  */
    {
    if ((yyvsp[0].string).DoDelete) free ((yyvsp[0].string).str);
    }
#line 4808 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 315:
#line 2130 "defparse.y" /* yacc.c:1646  */
    { 
        if ((yyvsp[-3].string).DoDelete) free ((yyvsp[-3].string).str);
        if ((yyvsp[-2].string).DoDelete) free ((yyvsp[-2].string).str);
        if ((yyvsp[-1].string).DoDelete) free ((yyvsp[-1].string).str);
        if ((yyvsp[0].string).DoDelete) free ((yyvsp[0].string).str);
        }
#line 4819 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 316:
#line 2139 "defparse.y" /* yacc.c:1646  */
    { 
    if ((yyvsp[-3].string).DoDelete) free ((yyvsp[-3].string).str);
    }
#line 4827 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 319:
#line 2149 "defparse.y" /* yacc.c:1646  */
    { }
#line 4833 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 320:
#line 2151 "defparse.y" /* yacc.c:1646  */
    { }
#line 4839 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 321:
#line 2153 "defparse.y" /* yacc.c:1646  */
    { }
#line 4845 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 322:
#line 2155 "defparse.y" /* yacc.c:1646  */
    { }
#line 4851 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 323:
#line 2159 "defparse.y" /* yacc.c:1646  */
    { }
#line 4857 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 324:
#line 2163 "defparse.y" /* yacc.c:1646  */
    {}
#line 4863 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 326:
#line 2168 "defparse.y" /* yacc.c:1646  */
    {}
#line 4869 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 327:
#line 2173 "defparse.y" /* yacc.c:1646  */
    {}
#line 4875 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 328:
#line 2178 "defparse.y" /* yacc.c:1646  */
    {
    if ((yyvsp[-2].string).DoDelete) free ((yyvsp[-2].string).str);
    if ((yyvsp[-1].string).DoDelete) free ((yyvsp[-1].string).str);
    }
#line 4884 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 331:
#line 2191 "defparse.y" /* yacc.c:1646  */
    {}
#line 4890 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 334:
#line 2201 "defparse.y" /* yacc.c:1646  */
    {
      if ((yyvsp[-3].string).DoDelete) free ((yyvsp[-3].string).str); //$2.str is either PIN or a comp name
      if ((yyvsp[-2].string).DoDelete) free ((yyvsp[-2].string).str); //$3.str is pin name
      }
#line 4899 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 336:
#line 2208 "defparse.y" /* yacc.c:1646  */
    {}
#line 4905 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 337:
#line 2212 "defparse.y" /* yacc.c:1646  */
    {}
#line 4911 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 338:
#line 2213 "defparse.y" /* yacc.c:1646  */
    {
    }
#line 4918 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 340:
#line 2219 "defparse.y" /* yacc.c:1646  */
    {}
#line 4924 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 341:
#line 2224 "defparse.y" /* yacc.c:1646  */
    {
     if ((yyvsp[-1].string).DoDelete) free ((yyvsp[-1].string).str); //$1.str is property name
     }
#line 4932 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 342:
#line 2230 "defparse.y" /* yacc.c:1646  */
    {}
#line 4938 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 343:
#line 2231 "defparse.y" /* yacc.c:1646  */
    {}
#line 4944 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 344:
#line 2232 "defparse.y" /* yacc.c:1646  */
    {}
#line 4950 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 345:
#line 2234 "defparse.y" /* yacc.c:1646  */
    {if ((yyvsp[-2].string).DoDelete) free ((yyvsp[-2].string).str);}
#line 4956 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 346:
#line 2238 "defparse.y" /* yacc.c:1646  */
    {}
#line 4962 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 347:
#line 2239 "defparse.y" /* yacc.c:1646  */
    {}
#line 4968 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 349:
#line 2244 "defparse.y" /* yacc.c:1646  */
    {if ((yyvsp[0].string).DoDelete) free ((yyvsp[0].string).str);}
#line 4974 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 351:
#line 2249 "defparse.y" /* yacc.c:1646  */
    {if ((yyvsp[0].string).DoDelete) free ((yyvsp[0].string).str);}
#line 4980 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 353:
#line 2254 "defparse.y" /* yacc.c:1646  */
    {}
#line 4986 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 354:
#line 2259 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 4992 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 355:
#line 2260 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 4998 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 356:
#line 2261 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5004 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 357:
#line 2262 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5010 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 358:
#line 2263 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5016 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 359:
#line 2264 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5022 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 360:
#line 2265 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5028 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 361:
#line 2266 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5034 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 362:
#line 2267 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5040 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 363:
#line 2268 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5046 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 364:
#line 2269 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5052 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 365:
#line 2270 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5058 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 366:
#line 2271 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5064 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 367:
#line 2272 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5070 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 368:
#line 2273 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5076 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 369:
#line 2274 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5082 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 370:
#line 2275 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5088 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 371:
#line 2276 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5094 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 372:
#line 2277 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5100 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 373:
#line 2278 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5106 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 374:
#line 2279 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5112 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 375:
#line 2280 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5118 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 376:
#line 2281 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5124 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 377:
#line 2282 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5130 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 378:
#line 2283 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5136 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 379:
#line 2284 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5142 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 380:
#line 2285 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5148 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 381:
#line 2286 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5154 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 382:
#line 2287 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5160 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 383:
#line 2288 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5166 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 384:
#line 2289 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5172 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 385:
#line 2290 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5178 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 386:
#line 2291 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5184 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 387:
#line 2292 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5190 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 388:
#line 2293 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5196 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 389:
#line 2294 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5202 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 390:
#line 2295 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5208 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 391:
#line 2296 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5214 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 392:
#line 2297 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5220 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 393:
#line 2298 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5226 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 394:
#line 2299 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5232 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 395:
#line 2300 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5238 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 396:
#line 2301 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5244 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 397:
#line 2302 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5250 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 398:
#line 2303 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5256 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 399:
#line 2304 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5262 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 400:
#line 2305 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5268 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 401:
#line 2306 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5274 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 402:
#line 2307 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5280 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 403:
#line 2308 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5286 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 404:
#line 2309 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5292 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 405:
#line 2310 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5298 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 406:
#line 2311 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5304 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 407:
#line 2312 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5310 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 408:
#line 2313 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5316 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 409:
#line 2314 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5322 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 410:
#line 2315 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5328 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 411:
#line 2316 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5334 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 412:
#line 2317 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5340 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 413:
#line 2318 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5346 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 414:
#line 2319 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5352 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 415:
#line 2320 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5358 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 416:
#line 2321 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5364 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 417:
#line 2322 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5370 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 418:
#line 2323 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5376 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 419:
#line 2324 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5382 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 420:
#line 2325 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5388 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 421:
#line 2326 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5394 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 422:
#line 2327 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5400 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 423:
#line 2328 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5406 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 424:
#line 2329 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5412 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 425:
#line 2330 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5418 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 426:
#line 2331 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5424 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 427:
#line 2332 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5430 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 428:
#line 2333 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5436 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 429:
#line 2334 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5442 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 430:
#line 2335 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5448 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 431:
#line 2336 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5454 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 432:
#line 2337 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5460 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 433:
#line 2338 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5466 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 434:
#line 2339 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5472 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 435:
#line 2340 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5478 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 436:
#line 2341 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5484 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 437:
#line 2342 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5490 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 438:
#line 2343 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5496 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 439:
#line 2344 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5502 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 440:
#line 2345 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5508 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 441:
#line 2346 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5514 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 442:
#line 2347 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5520 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 443:
#line 2348 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5526 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 444:
#line 2349 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5532 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 445:
#line 2350 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5538 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 446:
#line 2351 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5544 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 447:
#line 2352 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5550 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 448:
#line 2353 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5556 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 449:
#line 2354 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5562 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 450:
#line 2355 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5568 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 451:
#line 2356 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5574 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 452:
#line 2357 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5580 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 453:
#line 2358 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5586 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 454:
#line 2359 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5592 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 455:
#line 2360 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5598 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 456:
#line 2361 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5604 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 457:
#line 2362 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5610 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 458:
#line 2363 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5616 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 459:
#line 2364 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5622 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 460:
#line 2365 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5628 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 461:
#line 2366 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5634 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 462:
#line 2367 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5640 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 463:
#line 2368 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5646 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 464:
#line 2369 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5652 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 465:
#line 2370 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5658 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 466:
#line 2371 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5664 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 467:
#line 2372 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5670 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 468:
#line 2373 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5676 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 469:
#line 2374 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5682 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 470:
#line 2375 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5688 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 471:
#line 2376 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5694 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 472:
#line 2377 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5700 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 473:
#line 2378 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5706 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 474:
#line 2379 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5712 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 475:
#line 2380 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5718 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 476:
#line 2381 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5724 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 477:
#line 2382 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5730 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 478:
#line 2383 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5736 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 479:
#line 2384 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5742 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 480:
#line 2385 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5748 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 482:
#line 2390 "defparse.y" /* yacc.c:1646  */
    {if ((yyvsp[0].string).DoDelete) free ((yyvsp[0].string).str);}
#line 5754 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 483:
#line 2393 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5760 "defparse.tab.c" /* yacc.c:1646  */
    break;

  case 484:
#line 2394 "defparse.y" /* yacc.c:1646  */
    {(yyval.string)=(yyvsp[0].string);}
#line 5766 "defparse.tab.c" /* yacc.c:1646  */
    break;


#line 5770 "defparse.tab.c" /* yacc.c:1646  */
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
#line 2396 "defparse.y" /* yacc.c:1906  */




void deferror (const char *s) 
{ 
  printf("%s\n At line number %d of DEF\n",s,defLinenum+1);
  fprintf(stderr,"%s\n At line number %d of DEF\n",s,defLinenum+1);
  fflush(stdout);
  fflush(stderr);
  exit(-1);
}


