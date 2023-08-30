/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

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
#line 115 "lef.y" /* yacc.c:1909  */

	double dval ;
	int    integer ;
	char * string ;
	POINT  pt;

#line 363 "lef.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE lefyylval;

int lefyyparse (void);

#endif /* !YY_LEFYY_LEF_TAB_H_INCLUDED  */
