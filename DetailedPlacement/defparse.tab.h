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
#line 156 "defparse.y" /* yacc.c:1909  */

    double       dval ;
    int          integer ;
    lexemeStruct string ;
    int          keyword ;  /* really just a nop */
    struct       LEFDEFpoint pt;
    BBoxSimple   bbox;
    /* TOKEN *tk; */

#line 223 "defparse.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE deflval;

int defparse (void);

#endif /* !YY_DEF_DEFPARSE_TAB_H_INCLUDED  */
