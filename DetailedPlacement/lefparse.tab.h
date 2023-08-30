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
#line 142 "lefparse.y" /* yacc.c:1909  */

    int keyword;
    float fval;
    int ival;
    lexemeStruct lexeme;
    unsigned uval;
    LEFDEFpoint pt;
    void *ignore;
    LEFDEFrectangle rectVal;

#line 295 "lefparse.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE leflval;

int lefparse (void);

#endif /* !YY_LEF_LEFPARSE_TAB_H_INCLUDED  */
