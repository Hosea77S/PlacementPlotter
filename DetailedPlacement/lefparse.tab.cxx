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
#define yyparse         lefparse
#define yylex           leflex
#define yyerror         leferror
#define yydebug         lefdebug
#define yynerrs         lefnerrs

#define yylval          leflval
#define yychar          lefchar

/* Copy the first part of user declarations.  */
#line 1 "lefparse.y" /* yacc.c:339  */

#ifdef _MSC_VER
#pragma warning (disable:4786)
#endif

#include <limits.h>
//#include <malloc.h>
#include <stdlib.h>
//#include "DB.h"
#include "plGeom.h"
#include "placement.h"
#include "LEFDEFpoint.h"
#include "parserLEFDEF.h"
//#include "hash.h"
#include "localhash.h"
#include "sgi_hash_map.h"

using std::pair;
using std::vector;

typedef struct lexsstr
    {
    char *str;
    int  DoDelete;
    } lexemeStruct;

void leferror(char*);
int leflex(void);
//extern MasterCellHashTable *pMasterTable;
int          NumMasterCells;
//dbMasterRec *currentCellPtr;
//dbMasterPinRec *currentPinPtr;
//dbLayerGeometryList *pLGeomList;
//dbGeometry *pGeom;
//dbLayDirType tempDirection;
float Dummy;
char  DummyString[511];
extern int lefLinenum;
static char errtxt[1023];
static char tempDir[1023];
static char tempUse[1023];
static char tempShape[1023];
static BBox tempBBox;
static char *tempstr;
//static ctainerLayerGeoms emptyLGs;
int bCaseSens=0;
dbLayer *pTempLayer;
dbSite  *pTempSite;

//extern dbUnits   *pUnitsPtr;
//extern dbTimeNetlistRec *pNetlist;
//extern dbWrapper *pWrapperPtr;

extern ParserLEFDEF *pp;
extern DB           *pdb;

///block of globals for dbLayer ctor

static unsigned runningLayerIdx=0;
static dbLayer::Type tempLayerType;
static dbLayer::Dir tempLayerDir;
static unsigned tempPitch;
static unsigned tempLayerWidth;
static unsigned tempLayerHeight;
static unsigned tempThickness;
static unsigned tempSpacing;
static unsigned tempShrinkage;
static double   tempCapMult;
static double   tempEdgeCap;
static double   tempUnitRes;
static double   tempUnitCap;
static char     tempLayerName[1023];
//end dbLayer globals

//block of globals for dbSite ctor
static char         tempSiteName[1023];
static unsigned     tempSiteHeight;
static unsigned     tempSiteWidth;
static dbSite::Type tempSiteType;
static Symmetry     tempSymmetry;
//end dbSite globals

//block of globals for dbMasterCell ctor
static dbMasterCellType::MClass      tempMacroType;
static dbMasterCellType::PadSubClass tempPadClass;
static LEFDEFpoint                   tempCellOrig;
static ctainerMasterPinsLocal        tempPins;
//static ctainerMasterPinsLocal        emptyPins;
static ctainerLayerGeoms             tempObs;
static dbMasterCell                 *pTempCell;
static dbMasterCell                 *pTempEquivCell;
equivClassesMasterCells             *pTempCellQSpace;
static char                          tempCellName[1023];
static unsigned                      tempCellWidth;
static unsigned                      tempCellHeight;
enum EqClassFoundType {EQ_CLASS_FOUND,EQ_CLASS_NOT_FOUND,AMBIG_EQ_FOUND} ;

static EqClassFoundType                                 leqFound,
                                                        eeqFound,
                                                        *pLocalFound;
eqClassMasterCells *pCurrentLEQclass,*pCurrentEEQclass,**ppLocalClass;
static dbMasterCell                  *pLEQCell,*pEEQCell,**ppLocalEqCell;
//end dbMasterCell globals

//block of globals for dbMasterPin ctor
static char tempPinName[1023];
static ctainerLayerGeoms tempPorts;
static dbMasterPin *pTempPin;
static EqClassFoundType pinClassFound;
eqClassMasterPins *pCurrentPinClass;
dbMasterPin       *pLEQpin;
static dbMasterPin                  *pMustJoinPin;
//end dbMasterPin globals

//globals for geometries
static BBox tempLGrectangle;
static BBox tempGeomBoundingBox;
static vector<Point> tempPolygon;
static bool inPolygon; //true means we're looking at a polygon geom;
                       //false means a path

static ctainerLayerGeoms *pLGeomList;
static unsigned tempLGwidth;
//end globals for geometries

//globals for vias
static char              tempViaName[1023];
static double            tempViaResis;
static ctainerLayerGeoms tempViaLGs;
static dbVia            *pTempVia;
//end globals for vias

static bool warnMultSpace=true;


#ifndef BISON_DEB
int lefdebug; //in this case this is useless; it's just so we
              //don't get an error trying to initialize it.
#endif

#line 215 "lefparse.tab.c" /* yacc.c:339  */

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
   by #include "lefparse.tab.h".  */
#ifndef YY_LEF_LEFPARSE_TAB_H_INCLUDED
# define YY_LEF_LEFPARSE_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int lefdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    K_ID = 258,
    K_ORDBR1 = 259,
    K_ORDBR2 = 260,
    K_RISERS = 261,
    K_RISECS = 262,
    K_RISESATT1 = 263,
    K_RISET0 = 264,
    K_FALLRS = 265,
    K_FALLCS = 266,
    K_FALLSATT1 = 267,
    K_FALLT0 = 268,
    K_VARIABLE = 269,
    K_INTRINSIC = 270,
    K_SOURCE = 271,
    K_CASE = 272,
    K_ON = 273,
    K_OFF = 274,
    K_LAYER = 275,
    K_TYPE = 276,
    K_ROUTING = 277,
    K_MSLICE = 278,
    K_CUT = 279,
    K_OVERLAP = 280,
    K_END = 281,
    K_PITCH = 282,
    K_WIDTH = 283,
    K_SPACING = 284,
    K_DIRECTION = 285,
    K_RES = 286,
    K_CAP = 287,
    K_RPERSQ = 288,
    K_CPERSQ = 289,
    K_HEIGHT = 290,
    K_THICKNESS = 291,
    K_SHRINKAGE = 292,
    K_CAPMULTIPLIER = 293,
    K_EDGECAP = 294,
    K_HORIZ = 295,
    K_VERT = 296,
    K_VIA = 297,
    K_DEFAULT = 298,
    K_SITE = 299,
    K_PAD = 300,
    K_CORE = 301,
    K_ORIGIN = 302,
    K_SYMMETRY = 303,
    K_X = 304,
    K_Y = 305,
    K_R90 = 306,
    K_SIZE = 307,
    K_BY = 308,
    K_ARRAY = 309,
    K_N = 310,
    K_S = 311,
    K_W = 312,
    K_E = 313,
    K_FN = 314,
    K_FE = 315,
    K_FW = 316,
    K_FS = 317,
    K_DO = 318,
    K_STEP = 319,
    K_CANPLACE = 320,
    K_CANNOTOCCUPY = 321,
    K_TRACKS = 322,
    K_GCELL = 323,
    K_FLOORPLAN = 324,
    K_DEFAULTCAP = 325,
    K_MINPINS = 326,
    K_WIRECAP = 327,
    K_MACRO = 328,
    K_CLASS = 329,
    K_LEQ = 330,
    K_EEQ = 331,
    K_COVER = 332,
    K_RING = 333,
    K_BLOCK = 334,
    K_ENDCAP = 335,
    K_FEEDTHRU = 336,
    K_TIEHIGH = 337,
    K_TIELOW = 338,
    K_INPUT = 339,
    K_OUTPUT = 340,
    K_INOUT = 341,
    K_POWER = 342,
    K_SPACER = 343,
    K_PRE = 344,
    K_POST = 345,
    K_TO = 346,
    K_TOPLEFT = 347,
    K_TOPRIGHT = 348,
    K_BOTTOMLEFT = 349,
    K_BOTTOMRIGHT = 350,
    K_PIN = 351,
    K_USE = 352,
    K_SHAPE = 353,
    K_SETUPTIME = 354,
    K_SKIP = 355,
    K_ABUTMENT = 356,
    K_SIGNAL = 357,
    K_GROUND = 358,
    K_CLOCK = 359,
    K_TIEOFF = 360,
    K_ANALOG = 361,
    K_DATA = 362,
    K_PORT = 363,
    K_OBS = 364,
    K_RECT = 365,
    K_PATH = 366,
    K_POLYGON = 367,
    K_ITERATE = 368,
    K_TIMING = 369,
    K_UNATE = 370,
    K_INVERT = 371,
    K_NONINVERT = 372,
    K_NONUNATE = 373,
    K_RISE = 374,
    K_FALL = 375,
    K_TRANSITION = 376,
    K_DELAY = 377,
    K_FROMPIN = 378,
    K_TOPIN = 379,
    K_LIBRARY = 380,
    K_DESIGN = 381,
    K_PLUS = 382,
    K_MINUS = 383,
    K_STAR = 384,
    K_ASGN = 385,
    K_ACTIVE = 386,
    K_ANTENNAAREAFACTOR = 387,
    K_ANTENNALENGTHFACTOR = 388,
    K_ANTENNAMETALAREA = 389,
    K_ANTENNAMETALLENGTH = 390,
    K_ANTENNASIZE = 391,
    K_ANYEDGE = 392,
    K_CORRECTIONFACTOR = 393,
    K_CORRECTIONTABLE = 394,
    K_CURRENT = 395,
    K_CURRENTSOURCE = 396,
    K_DATABASE = 397,
    K_DIELECTRIC = 398,
    K_EDGERATE = 399,
    K_EDGERATETHRESHOLD1 = 400,
    K_EDGERATETHRESHOLD2 = 401,
    K_EDGERATESCALEFACTOR = 402,
    K_FALLTHRESH = 403,
    K_FALLSATCUR = 404,
    K_FALLSLEWLIMIT = 405,
    K_FALLVOLTAGETHRESHOLD = 406,
    K_FOREIGN = 407,
    K_FUNCTION = 408,
    K_GENERATE = 409,
    K_HOLD = 410,
    K_INOUTPINANTENNASIZE = 411,
    K_INPUTPINANTENNASIZE = 412,
    K_INPUTNOISEMARGIN = 413,
    K_INTEGER = 414,
    K_IRDROP = 415,
    K_IV_TABLES = 416,
    K_LEAKAGE = 417,
    K_MAXDELAY = 418,
    K_MAXLOAD = 419,
    K_METALOVERHANG = 420,
    K_MICRONS = 421,
    K_MILLIAMPS = 422,
    K_MILLIWATTS = 423,
    K_MINFEATURE = 424,
    K_MUSTJOIN = 425,
    K_NANOSECONDS = 426,
    K_NEGEDGE = 427,
    K_NOISETABLE = 428,
    K_NONDEFAULTRULE = 429,
    K_OHMS = 430,
    K_OFFSET = 431,
    K_OUTPUTRESISTANCE = 432,
    K_OUTPUTPINANTENNASIZE = 433,
    K_OUTPUTNOISEMARGIN = 434,
    K_OVERHANG = 435,
    K_PICOFARADS = 436,
    K_POSEDGE = 437,
    K_PROPERTY = 438,
    K_PROPERTYDEFINITIONS = 439,
    K_PULLDOWNRES = 440,
    K_RANGE = 441,
    K_REAL = 442,
    K_RESISTIVE = 443,
    K_RISETHRESH = 444,
    K_RISESATCUR = 445,
    K_RISESLEWLIMIT = 446,
    K_RISEVOLTAGETHRESHOLD = 447,
    K_SAMENET = 448,
    K_SETUP = 449,
    K_STACK = 450,
    K_STRING = 451,
    K_STRUCTURE = 452,
    K_TABLE = 453,
    K_TABLEAXIS = 454,
    K_TABLEENTRIES = 455,
    K_TABLEDIMENSION = 456,
    K_TIEOFFR = 457,
    K_TIME = 458,
    K_TRANSITIONTIME = 459,
    K_TRISTATE = 460,
    K_TOPOFSTACKONLY = 461,
    K_UNIVERSALNOISEMARGIN = 462,
    K_USER = 463,
    K_UNITS = 464,
    K_VERSION = 465,
    K_VHI = 466,
    K_VIARULE = 467,
    K_VICTIMLENGTH = 468,
    K_VICTIMNOISE = 469,
    K_VLO = 470,
    K_VOLTAGE = 471,
    K_VOLTS = 472,
    K_WIREEXTENSION = 473,
    K_DIVIDERCHAR = 474,
    K_BUSBITCHARS = 475,
    K_LENGTHTHRESHOLD = 476,
    K_USELENGTHTHRESHOLD = 477,
    K_COMMA = 478,
    K_SEMCOL = 479,
    K_DOT_DOT = 480,
    K_DOT = 481,
    K_COLON = 482,
    NUMBER = 483,
    QUOTED_STR = 484
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 142 "lefparse.y" /* yacc.c:355  */

    int keyword;
    float fval;
    int ival;
    lexemeStruct lexeme;
    unsigned uval;
    LEFDEFpoint pt;
    void *ignore;
    LEFDEFrectangle rectVal;

#line 496 "lefparse.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE leflval;

int lefparse (void);

#endif /* !YY_LEF_LEFPARSE_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 511 "lefparse.tab.c" /* yacc.c:358  */

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1929

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  230
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  220
/* YYNRULES -- Number of rules.  */
#define YYNRULES  659
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1094

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   484

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
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   395,   395,   396,   398,   400,   403,   405,   406,   407,
     408,   409,   410,   411,   412,   413,   414,   415,   416,   417,
     418,   419,   420,   421,   422,   423,   424,   428,   433,   437,
     441,   445,   449,   453,   457,   460,   462,   466,   473,   474,
     475,   476,   480,   481,   482,   486,   487,   491,   492,   496,
     497,   501,   502,   506,   509,   511,   515,   516,   517,   518,
     519,   520,   521,   524,   527,   533,   539,   545,   551,   557,
     563,   572,   576,   581,   584,   587,   589,   593,   600,   711,
     734,   736,   740,   741,   742,   743,   744,   745,   746,   747,
     748,   749,   750,   751,   752,   753,   754,   760,   768,   769,
     770,   771,   774,   776,   780,   782,   783,   784,   788,   789,
     791,   793,   794,   795,   799,   800,   801,   805,   806,   807,
     808,   812,   813,   814,   818,   824,   833,   874,   892,   972,
     996,  1002,  1004,  1008,  1009,  1010,  1068,  1069,  1070,  1071,
    1096,  1097,  1098,  1099,  1100,  1101,  1102,  1103,  1104,  1105,
    1106,  1107,  1108,  1109,  1110,  1111,  1112,  1113,  1114,  1115,
    1116,  1117,  1118,  1118,  1119,  1120,  1121,  1122,  1124,  1126,
    1130,  1132,  1136,  1138,  1139,  1141,  1146,  1147,  1148,  1153,
    1154,  1155,  1156,  1157,  1158,  1159,  1162,  1163,  1167,  1170,
    1179,  1179,  1184,  1186,  1190,  1195,  1199,  1239,  1245,  1246,
    1250,  1267,  1273,  1278,  1279,  1280,  1281,  1282,  1286,  1289,
    1293,  1302,  1306,  1306,  1309,  1309,  1313,  1317,  1321,  1325,
    1326,  1330,  1339,  1343,  1369,  1376,  1395,  1407,  1409,  1419,
    1423,  1424,  1428,  1429,  1434,  1439,  1440,  1441,  1444,  1447,
    1450,  1453,  1455,  1456,  1462,  1463,  1467,  1468,  1469,  1473,
    1474,  1478,  1480,  1485,  1486,  1487,  1488,  1489,  1490,  1491,
    1492,  1493,  1494,  1497,  1501,  1502,  1503,  1507,  1508,  1512,
    1515,  1517,  1520,  1522,  1533,  1534,  1535,  1539,  1540,  1544,
    1545,  1549,  1554,  1558,  1567,  1582,  1588,  1590,  1594,  1597,
    1599,  1610,  1616,  1618,  1622,  1626,  1627,  1628,  1629,  1632,
    1634,  1638,  1639,  1640,  1641,  1643,  1644,  1645,  1646,  1647,
    1648,  1649,  1650,  1651,  1652,  1658,  1659,  1673,  1674,  1678,
    1679,  1683,  1684,  1689,  1700,  1750,  1762,  1791,  1792,  1795,
    1797,  1801,  1802,  1803,  1804,  1805,  1809,  1813,  1814,  1818,
    1825,  1826,  1829,  1831,  1834,  1836,  1840,  1851,  1852,  1856,
    1857,  1861,  1864,  1866,  1870,  1871,  1872,  1875,  1877,  1881,
    1888,  1891,  1893,  1896,  1898,  1902,  1903,  1904,  1912,  1915,
    1917,  1923,  1924,  1925,  1929,  1932,  1934,  1938,  1939,  1940,
    1944,  1953,  1961,  1965,  1968,  1971,  1973,  1977,  1978,  1979,
    1983,  1987,  1990,  1995,  1999,  2003,  2004,  2008,  2012,  2016,
    2020,  2024,  2027,  2031,  2032,  2036,  2040,  2046,  2058,  2091,
    2092,  2096,  2097,  2098,  2103,  2104,  2111,  2115,  2116,  2120,
    2121,  2122,  2126,  2137,  2141,  2145,  2149,  2150,  2154,  2155,
    2156,  2157,  2157,  2159,  2160,  2165,  2168,  2187,  2192,  2193,
    2194,  2195,  2196,  2197,  2198,  2199,  2206,  2210,  2213,  2214,
    2217,  2219,  2222,  2223,  2229,  2230,  2234,  2238,  2242,  2247,
    2248,  2252,  2253,  2267,  2269,  2272,  2282,  2286,  2287,  2291,
    2295,  2297,  2298,  2299,  2300,  2301,  2302,  2303,  2304,  2305,
    2306,  2307,  2308,  2309,  2310,  2311,  2312,  2313,  2314,  2315,
    2316,  2317,  2318,  2319,  2320,  2321,  2322,  2323,  2324,  2325,
    2326,  2327,  2328,  2329,  2330,  2331,  2332,  2333,  2334,  2335,
    2336,  2337,  2338,  2339,  2340,  2341,  2342,  2343,  2344,  2345,
    2346,  2347,  2348,  2349,  2350,  2351,  2352,  2353,  2354,  2355,
    2356,  2357,  2358,  2359,  2360,  2361,  2362,  2363,  2364,  2365,
    2366,  2367,  2368,  2369,  2370,  2371,  2372,  2373,  2374,  2375,
    2376,  2377,  2378,  2379,  2380,  2381,  2382,  2383,  2384,  2385,
    2386,  2387,  2388,  2389,  2390,  2391,  2392,  2393,  2394,  2395,
    2396,  2397,  2398,  2399,  2400,  2401,  2402,  2403,  2404,  2405,
    2406,  2407,  2408,  2409,  2410,  2411,  2412,  2413,  2414,  2415,
    2416,  2417,  2418,  2419,  2420,  2421,  2422,  2423,  2424,  2425,
    2426,  2427,  2428,  2429,  2430,  2431,  2432,  2433,  2434,  2435,
    2436,  2437,  2438,  2439,  2440,  2441,  2442,  2443,  2444,  2445,
    2446,  2447,  2448,  2449,  2450,  2451,  2452,  2453,  2454,  2455,
    2456,  2457,  2458,  2459,  2460,  2461,  2462,  2463,  2464,  2465,
    2466,  2467,  2468,  2469,  2470,  2471,  2472,  2473,  2474,  2475,
    2476,  2477,  2478,  2479,  2480,  2481,  2482,  2483,  2484,  2485
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "K_ID", "K_ORDBR1", "K_ORDBR2",
  "K_RISERS", "K_RISECS", "K_RISESATT1", "K_RISET0", "K_FALLRS",
  "K_FALLCS", "K_FALLSATT1", "K_FALLT0", "K_VARIABLE", "K_INTRINSIC",
  "K_SOURCE", "K_CASE", "K_ON", "K_OFF", "K_LAYER", "K_TYPE", "K_ROUTING",
  "K_MSLICE", "K_CUT", "K_OVERLAP", "K_END", "K_PITCH", "K_WIDTH",
  "K_SPACING", "K_DIRECTION", "K_RES", "K_CAP", "K_RPERSQ", "K_CPERSQ",
  "K_HEIGHT", "K_THICKNESS", "K_SHRINKAGE", "K_CAPMULTIPLIER", "K_EDGECAP",
  "K_HORIZ", "K_VERT", "K_VIA", "K_DEFAULT", "K_SITE", "K_PAD", "K_CORE",
  "K_ORIGIN", "K_SYMMETRY", "K_X", "K_Y", "K_R90", "K_SIZE", "K_BY",
  "K_ARRAY", "K_N", "K_S", "K_W", "K_E", "K_FN", "K_FE", "K_FW", "K_FS",
  "K_DO", "K_STEP", "K_CANPLACE", "K_CANNOTOCCUPY", "K_TRACKS", "K_GCELL",
  "K_FLOORPLAN", "K_DEFAULTCAP", "K_MINPINS", "K_WIRECAP", "K_MACRO",
  "K_CLASS", "K_LEQ", "K_EEQ", "K_COVER", "K_RING", "K_BLOCK", "K_ENDCAP",
  "K_FEEDTHRU", "K_TIEHIGH", "K_TIELOW", "K_INPUT", "K_OUTPUT", "K_INOUT",
  "K_POWER", "K_SPACER", "K_PRE", "K_POST", "K_TO", "K_TOPLEFT",
  "K_TOPRIGHT", "K_BOTTOMLEFT", "K_BOTTOMRIGHT", "K_PIN", "K_USE",
  "K_SHAPE", "K_SETUPTIME", "K_SKIP", "K_ABUTMENT", "K_SIGNAL", "K_GROUND",
  "K_CLOCK", "K_TIEOFF", "K_ANALOG", "K_DATA", "K_PORT", "K_OBS", "K_RECT",
  "K_PATH", "K_POLYGON", "K_ITERATE", "K_TIMING", "K_UNATE", "K_INVERT",
  "K_NONINVERT", "K_NONUNATE", "K_RISE", "K_FALL", "K_TRANSITION",
  "K_DELAY", "K_FROMPIN", "K_TOPIN", "K_LIBRARY", "K_DESIGN", "K_PLUS",
  "K_MINUS", "K_STAR", "K_ASGN", "K_ACTIVE", "K_ANTENNAAREAFACTOR",
  "K_ANTENNALENGTHFACTOR", "K_ANTENNAMETALAREA", "K_ANTENNAMETALLENGTH",
  "K_ANTENNASIZE", "K_ANYEDGE", "K_CORRECTIONFACTOR", "K_CORRECTIONTABLE",
  "K_CURRENT", "K_CURRENTSOURCE", "K_DATABASE", "K_DIELECTRIC",
  "K_EDGERATE", "K_EDGERATETHRESHOLD1", "K_EDGERATETHRESHOLD2",
  "K_EDGERATESCALEFACTOR", "K_FALLTHRESH", "K_FALLSATCUR",
  "K_FALLSLEWLIMIT", "K_FALLVOLTAGETHRESHOLD", "K_FOREIGN", "K_FUNCTION",
  "K_GENERATE", "K_HOLD", "K_INOUTPINANTENNASIZE", "K_INPUTPINANTENNASIZE",
  "K_INPUTNOISEMARGIN", "K_INTEGER", "K_IRDROP", "K_IV_TABLES",
  "K_LEAKAGE", "K_MAXDELAY", "K_MAXLOAD", "K_METALOVERHANG", "K_MICRONS",
  "K_MILLIAMPS", "K_MILLIWATTS", "K_MINFEATURE", "K_MUSTJOIN",
  "K_NANOSECONDS", "K_NEGEDGE", "K_NOISETABLE", "K_NONDEFAULTRULE",
  "K_OHMS", "K_OFFSET", "K_OUTPUTRESISTANCE", "K_OUTPUTPINANTENNASIZE",
  "K_OUTPUTNOISEMARGIN", "K_OVERHANG", "K_PICOFARADS", "K_POSEDGE",
  "K_PROPERTY", "K_PROPERTYDEFINITIONS", "K_PULLDOWNRES", "K_RANGE",
  "K_REAL", "K_RESISTIVE", "K_RISETHRESH", "K_RISESATCUR",
  "K_RISESLEWLIMIT", "K_RISEVOLTAGETHRESHOLD", "K_SAMENET", "K_SETUP",
  "K_STACK", "K_STRING", "K_STRUCTURE", "K_TABLE", "K_TABLEAXIS",
  "K_TABLEENTRIES", "K_TABLEDIMENSION", "K_TIEOFFR", "K_TIME",
  "K_TRANSITIONTIME", "K_TRISTATE", "K_TOPOFSTACKONLY",
  "K_UNIVERSALNOISEMARGIN", "K_USER", "K_UNITS", "K_VERSION", "K_VHI",
  "K_VIARULE", "K_VICTIMLENGTH", "K_VICTIMNOISE", "K_VLO", "K_VOLTAGE",
  "K_VOLTS", "K_WIREEXTENSION", "K_DIVIDERCHAR", "K_BUSBITCHARS",
  "K_LENGTHTHRESHOLD", "K_USELENGTHTHRESHOLD", "K_COMMA", "K_SEMCOL",
  "K_DOT_DOT", "K_DOT", "K_COLON", "NUMBER", "QUOTED_STR", "$accept",
  "lef_file", "lef_rules", "rule", "end_lib_stmt", "version_stmt",
  "inant_stmt", "outant_stmt", "ioant_stmt", "busbitchar_stmt",
  "dividerchar_stmt", "propdefs_stmt", "propdefs_list", "propdef_item",
  "object_type", "prop_type", "poss_range", "poss_prop_val", "prop_val",
  "case_stmt", "units_stmt", "units_rules", "units_rule", "end_units",
  "units_time", "units_cap", "units_res", "units_power", "units_cur",
  "units_vlt", "units_db", "begin_case", "minfeature_stmt",
  "dielectric_stmt", "irdrop_stmt", "irtable_attr_list", "irtable_attr",
  "macro_stmt", "macro_id", "macro_body_list", "macro_body", "macro_size",
  "macro_class", "macro_core_subclass", "macro_pad_subclass",
  "macro_endcap_subclass", "macro_endcap_subclass_side", "source_class",
  "loeeq_start", "leq_or_eeq", "loeeq_string", "pin_stmt", "pin_id",
  "end_pin_id", "pin_attr_list", "pin_attr", "$@1", "direction",
  "pin_direction", "pin_shape", "net_pin_usage", "a_or_r", "port",
  "start_port", "obs_stmt", "$@2", "layer_geom_list", "layer_geom",
  "poss_layer_id_existing", "layer_id_existing", "layer", "geom",
  "layer_width", "rect", "rect_point", "point", "path", "$@3", "polygon",
  "$@4", "rect_iter", "path_iter", "polygon_iter", "point_list",
  "list_point", "lef_step_pattern", "via_geom", "via_id", "timing_stmt",
  "timing_attr_list", "timing_attr", "gen_timing_entry_list",
  "gen_timing_entry", "tbl_timing_entry", "tblax_spec123", "tbldim_spec",
  "tblax_spec", "tblent_spec", "tim_tbl_prefix", "h_or_s", "n_or_p_edge",
  "d_or_t", "poss_unate", "timing_entry", "unate_spec", "unate", "r_or_f",
  "min_max", "slew1_opt", "slew2_opt", "pin_spec", "number_list",
  "min_typ_max_list", "min_typ_max", "from_pin_spec", "to_pin_spec",
  "end_macro_id", "spacing_stmt", "same_net_attr_list", "same_net_attr",
  "stack_opt", "layer_stmt", "layer_body_opt", "layer_type",
  "layer_type_entry", "layer_attr_list", "layer_attr",
  "poss_layer_space_subset", "layer_space_subset", "poss_ult", "h_or_v",
  "layer_id_new", "end_layer_id", "lef_via_start", "lef_via_stmt",
  "default", "via_attr_list", "via_attr", "property_assignment_list",
  "property_name_val_list", "property_name_val", "rect_list",
  "point_orient_opt", "orient_opt", "end_via_id", "viarule_stmt",
  "nongenerate_stmt", "viarule_layer_stmt", "viarule_layer_attr_list",
  "viarule_layer_attr", "viarule_via_stmt_list", "viarule_via_stmt",
  "generate_stmt", "viarulegen_layer_stmt", "viarulegen_layer_attr_list",
  "viarulegen_layer_attr", "nondefault_stmt", "nondefault_list",
  "nondefault_element", "nondefault_layer", "nondefault_layer_attr_list",
  "nondefault_layer_attr", "nondefault_via", "nondefault_spacing",
  "crosstalk_stmt", "noise_thresholds", "noise", "threshold_list",
  "threshold", "noisetable", "noisetable_id", "end_nt", "nt_edgerate",
  "nt_outputres", "nt_viclnthnois_list", "nt_viclnthnois", "nt_viclnth",
  "nt_vicnois", "correctiontable", "crcntable_id", "end_ct",
  "ct_viclnthcorrfact_list", "ct_viclnthcorrfact", "ct_corrfact",
  "lef_site_new", "lef_site_stmt", "site_attr_list", "site_attr",
  "site_class", "symmetry", "symmetry_attr_list", "symmetry_attr",
  "end_site_id", "lef_array_stmt", "array_id", "end_array_id",
  "array_attr_list", "array_attr", "$@5", "site_entry", "site_id",
  "lef_site_pattern", "orient", "canplace_entry", "cannotoccupy_entry",
  "x_or_y", "layer_list_opt", "id_list", "lef_ggrid_list", "lef_ggrid",
  "floorplan_id", "end_floorplan_id", "floorplan_attr_list",
  "floorplan_attr", "defcap_table_opt", "distance", "defcap_table",
  "defcap_attr_list", "defcap_attr", "string", YY_NULLPTR
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
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484
};
# endif

#define YYPACT_NINF -905

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-905)))

#define YYTABLE_NINF -242

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -905,    71,    32,  -905,  -905,  1711,   -31,  -905,  1711,  1711,
    1711,  1711,  -127,  -100,   -97,  -905,   -94,  1711,   -63,  -905,
     -55,  -905,   -43,  1711,   -21,    -6,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,   256,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,   174,   160,  -905,  -905,  -905,
    -905,    76,  -905,    52,  -905,  -905,    72,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,   -12,
    -905,  -905,  -905,  -905,    -4,    48,    66,     6,  -905,    69,
     -94,  -905,    82,   198,    26,    34,    93,    43,    95,    98,
     123,   129,   104,   379,   251,  -905,  -905,  -905,  1711,   219,
     230,   -34,    94,   -94,   221,    58,  -905,  -905,  1711,  1711,
    1711,   275,   275,  1711,   261,  -905,  -905,   -94,  -905,  -905,
     299,   356,  1711,  -905,  -905,  -905,  -905,   237,  1711,  -905,
    -905,  -905,   107,  -905,   231,  -905,  -905,  -905,  -905,  -905,
    1711,   190,   208,   243,   238,   253,   257,   254,   258,   206,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    1711,   410,   405,   410,  -905,  -905,  -905,  -905,   -25,  1711,
     -94,   -94,   202,  -905,  -905,   204,  1711,  -905,  -905,  1711,
    1711,  1711,  -905,  -905,  1711,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,   -71,  -905,  -905,  -905,  -905,   209,
    1711,  -905,   131,    47,   210,  1711,  -905,   230,   207,   259,
     217,   218,   220,  -905,  -905,  -905,  -905,   -28,  -905,   384,
    -905,  -905,   226,  1711,  -905,  -905,  -905,   -94,   -94,  -905,
    -905,   223,   225,    31,  -905,  -905,   227,  -905,   426,  -905,
     334,   232,  -905,  -905,    53,  -905,  -905,  1711,  -905,   -94,
    1711,  1711,  1711,  -905,  -905,  -905,  -905,  -905,  -905,   -72,
    -905,  -905,   229,   235,   236,   239,   240,   241,   244,   242,
     410,   428,  1711,  -905,   416,  -905,  -905,  -905,   249,  -905,
     255,   406,   224,   177,  -905,  -905,  -905,   289,   260,   262,
    -905,  -905,    88,   -94,   263,  1054,  -905,   148,   264,  -905,
     341,  -905,  -905,  -905,   -94,   -94,   -94,   368,   427,   440,
     -94,   -94,   -94,   268,   270,   272,   273,   -94,  -905,  1711,
    1711,   278,  1711,  -905,   283,   352,  -905,  -905,  -905,  -905,
     284,   259,   285,   282,   265,   288,   291,   292,  -905,  -905,
     -94,  -905,  -905,   293,   295,   417,   418,  -905,  -905,   412,
    1711,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
     422,  -905,  1711,  -905,  -905,   -94,  -905,   -26,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,   327,   297,   298,   303,   304,
     305,   310,   311,   493,   516,  1711,  -905,   416,  1711,  -905,
    -905,  -905,   -94,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,   250,   424,  1711,  1711,  -905,    35,   415,
    -905,   334,   316,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    1711,  -905,   313,   314,  1711,   317,   234,    21,   318,  -905,
     319,   320,   -94,   -80,   321,   322,   323,   325,  1711,  1711,
     326,   329,   333,   336,  1711,  1711,  1711,   337,   338,   339,
     340,   342,   343,   344,   345,  -905,  -905,   248,  -905,  -905,
    -905,   331,   350,  -118,  -905,  -905,   351,   348,   349,   354,
     355,   357,   358,   359,   360,   361,   362,  -905,  -905,   363,
     -94,  -905,   -94,  -905,   352,  -905,   265,  -905,  -905,    41,
     364,    30,  -905,   330,  -905,  -905,  -905,   365,  -905,  -905,
     366,   367,   369,    38,  -905,  -905,   370,  -905,  -905,   374,
    -905,  -905,    -9,    62,   375,   148,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,   368,  1711,  -905,  -905,   372,   378,  -905,
     -94,   -56,   -41,   449,   467,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  1273,  -905,  1492,
     376,   376,   376,   376,   376,   376,   376,   376,   252,  -905,
    -905,  -905,  -905,    27,  -905,  -905,   387,   -75,  -905,   382,
       1,  -905,  -905,  -905,  -905,  -905,   383,   386,   388,   389,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,   390,  -905,  -905,
    -905,   391,   392,   570,   570,   570,  -905,  -905,   393,   394,
     395,   396,   397,  -107,   398,   380,   401,   402,   403,   404,
     408,   409,   411,   413,   414,   419,   420,   421,   423,   425,
    -905,   429,  -905,   430,   276,  -905,  -905,   -94,   -94,   431,
    -905,  -905,   432,   433,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,   434,   435,   -94,  -905,   453,    33,  -905,
    -905,  -905,   436,  1711,  -905,  -905,   282,  -905,  -905,  -905,
     529,   539,   566,  -905,   586,  -905,   437,  1711,   -94,   -94,
     -94,  -905,  1711,   438,   439,  -905,   441,   443,  -905,  -905,
     444,   -94,  1711,   -94,   -94,   -94,   -94,   -94,  -905,  -905,
    -905,   442,   445,   447,   448,   450,   451,   452,   454,   455,
    -905,  -905,  -905,  -905,  -905,   457,   474,  -905,  -905,  -905,
     -75,  -905,   376,  -905,  -905,   525,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,   456,  -905,   458,   459,  -905,  -905,  -905,
    -905,  -905,   -94,  -905,  -905,   462,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,   -94,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,   282,  -905,  1711,  -905,  -905,  -905,  -905,    67,   577,
     -94,   460,  -905,   461,  -905,  -905,   463,   466,   468,  -905,
    -905,  -905,  -905,  -905,  -905,  1711,   469,  -905,   422,   -13,
      92,   -13,   121,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,   470,   282,   446,   474,  -905,   471,  -905,  -905,
    -905,  -905,  -905,   472,  -905,   473,   122,  -905,  -905,   -94,
    -905,   476,   578,  -905,  -905,  -905,    42,    54,   422,  -905,
     478,   479,  -905,   480,  -905,   477,   124,   644,  -905,   474,
     376,   636,  -905,  -905,  -905,  -905,  -905,   631,  -905,   -94,
     -94,   -94,   -94,  -905,   -94,   482,  -905,  -905,   483,  -905,
    -905,  -905,   484,  -905,   487,    11,  -905,  -905,   488,   376,
    1711,   494,   -94,   561,   495,   496,   600,   497,  -905,  -905,
     489,  -905,  -905,   376,   498,  1711,  -905,  -905,   -94,  -905,
    -905,   -94,  -905,   499,   500,  -905,  -905,   501,   502,   672,
    -905,  -905,  -905,  -905
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     0,     2,     1,    71,     0,     0,   286,     0,     0,
       0,     0,     0,     0,     0,    75,     0,     0,     0,    35,
       0,    54,     0,     0,     0,     0,     5,     3,     7,     8,
       9,    10,    11,    12,    13,    21,    26,     0,    22,    23,
      24,    15,    80,    14,     6,   292,   327,    16,    19,    20,
      25,     0,   385,     0,    17,    18,     0,   470,   597,   598,
     599,   600,   518,   519,   520,   521,   644,   543,   564,   572,
     570,   548,   637,   604,   554,   498,   579,   515,   584,   655,
     616,   506,   593,   487,   605,   495,   536,   622,   610,   488,
     509,   537,   645,   647,   501,   612,   580,   491,   573,   620,
     658,   659,   591,   613,   484,   480,   562,   606,   654,   508,
     528,   525,   532,   531,   507,   618,   486,   485,   633,   533,
     527,   502,   560,   656,   552,   489,   550,   514,   492,   595,
     481,   516,   526,   623,   624,   539,   574,   538,   588,   615,
     589,   587,   629,   631,   632,   482,   483,   583,   641,   609,
     608,   614,   471,   611,   535,   490,   625,   479,   499,   586,
     569,   592,   581,   585,   546,   627,   638,   544,   567,   568,
     596,   517,   634,   503,   530,   630,   551,   504,   472,   473,
     474,   475,   476,   477,   478,   493,   494,   496,   497,   500,
     505,   510,   511,   512,   513,   522,   523,   524,   529,   534,
     541,   542,   540,   545,   547,   549,   555,   556,   557,   553,
     558,   559,   561,   563,   565,   566,   571,   575,   577,   576,
     578,   582,   590,   594,   601,   602,   603,   607,   617,   619,
     621,   626,   628,   635,   636,   643,   639,   642,   640,   646,
     648,   649,   650,   651,   652,   653,   657,   323,    27,     0,
     325,   407,   424,    79,     0,     0,     0,     0,   465,     0,
       0,   369,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   299,   328,   329,     0,     0,
       0,   383,     0,     0,     0,     0,   409,   412,     0,     0,
       0,     0,     0,     0,   463,   426,   428,     0,   429,   430,
       0,     0,     0,   287,    73,    31,    29,     0,     0,    76,
      72,   211,     0,    30,     0,    39,    40,    41,    38,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      55,    53,    56,    57,    58,    59,    60,    61,    62,    28,
       0,     0,     0,   357,    33,    32,    51,    52,     0,     0,
       0,     0,     0,   124,   125,     0,     0,   190,   227,     0,
       0,     0,    81,    87,     0,    85,    91,   131,    92,    93,
      78,    95,    88,    90,     0,   298,   295,   296,   297,     0,
       0,   291,   293,     0,     0,     0,   382,     0,     0,     0,
       0,     0,     0,   386,   419,   420,   421,     0,   417,     0,
     414,   415,     0,     0,   410,   408,   436,     0,     0,   448,
     449,     0,     0,     0,   454,   457,     0,   427,     0,   464,
       0,     0,   461,   462,     0,   459,   285,     0,    74,     0,
       0,     0,     0,   381,   370,   371,   372,   373,    34,     0,
     384,    63,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   357,   350,   123,   122,   121,     0,   284,
       0,     0,   108,   104,    98,    99,   100,     0,     0,     0,
     129,   192,     0,   342,     0,     0,   337,     0,     0,   127,
     170,    89,   294,   324,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   300,     0,
       0,     0,     0,   335,     0,     0,   330,   334,   326,   391,
       0,     0,     0,     0,     0,     0,     0,     0,   416,   418,
       0,   411,   422,     0,     0,     0,     0,   433,   455,     0,
       0,   423,   438,   439,   440,   441,   442,   445,   444,   443,
       0,   435,     0,   434,   460,     0,   221,     0,   219,   375,
     368,   329,    42,    43,    44,    45,     0,     0,     0,     0,
       0,     0,     0,     0,   361,     0,   347,   349,     0,   358,
      84,    86,     0,   109,   110,   111,   112,   113,   102,   105,
     106,   107,   101,   114,   115,   117,   118,   119,   120,   103,
     116,    82,    94,     0,     0,     0,     0,   228,   241,   275,
     276,   344,     0,    96,   336,   338,    49,    50,   339,   126,
       0,   171,     0,     0,     0,     0,     0,     0,     0,   189,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   128,   132,     0,   165,   192,
     166,     0,     0,   315,   321,   322,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   200,   346,     0,
     342,   201,     0,   340,   332,   401,     0,   393,   277,     0,
       0,     0,   395,     0,   387,   388,   389,     0,   446,   447,
       0,     0,     0,     0,   467,   425,     0,   437,   458,   289,
      77,   220,     0,     0,     0,    47,    66,    65,    67,    68,
      70,    64,    69,     0,     0,   360,   348,     0,     0,   191,
       0,     0,     0,   212,   214,   193,   194,   196,   195,   202,
     203,   204,   205,   206,   207,   197,   226,     0,   452,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   267,
     268,   244,   245,   229,   230,   233,     0,     0,   232,     0,
       0,   274,   343,   345,    83,   130,     0,     0,     0,     0,
     180,   179,   181,   182,   183,   184,   185,     0,   177,   178,
     176,     0,     0,   198,   198,   198,   186,   187,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     172,   174,   173,     0,     0,   301,   302,     0,     0,     0,
     316,   304,     0,     0,   309,   310,   311,   308,   307,   313,
     314,   312,   331,     0,     0,     0,   341,     0,     0,   403,
     394,   278,     0,     0,   390,   396,     0,   397,   413,   431,
       0,     0,     0,   468,     0,   290,     0,     0,     0,     0,
       0,   376,     0,     0,     0,    48,     0,     0,   359,    97,
       0,     0,     0,     0,     0,     0,     0,     0,   282,   453,
     283,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     264,   265,   266,   263,   231,     0,     0,   248,   246,   247,
       0,   253,     0,   249,   250,   251,   146,   145,   135,   143,
     137,   138,   164,     0,   199,     0,     0,   161,   152,   154,
     160,   156,   342,   133,   142,     0,   144,   157,   158,   139,
     141,   140,   147,   151,   153,   159,   155,   148,   149,   150,
     175,   136,   188,     0,   318,   303,   305,   306,   333,   209,
     210,     0,   405,     0,   400,   404,   398,   392,     0,     0,
       0,     0,   466,     0,   288,   374,     0,     0,     0,   380,
      46,    37,   352,   363,   208,     0,     0,   225,     0,     0,
       0,     0,     0,   269,   255,   257,   259,   261,   256,   258,
     260,   262,     0,     0,     0,   235,   243,   270,   242,   252,
     168,   169,   167,     0,   162,   319,     0,   402,   399,     0,
     456,     0,     0,   377,   378,   379,   351,   362,     0,   223,
       0,     0,   213,     0,   215,     0,     0,     0,   234,   236,
       0,     0,   134,   163,   320,   317,   406,   450,   469,     0,
       0,     0,     0,   353,     0,     0,   365,   364,     0,   216,
     217,   218,     0,   239,     0,     0,   279,   237,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   224,   238,
       0,   240,   280,   272,     0,   451,   432,   222,     0,   356,
     355,     0,   367,     0,     0,   271,   254,     0,     0,     0,
     273,   354,   366,   281
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,   -24,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,    45,  -905,  -374,  -378,
    -580,  -905,  -905,  -503,  -182,    -8,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -576,  -538,  -883,  -905,  -278,  -905,  -905,
    -905,  -905,   -47,  -905,  -905,  -905,  -904,  -905,  -905,  -905,
    -189,  -905,  -905,  -905,  -193,  -905,  -905,  -716,  -905,  -905,
    -905,  -757,  -905,  -332,  -905,   125,  -905,   464,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
      16,  -905,  -905,  -905,  -905,  -905,   179,  -905,  -261,  -905,
     266,  -905,  -660,  -905,  -905,  -905,  -905,  -266,  -905,  -905,
     280,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,   353,   228,  -905,    50,  -621,  -905,  -905,  -905,
    -905,  -905,  -103,  -905,  -905,  -905,  -905,   475,  -905,   465,
    -905,   346,  -905,  -905,  -905,  -905,  -905,   481,  -905,   485,
     486,     5,   135,  -247,  -231,   503,  -905,  -589,  -905,   332,
    -905,  -905,  -905,   324,  -905,  -259,  -905,  -905,    49,    -5
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    26,    27,    28,    29,    30,    31,    32,
      33,    34,   263,   319,   320,   555,   705,   864,   608,    35,
      36,   265,   330,   331,   332,   333,   334,   335,   336,   337,
     338,    37,    38,    39,    40,   257,   309,    41,    42,   272,
     362,   363,   468,   582,   578,   589,   590,   458,   364,   365,
     478,   366,   367,   645,   480,   646,  1033,   647,   813,   781,
     777,   788,   648,   649,   368,   471,   593,   725,   913,   504,
     505,   727,   728,   729,   834,   546,   730,   875,   731,   877,
     732,   733,   734,   547,   548,   697,   735,   976,   369,   472,
     597,   753,   754,   755,   994,   896,   995,  1028,   756,   757,
     900,   905,   998,   758,   759,   893,   760,   882,  1031,  1085,
     598,   679,  1055,  1056,   599,   600,   370,    43,   249,   303,
     856,    44,   274,   275,   379,   382,   498,   819,   820,  1035,
     656,    45,   381,    46,    47,   277,   383,   506,   507,   475,
     476,   674,   602,   762,   508,    48,   342,   343,  1016,  1043,
     454,   569,   451,   715,  1017,  1047,    49,   312,   434,   435,
     702,   861,   436,   437,    50,    51,    52,   281,   393,   279,
     280,   844,   389,   514,   681,   682,   683,   847,   386,   387,
     954,   838,   839,   952,    53,    54,   285,   286,   402,   287,
     397,   398,   405,    55,    56,   531,   294,   295,   959,   296,
     297,   421,   540,   298,   299,   412,  1061,   737,   413,   414,
     300,   543,   424,   425,   418,   260,   419,   693,   694,   738
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     247,   311,   673,   250,   251,   252,   253,   739,   259,   701,
     833,   371,   261,   726,   301,  1054,   902,   857,   267,   858,
     859,   394,   395,   396,   399,   883,   884,   885,   886,   887,
     888,   889,   307,   740,   741,   742,   743,   744,   745,   746,
     747,   740,   741,   742,   743,   744,   745,   746,   747,     4,
     696,   786,     5,   422,   455,   837,   843,   871,     6,   953,
     322,     7,   897,   340,   852,   323,   324,   499,   817,   423,
    1040,     3,   873,   500,     8,   450,     9,   453,   501,   542,
     409,   410,   499,  1044,   403,  1045,    10,   552,   862,   958,
     922,  1029,   461,   501,   248,  1020,  1021,   898,  1023,   778,
     282,   254,   779,   818,   283,    11,   282,   899,   787,   692,
     283,   390,   391,   392,   594,   553,   288,   923,   289,   290,
     348,   325,   780,   903,   554,  1057,   284,   430,   255,   456,
     349,   256,   284,   431,   258,  1048,     7,   289,   290,   291,
     292,   293,   748,   394,   395,   396,   749,   750,   288,   432,
     748,   350,   282,   481,   749,   750,   351,   258,   484,   485,
     486,   487,   488,   489,   672,   262,   490,   491,   492,   493,
     494,   836,   258,   264,   326,    12,   327,   422,   352,   353,
     354,   302,   751,   457,   564,   266,   997,   258,    13,    14,
     751,   355,    15,   423,  1006,   273,   518,   341,   700,   502,
     356,    16,   258,   276,   308,   904,    17,  1041,   268,   860,
      18,   595,   596,   357,   502,   258,    19,   837,   358,   650,
     304,   752,  1042,   269,   314,   651,   652,   653,  -241,   752,
     361,   659,   660,   661,   726,  1071,  1026,   328,   666,    20,
     315,    21,    22,   680,    23,   361,   680,   462,   463,   278,
     329,    24,    25,   503,   321,   527,   359,   360,   579,   580,
     581,   687,  1003,   495,   496,   840,   400,   401,   503,   841,
     499,   316,   305,   384,   270,   271,   719,   380,   720,   464,
     465,   466,   467,   406,   407,   408,   699,   361,   415,   420,
     306,  1008,   721,   310,   317,   841,   499,   427,   979,   980,
     981,   982,   942,   429,   720,   288,   313,   497,   573,   574,
     575,   576,   577,   718,  1058,   439,  1022,   339,   721,   344,
     258,   770,   345,   318,   409,   410,   289,   290,   291,   292,
     293,   416,   810,   811,   812,   449,   771,   772,   773,   774,
     775,   776,   460,  1074,   459,  1024,  1036,   346,  1053,   258,
     841,   470,   841,   347,   473,   474,   477,  1084,   385,   479,
     722,   723,   724,   785,   289,   290,   420,   610,   890,   891,
     892,   611,   612,   613,   388,   483,   606,   607,   583,   584,
     510,   585,   586,   587,   588,   426,   722,   723,   724,   532,
     533,   534,   535,   536,   537,   538,   539,   428,   522,   420,
     420,   375,   376,   377,   378,   914,   914,   914,   654,   655,
     915,   916,   523,   524,   440,   438,   614,   441,   442,   443,
     446,   444,   545,   448,   445,   549,   550,   551,   615,   447,
     340,   452,   469,   482,   509,   512,   513,   520,   616,   617,
     618,   701,   701,   701,   701,   515,   516,   566,   517,   619,
     521,   525,   530,   526,   565,   529,   541,   556,   568,   572,
     657,   870,   672,   557,   558,   601,   563,   559,   560,   561,
     477,  1075,   562,   570,   658,   620,   621,   622,   680,   571,
     690,   691,   623,   692,   591,   696,   592,   603,   609,   624,
     625,   626,   627,   628,   667,   668,   662,   670,   663,   629,
     664,   665,   630,   631,   632,   633,   669,   671,   675,   677,
     678,   634,   684,   704,  1046,   685,   686,   688,   635,   689,
     636,   706,   707,   713,   361,   695,   637,   708,   709,   710,
     638,   639,   640,   641,   711,   712,   714,   698,   736,   596,
     764,   766,   767,   642,   846,   769,   782,   783,   784,   789,
     790,   791,   643,   792,   795,   815,   644,   796,   943,   944,
     716,   797,   874,   717,   798,   802,   803,   804,   805,   855,
     806,   807,   808,   809,   816,   821,   822,   823,   824,   825,
     876,   826,   827,   828,   829,   830,   831,   832,   895,   848,
     499,   951,   842,   960,   849,   850,   868,   851,   854,   966,
     967,   968,   869,   863,   881,   765,   901,   906,   925,   768,
     907,   961,   908,   909,   910,   911,   912,   917,   918,   919,
     920,   921,   924,   793,   794,   926,   927,   928,   929,   799,
     800,   801,   930,   931,   940,   932,   962,   933,   934,   963,
     748,  1009,  1039,   935,   936,   937,  1027,   938,  1054,   939,
    1059,  1060,  1078,  1081,   941,   945,   946,   947,   948,   949,
     956,   964,   601,   971,   835,   972,   970,   973,   974,   984,
     983,   985,   986,   993,   987,   988,   989,  1093,   990,   991,
    1000,   865,  1001,  1002,  1005,   992,  1004,  1013,  1011,  1012,
    1014,   978,  1015,  1019,   814,  1034,  1032,  1018,  1025,  1030,
    1038,  1010,  1049,  1050,  1051,  1052,   894,  1068,  1069,   867,
    1067,   996,   999,   872,   835,  1070,  1073,  1083,  1076,  1079,
    1080,  1082,  1086,  1072,   761,  1091,  1092,  1089,  1090,   866,
     703,   845,   879,   567,   879,   955,   763,   372,     0,   676,
     511,   605,   853,   519,     0,   528,     0,     0,   544,     0,
    1037,     0,     0,     0,     0,     0,     0,   373,   374,     0,
     404,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   417,   433,     0,     0,     0,
    1062,  1063,  1064,  1065,     0,  1066,     0,     0,     0,     0,
       0,     0,     0,     0,   411,     0,     0,     0,     0,     0,
       0,     0,     0,  1077,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1087,
       0,     0,  1088,     0,     0,     0,     0,   950,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   957,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   965,     0,     0,     0,     0,   969,     0,     0,
       0,     0,     0,   975,     0,   835,     0,   977,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   601,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1007,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     977,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    57,     0,     0,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
     879,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,     0,     0,     0,     0,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,     0,   197,   198,     0,   199,     0,
     200,   201,   202,     0,   203,   204,   205,   206,     0,   207,
     208,   209,   210,   211,   212,   213,     0,   214,   215,   216,
       0,   217,   218,   219,   220,   221,     0,     0,     0,   222,
       0,     0,   223,   224,   225,     0,   226,   227,     0,   228,
       0,   229,   230,     0,     0,     0,   231,   232,   233,   234,
     235,   236,   237,   238,     0,   239,   240,   241,   242,   243,
     244,   245,   246,     0,     0,     0,    57,     0,   604,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,     0,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
       0,     0,     0,     0,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,     0,   197,   198,     0,   199,     0,   200,
     201,   202,     0,   203,   204,   205,   206,     0,   207,   208,
     209,   210,   211,   212,   213,     0,   214,   215,   216,     0,
     217,   218,   219,   220,   221,     0,     0,     0,   222,     0,
       0,   223,   224,   225,     0,   226,   227,     0,   228,     0,
     229,   230,     0,     0,     0,   231,   232,   233,   234,   235,
     236,   237,   238,     0,   239,   240,   241,   242,   243,   244,
     245,   246,     0,     0,     0,    57,     0,   878,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,     0,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,     0,
       0,     0,     0,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,     0,   197,   198,     0,   199,     0,   200,   201,
     202,     0,   203,   204,   205,   206,     0,   207,   208,   209,
     210,   211,   212,   213,     0,   214,   215,   216,     0,   217,
     218,   219,   220,   221,     0,     0,     0,   222,     0,     0,
     223,   224,   225,     0,   226,   227,     0,   228,     0,   229,
     230,     0,     0,     0,   231,   232,   233,   234,   235,   236,
     237,   238,     0,   239,   240,   241,   242,   243,   244,   245,
     246,     0,     0,     0,    57,     0,   880,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,     0,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,     0,     0,
       0,     0,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,     0,   197,   198,     0,   199,     0,   200,   201,   202,
       0,   203,   204,   205,   206,     0,   207,   208,   209,   210,
     211,   212,   213,     0,   214,   215,   216,     0,   217,   218,
     219,   220,   221,     0,     0,     0,   222,     0,     0,   223,
     224,   225,     0,   226,   227,     0,   228,     0,   229,   230,
       0,     0,     0,   231,   232,   233,   234,   235,   236,   237,
     238,     0,   239,   240,   241,   242,   243,   244,   245,   246
};

static const yytype_int16 yycheck[] =
{
       5,   260,   505,     8,     9,    10,    11,   596,    16,   547,
     670,   272,    17,   593,    26,     4,    15,    26,    23,    28,
      29,    49,    50,    51,   283,   741,   742,   743,   744,   745,
     746,   747,    26,     6,     7,     8,     9,    10,    11,    12,
      13,     6,     7,     8,     9,    10,    11,    12,    13,    17,
      63,   131,    20,   300,    79,   676,    26,   113,    26,    26,
      26,    29,   137,    20,    26,    31,    32,    20,   186,   300,
      28,     0,   113,    26,    42,   341,    44,   343,    31,    26,
      49,    50,    20,    29,    26,    31,    54,   159,    26,   846,
     197,   995,   351,    31,   125,   978,   979,   172,   981,    78,
      48,   228,    81,   221,    52,    73,    48,   182,   188,    71,
      52,   145,   146,   147,    26,   187,    44,   224,    65,    66,
      16,    87,   101,   122,   196,  1029,    74,    20,   228,   154,
      26,   228,    74,    26,   228,  1018,    29,    65,    66,    67,
      68,    69,   115,    49,    50,    51,   119,   120,    44,    42,
     115,    47,    48,   224,   119,   120,    52,   228,    27,    28,
      29,    30,    31,    32,   110,   228,    35,    36,    37,    38,
      39,   674,   228,   228,   140,   143,   142,   424,    74,    75,
      76,   193,   155,   208,   450,   228,   902,   228,   156,   157,
     155,    87,   160,   424,   951,    21,   224,   154,   224,   152,
      96,   169,   228,    43,   198,   204,   174,   165,   229,   218,
     178,   123,   124,   109,   152,   228,   184,   838,   114,   480,
     224,   194,   180,   229,    26,   484,   485,   486,   201,   194,
     183,   490,   491,   492,   814,   224,   993,   203,   497,   207,
      42,   209,   210,   213,   212,   183,   213,    45,    46,   173,
     216,   219,   220,   206,   228,   224,   152,   153,    81,    82,
      83,   520,   922,   132,   133,   224,    45,    46,   206,   228,
      20,    73,   224,   278,    18,    19,    26,    26,    28,    77,
      78,    79,    80,   288,   289,   290,   545,   183,   293,   297,
     224,   224,    42,   224,    96,   228,    20,   302,   874,   875,
     876,   877,    26,   308,    28,    44,   224,   176,    84,    85,
      86,    87,    88,   572,  1030,   320,   224,   224,    42,   224,
     228,    87,   224,   125,    49,    50,    65,    66,    67,    68,
      69,    70,    84,    85,    86,   340,   102,   103,   104,   105,
     106,   107,   350,  1059,   349,   224,   224,   224,   224,   228,
     228,   356,   228,   224,   359,   360,   361,  1073,   139,   364,
     110,   111,   112,   622,    65,    66,   374,    26,   116,   117,
     118,    30,    31,    32,   144,   380,   228,   229,    89,    90,
     385,    92,    93,    94,    95,    29,   110,   111,   112,    55,
      56,    57,    58,    59,    60,    61,    62,   160,   403,   407,
     408,    22,    23,    24,    25,   783,   784,   785,    40,    41,
     784,   785,   407,   408,   224,   184,    75,   209,   175,   181,
     166,   168,   427,   217,   167,   430,   431,   432,    87,   171,
      20,    26,   228,   224,   224,   228,   177,    53,    97,    98,
      99,   979,   980,   981,   982,   228,   228,   452,   228,   108,
     224,   228,    26,   228,    26,   228,   224,   228,    42,    53,
      33,   720,   110,   228,   228,   473,   224,   228,   228,   228,
     475,  1060,   228,   224,    34,   134,   135,   136,   213,   224,
      63,    63,   141,    71,   224,    63,   224,   224,   224,   148,
     149,   150,   151,   152,   499,   500,   228,   502,   228,   158,
     228,   228,   161,   162,   163,   164,   228,   224,   224,   224,
     228,   170,   224,   186,  1017,   224,   224,   224,   177,   224,
     179,   224,   224,    30,   183,   530,   185,   224,   224,   224,
     189,   190,   191,   192,   224,   224,    20,   542,   114,   124,
     224,   228,   228,   202,   214,   228,   228,   228,   228,   228,
     228,   228,   211,   228,   228,   224,   215,   228,   817,   818,
     565,   228,   113,   568,   228,   228,   228,   228,   228,   195,
     228,   228,   228,   228,   224,   224,   228,   228,   224,   224,
     113,   224,   224,   224,   224,   224,   224,   224,   201,   224,
      20,   138,   228,    64,   228,   228,   224,   228,   228,   858,
     859,   860,   224,   228,   228,   610,   224,   224,   228,   614,
     224,    72,   224,   224,   224,   224,   224,   224,   224,   224,
     224,   224,   224,   628,   629,   224,   224,   224,   224,   634,
     635,   636,   224,   224,   205,   224,    70,   224,   224,    53,
     115,    64,    64,   224,   224,   224,   200,   224,     4,   224,
      14,    20,    91,    53,   224,   224,   224,   224,   224,   224,
     224,   224,   670,   224,   672,   224,   228,   224,   224,   224,
     228,   224,   224,   199,   224,   224,   224,     5,   224,   224,
     224,   705,   224,   224,   943,   228,   224,   224,   228,   228,
     224,   873,   224,   224,   649,   222,   224,   975,   228,   228,
     224,   960,   224,   224,   224,   228,   753,   224,   224,   714,
     228,   900,   905,   721,   722,   228,   228,   228,   224,   224,
     224,   224,   224,  1055,   599,   224,   224,   228,   228,   713,
     551,   681,   737,   453,   739,   838,   601,   272,    -1,   511,
     387,   475,   693,   397,    -1,   413,    -1,    -1,   424,    -1,
    1009,    -1,    -1,    -1,    -1,    -1,    -1,   272,   272,    -1,
     285,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   294,   312,    -1,    -1,    -1,
    1039,  1040,  1041,  1042,    -1,  1044,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   291,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1062,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1078,
      -1,    -1,  1081,    -1,    -1,    -1,    -1,   835,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   843,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   857,    -1,    -1,    -1,    -1,   862,    -1,    -1,
      -1,    -1,    -1,   871,    -1,   873,    -1,   872,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   922,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   953,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     975,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    1075,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,    -1,    -1,    -1,    -1,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,    -1,   151,   152,    -1,   154,    -1,
     156,   157,   158,    -1,   160,   161,   162,   163,    -1,   165,
     166,   167,   168,   169,   170,   171,    -1,   173,   174,   175,
      -1,   177,   178,   179,   180,   181,    -1,    -1,    -1,   185,
      -1,    -1,   188,   189,   190,    -1,   192,   193,    -1,   195,
      -1,   197,   198,    -1,    -1,    -1,   202,   203,   204,   205,
     206,   207,   208,   209,    -1,   211,   212,   213,   214,   215,
     216,   217,   218,    -1,    -1,    -1,     3,    -1,   224,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
      -1,    -1,    -1,    -1,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,    -1,   151,   152,    -1,   154,    -1,   156,
     157,   158,    -1,   160,   161,   162,   163,    -1,   165,   166,
     167,   168,   169,   170,   171,    -1,   173,   174,   175,    -1,
     177,   178,   179,   180,   181,    -1,    -1,    -1,   185,    -1,
      -1,   188,   189,   190,    -1,   192,   193,    -1,   195,    -1,
     197,   198,    -1,    -1,    -1,   202,   203,   204,   205,   206,
     207,   208,   209,    -1,   211,   212,   213,   214,   215,   216,
     217,   218,    -1,    -1,    -1,     3,    -1,   224,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,    -1,
      -1,    -1,    -1,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,    -1,   151,   152,    -1,   154,    -1,   156,   157,
     158,    -1,   160,   161,   162,   163,    -1,   165,   166,   167,
     168,   169,   170,   171,    -1,   173,   174,   175,    -1,   177,
     178,   179,   180,   181,    -1,    -1,    -1,   185,    -1,    -1,
     188,   189,   190,    -1,   192,   193,    -1,   195,    -1,   197,
     198,    -1,    -1,    -1,   202,   203,   204,   205,   206,   207,
     208,   209,    -1,   211,   212,   213,   214,   215,   216,   217,
     218,    -1,    -1,    -1,     3,    -1,   224,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,    -1,    -1,
      -1,    -1,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,    -1,   151,   152,    -1,   154,    -1,   156,   157,   158,
      -1,   160,   161,   162,   163,    -1,   165,   166,   167,   168,
     169,   170,   171,    -1,   173,   174,   175,    -1,   177,   178,
     179,   180,   181,    -1,    -1,    -1,   185,    -1,    -1,   188,
     189,   190,    -1,   192,   193,    -1,   195,    -1,   197,   198,
      -1,    -1,    -1,   202,   203,   204,   205,   206,   207,   208,
     209,    -1,   211,   212,   213,   214,   215,   216,   217,   218
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   231,   232,     0,    17,    20,    26,    29,    42,    44,
      54,    73,   143,   156,   157,   160,   169,   174,   178,   184,
     207,   209,   210,   212,   219,   220,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   249,   250,   261,   262,   263,
     264,   267,   268,   347,   351,   361,   363,   364,   375,   386,
     394,   395,   396,   414,   415,   423,   424,     3,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   151,   152,   154,
     156,   157,   158,   160,   161,   162,   163,   165,   166,   167,
     168,   169,   170,   171,   173,   174,   175,   177,   178,   179,
     180,   181,   185,   188,   189,   190,   192,   193,   195,   197,
     198,   202,   203,   204,   205,   206,   207,   208,   209,   211,
     212,   213,   214,   215,   216,   217,   218,   449,   125,   348,
     449,   449,   449,   449,   228,   228,   228,   265,   228,   305,
     445,   449,   228,   242,   228,   251,   228,   449,   229,   229,
      18,    19,   269,    21,   352,   353,    43,   365,   173,   399,
     400,   397,    48,    52,    74,   416,   417,   419,    44,    65,
      66,    67,    68,    69,   426,   427,   429,   430,   433,   434,
     440,    26,   193,   349,   224,   224,   224,    26,   198,   266,
     224,   445,   387,   224,    26,    42,    73,    96,   125,   243,
     244,   228,    26,    31,    32,    87,   140,   142,   203,   216,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   224,
      20,   154,   376,   377,   224,   224,   224,   224,    16,    26,
      47,    52,    74,    75,    76,    87,    96,   109,   114,   152,
     153,   183,   270,   271,   278,   279,   281,   282,   294,   318,
     346,   368,   419,   429,   430,    22,    23,    24,    25,   354,
      26,   362,   355,   366,   449,   139,   408,   409,   144,   402,
     145,   146,   147,   398,    49,    50,    51,   420,   421,   445,
      45,    46,   418,    26,   417,   422,   449,   449,   449,    49,
      50,   435,   435,   438,   439,   449,    70,   427,   444,   446,
     305,   431,   433,   434,   442,   443,    29,   449,   160,   449,
      20,    26,    42,   347,   388,   389,   392,   393,   184,   449,
     224,   209,   175,   181,   168,   167,   166,   171,   217,   449,
     377,   382,    26,   377,   380,    79,   154,   208,   277,   449,
     305,   445,    45,    46,    77,    78,    79,    80,   272,   228,
     449,   295,   319,   449,   449,   369,   370,   449,   280,   449,
     284,   224,   224,   449,    27,    28,    29,    30,    31,    32,
      35,    36,    37,    38,    39,   132,   133,   176,   356,    20,
      26,    31,   152,   206,   299,   300,   367,   368,   374,   224,
     449,   402,   228,   177,   403,   228,   228,   228,   224,   421,
      53,   224,   449,   431,   431,   228,   228,   224,   439,   228,
      26,   425,    55,    56,    57,    58,    59,    60,    61,    62,
     432,   224,    26,   441,   443,   449,   305,   313,   314,   449,
     449,   449,   159,   187,   196,   245,   228,   228,   228,   228,
     228,   228,   228,   224,   377,    26,   449,   380,    42,   381,
     224,   224,    53,    84,    85,    86,    87,    88,   274,    81,
      82,    83,   273,    89,    90,    92,    93,    94,    95,   275,
     276,   224,   224,   296,    26,   123,   124,   320,   340,   344,
     345,   305,   372,   224,   224,   370,   228,   229,   248,   224,
      26,    30,    31,    32,    75,    87,    97,    98,    99,   108,
     134,   135,   136,   141,   148,   149,   150,   151,   152,   158,
     161,   162,   163,   164,   170,   177,   179,   185,   189,   190,
     191,   192,   202,   211,   215,   283,   285,   287,   292,   293,
     368,   445,   445,   445,    40,    41,   360,    33,    34,   445,
     445,   445,   228,   228,   228,   228,   445,   449,   449,   228,
     449,   224,   110,   303,   371,   224,   403,   224,   228,   341,
     213,   404,   405,   406,   224,   224,   224,   445,   224,   224,
      63,    63,    71,   447,   448,   449,    63,   315,   449,   445,
     224,   314,   390,   366,   186,   246,   224,   224,   224,   224,
     224,   224,   224,    30,    20,   383,   449,   449,   445,    26,
      28,    42,   110,   111,   112,   297,   300,   301,   302,   303,
     306,   308,   310,   311,   312,   316,   114,   437,   449,   437,
       6,     7,     8,     9,    10,    11,    12,    13,   115,   119,
     120,   155,   194,   321,   322,   323,   328,   329,   333,   334,
     336,   345,   373,   432,   224,   449,   228,   228,   449,   228,
      87,   102,   103,   104,   105,   106,   107,   290,    78,    81,
     101,   289,   228,   228,   228,   445,   131,   188,   291,   228,
     228,   228,   228,   449,   449,   228,   228,   228,   228,   449,
     449,   449,   228,   228,   228,   228,   228,   228,   228,   228,
      84,    85,    86,   288,   296,   224,   224,   186,   221,   357,
     358,   224,   228,   228,   224,   224,   224,   224,   224,   224,
     224,   224,   224,   372,   304,   305,   303,   406,   411,   412,
     224,   228,   228,    26,   401,   405,   214,   407,   224,   228,
     228,   228,    26,   448,   228,   195,   350,    26,    28,    29,
     218,   391,    26,   228,   247,   248,   360,   449,   224,   224,
     445,   113,   305,   113,   113,   307,   113,   309,   224,   449,
     224,   228,   337,   337,   337,   337,   337,   337,   337,   337,
     116,   117,   118,   335,   322,   201,   325,   137,   172,   182,
     330,   224,    15,   122,   204,   331,   224,   224,   224,   224,
     224,   224,   224,   298,   299,   298,   298,   224,   224,   224,
     224,   224,   197,   224,   224,   228,   224,   224,   224,   224,
     224,   224,   224,   224,   224,   224,   224,   224,   224,   224,
     205,   224,    26,   445,   445,   224,   224,   224,   224,   224,
     305,   138,   413,    26,   410,   412,   224,   449,   341,   428,
      64,    72,    70,    53,   224,   449,   445,   445,   445,   449,
     228,   224,   224,   224,   224,   305,   317,   449,   304,   313,
     313,   313,   313,   228,   224,   224,   224,   224,   224,   224,
     224,   224,   228,   199,   324,   326,   330,   337,   332,   334,
     224,   224,   224,   372,   224,   445,   341,   449,   224,    64,
     445,   228,   228,   224,   224,   224,   378,   384,   317,   224,
     315,   315,   224,   315,   224,   228,   341,   200,   327,   326,
     228,   338,   224,   286,   222,   359,   224,   445,   224,    64,
      28,   165,   180,   379,    29,    31,   303,   385,   315,   224,
     224,   224,   228,   224,     4,   342,   343,   326,   337,    14,
      20,   436,   445,   445,   445,   445,   445,   228,   224,   224,
     228,   224,   343,   228,   337,   437,   224,   445,    91,   224,
     224,    53,   224,   228,   337,   339,   224,   445,   445,   228,
     228,   224,   224,     5
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   230,   231,   231,   232,   232,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   233,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   242,   243,   244,   244,
     244,   244,   245,   245,   245,   246,   246,   247,   247,   248,
     248,   249,   249,   250,   251,   251,   252,   252,   252,   252,
     252,   252,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   265,   266,   267,   268,
     269,   269,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   271,   272,   272,
     272,   272,   272,   272,   273,   273,   273,   273,   274,   274,
     274,   274,   274,   274,   275,   275,   275,   276,   276,   276,
     276,   277,   277,   277,   278,   278,   279,   280,   281,   282,
     283,   284,   284,   285,   285,   285,   285,   285,   285,   285,
     285,   285,   285,   285,   285,   285,   285,   285,   285,   285,
     285,   285,   285,   285,   285,   285,   285,   285,   285,   285,
     285,   285,   286,   285,   285,   285,   285,   285,   285,   285,
     287,   287,   288,   288,   288,   288,   289,   289,   289,   290,
     290,   290,   290,   290,   290,   290,   291,   291,   292,   293,
     295,   294,   296,   296,   297,   297,   297,   297,   298,   298,
     299,   300,   301,   301,   301,   301,   301,   301,   302,   303,
     304,   305,   307,   306,   309,   308,   310,   311,   312,   313,
     313,   314,   315,   316,   316,   317,   318,   319,   319,   320,
     321,   321,   322,   322,   323,   324,   324,   324,   325,   326,
     327,   328,   328,   328,   329,   329,   330,   330,   330,   331,
     331,   332,   332,   333,   333,   333,   333,   333,   333,   333,
     333,   333,   333,   334,   335,   335,   335,   336,   336,   337,
     338,   338,   339,   339,   340,   340,   340,   341,   341,   342,
     342,   343,   344,   345,   346,   347,   348,   348,   349,   350,
     350,   351,   352,   352,   353,   354,   354,   354,   354,   355,
     355,   356,   356,   356,   356,   356,   356,   356,   356,   356,
     356,   356,   356,   356,   356,   357,   357,   358,   358,   359,
     359,   360,   360,   361,   362,   363,   364,   365,   365,   366,
     366,   367,   367,   367,   367,   367,   368,   369,   369,   370,
     371,   371,   372,   372,   373,   373,   374,   375,   375,   376,
     376,   377,   378,   378,   379,   379,   379,   380,   380,   381,
     382,   383,   383,   384,   384,   385,   385,   385,   386,   387,
     387,   388,   388,   388,   389,   390,   390,   391,   391,   391,
     392,   393,   394,   395,   396,   397,   397,   398,   398,   398,
     399,   400,   401,   402,   403,   404,   404,   405,   406,   407,
     408,   409,   410,   411,   411,   412,   413,   414,   415,   416,
     416,   417,   417,   417,   418,   418,   419,   420,   420,   421,
     421,   421,   422,   423,   424,   425,   426,   426,   427,   427,
     427,   428,   427,   427,   427,   429,   430,   431,   432,   432,
     432,   432,   432,   432,   432,   432,   433,   434,   435,   435,
     436,   436,   437,   437,   438,   438,   439,   440,   441,   442,
     442,   443,   443,   444,   444,   445,   446,   447,   447,   448,
     449,   449,   449,   449,   449,   449,   449,   449,   449,   449,
     449,   449,   449,   449,   449,   449,   449,   449,   449,   449,
     449,   449,   449,   449,   449,   449,   449,   449,   449,   449,
     449,   449,   449,   449,   449,   449,   449,   449,   449,   449,
     449,   449,   449,   449,   449,   449,   449,   449,   449,   449,
     449,   449,   449,   449,   449,   449,   449,   449,   449,   449,
     449,   449,   449,   449,   449,   449,   449,   449,   449,   449,
     449,   449,   449,   449,   449,   449,   449,   449,   449,   449,
     449,   449,   449,   449,   449,   449,   449,   449,   449,   449,
     449,   449,   449,   449,   449,   449,   449,   449,   449,   449,
     449,   449,   449,   449,   449,   449,   449,   449,   449,   449,
     449,   449,   449,   449,   449,   449,   449,   449,   449,   449,
     449,   449,   449,   449,   449,   449,   449,   449,   449,   449,
     449,   449,   449,   449,   449,   449,   449,   449,   449,   449,
     449,   449,   449,   449,   449,   449,   449,   449,   449,   449,
     449,   449,   449,   449,   449,   449,   449,   449,   449,   449,
     449,   449,   449,   449,   449,   449,   449,   449,   449,   449,
     449,   449,   449,   449,   449,   449,   449,   449,   449,   449,
     449,   449,   449,   449,   449,   449,   449,   449,   449,   449
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     3,     3,
       3,     3,     3,     3,     4,     0,     2,     6,     1,     1,
       1,     1,     1,     1,     1,     0,     3,     0,     1,     1,
       1,     3,     3,     3,     0,     2,     1,     1,     1,     1,
       1,     1,     1,     2,     4,     4,     4,     4,     4,     4,
       4,     1,     3,     3,     4,     0,     2,     4,     3,     2,
       0,     2,     3,     4,     3,     1,     3,     1,     1,     2,
       1,     1,     1,     1,     3,     1,     3,     5,     1,     1,
       1,     2,     2,     2,     0,     1,     1,     1,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     3,     2,
       2,     0,     2,     3,     5,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     0,     5,     3,     1,     1,     4,     4,     4,
       0,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       0,     4,     0,     2,     1,     1,     1,     1,     0,     1,
       2,     2,     1,     1,     1,     1,     1,     1,     3,     3,
       2,     2,     0,     4,     0,     4,     5,     5,     5,     1,
       2,     1,     7,     4,     6,     1,     4,     0,     2,     2,
       1,     2,     1,     1,     4,     1,     2,     3,     5,     3,
       3,     0,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     1,     2,     7,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     1,     1,     1,     1,     1,     2,
       0,     4,     0,     2,     2,     1,     1,     1,     2,     1,
       2,     5,     3,     3,     2,     4,     0,     2,     6,     0,
       1,     3,     0,     2,     3,     1,     1,     1,     1,     0,
       2,     3,     3,     4,     3,     4,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     1,     4,     2,     0,
       1,     1,     1,     2,     2,     2,     4,     0,     1,     0,
       2,     3,     2,     4,     1,     1,     3,     1,     2,     2,
       1,     2,     0,     2,     0,     1,     2,     5,     6,     3,
       2,     7,     0,     2,     5,     3,     3,     0,     2,     3,
       3,     0,     4,     0,     2,     1,     5,     3,     5,     0,
       2,     1,     1,     1,     5,     0,     2,     3,     3,     3,
       5,     1,     3,     2,     4,     0,     2,     3,     3,     3,
       5,     3,     2,     3,     3,     1,     2,     2,     3,     3,
       5,     3,     2,     1,     2,     2,     3,     2,     3,     1,
       2,     3,     1,     5,     1,     1,     3,     1,     2,     1,
       1,     1,     2,     4,     2,     2,     1,     2,     1,     1,
       1,     0,    10,     3,     3,     3,     2,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     4,     1,     1,
       0,     2,     1,     2,     1,     2,     6,     2,     2,     1,
       2,     1,     1,     0,     1,     1,     5,     1,     2,     5,
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1
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
        case 3:
#line 396 "lefparse.y" /* yacc.c:1646  */
    {/*printf("parsed successfully\n")*/}
#line 2666 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 400 "lefparse.y" /* yacc.c:1646  */
    {/*printf("One rule parsed\n");*/}
#line 2672 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 403 "lefparse.y" /* yacc.c:1646  */
    {//printf("One layer parsed\n");
                     }
#line 2679 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 428 "lefparse.y" /* yacc.c:1646  */
    {
                      }
#line 2686 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 433 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2692 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 437 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2698 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 441 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2704 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 445 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2710 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 449 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2716 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 453 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2722 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 457 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2728 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 462 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2734 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 467 "lefparse.y" /* yacc.c:1646  */
    {
     if ((yyvsp[-4].lexeme).DoDelete) free ((yyvsp[-4].lexeme).str);
     }
#line 2742 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 473 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2748 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 474 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2754 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 475 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2760 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 476 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2766 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 480 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2772 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 481 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2778 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 482 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2784 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 486 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2790 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 487 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2796 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 491 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2802 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 492 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2808 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 496 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2814 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 497 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2820 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 501 "lefparse.y" /* yacc.c:1646  */
    {bCaseSens = 1;}
#line 2826 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 502 "lefparse.y" /* yacc.c:1646  */
    {bCaseSens = 0;}
#line 2832 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 506 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2838 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 511 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2844 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 515 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2850 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 516 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2856 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 517 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2862 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 518 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2868 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 519 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2874 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 520 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2880 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 521 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2886 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 524 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2892 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 528 "lefparse.y" /* yacc.c:1646  */
    {
    //pUnitsPtr->timConv = (int)($3+1e-5);
    }
#line 2900 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 534 "lefparse.y" /* yacc.c:1646  */
    {
    //pUnitsPtr->capConv = (int)($3+1e-5);
    }
#line 2908 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 540 "lefparse.y" /* yacc.c:1646  */
    {
    //pUnitsPtr->resConv = (int)($3+1e-5);
    }
#line 2916 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 546 "lefparse.y" /* yacc.c:1646  */
    {
    //pUnitsPtr->powConv = (int)($3+1e-5);
    }
#line 2924 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 552 "lefparse.y" /* yacc.c:1646  */
    {
    //pUnitsPtr->curConv = (int)($3+1e-5);
    }
#line 2932 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 558 "lefparse.y" /* yacc.c:1646  */
    {
    //pUnitsPtr->vltConv = (int)($3+1e-5);
    }
#line 2940 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 564 "lefparse.y" /* yacc.c:1646  */
    {
    //pUnitsPtr->LEFDistConv = (int)($3+1e-5);
    //pUnitsPtr->DEFDistConv = pUnitsPtr->LEFDistConv;
    pdb->context._units = (int)((yyvsp[-1].fval)+1e-5);
    }
#line 2950 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 572 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2956 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 576 "lefparse.y" /* yacc.c:1646  */
    { pdb->context._minFeatureX = (yyvsp[-1].pt).x;
                                        pdb->context._minFeatureY = (yyvsp[-1].pt).y; }
#line 2963 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 581 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2969 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 584 "lefparse.y" /* yacc.c:1646  */
    {}
#line 2975 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 593 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[-2].lexeme).DoDelete) free((yyvsp[-2].lexeme).str);}
#line 2981 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 601 "lefparse.y" /* yacc.c:1646  */
    {
    //if (currentCellPtr->getMacroType() == MacroTypeCORE)
    //    currentCellPtr->SetType(TypeCC); // May be changed to TypeSC
    pdb->design._cellLib.push_back(pTempCell =
                 new dbMasterCell(tempCellName,
                                  tempMacroType,
                                  tempPadClass, //meaningful only if pad
                                  tempCellWidth,
                                  tempCellHeight,
                                  tempCellOrig,
                                  tempPins,
                                  tempObs,
                                  tempSymmetry,
                                  *pTempSite) );

    ctainerMasterPinsLocal::iterator iP;

    itLayerGeom iLG;

    for (iP=tempPins.begin();iP!=tempPins.end();iP++)
        {
        (*iP)->_cell = pTempCell;

        //shift all port locations by the origin
        ctainerLayerGeoms &LGs = (*iP)->_ports;

        for (iLG=LGs.begin();iLG!=LGs.end();iLG++)
            {
            (*iLG)->_rect.TranslateBy(tempCellOrig);
            }
        }

    // now shift obstacles by origin
    for (iLG=tempObs.begin();iLG!=tempObs.end();iLG++)
        {
        (*iLG)->_rect.TranslateBy(tempCellOrig);
        }


    pair<char const* const,dbMasterCell*> const &pref =
        pair<char const* const,dbMasterCell*>(
                                 tempstr=strdup(tempCellName),
                                 pTempCell) ;
                                 
    pp->stringsToClean.push_back(tempstr);
                                         

    pair<ParserLEFDEF::masterCellHashMapType::iterator,bool> p =
        pp->masterCellHash.insert(pref);

    if (!p.second)
        {
        sprintf(errtxt,"duplicate declaration of master cell %s "
                  "in line %d of LEF; ignored",tempCellName,lefLinenum);
        abkwarn(0,errtxt);
        pdb->design._cellLib.pop_back();
        delete pTempCell;
        for (unsigned idx=0;idx<tempPins.size();idx++) delete tempPins[idx];
        tempPins.clear();
        break;
        }

    // now we can add the pins to the _pinLib; search for
    // "b3nrpqe" in comments to see what I'm talking about.

    for (unsigned idx=0;idx<tempPins.size();idx++) 
        pdb->design._pinLib.push_back(tempPins[idx]);

   switch (leqFound)
       {
       case EQ_CLASS_FOUND:
           pCurrentLEQclass->push_back(pTempCell);
           break;
       case EQ_CLASS_NOT_FOUND:
           {
           eqClassMasterCells newClass;
           newClass.push_back(pLEQCell);
           newClass.push_back(pTempCell);
           pp->tempCellLEQs.push_back(newClass);
           break;
           }
       //note: if no leq was specified, the value of leqFound will
       //      be AMBIG_EQ_FOUND, so neither branch taken.
       case AMBIG_EQ_FOUND:
           break; //satisfy compiler
       }

   switch (eeqFound)
       {
       case EQ_CLASS_FOUND:
           pCurrentEEQclass->push_back(pTempCell);
           break;
       case EQ_CLASS_NOT_FOUND:
           {
           eqClassMasterCells newClass;
           newClass.push_back(pEEQCell);
           newClass.push_back(pTempCell);
           pp->tempCellEEQs.push_back(newClass);
           break;
           }
       //note: if no eeq was specified, the value of eeqFound will
       //      be AMBIG_EQ_FOUND, so neither branch taken.
       case AMBIG_EQ_FOUND:
           break; //satisfy compiler
       }
   ;
}
#line 3093 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 712 "lefparse.y" /* yacc.c:1646  */
    {
    strcpy(tempCellName,(yyvsp[0].lexeme).str);
    tempMacroType = dbMasterCellType::CORE;  //the default value
    tempPadClass = dbMasterCellType::PadUNKNOWN;
    tempCellWidth = tempCellHeight =  unsigned(-1);
    tempCellOrig.x = tempCellOrig.y = 0;
    tempPins.clear();
    tempObs.clear();
    pTempSite = NULL;
    pTempCell = NULL;
    leqFound = eeqFound = AMBIG_EQ_FOUND;
    tempSymmetry.x = tempSymmetry.y = tempSymmetry.rot90 = false;
    pCurrentLEQclass=pCurrentEEQclass = NULL;
    pLEQCell = pEEQCell = NULL;
    ppLocalClass  = NULL;
    ppLocalEqCell = NULL;
    pLocalFound   = NULL;
    if ((yyvsp[0].lexeme).DoDelete) free((yyvsp[0].lexeme).str);
    }
#line 3117 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 740 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3123 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 741 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[-2].lexeme).DoDelete) free((yyvsp[-2].lexeme).str);}
#line 3129 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 742 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3135 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 744 "lefparse.y" /* yacc.c:1646  */
    {tempCellOrig=(yyvsp[-1].pt);}
#line 3141 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 745 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3147 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 752 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3153 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 753 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3159 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 754 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3165 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 761 "lefparse.y" /* yacc.c:1646  */
    {
        tempCellWidth = (yyvsp[-3].ival);
        tempCellHeight= (yyvsp[-1].ival);
        }
#line 3174 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 768 "lefparse.y" /* yacc.c:1646  */
    {tempMacroType = dbMasterCellType::COVER;}
#line 3180 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 769 "lefparse.y" /* yacc.c:1646  */
    {tempMacroType = dbMasterCellType::RING;}
#line 3186 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 770 "lefparse.y" /* yacc.c:1646  */
    {tempMacroType = dbMasterCellType::BLOCK;}
#line 3192 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 772 "lefparse.y" /* yacc.c:1646  */
    {tempMacroType = dbMasterCellType::CORE;
           if ((yyvsp[-1].lexeme).DoDelete) free ((yyvsp[-1].lexeme).str);/*part of kludge*/}
#line 3199 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 775 "lefparse.y" /* yacc.c:1646  */
    {tempMacroType = dbMasterCellType::PAD;}
#line 3205 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 777 "lefparse.y" /* yacc.c:1646  */
    {tempMacroType = dbMasterCellType::ENDCAP;}
#line 3211 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 782 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3217 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 783 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3223 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 784 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3229 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 788 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3235 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 789 "lefparse.y" /* yacc.c:1646  */
    {tempPadClass = dbMasterCellType::INPUT;
      if ((yyvsp[0].lexeme).DoDelete) free ((yyvsp[0].lexeme).str);/*part of kludge*/}
#line 3242 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 791 "lefparse.y" /* yacc.c:1646  */
    {tempPadClass = dbMasterCellType::OUTPUT;
      if ((yyvsp[0].lexeme).DoDelete) free ((yyvsp[0].lexeme).str);/*part of kludge*/}
#line 3249 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 793 "lefparse.y" /* yacc.c:1646  */
    {tempPadClass = dbMasterCellType::INOUT;}
#line 3255 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 794 "lefparse.y" /* yacc.c:1646  */
    {tempPadClass = dbMasterCellType::POWER;}
#line 3261 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 795 "lefparse.y" /* yacc.c:1646  */
    {tempPadClass = dbMasterCellType::SPACER;}
#line 3267 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 799 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3273 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 800 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3279 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 801 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3285 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 805 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3291 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 806 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3297 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 807 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3303 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 808 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3309 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 812 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3315 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 813 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3321 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 814 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3327 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 818 "lefparse.y" /* yacc.c:1646  */
    {
            pTempCellQSpace = &(pp->tempCellLEQs);
            ppLocalClass = &pCurrentLEQclass;
            pLocalFound  = &leqFound;
            ppLocalEqCell = &pLEQCell;
            }
#line 3338 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 824 "lefparse.y" /* yacc.c:1646  */
    {
            pTempCellQSpace = &(pp->tempCellEEQs);
            ppLocalClass = &pCurrentEEQclass;
            pLocalFound  = &eeqFound;
            ppLocalEqCell = &pEEQCell;
            }
#line 3349 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 834 "lefparse.y" /* yacc.c:1646  */
    {
    bool found=false;
    equivClassesMasterCells::iterator iEC;
    eqClassMasterCells::iterator iMC;
    for (iEC=pTempCellQSpace->begin();
         iEC!=pTempCellQSpace->end();iEC++)
        {
        for (iMC = (*iEC).begin();iMC!=(*iEC).end();iMC++)
            {
            if ((*iMC) == pTempEquivCell )
                {
                found = true;
                break;
                }
            }
        if (found)
            break;
        }

    // At this point we know where the new cell will go:
    // if found is true, then pTempCell will be added to
    // (*iEC); otherwise we'll make a new vector containing
    // pTempEquivCell and pTempCell and push it back on pTempCellQSpace.

    // Unfortunately pTempCell does not yet exist.  So we've got
    // to save this info to be used after construction.

    if (found)
        {
        *ppLocalClass = &(*iEC);
        *pLocalFound = EQ_CLASS_FOUND;
        }
    else
        {
        *ppLocalEqCell = pTempEquivCell;
        *pLocalFound = EQ_CLASS_NOT_FOUND;
        }
    }
#line 3392 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 875 "lefparse.y" /* yacc.c:1646  */
    {
    ParserLEFDEF::masterCellHashMapType::iterator iC 
                 = pp->masterCellHash.find((yyvsp[0].lexeme).str);
    if (iC == pp->masterCellHash.end())
        {
        sprintf(errtxt,"Master Cell %s not found in line %d "
                       "of LEF file",(yyvsp[0].lexeme).str,lefLinenum);
        abkfatal(0,errtxt);
        }
     else
        pTempEquivCell = (*iC).second;

    if ((yyvsp[0].lexeme).DoDelete) free ((yyvsp[0].lexeme).str);
    }
#line 3411 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 893 "lefparse.y" /* yacc.c:1646  */
    {
        if (tempPorts.size() == 0)
            {
            //sprintf(errtxt,"In line %d of LEF file, pin %s "
            //               "of cell %s has no port geometries; ignored",
            //               lefLinenum,tempPinName,tempCellName);
            //abkwarn(tempPorts.size(),errtxt);
            //break;
            tempGeomBoundingBox.add(0,0); //work-around
            }
        if (tempGeomBoundingBox.isEmpty())
            {
            sprintf(errtxt,"In line %d of LEF file, pin %s "
                           "of cell %s has empty bounding box; adding "
                           "a point to prevent crash",lefLinenum,tempPinName,
                           tempCellName);
            abkwarn(0,errtxt);
            tempGeomBoundingBox.add(0,0); //work-around
            }

        //pdb->design._pinLib.push_back(pTempPin =
        //line above had to be removed; we can't afford to add
        //this pin to the _pinLib until we know if the master cell
        //is going to stay. comment reference string "b3nrpqe"

        tempPins.push_back(pTempPin =
             new dbMasterPin(tempPinName,
                              tempDir,
                              tempUse,
                              tempShape,
                              tempGeomBoundingBox,
                              tempGeomBoundingBox.getGeomCenter()
                              )
                              );
        pTempPin->_riseDelay = pTempPin->_fallDelay = pTempPin->_riseResist
        = pTempPin->_fallResist = pTempPin->_inputCap = -1.0;

        pTempPin->_ports = tempPorts;

        if (pMustJoinPin)
            {
            if (pMustJoinPin->_mustJoin)
                {
                pMustJoinPin->_mustJoin->push_back(pTempPin);
                }
            else
                {
                ctainerMasterPinsLocal *pmj = new ctainerMasterPinsLocal;
                pmj->push_back(pMustJoinPin);
                pmj->push_back(pTempPin);
                pMustJoinPin->_mustJoin = pmj;
                pTempPin->_mustJoin = pmj;
                }
            }

        switch(pinClassFound)
            {
            case EQ_CLASS_FOUND:
                pCurrentPinClass->push_back(pTempPin);
                break;
            case EQ_CLASS_NOT_FOUND:
                {
                eqClassMasterPins newClass;
                newClass.push_back(pLEQpin);
                newClass.push_back(pTempPin);
                pdb->design._pinLEQs.push_back(newClass);
                break;
                }

            //note: if no LEQ was specified at all, we get
            //      the value AMBIG_EQ_FOUND for pinClassFound,
            //      so neither branch taken
            case AMBIG_EQ_FOUND:
                break; //satisfy compiler
            }
        }
#line 3492 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 973 "lefparse.y" /* yacc.c:1646  */
    {
    strcpy(tempPinName,(yyvsp[0].lexeme).str);
    tempDir[0] = tempUse[0] = tempShape[0] = '\0';
    tempBBox.clear();
    tempPorts.clear();
    tempGeomBoundingBox.clear();
    tempPolygon.clear();
    pinClassFound = AMBIG_EQ_FOUND;
    pCurrentPinClass=NULL;
    pLEQpin = NULL;
    pMustJoinPin = NULL;
    //currentPinPtr = new dbMasterPinRec;
    //if (!currentPinPtr) leferror("Failed to allocate pin");
    //currentPinPtr->setName($<lexeme>2.str);

    if ((yyvsp[0].lexeme).DoDelete) free((yyvsp[0].lexeme).str);

    //currentCellPtr->m_pPinTable->AddPin(currentPinPtr);
    //currentCellPtr->IncrementNumPins();
    }
#line 3517 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 996 "lefparse.y" /* yacc.c:1646  */
    {
                     //LOOK! check that name is the same
                     if ((yyvsp[0].lexeme).DoDelete) free((yyvsp[0].lexeme).str);
                     }
#line 3526 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1004 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3532 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1008 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[-1].lexeme).DoDelete) free((yyvsp[-1].lexeme).str);}
#line 3538 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1009 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[-3].lexeme).DoDelete) free((yyvsp[-3].lexeme).str);}
#line 3544 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1011 "lefparse.y" /* yacc.c:1646  */
    {
     //we want to search tempPins *only* for the equivalent pin
     ctainerMasterPinsLocal::const_iterator iPeq;
     bool nameFound = false;
     for (iPeq=tempPins.begin();iPeq!=tempPins.end();iPeq++)
         {
         if (strcmp((*iPeq)->getName(),(yyvsp[-1].lexeme).str)==0)
             {
             nameFound = true;
             break;
             }
         }

     if (!nameFound)
         {
         sprintf(errtxt,"Pin %s, allegedly equivalent to pin %s,"
                        " not found in cell %s in line %d of LEF",
                        (yyvsp[-1].lexeme).str,tempPinName,tempCellName,lefLinenum);
         abkfatal(0,errtxt);
         }

    // now we've found the equivalent pin; we need to see if
    // it's already got an equiv class
    typedef equivClassesMasterPins  &rQSpace;
    rQSpace LEQs(pdb->design._pinLEQs);

    bool classFound = false;
    equivClassesMasterPins::iterator iPC;
    eqClassMasterPins::const_iterator iP;
    
    for (iPC=LEQs.begin();iPC!=LEQs.end();iPC++)
        {
        for (iP=(*iPC).begin();iP!=(*iPC).end();iP++)
            {
            if ((*iP) == (*iPeq))
                {
                classFound = true;
                break;
                } 
            }
        if (classFound)
            break;
        }

    if (classFound)
        {
        pCurrentPinClass = &(*iPC);
        pinClassFound = EQ_CLASS_FOUND;
        }
    else
        {
        pLEQpin=(*iPeq);
        pinClassFound = EQ_CLASS_NOT_FOUND;
        }

     if ((yyvsp[-1].lexeme).DoDelete) free((yyvsp[-1].lexeme).str);
     }
#line 3606 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1068 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3612 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1069 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3618 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1070 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3624 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1072 "lefparse.y" /* yacc.c:1646  */
    {
             //we want to search tempPins *only* for the mustjoin pin
             ctainerMasterPinsLocal::const_iterator iPmj;
             bool nameFound = false;
             for (iPmj=tempPins.begin();iPmj!=tempPins.end();iPmj++)
                 {
                 if (strcmp((*iPmj)->getName(),(yyvsp[-1].lexeme).str)==0)
                     {
                     nameFound = true;
                     pMustJoinPin = *iPmj;
                     break;
                     }
                 }

             if (!nameFound)
                 {
                 sprintf(errtxt,"Pin %s, which allegedly must join pin %s,"
                                " not found in cell %s in line %d of LEF",
                                (yyvsp[-1].lexeme).str,tempPinName,tempCellName,lefLinenum);
                 abkfatal(0,errtxt);
                 }
//            tempMustJoin = true;
            if ((yyvsp[-1].lexeme).DoDelete) free((yyvsp[-1].lexeme).str);
            }
#line 3653 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1096 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[-1].lexeme).DoDelete) free((yyvsp[-1].lexeme).str);}
#line 3659 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1097 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[-1].lexeme).DoDelete) free((yyvsp[-1].lexeme).str);}
#line 3665 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1098 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[-1].lexeme).DoDelete) free((yyvsp[-1].lexeme).str);}
#line 3671 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1099 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3677 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1100 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3683 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1101 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3689 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1102 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3695 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1103 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3701 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1104 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3707 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1105 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3713 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1106 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3719 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1107 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3725 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1108 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3731 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1109 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3737 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1110 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3743 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1111 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3749 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1112 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3755 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1113 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3761 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1114 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3767 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1115 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3773 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1116 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3779 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1117 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3785 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1118 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3791 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1118 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3797 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1119 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3803 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1120 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3809 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1121 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3815 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1123 "lefparse.y" /* yacc.c:1646  */
    {/*LOOK! "distance" is a guess*/}
#line 3821 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1125 "lefparse.y" /* yacc.c:1646  */
    {/*LOOK! units are sq microns, irresp of UNITS stmt*/}
#line 3827 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 1127 "lefparse.y" /* yacc.c:1646  */
    {/*LOOK! units are microns, irresp of UNITS stmt*/}
#line 3833 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1132 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3839 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 1136 "lefparse.y" /* yacc.c:1646  */
    {strcpy(tempDir,"INPUT");
      if ((yyvsp[0].lexeme).DoDelete) free ((yyvsp[0].lexeme).str);/*part of kludge*/}
#line 3846 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1138 "lefparse.y" /* yacc.c:1646  */
    {strcpy(tempDir,"INOUT");}
#line 3852 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 1139 "lefparse.y" /* yacc.c:1646  */
    {strcpy(tempDir,"OUTPUT");
      if ((yyvsp[0].lexeme).DoDelete) free ((yyvsp[0].lexeme).str);/*part of kludge*/}
#line 3859 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1141 "lefparse.y" /* yacc.c:1646  */
    {strcpy(tempDir,"OUTPUT TRISTATE");
      if ((yyvsp[-1].lexeme).DoDelete) free ((yyvsp[-1].lexeme).str);/*part of kludge*/}
#line 3866 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 1146 "lefparse.y" /* yacc.c:1646  */
    {strcpy(tempShape,"ABUTMENT");}
#line 3872 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 1147 "lefparse.y" /* yacc.c:1646  */
    {strcpy(tempShape,"RING");}
#line 3878 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 1148 "lefparse.y" /* yacc.c:1646  */
    {strcpy(tempShape,"FEEDTHRU");}
#line 3884 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1153 "lefparse.y" /* yacc.c:1646  */
    {strcpy(tempUse,"SIGNAL");}
#line 3890 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1154 "lefparse.y" /* yacc.c:1646  */
    {strcpy(tempUse,"POWER");}
#line 3896 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 1155 "lefparse.y" /* yacc.c:1646  */
    {strcpy(tempUse,"GROUND");}
#line 3902 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 1156 "lefparse.y" /* yacc.c:1646  */
    {strcpy(tempUse,"CLOCK");}
#line 3908 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 1157 "lefparse.y" /* yacc.c:1646  */
    {strcpy(tempUse,"TIEOFF");}
#line 3914 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 1158 "lefparse.y" /* yacc.c:1646  */
    {strcpy(tempUse,"ANALOG");}
#line 3920 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 1159 "lefparse.y" /* yacc.c:1646  */
    {strcpy(tempUse,"DATA");}
#line 3926 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 1162 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3932 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1163 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3938 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 1167 "lefparse.y" /* yacc.c:1646  */
    { }
#line 3944 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1170 "lefparse.y" /* yacc.c:1646  */
    {
                    if ((yyvsp[0].lexeme).DoDelete) free((yyvsp[0].lexeme).str); //KLUDGE
                    pLGeomList = &tempPorts;
                    /*pLGeomList = &(currentPinPtr->ports);*/
                    pTempLayer=NULL;
                    }
#line 3955 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1179 "lefparse.y" /* yacc.c:1646  */
    {pLGeomList = &tempObs;tempGeomBoundingBox.clear();
             tempPolygon.clear();pTempLayer=NULL;}
#line 3962 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 1181 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3968 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1186 "lefparse.y" /* yacc.c:1646  */
    {}
#line 3974 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1191 "lefparse.y" /* yacc.c:1646  */
    {
        tempLGwidth = pTempLayer->getWidth();
        }
#line 3982 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1196 "lefparse.y" /* yacc.c:1646  */
    {
        }
#line 3989 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1200 "lefparse.y" /* yacc.c:1646  */
    {
        //LOOK! the whole "width" thing is unnecessary for us for at the moment.
        //      it only refers to what happens in PATH stmts.
        //      if we decide to parse these at some point, we will need
        //      to use this.

        //OK, these rules have gone through a bunch of iterations.  The
        //current incarnation (ParserLEFDEF4.5.4, 22 Jan 98) is almost
        //absurdly liberal, but that shouldn't really hurt anything.

        //motivation:  Some examples specify a layer before a geometry
        //             given as a via, even though it's meaningless in
        //             that case (AMD1,NEC_HUGE).  Others don't (SANYO).
        //             Others give a layer and then several rectangles,
        //             even though that (like a layer before a via_geom)
        //             is apparently forbidden by LEF manual page 1-53.
        //
        //             I guess the only thing we really need to be
        //             sure of is that, if a geometry is given other
        //             than as a via, a layer has been specified.  Next
        //             check takes care of that, since we set pTempLayer
        //             to NULL before getting here (rules start_port
        //             and obs_stmt).


        if (!pTempLayer)
            {
            sprintf(errtxt,"In line %d of LEF: geometry with undefined layer",
                            lefLinenum);
            abkfatal(0,errtxt);
            }
        if (tempPolygon.empty())
            pLGeomList->push_back(new dbLayerGeom(tempLGrectangle,
                                                      *pTempLayer));
        else
            pLGeomList->push_back(new dbLayerGeom(tempPolygon,
                                                      *pTempLayer));
        }
#line 4032 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1240 "lefparse.y" /* yacc.c:1646  */
    {
        }
#line 4039 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1245 "lefparse.y" /* yacc.c:1646  */
    {pTempLayer=NULL;}
#line 4045 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1250 "lefparse.y" /* yacc.c:1646  */
    {
                     strcpy(DummyString,(yyvsp[0].lexeme).str);
                     ParserLEFDEF::layerHashMapType::iterator iL =
                                                   pp->layerHash.find((yyvsp[0].lexeme).str);
                     if (iL == pp->layerHash.end())
                         {
                         sprintf(errtxt,"Layer %s not found in line %d "
                                        "of LEF file",(yyvsp[0].lexeme).str,lefLinenum);
                         abkfatal(0,errtxt);
                         }
                      else
                         pTempLayer = (*iL).second;
                      if ((yyvsp[0].lexeme).DoDelete) free((yyvsp[0].lexeme).str);
                      }
#line 4064 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1268 "lefparse.y" /* yacc.c:1646  */
    {
    }
#line 4071 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1273 "lefparse.y" /* yacc.c:1646  */
    {
                 tempLGrectangle = (yyvsp[0].rectVal);
                 tempGeomBoundingBox.add((yyvsp[0].rectVal).llx,(yyvsp[0].rectVal).lly);
                 tempGeomBoundingBox.add((yyvsp[0].rectVal).urx,(yyvsp[0].rectVal).ury);
                 }
#line 4081 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1278 "lefparse.y" /* yacc.c:1646  */
    {abkwarn(0,"path geometry declared; ignored");}
#line 4087 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1279 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4093 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1280 "lefparse.y" /* yacc.c:1646  */
    {abkwarn(0,"iterated rectangle geometry declared; ignored");}
#line 4099 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1281 "lefparse.y" /* yacc.c:1646  */
    {abkwarn(0,"iterated path geometry declared; ignored");}
#line 4105 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1282 "lefparse.y" /* yacc.c:1646  */
    {abkwarn(0,"iterated polygon geometry declared; ignored");}
#line 4111 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 1286 "lefparse.y" /* yacc.c:1646  */
    {tempLayerWidth=(yyvsp[-1].ival);}
#line 4117 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1289 "lefparse.y" /* yacc.c:1646  */
    {(yyval.rectVal)=(yyvsp[-1].rectVal);}
#line 4123 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1294 "lefparse.y" /* yacc.c:1646  */
    {
       (yyval.rectVal).llx = int(min((yyvsp[-1].pt).x,(yyvsp[0].pt).x));
       (yyval.rectVal).lly = int(min((yyvsp[-1].pt).y,(yyvsp[0].pt).y));
       (yyval.rectVal).urx = int(max((yyvsp[-1].pt).x,(yyvsp[0].pt).x));
       (yyval.rectVal).ury = int(max((yyvsp[-1].pt).y,(yyvsp[0].pt).y));
       }
#line 4134 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1303 "lefparse.y" /* yacc.c:1646  */
    {(yyval.pt).x = (yyvsp[-1].ival); (yyval.pt).y = (yyvsp[0].ival);}
#line 4140 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1306 "lefparse.y" /* yacc.c:1646  */
    {inPolygon=false;}
#line 4146 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1306 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4152 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1309 "lefparse.y" /* yacc.c:1646  */
    {inPolygon=true;}
#line 4158 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1309 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4164 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1313 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4170 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1317 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4176 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1321 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4182 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1331 "lefparse.y" /* yacc.c:1646  */
    {
     if (inPolygon) tempPolygon.push_back((yyvsp[0].pt));
     tempGeomBoundingBox += (yyvsp[0].pt);
     }
#line 4191 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1339 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4197 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1353 "lefparse.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-3].lexeme).DoDelete) free ((yyvsp[-3].lexeme).str); //KLUDGE
        typedef ctainerLayerGeoms const &rlg;
        rlg LGref(pTempVia->getGeometries());

        ctainerLayerGeoms::const_iterator iLG;

        for (iLG=LGref.begin();iLG!=LGref.end();iLG++)
            {
            BBox b=*(*iLG);
            b.TranslateBy((yyvsp[-2].pt));
            pLGeomList->push_back(new dbLayerGeom(b,(*iLG)->getLayer()));
            tempGeomBoundingBox.add(b.xMin,b.yMin);
            tempGeomBoundingBox.add(b.xMax,b.yMax);
            }
        }
#line 4218 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1370 "lefparse.y" /* yacc.c:1646  */
    {
        if ((yyvsp[-5].lexeme).DoDelete) free ((yyvsp[-5].lexeme).str); //KLUDGE
        abkwarn(0,"geometry specified as iterated via; ignored");
        }
#line 4227 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1377 "lefparse.y" /* yacc.c:1646  */
    {
     ParserLEFDEF::viaHashMapType::iterator iV
                   = pp->viaHash.find((yyvsp[0].lexeme).str);
     if (iV == pp->viaHash.end())
         {
         sprintf(errtxt,"Via %s not found in line %d "
                        "of LEF file",(yyvsp[0].lexeme).str,lefLinenum);
         abkfatal(0,errtxt);
         }
     else
         pTempVia = (*iV).second;

     if ((yyvsp[0].lexeme).DoDelete) free((yyvsp[0].lexeme).str);

    }
#line 4247 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1396 "lefparse.y" /* yacc.c:1646  */
    {
        }
#line 4254 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1409 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4260 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1419 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4266 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1423 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4272 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1424 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4278 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1428 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4284 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1429 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4290 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1435 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4296 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1444 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4302 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1447 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4308 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1450 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4314 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 1455 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4320 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 1456 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4326 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 1462 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4332 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1463 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4338 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 246:
#line 1467 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4344 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1468 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4350 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1469 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4356 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1473 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4362 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 250:
#line 1474 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4368 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 252:
#line 1480 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4374 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 253:
#line 1485 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4380 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 1486 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4386 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1487 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4392 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 256:
#line 1488 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4398 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 257:
#line 1489 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4404 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1490 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4410 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 1491 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4416 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 260:
#line 1492 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4422 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1493 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4428 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 1494 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4434 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 263:
#line 1497 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4440 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1501 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4446 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1502 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4452 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 1503 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4458 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1507 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4464 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 268:
#line 1508 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4470 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1512 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4476 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1517 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4482 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 1522 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4488 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 1533 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4494 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 275:
#line 1534 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4500 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 276:
#line 1535 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4506 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 277:
#line 1539 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4512 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 278:
#line 1540 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4518 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 1554 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4524 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 1558 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4530 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 284:
#line 1568 "lefparse.y" /* yacc.c:1646  */
    {
    //currentCellPtr->BuildPinArray();
    //NumMasterCells++;
    if ((yyvsp[0].lexeme).DoDelete) free((yyvsp[0].lexeme).str);
    }
#line 4540 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 285:
#line 1583 "lefparse.y" /* yacc.c:1646  */
    {
                 }
#line 4547 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 1590 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4553 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 288:
#line 1594 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[-4].lexeme).DoDelete) free((yyvsp[-4].lexeme).str); if ((yyvsp[-3].lexeme).DoDelete) free((yyvsp[-3].lexeme).str);}
#line 4559 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 290:
#line 1599 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4565 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 291:
#line 1611 "lefparse.y" /* yacc.c:1646  */
    {
       //pTempLayer->direction = tempDirection;
       }
#line 4573 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 293:
#line 1618 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4579 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 294:
#line 1622 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4585 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 295:
#line 1626 "lefparse.y" /* yacc.c:1646  */
    {tempLayerType = dbLayer::MASTERSLICE;}
#line 4591 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 296:
#line 1627 "lefparse.y" /* yacc.c:1646  */
    {tempLayerType = dbLayer::CUT;}
#line 4597 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 297:
#line 1628 "lefparse.y" /* yacc.c:1646  */
    {tempLayerType = dbLayer::OVERLAP;}
#line 4603 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 298:
#line 1629 "lefparse.y" /* yacc.c:1646  */
    {tempLayerType = dbLayer::ROUTING;}
#line 4609 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 300:
#line 1634 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4615 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 1638 "lefparse.y" /* yacc.c:1646  */
    {tempPitch = (yyvsp[-1].ival);}
#line 4621 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 302:
#line 1639 "lefparse.y" /* yacc.c:1646  */
    {tempLayerWidth = (yyvsp[-1].ival);}
#line 4627 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 303:
#line 1640 "lefparse.y" /* yacc.c:1646  */
    {tempSpacing = (yyvsp[-2].ival);}
#line 4633 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 304:
#line 1641 "lefparse.y" /* yacc.c:1646  */
    {//taken care of in h_or_v rule
                                  }
#line 4640 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 1643 "lefparse.y" /* yacc.c:1646  */
    {tempUnitRes = (yyvsp[-1].fval);}
#line 4646 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 306:
#line 1644 "lefparse.y" /* yacc.c:1646  */
    {tempUnitCap = (yyvsp[-1].fval);}
#line 4652 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 307:
#line 1645 "lefparse.y" /* yacc.c:1646  */
    {tempEdgeCap = (yyvsp[-1].fval); }
#line 4658 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 308:
#line 1646 "lefparse.y" /* yacc.c:1646  */
    {tempCapMult = (yyvsp[-1].fval);}
#line 4664 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 309:
#line 1647 "lefparse.y" /* yacc.c:1646  */
    {tempLayerHeight = (yyvsp[-1].ival);}
#line 4670 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 310:
#line 1648 "lefparse.y" /* yacc.c:1646  */
    {tempThickness = (yyvsp[-1].ival);}
#line 4676 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 311:
#line 1649 "lefparse.y" /* yacc.c:1646  */
    {tempShrinkage = (yyvsp[-1].ival);}
#line 4682 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 312:
#line 1650 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4688 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 313:
#line 1651 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4694 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 314:
#line 1652 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4700 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 315:
#line 1658 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4706 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 316:
#line 1660 "lefparse.y" /* yacc.c:1646  */
    {
      if (warnMultSpace)
          {
          warnMultSpace=false;
          abkwarn(0,"Multiple spacing rules for regular wiring in a "
                  "single layer.\nThis is not supported by DB; the "
                  "spacing used will be the last specified.\nLength "
                  "thresholds are also unsupported.");
          }
      }
#line 4721 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 317:
#line 1673 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4727 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 318:
#line 1674 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4733 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 319:
#line 1678 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4739 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 320:
#line 1679 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4745 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 321:
#line 1683 "lefparse.y" /* yacc.c:1646  */
    {tempLayerDir = dbLayer::HORIZ;}
#line 4751 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 322:
#line 1684 "lefparse.y" /* yacc.c:1646  */
    {tempLayerDir = dbLayer::VERT;}
#line 4757 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 323:
#line 1689 "lefparse.y" /* yacc.c:1646  */
    {
                     strcpy(tempLayerName,(yyvsp[0].lexeme).str); if ((yyvsp[0].lexeme).DoDelete) free((yyvsp[0].lexeme).str);
                     tempLayerDir = dbLayer::NOPREFERRED;
                     tempLayerType= dbLayer::Type(-1) ;
                     tempPitch=tempLayerWidth=tempThickness=tempSpacing
                     =tempShrinkage= tempLayerHeight = unsigned(-1);
                     tempCapMult=tempEdgeCap=tempUnitRes=tempUnitCap=DBL_MAX;
                     }
#line 4770 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 324:
#line 1700 "lefparse.y" /* yacc.c:1646  */
    {
                   //LOOK! need to check names
                   pdb->context._layers.push_back(pTempLayer =
                                                  new dbLayer(
                                                      tempLayerName,
                                                      runningLayerIdx++,
                                                      tempLayerType,
                                                      tempLayerDir,
                                                      tempPitch,
                                                      tempLayerHeight,
                                                      tempLayerWidth,
                                                      tempThickness,
                                                      tempSpacing,
                                                      tempShrinkage,
                                                      tempCapMult,
                                                      tempEdgeCap,
                                                      tempUnitRes,
                                                      tempUnitCap) );

                   pair<char const* const,dbLayer*> const &pref =
                         pair<char const* const,dbLayer*>(
                                                     tempstr=
                                                          strdup(tempLayerName),
                                                     pTempLayer) ;
                                                     
                   pp->stringsToClean.push_back(tempstr);
                                               
                   
                   pair<ParserLEFDEF::layerHashMapType::iterator,bool> p =
                        pp->layerHash.insert(pref);

                   if (!p.second)
                       {
                       sprintf(errtxt,"duplicate declaration of layer %s "
                                      "in line %d of LEF",tempLayerName,lefLinenum);
                       abkfatal(0,errtxt);
                       pdb->context._layers.pop_back();
                       delete pTempLayer;
                       }

                   if ((yyvsp[0].lexeme).DoDelete) free((yyvsp[0].lexeme).str);
                   }
#line 4817 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 325:
#line 1751 "lefparse.y" /* yacc.c:1646  */
    {
    if ((yyvsp[-1].lexeme).DoDelete) free ((yyvsp[-1].lexeme).str); //KLUDGE
    tempViaResis = DBL_MAX;
    tempViaLGs.clear();
    pTempLayer   = NULL;
    strcpy(tempViaName,(yyvsp[0].lexeme).str);
    if ((yyvsp[0].lexeme).DoDelete) free ((yyvsp[0].lexeme).str);
    }
#line 4830 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 326:
#line 1763 "lefparse.y" /* yacc.c:1646  */
    {
           std::sort(tempViaLGs.begin(),tempViaLGs.end(),CompareLayerGeoms());
           pp->tempAllVias.push_back(pTempVia = new dbVia(tempViaName,
                                                          tempViaResis,
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
                sprintf(errtxt,"duplicate declaration of via %s "
                          "in line %d of LEF.  First declaration"
                          " accepted; subsequent ignored.",tempViaName,lefLinenum);
                abkwarn(0,errtxt);
                pp->tempAllVias.pop_back();
                delete pTempVia;
                }
           }
#line 4861 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 328:
#line 1792 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4867 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 330:
#line 1797 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4873 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 331:
#line 1801 "lefparse.y" /* yacc.c:1646  */
    {tempViaResis=(yyvsp[-1].fval);}
#line 4879 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 332:
#line 1802 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4885 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 333:
#line 1803 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[-2].lexeme).DoDelete) free((yyvsp[-2].lexeme).str);}
#line 4891 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 334:
#line 1804 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4897 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 335:
#line 1805 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4903 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 336:
#line 1809 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4909 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 337:
#line 1813 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4915 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 338:
#line 1814 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4921 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 339:
#line 1819 "lefparse.y" /* yacc.c:1646  */
    {
     if ((yyvsp[-1].lexeme).DoDelete) free ((yyvsp[-1].lexeme).str);
     }
#line 4929 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 340:
#line 1825 "lefparse.y" /* yacc.c:1646  */
    {tempViaLGs.push_back(new dbLayerGeom((yyvsp[0].rectVal),*pTempLayer,true));}
#line 4935 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 341:
#line 1826 "lefparse.y" /* yacc.c:1646  */
    {tempViaLGs.push_back(new dbLayerGeom((yyvsp[0].rectVal),*pTempLayer,true));}
#line 4941 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 343:
#line 1831 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4947 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 345:
#line 1836 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4953 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 346:
#line 1840 "lefparse.y" /* yacc.c:1646  */
    {/*LOOK! check names*/
                  if ((yyvsp[0].lexeme).DoDelete) free((yyvsp[0].lexeme).str);}
#line 4960 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 347:
#line 1851 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[-3].lexeme).DoDelete) free((yyvsp[-3].lexeme).str);if ((yyvsp[0].lexeme).DoDelete) free ((yyvsp[0].lexeme).str);}
#line 4966 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 348:
#line 1852 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[-4].lexeme).DoDelete) free((yyvsp[-4].lexeme).str); if ((yyvsp[0].lexeme).DoDelete) free((yyvsp[0].lexeme).str);}
#line 4972 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 349:
#line 1856 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4978 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 350:
#line 1857 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4984 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 351:
#line 1861 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[-5].lexeme).DoDelete) free((yyvsp[-5].lexeme).str);}
#line 4990 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 353:
#line 1866 "lefparse.y" /* yacc.c:1646  */
    {}
#line 4996 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 354:
#line 1870 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5002 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 355:
#line 1871 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5008 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 356:
#line 1872 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5014 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 358:
#line 1877 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5020 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 359:
#line 1881 "lefparse.y" /* yacc.c:1646  */
    {
                                if ((yyvsp[-2].lexeme).DoDelete) free((yyvsp[-2].lexeme).str); //KLUDGE
                                if ((yyvsp[-1].lexeme).DoDelete) free((yyvsp[-1].lexeme).str);
                                }
#line 5029 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 360:
#line 1888 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5035 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 362:
#line 1893 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[-2].lexeme).DoDelete) free((yyvsp[-2].lexeme).str);}
#line 5041 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 364:
#line 1898 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5047 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 365:
#line 1902 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5053 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 366:
#line 1903 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5059 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 367:
#line 1904 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5065 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 368:
#line 1912 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[-3].lexeme).DoDelete) free((yyvsp[-3].lexeme).str); if ((yyvsp[0].lexeme).DoDelete) free((yyvsp[0].lexeme).str);}
#line 5071 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 370:
#line 1917 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5077 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 371:
#line 1923 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5083 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 372:
#line 1924 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5089 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 373:
#line 1925 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5095 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 374:
#line 1929 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[-3].lexeme).DoDelete) free((yyvsp[-3].lexeme).str); if ((yyvsp[0].lexeme).DoDelete) free((yyvsp[0].lexeme).str);}
#line 5101 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 376:
#line 1934 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5107 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 377:
#line 1938 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5113 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 378:
#line 1939 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5119 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 379:
#line 1940 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5125 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 380:
#line 1945 "lefparse.y" /* yacc.c:1646  */
    {
             if ((yyvsp[-4].lexeme).DoDelete) free((yyvsp[-4].lexeme).str); //KLUDGE
             if ((yyvsp[-3].lexeme).DoDelete) free((yyvsp[-3].lexeme).str);
             if ((yyvsp[0].lexeme).DoDelete) free((yyvsp[0].lexeme).str);
             }
#line 5135 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 381:
#line 1953 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5141 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 382:
#line 1961 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5147 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 383:
#line 1965 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5153 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 384:
#line 1968 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5159 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 386:
#line 1973 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5165 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 387:
#line 1977 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5171 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 388:
#line 1978 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5177 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 389:
#line 1979 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5183 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 390:
#line 1983 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5189 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 391:
#line 1987 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[-1].lexeme).DoDelete) free((yyvsp[-1].lexeme).str);}
#line 5195 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 392:
#line 1990 "lefparse.y" /* yacc.c:1646  */
    {/*LOOK! check names*/
                        if ((yyvsp[0].lexeme).DoDelete) free((yyvsp[0].lexeme).str);}
#line 5202 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 393:
#line 1995 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5208 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 394:
#line 1999 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5214 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 395:
#line 2003 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5220 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 396:
#line 2004 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5226 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 397:
#line 2008 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5232 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 398:
#line 2012 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5238 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 399:
#line 2016 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5244 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 400:
#line 2020 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5250 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 401:
#line 2024 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[-1].lexeme).DoDelete) free((yyvsp[-1].lexeme).str);}
#line 5256 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 402:
#line 2027 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[0].lexeme).DoDelete) free((yyvsp[0].lexeme).str);}
#line 5262 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 403:
#line 2031 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5268 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 404:
#line 2032 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5274 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 405:
#line 2036 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5280 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 406:
#line 2040 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5286 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 407:
#line 2047 "lefparse.y" /* yacc.c:1646  */
    {
        strcpy(tempSiteName,(yyvsp[0].lexeme).str);
        tempSiteHeight = tempSiteWidth = unsigned(-1);
        tempSymmetry.x = tempSymmetry.y = tempSymmetry.rot90 = false;
        tempSiteType = dbSite::Type(-1);
        if ((yyvsp[0].lexeme).DoDelete) free((yyvsp[0].lexeme).str);
        }
#line 5298 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 408:
#line 2059 "lefparse.y" /* yacc.c:1646  */
    {
               pdb->context._sites.push_back(pTempSite =
                 new dbSite(tempSiteName,
                            tempSiteType,
                            tempSymmetry,
                            tempSiteHeight,
                            tempSiteWidth));

               pair<char const* const,dbSite*> const &pref =
                         pair<char const* const,dbSite*>(
                                                     tempstr=
                                                          strdup(tempSiteName),
                                                     pTempSite) ;
                                                     
               pp->stringsToClean.push_back(tempstr);
                                                              
                   
               pair<ParserLEFDEF::siteHashMapType::iterator,bool> p =
                        pp->siteHash.insert(pref);

               if (!p.second)
                   {
                   sprintf(errtxt,"duplicate declaration of site %s "
                                  "in line %d of LEF",tempSiteName,lefLinenum);
                   abkfatal(0,errtxt);
                   pdb->context._sites.pop_back();
                   delete pTempSite;
                   }
               }
#line 5332 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 409:
#line 2091 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5338 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 410:
#line 2092 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5344 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 411:
#line 2096 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5350 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 412:
#line 2097 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5356 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 413:
#line 2098 "lefparse.y" /* yacc.c:1646  */
    {tempSiteWidth  = (yyvsp[-3].ival);
                                              tempSiteHeight = (yyvsp[-1].ival);}
#line 5363 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 414:
#line 2103 "lefparse.y" /* yacc.c:1646  */
    {tempSiteType = dbSite::PAD;}
#line 5369 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 415:
#line 2104 "lefparse.y" /* yacc.c:1646  */
    {tempSiteType = dbSite::CORE;
                if ((yyvsp[0].lexeme).DoDelete) free ((yyvsp[0].lexeme).str);/*part of kludge*/
               }
#line 5377 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 416:
#line 2111 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5383 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 417:
#line 2115 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5389 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 418:
#line 2116 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5395 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 419:
#line 2120 "lefparse.y" /* yacc.c:1646  */
    {tempSymmetry.x=true;if ((yyvsp[0].lexeme).DoDelete) free ((yyvsp[0].lexeme).str); /*KLUDGE*/}
#line 5401 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 420:
#line 2121 "lefparse.y" /* yacc.c:1646  */
    {tempSymmetry.y=true;if ((yyvsp[0].lexeme).DoDelete) free ((yyvsp[0].lexeme).str); /*KLUDGE*/}
#line 5407 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 421:
#line 2122 "lefparse.y" /* yacc.c:1646  */
    {tempSymmetry.rot90=true;}
#line 5413 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 422:
#line 2126 "lefparse.y" /* yacc.c:1646  */
    {//LOOK! need to check name is the same
                   if ((yyvsp[0].lexeme).DoDelete) free((yyvsp[0].lexeme).str);}
#line 5420 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 423:
#line 2137 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5426 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 424:
#line 2141 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[0].lexeme).DoDelete) free((yyvsp[0].lexeme).str);}
#line 5432 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 425:
#line 2145 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[0].lexeme).DoDelete) free((yyvsp[0].lexeme).str);}
#line 5438 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 426:
#line 2149 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5444 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 427:
#line 2150 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5450 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 428:
#line 2154 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5456 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 429:
#line 2155 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5462 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 430:
#line 2156 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5468 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 431:
#line 2157 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5474 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 432:
#line 2158 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5480 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 433:
#line 2159 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5486 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 434:
#line 2160 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5492 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 435:
#line 2165 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5498 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 436:
#line 2169 "lefparse.y" /* yacc.c:1646  */
    {
                     strcpy(DummyString,(yyvsp[0].lexeme).str);
                     ParserLEFDEF::siteHashMapType::iterator iL
                                   = pp->siteHash.find((yyvsp[0].lexeme).str);
                     if (iL == pp->siteHash.end())
                         {
                         sprintf(errtxt,"Site %s not found in line %d "
                                        "of LEF file",(yyvsp[0].lexeme).str,lefLinenum);
                         abkfatal(0,errtxt);
                         }
                     else
                         pTempSite = (*iL).second;

                     if ((yyvsp[0].lexeme).DoDelete) free((yyvsp[0].lexeme).str);
                     }
#line 5518 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 437:
#line 2187 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5524 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 438:
#line 2192 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[0].lexeme).DoDelete) free ((yyvsp[0].lexeme).str);}
#line 5530 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 439:
#line 2193 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[0].lexeme).DoDelete) free ((yyvsp[0].lexeme).str);}
#line 5536 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 440:
#line 2194 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[0].lexeme).DoDelete) free ((yyvsp[0].lexeme).str);}
#line 5542 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 441:
#line 2195 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[0].lexeme).DoDelete) free ((yyvsp[0].lexeme).str);}
#line 5548 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 442:
#line 2196 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5554 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 443:
#line 2197 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5560 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 444:
#line 2198 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5566 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 445:
#line 2199 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5572 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 446:
#line 2206 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[-2].lexeme).DoDelete) free((yyvsp[-2].lexeme).str);}
#line 5578 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 447:
#line 2210 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[-2].lexeme).DoDelete) free((yyvsp[-2].lexeme).str);}
#line 5584 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 448:
#line 2213 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[0].lexeme).DoDelete) free ((yyvsp[0].lexeme).str); /*KLUDGE*/}
#line 5590 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 449:
#line 2214 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[0].lexeme).DoDelete) free ((yyvsp[0].lexeme).str); /*KLUDGE*/}
#line 5596 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 451:
#line 2219 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5602 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 452:
#line 2222 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[0].lexeme).DoDelete) free((yyvsp[0].lexeme).str);}
#line 5608 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 453:
#line 2223 "lefparse.y" /* yacc.c:1646  */
    { //LOOK! this is a problem.  How are we
                       //going to free everything?
                     if ((yyvsp[0].lexeme).DoDelete) free((yyvsp[0].lexeme).str);}
#line 5616 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 454:
#line 2229 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5622 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 455:
#line 2230 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5628 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 456:
#line 2234 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5634 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 457:
#line 2238 "lefparse.y" /* yacc.c:1646  */
    {if ((yyvsp[0].lexeme).DoDelete) free((yyvsp[0].lexeme).str);}
#line 5640 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 458:
#line 2242 "lefparse.y" /* yacc.c:1646  */
    {/*LOOK! check names*/
                    if ((yyvsp[0].lexeme).DoDelete) free((yyvsp[0].lexeme).str);}
#line 5647 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 459:
#line 2247 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5653 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 460:
#line 2248 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5659 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 461:
#line 2252 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5665 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 462:
#line 2253 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5671 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 464:
#line 2269 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5677 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 465:
#line 2273 "lefparse.y" /* yacc.c:1646  */
    {
    if ((yyvsp[0].fval) >= 0.0)
        (yyval.ival) = (int)((yyvsp[0].fval)*(pdb->context._units)+0.5);
    else
        (yyval.ival) = (int)((yyvsp[0].fval)*(pdb->context._units)-0.5);
    }
#line 5688 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 466:
#line 2282 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5694 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 467:
#line 2286 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5700 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 468:
#line 2287 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5706 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 469:
#line 2291 "lefparse.y" /* yacc.c:1646  */
    {}
#line 5712 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 470:
#line 2295 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5718 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 471:
#line 2297 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5724 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 472:
#line 2298 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5730 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 473:
#line 2299 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5736 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 474:
#line 2300 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5742 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 475:
#line 2301 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5748 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 476:
#line 2302 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5754 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 477:
#line 2303 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5760 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 478:
#line 2304 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5766 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 479:
#line 2305 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5772 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 480:
#line 2306 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5778 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 481:
#line 2307 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5784 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 482:
#line 2308 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5790 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 483:
#line 2309 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5796 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 484:
#line 2310 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5802 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 485:
#line 2311 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5808 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 486:
#line 2312 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5814 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 487:
#line 2313 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5820 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 488:
#line 2314 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5826 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 489:
#line 2315 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5832 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 490:
#line 2316 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5838 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 491:
#line 2317 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5844 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 492:
#line 2318 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5850 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 493:
#line 2319 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5856 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 494:
#line 2320 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5862 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 495:
#line 2321 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5868 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 496:
#line 2322 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5874 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 497:
#line 2323 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5880 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 498:
#line 2324 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5886 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 499:
#line 2325 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5892 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 500:
#line 2326 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5898 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 501:
#line 2327 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5904 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 502:
#line 2328 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5910 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 503:
#line 2329 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5916 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 504:
#line 2330 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5922 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 505:
#line 2331 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5928 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 506:
#line 2332 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5934 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 507:
#line 2333 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5940 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 508:
#line 2334 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5946 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 509:
#line 2335 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5952 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 510:
#line 2336 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5958 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 511:
#line 2337 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5964 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 512:
#line 2338 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5970 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 513:
#line 2339 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5976 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 514:
#line 2340 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5982 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 515:
#line 2341 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5988 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 516:
#line 2342 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 5994 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 517:
#line 2343 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6000 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 518:
#line 2344 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6006 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 519:
#line 2345 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6012 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 520:
#line 2346 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6018 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 521:
#line 2347 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6024 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 522:
#line 2348 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6030 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 523:
#line 2349 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6036 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 524:
#line 2350 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6042 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 525:
#line 2351 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6048 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 526:
#line 2352 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6054 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 527:
#line 2353 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6060 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 528:
#line 2354 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6066 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 529:
#line 2355 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6072 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 530:
#line 2356 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6078 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 531:
#line 2357 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6084 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 532:
#line 2358 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6090 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 533:
#line 2359 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6096 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 534:
#line 2360 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6102 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 535:
#line 2361 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6108 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 536:
#line 2362 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6114 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 537:
#line 2363 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6120 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 538:
#line 2364 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6126 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 539:
#line 2365 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6132 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 540:
#line 2366 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6138 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 541:
#line 2367 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6144 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 542:
#line 2368 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6150 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 543:
#line 2369 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6156 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 544:
#line 2370 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6162 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 545:
#line 2371 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6168 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 546:
#line 2372 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6174 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 547:
#line 2373 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6180 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 548:
#line 2374 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6186 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 549:
#line 2375 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6192 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 550:
#line 2376 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6198 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 551:
#line 2377 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6204 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 552:
#line 2378 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6210 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 553:
#line 2379 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6216 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 554:
#line 2380 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6222 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 555:
#line 2381 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6228 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 556:
#line 2382 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6234 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 557:
#line 2383 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6240 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 558:
#line 2384 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6246 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 559:
#line 2385 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6252 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 560:
#line 2386 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6258 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 561:
#line 2387 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6264 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 562:
#line 2388 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6270 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 563:
#line 2389 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6276 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 564:
#line 2390 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6282 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 565:
#line 2391 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6288 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 566:
#line 2392 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6294 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 567:
#line 2393 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6300 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 568:
#line 2394 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6306 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 569:
#line 2395 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6312 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 570:
#line 2396 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6318 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 571:
#line 2397 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6324 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 572:
#line 2398 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6330 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 573:
#line 2399 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6336 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 574:
#line 2400 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6342 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 575:
#line 2401 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6348 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 576:
#line 2402 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6354 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 577:
#line 2403 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6360 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 578:
#line 2404 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6366 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 579:
#line 2405 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6372 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 580:
#line 2406 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6378 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 581:
#line 2407 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6384 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 582:
#line 2408 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6390 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 583:
#line 2409 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6396 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 584:
#line 2410 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6402 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 585:
#line 2411 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6408 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 586:
#line 2412 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6414 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 587:
#line 2413 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6420 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 588:
#line 2414 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6426 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 589:
#line 2415 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6432 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 590:
#line 2416 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6438 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 591:
#line 2417 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6444 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 592:
#line 2418 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6450 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 593:
#line 2419 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6456 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 594:
#line 2420 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6462 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 595:
#line 2421 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6468 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 596:
#line 2422 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6474 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 597:
#line 2423 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6480 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 598:
#line 2424 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6486 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 599:
#line 2425 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6492 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 600:
#line 2426 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6498 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 601:
#line 2427 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6504 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 602:
#line 2428 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6510 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 603:
#line 2429 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6516 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 604:
#line 2430 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6522 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 605:
#line 2431 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6528 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 606:
#line 2432 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6534 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 607:
#line 2433 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6540 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 608:
#line 2434 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6546 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 609:
#line 2435 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6552 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 610:
#line 2436 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6558 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 611:
#line 2437 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6564 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 612:
#line 2438 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6570 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 613:
#line 2439 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6576 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 614:
#line 2440 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6582 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 615:
#line 2441 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6588 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 616:
#line 2442 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6594 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 617:
#line 2443 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6600 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 618:
#line 2444 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6606 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 619:
#line 2445 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6612 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 620:
#line 2446 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6618 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 621:
#line 2447 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6624 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 622:
#line 2448 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6630 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 623:
#line 2449 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6636 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 624:
#line 2450 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6642 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 625:
#line 2451 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6648 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 626:
#line 2452 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6654 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 627:
#line 2453 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6660 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 628:
#line 2454 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6666 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 629:
#line 2455 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6672 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 630:
#line 2456 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6678 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 631:
#line 2457 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6684 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 632:
#line 2458 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6690 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 633:
#line 2459 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6696 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 634:
#line 2460 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6702 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 635:
#line 2461 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6708 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 636:
#line 2462 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6714 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 637:
#line 2463 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6720 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 638:
#line 2464 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6726 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 639:
#line 2465 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6732 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 640:
#line 2466 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6738 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 641:
#line 2467 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6744 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 642:
#line 2468 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6750 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 643:
#line 2469 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6756 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 644:
#line 2470 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6762 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 645:
#line 2471 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6768 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 646:
#line 2472 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6774 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 647:
#line 2473 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6780 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 648:
#line 2474 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6786 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 649:
#line 2475 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6792 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 650:
#line 2476 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6798 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 651:
#line 2477 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6804 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 652:
#line 2478 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6810 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 653:
#line 2479 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6816 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 654:
#line 2480 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6822 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 655:
#line 2481 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6828 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 656:
#line 2482 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6834 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 657:
#line 2483 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6840 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 658:
#line 2484 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6846 "lefparse.tab.c" /* yacc.c:1646  */
    break;

  case 659:
#line 2485 "lefparse.y" /* yacc.c:1646  */
    {(yyval.lexeme)=(yyvsp[0].lexeme);}
#line 6852 "lefparse.tab.c" /* yacc.c:1646  */
    break;


#line 6856 "lefparse.tab.c" /* yacc.c:1646  */
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
      yyerror (YY_((char *)"syntax error"));
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
  yyerror (YY_((char *)"memory exhausted"));
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
#line 2492 "lefparse.y" /* yacc.c:1906  */

/*
   main () 
   {
   yyparse();
   }
   
   */


void leferror ( char *s) 
{ 
  printf("%s\n\tIn line %d of LEF\n",s,lefLinenum+1);
  fprintf(stderr,"%s\n\tIn line %d of LEF\n",s,lefLinenum+1);
  fflush(stdout);
  fflush(stderr);
  exit(-1);
}
