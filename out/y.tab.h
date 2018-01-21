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
    COMMA = 270,
    EQUAL = 271,
    EQUAL_EQUAL = 272,
    GREATER = 273,
    GREATER_EQUAL = 274,
    LESS = 275,
    LESS_EQUAL = 276,
    WRITE = 277,
    WRITELN = 278,
    HALT = 279,
    VAR = 280,
    TRUE = 281,
    FALSE = 282,
    BEGIN_SCOPE = 283,
    END_SCOPE = 284,
    TYPE = 285,
    ID = 286,
    STRING = 287,
    PI = 288,
    E = 289,
    NUM = 290,
    UMINUS = 291
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
#define COMMA 270
#define EQUAL 271
#define EQUAL_EQUAL 272
#define GREATER 273
#define GREATER_EQUAL 274
#define LESS 275
#define LESS_EQUAL 276
#define WRITE 277
#define WRITELN 278
#define HALT 279
#define VAR 280
#define TRUE 281
#define FALSE 282
#define BEGIN_SCOPE 283
#define END_SCOPE 284
#define TYPE 285
#define ID 286
#define STRING 287
#define PI 288
#define E 289
#define NUM 290
#define UMINUS 291

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 14 "src/hsc.yacc" /* yacc.c:1909  */

	int chr;
	double dbl;
	char *str;
	Node *sym;

#line 133 "out/y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_OUT_Y_TAB_H_INCLUDED  */
