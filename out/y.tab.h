/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_OUT_Y_TAB_H_INCLUDED
# define YY_YY_OUT_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ADD = 258,
    SUB = 259,
    MUL = 260,
    DIV = 261,
    AND = 262,
    OR = 263,
    NOT = 264,
    NEWLINE = 265,
    ROUND_OPEN = 266,
    ROUND_CLOSE = 267,
    COLON = 268,
    ASSIGNMENT = 269,
    WRITE = 270,
    WRITELN = 271,
    HALT = 272,
    VAR = 273,
    TRUE = 274,
    FALSE = 275,
    TYPE = 276,
    ID = 277,
    STRING = 278,
    PI = 279,
    E = 280,
    NUM = 281,
    UMINUS = 282
  };
#endif
/* Tokens.  */
#define ADD 258
#define SUB 259
#define MUL 260
#define DIV 261
#define AND 262
#define OR 263
#define NOT 264
#define NEWLINE 265
#define ROUND_OPEN 266
#define ROUND_CLOSE 267
#define COLON 268
#define ASSIGNMENT 269
#define WRITE 270
#define WRITELN 271
#define HALT 272
#define VAR 273
#define TRUE 274
#define FALSE 275
#define TYPE 276
#define ID 277
#define STRING 278
#define PI 279
#define E 280
#define NUM 281
#define UMINUS 282

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 14 "src/hsc.yacc" /* yacc.c:1909  */

	int chr;
	double dbl;
	char *str;
	Node *sym;

#line 115 "out/y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_OUT_Y_TAB_H_INCLUDED  */