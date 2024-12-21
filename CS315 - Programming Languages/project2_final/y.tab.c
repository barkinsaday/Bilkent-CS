/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20170709

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0


#if ! defined(YYSTYPE) && ! defined(YYSTYPE_IS_DECLARED)
/* Default: YYSTYPE is the semantic value type. */
typedef int YYSTYPE;
# define YYSTYPE_IS_DECLARED 1
#endif

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define TEXT 257
#define THIS 258
#define BEGINN 259
#define ENDD 260
#define IF 261
#define IFF 262
#define ELSE 263
#define LOOP 264
#define BOOL_TRUE 265
#define BOOL_FALSE 266
#define SENSOR 267
#define STRING 268
#define BOOLEAN 269
#define INT 270
#define FLOAT 271
#define LIST 272
#define OBJECT 273
#define VOID 274
#define FUNCTION 275
#define STATIC 276
#define RETURN 277
#define CONNECT_TO_URL 278
#define GET_TIME 279
#define GET_INPUT 280
#define SEND_INPUT 281
#define PRINT 282
#define LENGTH 283
#define GET_SENSORS 284
#define GET_SENSOR_INPUT 285
#define TURN_ON_SWITCH 286
#define TURN_OFF_SWITCH 287
#define GET_SWITCH 288
#define GET_NAME 289
#define IS_EQUAL_OP 290
#define IS_NOT_EQUAL_OP 291
#define GREATER_OP 292
#define GREATER_OR_EQUAL_OP 293
#define LESS_OR_EQUAL_OP 294
#define LESS_OP 295
#define ASSIGN_OP 296
#define ADD_OP 297
#define SUB_OP 298
#define MUL_OP 299
#define DIV_OP 300
#define AND_OP 301
#define OR_OP 302
#define NOT_OP 303
#define SEMI_COLON 304
#define COLON 305
#define COMMA 306
#define DOT 307
#define LCURL 308
#define RCURL 309
#define LP 310
#define RP 311
#define LSQUARE 312
#define RSQUARE 313
#define IDENTIFIER 314
#define INT_VALUE 315
#define FLOAT_VALUE 316
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    1,    1,    2,    2,    2,    3,    4,    5,    5,
    5,    5,    5,    7,    7,    9,   14,   14,   14,   14,
   13,   13,   13,   13,   13,   13,   16,   16,   16,   19,
   19,   19,   20,   20,   20,   20,    6,    6,   22,   22,
   23,   23,   24,   24,   24,   15,    8,    8,    8,   11,
   11,   11,   11,   30,   30,   30,   30,   28,   28,   28,
   28,   28,   28,   28,   28,   28,   28,   28,   28,   28,
   27,   27,   29,   29,   12,   12,   12,   12,   31,   31,
   31,   31,   25,   25,   21,   21,   17,   17,   32,   32,
   33,   33,   18,   10,   26,   26,   26,   26,   26,   26,
};
static const YYINT yylen[] = {                            2,
    3,    1,    2,    1,    1,    2,   11,    7,    1,    1,
    1,    1,    1,    4,    3,    2,    1,    1,    3,    3,
    1,    1,    1,    1,    1,    1,    3,    3,    1,    3,
    3,    1,    3,    1,    1,    1,    3,    1,    3,    1,
    2,    1,    3,    1,    3,    4,    4,    3,    1,   10,
   10,    9,    9,    9,    9,    8,    8,    6,    4,    3,
    5,    6,    5,    5,    5,    5,    6,    6,    6,    5,
    3,    1,    4,    2,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    4,    3,    4,    6,
    1,    3,    3,    7,    1,    1,    1,    1,    1,    1,
};
static const YYINT yydefred[] = {                         0,
    0,    0,    0,    0,    0,    0,   78,   82,   79,   80,
   81,   76,   77,    0,    0,    0,    0,    0,    0,    0,
    4,    5,    0,    9,   10,   11,   12,   13,    0,    0,
   18,   49,   75,    0,    0,    0,    0,    0,    0,   22,
   83,   84,    0,    0,    0,    0,    0,   85,   86,    0,
   36,   16,    0,    0,    0,   23,   24,    0,   32,   35,
    0,   40,   42,   44,    0,    0,    0,    1,    3,    6,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   41,    0,    0,    0,    0,    0,    0,    0,   95,
   96,   97,   98,  100,   99,    0,    0,    0,    0,    0,
    0,   60,    0,    0,    0,   15,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   20,   48,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   88,    0,
    0,    0,   43,   33,    0,   93,    0,    0,    0,    0,
    0,   30,   31,   39,   59,   46,   14,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   47,   64,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   87,   71,
    0,    0,   61,    0,   63,   65,   66,    0,    0,    0,
   70,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   92,   58,   62,   67,   68,   69,    8,    0,
   94,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   90,    0,    0,    0,    0,
    0,   53,   73,    0,   52,    0,    0,    0,    0,    0,
    0,   51,   50,    0,    0,    0,    0,    7,   57,    0,
   56,    0,   55,   54,
};
static const YYINT yydgoto[] = {                          2,
   19,   20,   21,   22,   23,   50,   24,   51,   26,   27,
   28,   29,   87,   53,   31,   55,   56,   57,   58,   59,
   60,   61,   62,   63,   64,   98,   88,   32,  187,  131,
   33,   84,  132,
};
static const YYINT yysindex[] = {                      -243,
   48,    0, -289, -290, -286, -282,    0,    0,    0,    0,
    0,    0,    0,  386, -191, -264, -256, -273, -201,   48,
    0,    0, -242,    0,    0,    0,    0,    0, -238, -285,
    0,    0,    0, -213,  -21,  -21,  -21, -197, -186,    0,
    0,    0,  -11,  -79,  -21, -191, -273,    0,    0, -208,
    0,    0, -254,    0,  334,    0,    0, -195,    0,    0,
 -192,    0,    0,    0, -200, -191, -191,    0,    0,    0,
 -183, -191,  158, -231, -190, -297,  334, -271, -270, -196,
 -178,    0, -177, -140, -266,  325, -166, -165,  -21,    0,
    0,    0,    0,    0,    0, -144, -144, -144, -144, -144,
  -21,    0, -162, -163, -191,    0, -159, -158, -156, -155,
 -153, -152, -143, -142, -137, -136, -273,    0,    0, -135,
 -126, -133, -112, -110, -124, -111, -105,  -73,    0,  -69,
  -99,  -96,    0,    0, -191,    0, -192, -144, -195, -195,
 -229,    0,    0,    0,    0,    0,    0, -191, -101, -191,
  -89,  -88,  -86, -191, -191, -191,  -84,    0,    0,   48,
   48,   48,  -90,   77, -191,  -85,  -83,  394,    0,    0,
 -268,  -78,    0,  -76,    0,    0,    0,  -72,  -68,  -63,
    0,  -94,  -60,  -59,  -57,  -62,  -58,  -52,  -54,  -47,
  -50,  -48,    0,    0,    0,    0,    0,    0,    0,    1,
    0,   48,  -43,  -42,   48,  -41,  -79,  124,  341,  -39,
  -44,  -79,   48,  -29,   48,    0,  -38,  -30,  -25,  -27,
   48,    0,    0,  -17,    0,  -13,   48,  -20,   48,  -10,
   -8,    0,    0,   -7,   48,   -2,   48,    0,    0,    2,
    0,    4,    0,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -263,    0, -259,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   66,    0,    0,  286,
    0,    0,    0,  215,  333,    0,    0,  113,    0,    0,
  270,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, -301,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, -258,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   13,    0,    0,    0,    0,    0,  278,    0,  160,  207,
  262,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    5,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -14,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
  -18,    0,    0,    0,    0,   63,    0,   -1,    0,    0,
    0,   78,  -12,    3,   -9,  -28,    0,    0,   10,   16,
    0,  202,  199,  265,    0,    0,  -53,    0, -122,    0,
    0,  116,  161,
};
#define YYTABLESIZE 668
static const YYINT yytable[] = {                         25,
    2,   69,   52,   30,   89,   54,   77,   77,   77,   72,
   72,   72,  103,  122,   77,    1,   86,   34,   25,   35,
  120,   73,   30,   36,   74,   40,    3,   37,   96,   97,
   89,   89,   17,   41,   42,   89,   54,   19,   67,  123,
  124,  189,  134,   17,  133,   65,   17,   16,   19,    2,
   17,   19,   73,   66,  104,   74,   54,   54,   68,  106,
   77,   70,   54,  118,   54,   40,    3,   96,   97,  141,
   75,   43,   77,   41,   42,   71,   44,   80,   45,  119,
   46,  170,   47,   48,   49,  218,  220,   16,   81,  223,
   17,   39,  147,   89,  172,   54,  174,   76,   78,   79,
  178,  179,  180,   99,  100,  139,  140,   85,  101,  171,
  102,   43,  105,    3,  142,  143,   44,  125,   45,  121,
   46,   83,   47,   48,   49,   54,    7,    8,    9,   10,
   11,   12,   13,  128,   16,  126,  127,   17,   54,  135,
   54,  182,  183,  184,   54,   54,   54,  136,  145,  146,
  148,  149,  190,  150,  151,   54,  152,  153,   25,   25,
   25,  130,   30,   30,   30,  138,  154,  155,  129,   47,
   48,   49,  156,  157,  160,  158,    7,    8,    9,   10,
   11,   12,   13,  211,  159,  163,  214,    7,    8,    9,
   10,   11,   12,   13,  224,  161,  226,  162,  164,  165,
   25,  166,  231,   25,   30,  167,  168,   30,  234,  173,
  236,   25,  169,   25,  199,   30,  240,   30,  242,   25,
  185,  175,  176,   30,  177,   25,  181,   25,  191,   30,
  192,   30,  194,   25,  195,   25,    3,   30,  196,   30,
  186,  186,  197,   41,   42,  130,    3,  198,  200,  201,
  202,  203,  204,   41,   42,  205,  206,   16,  207,  208,
   17,  209,  212,  210,  222,  213,  215,   16,  221,  227,
   17,   89,   89,   89,   89,   89,   89,   89,   89,  225,
  228,   43,  229,  230,   83,  186,  186,  235,   45,  186,
  137,  232,   47,   48,   49,  233,   74,  237,   45,  144,
  238,  239,   47,   48,   49,    3,  241,   82,    4,    5,
  243,    6,  244,   89,    7,    8,    9,   10,   11,   12,
   13,   91,  216,   14,   15,    0,   16,    0,  193,   17,
    0,    0,   34,   34,   34,   34,   34,   34,   34,   34,
    0,    0,    0,    7,    8,    9,   10,   11,   12,   13,
    0,    0,    0,    0,    0,   34,   34,   34,   34,   34,
   34,   18,   34,   34,   34,   34,   34,   34,    0,   34,
    0,   34,   17,    0,   34,   17,   34,    0,   34,   29,
   29,   29,   29,   29,   29,   29,   29,  188,    0,    0,
    7,    8,    9,   10,   11,   12,   13,    0,    0,    0,
    0,    0,   29,   29,   29,   29,   29,   29,    0,   29,
   29,    0,    0,   29,   29,    0,   29,    0,   29,    0,
    0,   29,    0,   29,    0,   29,   27,   27,   27,   27,
   27,   27,   27,   27,  217,  107,    0,  108,  109,    0,
  110,  111,  112,  113,  114,  115,  116,    0,    0,   27,
   27,   27,   27,   27,   27,    0,   27,   27,    0,    0,
   27,   27,    0,   27,    0,   27,    0,    0,   27,    0,
   27,  117,   27,   28,   28,   28,   28,   28,   28,   28,
   28,   26,   26,   26,   26,   26,   26,   26,   26,    0,
    0,    0,    0,    0,    0,    0,   28,   28,   28,   28,
   28,   28,    0,   28,   28,    0,    0,   28,   28,    0,
   28,    0,   28,    0,    0,   28,    0,   28,   26,   28,
   26,   18,    0,   26,   18,   26,    0,   26,   45,   45,
   45,   45,   45,   45,   45,   45,   38,   38,   38,   38,
   38,   38,   38,   38,   37,   37,   37,   37,   37,   37,
   37,   37,   25,   25,   25,   25,   25,   25,   25,   25,
    0,    0,   45,   45,    0,   45,    0,   45,    0,    0,
   45,   38,   45,   38,   45,   38,    0,    0,   38,   37,
   38,   37,   38,   37,    0,    0,   37,    0,   37,   25,
   37,   25,    0,    0,   25,    0,   25,    0,   25,   21,
   21,   21,   21,   21,   21,   21,   21,    7,    8,    9,
   10,   11,   12,   13,   90,   91,   92,   93,   94,   95,
    0,   96,   97,   90,   91,   92,   93,   94,   95,    0,
   96,   97,    0,    0,    0,  134,   21,    0,   21,    0,
    0,   21,    0,   21,    0,   21,    0,    0,    0,    0,
    0,  219,    7,    8,    9,   10,   11,   12,   13,   38,
    7,    8,    9,   10,   11,   12,   13,  128,
};
static const YYINT yycheck[] = {                          1,
  260,   20,   15,    1,  302,   15,   35,   36,   37,  311,
  296,  313,   66,  311,   43,  259,   45,  307,   20,  310,
   74,  307,   20,  310,  310,  257,  258,  310,  297,  298,
  302,  302,  296,  265,  266,  302,   46,  296,  312,  311,
  311,  164,  311,  307,  311,  310,  310,  279,  307,  309,
  282,  310,  307,  310,   67,  310,   66,   67,  260,   72,
   89,  304,   72,   73,   74,  257,  258,  297,  298,   98,
  284,  303,  101,  265,  266,  314,  308,  275,  310,  311,
  312,  135,  314,  315,  316,  208,  209,  279,  275,  212,
  282,   14,  105,  302,  148,  105,  150,   35,   36,   37,
  154,  155,  156,  299,  300,   96,   97,   45,  301,  138,
  311,  303,  296,  258,   99,  100,  308,  314,  310,  310,
  312,   44,  314,  315,  316,  135,  267,  268,  269,  270,
  271,  272,  273,  274,  279,  314,  314,  282,  148,  306,
  150,  160,  161,  162,  154,  155,  156,  313,  311,  313,
  310,  310,  165,  310,  310,  165,  310,  310,  160,  161,
  162,   84,  160,  161,  162,  310,  310,  310,  309,  314,
  315,  316,  310,  310,  308,  311,  267,  268,  269,  270,
  271,  272,  273,  202,  311,  310,  205,  267,  268,  269,
  270,  271,  272,  273,  213,  308,  215,  308,  310,  305,
  202,  275,  221,  205,  202,  275,  306,  205,  227,  311,
  229,  213,  309,  215,  309,  213,  235,  215,  237,  221,
  311,  311,  311,  221,  311,  227,  311,  229,  314,  227,
  314,  229,  311,  235,  311,  237,  258,  235,  311,  237,
  163,  164,  311,  265,  266,  168,  258,  311,  309,  309,
  308,  314,  311,  265,  266,  308,  311,  279,  306,  310,
  282,  310,  306,  263,  309,  308,  308,  279,  308,  308,
  282,  267,  268,  269,  270,  271,  272,  273,  274,  309,
  311,  303,  308,  311,  207,  208,  209,  308,  310,  212,
   89,  309,  314,  315,  316,  309,  311,  308,  310,  101,
  309,  309,  314,  315,  316,  258,  309,   43,  261,  262,
  309,  264,  309,  309,  267,  268,  269,  270,  271,  272,
  273,  309,  207,  276,  277,   -1,  279,   -1,  168,  282,
   -1,   -1,  267,  268,  269,  270,  271,  272,  273,  274,
   -1,   -1,   -1,  267,  268,  269,  270,  271,  272,  273,
   -1,   -1,   -1,   -1,   -1,  290,  291,  292,  293,  294,
  295,  314,  297,  298,  299,  300,  301,  302,   -1,  304,
   -1,  306,  307,   -1,  309,  310,  311,   -1,  313,  267,
  268,  269,  270,  271,  272,  273,  274,  311,   -1,   -1,
  267,  268,  269,  270,  271,  272,  273,   -1,   -1,   -1,
   -1,   -1,  290,  291,  292,  293,  294,  295,   -1,  297,
  298,   -1,   -1,  301,  302,   -1,  304,   -1,  306,   -1,
   -1,  309,   -1,  311,   -1,  313,  267,  268,  269,  270,
  271,  272,  273,  274,  311,  278,   -1,  280,  281,   -1,
  283,  284,  285,  286,  287,  288,  289,   -1,   -1,  290,
  291,  292,  293,  294,  295,   -1,  297,  298,   -1,   -1,
  301,  302,   -1,  304,   -1,  306,   -1,   -1,  309,   -1,
  311,  314,  313,  267,  268,  269,  270,  271,  272,  273,
  274,  267,  268,  269,  270,  271,  272,  273,  274,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  290,  291,  292,  293,
  294,  295,   -1,  297,  298,   -1,   -1,  301,  302,   -1,
  304,   -1,  306,   -1,   -1,  309,   -1,  311,  304,  313,
  306,  307,   -1,  309,  310,  311,   -1,  313,  267,  268,
  269,  270,  271,  272,  273,  274,  267,  268,  269,  270,
  271,  272,  273,  274,  267,  268,  269,  270,  271,  272,
  273,  274,  267,  268,  269,  270,  271,  272,  273,  274,
   -1,   -1,  301,  302,   -1,  304,   -1,  306,   -1,   -1,
  309,  302,  311,  304,  313,  306,   -1,   -1,  309,  302,
  311,  304,  313,  306,   -1,   -1,  309,   -1,  311,  304,
  313,  306,   -1,   -1,  309,   -1,  311,   -1,  313,  267,
  268,  269,  270,  271,  272,  273,  274,  267,  268,  269,
  270,  271,  272,  273,  290,  291,  292,  293,  294,  295,
   -1,  297,  298,  290,  291,  292,  293,  294,  295,   -1,
  297,  298,   -1,   -1,   -1,  311,  304,   -1,  306,   -1,
   -1,  309,   -1,  311,   -1,  313,   -1,   -1,   -1,   -1,
   -1,  311,  267,  268,  269,  270,  271,  272,  273,  274,
  267,  268,  269,  270,  271,  272,  273,  274,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 316
#define YYUNDFTOKEN 352
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"TEXT","THIS","BEGINN","ENDD",
"IF","IFF","ELSE","LOOP","BOOL_TRUE","BOOL_FALSE","SENSOR","STRING","BOOLEAN",
"INT","FLOAT","LIST","OBJECT","VOID","FUNCTION","STATIC","RETURN",
"CONNECT_TO_URL","GET_TIME","GET_INPUT","SEND_INPUT","PRINT","LENGTH",
"GET_SENSORS","GET_SENSOR_INPUT","TURN_ON_SWITCH","TURN_OFF_SWITCH",
"GET_SWITCH","GET_NAME","IS_EQUAL_OP","IS_NOT_EQUAL_OP","GREATER_OP",
"GREATER_OR_EQUAL_OP","LESS_OR_EQUAL_OP","LESS_OP","ASSIGN_OP","ADD_OP",
"SUB_OP","MUL_OP","DIV_OP","AND_OP","OR_OP","NOT_OP","SEMI_COLON","COLON",
"COMMA","DOT","LCURL","RCURL","LP","RP","LSQUARE","RSQUARE","IDENTIFIER",
"INT_VALUE","FLOAT_VALUE",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : program",
"program : BEGINN stmts ENDD",
"stmts : stmt",
"stmts : stmt stmts",
"stmt : matched",
"stmt : unmatched",
"stmt : non_if_stmt SEMI_COLON",
"matched : IFF LP bool_ex RP LCURL stmts RCURL ELSE LCURL stmts RCURL",
"unmatched : IF LP bool_ex RP LCURL stmts RCURL",
"non_if_stmt : assign",
"non_if_stmt : func_call",
"non_if_stmt : return_stmt",
"non_if_stmt : loop",
"non_if_stmt : static_func",
"assign : type IDENTIFIER ASSIGN_OP expr",
"assign : chain ASSIGN_OP expr",
"return_stmt : RETURN expr",
"chain : IDENTIFIER",
"chain : call_array",
"chain : chain DOT IDENTIFIER",
"chain : chain DOT call_array",
"expr : arith_expr",
"expr : TEXT",
"expr : object",
"expr : array",
"expr : bool_ex",
"expr : call_array",
"arith_expr : arith_expr ADD_OP term",
"arith_expr : arith_expr SUB_OP term",
"arith_expr : term",
"term : term MUL_OP exp",
"term : term DIV_OP exp",
"term : exp",
"exp : LP arith_expr RP",
"exp : IDENTIFIER",
"exp : constant_value",
"exp : func_call",
"bool_ex : bool_ex OR_OP bool_term",
"bool_ex : bool_term",
"bool_term : bool_term AND_OP bool_factor",
"bool_term : bool_factor",
"bool_factor : NOT_OP bool_exp",
"bool_factor : bool_exp",
"bool_exp : LP bool_ex RP",
"bool_exp : bool_value",
"bool_exp : arith_expr comparison arith_expr",
"call_array : IDENTIFIER LSQUARE expr RSQUARE",
"func_call : chain LP call_list RP",
"func_call : chain LP RP",
"func_call : built_in_func",
"static_func : STATIC type FUNCTION IDENTIFIER LP decleration_list RP LCURL stmts RCURL",
"static_func : STATIC VOID FUNCTION IDENTIFIER LP decleration_list RP LCURL stmts RCURL",
"static_func : STATIC type FUNCTION IDENTIFIER LP RP LCURL stmts RCURL",
"static_func : STATIC VOID FUNCTION IDENTIFIER LP RP LCURL stmts RCURL",
"object_func : type FUNCTION IDENTIFIER LP decleration_list RP LCURL stmts RCURL",
"object_func : VOID FUNCTION IDENTIFIER LP decleration_list RP LCURL stmts RCURL",
"object_func : type FUNCTION IDENTIFIER LP RP LCURL stmts RCURL",
"object_func : VOID FUNCTION IDENTIFIER LP RP LCURL stmts RCURL",
"built_in_func : chain DOT CONNECT_TO_URL LP call_list RP",
"built_in_func : PRINT LP call_list RP",
"built_in_func : GET_TIME LP RP",
"built_in_func : chain DOT GET_INPUT LP RP",
"built_in_func : chain DOT SEND_INPUT LP call_list RP",
"built_in_func : chain DOT LENGTH LP RP",
"built_in_func : THIS DOT GET_SENSORS LP RP",
"built_in_func : chain DOT GET_SENSORS LP RP",
"built_in_func : chain DOT GET_SENSOR_INPUT LP RP",
"built_in_func : chain DOT TURN_ON_SWITCH LP call_list RP",
"built_in_func : chain DOT TURN_OFF_SWITCH LP call_list RP",
"built_in_func : chain DOT GET_SWITCH LP call_list RP",
"built_in_func : chain DOT GET_NAME LP RP",
"call_list : expr COMMA call_list",
"call_list : expr",
"decleration_list : type IDENTIFIER COMMA decleration_list",
"decleration_list : type IDENTIFIER",
"type : prim",
"type : LIST",
"type : OBJECT",
"type : SENSOR",
"prim : BOOLEAN",
"prim : INT",
"prim : FLOAT",
"prim : STRING",
"bool_value : BOOL_TRUE",
"bool_value : BOOL_FALSE",
"constant_value : INT_VALUE",
"constant_value : FLOAT_VALUE",
"object : LCURL properties methods RCURL",
"object : LCURL properties RCURL",
"properties : type IDENTIFIER COLON expr",
"properties : type IDENTIFIER COLON expr COMMA properties",
"methods : object_func",
"methods : object_func COMMA methods",
"array : LSQUARE call_list RSQUARE",
"loop : LOOP LP bool_ex RP LCURL stmts RCURL",
"comparison : IS_EQUAL_OP",
"comparison : IS_NOT_EQUAL_OP",
"comparison : GREATER_OP",
"comparison : GREATER_OR_EQUAL_OP",
"comparison : LESS_OP",
"comparison : LESS_OR_EQUAL_OP",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 148 "example.y"
#include "lex.yy.c"
int yyerror(char* s){
  fprintf(stderr, "%s on line %d\n",s, yylineno);
  return 1;
}

int main(){
  yyparse();
  return 0;
}
#line 555 "y.tab.c"

#if YYDEBUG
#include <stdio.h>	/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yym = 0;
    yyn = 0;
    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        yychar = YYLEX;
        if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if (((yyn = yysindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if (((yyn = yyrindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag != 0) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab; /* redundant goto avoids 'unused label' warning */
yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if (((yyn = yysindex[*yystack.s_mark]) != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym > 0)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);

    switch (yyn)
    {
case 1:
#line 6 "example.y"
	{printf("Input program is valid!\n"); return 0;}
break;
#line 758 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            yychar = YYLEX;
            if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if (((yyn = yygindex[yym]) != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
